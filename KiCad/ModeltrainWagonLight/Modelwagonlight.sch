EESchema Schematic File Version 2
LIBS:power
LIBS:device
LIBS:switches
LIBS:relays
LIBS:motors
LIBS:transistors
LIBS:conn
LIBS:linear
LIBS:regul
LIBS:74xx
LIBS:cmos4000
LIBS:adc-dac
LIBS:memory
LIBS:xilinx
LIBS:microcontrollers
LIBS:dsp
LIBS:microchip
LIBS:analog_switches
LIBS:motorola
LIBS:texas
LIBS:intel
LIBS:audio
LIBS:interface
LIBS:digital-audio
LIBS:philips
LIBS:display
LIBS:cypress
LIBS:siliconi
LIBS:opto
LIBS:atmel
LIBS:contrib
LIBS:valves
EELAYER 25 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L D D2
U 1 1 5A951F12
P 5100 4300
F 0 "D2" H 5100 4400 50  0000 C CNN
F 1 "1n4148" H 5100 4200 50  0000 C CNN
F 2 "" H 5100 4300 50  0001 C CNN
F 3 "" H 5100 4300 50  0001 C CNN
	1    5100 4300
	-1   0    0    1   
$EndComp
$Comp
L D D1
U 1 1 5A9520CA
P 5100 3950
F 0 "D1" H 5100 4050 50  0000 C CNN
F 1 "1n4148" H 5100 3850 50  0000 C CNN
F 2 "" H 5100 3950 50  0001 C CNN
F 3 "" H 5100 3950 50  0001 C CNN
	1    5100 3950
	-1   0    0    1   
$EndComp
$Comp
L D D4
U 1 1 5A95212B
P 5100 5000
F 0 "D4" H 5100 5100 50  0000 C CNN
F 1 "1n4148" H 5100 4900 50  0000 C CNN
F 2 "" H 5100 5000 50  0001 C CNN
F 3 "" H 5100 5000 50  0001 C CNN
	1    5100 5000
	1    0    0    -1  
$EndComp
$Comp
L D D3
U 1 1 5A952190
P 5100 4650
F 0 "D3" H 5100 4750 50  0000 C CNN
F 1 "1n4148" H 5100 4550 50  0000 C CNN
F 2 "" H 5100 4650 50  0001 C CNN
F 3 "" H 5100 4650 50  0001 C CNN
	1    5100 4650
	1    0    0    -1  
$EndComp
$Comp
L D_Zener D5
U 1 1 5A9521EF
P 6300 4250
F 0 "D5" H 6300 4350 50  0000 C CNN
F 1 "Zener" H 6300 4150 50  0000 C CNN
F 2 "" H 6300 4250 50  0001 C CNN
F 3 "" H 6300 4250 50  0001 C CNN
	1    6300 4250
	0    1    1    0   
$EndComp
$Comp
L R R1
U 1 1 5A952272
P 5900 3950
F 0 "R1" V 5980 3950 50  0000 C CNN
F 1 "R" V 5900 3950 50  0000 C CNN
F 2 "" V 5830 3950 50  0001 C CNN
F 3 "" H 5900 3950 50  0001 C CNN
	1    5900 3950
	0    -1   -1   0   
$EndComp
$Comp
L LED D7
U 1 1 5A9522B7
P 7750 3950
F 0 "D7" H 7750 4050 50  0000 C CNN
F 1 "LED" H 7750 3850 50  0000 C CNN
F 2 "" H 7750 3950 50  0001 C CNN
F 3 "" H 7750 3950 50  0001 C CNN
	1    7750 3950
	-1   0    0    1   
$EndComp
$Comp
L LED D6
U 1 1 5A9524FB
P 7250 3950
F 0 "D6" H 7250 4050 50  0000 C CNN
F 1 "LED" H 7250 3850 50  0000 C CNN
F 2 "" H 7250 3950 50  0001 C CNN
F 3 "" H 7250 3950 50  0001 C CNN
	1    7250 3950
	-1   0    0    1   
$EndComp
$Comp
L R R2
U 1 1 5A9526BF
P 6750 3950
F 0 "R2" V 6830 3950 50  0000 C CNN
F 1 "R" V 6750 3950 50  0000 C CNN
F 2 "" V 6680 3950 50  0001 C CNN
F 3 "" H 6750 3950 50  0001 C CNN
	1    6750 3950
	0    -1   -1   0   
$EndComp
Wire Wire Line
	5250 3950 5750 3950
Wire Wire Line
	6050 3950 6600 3950
Wire Wire Line
	6300 3950 6300 4100
Connection ~ 6300 3950
Wire Wire Line
	6900 3950 7100 3950
Wire Wire Line
	7400 3950 7600 3950
Wire Wire Line
	7900 3950 7950 3950
Wire Wire Line
	7950 3950 7950 4650
Wire Wire Line
	7950 4650 5250 4650
Wire Wire Line
	6300 4400 6300 4650
Wire Wire Line
	5300 5000 5250 5000
Wire Wire Line
	5300 4650 5300 5000
Connection ~ 5300 4650
Connection ~ 5300 3950
Wire Wire Line
	3500 3950 4950 3950
Wire Wire Line
	4700 3950 4700 4650
Wire Wire Line
	4700 4650 4950 4650
$Comp
L AC #PWR1
U 1 1 5A952F27
P 3500 3900
F 0 "#PWR1" H 3500 3800 50  0001 C CNN
F 1 "AC" H 3500 4150 50  0000 C CNN
F 2 "" H 3500 3900 50  0001 C CNN
F 3 "" H 3500 3900 50  0001 C CNN
	1    3500 3900
	1    0    0    -1  
$EndComp
$Comp
L AC #PWR2
U 1 1 5A952FC9
P 3500 4350
F 0 "#PWR2" H 3500 4250 50  0001 C CNN
F 1 "AC" H 3500 4600 50  0000 C CNN
F 2 "" H 3500 4350 50  0001 C CNN
F 3 "" H 3500 4350 50  0001 C CNN
	1    3500 4350
	-1   0    0    1   
$EndComp
Connection ~ 4700 3950
Text Notes 2600 4150 0    60   ~ 0
Current drawn from track 15V 20kHz PWM
Wire Wire Line
	3500 3950 3500 3900
Connection ~ 6300 4650
Wire Wire Line
	5250 4300 5300 4300
Wire Wire Line
	5300 4300 5300 3950
Wire Wire Line
	3500 4300 4950 4300
Wire Wire Line
	4850 4300 4850 5000
Wire Wire Line
	4850 5000 4950 5000
Wire Wire Line
	3500 4300 3500 4350
Connection ~ 4850 4300
$Comp
L C C1
U 1 1 5A953B73
P 5550 4300
F 0 "C1" H 5575 4400 50  0000 L CNN
F 1 "220nF" H 5575 4200 50  0000 L CNN
F 2 "" H 5588 4150 50  0001 C CNN
F 3 "" H 5550 4300 50  0001 C CNN
	1    5550 4300
	1    0    0    -1  
$EndComp
Wire Wire Line
	5550 4150 5550 3950
Connection ~ 5550 3950
Wire Wire Line
	5550 4450 5550 4650
Connection ~ 5550 4650
Text Notes 4550 3700 0    60   ~ 0
If VD5 = 5V1 and VD6/7 = 1.2V (one red led)\n\nVled = 2 x 1.2V\nIled --> 1mA?\nR2 = (VD5 - VLed) / ILed = (5.1 - 2.4) / 0.001 = 2k7 Ohm\n\nVR1 = Vsup - VD5 = 15 - 5.1 = 9.9V\nID5 --> 1mA?\nIR1 = Iled + ID5\nR1 = VR1 / IR1 = 9.9 / 0.002 = 4k95 Ohm\n\nPR1 = VR1 x IR1 = 9.9 x 0.002 = 20mW --> OK\nPD5 = VD5 x ID5 = 9.9 x 0.001 = 10mW --> OK\nPR2 = VR2 x IR2 = 2.7 x 0.001 = 3mW --> OK\n
$EndSCHEMATC
