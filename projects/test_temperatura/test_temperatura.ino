#include <DHT.h>
#define DHTPIN 2      // Pin de datos del sensor
#define DHTTYPE DHT11 // Cambiar a DHT22 si usás ese

DHT dht(DHTPIN, DHTTYPE);

const int bLed = 10;
const int yLed = 11;

void setup() {
  Serial.begin(9600);
  dht.begin();
  pinMode(bLed, OUTPUT);
  pinMode(yLed, OUTPUT);
}

void loop() {
  float temp = dht.readTemperature();
  if (isnan(temp)) {
    Serial.println("Error al leer el sensor DHT");
    return;
  }

  Serial.print("Temperatura: ");
  Serial.print(temp);
  Serial.println(" °C");

  if (temp<18.0) {
    analogWrite(bLed, 255);
    analogWrite(yLed, 0);
  } else {
    analogWrite(bLed, 0);
    analogWrite(yLed, 255);
  }

  delay(2000);
}
