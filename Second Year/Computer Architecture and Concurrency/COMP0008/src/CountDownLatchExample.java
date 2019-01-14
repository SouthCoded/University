/*
 * Java 5 CountDownLatch Example.
 */

// Comment and uncomment the next lines to switch between
// the demo using the Java Concurrency package and your
// own "comp0008" concurrency package classes.

//import java.util.concurrent.CountDownLatch;
import comp0008.CountDownLatch;


public class CountDownLatchExample {
	
	/***** A COUNT-DOWN LATCH HOLDING BACK 4 THREADS BEFORE RELEASING *****/
	private static CountDownLatch latch = new CountDownLatch(4);
	
	public static void main(final String[] args) {
		Thread[] threads = new Thread[10];
		
		System.out.println("Creating Threads.");
		
		
		for (int i = 0; i < 10; i++) {
			threads[i] = new CountDownLatchExampleThread(i, latch);
		}

		System.out.println("Started Threads.");

		for (int i = 0; i < 10; i++) {
			threads[i].start();
		}

		System.out.println("All Threads Started.");
		
	}

}

/*
 * ExampleThread encapsulates an integer id and a Java 5 Count Down Latch.
 * It initially sleeps for a number of seconds determined by its id value.
 */
class CountDownLatchExampleThread extends Thread {
	
	private int id;
	private CountDownLatch latch;
	
	public CountDownLatchExampleThread(final int id, final CountDownLatch latch) {
		this.id = id;
		this.latch = latch;
	}
	
	public void run() {
		
		System.out.println("Thread " + id + " running.");
		
		try {
			// Sleep for number of seconds determined by id value.
			sleep(id * 1000);

			System.out.println("Thread " + id + " hitting latch.");
			latch.countDown();
			latch.await();
			System.out.println("Thread " + id + " released from latch.");
			sleep(5000);
		}
		catch (InterruptedException except){
			System.out.println("Thread " + id + " was interrupted.");
		}
	}
}