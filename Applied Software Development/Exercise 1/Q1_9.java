import java.util.Scanner;

public class Q1_9 {
	
	public static void main(String[] args) {
		
		Scanner Sf = new Scanner(System.in);
		
		long number = Sf.nextLong();
		
		Boolean value = palindrome(number);
		
		if(value == true) {
			System.out.println("Palindrome");
		}
		else {
			System.out.println("Not a palindrome");
		}
	}
	
	public static Boolean palindrome(long number) {
		
		String str = number + "";
				
		char[] palindrome = str.toCharArray();
				
		for (int x = 0; x < palindrome.length; x++) {
			char fnumber = palindrome[x];
			char lnumber = palindrome[palindrome.length-x-1];
			
			if (fnumber != lnumber) {
				return false;
			}
		}
		
		return true;
	}
	
}
