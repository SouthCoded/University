import java.util.*;

public class DV implements RoutingAlgorithm {
    
    static int LOCAL = -1;
    static int UNKNOWN = -2;
    static int INFINITY = 60;

    DV algorithm;
    ArrayList<DVRoutingTableEntry> self_router = new ArrayList<DVRoutingTableEntry>();
    Map <Integer, Integer> garbageCollection = new HashMap<Integer, Integer>();
    Router router;
    int updateInterval;
    boolean allowReverse;
    boolean allowExpire;
        
    public DV()
    {

    }

    public void setRouterObject(Router obj)
    {
    	router = obj;
    }
    
    public void setUpdateInterval(int u)
    {
    	updateInterval = u;
    }
    
    public void setAllowPReverse(boolean flag){
    	allowReverse = flag;
    }
    
    public void setAllowExpire(boolean flag){
    	allowExpire = flag;
    }
    
    //add own router information
    public void initalise()
    {

    	self_router.add(new DVRoutingTableEntry(router.getId(),LOCAL,0,0));

    }

    public int getNextHop(int destination)
    {

  		for (DVRoutingTableEntry x : self_router){
  			if(destination == x.getDestination()){
  				return x.getInterface();
  			}
  		}

        return -2;
    }
       
    public void tidyTable()
    {

        if(allowExpire){

            Link[] links = router.getLinks();
            boolean route_down = false;

            Set<Integer> set = new HashSet<> ();

            //Search for entries of infinity in our routing table and adds them to the keyset if they aren't already added
            for(DVRoutingTableEntry entry : self_router){
                
                boolean already = false;


                if(entry.getMetric() == 60){
                    for (int key : garbageCollection.keySet()) {
                        //If we already have the node in our map, we decrement the time
                        if(entry.getDestination() == key){
                            garbageCollection.replace(key,garbageCollection.get(key)-1);
                            already = true;
                        }
                    } 
                    //If we don't we add it, with a timeout
                    if(!already){    
                        garbageCollection.put(entry.getDestination(),updateInterval*4);            
                    }
                }
                else{

                    set = new HashSet<> ();
                    
                    for (int key : garbageCollection.keySet()) {
                        //If we have a router in a garbage collection but it isn't equal to 60, then we delete the router from our records
                        if(entry.getDestination() == key){
                            set.add(key);
                        }
                    } 
                    garbageCollection.keySet().removeAll(set);
                }
            }


            //For timeouts in our keyset, deletes the routers and other routers that use that interface
            for (int key : garbageCollection.keySet()) {
                
                //Node is timed out
                if(garbageCollection.get(key) == 0){
                    
                    int marker=0;

                    //Gets interface number of timed out node
                     for(int y = self_router.size()-1; y >= 0; y--){
                        if(self_router.get(y).getDestination() == key){
                            marker = self_router.get(y).getInterface();
                        }
                    }

                    //Removes node
                    for(int y = self_router.size()-1; y >= 0; y--){
                        if(marker == self_router.get(y).getInterface()){
                            self_router.remove(y);
                        }
                    }
                    set.add(key);
                }
            }

            //Deletes the keys from the set
            garbageCollection.keySet().removeAll(set);


            //Adding nodes connected to expired links to our keyset
            for(Link x : links){
                //There is a downed link
                if(!x.isUp()){
                    route_down = true;

                    //We check our routing table for the correct routing table entry to update it to infinity
                    for(int y = 0; y< self_router.size(); y++){
                        if((router.getId() == x.getRouter(0) && self_router.get(y).getInterface() == x.getInterface(0)) || (router.getId() == x.getRouter(1) && self_router.get(y).getInterface() == x.getInterface(1))) {
                            self_router.get(y).setMetric(INFINITY);
                            
                            boolean already = false;
                            
                            //We update the node to infinity and want to add it to our keyset
                            for (int key : garbageCollection.keySet()) {
                                //If we already have the node in our map, we decrement the time
                                if(x.getRouter(0) == router.getId() && key == x.getRouter(1)){
                                    already = true;
                                }
                                else if(x.getRouter(1) == router.getId() && key == x.getRouter(0)){
                                    already = true;
                                }
                            }
                            //Otherwise if the node isn't in our map so we add it
                            if(!already){
                                if(x.getRouter(0) == router.getId() && self_router.get(y).getDestination() == x.getRouter(1)){
                                    garbageCollection.put(x.getRouter(1),updateInterval*4);

                                }
                                else if(x.getRouter(1) == router.getId() && self_router.get(y).getDestination() == x.getRouter(0)){
                                    garbageCollection.put(x.getRouter(0),updateInterval*4);
                                }
                            }
                        }
                    }
                }
            }


        }
        else{
        	Link[] links = router.getLinks();

        	for(Link x : links){
                //Checking if a link is up, if it isn't then we set the metric to infinity
        		if(!x.isUp()){
        			for(int y = 0; y< self_router.size(); y++){
        				if((router.getId() == x.getRouter(0) && self_router.get(y).getInterface() == x.getInterface(0)) || (router.getId() == x.getRouter(1) && self_router.get(y).getInterface() == x.getInterface(1))) {
        					self_router.get(y).setMetric(INFINITY);
        				}
        			}
        		}
        	}
        }

    }
    
    //Called for each router and interface on that router
    public Packet generateRoutingPacket(int iface)
    {

    	Link[] links = router.getLinks();
    	boolean link_dead = false;

        //Checking if a link is dead, if it is we don't send a packet
    	for(Link x : links){
    		if(!x.isUp()){
				if(x.getRouter(0) == router.getId() && x.getInterface(0) == iface || (x.getRouter(1) == router.getId() && x.getInterface(1) == iface)){
					link_dead = true;
				}
	    	}
    	}

    	if(link_dead){
    		return null;
    	}
    	else{

    		//sets the packet to the current router id
			Packet packet = new Packet(router.getId(),Packet.BROADCAST);
			Payload payload = new Payload();
			
            //Adding routing table (all)
			for (int d =0; d< self_router.size(); d++){

				if(allowReverse){
                    boolean link_exists = false;
                    
                    for(Link x : links){
                        //If the link connections to the routing table destination directly then we can send results
                        if(x.getRouter(1) == self_router.get(d).getDestination() && x.isUp()){
                            link_exists = true;
                        }
                    }

                    //If the link doesn't exist between the two nodes and we are using the same interface as the routing table, we use the link to know about the place so don't need to send it
					if(self_router.get(d).getInterface() == iface && link_exists == false){

						int a = self_router.get(d).getDestination();
						int b = self_router.get(d).getInterface();
						int c = self_router.get(d).getTime();

						DVRoutingTableEntry temp = new DVRoutingTableEntry(a,b,INFINITY,c);

						payload.addEntry(temp);
					}
					else{

                        int a = self_router.get(d).getDestination();
                        int b = self_router.get(d).getInterface();
                        int c = self_router.get(d).getMetric();
                        int e = self_router.get(d).getTime();

                        DVRoutingTableEntry temp = new DVRoutingTableEntry(a,b,c,e);

                        payload.addEntry(temp);
					}
				}
				else{

                    //Adding routing table entries to send off
                    int a = self_router.get(d).getDestination();
                    int b = self_router.get(d).getInterface();
                    int c = self_router.get(d).getMetric();
                    int e = self_router.get(d).getTime();

                    DVRoutingTableEntry temp2 = new DVRoutingTableEntry(a,b,c,e);
					payload.addEntry(temp2);
				}

			}



			packet.setPayload(payload);

			return packet;
    	}
			
    }
    
    //Packet came in on this interface
    public void processRoutingPacket(Packet p, int iface)
    {

    	Payload payload = p.getPayload();
    	Vector<Object> data = payload.getData();

    	int metric;

    	//Gets own interface metric
		metric = router.getInterfaceWeight(iface);


    	//For the data in the payload, we go through each entry
    	for(int y =0; y < data.size(); y++){
    		
    		String[] values= data.get(y).toString().split(" ");

    		int d = Integer.parseInt(values[1]);
    		int i = Integer.parseInt(values[3]);
    		int m = Integer.parseInt(values[5]);

            //Checking if the value is inifity
    		if(allowReverse && m == INFINITY){

                for (int x =0; x< self_router.size(); x++){
                    
                    //Checks if we should ignore the value if it comes the downed link
                    if(self_router.get(x).getDestination() == d && (iface == self_router.get(x).getInterface())){
                        Link[] links = router.getLinks();
                        boolean ignore = false;
                        for(Link l : links){
                            if(!l.isUp()){
                                if((l.getRouter(0) == router.getId() && p.getSource() == l.getRouter(1)) || (l.getRouter(1) == router.getId() && p.getSource() == l.getRouter(0))){
                                    ignore = true;
                                }
                            }
                        }
                        
                        if(!ignore){
                            self_router.get(x).setMetric(m);
                        }
                        
                    }
                }
			}
			else{
				m = Integer.parseInt(values[5]) + metric;
	
	    		boolean dup = false;

	    		//Searching for routing entry in our routing table, checking if we already have 
	    		for (int x =0; x< self_router.size(); x++){
					if(self_router.get(x).getDestination() == d){
		    			dup = true;
		    		}
	    		}

	    		//Searching for routing entry in our routing table
	    		for (int x =0; x< self_router.size(); x++){
	    	
                    //Adding new link
	    			if(dup == false){
                        Link[] links = router.getLinks();
                        boolean ignore = false;
                        //Makes sure packet isn't coming fomr a downed link
                        for(Link l : links){
                            if(!l.isUp()){
                                if((l.getRouter(0) == router.getId() && p.getSource() == l.getRouter(1)) || (l.getRouter(1) == router.getId() && p.getSource() == l.getRouter(0))){
                                    ignore = true;
                                }
                            }
                        }
                        if(!ignore && m <=60){
    						self_router.add(new DVRoutingTableEntry(d,iface,m,router.getCurrentTime()));
    						dup = true;
                        }
		    		}//Deals with node failures
		    		else if(self_router.get(x).getDestination() == d && (iface == self_router.get(x).getInterface())){
                        Link[] links = router.getLinks();
                        boolean ignore = false;
                        //Makes sure packet isn't coming fomr a downed link
                        for(Link l : links){
                            if(!l.isUp()){
                                if((l.getRouter(0) == router.getId() && p.getSource() == l.getRouter(1)) || (l.getRouter(1) == router.getId() && p.getSource() == l.getRouter(0))){
                                    ignore = true;
                                }
                            }
                        }
                        if(!ignore && m <=60){
		    			    self_router.get(x).setMetric(m);
                        }
		    		} //Seeing if the value gotten is better than what we currently have
		     		else if(self_router.get(x).getDestination() == d && (m < self_router.get(x).getMetric())){

                        Link[] links = router.getLinks();
                        boolean ignore = false;
                        //Makes sure packet isn't coming fomr a downed link
                        for(Link l : links){
                            if(!l.isUp()){
                                if((l.getRouter(0) == router.getId() && p.getSource() == l.getRouter(1)) || (l.getRouter(1) == router.getId() && p.getSource() == l.getRouter(0))){
                                    ignore = true;
                                }
                            }
                        }

                        if(!ignore && m <=60){
						    self_router.get(x).setMetric(m);
						    self_router.get(x).setInterface(iface);
                        }
		     		}	

    		  }
    	}

    	}    	
    }

	
    
    //Prints in the formate
    public void showRoutes()
    {
    	System.out.println("Router " + router.getId());
    	
    	int router_id = 0;
    	
    	self_router.sort(Comparator.comparing(DVRoutingTableEntry::getDestination));
			
		for (DVRoutingTableEntry x : self_router){
    		
    		System.out.println(x.toString());
    			
    	}

    }

}

class DVRoutingTableEntry implements RoutingTableEntry{
    
	int destination;
	int interface_num;
	int metric;
	int time;

    public DVRoutingTableEntry(int d, int i, int m, int t)
	{
		destination = d;
		interface_num = i;
		metric = m;
		time = t;
	}

    public int getDestination() { return destination; } 
    public void setDestination(int d) { 
    	destination = d;
    }
    public int getInterface() { return interface_num; }
    public void setInterface(int i) {
    	interface_num = i;
    }
    public int getMetric() { return metric;}
    public void setMetric(int m) {
    	metric = m;
    } 
    public int getTime() {return time;}
    public void setTime(int t) { 
    	time = t;
    }
    public String toString() 
	{
	    return "d " + destination + " i " + interface_num +" m " + metric;
	}
}

