public interface RoutingTableEntry
{
    public int getDestination();		// returns destination
						//   field of table entry
    public void setDestination(int d);		// sets destination
						//   field of table entry
    public int getInterface();			// returns interface
						//   field of table entry
    public void setInterface(int i);		// sets interface field of
						//   table entry
    public int getMetric();			// gets metric field of
						//   table entry
    public void setMetric(int m);		// sets metric field of
						//   table entry
    public int getTime();			// gets time field (time
						//   added to table) of
						//   table entry
    public void setTime(int t);			// sets time field (time
						//   added to table) of
						//   table entry
    public String toString();			// returns printable version
						//   of entire table entry
						//   as String
}
