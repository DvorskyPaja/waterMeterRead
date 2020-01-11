#!/usr/bin/python3

import datetime
import RPi.GPIO as GPIO
import time
import shutil
from picamera import PiCamera

LedPin = 13

def setup():
	GPIO.setmode(GPIO.BOARD)       # Numbers GPIOs by physical location
	GPIO.setup(LedPin, GPIO.OUT)   # Set LedPin's mode is output
	GPIO.output(LedPin, GPIO.LOW)  # Set LedPin high(+3.3V) to off led

def generateName():
	now = datetime.datetime.now()
	imageName = str(now.year) + "_" + str(now.month) + "_" + str(now.day) + "_" + str(now.hour) + "_" + str(now.minute) + "_" + str(now.second) \
        + ".jpg"
	print (imageName)
	return imageName

def capturePicture(fileName):
	camera.start_preview()
	time.sleep(5)

	fullPath = '/home/pi/Desktop/' + fileName
	camera.capture(fullPath)
	targetPath = "/home/pi/Pictures/water.jpg"
	#shutil.move(fullPath, targetPath)
        shutil.copy(fullPath, targetPath)

def sequence():
	print ('...led on')
	GPIO.output(LedPin, GPIO.HIGH)  # led on
	capturePicture(generateName())
	print ('...led off')
	GPIO.output(LedPin, GPIO.LOW)  # led off
	time.sleep(3.0)

setup()
camera = PiCamera()
camera.start_preview()
time.sleep(5)
#for loop fo r
for i in range(1):
	sequence()
