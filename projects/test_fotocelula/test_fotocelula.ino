int leds[] = {13,11,10}; // Red, Yellow, Green
int buttons[] = {7,8,12}; // Red, Yellow, Green
int analogicos[] = {A0,A1}; // LDR, Potenciometro
bool estados[] = {true,true,true};
bool estAnteBut[] = {HIGH,HIGH,HIGH};

void setup() {
  Serial.begin(9600);
  for (int i = 0; i<3; i++) {
    pinMode(leds[i], OUTPUT); 
    pinMode(buttons[i], INPUT_PULLUP);
  }
}

void loop() {

  int luz = analogRead(analogicos[0]);
  int pot = analogRead(analogicos[1]);
  int BRILLO = map(pot, 0, 1023, 0, 255); // Mapea pot * 255 / 1023

  Serial.print(luz); // Chequeo que lee el LDR
  delay(50); // Para no saturar puerto

  if (luz < 800) { // Hay luz, apago leds
    for (int i = 0; i<3; i++) {
      analogWrite(leds[i], 0);
      estados[i] = true; // Se reinicia para que el proximo estado avise que estuvieron prendidos
    }
  } 
  else { // Hay oscuridad
    for (int i = 0; i<3; i++) {
      bool estadoBut = digitalRead(buttons[i]); // Leo estado del led

      if ((estadoBut == LOW) && (estAnteBut[i] == HIGH)) { // Detecto flanco de bajada presionando
        delay(50);
        estados[i] = !estados[i]; // Cambio estado del led en el ternario
      }

      estAnteBut[i] = estadoBut; // Guardo estado del led para la prox
      analogWrite(leds[i], estados[i] ? BRILLO : 0);
    }
  }
}