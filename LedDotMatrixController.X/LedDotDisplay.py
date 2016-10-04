#!/usr/bin/env python
# -*- coding: utf-8 -*-
#
#  main.py
# prio :  ~nice -n -20 python LedDotDisplay.py
from threading import Timer

try:
    import RPi.GPIO as GPIO
except RuntimeError:
    print("Error importing RPi.GPIO!  This is probably because you need superuser privileges.  You can achieve this by using 'sudo' to run your script")

import time
import spidev
import sys
import numpy as np

GPIO.setmode(GPIO.BCM)#BCM)#BOARD)
GPIO.setup(17, GPIO.OUT)

spi = spidev.SpiDev()
spi.open(0, 0)
spi.max_speed_hz = 10000000
spi.mode = 0b00


GreenLeds =np.array([[[1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1],
                      [1,1,1,1,0,0,1,1,1,1,1,1,1,1,1,1],
                      [1,1,1,0,0,0,0,1,1,1,1,1,1,1,1,1],
                      [1,1,1,1,0,0,1,1,1,1,1,1,1,1,1,1],
                      [1,1,1,1,1,0,0,1,1,1,1,1,1,1,1,1],
                      [1,1,1,1,1,0,0,0,0,1,1,1,1,1,1,1],
                      [1,1,1,1,1,0,0,0,1,0,1,1,1,1,1,1],
                      [1,1,1,1,0,1,0,0,1,1,0,1,1,1,1,1],
                      [1,1,1,0,1,1,0,0,1,1,0,1,1,1,1,1],
                      [1,1,1,1,1,1,0,0,0,1,1,1,1,1,1,1],
                      [1,1,1,1,1,1,0,1,0,1,1,1,1,1,1,1],
                      [1,1,1,1,1,0,1,1,1,0,0,1,1,1,1,1],
                      [1,1,1,1,1,0,1,1,1,1,1,0,0,1,1,1],
                      [1,1,1,1,1,0,1,1,1,1,1,1,0,1,1,1],
                      [1,1,1,0,0,1,1,1,1,1,1,0,1,1,1,1],
                      [1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1]],
                      
                     [[1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1],
                      [1,1,1,1,1,0,0,1,1,1,1,1,1,1,1,1],
                      [1,1,1,1,0,0,0,0,1,1,1,1,1,1,1,1],
                      [1,1,1,1,1,0,0,1,1,1,1,1,1,1,1,1],
                      [1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,1],
                      [1,1,1,1,1,1,0,0,0,1,1,1,1,1,1,1],
                      [1,1,1,1,1,1,0,0,1,0,1,1,1,1,1,1],
                      [1,1,1,1,1,0,0,0,0,1,0,1,1,1,1,1],
                      [1,1,1,1,0,1,1,0,0,1,0,1,1,1,1,1],
                      [1,1,1,1,1,1,1,0,0,0,1,1,1,1,1,1],
                      [1,1,1,1,1,1,1,0,1,0,1,1,1,1,1,1],
                      [1,1,1,1,1,1,0,1,1,1,0,1,1,1,1,1],
                      [1,1,1,1,1,0,1,1,1,1,1,0,1,1,1,1],
                      [1,1,1,1,1,1,0,0,1,1,1,1,0,1,1,1],
                      [1,1,1,1,1,1,1,0,1,1,1,0,0,1,1,1],
                      [1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,1]],
                      
                     [[1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1],
                      [1,1,1,1,1,0,0,1,1,1,1,1,1,1,1,1],
                      [1,1,1,1,0,0,0,0,1,1,1,1,1,1,1,1],
                      [1,1,1,1,1,0,0,1,1,1,1,1,1,1,1,1],
                      [1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,1],
                      [1,1,1,1,1,1,0,0,0,1,1,1,1,1,1,1],
                      [1,1,1,1,1,1,0,0,1,0,1,1,1,1,1,1],
                      [1,1,1,1,1,0,0,0,0,1,0,1,1,1,1,1],
                      [1,1,1,1,0,1,1,0,0,1,0,1,1,1,1,1],
                      [1,1,1,1,1,1,1,0,0,0,1,1,1,1,1,1],
                      [1,1,1,1,1,1,1,0,1,0,1,1,1,1,1,1],
                      [1,1,1,1,1,1,0,1,1,0,1,1,1,1,1,1],
                      [1,1,1,1,1,0,1,1,1,1,0,0,1,1,1,1],
                      [1,1,1,1,1,1,0,0,1,1,1,0,1,1,1,1],
                      [1,1,1,1,1,1,1,1,0,1,0,0,1,1,1,1],
                      [1,1,1,1,1,1,0,0,0,1,1,1,1,1,1,1]],
                      
                     [[1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1],
                      [1,1,1,1,1,0,0,1,1,1,1,1,1,1,1,1],
                      [1,1,1,1,0,0,0,0,1,1,1,1,1,1,1,1],
                      [1,1,1,1,1,0,0,1,1,1,1,1,1,1,1,1],
                      [1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,1],
                      [1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,1],
                      [1,1,1,1,1,1,0,0,0,1,1,1,1,1,1,1],
                      [1,1,1,1,1,1,0,0,1,0,1,1,1,1,1,1],
                      [1,1,1,1,1,1,1,0,0,0,1,1,1,1,1,1],
                      [1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1],
                      [1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1],
                      [1,1,1,1,1,1,0,1,0,1,1,1,1,1,1,1],
                      [1,1,1,1,1,1,0,1,1,0,1,1,1,1,1,1],
                      [1,1,1,1,1,1,1,0,1,1,0,1,1,1,1,1],
                      [1,1,1,1,1,1,1,1,0,1,0,1,1,1,1,1],
                      [1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1]],
                      
                     [[1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1],
                      [1,1,1,1,1,0,0,1,1,1,1,1,1,1,1,1],
                      [1,1,1,1,0,0,0,0,1,1,1,1,1,1,1,1],
                      [1,1,1,1,1,0,0,1,1,1,1,1,1,1,1,1],
                      [1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,1],
                      [1,1,1,1,1,1,0,0,0,1,1,1,1,1,1,1],
                      [1,1,1,1,1,1,0,0,0,1,1,1,1,1,1,1],
                      [1,1,1,1,1,1,0,0,0,1,1,1,1,1,1,1],
                      [1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1],
                      [1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1],
                      [1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1],
                      [1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1],
                      [1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1],
                      [1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1],
                      [1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1],
                      [1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1]],
                      
                     [[1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1],
                      [1,1,1,1,1,0,0,1,1,1,1,1,1,1,1,1],
                      [1,1,1,1,0,0,0,0,1,1,1,1,1,1,1,1],
                      [1,1,1,1,1,0,0,1,1,1,1,1,1,1,1,1],
                      [1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,1],
                      [1,1,1,1,1,1,0,0,0,1,1,1,1,1,1,1],
                      [1,1,1,1,1,1,0,0,1,0,1,1,1,1,1,1],
                      [1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1],
                      [1,1,1,1,1,1,1,0,0,0,1,1,1,1,1,1],
                      [1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1],
                      [1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1],
                      [1,1,1,1,1,1,0,0,0,1,1,1,1,1,1,1],
                      [1,1,1,1,1,1,0,1,1,0,1,1,1,1,1,1],
                      [1,1,1,1,1,1,1,0,1,1,0,1,1,1,1,1],
                      [1,1,1,1,1,0,0,0,1,1,1,0,1,1,1,1],
                      [1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1]],
                      
                     [[1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1],
                      [1,1,1,1,0,0,1,1,1,1,1,1,1,1,1,1],
                      [1,1,1,0,0,0,0,1,1,1,1,1,1,1,1,1],
                      [1,1,1,1,0,0,1,1,1,1,1,1,1,1,1,1],
                      [1,1,1,1,1,0,0,1,1,1,1,1,1,1,1,1],
                      [1,1,1,1,1,0,0,0,1,1,1,1,1,1,1,1],
                      [1,1,1,1,1,0,0,0,0,1,1,1,1,1,1,1],
                      [1,1,1,1,1,0,0,0,1,0,1,1,1,1,1,1],
                      [1,1,1,1,1,1,0,0,1,0,1,1,1,1,1,1],
                      [1,1,1,1,1,1,0,0,0,1,1,1,1,1,1,1],
                      [1,1,1,1,1,1,0,1,0,1,1,1,1,1,1,1],
                      [1,1,1,1,1,0,1,1,1,0,1,1,1,1,1,1],
                      [1,1,1,1,1,0,1,1,1,1,0,1,1,1,1,1],
                      [1,1,1,0,0,0,1,1,1,1,1,0,0,1,1,1],
                      [1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1],
                      [1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1]],
                      
                     [[1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1],
                      [1,1,1,1,0,0,1,1,1,1,1,1,1,1,1,1],
                      [1,1,1,0,0,0,0,1,1,1,1,1,1,1,1,1],
                      [1,1,1,1,0,0,1,1,1,1,1,1,1,1,1,1],
                      [1,1,1,1,1,0,0,1,1,1,1,1,1,1,1,1],
                      [1,1,1,1,1,0,0,0,0,1,1,1,1,1,1,1],
                      [1,1,1,1,1,0,0,0,1,0,1,1,1,1,1,1],
                      [1,1,1,1,0,1,0,0,1,1,0,1,1,1,1,1],
                      [1,1,1,0,1,1,0,0,1,1,0,1,1,1,1,1],
                      [1,1,1,1,1,1,0,0,0,1,1,1,1,1,1,1],
                      [1,1,1,1,1,1,0,1,0,1,1,1,1,1,1,1],
                      [1,1,1,1,1,0,1,1,1,0,0,0,1,1,1,1],
                      [1,1,1,1,1,0,1,1,1,1,1,1,0,1,1,1],
                      [1,1,1,1,1,0,1,1,1,1,1,0,0,1,1,1],
                      [1,1,1,0,0,1,1,1,1,1,1,1,1,1,1,1],
                      [1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1]],
                      
                     [[1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1],
                      [1,1,1,1,1,0,0,1,1,1,1,1,1,1,1,1],
                      [1,1,1,1,0,0,0,0,1,1,1,1,1,1,1,1],
                      [1,1,1,1,1,0,0,1,1,1,1,1,1,1,1,1],
                      [1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,1],
                      [1,1,1,1,1,1,0,0,0,1,1,1,1,1,1,1],
                      [1,1,1,1,1,1,0,0,1,0,1,1,1,1,1,1],
                      [1,1,1,1,1,0,0,0,0,1,0,1,1,1,1,1],
                      [1,1,1,1,0,1,1,0,0,1,0,1,1,1,1,1],
                      [1,1,1,1,1,1,1,0,0,0,1,1,1,1,1,1],
                      [1,1,1,1,1,1,1,0,1,0,1,1,1,1,1,1],
                      [1,1,1,1,1,1,0,1,1,0,1,1,1,1,1,1],
                      [1,1,1,1,1,0,1,1,1,1,0,0,1,1,1,1],
                      [1,1,1,1,1,1,0,0,1,1,1,0,1,1,1,1],
                      [1,1,1,1,1,1,1,1,0,1,0,0,1,1,1,1],
                      [1,1,1,1,1,1,0,0,0,1,1,1,1,1,1,1]],
                      
                     [[1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1],
                      [1,1,1,1,1,0,0,1,1,1,1,1,1,1,1,1],
                      [1,1,1,1,0,0,0,0,1,1,1,1,1,1,1,1],
                      [1,1,1,1,1,0,0,1,1,1,1,1,1,1,1,1],
                      [1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,1],
                      [1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,1],
                      [1,1,1,1,1,1,0,0,0,1,1,1,1,1,1,1],
                      [1,1,1,1,1,1,0,0,1,0,1,1,1,1,1,1],
                      [1,1,1,1,1,1,1,0,0,0,1,1,1,1,1,1],
                      [1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1],
                      [1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1],
                      [1,1,1,1,1,1,0,1,0,1,1,1,1,1,1,1],
                      [1,1,1,1,1,1,0,1,1,0,1,1,1,1,1,1],
                      [1,1,1,1,1,1,1,0,1,1,0,1,1,1,1,1],
                      [1,1,1,1,1,1,1,1,0,1,0,1,1,1,1,1],
                      [1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1]],
                      
                     [[1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1],
                      [1,1,1,1,1,0,0,1,1,1,1,1,1,1,1,1],
                      [1,1,1,1,0,0,0,0,1,1,1,1,1,1,1,1],
                      [1,1,1,1,1,0,0,1,1,1,1,1,1,1,1,1],
                      [1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,1],
                      [1,1,1,1,1,1,0,0,0,1,1,1,1,1,1,1],
                      [1,1,1,1,1,1,0,0,0,1,1,1,1,1,1,1],
                      [1,1,1,1,1,1,0,0,0,1,1,1,1,1,1,1],
                      [1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1],
                      [1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1],
                      [1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1],
                      [1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1],
                      [1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1],
                      [1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1],
                      [1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1],
                      [1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1]],
                      
                     [[1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1],
                      [1,1,1,1,1,0,0,1,1,1,1,1,1,1,1,1],
                      [1,1,1,1,0,0,0,0,1,1,1,1,1,1,1,1],
                      [1,1,1,1,1,0,0,1,1,1,1,1,1,1,1,1],
                      [1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,1],
                      [1,1,1,1,1,1,0,0,0,1,1,1,1,1,1,1],
                      [1,1,1,1,1,1,0,0,1,0,1,1,1,1,1,1],
                      [1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1],
                      [1,1,1,1,1,1,1,0,0,0,1,1,1,1,1,1],
                      [1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1],
                      [1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1],
                      [1,1,1,1,1,1,0,0,0,1,1,1,1,1,1,1],
                      [1,1,1,1,1,1,0,1,1,0,1,1,1,1,1,1],
                      [1,1,1,1,1,1,1,0,1,1,0,1,1,1,1,1],
                      [1,1,1,1,1,0,0,0,1,1,1,0,1,1,1,1],
                      [1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1]],
                      
                     [[1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1],
                      [1,1,1,1,0,0,1,1,1,1,1,1,1,1,1,1],
                      [1,1,1,0,0,0,0,1,1,1,1,1,1,1,1,1],
                      [1,1,1,1,0,0,1,1,1,1,1,1,1,1,1,1],
                      [1,1,1,1,1,0,0,1,1,1,1,1,1,1,1,1],
                      [1,1,1,1,1,0,0,0,0,1,1,1,1,1,1,1],
                      [1,1,1,1,1,0,0,0,1,0,1,1,1,1,1,1],
                      [1,1,1,1,0,1,0,0,1,1,0,1,1,1,1,1],
                      [1,1,1,0,1,1,0,0,1,1,0,1,1,1,1,1],
                      [1,1,1,1,1,1,0,0,0,1,1,1,1,1,1,1],
                      [1,1,1,1,1,1,0,1,0,1,1,1,1,1,1,1],
                      [1,1,1,1,1,0,1,1,1,0,0,0,1,1,1,1],
                      [1,1,1,1,1,0,1,1,1,1,1,1,0,1,1,1],
                      [1,1,1,1,1,0,1,1,1,1,1,0,0,1,1,1],
                      [1,1,1,0,0,1,1,1,1,1,1,1,1,1,1,1],
                      [1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1]]])


''' Sequence is 1, 2, 3, 4, 5, 6, 7, 8, 3, 4, 5, 6, 8, --> 1    '''


RedLeds   = np.array([[0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0],
                      [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0],
                      [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0],
                      [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0],
                      [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0],
                      [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0],
                      [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0],
                      [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0],
                      [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0],
                      [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0],
                      [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0],
                      [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0],
                      [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0],
                      [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0],
                      [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0],
                      [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0]])


def main(): 
        
    print ('Blink the LED'"'"'S!')


    bToggle = False
    
    count = 0
    
    rt = RepeatedTimer(0.0005, OperateLeds)  #0.00005  # 0.008 --> below 10ms --> 100Hz
    
    try:
        
        while (True) : 

            bToggle = not bToggle
            GPIO.output(17, bToggle)
            
            OperateLeds.Count += 1
            
            if (OperateLeds.Count == 8):
                OperateLeds.Count = 0
                
            if (OperateLeds.Count == 0):
                OperateLeds.Image = 0
            elif (OperateLeds.Count == 1):
                OperateLeds.Image = 1
            elif (OperateLeds.Count == 2):
                OperateLeds.Image = 2
            elif (OperateLeds.Count == 3):
                OperateLeds.Image = 3
            elif (OperateLeds.Count == 4):
                OperateLeds.Image = 4
            elif (OperateLeds.Count == 5):
                OperateLeds.Image = 5
            elif (OperateLeds.Count == 6):
                OperateLeds.Image = 6
            elif (OperateLeds.Count == 7):
                OperateLeds.Image = 7
            elif (OperateLeds.Count == 8):
                OperateLeds.Image = 8
            elif (OperateLeds.Count == 9):
                OperateLeds.Image = 3
            elif (OperateLeds.Count == 10):
                OperateLeds.Image = 4
            elif (OperateLeds.Count == 11):
                OperateLeds.Image = 5
            elif (OperateLeds.Count == 12):
                OperateLeds.Image = 6
            elif (OperateLeds.Count == 13):
                OperateLeds.Image = 8
            
            
            #userinput = input()                     
            
            time.sleep(0.1)
            
            #rt.interval = userinput
    
    except KeyboardInterrupt:
        print ('Clearing shift registers')
        resp = spi.xfer2([0xFF, 0xF, 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF  ]) 
        
        print ('Stopping thread rt...')
        rt.stop()
        
        print ('Clean up GPIO!')
        GPIO.cleanup()
        
        print ('Close SPI!')
        spi.close()
        
        print ('Bye...')
            
    
    return 0
    
    
def OperateLeds():    
    #sys.stderr.write("\x1b[2J\x1b[H")                           # Clear the terminal        
    
    if OperateLeds.row == 0:
        OperateLeds.rowfirstbyte  = ~0x01
        OperateLeds.rowsecondbyte = ~0x01    
    
    elif OperateLeds.row == 1:
        OperateLeds.rowfirstbyte  = ~0x02
        OperateLeds.rowsecondbyte = ~0x02

    elif OperateLeds.row == 2:
        OperateLeds.rowfirstbyte  = ~0x04
        OperateLeds.rowsecondbyte = ~0x04
            
    elif OperateLeds.row == 3:
        OperateLeds.rowfirstbyte  = ~0x08
        OperateLeds.rowsecondbyte = ~0x08
            
    elif OperateLeds.row == 4:
        OperateLeds.rowfirstbyte  = ~0x10
        OperateLeds.rowsecondbyte = ~0x10
        
    elif OperateLeds.row == 5:
        OperateLeds.rowfirstbyte  = ~0x20
        OperateLeds.rowsecondbyte = ~0x20
            
    elif OperateLeds.row == 6:
        OperateLeds.rowfirstbyte  = ~0x40
        OperateLeds.rowsecondbyte = ~0x40
            
    elif OperateLeds.row == 7:
        OperateLeds.rowfirstbyte  = ~0x80
        OperateLeds.rowsecondbyte = ~0x80  
            
    
    OperateLeds.greencol1firstbyte  = GreenLeds[OperateLeds.Image, OperateLeds.row, 0] | GreenLeds[OperateLeds.Image, OperateLeds.row, 1] << 1 | GreenLeds[OperateLeds.Image, OperateLeds.row, 2] << 2 | GreenLeds[OperateLeds.Image, OperateLeds.row, 3] << 3 | GreenLeds[OperateLeds.Image, OperateLeds.row, 4] << 4 | GreenLeds[OperateLeds.Image, OperateLeds.row, 5] << 5 | GreenLeds[OperateLeds.Image, OperateLeds.row, 6] << 6 | GreenLeds[OperateLeds.Image, OperateLeds.row, 7] << 7
    OperateLeds.greencol2secondbyte = GreenLeds[OperateLeds.Image, OperateLeds.row, 8] | GreenLeds[OperateLeds.Image, OperateLeds.row, 9] << 1 | GreenLeds[OperateLeds.Image, OperateLeds.row, 10] << 2 | GreenLeds[OperateLeds.Image, OperateLeds.row, 11] << 3 | GreenLeds[OperateLeds.Image, OperateLeds.row, 12] << 4 | GreenLeds[OperateLeds.Image, OperateLeds.row, 13] << 5 | GreenLeds[OperateLeds.Image, OperateLeds.row, 14] << 6 | GreenLeds[OperateLeds.Image, OperateLeds.row, 15] << 7
    OperateLeds.greencol31firstbyte = GreenLeds[OperateLeds.Image, OperateLeds.row + 8, 0] | GreenLeds[OperateLeds.Image, OperateLeds.row + 8, 1] << 1 | GreenLeds[OperateLeds.Image, OperateLeds.row + 8, 2] << 2 | GreenLeds[OperateLeds.Image, OperateLeds.row + 8, 3] << 3 | GreenLeds[OperateLeds.Image, OperateLeds.row + 8, 4] << 4 | GreenLeds[OperateLeds.Image, OperateLeds.row + 8, 5] << 5 | GreenLeds[OperateLeds.Image, OperateLeds.row + 8, 6] << 6 | GreenLeds[OperateLeds.Image, OperateLeds.row + 8, 7] << 7
    OperateLeds.greencol4secondbyte = GreenLeds[OperateLeds.Image, OperateLeds.row + 8, 8] | GreenLeds[OperateLeds.Image, OperateLeds.row + 8, 9] << 1 | GreenLeds[OperateLeds.Image, OperateLeds.row + 8, 10] << 2 | GreenLeds[OperateLeds.Image, OperateLeds.row + 8, 11] << 3 | GreenLeds[OperateLeds.Image, OperateLeds.row + 8, 12] << 4 | GreenLeds[OperateLeds.Image, OperateLeds.row + 8, 13] << 5 | GreenLeds[OperateLeds.Image, OperateLeds.row + 8, 14] << 6 | GreenLeds[OperateLeds.Image, OperateLeds.row + 8, 15] << 7
    
    
    
    OperateLeds.redcol1firstbyte  = 0xFF  #RedLeds[OperateLeds.row, 1]
    OperateLeds.redcol2secondbyte = 0xFF  #RedLeds[OperateLeds.row, 2]
    OperateLeds.redcol3firstbyte  = 0xFF  #RedLeds[OperateLeds.row, 3]
    OperateLeds.redcol4secondbyte = 0xFF  #edLeds[OperateLeds.row, 4]
    
    


    resp = spi.xfer2([OperateLeds.greencol4secondbyte, OperateLeds.greencol31firstbyte, OperateLeds.greencol2secondbyte, OperateLeds.greencol1firstbyte, 
                      OperateLeds.redcol4secondbyte, OperateLeds.redcol3firstbyte, OperateLeds.redcol2secondbyte, OperateLeds.redcol1firstbyte, 
                      OperateLeds.rowsecondbyte, OperateLeds.rowfirstbyte]) #OperateLeds.cOutput >> 8, OperateLeds.cOutput])  ~OperateLeds.cOutput
    #print(resp)
    #print(OperateLeds.row)
    
    OperateLeds.row += 1
    if OperateLeds.row == 8:
        OperateLeds.row = 0
        
    
    
    
# Initialize OperateLeds() local static variables
OperateLeds.Count = 0
OperateLeds.Image = 0
OperateLeds.row = 0
OperateLeds.rowfirstbyte = ~0x00
OperateLeds.rowsecondbyte = ~0x00

OperateLeds.greencol1firstbyte = ~0x00
OperateLeds.greencol2secondbyte = ~0x00
OperateLeds.greencol31firstbyte = ~0x00
OperateLeds.greencol4secondbyte = ~0x00

OperateLeds.redcol1firstbyte = ~0x00
OperateLeds.redcol2secondbyte = ~0x00
OperateLeds.redcol3firstbyte = ~0x00
OperateLeds.redcol4secondbyte = ~0x00


class RepeatedTimer(object):
    def __init__(self, interval, function, *args, **kwargs):
        self.timer      = None
        self.interval   = interval
        self.function   = function
        self.args       = args
        self.kwargs     = kwargs
        self.is_running = False
        self.start()
        
    def _run(self):
        self.is_running = False
        self.start()
        self.function(*self.args, **self.kwargs)
        
    def start(self):
        if not self.is_running:
            self._timer = Timer(self.interval, self._run)
            self._timer.start()
            self.is_running = True
            
    def stop(self):
        self._timer.cancel()
        self.is_running = False

if __name__ == '__main__': main()

