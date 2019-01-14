package comp0008;
/*
 * COMP0008 CountDownLatch - needs to be implemented.
 */

import static java.lang.Thread.sleep;

public class CountDownLatch {

	public int timer;

	public CountDownLatch(int count) {
		timer = count;
	}
	
	public synchronized void countDown() {
		timer--;
		if(timer == 0) {
			notify();
		}
	}
	
	public synchronized void await() {

		if (timer > 0) {
		try {
			wait();
		} catch (InterruptedException e) {
			System.out.println("error");
		}
		}
		else{
			notify();
		}

	}

}
