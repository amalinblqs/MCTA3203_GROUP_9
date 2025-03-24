
#include <Servo.h>

Servo myServo;
int potPin = A0; 
int servoPin = 8;
int angle = 90; // Default servo position

void setup() {
    myServo.attach(servoPin);
    Serial.begin(9600);
}

void loop() {
    // Read potentiometer and map to 0-180
    int potValue = analogRead(potPin);
    int potAngle = map(potValue, 0, 1023, 0, 180);
    
    // Check if there's serial input
    if (Serial.available() > 0) {
        angle = Serial.parseInt(); // Read angle from Python
        if (angle >= 0 && angle <= 180) {
            myServo.write(angle);
            Serial.print("Received Angle: ");
            Serial.println(angle);
        }
    }

    Serial.print("Potentiometer Value: "); 
    Serial.print(potValue);
    Serial.print(" | Servo Angle: "); 
    Serial.println(potAngle);

    delay(50);
}
