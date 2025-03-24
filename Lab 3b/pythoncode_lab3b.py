import serial
import time

# Define the serial port and baud rate (Check the correct COM port in Device Manager)
SERIAL_PORT = "COM8"  # Change this to your actual port (e.g., "COM3" on Windows or "/dev/ttyUSB0" on Linux/Mac)
BAUD_RATE = 9600

try:
    # Establish connection
    arduino = serial.Serial(SERIAL_PORT, BAUD_RATE, timeout=1)
    time.sleep(2)  # Wait for the connection to establish
    arduino.flush()  # Clear any junk data in the buffer
    print("Connected to Arduino!")

    while True:
        # Read data from Arduino
        if arduino.in_waiting > 0:
            raw_data = arduino.readline()
            try:
                data = raw_data.decode(errors="ignore").strip()  # Handle decoding errors
                print(f"Arduino says: {data}")
            except UnicodeDecodeError as e:
                print(f"Decoding error: {e}. Raw data: {raw_data}")  # Debugging info

        # Get user input for servo angle
        angle = input("Enter servo angle (0-180) or 'q' to quit: ")
        if angle.lower() == "q":
            break  # Exit loop if user enters 'q'

        # Send angle to Arduino
        if angle.isdigit():
            angle = int(angle)
            if 0 <= angle <= 180:
                arduino.write(f"{angle}\n".encode())  # Send valid angle
            else:
                print("Invalid range! Enter a number between 0 and 180.")
        else:
            print("Invalid input! Please enter a number between 0 and 180.")

except serial.SerialException:
    print("Error: Could not connect to Arduino. Check the port and try again.")

except KeyboardInterrupt:
    print("\nProgram terminated by user.")

finally:
    if 'arduino' in locals():
        arduino.close()
        print("Serial connection closed.")

