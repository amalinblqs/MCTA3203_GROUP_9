#include <Wire.h>

#define IR_SENSOR 9
#define LED 8

void setup() {
  Wire.begin(8); // Slave address 8
  Wire.onRequest(requestEvent);
  
  pinMode(IR_SENSOR, INPUT);
  pinMode(LED, OUTPUT);
  digitalWrite(LED, LOW);
}

void loop() {
  int detection = digitalRead(IR_SENSOR);
  digitalWrite(LED, !detection);
  delay(100);
}

void requestEvent() {
  Wire.write(digitalRead(IR_SENSOR));
}