#include <stdio.h>

int main (){

	printf("Enter the number of integers\n");

	int number = 0;

	scanf("%d", &number);

	printf("Enter your integers\n");

	int numList[number];

	for(int i = 0; i <number;i++){

		int temp;
		scanf("%d", &temp);
		numList[i] = temp;

	}

	int swap = 1;

	while(swap > 0){

		swap -= 1;

		if (swap >= 0){
			for(int p = 0; p < number-1; p++){

				if(numList[p] > numList[p+1]){

					int temp = numList[p];
					numList[p] = numList[p+1];
					numList[p+1] = temp;

					swap += 1;
				} 
			}
			
		}
	}

	printf("Here is the list:");

	for(int a = 0; a < number; a++){
		printf("%d ", numList[a]);
	}

	printf("\n");


	return 0;
}