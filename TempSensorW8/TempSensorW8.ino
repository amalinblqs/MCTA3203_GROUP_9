const int analogPin = A0;  // Analog pin for LM35
const float voltageRef = 5.0;  // Voltage reference (5V from Arduino)
const int sensorMax = 1023;  // Max value for analogRead()

void setup() {
  Serial.begin(9600);
}

void loop() {
  int sensorValue = analogRead(analogPin);
  float voltage = sensorValue * (voltageRef / sensorMax); // Convert to voltage
  float temperature = voltage * 100.0; // LM35 gives 10mV per °C (adjust this if using different LM35)

  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.println(" °C");

  delay(1000); // Delay for 1 second
}