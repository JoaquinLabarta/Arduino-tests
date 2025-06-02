const int sensores[5] = {2,3,4,5,6};

void setup() {
  Serial.begin(9600);
  for (int i = 0; i<5; i++) {
    pinMode(sensores[i], INPUT);
  }
}

void loop() {
  for (int i = 0; i<5; i++) {
    int estado = digitalRead(sensores[i]);
    Serial.print("Sensor ");
    Serial.print(i);
    Serial.print(": ");
    Serial.println(estado == HIGH ? "Obstáculo" : "Libre");
    delay(300);
  }
}
