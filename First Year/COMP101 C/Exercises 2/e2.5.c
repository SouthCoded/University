// Written by Duncan 12/10/17
//Prints star stuff


#include <stdio.h>


int main(void){

	int y1= 0;
	int y2= 6;

	for(int x=0;x<6;x++){
		
		for(int z1=0;z1<y1;z1++){
			printf(" ");
		}

		for(int z2=y2;z2>0;z2--){
			printf("*");
		}

		y1++;
		y2--;

		printf("\n");
	}


}