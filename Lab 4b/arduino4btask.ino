
#include <Servo.h>
#include <ArduinoJson.h>


Servo servo;
int servoPin = 9;
int greenLEDPin = 7;
int redLEDPin = 6;


void setup() {
  servo.attach(servoPin);
  servo.write(0);  // default locked
  pinMode(greenLEDPin, OUTPUT);
  pinMode(redLEDPin, OUTPUT);


  Serial.begin(9600);
  Serial.println("Arduino ready");
}


void loop() {
  static String jsonInput = "";


  while (Serial.available() > 0) {
    char incoming = Serial.read();


    if (incoming == '\n') {
      DynamicJsonDocument doc(128);
      DeserializationError error = deserializeJson(doc, jsonInput);


      if (!error) {
        const char* access = doc["access"];
        int angle = doc["angle"];


        if (strcmp(access, "granted") == 0) {
          servo.write(angle);
          digitalWrite(greenLEDPin, HIGH);
          digitalWrite(redLEDPin, LOW);
          Serial.println("Access granted → Green LED + Servo moved");
        } else {
          servo.write(angle);
          digitalWrite(greenLEDPin, LOW);
          digitalWrite(redLEDPin, HIGH);
          Serial.println("Access denied → Red LED + Servo moved");
        }
      } else {
        Serial.println("Failed to parse JSON.");
      }


      jsonInput = ""; // reset input
    } else {
      jsonInput += incoming;
    }
  }
}
