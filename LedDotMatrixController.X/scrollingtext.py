#!/usr/bin/env python
# -*- coding: utf-8 -*-
#
#  main.py
# prio :  ~nice -n -20 python LedDotDisplay.py
from threading import Timer
from random import randint

import time
import sys
import numpy as np
import serial
from operator import xor

DEBUG = False
On = True
Off = False

ser = serial.Serial()
ser.baudrate = 250000
ser.port = 'COM4'
ser.open()

GreenLeds =np.array( [[1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1],
                      [1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1],
                      [1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1],
                      [1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1],
                      [1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1],
                      [1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1],
                      [1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1],
                      [1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1],
                      [1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1],
                      [1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1],
                      [1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1],
                      [1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1],
                      [1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1],
                      [1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1],
                      [1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1],
                      [1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1]])

RedLeds =  np.array( [[1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1],
                      [1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1],
                      [1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1],
                      [1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1],
                      [1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1],
                      [1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1],
                      [1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1],
                      [1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1],
                      [1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1],
                      [1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1],
                      [1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1],
                      [1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1],
                      [1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1],
                      [1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1],
                      [1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1],
                      [1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1]])

green = 1
red = 1
orange = 0 
black = 1

StopProgram = 0

def main(): 
    
    print ('Blink the LED'"'"'S!')

  
    
    rt = RepeatedTimer(0.050, OperateLeds)  #0.00005  # 0.008 --> below 10ms --> 100Hz
    
    UserIn = RepeatedTimer(1, ReadUser)
    
    try:        

        while (True) : 
            
                       
            '''
            for x in range (0, 16):
                SetLed(0,x,On,'green')
                               
                SetLed(0,x-1,Off,'green')
                              
                time.sleep(0.03)
            
            y = 15
            for x in range (0, 16):
                
                SetLed(0,y,On,'green')
                               
                SetLed(0,y+1,Off,'green')
                
                y -= 1
                              
                time.sleep(0.03)            

           '''
            
            
  
       

            
            if (green):
                SetLed(randint(0,16) ,randint(0,16) , randint(0,1),'green', True)
                
            if (red):
                SetLed(randint(0,16) ,randint(0,16) , randint(0,1),'red', True)
                
            if (orange):
                SetLed(randint(0,16) ,randint(0,16) , randint(0,1),'orange', True)
                
            if (black):
                SetLed(randint(0,16) ,randint(0,16) , 0,'orange', True)
                
            if (StopProgram == True):
                print ('Stopping thread rt and ReadUser...')
                rt.stop()
                UserIn.stop()
                time.sleep(0.1) 
        
                print ('Set Dot matrix display to default routine...')
                for x in range (0, 16):
                    ser.write(bytes( [0x5]))
        
                print ('Release serial port')
                ser.close()
        
                print ('Bye...')   
                exit()
  
            time.sleep(0.01) 
           

            #rt.interval = userinput

    except KeyboardInterrupt:
        
        print ('Stopping thread rt and ReadUser...')
        rt.stop()
        UserIn.stop()
        time.sleep(0.1) 

        print ('Set Dot matrix display to default routine...')
        for x in range (0, 16):
            ser.write(bytes( [0x5]))

        print ('Release serial port')
        ser.close()

        print ('Bye...')

    ser.close()
    return 0



def SetLed(row, col, value, color, unique):
    
    if (row < 16 and col < 16 and row > -1 and col > -1):
        if (color == 'green'):
            if (unique):
                if (RedLeds[row, col] == 0):
                    RedLeds[row, col] = 1
                GreenLeds[row, col] = value
            else:
                GreenLeds[row, col] = not value
            
        if (color == 'red'):
            if (unique):
                if (GreenLeds[row, col] == 0):
                    GreenLeds[row, col] = 1                
                RedLeds[row, col] = not value
            else:
                RedLeds[row, col] = not value
    
        if (color == 'orange'):
            GreenLeds[row, col] = not value
            RedLeds[row, col] = not value
    

def ReadUser():
    userinput = input()
    
    global green
    global red
    global orange
    global black
    global StopProgram
    
    if (userinput == '0'):
        StopProgram = True        
    if (userinput == '1'):
        green = not green
    if (userinput == '2'):
        red = not red
    if (userinput == '3'):
        orange = not orange  
    if (userinput == '4'):
        black = not black
    
    userinput = 0


def OperateLeds():

    OperateLeds.row = 0

    ser.write(bytes( [0xA]))

    for x in range (8):
        if x == 8:
            break

        OperateLeds.greencol1byte = GreenLeds[ OperateLeds.row, 0] | GreenLeds[ OperateLeds.row, 1] << 1 | GreenLeds[ OperateLeds.row, 2] << 2 | GreenLeds[ OperateLeds.row, 3] << 3 | GreenLeds[ OperateLeds.row, 4] << 4 | GreenLeds[ OperateLeds.row, 5] << 5 | GreenLeds[ OperateLeds.row, 6] << 6 | GreenLeds[ OperateLeds.row, 7] << 7
        OperateLeds.greencol2byte = GreenLeds[ OperateLeds.row, 8] | GreenLeds[ OperateLeds.row, 9] << 1 | GreenLeds[ OperateLeds.row, 10] << 2 | GreenLeds[ OperateLeds.row, 11] << 3 | GreenLeds[ OperateLeds.row, 12] << 4 | GreenLeds[ OperateLeds.row, 13] << 5 | GreenLeds[ OperateLeds.row, 14] << 6 | GreenLeds[ OperateLeds.row, 15] << 7
        OperateLeds.greencol3byte = GreenLeds[ OperateLeds.row + 8, 0] | GreenLeds[ OperateLeds.row + 8, 1] << 1 | GreenLeds[ OperateLeds.row + 8, 2] << 2 | GreenLeds[ OperateLeds.row + 8, 3] << 3 | GreenLeds[ OperateLeds.row + 8, 4] << 4 | GreenLeds[ OperateLeds.row + 8, 5] << 5 | GreenLeds[ OperateLeds.row + 8, 6] << 6 | GreenLeds[ OperateLeds.row + 8, 7] << 7
        OperateLeds.greencol4byte = GreenLeds[ OperateLeds.row + 8, 8] | GreenLeds[ OperateLeds.row + 8, 9] << 1 | GreenLeds[ OperateLeds.row + 8, 10] << 2 | GreenLeds[ OperateLeds.row + 8, 11] << 3 | GreenLeds[ OperateLeds.row + 8, 12] << 4 | GreenLeds[ OperateLeds.row + 8, 13] << 5 | GreenLeds[ OperateLeds.row + 8, 14] << 6 | GreenLeds[ OperateLeds.row + 8, 15] << 7

        OperateLeds.redcol1byte   = RedLeds[ OperateLeds.row, 0] | RedLeds[ OperateLeds.row, 1] << 1 | RedLeds[ OperateLeds.row, 2] << 2 | RedLeds[ OperateLeds.row, 3] << 3 | RedLeds[ OperateLeds.row, 4] << 4 | RedLeds[ OperateLeds.row, 5] << 5 | RedLeds[ OperateLeds.row, 6] << 6 | RedLeds[ OperateLeds.row, 7] << 7 
        OperateLeds.redcol2byte   = RedLeds[ OperateLeds.row, 8] | RedLeds[ OperateLeds.row, 9] << 1 | RedLeds[ OperateLeds.row, 10] << 2 | RedLeds[ OperateLeds.row, 11] << 3 | RedLeds[ OperateLeds.row, 12] << 4 | RedLeds[ OperateLeds.row, 13] << 5 | RedLeds[ OperateLeds.row, 14] << 6 | RedLeds[ OperateLeds.row, 15] << 7 
        OperateLeds.redcol3byte   = RedLeds[ OperateLeds.row + 8, 0] | RedLeds[ OperateLeds.row + 8, 1] << 1 | RedLeds[ OperateLeds.row + 8, 2] << 2 | RedLeds[ OperateLeds.row + 8, 3] << 3 | RedLeds[ OperateLeds.row + 8, 4] << 4 | RedLeds[ OperateLeds.row + 8, 5] << 5 | RedLeds[ OperateLeds.row + 8, 6] << 6 | RedLeds[ OperateLeds.row + 8, 7] << 7 
        OperateLeds.redcol4byte   = RedLeds[ OperateLeds.row + 8, 8] | RedLeds[ OperateLeds.row + 8, 9] << 1 | RedLeds[ OperateLeds.row + 8, 10] << 2 | RedLeds[ OperateLeds.row + 8, 11] << 3 | RedLeds[ OperateLeds.row + 8, 12] << 4 | RedLeds[ OperateLeds.row + 8, 13] << 5 | RedLeds[ OperateLeds.row + 8, 14] << 6 | RedLeds[ OperateLeds.row + 8, 15] << 7 
        
        if (DEBUG):
            print (OperateLeds.greencol1byte)
            print (OperateLeds.greencol2byte)
            print (OperateLeds.greencol3byte)
            print (OperateLeds.greencol4byte)

        ser.write(bytes( [OperateLeds.greencol1byte]))
        ser.write(bytes( [OperateLeds.greencol2byte]))
        ser.write(bytes( [OperateLeds.greencol3byte]))
        ser.write(bytes( [OperateLeds.greencol4byte]))


        ser.write(bytes( [OperateLeds.redcol1byte]))
        ser.write(bytes( [OperateLeds.redcol2byte]))
        ser.write(bytes( [OperateLeds.redcol3byte]))
        ser.write(bytes( [OperateLeds.redcol4byte]))
        OperateLeds.row += 1



# Initialize OperateLeds() local static variables
OperateLeds.row = 0

OperateLeds.greencol1byte = ~0x00
OperateLeds.greencol2byte = ~0x00
OperateLeds.greencol3byte = ~0x00
OperateLeds.greencol4byte = ~0x00

OperateLeds.redcol1byte = ~0x00
OperateLeds.redcol2byte = ~0x00
OperateLeds.redcol3byte = ~0x00
OperateLeds.redcol4byte = ~0x00


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

