import serial

ser = serial.Serial('/dev/ttyUSB0')
ser.baudrate = 9600
ser.write(b'hello')