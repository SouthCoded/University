// Written by Duncan 12/10/17
//Prints star stuff


#include <stdio.h>


int main(void){

	for(int x=0;x<4;x++){
		if(x == 0 || x == 3){
			for(int y=0;y<5;y++){
			printf("*");
			}
		}
		else{
			printf("*");
			for(int y=0;y<3;y++){
				printf(" ");
			}
			printf("*");
		}
		

		printf("\n\n");
	}


}