import sys
from libs.dnslib.RR import *
from libs.dnslib.Header import Header
from libs.dnslib.QE import QE
from libs.inetlib.types import *

from binascii import unhexlify
SEND = 0
RECV = 1

class Net_Data:
  
  def __init__ (this, sendrecv, socket_id, raw_packet, inet_addr, inet_port):
    this.sendrecv = sendrecv
    this.socket_id = socket_id
    this.raw_packet = raw_packet
    this.inet_addr = inet_addr
    this.inet_port = inet_port

    this.parse_network_data()

  def parse_network_data (this):
    net_data = this.raw_packet
    offset = 0
    header = Header.fromData(net_data, offset)
    offset += len(header)
    query = QE.fromData(net_data, offset)
    offset += len(query)
    a_rr_list = []
    ns_rr_list = []
    ar_rr_list = []
    for i in range(header._ancount):
      if offset < len(net_data):
        (a_rr, a_rr_len) = RR.fromData(net_data, offset)
        offset += a_rr_len
        a_rr_list.append(a_rr)
    for i in range(header._nscount):
      if offset < len(net_data):
        (ns_rr, ns_rr_len) = RR.fromData(net_data, offset)
        offset += ns_rr_len
        ns_rr_list.append(ns_rr)
    for i in range(header._arcount):
      if offset < len(net_data):
        (ar_rr, ar_rr_len) = RR.fromData(net_data, offset)
        offset += ar_rr_len
        if not ar_rr._type == -1:
          ar_rr_list.append(ar_rr)
    this.header = header
    this.query = query
    this.a_rr_list = a_rr_list
    this.ns_rr_list = ns_rr_list
    this.ar_rr_list = ar_rr_list
    
  def __str__ (this):
    return str(this.sendrecv) + ', ' + str(this.socket_id) + ', ' + \
      str(this.raw_packet) + ', ' + str(this.inet_port) + ', ' + \
      str(this.inet_addr)

def parse_strace (strace_data):
  net_data_list = []
  split_string = strace_data.split("\n")
  i = 0
  for verbiage in split_string:
    i += 1
    print verbiage
    if not (verbiage[0:6] == 'sendto' or verbiage[0:8] == 'recvfrom') or \
    not verbiage.find('unfinished') == -1:
      continue
    sendrecv = -1
    if verbiage[0:6] == 'sendto':
      sendrecv = 0
      offset = 7
    elif verbiage[0:8] == 'recvfrom':
      sendrecv = 1
      offset = 9
    else:
      print "mysterious happenings"
      exit(1)
    
    # fsck yeah magic numbers everywhere
    data_split = (verbiage[offset:]).split(', ')
    socket_id = int(data_split[0])
    escaped_hex = data_split[1][1:len(data_split[1]) - 1]
    unescaped_hex = escaped_hex.replace('\\x', '')
    try:
      raw_data = unhexlify(unescaped_hex)
    except TypeError as e:
      print split_string
      print data_split[1], len(data_split[1])
      print escaped_hex, len(escaped_hex)
      print unescaped_hex, len(unescaped_hex)
      print e
      sys.stdout.flush()
      exit(1)
    inet_port_str = data_split[5]
    inet_port = -1
    inet_addr = -1
    
    if data_split[4] == "NULL":
      inet_port = net_data_list[len(net_data_list) - 1].inet_port
      inet_addr = net_data_list[len(net_data_list) - 1].inet_addr
    else:
      inet_port_str = data_split[5]
      inet_port = int(inet_port_str[inet_port_str.index("(") + \
        1:inet_port_str.index(")")])
      inet_addr_str = data_split[6]
      inet_addr = inet_addr_str[inet_addr_str.index('"') + \
        1:len(inet_addr_str) - 3]
    net_data = Net_Data (sendrecv, socket_id, raw_data, inet_addr, inet_port)
    net_data_list.append(net_data)
  
  return net_data_list
