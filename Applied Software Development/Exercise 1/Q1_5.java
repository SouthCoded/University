import java.util.Scanner;

public class Q1_5 {
	
	
//	a method that inputs and returns a double value
	
//	a method that takes two double parameters, adds them together and returns the square root of 
//	the result, 

//	a main method to create an object and call the other two methods, displaying the result of calling 
//	the second method

	public static void main(String[] args) {
		
		Q1_5 obj = new Q1_5();
		double a = obj.handler();
		double b = obj.handler();
		System.out.println(obj.squareroot(a, b));

	}
	
	public double handler() {
		System.out.println("Enter number");
		Scanner Sf = new Scanner(System.in);
		return Sf.nextDouble();
		
	}
	
	
	public double squareroot (double a, double b) {
		
		double number = a+b;
		double sqrtroot = Math.sqrt(number);
		
		return sqrtroot;
	}
	
}
