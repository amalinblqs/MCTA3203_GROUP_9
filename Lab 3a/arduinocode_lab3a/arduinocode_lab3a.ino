int potPin = A0;   // Potentiometer connected to A0
int ledPin = 9;    // LED connected to PWM pin 9
int potValue = 0;  // Variable to store potentiometer value
int brightness = 0; // LED brightness (0-255)

void setup() {
    Serial.begin(9600);  // Start serial communication
    pinMode(ledPin, OUTPUT);  // Set LED pin as output
}

void loop() {
    potValue = analogRead(potPin);  // Read the potentiometer value (0-1023)
    brightness = map(potValue, 0, 1023, 0, 255); // Convert to PWM range (0-255)
    
    analogWrite(ledPin, brightness);  // Set LED brightness
    
    Serial.println(brightness);  // Send brightness value to Serial Monitor
    delay(50); // Small delay for stability
}