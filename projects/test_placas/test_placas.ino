int leds[] = {13,11,10}; // Red, Yellow, Green
int buttons[] = {7,8,12}; // Red, Yellow, Green
int analogicos[] = {A0,A1}; // LDR, Potenciometro
int BRILLO;

void setup() {
  Serial.begin(9600);
  for (int i = 0; i<3; i++) {
    pinMode(leds[i], OUTPUT); 
  }
  for (int j = 0; j<3; j++) {
    pinMode(buttons[j], INPUT_PULLUP); // HIGH cuando no esta presionado, si fuese solo INPUT es al reves pero detecta mucho ruido
  }
}

void loop() {

  BRILLO = map(analogRead(analogicos[1]), 0, 1023, 0, 255); // Mapea var * 255 / 1023
  
  Serial.print(analogRead(analogicos[0])); // Chequeo que lee el LDR
  delay(100);

  if (analogRead(analogicos[0]) < 770) { // Si no detecto luz que se apague
    delay(100);
    for (int i = 0; i<3; i++) {
      analogWrite(leds[i], 0);
    }
  } 
  else {
    if (digitalRead(buttons[0]) == HIGH) {
      analogWrite(leds[0], BRILLO);
    } else {
      analogWrite(leds[0], 0);
    }

    if (digitalRead(buttons[1]) == HIGH) {
      analogWrite(leds[1], BRILLO);
    } else {
      analogWrite(leds[1], 0);
    }

    if (digitalRead(buttons[2]) == HIGH) {
      analogWrite(leds[2], BRILLO); 
    } else {
      analogWrite(leds[2], 0);
    }

    delay(100);
  }
}