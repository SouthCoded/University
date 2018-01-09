import java.util.ArrayList;
import java.util.Scanner;

public class Q1_3 {

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		
		Scanner Sf = new Scanner(System.in);
		ArrayList list = new ArrayList();
		
		int x = 0;
		while(x != 10) {
			System.out.println("Enter string " + (x+1));
			String temp = Sf.next();
			list.add(temp);
			x++;
		}
		
		for(int p = 9; p >= 0;p--) {
			System.out.println(list.get(p));

		}
		
		
		
	}
	
}
