#!/usr/bin/env python3
import serial
import time

ser = serial.Serial('/dev/ttyUSB0', 115200)

print(ser)

ser.write('LON\r'.encode())

time.sleep(5)

x = ser.readline()
print(x)