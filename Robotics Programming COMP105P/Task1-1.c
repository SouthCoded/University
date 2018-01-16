
#include "abdrive.h"


void right_turn(){
	
	drive_goto(307,307);
	drive_goto(51,0);

}

void main() {

	for(int x=0;x<4;x++){
		right_turn();
	}

}

