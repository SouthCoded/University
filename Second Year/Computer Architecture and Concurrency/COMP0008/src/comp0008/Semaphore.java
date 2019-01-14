package comp0008;
/*
 * COMP0008 Semaphore - needs to be implemented.
 */

public class Semaphore {

	public int total_permits;
	public int permits_used = 0;

	public Semaphore(int permits) {
		total_permits = permits;
	}
	
	public synchronized void acquire() {
		if(permits_used < total_permits){
			permits_used++;
		}
		else{
			try {
				wait();
			} catch (InterruptedException e) {
				e.printStackTrace();
			}
		}
	}
	
	public synchronized void release() {
		permits_used--;
		notify();
	}

}
