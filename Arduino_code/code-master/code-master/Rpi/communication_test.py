#!/usr/bin/env python
import sys
import RPi.GPIO as GPIO
import serial
import time
from collections import Counter
import math
import arduinoCom
import os
from collect_frames import *

#Variable to enable or disable code on Pi, this variable can be triggered from switch later.
Run = True
#Pin configuration type BCM
GPIO.setmode(GPIO.BCM)

#Close Serial Connections to Raspberry Pi
def Close_connection():
    GPIO.cleanup()
    robot.closeSerial()
    sys.exit('Empty Sear Found - Task finished')

#Create an Arduino Object which has base code for communication between Pi and Arduino
arduino = arduinoCom.Arduino()

time.sleep(2)

#Try connecting to Ardunio from any of the USB ports
for i in range (10):
    if arduino.connect() == 1:
        print 'connection established'
        break
    else:
        print 'Connection failed'

#Sample code for using the set get protocol
x_o = 0;
r_o = 0;

while True:
    pos = capture_circle()

    #Set original values, or find changes in circle position or radius.
    if x_o == 0:
        x_o = pos[0]
    else:
        x_new = pos[0]
        
    if r_o == 0:
        r_o = pos[2]
    else:
        r_new = pos[2]

    delta_x = x_o - x_new
    delta_r  = r_o - r_new
    
    if delta_x > 0:
        angular_velocity = -5
    else:
        angular_velocity =  5

    if delta_r > 0:
        linear_velocity =  5
    else:
        linear_velocity = -5

    #Send the movement signals to the arduino
    arduino.set_value(linear_velocity, angular_velocity)
    time.sleep(0.1)
