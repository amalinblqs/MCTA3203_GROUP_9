#include <Wire.h>
#include <MPU6050.h>

MPU6050 mpu;
int ax, ay, az, gx, gy, gz;
const int accelThreshold = 17000; // Increased threshold for correct motion detection
const int gyroThreshold = 1000;   // Keep gyro threshold the same
const int greenLED = 5;
const int redLED = 6;

void setup() {
    Serial.begin(9600);
    Wire.begin();
    mpu.initialize();
    
    pinMode(greenLED, OUTPUT);
    pinMode(redLED, OUTPUT);
}

void loop() {
    mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);

    Serial.print("Ax: "); Serial.print(ax);
    Serial.print(" Ay: "); Serial.print(ay);
    Serial.print(" Az: "); Serial.print(az);
    Serial.print(" | Gx: "); Serial.print(gx);
    Serial.print(" Gy: "); Serial.print(gy);
    Serial.print(" Gz: "); Serial.println(gz);

    bool motionDetected = (abs(ax) > accelThreshold || abs(ay) > accelThreshold || abs(az - 16384) > accelThreshold);
    bool rotationDetected = (abs(gx) > gyroThreshold || abs(gy) > gyroThreshold || abs(gz) > gyroThreshold);

    if (motionDetected && !rotationDetected) {
        digitalWrite(greenLED, HIGH); // Motion only
        digitalWrite(redLED, LOW);
    } else if (rotationDetected) {
        digitalWrite(redLED, HIGH); // Rotation detected
        digitalWrite(greenLED, LOW);
    } else {
        digitalWrite(greenLED, LOW);
        digitalWrite(redLED, LOW);
    }

    delay(100);
}