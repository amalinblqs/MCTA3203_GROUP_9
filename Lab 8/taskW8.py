import serial
import matplotlib.pyplot as plt
import re
import time

# CONFIGURATION
port = 'COM4'  # Replace with your actual COM port
baud_rate = 9600
timeout = 2
duration = 30  # Duration in seconds to record data

# Connect to serial
try:
    ser = serial.Serial(port, baud_rate, timeout=timeout)
    print(f"Connected to {port} at {baud_rate} baud.")
except Exception as e:
    print(f"Connection failed: {e}")
    exit()

temperatures = []
timestamps = []

start_time = time.time()

print(f"\nCollecting data for {duration} seconds...\n")

try:
    while True:
        current_time = time.time()
        elapsed = current_time - start_time

        if elapsed > duration:
            print("Finished data collection.\n")
            break

        raw = ser.readline().decode('utf-8').strip()
        if raw:
            match = re.search(r"([-+]?\d*\.\d+|\d+)", raw)
            if match:
                temperature = float(match.group(1))
                temperatures.append(temperature)
                timestamps.append(elapsed)
                print(f"{elapsed:.1f}s -> {temperature:.2f} °C")
            else:
                print(f"Ignored: {raw}")
        else:
            print("No data received.")

finally:
    ser.close()
    if temperatures:
        plt.plot(timestamps, temperatures, marker='o', linestyle='-')
        plt.title("Temperature Over 30 Seconds")
        plt.xlabel("Time (s)")
        plt.ylabel("Temperature (°C)")
        plt.grid(True)
        plt.tight_layout()
        plt.show(block=True)
    else:
        print("No temperature data to plot.")
