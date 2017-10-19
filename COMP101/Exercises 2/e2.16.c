// Written by Duncan 12/10/17
//Prints star stuff


#include <stdio.h>

int rectangle(int width, int height, char * container){
	
	for(int x=0;x<height;x++){

		for(int y=0;y<width;y++){
			printf("%s",container);
		}
		printf("\n");
	}

	printf("\n");


}


int main(void){

	rectangle(10,10,"ABC");
	rectangle(5,10,"$");

}
