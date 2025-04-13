import serial
import time

# Open serial port
arduino = serial.Serial('COM4', 9600, timeout=2)
time.sleep(2)  # Give Arduino time to boot

# Clear any buffered input
arduino.reset_input_buffer()

# Wait for "READY" message
while True:
    line = arduino.readline().decode('utf-8').strip()
    if line:
        print("Arduino says:", line)
    if "READY" in line:
        break

# Send command
command = 'D'  # Change to 'A' to test other case
arduino.write(command.encode())  # Send 'A' or 'D'
print("Sent command:", command)

# Wait and read response
time.sleep(2)
while arduino.in_waiting:
    response = arduino.readline().decode().strip()
    print("Arduino responded:", response)

arduino.close()
