const int sensores[5] = {2, 4, 7, 8, 12}; // S0..S4 (Izq a Der)
const int motores[6] = {6, 11, 3, 5, 9, 10};  // ENABLE1, ENABLE2, IN1, IN2, IN3, IN4

void setup() {
  Serial.begin(9600);

  for (int i = 0; i < 5; i++) {
    pinMode(sensores[i], INPUT);
  }

  for (int j = 0; j < 6; j++) {
    pinMode(motores[j], OUTPUT);
  }
}

void loop() {
  // Velocidades maximas
  analogWrite(motores[0], 50); // ENABLE1
  analogWrite(motores[1], 50); // ENABLE2

  // Leer sensores
  int s[5];
  for (int i = 0; i < 5; i++) {
    s[i] = digitalRead(sensores[i]);
  }

  // Lógica de movimiento
  if (s[0] == 0 && s[1] == 0 && s[2] == 1 && s[3] == 0 && s[4] == 0) {
    avanzar();
  } else if ((s[0] == 0 && s[1] == 1) || (s[0] == 1)) {
    girarIzquierda();
  } else if ((s[3] == 1 && s[4] == 0) || (s[4] == 1)) {
    girarDerecha();
  } else if (s[0] == 0 && s[1] == 0 && s[2] == 0 && s[3] == 0 && s[4] == 0) {
    detener();
  }
  delay(100);
}

void avanzar() {
  digitalWrite(motores[2], HIGH); // IN1
  digitalWrite(motores[3], LOW);  // IN2
  digitalWrite(motores[4], HIGH); // IN3
  digitalWrite(motores[5], LOW);  // IN4
}

void girarIzquierda() {
  digitalWrite(motores[2], LOW);
  digitalWrite(motores[3], HIGH);
  digitalWrite(motores[4], HIGH);
  digitalWrite(motores[5], LOW);
}

void girarDerecha() {
  digitalWrite(motores[2], HIGH);
  digitalWrite(motores[3], LOW);
  digitalWrite(motores[4], LOW);
  digitalWrite(motores[5], HIGH);
}

void detener() {
  digitalWrite(motores[2], LOW);
  digitalWrite(motores[3], LOW);
  digitalWrite(motores[4], LOW);
  digitalWrite(motores[5], LOW);
}
