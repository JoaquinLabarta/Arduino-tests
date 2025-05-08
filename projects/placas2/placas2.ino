int rLed = 13;
int yLed = 11;
int gLed = 10;
int rBut = 7;
int yBut = 8;
int gBut = 12;
int POT = A1;
int BRILLO;

void setup() {
  Serial.begin(9600);
  pinMode(rBut,INPUT_PULLUP);
  pinMode(yBut,INPUT_PULLUP);
  pinMode(gBut,INPUT_PULLUP);
  pinMode(rLed, OUTPUT);
  pinMode(yLed, OUTPUT);
  pinMode(gLed,OUTPUT);
}

void loop() {

  BRILLO = map(analogRead(POT), 0, 1023, 0, 255); // Mapea var * 255 / 1023

  if (digitalRead(rBut) == LOW) {analogWrite(rLed, BRILLO);}
  if (digitalRead(yBut) == HIGH) {analogWrite(yLed, BRILLO);}
  if (digitalRead(gBut) == LOW) {analogWrite(gLed, BRILLO);}
  
  
  

  delay(100);
}