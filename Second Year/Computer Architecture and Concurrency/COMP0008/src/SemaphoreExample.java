/*
 * Java 5 Semaphore Example.
 */

// Comment and uncomment the next lines to switch between
// the demo using the Java Concurrency package and your
// own "comp0008" concurrency package classes.

//import java.util.concurrent.Semaphore;
import comp0008.Semaphore;

public class SemaphoreExample {
	
	/***** A SEMAPHORE ALLOWING 4 PERMITS *****/
	private static Semaphore semaphore = new Semaphore(4);
	
	public static void main(final String[] args) {
		Thread[] threads = new Thread[10];
		
		System.out.println("Creating Threads.");
		
		
		for (int i = 0; i < 10; i++) {
			threads[i] = new SemaphoreExampleThread(i, semaphore);
		}

		System.out.println("Started Threads.");

		for (int i = 0; i < 10; i++) {
			threads[i].start();
		}

		System.out.println("All Threads Started.");
		
	}

}

/*
 * ExampleThread encapsulates an integer id and a Java 5 Semaphore.
 * It initially sleeps for a number of seconds determined by its id value.
 */
class SemaphoreExampleThread extends Thread {
	
	private int id;
	private Semaphore semaphore;
	
	public SemaphoreExampleThread(final int id, final Semaphore semaphore) {
		this.id = id;
		this.semaphore = semaphore;
	}
	
	public void run() {
		
		System.out.println("Thread " + id + " running.");
		
		try {
			// Sleep for number of seconds determined by id value.
			sleep(id * 1000);

			semaphore.acquire();
			System.out.println("Thread " + id + " entered critical section.");
			sleep(5000);
		}
		catch (InterruptedException except){
			System.out.println("Thread " + id + " was interrupted.");
		}
		finally {
			System.out.println("Thread " + id + " exiting critical section.");
			semaphore.release();
		}
	}
}
