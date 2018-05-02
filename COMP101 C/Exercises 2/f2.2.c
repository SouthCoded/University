#include<stdio.h>

int main(){
	
	int x = 0;

	while(x<4){
		if (x == 0 || x == 3){
			int y = 0;
			for(y=0;y<5;y++){
				printf("*");
			}
			printf("\n");
		}
		else{
			printf("*");
			int y = 0;
			for(y=0;y<3;y++){
				printf(" ");
			}
			printf("*\n");
		}
		x++;
	}


}