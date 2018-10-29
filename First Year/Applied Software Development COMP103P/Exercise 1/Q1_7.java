
public class Q1_7 {
	
	public static void main(String[] args) {
		
		String x = toBase(3,2);
		
		System.out.println(x);
	}
	
	public static String toBase(int n, int b) {
		
		return Integer.toString(n, b);
		
	}
}
