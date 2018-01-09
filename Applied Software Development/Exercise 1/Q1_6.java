import java.util.Scanner;

public class Q1_6 {
	
	static double a;
	static double b;
	
	public static void main(String[] args) {
		
		Q1_6 obj = new Q1_6();
		a = obj.handler();
		b = obj.handler();
		System.out.println(obj.squareroot());

	}
	
	private double handler() {
		System.out.println("Enter number");
		Scanner Sf = new Scanner(System.in);
		return Sf.nextDouble();
		
	}
	
	
	private double squareroot () {
		
		double number = getA()+getB();
		double sqrtroot = Math.sqrt(number);
		
		return sqrtroot;
	}
	
	
	public double getA() {
		return a;
	}
	public double getB() {
		return b;
	}
	
	
	
}
