// Written by Duncan 5/10/17
// This program displays my name.

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>
#include "graphics.h"

int convert(double radian){

	int degree;

	degree = radian * 180 / 3.14;

	return degree;
}

int main(void){
 
 int z = 0;
 colour colours[13] = {black, blue,cyan, darkgray, gray, green, lightgray, magenta, orange, pink, red, white, yellow};

 setColour(black);
 fillRect(0,0,499,299);

 for(double x=0; x<12.56; x = x + .1){

	double y = sin(x);

	y = convert(y);

	z += 5;

	int random =  rand() % 13;

	setColour(colours[random]);
	drawLine(40+z,175+y,0+z,175+y);

	sleep(1);

/*
	    if(x > 6.28){
	    	setColour(colours[black]);
	    	drawLine(40+z,175+y,0+z,175+y);
	    }
  */  
	 }




 return 0;
}
