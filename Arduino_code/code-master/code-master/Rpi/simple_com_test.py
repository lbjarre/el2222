import RPi.GPIO as GPIO
import arduinoCom

GPIO.setmode(GPIO.BCM)

arduino = arduinoCom.Arduino()

for _ in xrange(10):
    if arduino.connect() == 1:
        print 'Connection established'
        break
else:
    raise IOError('Could not connect to Arduino')
