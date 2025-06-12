#include <SPI.h>
#include <Pixy.h>

Pixy pixy;

const int buzzerPin = 9;  // Digital pin for the passive buzzer

void setup() {
  Serial.begin(9600);
  pixy.init();

  pinMode(buzzerPin, OUTPUT);  // Set buzzer pin as output
  digitalWrite(buzzerPin, LOW);  // Ensure it's off at start
}

void loop() {
  uint16_t blockCount = pixy.getBlocks();

  bool whiteDetected = false;

  if (blockCount > 0) {
    for (int i = 0; i < blockCount; i++) {
      uint8_t sig = pixy.blocks[i].signature;

      if (sig == 1) {
        whiteDetected = true;
        break;
      }
    }
  }

  if (whiteDetected) {
    Serial.println("⚠ WARNING: White cloth detected!");
    digitalWrite(buzzerPin, HIGH);  // Turn on buzzer
  } else {
    Serial.println("OK - No white cloth detected.");
    digitalWrite(buzzerPin, LOW);  // Turn off buzzer
  }

  delay(500);  // 0.5 second update
}