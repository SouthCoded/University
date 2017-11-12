import processing.serial.*;
import java.lang.Math;

Serial myPort;

String serialVal; 
int xPos;

int lit = -1;
float kelvin = -1.0;
float celcius = -1.0;
float fahrenheit = -1.0;

float prevY;

void setup() {
  size(800, 800);
  myPort = new Serial(this, Serial.list()[0], 9600); //setting up the serial connection
  myPort.bufferUntil('\n');
  frameRate(5); //how often the data is processed per second
  drawGraph();
}
//Method called by myPort.bufferUntil, simply waits for all the data to be sent 
void serialEvent(Serial p) {
  serialVal = myPort.readString();
}

void draw(){
  
  if (serialVal != null){ 
    
    serialVal = trim(serialVal);
    
    if (float(serialVal) > 100){  //checks if the data is the temperature or the light number
      kelvin = float(serialVal);
      celcius = kelvin - 273.15;
      fahrenheit = (celcius * (9.0/5)) + 32;
     }
    else{
      lit = int(serialVal); 
      String temp = "";
            
      if (lit == 1){
        temp = str(kelvin) + " K";
       }
      if (lit == 2){
        celcius = Math.round(celcius*100) / 100.0;
        temp = str(celcius) + " C";
       }
      if (lit == 3){
        fahrenheit = Math.round(fahrenheit*100) / 100.0;
        temp = str(fahrenheit) + " F";
       }
      if (lit == 0){
        temp = "Click a setting";
       }
   
      updateText(temp);
     
    }
    
  } 
  if (fahrenheit > 0 && fahrenheit < 100 ){
    float plotVar = fahrenheit/100;
    plotVar = 800 - (plotVar*800); //scales the temperature to fit the graph
    strokeWeight(2);
    stroke(255, 0, 0);
    line(frameCount-25, prevY, frameCount-24, plotVar);
    prevY = plotVar;
  }
}

void drawGraph() {
  background(0);

  //Draws Vertical Grid Lines
  for (int i = 0; i <= width; i += 50) {
    fill(0, 255, 0);
    text(i/2, i-10, height-15);
    stroke(255);
    line(i, height, i, 0);
  }

  //Draws Horizontal Grid Lines 
  for (int j = 0; j < height; j += 40) {
    fill(0, 255, 0);
    text(100-j/(height/100), 0, j);
    stroke(255);
    line(0, j, width, j);
  }
  
  //Draws the White Rectangle
  fill(255);    
  noStroke();
  rect(600, 50, 175, 50);
}

void updateText(String temperature){
  //Redraws the White Rectangle as there is no "erase" 
  fill(255);    
  noStroke();
  rect(600, 50, 175, 50);
   
  //Draws the text 
  fill(0, 0, 0);
  textSize(20);
  text(temperature, 615, 82);
  
}
