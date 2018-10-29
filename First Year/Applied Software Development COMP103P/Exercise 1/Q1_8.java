import java.util.Scanner;

public class Q1_8 {
	
	public static void main(String[] args) {

	boolean x = true;
	
	while(x) {
		Scanner Sf = new Scanner(System.in);		
		System.out.println("1. Convert millimetres to feet.");
		System.out.println("2. Convert metres to inches.");
		System.out.println("3. Convert kilometres to yards.");
		System.out.println("4. Quit");
		
		System.out.print("Insert Choice : ");
		
		double value = 0;
		
		switch(Sf.nextInt()) {
			case 1: value = milliToFeet();break;
			case 2: value = meterToInch();break;
			case 3: value = kiloToYards();break;
			case 4: x = false; System.out.println("Exited");break;
			default: System.out.println("Not an option");
		}
		
		System.out.println("Value is " + value);
	}
	
	}

	private static double kiloToYards() {
		// TODO Auto-generated method stub
		Scanner Sf = new Scanner(System.in);		
		System.out.println("Enter number");
		double temp = Sf.nextDouble();
		return temp * 1093.61;
	}

	private static double meterToInch() {
		// TODO Auto-generated method stub
		Scanner Sf = new Scanner(System.in);		
		System.out.println("Enter number");
		double temp = Sf.nextDouble();
		return temp * 39.3701;
		
	}

	private static double milliToFeet() {
		// TODO Auto-generated method stub
		Scanner Sf = new Scanner(System.in);		
		System.out.println("Enter number");
		double temp = Sf.nextDouble();
		return temp * 0.00328084;
		
	}

}
