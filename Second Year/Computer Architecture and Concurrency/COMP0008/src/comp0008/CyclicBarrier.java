package comp0008;
/*
 * COMP0008 CyclicBarrier - needs to be implemented.
 */

import java.util.concurrent.BrokenBarrierException;

import static java.lang.Thread.sleep;

public class CyclicBarrier {

	public int end;
	public int counter;
	public CyclicBarrier(int count) {

		end = count;
	}
	
	public synchronized void await() throws BrokenBarrierException {

		if(counter != end){
			try {
				counter++;
				wait();
			} catch (InterruptedException e) {
				e.printStackTrace();
			}

		}
		else{
			notifyAll();
			counter = 0;
		}

	}

}
