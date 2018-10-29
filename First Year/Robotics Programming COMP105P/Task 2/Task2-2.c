#include <stdio.h>


int printArray(int *array, int length)
{
   for(int a = 0; a < length; a++){
		printf("%d ", array[a]);
	}
	printf("\n");

	return 0;
}



int main (){

	printf("Enter the number of integers\n");

	int number = 0;

	scanf("%d", &number);

	printf("Enter your integers\n");

	int numList[number];

	for(int i = 0; i < number;i++){

		int temp;
		scanf("%d", &temp);
		numList[i] = temp;

	}


	int turn = 1;

	printf("The Steps\n");
	printArray(numList,number);

	while(turn > 0){

		turn -= 1;

		if (turn >= 0){
			
			int swap = 0;

			for(int p = 0; p < number-1; p++){

				if(numList[p] > numList[p+1]){

					int temp = numList[p];
					numList[p] = numList[p+1];
					numList[p+1] = temp;

					printArray(numList,number);

					swap = 1;
				} 


			}

			if(swap == 1){
				turn += 1;
			}
		}
	}

	printf("Here is the final list: ");

	printArray(numList,number);

	printf("\n");


	return 0;
}