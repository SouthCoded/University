int ThermistorPin = 0;
int voltageOutput;
float fixedResistor = 10000;
float logR2, R2, T;
float c1 = 1.009249522e-03, c2 = 2.378405444e-04, c3 = 2.019202697e-07;

void setup() {
Serial.begin(9600);
}

void loop() {

  voltageOutput = analogRead(ThermistorPin);
  R2 = fixedResistor * (1023.0 / (float)voltageOutput - 1.0);
  logR2 = log(R2);
  float K = (1.0 / (c1 + c2*logR2 + c3*logR2*logR2*logR2)); // Steinhart and Hart Equation. T  = 1 / {A + B[ln(R)] + C[ln(R)]^3}
  float C = K - 273.15;                                     // Converting Kelvin to Celcius
  float F = (C * 9.0)/ 5.0 + 32.0;                          // Converting Celcius to Fahrenheit

  Serial.println("Temperature: "); 
  Serial.print(K);
  Serial.println(" K"); 
   Serial.print(C);
  Serial.println(" C");
   Serial.print(F);
  Serial.println(" F");

  delay(500);
}

