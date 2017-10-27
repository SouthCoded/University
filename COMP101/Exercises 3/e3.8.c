//Written by Duncan 27/10/17
//Prints strong number


#include 	<stdio.h>

int main(void){

	for(int x=1;x<1000000;x++){

		int digit = x;
		//printf("This is the digit %i \n",x);
		int total = 0;

		while(digit > 0){
			
			int factorial;

			int first_digit = digit % 10;
			
			if(first_digit == 0){
				factorial = 0;
			}
			else{
				factorial = 1;
			}

			//printf("This is the first_digit %i ", first_digit);
			while(first_digit > 1){
				factorial = factorial * first_digit;
				first_digit = first_digit-1;
			}
			//printf("These are the factorials %i \n", factorial);
			total += factorial;

			digit = digit/10;
		}
		//printf("%i\n",total);

		if(total == x){
			printf("%i is a strong number!\n", x);
		}

	}

}