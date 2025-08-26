#include <OneWire.h>
#include <DallasTemperature.h>
#define pinHumedad 1
OneWire ourWire(12);
DallasTemperature sensors(&ourWire);

void setup() {
  // put your setup code here, to run once:
  delay(1000);
  Serial.begin(9600);
  sensors.begin();

}

void loop() {
  // put your main code here, to run repeatedly:
  sensors.requestTemperatures();
  float temp = sensors.getTempCByIndex(0);
  float humedad = analogRead(pinHumedad);
  humedad = map(humedad,1024,0,0,100);

  Serial.print("Temperatura: ");
  Serial.print(temp);
  Serial.println(" °C");
  Serial.print("Humedad Relativa: ");
  Serial.print(humedad);
  Serial.println("%");
  delay(500);

}
