#include <DHT.h>
#define DHTTYPE DHT11 // Cambiar a DHT22 si usás ese

const int bLed = 12;
const int buzzer = 3; 
const int DHTPIN = 2;

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  dht.begin();
  pinMode(bLed, OUTPUT);
  pinMode(buzzer, OUTPUT);
}

void loop() {
  float temp = dht.readTemperature();

  // Error
  if (isnan(temp)) {
    Serial.println("Error al leer el sensor DHT");
    return;
  }

  Serial.print("Temperatura: ");
  Serial.print(temp);
  Serial.println(" °C");

  if (temp>18.0) {
    analogWrite(bLed, 255);
    delay(100);
    analogWrite(bLed,0);
  } else {
    analogWrite(bLed, 0);
  }

  delay(2000);
}
