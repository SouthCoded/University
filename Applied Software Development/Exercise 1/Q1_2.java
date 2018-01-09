import java.util.Scanner;

public class Q1_2 {

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		int total = 0;
		
		Scanner Sf = new Scanner(System.in);
		double[] list = new double[10];
		
		int x = 0;
		while(x != 10) {
			System.out.println("Enter number " + (x+1));
			double temp = Sf.nextDouble();
			list[x] = temp;
			total += list[x];
			x++;

		}
		
		System.out.println(total/10);
		
		
	}
	
}
