#!/usr/bin/env python
# -*- coding: utf-8 -*-
#
#  main.py
# prio :  ~nice -n -20 python LedDotDisplay.py
from threading import Timer

import time
import sys
import numpy as np
import serial

ser = serial.Serial()
ser.baudrate = 19200
ser.port = 'COM4'
ser.open()

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

    #rt = RepeatedTimer(0.0005, OperateLeds)  #0.00005  # 0.008 --> below 10ms --> 100Hz

    try:

        while (True) : 

            bToggle = not bToggle
            #GPIO.output(17, bToggle)

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

            OperateLeds()
            #userinput = input()                     

            time.sleep(0.1)

            #rt.interval = userinput

    except KeyboardInterrupt:
        print ('Clearing shift registers')


        print ('Stopping thread rt...')
        #rt.stop()

        print ('Release serial port')
        ser.close()

        print ('Bye...')


    return 0


def OperateLeds():
    
    OperateLeds.row = 0
    
    for x in range (8):
        if x == 8:
            break

        OperateLeds.greencol1firstbyte  = GreenLeds[OperateLeds.Image, OperateLeds.row, 0] | GreenLeds[OperateLeds.Image, OperateLeds.row, 1] << 1 | GreenLeds[OperateLeds.Image, OperateLeds.row, 2] << 2 | GreenLeds[OperateLeds.Image, OperateLeds.row, 3] << 3 | GreenLeds[OperateLeds.Image, OperateLeds.row, 4] << 4 | GreenLeds[OperateLeds.Image, OperateLeds.row, 5] << 5 | GreenLeds[OperateLeds.Image, OperateLeds.row, 6] << 6 | GreenLeds[OperateLeds.Image, OperateLeds.row, 7] << 7
        OperateLeds.greencol2secondbyte = GreenLeds[OperateLeds.Image, OperateLeds.row, 8] | GreenLeds[OperateLeds.Image, OperateLeds.row, 9] << 1 | GreenLeds[OperateLeds.Image, OperateLeds.row, 10] << 2 | GreenLeds[OperateLeds.Image, OperateLeds.row, 11] << 3 | GreenLeds[OperateLeds.Image, OperateLeds.row, 12] << 4 | GreenLeds[OperateLeds.Image, OperateLeds.row, 13] << 5 | GreenLeds[OperateLeds.Image, OperateLeds.row, 14] << 6 | GreenLeds[OperateLeds.Image, OperateLeds.row, 15] << 7
        OperateLeds.greencol31firstbyte = GreenLeds[OperateLeds.Image, OperateLeds.row + 8, 0] | GreenLeds[OperateLeds.Image, OperateLeds.row + 8, 1] << 1 | GreenLeds[OperateLeds.Image, OperateLeds.row + 8, 2] << 2 | GreenLeds[OperateLeds.Image, OperateLeds.row + 8, 3] << 3 | GreenLeds[OperateLeds.Image, OperateLeds.row + 8, 4] << 4 | GreenLeds[OperateLeds.Image, OperateLeds.row + 8, 5] << 5 | GreenLeds[OperateLeds.Image, OperateLeds.row + 8, 6] << 6 | GreenLeds[OperateLeds.Image, OperateLeds.row + 8, 7] << 7
        OperateLeds.greencol4secondbyte = GreenLeds[OperateLeds.Image, OperateLeds.row + 8, 8] | GreenLeds[OperateLeds.Image, OperateLeds.row + 8, 9] << 1 | GreenLeds[OperateLeds.Image, OperateLeds.row + 8, 10] << 2 | GreenLeds[OperateLeds.Image, OperateLeds.row + 8, 11] << 3 | GreenLeds[OperateLeds.Image, OperateLeds.row + 8, 12] << 4 | GreenLeds[OperateLeds.Image, OperateLeds.row + 8, 13] << 5 | GreenLeds[OperateLeds.Image, OperateLeds.row + 8, 14] << 6 | GreenLeds[OperateLeds.Image, OperateLeds.row + 8, 15] << 7

        OperateLeds.redcol1firstbyte  = 0xFF  #RedLeds[OperateLeds.row, 1]
        OperateLeds.redcol2secondbyte = 0xFF  #RedLeds[OperateLeds.row, 2]
        OperateLeds.redcol3firstbyte  = 0xFF  #RedLeds[OperateLeds.row, 3]
        OperateLeds.redcol4secondbyte = 0xFF  #edLeds[OperateLeds.row, 4]

        ser.write(OperateLeds.greencol1firstbyte)
        ser.write(OperateLeds.greencol2secondbyte)
        ser.write(OperateLeds.greencol31firstbyte)
        ser.write(OperateLeds.greencol4secondbyte)

        ser.write(OperateLeds.redcol1firstbyte )
        ser.write(OperateLeds.redcol2secondbyte)
        ser.write(OperateLeds.redcol3firstbyte )
        ser.write(OperateLeds.redcol4secondbyte)   
        
        print ('OperateLeds.row = ', OperateLeds.row)
        print (OperateLeds.greencol1firstbyte)
        print (OperateLeds.greencol2secondbyte)
        print (OperateLeds.greencol31firstbyte)
        print (OperateLeds.greencol4secondbyte)
        print (OperateLeds.redcol1firstbyte)
        print (OperateLeds.redcol2secondbyte)
        print (OperateLeds.redcol3firstbyte)
        print (OperateLeds.redcol4secondbyte)
        


        OperateLeds.row += 1



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

