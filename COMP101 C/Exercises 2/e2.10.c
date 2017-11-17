// Written by Duncan 12/10/17
//Prints star stuff


#include <stdio.h>

int spaces(int number){
	for(int z1=0;z1<number;z1++){
			printf(" ");
		}
}

int main(void){

	int hashes = -1;
	int stars = 4;

	for(int first=0;first<7;first++){
		printf("*");
	}

	printf("\n");

	for(int x=0;x<6;x++){
		
		if(x != 0){
			printf("#");
		}

		spaces(hashes);
		
		printf("#");
		printf("*");

		spaces(stars);

		if(x != 5){
			printf("*");
		}


		stars--;
		hashes++;		
		printf("\n");
	}

	for(int last=0;last<7;last++){
		printf("#");
	}
	printf("\n");

	
}

