import serial
import time

arduino = serial.Serial(port='COM4', baudrate=115200, timeout=.1)

for i in range(3,111):
    arduino.write(open(f'{i}.bmp', 'rb').read())
    print(i)