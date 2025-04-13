import serial
import time

# Connect to Arduino on correct COM port (change COM4 if needed)
arduino = serial.Serial('COM4', 9600, timeout=1)
time.sleep(2)  # Give some time for the connection to establish

# Simulated card ID (not in authorized list)
simulated_card_id = "FAKE12345"
authorized_cards = ["1234567890", "ABCDEFG"]  # Example authorized IDs

if simulated_card_id in authorized_cards:
    print("Access granted. Sending 'A' to Arduino.")
    arduino.write(b'A')
else:
    print("Access denied. Sending 'D' to Arduino.")
    arduino.write(b'D')
