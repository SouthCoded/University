import java.text.DecimalFormat;
import java.util.Random;

public class Q1_4 {

	public static void main(String[] args) {
		double average = generateRandom();
		generateAverage(average);
		
	}
	
	public static void generateAverage(double average) {
		// TODO Auto-generated method stub
		DecimalFormat numberFormat = new DecimalFormat("#.0000000");

		System.out.println(numberFormat.format(average/10000) + " is the average number");
	}

	public static double generateRandom() {
		
		double x;
		boolean p;
		int counter = 0;
		double big = -1;
		double small = 1;
		double total = 0;
		
		while(counter != 10000) {
						
			Random temp = new Random();
			x = temp.nextDouble();
			p = temp.nextBoolean();
			
			if(p == false) {
				x = x*-1;
			}
			
			if(x < small) {
				small = x;
			}
			if(x > big) {
				big = x;
			}
			
			total += x;
			counter ++;
			
		}
		
		DecimalFormat numberFormat = new DecimalFormat("#.0000000");

		System.out.println(numberFormat.format(small) + " is the smallest number");
		System.out.println(numberFormat.format(big) + " is the largest number");
		
		
		return total;
		
	}
	
	
	
	
}
