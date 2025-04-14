// Sensor pins
const int LM_PIN = A0;   // Pin A0 for the temperature sensor (LM35)
const int LDR_PIN = A1;  // pin A1 for the light sensor (LDR)

// Variables for sensor readings
float lm_value;          // Temperature sensor reading
float temp_celsius;      // Temperature in Celsius
int ldr_value;           // Light sensor reading (0-1023)
int ldr_percentage;      // Light level as percentage (0-100)

void setup() {
    Serial.begin(9600);             // Initialize serial communication at 9600 baud rate
    Serial.println("CLEARDATA");    // Clears any existing data
    Serial.println("LABEL,CLOCK,TEMPERATURE,LIGHT");  // Set column headers in Excel
}

void loop() {
    // Read and process temperature sensor
    lm_value = analogRead(LM_PIN);               // Read analog voltage from LM35
    temp_celsius = (lm_value / 1023.0) * 500.0;  // Convert analog value to Celsius
    
    // Read and process light sensor
    ldr_value = analogRead(LDR_PIN);                   // Read analog voltage from LDR
    ldr_percentage = map(ldr_value, 0, 1023, 0, 100);  // Convert raw value to percentage
    
    // Send data to serial in CSV format
    Serial.print("DATA,TIME,");     // 'TIME' will be automatically replaced by the current time in Excel logger
    Serial.print(temp_celsius);     // Print temperature value
    Serial.print(",");              // Using comma as separator instead of period
    Serial.println(ldr_percentage); // Print light level percentage
    
    delay(1500);  // Wait for 1.5 seconds before next reading
}