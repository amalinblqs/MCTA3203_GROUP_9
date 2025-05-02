#include <SoftwareSerial.h> 
SoftwareSerial bluetooth(2, 3); // RX, TX 
void setup() { 
Serial.begin(9600);   // Serial communication with the computer 
bluetooth.begin(9600); // Serial communication with HC-05 module 
Serial.println("Bluetooth Communication Ready"); 
} 
void loop() { 
// Read data from the computer and send it to HC-05 
if (Serial.available() > 0) { 
char data = Serial.read(); 
bluetooth.print(data); 
} 
// Read data from HC-05 and send it to the computer 
if (bluetooth.available() > 0) { 
char data = bluetooth.read(); 
Serial.print(data); 
} 
}