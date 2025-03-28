#include <Wire.h>
#include <MPU6050.h>

MPU6050 mpu;

// Define LED pins
const int led1 = 6;  // GreenLED for Gesture 1
const int led2 = 7;  // YellowLED for Gesture 2

const int threshold = 1000;  // Adjust this threshold as needed
int previousGesture = -1;

void setup() {
  Serial.begin(9600);
  Wire.begin();
  mpu.initialize();

  // Set LED pins as output
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);

  // Turn off LEDs initially
  digitalWrite(led1, LOW);
  digitalWrite(led2, LOW);
}

void loop() {
  int gesture = detectGesture();

  if (gesture != previousGesture) {
    Serial.print("Detected Gesture: ");
    if (gesture == 1) {
      Serial.println("Gesture 1: Right");
      digitalWrite(led1, HIGH);  // Turn on LED1
      digitalWrite(led2, LOW);   // Turn off other LED
    } else if (gesture == 2) {
      Serial.println("Gesture 2: Left");
      digitalWrite(led2, HIGH);  // Turn on LED2
      digitalWrite(led1, LOW);
    } else {
      // No gesture detected, turn off all LEDs
      digitalWrite(led1, LOW);
      digitalWrite(led2, LOW);
    }

    previousGesture = gesture;
  }
}

// Function to detect gestures based on accelerometer data
int detectGesture() {
  int ax, ay, az, gx, gy, gz;
  mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);

  if (ax > threshold && ay < threshold) {
    return 1;  // Gesture 1 detected
  } else if (ax < -threshold && ay > threshold) {
    return 2;  // Gesture 2 detected
  }
  return 0;  // No gesture detected
}
