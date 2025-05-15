const int TRIG = 2;
const int ECHO = 3;
const int LED = 10; // Uso el 10 por PWM

long duracion;
float distancia;

void setup() {
  Serial.begin(9600);
  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT_PULLUP);
  pinMode(LED, OUTPUT);
}

void loop() {
  // Pulso de 10us
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);

  // Mido tiempo del rebote del pulso
  duracion = pulseIn(ECHO, HIGH);
  Serial.println(duracion);

  // Calculo distancia (cm)
  distancia = duracion * 0.017;

  int brillo = map(distancia, 5, 50, 255, 0);  // Más cerca => más brillo
  brillo = constrain(brillo, 0, 255); // Limito valores

  analogWrite(LED, brillo);

  Serial.print("Distancia: ");
  Serial.print(distancia);
  Serial.println(" cm");

  delay(200);
}
