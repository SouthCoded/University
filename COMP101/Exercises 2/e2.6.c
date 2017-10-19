// Written by Duncan 12/10/17
//Prints star stuff


#include <stdio.h>


int main(void){

	int y1= 0;
	int reverse = 0;

	for(int x=0;x<11;x++){
		
		for(int z1=0;z1<y1;z1++){
			printf(" ");
		}

		for(int z=0;z<6;z++){
			printf("*");
		}

		if(y1<5 && reverse == 0){
		  y1++;
		  
		}
		else{
		  y1--;
		  reverse = 1;
		}
		

		printf("\n");
	}


}