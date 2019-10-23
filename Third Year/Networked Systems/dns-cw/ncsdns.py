#!/usr/bin/python

from copy import copy
from optparse import OptionParser, OptionValueError
import pprint
from random import seed, randint
import struct
from socket import *
from sys import exit, maxsize as MAXINT
from time import time, sleep

from libs.collections_backport import OrderedDict
from libs.dnslib.RR import *
from libs.dnslib.Header import Header
from libs.dnslib.QE import QE
from libs.inetlib.types import *
from libs.util import *

# timeout in seconds to wait for reply
TIMEOUT = 5

# domain name and internet address of a root name server
ROOTNS_DN = "f.root-servers.net."
ROOTNS_IN_ADDR = "192.5.5.241"

# cache objects
class RR_A_Cache:
    def __init__(self):
        self.cache = dict()     # domain_name -> [(ip_address, expiration_time, authoritative)]

    def put(self,domain_name,ip_addr,expiration,authoritative=False):
        if domain_name not in self.cache:
            self.cache[domain_name] = dict()
        self.cache[domain_name][ip_addr] = (expiration,authoritative)

    def contains(self,domain_name):
        return domain_name in self.cache
    
    def getIpAddresses(self,domain_name):
        return list(self.cache[domain_name].keys())

    def getExpiration(self,domain_name,ip_address):
        return self.cache[domain_name][ip_address][0]
    
    def getAuthoritative(self,domain_name,ip_address):
        return self.cache[domain_name][ip_address][1]

    def __str__(self):
        return str(self.cache)

class CN_Cache:
    def __init__(self):
        self.cache = dict()     # domain_name -> (cname, expiration_time)

    def put(self,domain_name,canonical_name,expiration):
        self.cache[domain_name] = (canonical_name,expiration)

    def contains(self,domain_name):
        return domain_name in self.cache

    def getCanonicalName(self, domain_name):
        return self.cache[domain_name][0]

    def getCanonicalNameExpiration(self,domain_name):
        return self.cache[domain_name][1]

    def __str__(self):
        return str(self.cache)

class RR_NS_Cache:
    def __init__(self):
        self.cache = dict()     # domain_name -> (NS_record,expiration_time, authoritative)
        
    def put(self,zone_domain_name,name_server_domain_name,expiration,authoritative):
        if zone_domain_name not in self.cache:
            self.cache[zone_domain_name] = OrderedDict()
        self.cache[zone_domain_name][name_server_domain_name] = (expiration,authoritative)

    def get(self,zone_domain_name):
        list_name_servers = []
        for name_server in self.cache[zone_domain_name]:
            list_name_servers += [(name_server,self.cache[zone_domain_name][name_server][0],self.cache[zone_domain_name][name_server][1])]
        return list_name_servers

    def contains(self,zone_domain_name):
        return zone_domain_name in self.cache

    def getKeys(self):
        return list(self.cache.keys())

    def __str__(self):
        return str(self.cache)


# >>> entry point of ncsdns.py <<<

# Seed random number generator with current time of day:
now = int(time())
seed(now)

# Initialize the pretty printer:
pp = pprint.PrettyPrinter(indent=3)

# Initialize the cache data structures
acache = RR_A_Cache()
acache.put(DomainName(ROOTNS_DN),InetAddr(ROOTNS_IN_ADDR),expiration=MAXINT,authoritative=True)

nscache = RR_NS_Cache()
nscache.put(DomainName("."),DomainName(ROOTNS_DN),expiration=MAXINT,authoritative=True)

cnamecache = CN_Cache()

# Parse the command line and assign us an ephemeral port to listen on:
def check_port(option, opt_str, value, parser):
    if value < 32768 or value > 61000:
        raise OptionValueError("need 32768 <= port <= 61000")
    parser.values.port = value

parser = OptionParser()
parser.add_option("-p", "--port", dest="port", type="int", action="callback",
                  callback=check_port, metavar="PORTNO", default=0,
                  help="UDP port to listen on (default: use an unused ephemeral port)")
(options, args) = parser.parse_args()

# Create a server socket to accept incoming connections from DNS
# client resolvers (stub resolvers):
ss = socket(AF_INET, SOCK_DGRAM)
ss.bind(("127.0.0.1", options.port))
serveripaddr, serverport = ss.getsockname()

# NOTE: In order to pass the test suite, the following must be the
# first line that your dns server prints and flushes within one
# second, to sys.stdout:
print("%s: listening on port %d" % (sys.argv[0], serverport))
sys.stdout.flush()

# Create a client socket on which to send requests to other DNS
# servers:
setdefaulttimeout(TIMEOUT)
cs = socket(AF_INET, SOCK_DGRAM)


#Adds records to cache
def record_parser(qEntry,rEntry,rData,acache,nscache):

    total_added = len(qEntry) + 12

    # print("In record parser ------ ")
    # print(str(qEntry))
    # print(str(rEntry))
    # print("---------")

    rIterator = rEntry

    authority = False

    while rIterator[1] > 0:

        if rIterator[0]._type == 1:
            if str(qEntry._dn) == str(rIterator[0]._dn):
                authority = True
                acache.put(rIterator[0]._dn,InetAddr(inet_ntoa(rIterator[0]._inaddr)),expiration=rIterator[0]._ttl,authoritative=True)
            else:
                acache.put(rIterator[0]._dn,InetAddr(inet_ntoa(rIterator[0]._inaddr)),expiration=rIterator[0]._ttl,authoritative=False)

        elif rIterator[0]._type == 2:

            if authority:
                nscache.put(rIterator[0]._dn,rIterator[0]._nsdn,expiration=rIterator[0]._ttl,authoritative=True)
            
            elif nscache.contains(rIterator[0]._dn):
                list_of_ns = nscache.get(rIterator[0]._dn)
                not_in = True

                for y in list_of_ns:
                    if y[0] == rIterator[0]._nsdn:
                        not_in = False

                if not_in:
                    nscache.put(rIterator[0]._dn,rIterator[0]._nsdn,expiration=rIterator[0]._ttl,authoritative=False)
            else:
                nscache.put(rIterator[0]._dn,rIterator[0]._nsdn,expiration=rIterator[0]._ttl,authoritative=False)
        
        elif rIterator[0]._type == 5:
            authority = True
            cnamecache.put(rIterator[0]._dn,rIterator[0]._cname,expiration=rIterator[0]._ttl)

        try:
            temp_resource = RR.fromData(rData,total_added + rIterator[1])

            if temp_resource[1] > 0:
                total_added += rIterator[1]
                rIterator = temp_resource

        except:
            return rEntry
            break


def find_address(inner_data,acache,nscache,nsdn_record):

    queryheader = Header.fromData(inner_data)
    #print ("Query header received from client is:\n", hexdump(queryheader.pack()))

    original_questionEntry = QE.fromData(inner_data,12)
    #print ("Question Entry received from client is:\n", hexdump(questionEntry.pack()))

    try:
        original_resourceRecord = RR.fromData(inner_data,len(original_questionEntry) + 12)
    except:
        print("No resources found")

    questionEntry = original_questionEntry
    
    # Starting off, if it doesn't contain address, will send information to root DNS
    if (not acache.contains(str(original_questionEntry._dn))) and (not cnamecache.contains(str(original_questionEntry._dn))):

        forward_addr = acache.getIpAddresses(DomainName(ROOTNS_DN))

        cs.sendto(inner_data,(str(forward_addr[0]),53))
  
        try:
            (response_data, response_address) = cs.recvfrom(512)
        except:
            try:
                (response_data, response_address) = cs.recvfrom(512)
            except:
                ss.sendto(str.encode("Root server not found, are you connected to the internet?"), client_address)

        questionEntry = QE.fromData(response_data,12)
        #print ("Question Entry received from server query is:\n", hexdump(questionEntry.pack()))

        resourceRecord = RR.fromData(response_data,len(questionEntry) + 12)

        #Keeps track of the NSDN records
        nsdn_record.append(resourceRecord[0]._dn)

        resource_entry = record_parser(questionEntry,resourceRecord,response_data,acache,nscache)
    
        second_time_empty = False

        #Checks if query is in the cache
        while not acache.contains(str(original_questionEntry._dn)):

            #A record
            if questionEntry._type == 1:

                #If the question entry is the current packet
                if str(resourceRecord[0]._dn) == str(original_questionEntry._dn):
                    
                    #Adds information to cache
                    print("Found string")
                    record_parser(questionEntry,resourceRecord,response_data,acache,nscache)

                    #Checks if it is a NS name instead of an A record, then we need to resolve it and get the IP address
                    if resourceRecord[0]._type == 2:
                        headerPart = Header(2,0,0,qdcount=1)
                        questionPart = QE(1,resourceRecord[0]._nsdn)
                        q = headerPart.pack() + questionPart.pack()
                        print(str(resourceRecord[0]))

                        address_record = find_address(q,acache,nscache,nsdn_record)
                        print(str(address_record))
                        print("Calling record parser for address record")
                        record_parser(questionPart,address_record,q,acache,nscache)
                        resourceRecord = address_record

                    #Checks if the current packet is a CNAME, if it is then we have to find the actual IP address
                    elif resourceRecord[0]._type == 5:
                        print(str(cnamecache))
                        print(resourceRecord[0]._dn)
                        cname_holder = cnamecache.getCanonicalName(DomainName(str(resourceRecord[0]._dn)))
                    
                        headerPart = Header(2,0,0,qdcount=1)
                        questionPart = QE(1,cname_holder)
                        q = headerPart.pack() + questionPart.pack()

                        resourceRecord = find_address(q,acache,nscache,nsdn_record)

                    return resourceRecord

                #If we already have the resourceRecord, we can send the next query
                elif acache.contains(str(resourceRecord[0]._nsdn)):
                    
                    total_added = len(questionEntry) + 12
                    record_success = True

                    print()
                    print("Have resource record")
                    print(resourceRecord[0]._nsdn)

                    forward_addr = acache.getIpAddresses(DomainName(str(resourceRecord[0]._nsdn)))

                    cs.sendto(inner_data,(str(forward_addr[0]),53))

                    #Sending the query, error proof so that if one A record fails then we move onto the next one
                    try:
                        (response_data, response_address) = cs.recvfrom(512)
                    except:
                        print("Timed out, trying other records")
                        temp_record = RR.fromData(response_data,len(questionEntry) + 12 + resourceRecord[1])
                        resourceRecord = temp_record
                        print("New Record = " + str(resourceRecord[0]))
                        record_success = False

                    print(hexdump(response_data))
                    print("End of response data\n")

                    if record_success:
                        questionEntry = QE.fromData(response_data,12)
                        resourceRecord = RR.fromData(response_data,len(questionEntry) + 12)
                        nsdn_record.append(resourceRecord[0]._dn)


                #Didn't receive any A records therefore they are all NS records and we need to lookup one of them up
                elif second_time_empty == True:
                    print("No A records")

                    headerPart = Header(2,0,0,qdcount=1)
                    questionPart = QE(1,resourceRecord[0]._nsdn)
                    q = headerPart.pack() + questionPart.pack()
                    print(str(resourceRecord[0]))

                    address_record = find_address(q,acache,nscache,nsdn_record)
                    print(str(address_record))
                    print("Calling record parser for address record")
                    record_parser(questionPart,address_record,q,acache,nscache)

                    second_time_empty = False

                #Don't have any of the resource records (first time adds everything)
                else:        
                    print("Don't have RR")    
                    print("For " + str(resourceRecord[0]))    
                    resource_entry = record_parser(questionEntry,resourceRecord,response_data,acache,nscache)
                    print(str(acache))
                    second_time_empty = True

        #If we now contain the answer in the cache after requesting the new packet, ensures we don't loop again with the right answer
        if acache.contains(str(original_questionEntry._dn)):
            print(questionEntry._type)
            print(str(resourceRecord[0]))
            return resourceRecord
    
    #If the cache already contains the address, can either be in the A records or CNAME
    else:
        print("We here cause we already have the answer")

        if  acache.contains(str(original_questionEntry._dn)):
            ip_addr_value = acache.getIpAddresses(DomainName(str(original_questionEntry._dn)))
            ttl = acache.getExpiration(DomainName(str(original_questionEntry._dn)),ip_addr_value[0])
            resourcePart = RR_A(DomainName(str(original_questionEntry._dn)),ttl,inet_aton(str(ip_addr_value[0])))

            return (resourcePart,resourcePart._rdlength)
        
        elif cnamecache.contains(str(original_questionEntry._dn)):
            
            key_cname_value = original_questionEntry._dn

            while cnamecache.contains(str(key_cname_value)):
                key_cname_value = cnamecache.getCanonicalName(DomainName(str(key_cname_value)))

            ip_addr_value = acache.getIpAddresses(DomainName(str(key_cname_value)))
            ttl = acache.getExpiration(DomainName(str(key_cname_value)),ip_addr_value[0])
            resourcePart = RR_A(DomainName(str(key_cname_value)),ttl,inet_aton(str(ip_addr_value[0])))


            return (resourcePart,resourcePart._rdlength)


nsdn_record = list()

# This is a simple, single-threaded server that takes successive
# connections with each iteration of the following loop:
while 1:
    (data, client_address,) = ss.recvfrom(512) # DNS limits UDP msgs to 512 bytes
    if not data:
        logger.error("client provided no data")
        continue
    
    print("------------------------------------------------------------------------------------")
    print("Query received from client is:\n%s" %(hexdump(data)))

    #
    # TODO: Insert code here to perform the recursive DNS lookup;
    #       putting the result in the "reply" variable.
    #
    # NOTE: You can (and are encouraged to) create external functions
    #       that you call from here.
    #

    queryheader = Header.fromData(data)
    #print ("Query header received from client is:\n", hexdump(queryheader.pack()))

    original_questionEntry = QE.fromData(data,12)
    #print ("Question Entry received from client is:\n", hexdump(questionEntry.pack()))
    
    list.clear(nsdn_record)

    answer_resourceRecord = find_address(data,acache,nscache,nsdn_record)

    print("Got address")

    print(str(answer_resourceRecord))

    #If the answer we receive does not match our original query, we have a CNAME 
    if str(answer_resourceRecord[0]._dn) != str(original_questionEntry._dn):

        key_cname_value = original_questionEntry._dn
        total_cname = 0

        #Counting the number of CNAME jumps for our packet header
        while cnamecache.contains(str(key_cname_value)):
            total_cname +=1
            key_cname_value = cnamecache.getCanonicalName(DomainName(str(key_cname_value)))

        #Number of valid IP addresess for the name
        ip_num = len(acache.getIpAddresses(DomainName(str(answer_resourceRecord[0]._dn))))
        
        headerPart = Header(Header.fromData(data)._id,0,0,qdcount=1,ancount=total_cname+ip_num,qr=1,nscount=1,arcount=1)
        questionPart = QE(1,original_questionEntry._dn)
        reply = headerPart.pack() + questionPart.pack()


        key_cname_value = original_questionEntry._dn

        #Adding all the CNAME resource info to the packet
        while cnamecache.contains(str(key_cname_value)):
            resourcePart = RR_CNAME(key_cname_value,cnamecache.getCanonicalNameExpiration(DomainName(str(key_cname_value))),cnamecache.getCanonicalName(DomainName(str(key_cname_value))))
            reply = reply + resourcePart.pack()
            key_cname_value = cnamecache.getCanonicalName(DomainName(str(key_cname_value)))

        #Adding the A record to the packet
        ip_addr_value = acache.getIpAddresses(DomainName(str(answer_resourceRecord[0]._dn)))

        if len(ip_addr_value) > 1:
            for x in ip_addr_value:
                resourcePart2 = RR_A(answer_resourceRecord[0]._dn,answer_resourceRecord[0]._ttl,inet_aton(str(x)))
                reply = reply + resourcePart2.pack()
        else:
            resourcePart2 = RR_A(answer_resourceRecord[0]._dn,answer_resourceRecord[0]._ttl,answer_resourceRecord[0]._addr)
            reply = reply + resourcePart2.pack()

        key_list = nscache.getKeys()[1:]

        list.reverse(nsdn_record) 

        print(nsdn_record)
        print(key_list)


        #Checking for NSDN records, goes in reverse order working from the latest NS record we received
        for x in nsdn_record:

            if x in key_list:

                list_of_ns = nscache.get(x)
                result = ""

                for y in list_of_ns:
                    if acache.contains(str(y[0])):
                        result = y

                #Once it has found the latest that qualifies, it ends so we only get that one result
                if result != "":
                    nsPart = RR_NS(x,result[1],result[0])
                    reply = reply + nsPart.pack()

                    ip_addr_value = acache.getIpAddresses(DomainName(str(result[0])))
                    ttl = acache.getExpiration(DomainName(str(result[0])),ip_addr_value[0])

                    arPart = RR_A(DomainName(str(result[0])),ttl,inet_aton(str(ip_addr_value[0])))

                    reply = reply + arPart.pack()

                    break
                
    #The answer is our original query, therefore A record
    else:

        #Number of valid IP addresess for the name
        ip_num = len(acache.getIpAddresses(DomainName(str(answer_resourceRecord[0]._dn))))

        headerPart = Header(Header.fromData(data)._id,0,0,qdcount=1,ancount=ip_num,qr=1,nscount=1,arcount=1)
        questionPart = QE(1,original_questionEntry._dn)

        reply = headerPart.pack() + questionPart.pack()

        #Adding the A record to the packet
        ip_addr_value = acache.getIpAddresses(DomainName(str(answer_resourceRecord[0]._dn)))

        if len(ip_addr_value) > 1:
            for x in ip_addr_value:
                resourcePart2 = RR_A(answer_resourceRecord[0]._dn,answer_resourceRecord[0]._ttl,inet_aton(str(x)))
                reply = reply + resourcePart2.pack()
        else:
            resourcePart2 = RR_A(answer_resourceRecord[0]._dn,answer_resourceRecord[0]._ttl,answer_resourceRecord[0]._addr)
            reply = reply + resourcePart2.pack()
        

        key_list = nscache.getKeys()[1:]
    
        list.reverse(nsdn_record) 
        
        #Checking for NSDN records, goes in reverse order working from the latest NS record we received
        for x in nsdn_record:

            if x in key_list:
                
                list_of_ns = nscache.get(x)
                result = ""

                for y in list_of_ns:
                    if acache.contains(str(y[0])):
                        result = y
                
                #Once it has found the latest that qualifies, it ends so we only get that one result
                if result != "":
                    nsPart = RR_NS(x,result[1],result[0])
                    reply = reply + nsPart.pack()

                    ip_addr_value = acache.getIpAddresses(DomainName(str(result[0])))
                    ttl = acache.getExpiration(DomainName(str(result[0])),ip_addr_value[0])

                    arPart = RR_A(DomainName(str(result[0])),ttl,inet_aton(str(ip_addr_value[0])))

                    reply = reply + arPart.pack()
                    break
                

    logger.log(DEBUG2, "our reply in full:")
    logger.log(DEBUG2, hexdump(reply))

    ss.sendto(reply, client_address)



