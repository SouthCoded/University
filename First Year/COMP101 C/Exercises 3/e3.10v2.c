//Written by Duncan 20/10/17
//Prints numbers in star form 


#include <stdio.h>
#include <string.h>

int main(void){

	int first,second,third;
	char grid[5][21] = {
	{' ',' ',' ',' ',' ',' ', ' ',' ',' ',' ',' ',' ',' ', ' ',' ',' ',' ',' ',' ',' ', ' '},
	{' ',' ',' ',' ',' ',' ', ' ',' ',' ',' ',' ',' ',' ', ' ',' ',' ',' ',' ',' ',' ', ' '},
	{' ',' ',' ',' ',' ',' ', ' ',' ',' ',' ',' ',' ',' ', ' ',' ',' ',' ',' ',' ',' ', ' '},
	{' ',' ',' ',' ',' ',' ', ' ',' ',' ',' ',' ',' ',' ', ' ',' ',' ',' ',' ',' ',' ', ' '},
	{' ',' ',' ',' ',' ',' ', ' ',' ',' ',' ',' ',' ',' ', ' ',' ',' ',' ',' ',' ',' ', ' '},
	};

	static char one[5][6] = {
	{' ',' ',' ','*',' ',' '},
	{' ',' ','*','*',' ',' '},
	{' ',' ',' ','*',' ',' '},
	{' ',' ',' ','*',' ',' '},
	{' ',' ','*','*','*',' '},
	};
	static char two[5][6] = {
	{'*','*','*','*','*','*'},
	{' ',' ',' ',' ',' ','*'},
	{'*','*','*','*','*','*'},
	{'*',' ',' ',' ',' ',' '},
	{'*','*','*','*','*','*'},
	};
	static char three[5][6] = {
	{'*','*','*','*','*','*'},
	{' ',' ',' ',' ',' ','*'},
	{'*','*','*','*','*','*'},
	{' ',' ',' ',' ',' ','*'},
	{'*','*','*','*','*','*'},
	};
	static char four[5][6] = {
	{' ',' ','*','*',' ',' '},
	{' ','*',' ','*',' ',' '},
	{'*',' ',' ','*',' ',' '},
	{'*','*','*','*','*','*'},
	{' ',' ',' ','*',' ',' '},
	};
	static char five[5][6] = {
	{'*','*','*','*','*','*'},
	{'*',' ',' ',' ',' ',' '},
	{'*','*','*','*','*','*'},
	{' ',' ',' ',' ',' ','*'},
	{'*','*','*','*','*','*'},
	};
	static char six[5][6] = {
	{'*','*','*','*','*','*'},
	{'*',' ',' ',' ',' ',' '},
	{'*','*','*','*','*','*'},
	{'*',' ',' ',' ',' ','*'},
	{'*','*','*','*','*','*'},
	};
	static char seven[5][6] = {
	{'*','*','*','*','*','*'},
	{' ',' ',' ',' ','*',' '},
	{' ',' ',' ','*',' ',' '},
	{' ',' ','*',' ',' ',' '},
	{' ','*',' ',' ',' ',' '},
	};
	static char eight[5][6] = {
	{'*','*','*','*','*','*'},
	{'*',' ',' ',' ',' ','*'},
	{'*','*','*','*','*','*'},
	{'*',' ',' ',' ',' ','*'},
	{'*','*','*','*','*','*'},
	};
	static char nine[5][6] = {
	{'*','*','*','*','*','*'},
	{'*',' ',' ',' ',' ','*'},
	{'*','*','*','*','*','*'},
	{' ',' ',' ',' ',' ','*'},
	{' ',' ',' ',' ',' ','*'},
	};
	static char zero[5][6] = {
	{'*','*','*','*','*','*'},
	{'*',' ',' ',' ',' ','*'},
	{'*',' ',' ',' ',' ','*'},
	{'*',' ',' ',' ',' ','*'},
	{'*','*','*','*','*','*'},
	};

	scanf("%i,%i,%i", &first,&second,&third); 


	char holder[5][6];
	
	switch(first){
		case 0: memcpy(&holder,&zero, sizeof holder); break;
		case 1: memcpy(&holder,&one, sizeof holder); break;
		case 2: memcpy(&holder,&two, sizeof holder); break;
		case 3: memcpy(&holder,&three, sizeof holder); break;
		case 4: memcpy(&holder,&four, sizeof holder); break;
		case 5: memcpy(&holder,&five, sizeof holder); break;
		case 6: memcpy(&holder,&six, sizeof holder); break;
		case 7: memcpy(&holder,&seven, sizeof holder); break;
		case 8: memcpy(&holder,&eight, sizeof holder); break;
		case 9: memcpy(&holder,&nine, sizeof holder); break;
	}

	//first digit
	for(int d =0 ;d<5;d++){
		for(int e = 0; e<6;e++){
			grid[d][e] = holder[d][e];
		}
	}

	switch(second){
		case 0: memcpy(&holder, &zero, sizeof holder); break;
		case 1: memcpy(&holder,&one, sizeof holder); break;
		case 2: memcpy(&holder,&two, sizeof holder); break;
		case 3: memcpy(&holder,&three, sizeof holder); break;
		case 4: memcpy(&holder,&four, sizeof holder); break;
		case 5: memcpy(&holder,&five, sizeof holder); break;
		case 6: memcpy(&holder,&six, sizeof holder); break;
		case 7: memcpy(&holder,&seven, sizeof holder); break;
		case 8: memcpy(&holder,&eight, sizeof holder); break;
		case 9: memcpy(&holder,&nine, sizeof holder); break;
	}

	//second digit
	for(int d =0 ;d<5;d++){
		for(int e = 0; e<6;e++){
			grid[d][e+7] = holder[d][e];
		}
	}

	switch(third){
		case 0: memcpy(&holder,&zero, sizeof holder); break;
		case 1: memcpy(&holder,&one, sizeof holder); break;
		case 2: memcpy(&holder,&two, sizeof holder); break;
		case 3: memcpy(&holder,&three, sizeof holder); break;
		case 4: memcpy(&holder,&four, sizeof holder); break;
		case 5: memcpy(&holder,&five, sizeof holder); break;
		case 6: memcpy(&holder,&six, sizeof holder); break;
		case 7: memcpy(&holder,&seven, sizeof holder); break;
		case 8: memcpy(&holder,&eight, sizeof holder); break;
		case 9: memcpy(&holder,&nine, sizeof holder); break;
	}
	//third digit
	for(int d =0 ;d<5;d++){
		for(int e = 0; e<6;e++){
			grid[d][e+14] = holder[d][e];
		}
	}

	//print all
	for(int d =0 ;d<5;d++){
		for(int e = 0; e<21;e++){
			printf("%c",grid[d][e]);
		}
		printf("\n");
	}
}