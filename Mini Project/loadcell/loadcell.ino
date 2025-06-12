#include "HX711.h"

#define DT  3
#define SCK 2

HX711 scale; 

// Replace this with the number you got from calibration
#define CALIBRATION_FACTOR  87.38134

void setup() {
  Serial.begin(9600);
  scale.begin(DT, SCK);
  scale.set_scale(CALIBRATION_FACTOR);
  scale.tare();
  Serial.println("Scale ready. Place weight.");
}

void loop() {
  float weight = scale.get_units(10);  // average over 10 readings
  Serial.print("Weight: ");
  Serial.print(weight, 2);
  Serial.println(" grams");
  delay(500);
}
