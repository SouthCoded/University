//Code for Comp101 Arduino Project
//Duncan Rowe, 4/11/17

#include <math.h>
//Variables for calculating temperature
int thermistorPin = 0;
int voltageOutput;
float fixedResistor = 10000;
float logRestistor2, resistor2, T;
float c1 = 1.009249522e-03, c2 = 2.378405444e-04, c3 = 2.019202697e-07;

//Setting variables for the buttons
int firstButtonInput = 2;
int firstLight = 3;
int firstButtonState = 0;

int secondButtonInput = 8;
int secondLight = 9;
int secondButtonState = 0;

int thirdButtonInput = 12;
int thirdLight = 13;
int thirdButtonState = 0;

//Variable for the lights
int lightOn = 0;

//Variable for the speaker
int speaker = 10;

void setup() {
Serial.begin(9600);

pinMode(firstLight, OUTPUT);
pinMode(firstButtonInput, INPUT);
digitalWrite(firstButtonInput, HIGH);

pinMode(secondLight, OUTPUT);
pinMode(secondButtonInput, INPUT);
digitalWrite(secondButtonInput, HIGH);

pinMode(thirdLight, OUTPUT);
pinMode(thirdButtonInput, INPUT);
digitalWrite(thirdButtonInput, HIGH);
 
pinMode(speaker, OUTPUT);

}

void loop() {

  //Calculating temperature from the thermistor
  voltageOutput = analogRead(thermistorPin)-200;
  resistor2 = fixedResistor * (1023.0 / (float)voltageOutput - 1.0);
  logRestistor2 = log(resistor2);
  float kelvin = (1.0 / (c1 + c2*logRestistor2 + c3*logRestistor2*logRestistor2*logRestistor2)); // Steinhart and Hart Equation. T  = 1 / {A + B[ln(R)] + C[ln(R)]^3}

  //Reading input from buttons and setting the appropriate lights
  firstButtonState = digitalRead(firstButtonInput);
  if (firstButtonState == LOW) {
      digitalWrite(firstLight, HIGH);
      digitalWrite(secondLight, LOW);
      digitalWrite(thirdLight, LOW);   
      lightOn = 1;   
  }

  secondButtonState = digitalRead(secondButtonInput);
  if (secondButtonState == LOW) {
      digitalWrite(secondLight, HIGH);
      digitalWrite(firstLight, LOW);
      digitalWrite(thirdLight, LOW); 
      lightOn = 2; 
  }

  thirdButtonState = digitalRead(thirdButtonInput);
  if (thirdButtonState == LOW) {
      digitalWrite(thirdLight, HIGH);
      digitalWrite(firstLight, LOW);  
      digitalWrite(secondLight, LOW);
      lightOn = 3;
  }

  //Speaker only plays Jingle Bells if it is below freezing
  if (kelvin < 273.15){
      song();

  }

  Serial.println(kelvin);
  delay(1500);
  Serial.println(lightOn);

  delay(1500);

}

void song(){
  
  int length = 26;
  char note[] = "eeeeeeegcde fffffeeeeddedg";    //Overall sheet music for jingle bells
  int beat[] = { 1, 1, 2, 1, 1, 2, 1, 1, 1, 1, 4, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2}; //How long each note should play for
  int tempo = 300;
  
  for (int i = 0; i < length; i++) {
    if (note[i] == ' ') {
      delay(beat[i] * tempo); // rest
    }
    else {
     char name[] = { 'c', 'd', 'e', 'f', 'g'};
     int tone[] = { 1915, 1700, 1519, 1432, 1275};
     
     for (int t = 0; t < 5; t++) {
        if (name[t] == note[i]) { 
           for (long p = 0; p < (beat[i] * tempo * 1000L); p += tone[t] * 2) {  //For loop is necessary as turning the speaker off and on is one click and you want a continous sound
             digitalWrite(speaker, HIGH);
             delayMicroseconds(tone[t]);
             digitalWrite(speaker, LOW);
             delayMicroseconds(tone[t]);
           }
        }
     }
    } 
    delay(tempo / 2);  // pause between notes
  }
} 


