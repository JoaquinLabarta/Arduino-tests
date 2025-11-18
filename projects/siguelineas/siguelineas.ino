const int sensores[5] = { A0, A1, A2, A3, A4 };  // S0..S4 (Izq a Der)
const int motores[6] = { 10, 11, 7, 6, 5, 4 };   // ENABLE1, ENABLE2, IN1, IN2, IN3, IN4

// Variables globales del PID
int lastError = 0;             // Ultima error registrado
float integral = 0;            // Acumulador del termino integral
int lastKnownPosition = 2000;  // Ultima posicion conocida (inicio en el centro)

void setup() {
  Serial.begin(9600);  // Inicia comunicacion para depurar

  // Configura los pines de los sensores y motores
  for (int i = 0; i < 5; i++) {
    pinMode(sensores[i], INPUT);
  }
  for (int j = 0; j < 6; j++) {
    pinMode(motores[j], OUTPUT);
  }
}

void loop() {
  // Lectura de sensores y cálculo de posición
  int sensorValues[5];
  int position = 0;
  int activeSensors = 0;

  for (int i = 0; i < 5; i++) {
    sensorValues[i] = analogRead(sensores[i]);
    if (sensorValues[i] > 500) {
      position += i * 1000;  // Configuro peso a los sensores (0,1000,2000,3000,4000)
      activeSensors++;       // Cuento cantidad de sensores activos
    }
  }

  int linePosition;
  if (activeSensors > 0) {
    linePosition = position / activeSensors;  // Promedio posicion
    lastKnownPosition = linePosition;
  } else {
    linePosition = lastKnownPosition;  // Mantener última posición si se pierde la línea
  }

  // PID
  int setPoint = 2000;                  // Centro
  int error = linePosition - setPoint;  // Error actual

  // Constantes PID
  float Kp = 0.04;    // Ganancia proporcional
  float Ki = 0.0003;  // Ganancia integral
  float Kd = 0.7;    // Ganancia derivativa

  integral += error;
  integral = constrain(integral, -1000, 1000);  // Acota el valor para proteger contra integral windup

  int derivative = error - lastError;                           // Cambio de error respecto al anterior
  float output = Kp * error + Ki * integral + Kd * derivative;  // Cálculo de salida PID
  lastError = error;                                            // Actualiza el último error

  // Control de motores
  int baseSpeed = 80;  // Velocidad base de los motores (ajustable)
  int maxSpeed = 170;   // Velocidad máxima de los motores

  int leftSpeed = (baseSpeed + output);   // Ajuste de velocidad izquierda
  int rightSpeed = baseSpeed - output;  // Ajuste de velocidad derecha

  // Limita las velocidades para no exceder el PWM máximo
  leftSpeed = constrain(leftSpeed, 0, maxSpeed);
  rightSpeed = constrain(rightSpeed, 0, maxSpeed);

  // Motor izquierdo
  analogWrite(motores[0], leftSpeed);  // ENABLE1
  digitalWrite(motores[2], HIGH);      // IN1 (sentido adelante activado)
  digitalWrite(motores[3], LOW);       // IN2 (sentido trasero no activado)

  // Motor derecho
  analogWrite(motores[1], rightSpeed);  // ENABLE2
  digitalWrite(motores[4], HIGH);       // IN3 (sentido adelante activado)
  digitalWrite(motores[5], LOW);        // IN4 (sentido trasero no activado)
  
  delay(10);  // Pausa para estabilidad
}