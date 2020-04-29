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


void print_binary(int num)
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

long int_to_binary(int num) {
    long binary = 0;
    if(num - 5076 >= 0){
    	binary += 1000000000000;
    	num -= 5076;
    }
    if(num - 2048 >= 0){
    	binary += 100000000000;
    	num -= 2048;
    }
    if(num - 1024 >= 0){
    	binary += 10000000000;
    	num -= 1024;
    }
    if(num - 512 >= 0){
    	binary += 1000000000;
    	num -= 512;
    }
    if(num - 256 >= 0){
    	binary += 100000000;
    	num -= 256;
    }
    if(num - 128 >= 0){
    	binary += 10000000;
    	num -= 128;
    }
    if(num - 64 >= 0){
    	binary += 1000000;
    	num -= 64;
    }
    if(num - 32 >= 0){
    	binary += 100000;
    	num -= 32;
    }
    if(num - 16 >= 0){
    	binary += 10000;
    	num -= 16;
    }
    if(num - 8 >= 0){
    	binary += 1000;
    	num -= 8;
    }
    if(num - 4 >= 0){
    	binary += 100;
    	num -= 4;
    }
    if(num - 2 >= 0){
    	binary += 10;
    	num -= 2;
    }
    if(num - 1 >= 0){
    	binary += 1;
    	num -= 1;
    }

    return binary;
}


int checker(char* w, char* K, struct node * head){

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

void writer(char* a, FILE* out_file,struct node* head, int numberbit){
	
	int number_bit = numberbit;

	char encoded_buffer[50000] = "";

	int i = 0;

	//Adds all values into encoded buffer
	while(a[i] != '='){

		//Copies all of the value into b
		char b[1000] = "";
		int index = 0;

		if(a[i] == '-'){
			number_bit += 1;
			i++;
		}

		while(a[i] != '+'){
			b[index] = a[i];
			index += 1;
			i++;
		}
		
		//Makes sure ptr exists in linkedlist
	    struct node *checker = head;   
		while (strcmp(checker->data->base_pattern,b) != 0) { 
			//printf("This is checker %s\n",checker->data->base_pattern);
		 	checker = checker->next;
		}

		long value = int_to_binary(checker->data->value);

		//printf("This is the value %d\n",value);

		int bit_length = 1;
		long ten_increment = 10;

		//Gets how many bits the value is 
		while(value/ten_increment != 0){
			ten_increment *= 10;
			bit_length += 1;
		}

		while(bit_length < number_bit){
			strcat(encoded_buffer,"0");
			bit_length += 1;
		}

		char str[20];
		sprintf(str, "%ld", value);

		strcat(encoded_buffer,str);
		i++;
	}
	
	//Grabs first 8 bits
	if(strlen(encoded_buffer) < 8){
		while(strlen(encoded_buffer) < 8){
			strcat(encoded_buffer,"0");
		}
	}

	float number_of_bytes = (strlen(encoded_buffer)/8.0);

	int byte_counter = 0;
	while(number_of_bytes > 0){
		
		int output_number = 0;

		if(encoded_buffer[byte_counter] == '1'){
			output_number += 128;
		}
		if(encoded_buffer[byte_counter+1] == '1'){
			output_number += 64;
		}
		if(encoded_buffer[byte_counter+2] == '1'){
			output_number += 32;
		}
		if(encoded_buffer[byte_counter+3] == '1'){
			output_number += 16;
		}
		if(encoded_buffer[byte_counter+4] == '1'){
			output_number += 8;
		}
		if(encoded_buffer[byte_counter+5] == '1'){
			output_number += 4;
		}
		if(encoded_buffer[byte_counter+6] == '1'){
			output_number += 2;
		}
		if(encoded_buffer[byte_counter+7] == '1'){
			output_number += 1;
		}

		byte_counter += 8;
		number_of_bytes -= 1;
		//printf("Writing value %d\n",output_number);
		fwrite(&output_number,sizeof(char),1,out_file);	
	}


	//printf("Here is data %s, the next %p and the value %d\n", checker->data->base_pattern,checker->next,checker->data->value);
}

char* two_bit_converter(uint32_t num){
	char* temp;

	if(((num > 0x1) == 0) && ((num & 0x1) == 0)){
		temp = "00";
	}
	else if(((num > 0x1) == 0) && ((num & 0x1) == 1)){
		temp = "01";
	}
	else if(((num > 0x1) == 1) &&  ((num & 0x1) == 0)){
		temp = "10";
	}
	else{
		temp = "11";
	}
	return temp;
}


void Encode(FILE* in_file, FILE* out_file) {

	struct node* head = NULL; 
	struct node* tail = NULL;
	int value_counter = 4;
	int number_bit = 3;
	char all_output[50000] = "";
	int multi_2 = 8;
	int error_check;
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

	char w [1000] = "a";
	int two_bit = 1;

	int first_run = 1;

	char* K;

	int loop;

	while(number_of_bases > 0){

		unsigned char input;
		//Reads in a byte
		error_check = fread(&input, sizeof(char), 1, in_file);

		print_binary(input);
		uint32_t base;
	
		if(first_run){
			loop = 3;
		}
		else{
			loop = 4;
		}

		//If there is an error, means no more input
		if(error_check == 0){
			printf("Error detected as we are reading bits but not intialized yet\n");
			if(w[0] != 'a' && number_of_bases == 1){
				strcat(all_output,w);
		 		strcat(all_output,"+");
			}
			else{
				error = 1;
			}
			number_of_bases = 0;
		}
		else{
			while(loop > 0 && number_of_bases > 0){
				
				//Want to change so that we only interpret 2 bit so
				if(two_bit == 1){
					base = input >> 6;
					two_bit = 2;
				}
				else if(two_bit == 2){
					base = (input & 0x30) >> 4;
					two_bit = 3;
				}
				else if(two_bit == 3){
					base = (input & 0x0C) >> 2;
					two_bit = 4;
				}
				else if(two_bit == 4){
					base = (input & 0x03);
					two_bit = 1;
				}

				if(first_run){
					char* temp_K = two_bit_converter(base);
					strcpy(w,temp_K);			
					first_run = 0;
				}

				//If we aren't at the last base
				if(number_of_bases > 1){
					uint32_t temp_base; 
					//Looks ahead at next base
					if(two_bit == 1){
						temp_base = input >> 6;
					}
					else if(two_bit == 2){
						temp_base = (input & 0x30) >> 4;
					}
					else if(two_bit == 3){
						temp_base = (input & 0x0C) >> 2;
					}
					else if(two_bit == 4){
						temp_base = (input & 0x03);
					}
					K = two_bit_converter(temp_base);
				}
				else{
					K = NULL;
				}

				printf("This is K %s and w %s\n",K,w);

				//For Base
				if(K == NULL){
		 			//writer(w,out_file);
		 			strcat(all_output,w);
		 			strcat(all_output,"+");
				}
				//Contains wK in table then repeat and wK becomes w
				else if(checker(w,K,head)){
					strcat(w,K);
				} 
				else{
					//write out w
				    //writer(w,out_file);
					strcat(all_output,w);
					strcat(all_output,"+");
					
					//adding wK to the string table
					struct node *temp = (struct node*)malloc(sizeof(struct node));
					char* temp_w = malloc(1000*sizeof(char));
					strcpy(temp_w,w);
					strcat(temp_w,K);

				    struct compressor *compress_temp = (struct compressor*)malloc(sizeof(struct compressor));
				    compress_temp->base_pattern = temp_w;
				    compress_temp->value = value_counter;

				    temp->data = compress_temp;
				    temp->next = NULL;

				    tail->next = temp;
				    tail = temp;

				    if(value_counter == multi_2){
				    	strcat(all_output,"-");
				    	multi_2 *= 2;
				    }

				   	value_counter +=1;


				    //K replaces w
				    strcpy(w,K);  
				}

				loop -=1;
				number_of_bases -= 1;
			}
		}

		printf("number_of_bases %d\n",number_of_bases);
	}

	strcat(all_output,"=");
	if(error == 1){
		printf("Invalid encoder input: .*\n");
	}
	else{
		writer(all_output,out_file,head,number_bit);
	}
	

}
