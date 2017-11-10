#include <math.h>
int thermistorPin = 0;
int voltageOutput;
float fixedResistor = 10000;
float logR2, R2, T;
float c1 = 1.009249522e-03, c2 = 2.378405444e-04, c3 = 2.019202697e-07;

int firstButtonInput = 2;
int firstLight = 3;
int firstButtonState = 0;

int secondButtonInput = 8;
int secondLight = 9;
int secondButtonState = 0;

int thirdButtonInput = 12;
int thirdLight = 13;
int thirdButtonState = 0;

int lit = 0;

int buzzer = 10;

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
 
pinMode(buzzer, OUTPUT);

song();

}

void loop() {

  voltageOutput = analogRead(thermistorPin)-200;
  R2 = fixedResistor * (1023.0 / (float)voltageOutput - 1.0);
  logR2 = log(R2);
  float K = (1.0 / (c1 + c2*logR2 + c3*logR2*logR2*logR2)); // Steinhart and Hart Equation. T  = 1 / {A + B[ln(R)] + C[ln(R)]^3}


  firstButtonState = digitalRead(firstButtonInput);
  if (firstButtonState == LOW) {
      digitalWrite(firstLight, HIGH);
      digitalWrite(secondLight, LOW);
      digitalWrite(thirdLight, LOW);   
      lit = 1;   
  }

  secondButtonState = digitalRead(secondButtonInput);
  if (secondButtonState == LOW) {
      digitalWrite(secondLight, HIGH);
      digitalWrite(firstLight, LOW);
      digitalWrite(thirdLight, LOW); 
      lit = 2; 
  }

  thirdButtonState = digitalRead(thirdButtonInput);
  if (thirdButtonState == LOW) {
      digitalWrite(thirdLight, HIGH);
      digitalWrite(firstLight, LOW);  
      digitalWrite(secondLight, LOW);
      lit = 3;
  }

  Serial.println(K);
  delay(1500);
  Serial.println(lit);

  delay(1500);

}

void song(){
  
  int length = 26;
  char notes[] = "eeeeeeegcde fffffeeeeddedg";
  int beats[] = { 1, 1, 2, 1, 1, 2, 1, 1, 1, 1, 4, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2};
  int tempo = 300;
  
   for (int i = 0; i < length; i++) {
    if (notes[i] == ' ') {
      delay(beats[i] * tempo); // rest
    }
    else {
      char names[] = { 'c', 'd', 'e', 'f', 'g'};
     int tones[] = { 1915, 1700, 1519, 1432, 1275};

      for (int t = 0; t < 5; t++) {
        if (names[t] == notes[i]) {
           for (long p = 0; p < (beats[i] * tempo * 1000L); p += tones[t] * 2) {
            digitalWrite(buzzer, HIGH);
            delayMicroseconds(tones[t]);
            digitalWrite(buzzer, LOW);
            delayMicroseconds(tones[t]);
          }
        }
      }
   } 
    // pause between notes
    delay(tempo / 2); 
  }
} 






