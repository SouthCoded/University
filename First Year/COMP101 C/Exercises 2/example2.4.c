
#include <stdio.h>

int main(){

	int x = 0;
    int y = 0;

	while(x < 4){
		while(y < 4){
			printf("*");
			y++;
		}
		printf("\n");
		y = 0;
		x ++;
	}
}  