"""
Key Takeaways

The arduino reads in a single byte at a time. This is worth considering for 
what I want the codes to be because converting from multiple bytes to an int
does not sound pleasant. Changing the codes to be from 0 - 255 may be the most 
expedient solution.
"""

import serial
import time

arduino = serial.Serial("/dev/ttyACM0", 2000000)

phrase = "hello owo"
newPhrase = ""
"""arduino.write(phrase.encode())
print(arduino.readline())

for i in phrase:
	newPhrase += arduino.readline().decode("utf-8")

print(newPhrase)"""

while True:
	arduino.write(chr(100).encode())
	time.sleep(1)
	arduino.write(chr(0).encode())
	time.sleep(1)