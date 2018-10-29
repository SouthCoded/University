// Written by Duncan 12/10/17
//Prints star stuff


#include <stdio.h>


int main(void){

	int y1= 0;
	int reverse = 0;

	printf("*");
	printf("\n");
	for(int x=0;x<7;x++){
		
		printf("*");

		for(int z1=0;z1<y1;z1++){
			printf(" ");
		}

		
		  printf("*");
	    
		

		if(y1<3 && reverse == 0){
		  y1++;
		  
		}
		else{
		  y1--;
		  reverse = 1;
		}
		
		printf("\n");
	}
	printf("*");
	printf("\n");




}