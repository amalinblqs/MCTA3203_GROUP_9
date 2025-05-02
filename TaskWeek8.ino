#include <SoftwareSerial.h>

const int analogPin = A0;      // LM35 sensor connected to A0
const int fanPin = 8;          // Fan connected to digital pin 8 (via relay)
const float voltageRef = 5.0;  // Voltage reference (5V)
const int sensorMax = 1023;    // Max analog value for 10-bit ADC

bool manualOverride = false;   // Tracks if phone manually controls fan
bool fanState = false;         // Stores the fan's ON/OFF state

SoftwareSerial bluetooth(2, 3); // RX, TX (connect HC-05 TX to pin 2, RX to pin 3)

void setup() {
  Serial.begin(9600);           // For Bluetooth (HC-05)
  bluetooth.begin(9600);        // Bluetooth communication
  pinMode(fanPin, OUTPUT);      // Set fan pin as output
  digitalWrite(fanPin, LOW);    // Fan is OFF initially
  Serial.println("Bluetooth Fan Control Ready");
}

void loop() {
  // Read temperature from LM35
  int sensorValue = analogRead(analogPin);
  float voltage = sensorValue * (voltageRef / sensorMax);
  float temperature = voltage * 100.0; // LM35 outputs 10mV/°C

  // Send temperature to both Serial Monitor and Bluetooth
  String tempMessage = "Temperature: " + String(temperature) + " °C";
  Serial.println(tempMessage);
  bluetooth.println(tempMessage);

  // Auto fan control (only if not manually overridden)
  if (!manualOverride) {
    if (temperature >= 30.0 && !fanState) {
      digitalWrite(fanPin, HIGH);  // Turn fan ON
      fanState = true;
      Serial.println("Auto: Fan ON");
      bluetooth.println("Auto: Fan ON");
    } else if (temperature < 30.0 && fanState) {
      digitalWrite(fanPin, LOW);   // Turn fan OFF
      fanState = false;
      Serial.println("Auto: Fan OFF");
      bluetooth.println("Auto: Fan OFF");
    }
  }

  // Check for incoming Bluetooth commands
  if (bluetooth.available()) {
    String command = bluetooth.readStringUntil('\n');
    command.trim();

    if (command == "FAN_ON") {
      digitalWrite(fanPin, HIGH);  // Turn fan ON
      fanState = true;
      manualOverride = true;
      Serial.println("Manual: Fan ON");
      bluetooth.println("Manual: Fan ON");
    } else if (command == "FAN_OFF") {
      digitalWrite(fanPin, LOW);   // Turn fan OFF
      fanState = false;
      manualOverride = true;
      Serial.println("Manual: Fan OFF");
      bluetooth.println("Manual: Fan OFF");
    } else if (command == "AUTO") {
      manualOverride = false;
      Serial.println("Switched to AUTO mode");
      bluetooth.println("Switched to AUTO mode");
    }
  }

  delay(1000);  // 1 second delay between readings
}
