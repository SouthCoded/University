#include "comp0019.h"
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


struct compressor 
{ 
   char* base_pattern;
   int value; 
};

struct node { 
    struct compressor* data; 
    struct node* next; 
}; 

void printBinary(int num)
{
  printf("0b%d",(num & 0x80) >> 7);
  printf("%d",(num & 0x40) >> 6);
  printf("%d",(num & 0x20) >> 5);
  printf("%d",(num & 0x10) >> 4);
  printf("%d",(num & 0x08) >> 3);
  printf("%d",(num & 0x04) >> 2);
  printf("%d",(num & 0x02) >> 1);
  printf("%d\n",(num & 0x01));
}

int checkers(char* w, char* K, struct node * head){

	char a[50];
	char b[50];

	strcpy(a,w);
	strcpy(b,K);
	
	strcat(a,b);

	int found = 0;

	//Makes sure ptr exists in linkedlist
    struct node* checker = head;   

	while (checker != NULL) { 
	    if(strcmp(checker->data->base_pattern,a) == 0){
	        found = 1;
	    }
	    checker = checker->next;
	}

	return found;
}

void writers(char* a, FILE* out_file){

	//Grabs first 8 bits
	if(strlen(a) < 8){
		while(strlen(a) < 8){
			strcat(a,"0");
		}
	}

	float number_of_bytes = (strlen(a)/8.0);

	int byte_counter = 0;
	while(number_of_bytes > 0){
		
		int output_number = 0;

		if(a[byte_counter] == '1'){
			output_number += 128;
		}
		if(a[byte_counter+1] == '1'){
			output_number += 64;
		}
		if(a[byte_counter+2] == '1'){
			output_number += 32;
		}
		if(a[byte_counter+3] == '1'){
			output_number += 16;
		}
		if(a[byte_counter+4] == '1'){
			output_number += 8;
		}
		if(a[byte_counter+5] == '1'){
			output_number += 4;
		}
		if(a[byte_counter+6] == '1'){
			output_number += 2;
		}
		if(a[byte_counter+7] == '1'){
			output_number += 1;
		}

		byte_counter += 8;
		number_of_bytes -= 1;
		fwrite(&output_number,sizeof(char),1,out_file);	
	}
}

void Decode(FILE* in_file, FILE* out_file) {

	struct node* head = NULL; 
	struct node* tail = NULL;
	int number_bit = 3;
	int error_check = 1;
	int value_counter = 4;
	int multi_2 = 8;
	int error = 0;

	//Reads the number of bases
	uint32_t number_of_bases;
	fread(&number_of_bases, sizeof(uint32_t), 1, in_file);
	fwrite(&number_of_bases, sizeof(uint32_t), 1, out_file);

	printf("Number of bases %d\n",number_of_bases);

	//Intializing LinkedList
    head = (struct node*)malloc(sizeof(struct node)); 
    struct compressor compress_0 = {"00",0};
    head->data = &compress_0;
    
    struct node *temp_1 = (struct node*)malloc(sizeof(struct node));
    struct compressor compress_1 = {"01",1};
    temp_1->data = &compress_1;

    struct node *temp_2 = (struct node*)malloc(sizeof(struct node));
    struct compressor compress_2 = {"10",2};
    temp_2->data = &compress_2;

    struct node *temp_3 = (struct node*)malloc(sizeof(struct node));
    struct compressor compress_3 = {"11",3};
    temp_3->data = &compress_3;

  	head->next = temp_1;
  	temp_1->next = temp_2;
  	temp_2->next = temp_3;
  	temp_3->next = NULL;

    tail = temp_3;

	char full_buffer[50000] = "a";

	int counter = 0;
	int byte_numbers_read = 0;
	while(error_check != 0){

		unsigned char input;
		
		//Reads in a byte
		error_check = fread(&input, sizeof(char), 1, in_file);

		if(error_check == 1){
			if((input & 0x80) >> 7 == 0){
				full_buffer[counter] = '0';
			}
			else{
				full_buffer[counter] = '1';
			}
			
			if((input & 0x40) >> 6 == 0){
				full_buffer[counter+1] = '0';
			}
			else{
				full_buffer[counter+1] = '1';
			}

			if((input & 0x20) >> 5 == 0){
				full_buffer[counter+2] = '0';
			}
			else{
				full_buffer[counter+2] = '1';
			}

			if((input & 0x10) >> 4 == 0){
				full_buffer[counter+3] = '0';
			}
			else{
				full_buffer[counter+3] = '1';
			}

			if((input & 0x08) >> 3 == 0){
				full_buffer[counter+4] = '0';
			}
			else{
				full_buffer[counter+4] = '1';
			}
			if((input & 0x04) >> 2 == 0){
				full_buffer[counter+5] = '0';
			}
			else{
				full_buffer[counter+5] = '1';
			}
			if((input & 0x02) >> 1 == 0){
				full_buffer[counter+6] = '0';
			}
			else{
				full_buffer[counter+6] = '1';
			}
			if((input & 0x01) == 0){
				full_buffer[counter+7] = '0';
			}
			else{
				full_buffer[counter+7] = '1';
			}

			counter += 8;
			byte_numbers_read +=1;
		}
	}


	printf("byte_numbers_read = %d while number of bases is %d\n",byte_numbers_read,number_of_bases);


	float f = byte_numbers_read * 5; //Minimum number of bases that can be represented
	
	if(error_check == 0){
		if(full_buffer[0] == 'a' || number_of_bases >= f ){
			error = 1;
			number_of_bases = 0;
		}
	}

	counter = 0;
	int first_run = 1;

	//Contains all the bases
	char output_buffer[50000] = "";
	int out_counter = 0;
	char STRING[20] = "";

	while(number_of_bases > 0){

		int temp = 0;
		
		char w[1000] = "";

		//Grabs the correct digits
		while(temp != number_bit){
			w[temp] = full_buffer[counter];
			counter += 1;
			temp += 1;
		}

		printf("This is w %s\n",w);

		//Gets value of msb
		int two_bit = 1;
		while(temp-1 > 0){
			two_bit *= 2;
			temp -=1;
		}

		int value = 0;
		temp = 0;

		//Gets total value
		while(temp != number_bit){

			if(w[temp] == '1'){
				value += two_bit;
			}

			two_bit /= 2;
			temp += 1;
		}

		printf("Value of w %d\n", value);

	
		if(first_run == 0){
			int found = 0;
			char ENTRY[20];

			//Check if code in translation table
			struct node *checker = head;   
			while (checker != NULL) { 		
				printf("This is checker data %s and value %d\n",checker->data->base_pattern,checker->data->value);
				if(checker->data->value == value){
					found = 1;
				}	 	
				checker = checker->next;
			}

			//If code is in the translation table 
			if(found){
				struct node *checker = head;   
				while (checker->data->value != value) { 			 	
					 checker = checker->next;
				}
				strcpy(ENTRY,checker->data->base_pattern);
				printf("This is entry in found %s\n",ENTRY);

			}
			else{

				if(value_counter != value){
					error = 1;
					number_of_bases = 0;
				}
				else{
					//Edge Case
					strcpy(ENTRY,STRING);

					printf("This is entry in edge %s\n",ENTRY);

					char p[3];
					p[0] = STRING[0];
					p[1] = STRING[1];
					p[2] = '\0';

					printf("This is p %s\n",p);

					strcat(ENTRY,p);
					printf("This is entry in edge %s\n",ENTRY);

				}
				
			}


			int string_length = strlen(ENTRY);

			printf("This is ENTRY %s\n",ENTRY);

			int move_counter = 0;

			while(string_length != move_counter){
				output_buffer[out_counter] = ENTRY[move_counter];
				move_counter +=1;
				out_counter +=1;
			}

			number_of_bases -= string_length/2;
			printf("This is output_buffer %s\n",output_buffer);
			printf("This is STRING %s and value %d\n",STRING,value);

			//Adds String + Entry[0] to translation table
			struct node *temp_node = (struct node*)malloc(sizeof(struct node));
			char* temp_string = malloc(1000*sizeof(char));
			strcpy(temp_string,STRING);

			char p[3];
			p[0] = ENTRY[0];
			p[1] = ENTRY[1];
			p[2] = '\0';

			strcat(temp_string,p);

			printf("Adding new value to table %s\n",temp_string);
			struct compressor *compress_temp = (struct compressor*)malloc(sizeof(struct compressor));
			compress_temp->base_pattern = temp_string;
			compress_temp->value = value_counter;

			temp_node->data = compress_temp;
			temp_node->next = NULL;

			tail->next = temp_node;
			tail = temp_node;

			if(value_counter == multi_2-1){
				number_bit +=1;
				multi_2 *= 2;
			}

			value_counter +=1;

			strcpy(STRING,ENTRY);
		}
		if(first_run == 1){
			int found = 0;
			//Makes sure ptr exists in linkedlist
		    struct node *checker = head;   
			while (checker != NULL) { 		
				if(checker->data->value == value){
					strcpy(STRING,checker->data->base_pattern);
					found = 1;
				}	 	
				checker = checker->next;
			}

			if(found){
				int string_length = strlen(STRING);

				int move_counter = 0;

				while(string_length != move_counter){
					output_buffer[out_counter] = STRING[move_counter];
					move_counter +=1;
					out_counter +=1;
				}
				number_of_bases -= string_length/2;

				printf("This is output_buffer in first %s\n",output_buffer);
			}
			else{
				error = 1;
				number_of_bases = 0;
			}

			first_run = 0;
		}
	}

	if(error == 1){
		printf("Invalid decoder input: .*\n");
	}	
	else{
		writers(output_buffer,out_file);
	}
}
