EESchema Schematic File Version 4
LIBS:ClockDistrTest-cache
EELAYER 26 0
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
L ClockDistrTest-rescue:Conn_01x02_Male-ClockDistrTest-rescue J1
U 1 1 5AD59A7C
P 950 900
F 0 "J1" H 950 1000 50  0000 C CNN
F 1 "Conn_01x02_Male" H 950 700 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x02_P2.54mm_Vertical" H 950 900 50  0001 C CNN
F 3 "" H 950 900 50  0001 C CNN
	1    950  900 
	1    0    0    -1  
$EndComp
$Comp
L ClockDistrTest-rescue:LM7805_TO220-ClockDistrTest-rescue U3
U 1 1 5AD59A99
P 2950 900
F 0 "U3" H 2800 1025 50  0000 C CNN
F 1 "LM7805_TO220" H 2950 1025 50  0000 L CNN
F 2 "Package_TO_SOT_THT:TO-220-3_Horizontal_TabDown" H 2950 1125 50  0001 C CIN
F 3 "" H 2950 850 50  0001 C CNN
	1    2950 900 
	1    0    0    -1  
$EndComp
$Comp
L ClockDistrTest-rescue:GND-ClockDistrTest-rescue #PWR011
U 1 1 5AD59D67
P 2950 1650
F 0 "#PWR011" H 2950 1400 50  0001 C CNN
F 1 "GND" H 2950 1500 50  0000 C CNN
F 2 "" H 2950 1650 50  0001 C CNN
F 3 "" H 2950 1650 50  0001 C CNN
	1    2950 1650
	1    0    0    -1  
$EndComp
$Comp
L ClockDistrTest-rescue:+5V-ClockDistrTest-rescue #PWR012
U 1 1 5AD59DB0
P 3850 750
F 0 "#PWR012" H 3850 600 50  0001 C CNN
F 1 "+5V" H 3850 890 50  0000 C CNN
F 2 "" H 3850 750 50  0001 C CNN
F 3 "" H 3850 750 50  0001 C CNN
	1    3850 750 
	1    0    0    -1  
$EndComp
$Comp
L ClockDistrTest-rescue:SG-531-ClockDistrTest-rescue X1
U 1 1 5AD5A042
P 2550 2300
F 0 "X1" H 2350 2550 50  0000 L CNN
F 1 "SG-531" H 2600 2050 50  0000 L CNN
F 2 "Oscillator:Oscillator_SeikoEpson_SG-8002DC" H 3000 1950 50  0001 C CNN
F 3 "" H 2450 2300 50  0001 C CNN
	1    2550 2300
	1    0    0    -1  
$EndComp
$Comp
L ClockDistrTest-rescue:NB3N511-ClockDistrTest-rescue U2
U 1 1 5AD5DBD1
P 2550 4050
F 0 "U2" H 2650 4750 60  0000 L CNN
F 1 "NB3N511" H 2650 4650 60  0000 L CNN
F 2 "Package_SO:SOIC-8_3.9x4.9mm_P1.27mm" H 2600 3300 60  0001 C CNN
F 3 "http://www.onsemi.com/pub/Collateral/NB3N511-D.PDF" H 2600 3200 60  0001 C CNN
	1    2550 4050
	1    0    0    -1  
$EndComp
$Comp
L ClockDistrTest-rescue:C-ClockDistrTest-rescue C9
U 1 1 5AD5E473
P 4400 1200
F 0 "C9" H 4425 1300 50  0000 L CNN
F 1 "C" H 4425 1100 50  0000 L CNN
F 2 "Capacitor_SMD:C_1206_3216Metric" H 4438 1050 50  0001 C CNN
F 3 "" H 4400 1200 50  0001 C CNN
	1    4400 1200
	1    0    0    -1  
$EndComp
$Comp
L ClockDistrTest-rescue:C-ClockDistrTest-rescue C7
U 1 1 5AD5E538
P 3550 1200
F 0 "C7" H 3575 1300 50  0000 L CNN
F 1 "C" H 3575 1100 50  0000 L CNN
F 2 "Capacitor_SMD:C_1206_3216Metric" H 3588 1050 50  0001 C CNN
F 3 "" H 3550 1200 50  0001 C CNN
	1    3550 1200
	1    0    0    -1  
$EndComp
$Comp
L ClockDistrTest-rescue:C-ClockDistrTest-rescue C8
U 1 1 5AD5E56A
P 3850 1200
F 0 "C8" H 3875 1300 50  0000 L CNN
F 1 "C" H 3875 1100 50  0000 L CNN
F 2 "Capacitor_SMD:C_1206_3216Metric" H 3888 1050 50  0001 C CNN
F 3 "" H 3850 1200 50  0001 C CNN
	1    3850 1200
	1    0    0    -1  
$EndComp
$Comp
L ClockDistrTest-rescue:C-ClockDistrTest-rescue C5
U 1 1 5AD5E591
P 2350 1200
F 0 "C5" H 2375 1300 50  0000 L CNN
F 1 "C" H 2375 1100 50  0000 L CNN
F 2 "Capacitor_SMD:C_1206_3216Metric" H 2388 1050 50  0001 C CNN
F 3 "" H 2350 1200 50  0001 C CNN
	1    2350 1200
	1    0    0    -1  
$EndComp
$Comp
L ClockDistrTest-rescue:C-ClockDistrTest-rescue C4
U 1 1 5AD5E5C7
P 2100 1200
F 0 "C4" H 2125 1300 50  0000 L CNN
F 1 "C" H 2125 1100 50  0000 L CNN
F 2 "Capacitor_SMD:C_1206_3216Metric" H 2138 1050 50  0001 C CNN
F 3 "" H 2100 1200 50  0001 C CNN
	1    2100 1200
	1    0    0    -1  
$EndComp
$Comp
L ClockDistrTest-rescue:C-ClockDistrTest-rescue C10
U 1 1 5AD5E750
P 4750 1200
F 0 "C10" H 4775 1300 50  0000 L CNN
F 1 "C" H 4775 1100 50  0000 L CNN
F 2 "Capacitor_SMD:C_1206_3216Metric" H 4788 1050 50  0001 C CNN
F 3 "" H 4750 1200 50  0001 C CNN
	1    4750 1200
	1    0    0    -1  
$EndComp
$Comp
L ClockDistrTest-rescue:C-ClockDistrTest-rescue C11
U 1 1 5AD5E784
P 5100 1200
F 0 "C11" H 5125 1300 50  0000 L CNN
F 1 "C" H 5125 1100 50  0000 L CNN
F 2 "Capacitor_SMD:C_1206_3216Metric" H 5138 1050 50  0001 C CNN
F 3 "" H 5100 1200 50  0001 C CNN
	1    5100 1200
	1    0    0    -1  
$EndComp
$Comp
L ClockDistrTest-rescue:+5V-ClockDistrTest-rescue #PWR07
U 1 1 5AD5ECA0
P 2550 1900
F 0 "#PWR07" H 2550 1750 50  0001 C CNN
F 1 "+5V" H 2550 2040 50  0000 C CNN
F 2 "" H 2550 1900 50  0001 C CNN
F 3 "" H 2550 1900 50  0001 C CNN
	1    2550 1900
	1    0    0    -1  
$EndComp
$Comp
L ClockDistrTest-rescue:GND-ClockDistrTest-rescue #PWR08
U 1 1 5AD5ED68
P 2550 2700
F 0 "#PWR08" H 2550 2450 50  0001 C CNN
F 1 "GND" H 2550 2550 50  0000 C CNN
F 2 "" H 2550 2700 50  0001 C CNN
F 3 "" H 2550 2700 50  0001 C CNN
	1    2550 2700
	1    0    0    -1  
$EndComp
$Comp
L ClockDistrTest-rescue:GND-ClockDistrTest-rescue #PWR010
U 1 1 5AD5ED94
P 2550 4800
F 0 "#PWR010" H 2550 4550 50  0001 C CNN
F 1 "GND" H 2550 4650 50  0000 C CNN
F 2 "" H 2550 4800 50  0001 C CNN
F 3 "" H 2550 4800 50  0001 C CNN
	1    2550 4800
	1    0    0    -1  
$EndComp
$Comp
L ClockDistrTest-rescue:+5V-ClockDistrTest-rescue #PWR09
U 1 1 5AD5EE99
P 2550 3250
F 0 "#PWR09" H 2550 3100 50  0001 C CNN
F 1 "+5V" H 2550 3390 50  0000 C CNN
F 2 "" H 2550 3250 50  0001 C CNN
F 3 "" H 2550 3250 50  0001 C CNN
	1    2550 3250
	1    0    0    -1  
$EndComp
$Comp
L ClockDistrTest-rescue:Crystal-ClockDistrTest-rescue Y1
U 1 1 5AD5F521
P 1150 3700
F 0 "Y1" H 1150 3850 50  0000 C CNN
F 1 "Crystal" H 1150 3550 50  0000 C CNN
F 2 "Crystal:Crystal_HC49-U_Vertical" H 1150 3700 50  0001 C CNN
F 3 "" H 1150 3700 50  0001 C CNN
	1    1150 3700
	0    1    1    0   
$EndComp
$Comp
L ClockDistrTest-rescue:C-ClockDistrTest-rescue C1
U 1 1 5AD5F60E
P 850 4100
F 0 "C1" H 875 4200 50  0000 L CNN
F 1 "C" H 875 4000 50  0000 L CNN
F 2 "Capacitor_SMD:C_1206_3216Metric" H 888 3950 50  0001 C CNN
F 3 "" H 850 4100 50  0001 C CNN
	1    850  4100
	1    0    0    -1  
$EndComp
$Comp
L ClockDistrTest-rescue:C-ClockDistrTest-rescue C2
U 1 1 5AD5F685
P 1350 4100
F 0 "C2" H 1375 4200 50  0000 L CNN
F 1 "C" H 1375 4000 50  0000 L CNN
F 2 "Capacitor_SMD:C_1206_3216Metric" H 1388 3950 50  0001 C CNN
F 3 "" H 1350 4100 50  0001 C CNN
	1    1350 4100
	1    0    0    -1  
$EndComp
$Comp
L ClockDistrTest-rescue:GND-ClockDistrTest-rescue #PWR03
U 1 1 5AD5F876
P 1150 4350
F 0 "#PWR03" H 1150 4100 50  0001 C CNN
F 1 "GND" H 1150 4200 50  0000 C CNN
F 2 "" H 1150 4350 50  0001 C CNN
F 3 "" H 1150 4350 50  0001 C CNN
	1    1150 4350
	1    0    0    -1  
$EndComp
$Comp
L ClockDistrTest-rescue:+5V-ClockDistrTest-rescue #PWR05
U 1 1 5AD5FB76
P 1700 4200
F 0 "#PWR05" H 1700 4050 50  0001 C CNN
F 1 "+5V" H 1700 4340 50  0000 C CNN
F 2 "" H 1700 4200 50  0001 C CNN
F 3 "" H 1700 4200 50  0001 C CNN
	1    1700 4200
	1    0    0    -1  
$EndComp
$Comp
L ClockDistrTest-rescue:4049-ClockDistrTest-rescue U1
U 3 1 5AD601E3
P 3800 5600
F 0 "U1" H 3800 5650 50  0000 C CNN
F 1 "4049" H 3800 5550 50  0000 C CNN
F 2 "Package_DIP:DIP-16_W7.62mm" H 3800 5600 50  0001 C CNN
F 3 "" H 3800 5600 50  0001 C CNN
	3    3800 5600
	1    0    0    -1  
$EndComp
$Comp
L ClockDistrTest-rescue:4049-ClockDistrTest-rescue U1
U 4 1 5AD60358
P 3800 6050
F 0 "U1" H 3800 6100 50  0000 C CNN
F 1 "4049" H 3800 6000 50  0000 C CNN
F 2 "Package_DIP:DIP-16_W7.62mm" H 3800 6050 50  0001 C CNN
F 3 "" H 3800 6050 50  0001 C CNN
	4    3800 6050
	1    0    0    -1  
$EndComp
$Comp
L ClockDistrTest-rescue:4049-ClockDistrTest-rescue U1
U 5 1 5AD6040E
P 3800 6500
F 0 "U1" H 3800 6550 50  0000 C CNN
F 1 "4049" H 3800 6450 50  0000 C CNN
F 2 "Package_DIP:DIP-16_W7.62mm" H 3800 6500 50  0001 C CNN
F 3 "" H 3800 6500 50  0001 C CNN
	5    3800 6500
	1    0    0    -1  
$EndComp
$Comp
L ClockDistrTest-rescue:4049-ClockDistrTest-rescue U1
U 6 1 5AD6045D
P 3800 6950
F 0 "U1" H 3800 7000 50  0000 C CNN
F 1 "4049" H 3800 6900 50  0000 C CNN
F 2 "Package_DIP:DIP-16_W7.62mm" H 3800 6950 50  0001 C CNN
F 3 "" H 3800 6950 50  0001 C CNN
	6    3800 6950
	1    0    0    -1  
$EndComp
$Comp
L ClockDistrTest-rescue:4049-ClockDistrTest-rescue U1
U 2 1 5AD604BF
P 3000 5600
F 0 "U1" H 3000 5650 50  0000 C CNN
F 1 "4049" H 3000 5550 50  0000 C CNN
F 2 "Package_DIP:DIP-16_W7.62mm" H 3000 5600 50  0001 C CNN
F 3 "" H 3000 5600 50  0001 C CNN
	2    3000 5600
	1    0    0    -1  
$EndComp
$Comp
L ClockDistrTest-rescue:4049-ClockDistrTest-rescue U1
U 1 1 5AD60510
P 1950 5600
F 0 "U1" H 1950 5650 50  0000 C CNN
F 1 "4049" H 1950 5550 50  0000 C CNN
F 2 "Package_DIP:DIP-16_W7.62mm" H 1950 5600 50  0001 C CNN
F 3 "" H 1950 5600 50  0001 C CNN
	1    1950 5600
	1    0    0    -1  
$EndComp
$Comp
L ClockDistrTest-rescue:4049-ClockDistrTest-rescue U1
U 7 1 5AD60C43
P 850 6050
F 0 "U1" H 850 6100 50  0000 C CNN
F 1 "4049" H 850 6000 50  0000 C CNN
F 2 "Package_DIP:DIP-16_W7.62mm" H 850 6050 50  0001 C CNN
F 3 "" H 850 6050 50  0001 C CNN
	7    850  6050
	1    0    0    -1  
$EndComp
$Comp
L ClockDistrTest-rescue:GND-ClockDistrTest-rescue #PWR02
U 1 1 5AD60E78
P 850 6650
F 0 "#PWR02" H 850 6400 50  0001 C CNN
F 1 "GND" H 850 6500 50  0000 C CNN
F 2 "" H 850 6650 50  0001 C CNN
F 3 "" H 850 6650 50  0001 C CNN
	1    850  6650
	1    0    0    -1  
$EndComp
$Comp
L ClockDistrTest-rescue:+5V-ClockDistrTest-rescue #PWR01
U 1 1 5AD60EC2
P 850 5450
F 0 "#PWR01" H 850 5300 50  0001 C CNN
F 1 "+5V" H 850 5590 50  0000 C CNN
F 2 "" H 850 5450 50  0001 C CNN
F 3 "" H 850 5450 50  0001 C CNN
	1    850  5450
	1    0    0    -1  
$EndComp
$Comp
L ClockDistrTest-rescue:Crystal-ClockDistrTest-rescue Y2
U 1 1 5AD6137B
P 1900 6150
F 0 "Y2" H 1900 6300 50  0000 C CNN
F 1 "Crystal" H 1900 6000 50  0000 C CNN
F 2 "Crystal:Crystal_HC49-U_Vertical" H 1900 6150 50  0001 C CNN
F 3 "" H 1900 6150 50  0001 C CNN
	1    1900 6150
	-1   0    0    1   
$EndComp
$Comp
L ClockDistrTest-rescue:C-ClockDistrTest-rescue C3
U 1 1 5AD61382
P 1550 6350
F 0 "C3" H 1575 6450 50  0000 L CNN
F 1 "10pF" H 1575 6250 50  0000 L CNN
F 2 "Capacitor_SMD:C_1206_3216Metric" H 1588 6200 50  0001 C CNN
F 3 "" H 1550 6350 50  0001 C CNN
	1    1550 6350
	1    0    0    -1  
$EndComp
$Comp
L ClockDistrTest-rescue:C-ClockDistrTest-rescue C6
U 1 1 5AD61389
P 2350 6350
F 0 "C6" H 2375 6450 50  0000 L CNN
F 1 "10pF" H 2375 6250 50  0000 L CNN
F 2 "Capacitor_SMD:C_1206_3216Metric" H 2388 6200 50  0001 C CNN
F 3 "" H 2350 6350 50  0001 C CNN
	1    2350 6350
	1    0    0    -1  
$EndComp
$Comp
L ClockDistrTest-rescue:GND-ClockDistrTest-rescue #PWR04
U 1 1 5AD61390
P 1550 6600
F 0 "#PWR04" H 1550 6350 50  0001 C CNN
F 1 "GND" H 1550 6450 50  0000 C CNN
F 2 "" H 1550 6600 50  0001 C CNN
F 3 "" H 1550 6600 50  0001 C CNN
	1    1550 6600
	1    0    0    -1  
$EndComp
$Comp
L ClockDistrTest-rescue:R-ClockDistrTest-rescue R1
U 1 1 5AD61931
P 1900 5300
F 0 "R1" V 1980 5300 50  0000 C CNN
F 1 "1M" V 1900 5300 50  0000 C CNN
F 2 "Resistor_SMD:R_1206_3216Metric" V 1830 5300 50  0001 C CNN
F 3 "" H 1900 5300 50  0001 C CNN
	1    1900 5300
	0    1    1    0   
$EndComp
$Comp
L ClockDistrTest-rescue:R-ClockDistrTest-rescue R2
U 1 1 5AD6210A
P 2350 5950
F 0 "R2" V 2430 5950 50  0000 C CNN
F 1 "270" V 2350 5950 50  0000 C CNN
F 2 "Resistor_SMD:R_1206_3216Metric" V 2280 5950 50  0001 C CNN
F 3 "" H 2350 5950 50  0001 C CNN
	1    2350 5950
	-1   0    0    1   
$EndComp
$Comp
L ClockDistrTest-rescue:GND-ClockDistrTest-rescue #PWR06
U 1 1 5AD6272B
P 2350 6600
F 0 "#PWR06" H 2350 6350 50  0001 C CNN
F 1 "GND" H 2350 6450 50  0000 C CNN
F 2 "" H 2350 6600 50  0001 C CNN
F 3 "" H 2350 6600 50  0001 C CNN
	1    2350 6600
	1    0    0    -1  
$EndComp
$Comp
L ClockDistrTest-rescue:Conn_01x02_Male-ClockDistrTest-rescue J4
U 1 1 5AD6809E
P 4500 3850
F 0 "J4" H 4500 3950 50  0000 C CNN
F 1 "Conn_01x02_Male" H 4350 3650 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x02_P2.54mm_Vertical" H 4500 3850 50  0001 C CNN
F 3 "" H 4500 3850 50  0001 C CNN
	1    4500 3850
	0    1    1    0   
$EndComp
$Comp
L ClockDistrTest-rescue:Conn_01x02_Male-ClockDistrTest-rescue J3
U 1 1 5AD68320
P 4500 2100
F 0 "J3" H 4500 2200 50  0000 C CNN
F 1 "Conn_01x02_Male" H 4350 1900 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x02_P2.54mm_Vertical" H 4500 2100 50  0001 C CNN
F 3 "" H 4500 2100 50  0001 C CNN
	1    4500 2100
	0    1    1    0   
$EndComp
$Comp
L ClockDistrTest-rescue:Conn_01x02_Male-ClockDistrTest-rescue J5
U 1 1 5AD684BA
P 4500 5400
F 0 "J5" H 4500 5500 50  0000 C CNN
F 1 "Conn_01x02_Male" V 4350 5200 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x02_P2.54mm_Vertical" H 4500 5400 50  0001 C CNN
F 3 "" H 4500 5400 50  0001 C CNN
	1    4500 5400
	0    1    1    0   
$EndComp
Connection ~ 2350 900 
Wire Wire Line
	2950 1200 2950 1500
Wire Wire Line
	1350 1500 2100 1500
Connection ~ 2100 1500
Connection ~ 2350 1500
Connection ~ 2950 1500
Connection ~ 3550 1500
Wire Wire Line
	3250 900  3550 900 
Connection ~ 3550 900 
Connection ~ 3850 900 
Wire Wire Line
	1150 1000 1350 1000
Wire Wire Line
	1350 1000 1350 1500
Wire Wire Line
	2100 1050 2100 900 
Wire Wire Line
	2350 1050 2350 900 
Wire Wire Line
	2100 1500 2100 1350
Wire Wire Line
	2350 1500 2350 1350
Wire Wire Line
	3550 1500 3550 1350
Wire Wire Line
	3550 1050 3550 900 
Wire Wire Line
	3850 750  3850 900 
Wire Wire Line
	3850 1500 3850 1350
Wire Wire Line
	4400 1500 4400 1350
Connection ~ 3850 1500
Wire Wire Line
	4400 900  4400 1050
Wire Wire Line
	4750 900  4750 1050
Connection ~ 4400 900 
Wire Wire Line
	5100 900  5100 1050
Connection ~ 4750 900 
Wire Wire Line
	4750 1500 4750 1350
Connection ~ 4400 1500
Wire Wire Line
	5100 1500 5100 1350
Connection ~ 4750 1500
Wire Wire Line
	2550 1900 2550 1950
Wire Wire Line
	2550 2600 2550 2700
Wire Wire Line
	2550 3250 2550 3350
Wire Wire Line
	2550 4650 2550 4800
Wire Wire Line
	850  4250 1150 4250
Wire Wire Line
	1150 4250 1150 4350
Connection ~ 1150 4250
Wire Wire Line
	850  3950 850  3450
Wire Wire Line
	850  3450 1150 3450
Wire Wire Line
	1150 3450 1150 3550
Wire Wire Line
	1150 3850 1150 3950
Wire Wire Line
	1150 3950 1350 3950
Connection ~ 1350 3950
Wire Wire Line
	2050 3850 1400 3850
Wire Wire Line
	1400 3850 1400 3450
Connection ~ 1150 3450
Wire Wire Line
	2050 4250 1700 4250
Wire Wire Line
	1700 4250 1700 4200
Wire Wire Line
	2100 1950 2100 2300
Wire Wire Line
	2100 2300 2250 2300
Connection ~ 2550 1950
Wire Wire Line
	2100 1950 2550 1950
Wire Wire Line
	850  5450 850  5550
Wire Wire Line
	850  6550 850  6650
Wire Wire Line
	1550 6500 1550 6600
Wire Wire Line
	1550 5300 1550 5600
Wire Wire Line
	1550 6150 1750 6150
Wire Wire Line
	2350 6100 2350 6150
Connection ~ 2350 6150
Wire Wire Line
	1550 5300 1750 5300
Connection ~ 1550 6150
Wire Wire Line
	1650 5600 1550 5600
Connection ~ 1550 5600
Wire Wire Line
	2350 6500 2350 6600
Wire Wire Line
	2350 6150 2050 6150
Wire Wire Line
	2350 5800 2350 5600
Wire Wire Line
	2350 5300 2050 5300
Wire Wire Line
	2250 5600 2350 5600
Connection ~ 2350 5600
Wire Wire Line
	3300 5600 3400 5600
Wire Wire Line
	3500 6050 3400 6050
Wire Wire Line
	3400 5600 3400 6050
Connection ~ 3400 5600
Wire Wire Line
	3400 6500 3500 6500
Connection ~ 3400 6050
Wire Wire Line
	3400 6950 3500 6950
Connection ~ 3400 6500
Wire Wire Line
	2850 2300 4400 2300
Wire Wire Line
	3050 4050 4400 4050
Wire Wire Line
	4100 5600 4400 5600
Wire Wire Line
	4500 4150 4500 4050
Wire Wire Line
	4500 2300 4850 2300
Wire Wire Line
	4850 2300 4850 2800
Connection ~ 4850 4150
Wire Wire Line
	4850 5600 4500 5600
$Comp
L ClockDistrTest-rescue:+5V-ClockDistrTest-rescue #PWR014
U 1 1 5AD69C34
P 5500 1950
F 0 "#PWR014" H 5500 1800 50  0001 C CNN
F 1 "+5V" H 5500 2090 50  0000 C CNN
F 2 "" H 5500 1950 50  0001 C CNN
F 3 "" H 5500 1950 50  0001 C CNN
	1    5500 1950
	1    0    0    -1  
$EndComp
$Comp
L ClockDistrTest-rescue:GND-ClockDistrTest-rescue #PWR015
U 1 1 5AD69C99
P 5500 3300
F 0 "#PWR015" H 5500 3050 50  0001 C CNN
F 1 "GND" H 5500 3150 50  0000 C CNN
F 2 "" H 5500 3300 50  0001 C CNN
F 3 "" H 5500 3300 50  0001 C CNN
	1    5500 3300
	1    0    0    -1  
$EndComp
$Comp
L ClockDistrTest-rescue:+5V-ClockDistrTest-rescue #PWR013
U 1 1 5AD69F3B
P 5050 1950
F 0 "#PWR013" H 5050 1800 50  0001 C CNN
F 1 "+5V" H 5050 2090 50  0000 C CNN
F 2 "" H 5050 1950 50  0001 C CNN
F 3 "" H 5050 1950 50  0001 C CNN
	1    5050 1950
	1    0    0    -1  
$EndComp
$Comp
L ClockDistrTest-rescue:R-ClockDistrTest-rescue R3
U 1 1 5AD6A459
P 5050 2300
F 0 "R3" V 5130 2300 50  0000 C CNN
F 1 "1K" V 5050 2300 50  0000 C CNN
F 2 "Resistor_SMD:R_1206_3216Metric" V 4980 2300 50  0001 C CNN
F 3 "" H 5050 2300 50  0001 C CNN
	1    5050 2300
	-1   0    0    1   
$EndComp
Wire Wire Line
	5050 1950 5050 2150
$Comp
L ClockDistrTest-rescue:C-ClockDistrTest-rescue C12
U 1 1 5AD6B20B
P 5400 1200
F 0 "C12" H 5425 1300 50  0000 L CNN
F 1 "C" H 5425 1100 50  0000 L CNN
F 2 "Capacitor_SMD:C_1206_3216Metric" H 5438 1050 50  0001 C CNN
F 3 "" H 5400 1200 50  0001 C CNN
	1    5400 1200
	1    0    0    -1  
$EndComp
Wire Wire Line
	5400 900  5400 1050
Connection ~ 5100 900 
Wire Wire Line
	5400 1500 5400 1350
Connection ~ 5100 1500
$Comp
L ClockDistrTest-rescue:Conn_01x02_Male-ClockDistrTest-rescue J6
U 1 1 5AD6C486
P 4500 5850
F 0 "J6" H 4500 5950 50  0000 C CNN
F 1 "Conn_01x02_Male" V 4750 6200 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x02_P2.54mm_Vertical" H 4500 5850 50  0001 C CNN
F 3 "" H 4500 5850 50  0001 C CNN
	1    4500 5850
	0    1    1    0   
$EndComp
$Comp
L ClockDistrTest-rescue:Conn_01x02_Male-ClockDistrTest-rescue J7
U 1 1 5AD6C60A
P 4500 6300
F 0 "J7" H 4500 6400 50  0000 C CNN
F 1 "Conn_01x02_Male" V 4800 6600 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x02_P2.54mm_Vertical" H 4500 6300 50  0001 C CNN
F 3 "" H 4500 6300 50  0001 C CNN
	1    4500 6300
	0    1    1    0   
$EndComp
$Comp
L ClockDistrTest-rescue:Conn_01x02_Male-ClockDistrTest-rescue J2
U 1 1 5AD6C687
P 4450 6750
F 0 "J2" H 4450 6850 50  0000 C CNN
F 1 "Conn_01x02_Male" V 4750 7100 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x02_P2.54mm_Vertical" H 4450 6750 50  0001 C CNN
F 3 "" H 4450 6750 50  0001 C CNN
	1    4450 6750
	0    1    1    0   
$EndComp
Wire Wire Line
	4100 6050 4400 6050
Wire Wire Line
	4100 6500 4400 6500
Wire Wire Line
	4100 6950 4350 6950
Wire Wire Line
	4850 6050 4500 6050
Connection ~ 4850 5600
Wire Wire Line
	4850 6500 4500 6500
Connection ~ 4850 6050
Wire Wire Line
	4850 6950 4450 6950
Connection ~ 4850 6500
Wire Wire Line
	2100 900  2350 900 
Wire Wire Line
	2350 900  2650 900 
Wire Wire Line
	2100 1500 2350 1500
Wire Wire Line
	2350 1500 2950 1500
Wire Wire Line
	2950 1500 2950 1650
Wire Wire Line
	2950 1500 3550 1500
Wire Wire Line
	3550 1500 3850 1500
Wire Wire Line
	3550 900  3850 900 
Wire Wire Line
	3850 900  3850 1050
Wire Wire Line
	3850 900  4400 900 
Wire Wire Line
	3850 1500 4400 1500
Wire Wire Line
	4400 900  4750 900 
Wire Wire Line
	4750 900  5100 900 
Wire Wire Line
	4400 1500 4750 1500
Wire Wire Line
	4750 1500 5100 1500
Wire Wire Line
	1150 4250 1350 4250
Wire Wire Line
	1350 3950 2050 3950
Wire Wire Line
	1150 3450 1400 3450
Wire Wire Line
	2550 1950 2550 2000
Wire Wire Line
	2350 6150 2350 6200
Wire Wire Line
	1550 6150 1550 6200
Wire Wire Line
	1550 5600 1550 6150
Wire Wire Line
	2350 5600 2350 5300
Wire Wire Line
	2350 5600 2700 5600
Wire Wire Line
	3400 5600 3500 5600
Wire Wire Line
	3400 6050 3400 6500
Wire Wire Line
	3400 6500 3400 6950
Wire Wire Line
	4850 4150 4500 4150
Wire Wire Line
	4850 4150 4850 5600
Wire Wire Line
	5100 900  5400 900 
Wire Wire Line
	5100 1500 5400 1500
Wire Wire Line
	4850 5600 4850 6050
Wire Wire Line
	4850 6050 4850 6500
Wire Wire Line
	4850 6500 4850 6950
Wire Wire Line
	5050 2450 5050 2600
$Comp
L Interface_UART:MAX14783E U4
U 1 1 5AD6BC12
P 5500 2600
F 0 "U4" H 5600 3200 50  0000 C CNN
F 1 "MAX14783E" H 5750 3100 50  0000 C CNN
F 2 "Package_SO:SOIC-8_3.9x4.9mm_P1.27mm" H 5500 1900 50  0001 C CNN
F 3 "https://datasheets.maximintegrated.com/en/ds/MAX14783E.pdf" H 5500 2650 50  0001 C CNN
	1    5500 2600
	1    0    0    -1  
$EndComp
Wire Wire Line
	5100 2600 5050 2600
Connection ~ 5050 2600
Wire Wire Line
	5050 2600 5050 2700
Wire Wire Line
	5100 2700 5050 2700
Wire Wire Line
	5100 2800 4850 2800
Wire Wire Line
	5500 1950 5500 2100
Wire Wire Line
	5500 3200 5500 3300
$Comp
L Interface_UART:MAX14783E U9
U 1 1 5AD7A80E
P 9750 2600
F 0 "U9" H 9850 3200 50  0000 C CNN
F 1 "MAX14783E" H 10000 3100 50  0000 C CNN
F 2 "Package_SO:SOIC-8_3.9x4.9mm_P1.27mm" H 9750 1900 50  0001 C CNN
F 3 "https://datasheets.maximintegrated.com/en/ds/MAX14783E.pdf" H 9750 2650 50  0001 C CNN
	1    9750 2600
	-1   0    0    -1  
$EndComp
$Comp
L ClockDistrTest-rescue:+5V-ClockDistrTest-rescue #PWR030
U 1 1 5AD7DA25
P 9750 1950
F 0 "#PWR030" H 9750 1800 50  0001 C CNN
F 1 "+5V" H 9750 2090 50  0000 C CNN
F 2 "" H 9750 1950 50  0001 C CNN
F 3 "" H 9750 1950 50  0001 C CNN
	1    9750 1950
	1    0    0    -1  
$EndComp
$Comp
L ClockDistrTest-rescue:GND-ClockDistrTest-rescue #PWR031
U 1 1 5AD7DA78
P 9750 3350
F 0 "#PWR031" H 9750 3100 50  0001 C CNN
F 1 "GND" H 9750 3200 50  0000 C CNN
F 2 "" H 9750 3350 50  0001 C CNN
F 3 "" H 9750 3350 50  0001 C CNN
	1    9750 3350
	1    0    0    -1  
$EndComp
Wire Wire Line
	9750 1950 9750 2100
Wire Wire Line
	9750 3200 9750 3350
$Comp
L ClockDistrTest-rescue:R-ClockDistrTest-rescue R10
U 1 1 5AD83D65
P 10350 2850
F 0 "R10" V 10430 2850 50  0000 C CNN
F 1 "1K" V 10350 2850 50  0000 C CNN
F 2 "Resistor_SMD:R_1206_3216Metric" V 10280 2850 50  0001 C CNN
F 3 "" H 10350 2850 50  0001 C CNN
	1    10350 2850
	1    0    0    -1  
$EndComp
$Comp
L ClockDistrTest-rescue:Conn_01x02_Male-ClockDistrTest-rescue J12
U 1 1 5AD872BC
P 10600 2200
F 0 "J12" H 10600 2300 50  0000 C CNN
F 1 "Conn_01x02_Male" H 10450 2000 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x02_P2.54mm_Vertical" H 10600 2200 50  0001 C CNN
F 3 "" H 10600 2200 50  0001 C CNN
	1    10600 2200
	0    1    1    0   
$EndComp
Wire Wire Line
	10150 2500 10500 2500
Wire Wire Line
	10500 2500 10500 2400
$Comp
L ClockDistrTest-rescue:GND-ClockDistrTest-rescue #PWR035
U 1 1 5AD8DD65
P 10600 3350
F 0 "#PWR035" H 10600 3100 50  0001 C CNN
F 1 "GND" H 10600 3200 50  0000 C CNN
F 2 "" H 10600 3350 50  0001 C CNN
F 3 "" H 10600 3350 50  0001 C CNN
	1    10600 3350
	1    0    0    -1  
$EndComp
Wire Wire Line
	10600 2400 10600 3350
Wire Wire Line
	10150 2600 10250 2600
Wire Wire Line
	10350 2600 10350 2700
$Comp
L ClockDistrTest-rescue:GND-ClockDistrTest-rescue #PWR034
U 1 1 5AD97D53
P 10350 3350
F 0 "#PWR034" H 10350 3100 50  0001 C CNN
F 1 "GND" H 10350 3200 50  0000 C CNN
F 2 "" H 10350 3350 50  0001 C CNN
F 3 "" H 10350 3350 50  0001 C CNN
	1    10350 3350
	1    0    0    -1  
$EndComp
Wire Wire Line
	10350 3350 10350 3000
Wire Wire Line
	10150 2700 10250 2700
Wire Wire Line
	10250 2700 10250 2600
Connection ~ 10250 2600
Wire Wire Line
	10250 2600 10350 2600
$Comp
L ClockDistrTest-rescue:R-ClockDistrTest-rescue R5
U 1 1 5ADA21C1
P 6150 2650
F 0 "R5" V 6230 2650 50  0000 C CNN
F 1 "120E" V 6150 2650 50  0000 C CNN
F 2 "Resistor_SMD:R_1206_3216Metric" V 6080 2650 50  0001 C CNN
F 3 "" H 6150 2650 50  0001 C CNN
	1    6150 2650
	-1   0    0    1   
$EndComp
$Comp
L ClockDistrTest-rescue:R-ClockDistrTest-rescue R4
U 1 1 5ADA2300
P 6150 2250
F 0 "R4" V 6230 2250 50  0000 C CNN
F 1 "1K" V 6150 2250 50  0000 C CNN
F 2 "Resistor_SMD:R_1206_3216Metric" V 6080 2250 50  0001 C CNN
F 3 "" H 6150 2250 50  0001 C CNN
	1    6150 2250
	-1   0    0    1   
$EndComp
$Comp
L ClockDistrTest-rescue:R-ClockDistrTest-rescue R6
U 1 1 5ADA2370
P 6150 3050
F 0 "R6" V 6230 3050 50  0000 C CNN
F 1 "1K" V 6150 3050 50  0000 C CNN
F 2 "Resistor_SMD:R_1206_3216Metric" V 6080 3050 50  0001 C CNN
F 3 "" H 6150 3050 50  0001 C CNN
	1    6150 3050
	-1   0    0    1   
$EndComp
$Comp
L ClockDistrTest-rescue:+5V-ClockDistrTest-rescue #PWR016
U 1 1 5ADA23EE
P 6150 1950
F 0 "#PWR016" H 6150 1800 50  0001 C CNN
F 1 "+5V" H 6150 2090 50  0000 C CNN
F 2 "" H 6150 1950 50  0001 C CNN
F 3 "" H 6150 1950 50  0001 C CNN
	1    6150 1950
	1    0    0    -1  
$EndComp
$Comp
L ClockDistrTest-rescue:GND-ClockDistrTest-rescue #PWR017
U 1 1 5ADA244B
P 6150 3300
F 0 "#PWR017" H 6150 3050 50  0001 C CNN
F 1 "GND" H 6150 3150 50  0000 C CNN
F 2 "" H 6150 3300 50  0001 C CNN
F 3 "" H 6150 3300 50  0001 C CNN
	1    6150 3300
	1    0    0    -1  
$EndComp
Wire Wire Line
	6150 3300 6150 3200
Wire Wire Line
	6150 2900 6150 2800
Wire Wire Line
	5900 2800 6150 2800
Connection ~ 6150 2800
Wire Wire Line
	5900 2500 6150 2500
Wire Wire Line
	6150 2400 6150 2500
Connection ~ 6150 2500
Wire Wire Line
	6150 2100 6150 1950
$Comp
L ClockDistrTest-rescue:R-ClockDistrTest-rescue R8
U 1 1 5ADC3E4F
P 9100 2650
F 0 "R8" V 9180 2650 50  0000 C CNN
F 1 "120E" V 9100 2650 50  0000 C CNN
F 2 "Resistor_SMD:R_1206_3216Metric" V 9030 2650 50  0001 C CNN
F 3 "" H 9100 2650 50  0001 C CNN
	1    9100 2650
	-1   0    0    1   
$EndComp
$Comp
L ClockDistrTest-rescue:R-ClockDistrTest-rescue R7
U 1 1 5ADC3E56
P 9100 2250
F 0 "R7" V 9180 2250 50  0000 C CNN
F 1 "1K" V 9100 2250 50  0000 C CNN
F 2 "Resistor_SMD:R_1206_3216Metric" V 9030 2250 50  0001 C CNN
F 3 "" H 9100 2250 50  0001 C CNN
	1    9100 2250
	-1   0    0    1   
$EndComp
$Comp
L ClockDistrTest-rescue:R-ClockDistrTest-rescue R9
U 1 1 5ADC3E5D
P 9100 3050
F 0 "R9" V 9180 3050 50  0000 C CNN
F 1 "1K" V 9100 3050 50  0000 C CNN
F 2 "Resistor_SMD:R_1206_3216Metric" V 9030 3050 50  0001 C CNN
F 3 "" H 9100 3050 50  0001 C CNN
	1    9100 3050
	-1   0    0    1   
$EndComp
$Comp
L ClockDistrTest-rescue:+5V-ClockDistrTest-rescue #PWR028
U 1 1 5ADC3E64
P 9100 1950
F 0 "#PWR028" H 9100 1800 50  0001 C CNN
F 1 "+5V" H 9100 2090 50  0000 C CNN
F 2 "" H 9100 1950 50  0001 C CNN
F 3 "" H 9100 1950 50  0001 C CNN
	1    9100 1950
	1    0    0    -1  
$EndComp
$Comp
L ClockDistrTest-rescue:GND-ClockDistrTest-rescue #PWR029
U 1 1 5ADC3E6A
P 9100 3300
F 0 "#PWR029" H 9100 3050 50  0001 C CNN
F 1 "GND" H 9100 3150 50  0000 C CNN
F 2 "" H 9100 3300 50  0001 C CNN
F 3 "" H 9100 3300 50  0001 C CNN
	1    9100 3300
	1    0    0    -1  
$EndComp
Wire Wire Line
	9100 3300 9100 3200
Wire Wire Line
	9100 2900 9100 2800
Wire Wire Line
	9100 2400 9100 2500
Wire Wire Line
	9100 2100 9100 1950
Wire Wire Line
	9350 2500 9100 2500
Connection ~ 9100 2500
Wire Wire Line
	9350 2800 9100 2800
Connection ~ 9100 2800
$Comp
L Interface_UART:MAX3284E U7
U 1 1 5ADDCA8A
P 8650 4300
F 0 "U7" H 8350 4650 50  0000 L CNN
F 1 "MAX3284E" H 8800 4650 50  0000 L CNN
F 2 "Package_TO_SOT_SMD:SOT-23-6" H 8650 3600 50  0001 C CNN
F 3 "https://datasheets.maximintegrated.com/en/ds/MAX3280E-MAX3284E.pdf" H 8640 4260 50  0001 C CNN
	1    8650 4300
	1    0    0    -1  
$EndComp
Text Label 5950 2500 0    50   ~ 0
RS422-B
$Comp
L Interface_UART:MAX3284E U5
U 1 1 5ADE610B
P 6950 4300
F 0 "U5" H 6650 4650 50  0000 L CNN
F 1 "MAX3284E" H 7100 4650 50  0000 L CNN
F 2 "Package_TO_SOT_SMD:SOT-23-6" H 6950 3600 50  0001 C CNN
F 3 "https://datasheets.maximintegrated.com/en/ds/MAX3280E-MAX3284E.pdf" H 6940 4260 50  0001 C CNN
	1    6950 4300
	1    0    0    -1  
$EndComp
$Comp
L Interface_UART:MAX3284E U6
U 1 1 5ADE62DD
P 6950 5750
F 0 "U6" H 6650 6100 50  0000 L CNN
F 1 "MAX3284E" H 7100 6100 50  0000 L CNN
F 2 "Package_TO_SOT_SMD:SOT-23-6" H 6950 5050 50  0001 C CNN
F 3 "https://datasheets.maximintegrated.com/en/ds/MAX3280E-MAX3284E.pdf" H 6940 5710 50  0001 C CNN
	1    6950 5750
	1    0    0    -1  
$EndComp
$Comp
L ClockDistrTest-rescue:+5V-ClockDistrTest-rescue #PWR018
U 1 1 5ADE664A
P 6850 3800
F 0 "#PWR018" H 6850 3650 50  0001 C CNN
F 1 "+5V" H 6850 3940 50  0000 C CNN
F 2 "" H 6850 3800 50  0001 C CNN
F 3 "" H 6850 3800 50  0001 C CNN
	1    6850 3800
	1    0    0    -1  
$EndComp
$Comp
L ClockDistrTest-rescue:+5V-ClockDistrTest-rescue #PWR024
U 1 1 5ADE66B3
P 8550 3800
F 0 "#PWR024" H 8550 3650 50  0001 C CNN
F 1 "+5V" H 8550 3940 50  0000 C CNN
F 2 "" H 8550 3800 50  0001 C CNN
F 3 "" H 8550 3800 50  0001 C CNN
	1    8550 3800
	1    0    0    -1  
$EndComp
$Comp
L ClockDistrTest-rescue:+5V-ClockDistrTest-rescue #PWR019
U 1 1 5ADE671C
P 6850 5250
F 0 "#PWR019" H 6850 5100 50  0001 C CNN
F 1 "+5V" H 6850 5390 50  0000 C CNN
F 2 "" H 6850 5250 50  0001 C CNN
F 3 "" H 6850 5250 50  0001 C CNN
	1    6850 5250
	1    0    0    -1  
$EndComp
$Comp
L ClockDistrTest-rescue:GND-ClockDistrTest-rescue #PWR020
U 1 1 5ADE681C
P 6950 4800
F 0 "#PWR020" H 6950 4550 50  0001 C CNN
F 1 "GND" H 6950 4650 50  0000 C CNN
F 2 "" H 6950 4800 50  0001 C CNN
F 3 "" H 6950 4800 50  0001 C CNN
	1    6950 4800
	1    0    0    -1  
$EndComp
$Comp
L ClockDistrTest-rescue:GND-ClockDistrTest-rescue #PWR026
U 1 1 5ADE6885
P 8650 4800
F 0 "#PWR026" H 8650 4550 50  0001 C CNN
F 1 "GND" H 8650 4650 50  0000 C CNN
F 2 "" H 8650 4800 50  0001 C CNN
F 3 "" H 8650 4800 50  0001 C CNN
	1    8650 4800
	1    0    0    -1  
$EndComp
$Comp
L ClockDistrTest-rescue:GND-ClockDistrTest-rescue #PWR021
U 1 1 5ADE68EE
P 6950 6250
F 0 "#PWR021" H 6950 6000 50  0001 C CNN
F 1 "GND" H 6950 6100 50  0000 C CNN
F 2 "" H 6950 6250 50  0001 C CNN
F 3 "" H 6950 6250 50  0001 C CNN
	1    6950 6250
	1    0    0    -1  
$EndComp
Wire Wire Line
	6850 3800 6850 3850
Wire Wire Line
	7050 3900 7050 3850
Wire Wire Line
	7050 3850 6850 3850
Connection ~ 6850 3850
Wire Wire Line
	6850 3850 6850 3900
Wire Wire Line
	6950 4700 6950 4800
Wire Wire Line
	8550 3800 8550 3850
Wire Wire Line
	8750 3900 8750 3850
Wire Wire Line
	8750 3850 8550 3850
Connection ~ 8550 3850
Wire Wire Line
	8550 3850 8550 3900
Wire Wire Line
	8650 4700 8650 4800
Wire Wire Line
	6850 5250 6850 5300
Wire Wire Line
	7050 5350 7050 5300
Wire Wire Line
	7050 5300 6850 5300
Connection ~ 6850 5300
Wire Wire Line
	6850 5300 6850 5350
Wire Wire Line
	6950 6150 6950 6250
$Comp
L ClockDistrTest-rescue:Conn_01x02_Male-ClockDistrTest-rescue J9
U 1 1 5AE14EB4
P 7800 4100
F 0 "J9" H 7800 4200 50  0000 C CNN
F 1 "Conn_01x02_Male" H 7650 3900 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x02_P2.54mm_Vertical" H 7800 4100 50  0001 C CNN
F 3 "" H 7800 4100 50  0001 C CNN
	1    7800 4100
	0    1    1    0   
$EndComp
$Comp
L ClockDistrTest-rescue:GND-ClockDistrTest-rescue #PWR023
U 1 1 5AE15614
P 7800 4800
F 0 "#PWR023" H 7800 4550 50  0001 C CNN
F 1 "GND" H 7800 4650 50  0000 C CNN
F 2 "" H 7800 4800 50  0001 C CNN
F 3 "" H 7800 4800 50  0001 C CNN
	1    7800 4800
	1    0    0    -1  
$EndComp
Wire Wire Line
	7700 4300 7350 4300
Wire Wire Line
	7800 4300 7800 4800
$Comp
L ClockDistrTest-rescue:Conn_01x02_Male-ClockDistrTest-rescue J10
U 1 1 5AE20A26
P 9450 4100
F 0 "J10" H 9450 4200 50  0000 C CNN
F 1 "Conn_01x02_Male" H 9300 3900 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x02_P2.54mm_Vertical" H 9450 4100 50  0001 C CNN
F 3 "" H 9450 4100 50  0001 C CNN
	1    9450 4100
	0    1    1    0   
$EndComp
$Comp
L ClockDistrTest-rescue:GND-ClockDistrTest-rescue #PWR032
U 1 1 5AE20A9E
P 9450 4800
F 0 "#PWR032" H 9450 4550 50  0001 C CNN
F 1 "GND" H 9450 4650 50  0000 C CNN
F 2 "" H 9450 4800 50  0001 C CNN
F 3 "" H 9450 4800 50  0001 C CNN
	1    9450 4800
	1    0    0    -1  
$EndComp
Wire Wire Line
	9450 4800 9450 4300
Wire Wire Line
	9350 4300 9050 4300
$Comp
L ClockDistrTest-rescue:Conn_01x02_Male-ClockDistrTest-rescue J8
U 1 1 5AE2C540
P 7750 5550
F 0 "J8" H 7750 5650 50  0000 C CNN
F 1 "Conn_01x02_Male" H 7600 5350 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x02_P2.54mm_Vertical" H 7750 5550 50  0001 C CNN
F 3 "" H 7750 5550 50  0001 C CNN
	1    7750 5550
	0    1    1    0   
$EndComp
Wire Wire Line
	7650 5750 7350 5750
$Comp
L ClockDistrTest-rescue:GND-ClockDistrTest-rescue #PWR022
U 1 1 5AE3232D
P 7750 6250
F 0 "#PWR022" H 7750 6000 50  0001 C CNN
F 1 "GND" H 7750 6100 50  0000 C CNN
F 2 "" H 7750 6250 50  0001 C CNN
F 3 "" H 7750 6250 50  0001 C CNN
	1    7750 6250
	1    0    0    -1  
$EndComp
Wire Wire Line
	7750 6250 7750 5750
Connection ~ 4850 2800
Wire Wire Line
	4850 2800 4850 4150
$Comp
L Interface_UART:MAX3284E U8
U 1 1 5AE8B94C
P 8650 5750
F 0 "U8" H 8350 6100 50  0000 L CNN
F 1 "MAX3284E" H 8800 6100 50  0000 L CNN
F 2 "Package_TO_SOT_SMD:SOT-23-6" H 8650 5050 50  0001 C CNN
F 3 "https://datasheets.maximintegrated.com/en/ds/MAX3280E-MAX3284E.pdf" H 8640 5710 50  0001 C CNN
	1    8650 5750
	1    0    0    -1  
$EndComp
$Comp
L ClockDistrTest-rescue:+5V-ClockDistrTest-rescue #PWR025
U 1 1 5AE8B953
P 8550 5250
F 0 "#PWR025" H 8550 5100 50  0001 C CNN
F 1 "+5V" H 8550 5390 50  0000 C CNN
F 2 "" H 8550 5250 50  0001 C CNN
F 3 "" H 8550 5250 50  0001 C CNN
	1    8550 5250
	1    0    0    -1  
$EndComp
$Comp
L ClockDistrTest-rescue:GND-ClockDistrTest-rescue #PWR027
U 1 1 5AE8B959
P 8650 6250
F 0 "#PWR027" H 8650 6000 50  0001 C CNN
F 1 "GND" H 8650 6100 50  0000 C CNN
F 2 "" H 8650 6250 50  0001 C CNN
F 3 "" H 8650 6250 50  0001 C CNN
	1    8650 6250
	1    0    0    -1  
$EndComp
Wire Wire Line
	8550 5250 8550 5300
Wire Wire Line
	8750 5350 8750 5300
Wire Wire Line
	8750 5300 8550 5300
Connection ~ 8550 5300
Wire Wire Line
	8550 5300 8550 5350
Wire Wire Line
	8650 6150 8650 6250
$Comp
L ClockDistrTest-rescue:Conn_01x02_Male-ClockDistrTest-rescue J11
U 1 1 5AE8B965
P 9450 5550
F 0 "J11" H 9450 5650 50  0000 C CNN
F 1 "Conn_01x02_Male" H 9300 5350 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x02_P2.54mm_Vertical" H 9450 5550 50  0001 C CNN
F 3 "" H 9450 5550 50  0001 C CNN
	1    9450 5550
	0    1    1    0   
$EndComp
Wire Wire Line
	9350 5750 9050 5750
$Comp
L ClockDistrTest-rescue:GND-ClockDistrTest-rescue #PWR033
U 1 1 5AE8B96D
P 9450 6250
F 0 "#PWR033" H 9450 6000 50  0001 C CNN
F 1 "GND" H 9450 6100 50  0000 C CNN
F 2 "" H 9450 6250 50  0001 C CNN
F 3 "" H 9450 6250 50  0001 C CNN
	1    9450 6250
	1    0    0    -1  
$EndComp
Wire Wire Line
	9450 6250 9450 5750
$Comp
L ClockDistrTest-rescue:C-ClockDistrTest-rescue C13
U 1 1 5AE92EEC
P 5700 1200
F 0 "C13" H 5725 1300 50  0000 L CNN
F 1 "C" H 5725 1100 50  0000 L CNN
F 2 "Capacitor_SMD:C_1206_3216Metric" H 5738 1050 50  0001 C CNN
F 3 "" H 5700 1200 50  0001 C CNN
	1    5700 1200
	1    0    0    -1  
$EndComp
$Comp
L ClockDistrTest-rescue:C-ClockDistrTest-rescue C14
U 1 1 5AE92F74
P 6000 1200
F 0 "C14" H 6025 1300 50  0000 L CNN
F 1 "C" H 6025 1100 50  0000 L CNN
F 2 "Capacitor_SMD:C_1206_3216Metric" H 6038 1050 50  0001 C CNN
F 3 "" H 6000 1200 50  0001 C CNN
	1    6000 1200
	1    0    0    -1  
$EndComp
$Comp
L ClockDistrTest-rescue:C-ClockDistrTest-rescue C15
U 1 1 5AE92FFC
P 6300 1200
F 0 "C15" H 6325 1300 50  0000 L CNN
F 1 "C" H 6325 1100 50  0000 L CNN
F 2 "Capacitor_SMD:C_1206_3216Metric" H 6338 1050 50  0001 C CNN
F 3 "" H 6300 1200 50  0001 C CNN
	1    6300 1200
	1    0    0    -1  
$EndComp
$Comp
L ClockDistrTest-rescue:C-ClockDistrTest-rescue C16
U 1 1 5AE93086
P 6600 1200
F 0 "C16" H 6625 1300 50  0000 L CNN
F 1 "C" H 6625 1100 50  0000 L CNN
F 2 "Capacitor_SMD:C_1206_3216Metric" H 6638 1050 50  0001 C CNN
F 3 "" H 6600 1200 50  0001 C CNN
	1    6600 1200
	1    0    0    -1  
$EndComp
$Comp
L ClockDistrTest-rescue:C-ClockDistrTest-rescue C17
U 1 1 5AE9310E
P 6950 1200
F 0 "C17" H 6975 1300 50  0000 L CNN
F 1 "C" H 6975 1100 50  0000 L CNN
F 2 "Capacitor_SMD:C_1206_3216Metric" H 6988 1050 50  0001 C CNN
F 3 "" H 6950 1200 50  0001 C CNN
	1    6950 1200
	1    0    0    -1  
$EndComp
Wire Wire Line
	5400 900  5700 900 
Wire Wire Line
	5700 900  5700 1050
Connection ~ 5400 900 
Wire Wire Line
	5700 900  6000 900 
Wire Wire Line
	6000 900  6000 1050
Connection ~ 5700 900 
Wire Wire Line
	6000 900  6300 900 
Wire Wire Line
	6300 900  6300 1050
Connection ~ 6000 900 
Wire Wire Line
	6300 900  6600 900 
Wire Wire Line
	6600 900  6600 1050
Connection ~ 6300 900 
Wire Wire Line
	6600 900  6950 900 
Wire Wire Line
	6950 900  6950 1050
Connection ~ 6600 900 
Wire Wire Line
	5400 1500 5700 1500
Wire Wire Line
	5700 1500 5700 1350
Connection ~ 5400 1500
Wire Wire Line
	5700 1500 6000 1500
Wire Wire Line
	6000 1500 6000 1350
Connection ~ 5700 1500
Wire Wire Line
	6000 1500 6300 1500
Wire Wire Line
	6300 1500 6300 1350
Connection ~ 6000 1500
Wire Wire Line
	6300 1500 6600 1500
Wire Wire Line
	6600 1500 6600 1350
Connection ~ 6300 1500
Wire Wire Line
	6600 1500 6950 1500
Wire Wire Line
	6950 1500 6950 1350
Connection ~ 6600 1500
$Comp
L pspice:DIODE D1
U 1 1 5AEE6930
P 1700 900
F 0 "D1" H 1700 1165 50  0000 C CNN
F 1 "DIODE" H 1700 1074 50  0000 C CNN
F 2 "Diode_THT:D_DO-15_P10.16mm_Horizontal" H 1700 900 50  0001 C CNN
F 3 "" H 1700 900 50  0001 C CNN
	1    1700 900 
	1    0    0    -1  
$EndComp
Wire Wire Line
	1500 900  1150 900 
Wire Wire Line
	1900 900  2100 900 
Connection ~ 2100 900 
$Comp
L ClockDistrTest-rescue:R-ClockDistrTest-rescue R11
U 1 1 5AEFC266
P 7500 900
F 0 "R11" V 7580 900 50  0000 C CNN
F 1 "300" V 7500 900 50  0000 C CNN
F 2 "Resistor_SMD:R_1206_3216Metric" V 7430 900 50  0001 C CNN
F 3 "" H 7500 900 50  0001 C CNN
	1    7500 900 
	0    -1   -1   0   
$EndComp
Wire Wire Line
	7350 900  6950 900 
Connection ~ 6950 900 
$Comp
L Device:LED D2
U 1 1 5AF0580B
P 7650 1200
F 0 "D2" V 7688 1083 50  0000 R CNN
F 1 "LED" V 7597 1083 50  0000 R CNN
F 2 "LED_THT:LED_D5.0mm" H 7650 1200 50  0001 C CNN
F 3 "~" H 7650 1200 50  0001 C CNN
	1    7650 1200
	0    -1   -1   0   
$EndComp
Wire Wire Line
	7650 900  7650 1050
Wire Wire Line
	7650 1350 7650 1500
Wire Wire Line
	7650 1500 6950 1500
Connection ~ 6950 1500
Wire Wire Line
	6150 2500 6400 2500
Wire Wire Line
	6150 2800 6400 2800
$Comp
L ClockDistrTest-rescue:Conn_01x02_Male-ClockDistrTest-rescue J13
U 1 1 5AD969A5
P 6600 2700
F 0 "J13" H 6700 2800 50  0000 C CNN
F 1 "Conn_01x02_Male" V 6700 2200 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x02_P2.54mm_Vertical" H 6600 2700 50  0001 C CNN
F 3 "" H 6600 2700 50  0001 C CNN
	1    6600 2700
	-1   0    0    1   
$EndComp
Wire Wire Line
	6400 2500 6400 2600
Wire Wire Line
	6400 2700 6400 2800
$Comp
L ClockDistrTest-rescue:Conn_01x02_Male-ClockDistrTest-rescue J22
U 1 1 5ADAA57B
P 8650 2700
F 0 "J22" H 8650 2800 50  0000 C CNN
F 1 "Conn_01x02_Male" V 8700 2250 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x02_P2.54mm_Vertical" H 8650 2700 50  0001 C CNN
F 3 "" H 8650 2700 50  0001 C CNN
	1    8650 2700
	1    0    0    1   
$EndComp
Wire Wire Line
	8850 2600 8850 2500
Wire Wire Line
	8850 2500 9100 2500
Wire Wire Line
	8850 2700 8850 2800
Wire Wire Line
	8850 2800 9100 2800
$Comp
L ClockDistrTest-rescue:Conn_01x02_Male-ClockDistrTest-rescue J14
U 1 1 5AE5F9F1
P 6650 2700
F 0 "J14" H 6700 2800 50  0000 C CNN
F 1 "Conn_01x02_Male" V 6700 2250 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x02_P2.54mm_Vertical" H 6650 2700 50  0001 C CNN
F 3 "" H 6650 2700 50  0001 C CNN
	1    6650 2700
	1    0    0    1   
$EndComp
$Comp
L ClockDistrTest-rescue:Conn_01x02_Male-ClockDistrTest-rescue J15
U 1 1 5AE60DB3
P 7100 2700
F 0 "J15" H 7200 2800 50  0000 C CNN
F 1 "Conn_01x02_Male" V 7200 2200 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x02_P2.54mm_Vertical" H 7100 2700 50  0001 C CNN
F 3 "" H 7100 2700 50  0001 C CNN
	1    7100 2700
	-1   0    0    1   
$EndComp
$Comp
L ClockDistrTest-rescue:Conn_01x02_Male-ClockDistrTest-rescue J16
U 1 1 5AE60DBA
P 7150 2700
F 0 "J16" H 7200 2800 50  0000 C CNN
F 1 "Conn_01x02_Male" V 7200 2250 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x02_P2.54mm_Vertical" H 7150 2700 50  0001 C CNN
F 3 "" H 7150 2700 50  0001 C CNN
	1    7150 2700
	1    0    0    1   
$EndComp
$Comp
L ClockDistrTest-rescue:Conn_01x02_Male-ClockDistrTest-rescue J17
U 1 1 5AE69BC0
P 7600 2700
F 0 "J17" H 7700 2800 50  0000 C CNN
F 1 "Conn_01x02_Male" V 7700 2200 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x02_P2.54mm_Vertical" H 7600 2700 50  0001 C CNN
F 3 "" H 7600 2700 50  0001 C CNN
	1    7600 2700
	-1   0    0    1   
$EndComp
$Comp
L ClockDistrTest-rescue:Conn_01x02_Male-ClockDistrTest-rescue J18
U 1 1 5AE69BC7
P 7650 2700
F 0 "J18" H 7700 2800 50  0000 C CNN
F 1 "Conn_01x02_Male" V 7700 2250 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x02_P2.54mm_Vertical" H 7650 2700 50  0001 C CNN
F 3 "" H 7650 2700 50  0001 C CNN
	1    7650 2700
	1    0    0    1   
$EndComp
Wire Wire Line
	6900 2600 6850 2600
Wire Wire Line
	6850 2700 6900 2700
Wire Wire Line
	7350 2600 7400 2600
Wire Wire Line
	7400 2700 7350 2700
$Comp
L ClockDistrTest-rescue:Conn_01x02_Male-ClockDistrTest-rescue J19
U 1 1 5AEAA2FB
P 8100 2700
F 0 "J19" H 8200 2800 50  0000 C CNN
F 1 "Conn_01x02_Male" V 8200 2200 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x02_P2.54mm_Vertical" H 8100 2700 50  0001 C CNN
F 3 "" H 8100 2700 50  0001 C CNN
	1    8100 2700
	-1   0    0    1   
$EndComp
$Comp
L ClockDistrTest-rescue:Conn_01x02_Male-ClockDistrTest-rescue J20
U 1 1 5AEAA302
P 8150 2700
F 0 "J20" H 8200 2800 50  0000 C CNN
F 1 "Conn_01x02_Male" V 8200 2250 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x02_P2.54mm_Vertical" H 8150 2700 50  0001 C CNN
F 3 "" H 8150 2700 50  0001 C CNN
	1    8150 2700
	1    0    0    1   
$EndComp
$Comp
L ClockDistrTest-rescue:Conn_01x02_Male-ClockDistrTest-rescue J21
U 1 1 5AEB35EC
P 8600 2700
F 0 "J21" H 8700 2800 50  0000 C CNN
F 1 "Conn_01x02_Male" V 8700 2200 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x02_P2.54mm_Vertical" H 8600 2700 50  0001 C CNN
F 3 "" H 8600 2700 50  0001 C CNN
	1    8600 2700
	-1   0    0    1   
$EndComp
Wire Wire Line
	7850 2600 7900 2600
Wire Wire Line
	7850 2700 7900 2700
Wire Wire Line
	8350 2600 8400 2600
Wire Wire Line
	8350 2700 8400 2700
Text GLabel 6900 2800 3    50   Input ~ 0
A1
Text GLabel 6900 2500 1    50   Input ~ 0
B1
Wire Wire Line
	6900 2700 6900 2800
Connection ~ 6900 2700
Wire Wire Line
	6900 2500 6900 2600
Connection ~ 6900 2600
Text GLabel 7400 2500 1    50   Input ~ 0
B2
Text GLabel 7400 2800 3    50   Input ~ 0
A2
Text GLabel 7900 2500 1    50   Input ~ 0
B3
Text GLabel 7900 2800 3    50   Input ~ 0
A3
Text GLabel 8400 2500 1    50   Input ~ 0
B4
Text GLabel 8400 2800 3    50   Input ~ 0
A4
Wire Wire Line
	7400 2500 7400 2600
Connection ~ 7400 2600
Wire Wire Line
	7400 2800 7400 2700
Connection ~ 7400 2700
Wire Wire Line
	7900 2800 7900 2700
Connection ~ 7900 2700
Wire Wire Line
	7900 2500 7900 2600
Connection ~ 7900 2600
Wire Wire Line
	8400 2500 8400 2600
Connection ~ 8400 2600
Wire Wire Line
	8400 2800 8400 2700
Connection ~ 8400 2700
Text GLabel 6450 4200 0    50   Input ~ 0
A1
Text GLabel 6450 4400 0    50   Input ~ 0
B1
Text GLabel 6450 5650 0    50   Input ~ 0
A2
Text GLabel 6450 5850 0    50   Input ~ 0
B2
Text GLabel 8150 4200 0    50   Input ~ 0
A3
Text GLabel 8150 4400 0    50   Input ~ 0
B3
Text GLabel 8150 5650 0    50   Input ~ 0
A4
Text GLabel 8150 5850 0    50   Input ~ 0
B4
Wire Wire Line
	6450 4200 6550 4200
Wire Wire Line
	6550 4400 6450 4400
Wire Wire Line
	8150 4200 8250 4200
Wire Wire Line
	8150 4400 8250 4400
Wire Wire Line
	8150 5650 8250 5650
Wire Wire Line
	8150 5850 8250 5850
Wire Wire Line
	6450 5650 6550 5650
Wire Wire Line
	6450 5850 6550 5850
Text Label 5950 2900 0    50   ~ 0
RS422-A
$EndSCHEMATC