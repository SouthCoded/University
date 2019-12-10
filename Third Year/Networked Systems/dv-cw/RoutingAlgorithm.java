/**
 * The <code>RoutingAlgorithm</code> interface should be implemented by any
 * class whose instances are intended to provide the routing algorithm. The
 * class that implements this algorithm must have a zero argument constructor.
 *
 * @author  Adam Greenhalgh
 * @version 1.0, 16/02/07
 * @since   JDK1.0
 */
public interface RoutingAlgorithm {
    /**
     * Given a destination address, returns the out going interface for that address, -1 is returned for a local address, -2 is an unknown address.
     * @param destination the destination address
     * @return the local interface
     */
    public int getNextHop(int destination);
    /**
     * Passes the router object to the Routing algorithm, so that the algorithm can retreive values from the router.
     * @param obj
     */
    public void setRouterObject(Router obj);
    /**
     * Sets the routing update interval in time slots.
     * @param interval the update interval
     */
    public void setUpdateInterval(int interval);
    /** 
     * Generates a routing packet from the routing table.
     * @param iface interface id
     * @return Packet
     */
    public Packet generateRoutingPacket(int iface);
    /**
     * Given a routing packet from another router, process it (unless the interface is down) and update the routing table. 
     * @param p the packet to process
     * @param iface the interface it came in on
     */
    public void processRoutingPacket(Packet p, int iface);
    /**
     * A periodic task to refresh the routing-table entries on the basis of their expiration time, and on whether the corresponding interfaces are up/down.
     * This method is called before processing any new packets each round. 
     */
    public void tidyTable();
    /**
     * Initialise the routing algorthm. 
     * This must be called once the <code>setRouterObject</code> has been called.
     */
    public void initalise();
    /**
     * Prints the routing table to the screen.
     * The format is :
     * Router <id>
     * d <destination> i <interface> m <metric>
     * d <destination> i <interface> m <metric>
     * d <destination> i <interface> m <metric>
     */
    public void showRoutes();
    
    /**
     *Enables or disables split horizon with poison reverse.
     *@param flag a boolean indicating whether split horizon with poison reverse is on or off.
     */
    public void setAllowPReverse(boolean flag); 
    
    /**
     *Enables or disables routing table entry expiration.
     *@param flag a boolean indicating whether entry expiration is on or off.
     */
    public void setAllowExpire(boolean flag);

}
