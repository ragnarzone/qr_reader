import serial
import time

port = serial.Serial("/dev/ttyS0", baudrate = 115200, timeout = 2)

port.write(b"test data")

time.sleep(1)

rcv = port.read(9)
print(rcv)