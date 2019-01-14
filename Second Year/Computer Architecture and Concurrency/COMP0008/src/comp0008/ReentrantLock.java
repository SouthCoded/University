package comp0008;
/*
 * COMP0008 ReentrantLock - needs to be implemented.
 */

public class ReentrantLock {

	Boolean locked = false;
	public ReentrantLock(){

	}
	
	public synchronized void lock() {

		if(locked) {
			try {
				wait();
			} catch (InterruptedException e) {
				e.printStackTrace();
			}
		}

	}
	
	public synchronized void unlock() {
		locked = false;
		notify();
	}

}
