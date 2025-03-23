pip install pyserial

import serial
ser = serial.Serial('COM7', 9600)  # Replace 'COMX' with your actual port

try:
    while True:
        brightness = ser.readline().decode().strip()
        print("LED Brightness:", brightness)
except KeyboardInterrupt:
    print("\nSerial connection closed.")
    ser.close()
