#include <stdio.h>

int main(){

	long a;

	scanf("%ld",&a);

	int num = a;
 	int rev = 0;
	while (num > 0){
		int dig = num % 10;
    	rev = rev * 10 + dig;
    	num = num / 10;
	}

	if (a == rev){
		printf("Palindrome\n");
	}
	else{
		printf("Not a palindrome\n");
	}	


}
