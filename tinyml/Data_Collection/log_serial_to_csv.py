"""
log_serial_to_csv.py

Logs labeled sensor data streamed over serial from the ESP32 (in a
data-collection firmware build) into a CSV file compatible with the
tinyml/Dataset/<Label>/ schema.

Expected serial line format from the firmware (one line per sample):
    timestamp,accel_x,accel_y,accel_z,audio_sample

Usage:
    python log_serial_to_csv.py --port /dev/ttyUSB0 --baud 115200 \
        --label Healthy --duration 60 --out ../Dataset/Healthy/healthy_session01.csv
"""

import argparse
import csv
import time

import serial


def main():
    parser = argparse.ArgumentParser(description="Log ESP32 serial sensor data to CSV")
    parser.add_argument("--port", required=True, help="Serial port, e.g. /dev/ttyUSB0 or COM5")
    parser.add_argument("--baud", type=int, default=115200)
    parser.add_argument("--label", required=True, choices=["Healthy", "Warning", "Fault"])
    parser.add_argument("--duration", type=float, default=60.0, help="Recording duration in seconds")
    parser.add_argument("--out", required=True, help="Output CSV path")
    args = parser.parse_args()

    ser = serial.Serial(args.port, args.baud, timeout=1)
    print(f"Recording '{args.label}' for {args.duration}s from {args.port}...")

    start = time.time()
    rows_written = 0

    with open(args.out, "w", newline="") as f:
        writer = csv.writer(f)
        writer.writerow(["timestamp", "accel_x", "accel_y", "accel_z", "audio_sample", "label"])

        while time.time() - start < args.duration:
            line = ser.readline().decode("utf-8", errors="ignore").strip()
            if not line:
                continue
            parts = line.split(",")
            if len(parts) != 5:
                continue  # skip malformed / non-data lines (e.g. log messages)
            writer.writerow(parts + [args.label])
            rows_written += 1

    ser.close()
    print(f"Done. Wrote {rows_written} rows to {args.out}")


if __name__ == "__main__":
    main()
