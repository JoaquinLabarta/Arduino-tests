int rLed = 13;
int yLed = 11;
int gLed = 10;
int rBut = 7;
int yBut = 8;
int gBut = 12;
int LDR = A0; // No hacen falta declarar
int POT = A1;
int BRILLO;

void setup() {
  Serial.begin(9600);
  pinMode(rBut,INPUT_PULLUP); // HIGH cuando no esta precionado, si fuese solo INPUT es al reves pero detecta mucho ruido
  pinMode(yBut,INPUT_PULLUP);
  pinMode(gBut,INPUT_PULLUP);
  pinMode(rLed, OUTPUT);
  pinMode(yLed, OUTPUT);
  pinMode(gLed,OUTPUT);
}

void loop() {

  Serial.print(analogRead(LDR));
  delay(100);

  BRILLO = map(analogRead(POT), 0, 1023, 0, 255); // Mapea var * 255 / 1023

  if (analogRead(LDR) > 750) { // Si no detecto luz que se apague
    delay(100);
    analogWrite(rLed, 0);
    analogWrite(yLed, 0);
    analogWrite(gLed, 0);
  } else {
    if (digitalRead(rBut) == HIGH) {
      analogWrite(rLed, BRILLO);
    } else {
      analogWrite(rLed, 0);
    }

    if (digitalRead(yBut) == HIGH) {
      analogWrite(yLed, BRILLO);
    } else {
      analogWrite(yLed, 0);
    }

    if (digitalRead(gBut) == HIGH) {
      analogWrite(gLed, BRILLO); 
    } else {
      analogWrite(gLed, 0);
    }

    delay(100);
  }
}