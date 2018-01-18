
#include "abdrive.h"



void right_turn(){
	
	drive_goto(25,-25); //Turn right angle

}

void left_turn(){
	
	drive_goto(-25,25); //Turn left angle

}


void main() {


	char input[] = "A";

	for(int x =0; x< strlen(input);x++){

		switch(input[x]){

			case 'A':
				drive_goto(-17,17); //Turn left diagonal
				drive_goto(25,25); //Travel half distance
				drive_goto(17,-17); //Straightens
				drive_goto(25,25);
				drive_goto(-25,-25); //Backwards
				drive_goto(-17,17); //Turn left diagonal
				drive_goto(25,25); //Travel half distance
				right_turn();
				drive_goto(51,51); //Travel full distance

				//Resets for next position
				drive_goto(-17,17); //Turn left diagonal
				break;

			case 'E':
				drive_goto(25,25);
				drive_goto(-25,-25); //Backwards
				left_turn();
				drive_goto(17,17);
				right_turn(); 

				drive_goto(25,25);
				drive_goto(-25,-25); //Backwards
				left_turn();
				drive_goto(17,17);
				right_turn(); 

				drive_goto(25,25);

				//Resets for next position
				right_turn();
				drive_goto(50,50);
				left_turn();
				break;


			case 'F':
				left_turn();
				drive_goto(17,17);
				right_turn();
				drive_goto(25,25);   //Forwards
				drive_goto(-25,-25); //Backwards

				left_turn(); 
				drive_goto(17,17);
				right_turn(); 
				drive_goto(25,25);   //Forwards
				drive_goto(-25,-25); //Backwards

				//Resets for next position
				right_turn();
				drive_goto(50,50);
				left_turn();
				break;

			case 'H':
				left_turn();
				drive_goto(51,51);	//Forwards
				drive_goto(-25,-25); //Backwards
				right_turn(); 

				drive_goto(25,25);

				left_turn();
				drive_goto(25,25);  //Forwards
				drive_goto(-50,-50); //Backwards

				//Resets for next position
				right_turn();
				break;

			case 'I':
				left_turn();
				drive_goto(51,51);
				drive_goto(-51,-51);
				right_turn();

				//Resets for next position
				drive_goto(25,25);
				break;

			case 'K':
				left_turn();
				drive_goto(50,50); //Go forward
				drive_goto(-25,-25); //Go backwards
				drive_goto(17,-17); //Turn right diagonal
				drive_goto(25,25); //Travel half distance
				drive_goto(-25,-25); //Travels back
				right_turn();
				drive_goto(25,25);

				//Resets for next position
				drive_goto(-17,17); 
				break;

			case 'L':
				left_turn();
				drive_goto(51,51);
				drive_goto(-51,-51);
				right_turn();
				drive_goto(25,25);
				break;
			

		}

	}

}



