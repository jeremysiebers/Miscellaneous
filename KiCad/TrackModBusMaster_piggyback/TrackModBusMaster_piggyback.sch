EESchema Schematic File Version 4
LIBS:TrackModBusMaster_piggyback-cache
EELAYER 26 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title "ModBus Master piggyback"
Date ""
Rev "1.0"
Comp "Siebwalde"
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
Text Notes 600  2150 0    50   ~ 0
Supply 0V\nSupply 5V\nReset single ended from Ethernet_Target\nSPI_CLK\nSPI_SDI\nSPI_SDO\nSPI_SS\n\n\nRS485_BUS:\nTX_A\nTX_B\nRX_A\nRX_B\nSYNC_A\nSYNC_B\nRESET_A (ModBus_Master_Reset In)\nRESET_B (ModBus_Master_Reset In)\nRESET_A (Ethernet_Target Out)\nRESET_B (Ethernet_Target Out)
$Comp
L Connector_Generic:Conn_02x08_Odd_Even J1
U 1 1 5BCE4FC3
P 3550 1050
F 0 "J1" H 3600 1450 50  0000 C CNN
F 1 "Conn_02x08_Top_Bottom" H 3600 1550 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_2x08_P2.54mm_Vertical" H 3550 1050 50  0001 C CNN
F 3 "~" H 3550 1050 50  0001 C CNN
	1    3550 1050
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR011
U 1 1 5BCE50C5
P 3050 1550
F 0 "#PWR011" H 3050 1300 50  0001 C CNN
F 1 "GND" H 3050 1400 50  0000 C CNN
F 2 "" H 3050 1550 50  0001 C CNN
F 3 "" H 3050 1550 50  0001 C CNN
	1    3050 1550
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR010
U 1 1 5BCE5123
P 2900 700
F 0 "#PWR010" H 2900 550 50  0001 C CNN
F 1 "+5V" H 2900 840 50  0000 C CNN
F 2 "" H 2900 700 50  0001 C CNN
F 3 "" H 2900 700 50  0001 C CNN
	1    2900 700 
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR07
U 1 1 5BCE517A
P 2650 700
F 0 "#PWR07" H 2650 550 50  0001 C CNN
F 1 "+3.3V" H 2650 840 50  0000 C CNN
F 2 "" H 2650 700 50  0001 C CNN
F 3 "" H 2650 700 50  0001 C CNN
	1    2650 700 
	1    0    0    -1  
$EndComp
Wire Wire Line
	3050 1550 3050 1250
Wire Wire Line
	3050 750  3350 750 
Wire Wire Line
	3350 850  3050 850 
Connection ~ 3050 850 
Wire Wire Line
	3050 850  3050 750 
Wire Wire Line
	3350 950  2900 950 
Wire Wire Line
	2900 950  2900 700 
Wire Wire Line
	3350 1050 2900 1050
Wire Wire Line
	2900 1050 2900 950 
Connection ~ 2900 950 
Wire Wire Line
	3350 1150 3050 1150
Connection ~ 3050 1150
Wire Wire Line
	3050 1150 3050 850 
Wire Wire Line
	3350 1250 3050 1250
Connection ~ 3050 1250
Wire Wire Line
	3050 1250 3050 1150
Wire Wire Line
	3350 1350 2650 1350
Wire Wire Line
	2650 1350 2650 700 
Wire Wire Line
	3350 1450 2650 1450
Wire Wire Line
	2650 1450 2650 1350
Connection ~ 2650 1350
$Comp
L MCU_Microchip_PIC16:PIC16F18854-SO U6
U 1 1 5BCE5566
P 6950 2800
F 0 "U6" H 6600 3550 50  0000 C CNN
F 1 "PIC16F18854-SO" H 7350 3550 50  0000 C CNN
F 2 "Package_SO:SOIC-28W_7.5x17.9mm_P1.27mm" H 6950 1700 50  0001 C CNN
F 3 "http://ww1.microchip.com/downloads/en/DeviceDoc/PIC16(L)F18854%20Data%20Sheet_DS40001826C.pdf" H 7250 2200 50  0001 C CNN
	1    6950 2800
	1    0    0    -1  
$EndComp
$Comp
L Device:R R13
U 1 1 5BCE55D2
P 6500 1050
F 0 "R13" V 6580 1050 50  0000 C CNN
F 1 "1E" V 6500 1050 50  0000 C CNN
F 2 "Resistor_SMD:R_1206_3216Metric" V 6430 1050 50  0001 C CNN
F 3 "~" H 6500 1050 50  0001 C CNN
	1    6500 1050
	1    0    0    -1  
$EndComp
$Comp
L Device:C C12
U 1 1 5BCE56E1
P 6500 1450
F 0 "C12" H 6525 1550 50  0000 L CNN
F 1 "2.2u" H 6525 1350 50  0000 L CNN
F 2 "Capacitor_SMD:C_1206_3216Metric" H 6538 1300 50  0001 C CNN
F 3 "~" H 6500 1450 50  0001 C CNN
	1    6500 1450
	1    0    0    -1  
$EndComp
$Comp
L Device:C C13
U 1 1 5BCE5735
P 6700 1450
F 0 "C13" H 6725 1550 50  0000 L CNN
F 1 "100n" H 6725 1350 50  0000 L CNN
F 2 "Capacitor_SMD:C_1206_3216Metric" H 6738 1300 50  0001 C CNN
F 3 "~" H 6700 1450 50  0001 C CNN
	1    6700 1450
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR024
U 1 1 5BCE5793
P 6500 1700
F 0 "#PWR024" H 6500 1450 50  0001 C CNN
F 1 "GND" H 6500 1550 50  0000 C CNN
F 2 "" H 6500 1700 50  0001 C CNN
F 3 "" H 6500 1700 50  0001 C CNN
	1    6500 1700
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR023
U 1 1 5BCE57EE
P 6500 850
F 0 "#PWR023" H 6500 700 50  0001 C CNN
F 1 "+5V" H 6500 990 50  0000 C CNN
F 2 "" H 6500 850 50  0001 C CNN
F 3 "" H 6500 850 50  0001 C CNN
	1    6500 850 
	1    0    0    -1  
$EndComp
Wire Wire Line
	6500 850  6500 900 
Wire Wire Line
	6500 1200 6500 1250
Wire Wire Line
	6700 1300 6700 1250
Wire Wire Line
	6700 1250 6500 1250
Connection ~ 6500 1250
Wire Wire Line
	6500 1250 6500 1300
Wire Wire Line
	6500 1600 6500 1650
Wire Wire Line
	6700 1600 6700 1650
Wire Wire Line
	6700 1650 6500 1650
Connection ~ 6500 1650
Wire Wire Line
	6500 1650 6500 1700
Wire Wire Line
	6950 1250 6950 2000
Connection ~ 6700 1250
Wire Wire Line
	6700 1250 6950 1250
$Comp
L power:GND #PWR025
U 1 1 5BCE6BFB
P 6950 3750
F 0 "#PWR025" H 6950 3500 50  0001 C CNN
F 1 "GND" H 6950 3600 50  0000 C CNN
F 2 "" H 6950 3750 50  0001 C CNN
F 3 "" H 6950 3750 50  0001 C CNN
	1    6950 3750
	1    0    0    -1  
$EndComp
Wire Wire Line
	6950 3750 6950 3600
$Comp
L Connector_Generic:Conn_01x08 J5
U 1 1 5BCE6F4B
P 10750 1500
F 0 "J5" H 10750 1900 50  0000 C CNN
F 1 "Conn_01x08" H 10750 1000 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x08_P2.54mm_Vertical" H 10750 1500 50  0001 C CNN
F 3 "~" H 10750 1500 50  0001 C CNN
	1    10750 1500
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR030
U 1 1 5BCE706E
P 10450 1050
F 0 "#PWR030" H 10450 900 50  0001 C CNN
F 1 "+5V" H 10450 1190 50  0000 C CNN
F 2 "" H 10450 1050 50  0001 C CNN
F 3 "" H 10450 1050 50  0001 C CNN
	1    10450 1050
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR031
U 1 1 5BCE7087
P 10450 2150
F 0 "#PWR031" H 10450 1900 50  0001 C CNN
F 1 "GND" H 10450 2000 50  0000 C CNN
F 2 "" H 10450 2150 50  0001 C CNN
F 3 "" H 10450 2150 50  0001 C CNN
	1    10450 2150
	1    0    0    -1  
$EndComp
Wire Wire Line
	10550 1300 10450 1300
Wire Wire Line
	10450 1300 10450 1050
Wire Wire Line
	10450 2150 10450 1400
Wire Wire Line
	10450 1400 10550 1400
Text GLabel 10250 1200 0    50   Output ~ 0
Vpp
Wire Wire Line
	10250 1200 10550 1200
Text GLabel 10250 1500 0    50   BiDi ~ 0
ICSPDAT
Text GLabel 10250 1600 0    50   Output ~ 0
ICSPCLK
NoConn ~ 10550 1700
NoConn ~ 10550 1800
NoConn ~ 10550 1900
Wire Wire Line
	10550 1500 10250 1500
Wire Wire Line
	10550 1600 10250 1600
Text GLabel 5950 3000 0    50   Input ~ 0
~MCLR
Text GLabel 7600 2200 2    50   BiDi ~ 0
ICSPDAT
Text GLabel 7600 2300 2    50   Input ~ 0
ICSPCLK
$Comp
L Interface_UART:ST485EBDR U1
U 1 1 5BCEAD9E
P 1850 3600
F 0 "U1" H 1600 3950 50  0000 C CNN
F 1 "ST485EBDR" H 1950 3950 50  0000 L CNN
F 2 "Package_SO:SOIC-8_3.9x4.9mm_P1.27mm" H 1850 2700 50  0001 C CNN
F 3 "http://www.st.com/resource/en/datasheet/st485eb.pdf" H 1850 3650 50  0001 C CNN
	1    1850 3600
	-1   0    0    -1  
$EndComp
$Comp
L Device:R R1
U 1 1 5BCEBE99
P 700 3200
F 0 "R1" V 780 3200 50  0000 C CNN
F 1 "1E" V 700 3200 50  0000 C CNN
F 2 "Resistor_SMD:R_1206_3216Metric" V 630 3200 50  0001 C CNN
F 3 "~" H 700 3200 50  0001 C CNN
	1    700  3200
	1    0    0    -1  
$EndComp
$Comp
L Device:C C1
U 1 1 5BCEBE9F
P 700 3600
F 0 "C1" H 725 3700 50  0000 L CNN
F 1 "2.2u" H 725 3500 50  0000 L CNN
F 2 "Capacitor_SMD:C_1206_3216Metric" H 738 3450 50  0001 C CNN
F 3 "~" H 700 3600 50  0001 C CNN
	1    700  3600
	1    0    0    -1  
$EndComp
$Comp
L Device:C C4
U 1 1 5BCEBEA5
P 900 3600
F 0 "C4" H 925 3700 50  0000 L CNN
F 1 "100n" H 925 3500 50  0000 L CNN
F 2 "Capacitor_SMD:C_1206_3216Metric" H 938 3450 50  0001 C CNN
F 3 "~" H 900 3600 50  0001 C CNN
	1    900  3600
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR02
U 1 1 5BCEBEAB
P 700 3950
F 0 "#PWR02" H 700 3700 50  0001 C CNN
F 1 "GND" H 700 3800 50  0000 C CNN
F 2 "" H 700 3950 50  0001 C CNN
F 3 "" H 700 3950 50  0001 C CNN
	1    700  3950
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR01
U 1 1 5BCEBEB1
P 700 3000
F 0 "#PWR01" H 700 2850 50  0001 C CNN
F 1 "+5V" H 700 3140 50  0000 C CNN
F 2 "" H 700 3000 50  0001 C CNN
F 3 "" H 700 3000 50  0001 C CNN
	1    700  3000
	1    0    0    -1  
$EndComp
Wire Wire Line
	700  3000 700  3050
Wire Wire Line
	700  3350 700  3400
Wire Wire Line
	900  3450 900  3400
Wire Wire Line
	900  3400 700  3400
Connection ~ 700  3400
Wire Wire Line
	700  3400 700  3450
Wire Wire Line
	700  3750 700  3800
Wire Wire Line
	900  3750 900  3800
Wire Wire Line
	900  3800 700  3800
Connection ~ 700  3800
Wire Wire Line
	1850 3200 1850 3100
Wire Wire Line
	1850 3100 900  3100
Wire Wire Line
	900  3100 900  3400
Connection ~ 900  3400
Wire Wire Line
	1850 4100 1850 4150
Wire Wire Line
	1850 4150 900  4150
Wire Wire Line
	900  4150 900  3800
Connection ~ 900  3800
Text GLabel 1400 3500 0    50   Input ~ 0
Reset_B
Text GLabel 1400 3800 0    50   Input ~ 0
Reset_A
Wire Wire Line
	1450 3500 1400 3500
Wire Wire Line
	1450 3800 1400 3800
$Comp
L Device:R R4
U 1 1 5BCF3B62
P 2550 3500
F 0 "R4" V 2630 3500 50  0000 C CNN
F 1 "100E" V 2550 3500 50  0000 C CNN
F 2 "Resistor_SMD:R_1206_3216Metric" V 2480 3500 50  0001 C CNN
F 3 "~" H 2550 3500 50  0001 C CNN
	1    2550 3500
	0    1    1    0   
$EndComp
Wire Wire Line
	2400 3500 2250 3500
Wire Wire Line
	2250 3600 2350 3600
Wire Wire Line
	2350 3600 2350 3700
Wire Wire Line
	2350 3800 2250 3800
Wire Wire Line
	2250 3700 2350 3700
Connection ~ 2350 3700
Wire Wire Line
	2350 3700 2350 3800
Wire Wire Line
	1850 4150 2350 4150
Wire Wire Line
	2350 4150 2350 3800
Connection ~ 1850 4150
Connection ~ 2350 3800
$Comp
L Device:R R6
U 1 1 5BCF7A9A
P 2750 3700
F 0 "R6" V 2830 3700 50  0000 C CNN
F 1 "10k" V 2750 3700 50  0000 C CNN
F 2 "Resistor_SMD:R_1206_3216Metric" V 2680 3700 50  0001 C CNN
F 3 "~" H 2750 3700 50  0001 C CNN
	1    2750 3700
	-1   0    0    1   
$EndComp
$Comp
L power:GND #PWR09
U 1 1 5BCF7ADB
P 2750 3950
F 0 "#PWR09" H 2750 3700 50  0001 C CNN
F 1 "GND" H 2750 3800 50  0000 C CNN
F 2 "" H 2750 3950 50  0001 C CNN
F 3 "" H 2750 3950 50  0001 C CNN
	1    2750 3950
	1    0    0    -1  
$EndComp
Wire Wire Line
	2700 3500 2750 3500
Wire Wire Line
	2750 3500 2750 3550
$Comp
L Device:C C7
U 1 1 5BCFA0DF
P 2950 3700
F 0 "C7" H 2975 3800 50  0000 L CNN
F 1 "100n" H 2975 3600 50  0000 L CNN
F 2 "Capacitor_SMD:C_1206_3216Metric" H 2988 3550 50  0001 C CNN
F 3 "~" H 2950 3700 50  0001 C CNN
	1    2950 3700
	1    0    0    -1  
$EndComp
Wire Wire Line
	2750 3500 2950 3500
Wire Wire Line
	2950 3500 2950 3550
Connection ~ 2750 3500
Wire Wire Line
	700  3800 700  3950
Wire Wire Line
	2750 3850 2750 3900
Wire Wire Line
	2950 3850 2950 3900
Wire Wire Line
	2950 3900 2750 3900
Connection ~ 2750 3900
Wire Wire Line
	2750 3900 2750 3950
$Comp
L Device:Q_NMOS_GSD Q1
U 1 1 5BCFF801
P 3300 3500
F 0 "Q1" H 3500 3550 50  0000 L CNN
F 1 "BVSS123LT1G" H 3500 3450 50  0000 L CNN
F 2 "Package_TO_SOT_SMD:SOT-23" H 3500 3600 50  0001 C CNN
F 3 "~" H 3300 3500 50  0001 C CNN
	1    3300 3500
	1    0    0    -1  
$EndComp
Wire Wire Line
	3100 3500 2950 3500
Connection ~ 2950 3500
$Comp
L power:GND #PWR015
U 1 1 5BD01049
P 3400 3950
F 0 "#PWR015" H 3400 3700 50  0001 C CNN
F 1 "GND" H 3400 3800 50  0000 C CNN
F 2 "" H 3400 3950 50  0001 C CNN
F 3 "" H 3400 3950 50  0001 C CNN
	1    3400 3950
	1    0    0    -1  
$EndComp
Wire Wire Line
	3400 3950 3400 3700
Text GLabel 3600 3250 2    50   Output ~ 0
Reset
Wire Wire Line
	3600 3250 3400 3250
Wire Wire Line
	3400 3250 3400 3300
$Comp
L Interface_UART:ST485EBDR U2
U 1 1 5BD0430D
P 1850 5050
F 0 "U2" H 1600 5400 50  0000 C CNN
F 1 "ST485EBDR" H 1950 5400 50  0000 L CNN
F 2 "Package_SO:SOIC-8_3.9x4.9mm_P1.27mm" H 1850 4150 50  0001 C CNN
F 3 "http://www.st.com/resource/en/datasheet/st485eb.pdf" H 1850 5100 50  0001 C CNN
	1    1850 5050
	-1   0    0    -1  
$EndComp
$Comp
L Device:R R2
U 1 1 5BD04314
P 700 4650
F 0 "R2" V 780 4650 50  0000 C CNN
F 1 "1E" V 700 4650 50  0000 C CNN
F 2 "Resistor_SMD:R_1206_3216Metric" V 630 4650 50  0001 C CNN
F 3 "~" H 700 4650 50  0001 C CNN
	1    700  4650
	1    0    0    -1  
$EndComp
$Comp
L Device:C C2
U 1 1 5BD0431B
P 700 5050
F 0 "C2" H 725 5150 50  0000 L CNN
F 1 "2.2u" H 725 4950 50  0000 L CNN
F 2 "Capacitor_SMD:C_1206_3216Metric" H 738 4900 50  0001 C CNN
F 3 "~" H 700 5050 50  0001 C CNN
	1    700  5050
	1    0    0    -1  
$EndComp
$Comp
L Device:C C5
U 1 1 5BD04322
P 900 5050
F 0 "C5" H 925 5150 50  0000 L CNN
F 1 "100n" H 925 4950 50  0000 L CNN
F 2 "Capacitor_SMD:C_1206_3216Metric" H 938 4900 50  0001 C CNN
F 3 "~" H 900 5050 50  0001 C CNN
	1    900  5050
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR04
U 1 1 5BD04329
P 700 5400
F 0 "#PWR04" H 700 5150 50  0001 C CNN
F 1 "GND" H 700 5250 50  0000 C CNN
F 2 "" H 700 5400 50  0001 C CNN
F 3 "" H 700 5400 50  0001 C CNN
	1    700  5400
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR03
U 1 1 5BD0432F
P 700 4450
F 0 "#PWR03" H 700 4300 50  0001 C CNN
F 1 "+5V" H 700 4590 50  0000 C CNN
F 2 "" H 700 4450 50  0001 C CNN
F 3 "" H 700 4450 50  0001 C CNN
	1    700  4450
	1    0    0    -1  
$EndComp
Wire Wire Line
	700  4450 700  4500
Wire Wire Line
	700  4800 700  4850
Wire Wire Line
	900  4900 900  4850
Wire Wire Line
	900  4850 700  4850
Connection ~ 700  4850
Wire Wire Line
	700  4850 700  4900
Wire Wire Line
	700  5200 700  5250
Wire Wire Line
	900  5200 900  5250
Wire Wire Line
	900  5250 700  5250
Connection ~ 700  5250
Wire Wire Line
	1850 4650 1850 4550
Wire Wire Line
	1850 4550 900  4550
Wire Wire Line
	900  4550 900  4850
Connection ~ 900  4850
Wire Wire Line
	1850 5550 1850 5600
Wire Wire Line
	1850 5600 900  5600
Wire Wire Line
	900  5600 900  5250
Connection ~ 900  5250
Text GLabel 1400 4950 0    50   Input ~ 0
Rx_B
Text GLabel 1400 5250 0    50   Input ~ 0
Rx_A
Wire Wire Line
	1450 4950 1400 4950
Wire Wire Line
	1450 5250 1400 5250
Wire Wire Line
	2250 5050 2350 5050
Wire Wire Line
	2350 5050 2350 5150
Wire Wire Line
	2350 5250 2250 5250
Wire Wire Line
	2250 5150 2350 5150
Connection ~ 2350 5150
Wire Wire Line
	2350 5150 2350 5250
Wire Wire Line
	1850 5600 2350 5600
Wire Wire Line
	2350 5600 2350 5250
Connection ~ 1850 5600
Connection ~ 2350 5250
Wire Wire Line
	700  5250 700  5400
Text GLabel 2450 4950 2    50   Output ~ 0
Rx
Wire Wire Line
	2250 4950 2450 4950
$Comp
L Interface_UART:ST485EBDR U3
U 1 1 5BD0A572
P 1850 6500
F 0 "U3" H 1600 6850 50  0000 C CNN
F 1 "ST485EBDR" H 1950 6850 50  0000 L CNN
F 2 "Package_SO:SOIC-8_3.9x4.9mm_P1.27mm" H 1850 5600 50  0001 C CNN
F 3 "http://www.st.com/resource/en/datasheet/st485eb.pdf" H 1850 6550 50  0001 C CNN
	1    1850 6500
	-1   0    0    -1  
$EndComp
$Comp
L Device:R R3
U 1 1 5BD0A579
P 700 6100
F 0 "R3" V 780 6100 50  0000 C CNN
F 1 "1E" V 700 6100 50  0000 C CNN
F 2 "Resistor_SMD:R_1206_3216Metric" V 630 6100 50  0001 C CNN
F 3 "~" H 700 6100 50  0001 C CNN
	1    700  6100
	1    0    0    -1  
$EndComp
$Comp
L Device:C C3
U 1 1 5BD0A580
P 700 6500
F 0 "C3" H 725 6600 50  0000 L CNN
F 1 "2.2u" H 725 6400 50  0000 L CNN
F 2 "Capacitor_SMD:C_1206_3216Metric" H 738 6350 50  0001 C CNN
F 3 "~" H 700 6500 50  0001 C CNN
	1    700  6500
	1    0    0    -1  
$EndComp
$Comp
L Device:C C6
U 1 1 5BD0A587
P 900 6500
F 0 "C6" H 925 6600 50  0000 L CNN
F 1 "100n" H 925 6400 50  0000 L CNN
F 2 "Capacitor_SMD:C_1206_3216Metric" H 938 6350 50  0001 C CNN
F 3 "~" H 900 6500 50  0001 C CNN
	1    900  6500
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR06
U 1 1 5BD0A58E
P 700 6850
F 0 "#PWR06" H 700 6600 50  0001 C CNN
F 1 "GND" H 700 6700 50  0000 C CNN
F 2 "" H 700 6850 50  0001 C CNN
F 3 "" H 700 6850 50  0001 C CNN
	1    700  6850
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR05
U 1 1 5BD0A594
P 700 5900
F 0 "#PWR05" H 700 5750 50  0001 C CNN
F 1 "+5V" H 700 6040 50  0000 C CNN
F 2 "" H 700 5900 50  0001 C CNN
F 3 "" H 700 5900 50  0001 C CNN
	1    700  5900
	1    0    0    -1  
$EndComp
Wire Wire Line
	700  5900 700  5950
Wire Wire Line
	700  6250 700  6300
Wire Wire Line
	900  6350 900  6300
Wire Wire Line
	900  6300 700  6300
Connection ~ 700  6300
Wire Wire Line
	700  6300 700  6350
Wire Wire Line
	700  6650 700  6700
Wire Wire Line
	900  6650 900  6700
Wire Wire Line
	900  6700 700  6700
Connection ~ 700  6700
Wire Wire Line
	1850 6100 1850 6000
Wire Wire Line
	1850 6000 900  6000
Wire Wire Line
	900  6000 900  6300
Connection ~ 900  6300
Wire Wire Line
	1850 7000 1850 7050
Wire Wire Line
	1850 7050 900  7050
Wire Wire Line
	900  7050 900  6700
Connection ~ 900  6700
Text GLabel 1400 6400 0    50   Output ~ 0
Tx_B
Text GLabel 1400 6700 0    50   Output ~ 0
Tx_A
Wire Wire Line
	1450 6400 1400 6400
Wire Wire Line
	1450 6700 1400 6700
Wire Wire Line
	700  6700 700  6850
NoConn ~ 2250 6400
Wire Wire Line
	1850 6000 2350 6000
Wire Wire Line
	2350 6000 2350 6500
Wire Wire Line
	2350 6500 2250 6500
Connection ~ 1850 6000
Text GLabel 2450 6700 2    50   Input ~ 0
Tx
Wire Wire Line
	2450 6700 2250 6700
$Comp
L Interface_UART:ST485EBDR U5
U 1 1 5BD29C15
P 5000 6500
F 0 "U5" H 4750 6850 50  0000 C CNN
F 1 "ST485EBDR" H 5100 6850 50  0000 L CNN
F 2 "Package_SO:SOIC-8_3.9x4.9mm_P1.27mm" H 5000 5600 50  0001 C CNN
F 3 "http://www.st.com/resource/en/datasheet/st485eb.pdf" H 5000 6550 50  0001 C CNN
	1    5000 6500
	-1   0    0    -1  
$EndComp
$Comp
L Device:R R11
U 1 1 5BD29C1C
P 3850 6100
F 0 "R11" V 3930 6100 50  0000 C CNN
F 1 "1E" V 3850 6100 50  0000 C CNN
F 2 "Resistor_SMD:R_1206_3216Metric" V 3780 6100 50  0001 C CNN
F 3 "~" H 3850 6100 50  0001 C CNN
	1    3850 6100
	1    0    0    -1  
$EndComp
$Comp
L Device:C C9
U 1 1 5BD29C23
P 3850 6500
F 0 "C9" H 3875 6600 50  0000 L CNN
F 1 "2.2u" H 3875 6400 50  0000 L CNN
F 2 "Capacitor_SMD:C_1206_3216Metric" H 3888 6350 50  0001 C CNN
F 3 "~" H 3850 6500 50  0001 C CNN
	1    3850 6500
	1    0    0    -1  
$EndComp
$Comp
L Device:C C11
U 1 1 5BD29C2A
P 4050 6500
F 0 "C11" H 4075 6600 50  0000 L CNN
F 1 "100n" H 4075 6400 50  0000 L CNN
F 2 "Capacitor_SMD:C_1206_3216Metric" H 4088 6350 50  0001 C CNN
F 3 "~" H 4050 6500 50  0001 C CNN
	1    4050 6500
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR019
U 1 1 5BD29C31
P 3850 6850
F 0 "#PWR019" H 3850 6600 50  0001 C CNN
F 1 "GND" H 3850 6700 50  0000 C CNN
F 2 "" H 3850 6850 50  0001 C CNN
F 3 "" H 3850 6850 50  0001 C CNN
	1    3850 6850
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR018
U 1 1 5BD29C37
P 3850 5900
F 0 "#PWR018" H 3850 5750 50  0001 C CNN
F 1 "+5V" H 3850 6040 50  0000 C CNN
F 2 "" H 3850 5900 50  0001 C CNN
F 3 "" H 3850 5900 50  0001 C CNN
	1    3850 5900
	1    0    0    -1  
$EndComp
Wire Wire Line
	3850 5900 3850 5950
Wire Wire Line
	3850 6250 3850 6300
Wire Wire Line
	4050 6350 4050 6300
Wire Wire Line
	4050 6300 3850 6300
Connection ~ 3850 6300
Wire Wire Line
	3850 6300 3850 6350
Wire Wire Line
	3850 6650 3850 6700
Wire Wire Line
	4050 6650 4050 6700
Wire Wire Line
	4050 6700 3850 6700
Connection ~ 3850 6700
Wire Wire Line
	5000 6100 5000 6000
Wire Wire Line
	5000 6000 4050 6000
Wire Wire Line
	4050 6000 4050 6300
Connection ~ 4050 6300
Wire Wire Line
	5000 7000 5000 7050
Wire Wire Line
	5000 7050 4050 7050
Wire Wire Line
	4050 7050 4050 6700
Connection ~ 4050 6700
Text GLabel 4550 6400 0    50   Output ~ 0
Sync_B
Text GLabel 4550 6700 0    50   Output ~ 0
Sync_A
Wire Wire Line
	4600 6400 4550 6400
Wire Wire Line
	4600 6700 4550 6700
Wire Wire Line
	3850 6700 3850 6850
NoConn ~ 5400 6400
Wire Wire Line
	5000 6000 5500 6000
Wire Wire Line
	5500 6000 5500 6500
Wire Wire Line
	5500 6500 5400 6500
Connection ~ 5000 6000
Wire Wire Line
	5400 6600 5500 6600
Wire Wire Line
	5500 6600 5500 6500
Connection ~ 5500 6500
Text GLabel 5600 6700 2    50   Input ~ 0
Sync
Wire Wire Line
	5600 6700 5400 6700
$Comp
L Interface_UART:ST485EBDR U4
U 1 1 5BD2F9D2
P 5000 5050
F 0 "U4" H 4750 5400 50  0000 C CNN
F 1 "ST485EBDR" H 5100 5400 50  0000 L CNN
F 2 "Package_SO:SOIC-8_3.9x4.9mm_P1.27mm" H 5000 4150 50  0001 C CNN
F 3 "http://www.st.com/resource/en/datasheet/st485eb.pdf" H 5000 5100 50  0001 C CNN
	1    5000 5050
	-1   0    0    -1  
$EndComp
$Comp
L Device:R R10
U 1 1 5BD2F9D9
P 3850 4650
F 0 "R10" V 3930 4650 50  0000 C CNN
F 1 "1E" V 3850 4650 50  0000 C CNN
F 2 "Resistor_SMD:R_1206_3216Metric" V 3780 4650 50  0001 C CNN
F 3 "~" H 3850 4650 50  0001 C CNN
	1    3850 4650
	1    0    0    -1  
$EndComp
$Comp
L Device:C C8
U 1 1 5BD2F9E0
P 3850 5050
F 0 "C8" H 3875 5150 50  0000 L CNN
F 1 "2.2u" H 3875 4950 50  0000 L CNN
F 2 "Capacitor_SMD:C_1206_3216Metric" H 3888 4900 50  0001 C CNN
F 3 "~" H 3850 5050 50  0001 C CNN
	1    3850 5050
	1    0    0    -1  
$EndComp
$Comp
L Device:C C10
U 1 1 5BD2F9E7
P 4050 5050
F 0 "C10" H 4075 5150 50  0000 L CNN
F 1 "100n" H 4075 4950 50  0000 L CNN
F 2 "Capacitor_SMD:C_1206_3216Metric" H 4088 4900 50  0001 C CNN
F 3 "~" H 4050 5050 50  0001 C CNN
	1    4050 5050
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR017
U 1 1 5BD2F9EE
P 3850 5400
F 0 "#PWR017" H 3850 5150 50  0001 C CNN
F 1 "GND" H 3850 5250 50  0000 C CNN
F 2 "" H 3850 5400 50  0001 C CNN
F 3 "" H 3850 5400 50  0001 C CNN
	1    3850 5400
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR016
U 1 1 5BD2F9F4
P 3850 4450
F 0 "#PWR016" H 3850 4300 50  0001 C CNN
F 1 "+5V" H 3850 4590 50  0000 C CNN
F 2 "" H 3850 4450 50  0001 C CNN
F 3 "" H 3850 4450 50  0001 C CNN
	1    3850 4450
	1    0    0    -1  
$EndComp
Wire Wire Line
	3850 4450 3850 4500
Wire Wire Line
	3850 4800 3850 4850
Wire Wire Line
	4050 4900 4050 4850
Wire Wire Line
	4050 4850 3850 4850
Connection ~ 3850 4850
Wire Wire Line
	3850 4850 3850 4900
Wire Wire Line
	3850 5200 3850 5250
Wire Wire Line
	4050 5200 4050 5250
Wire Wire Line
	4050 5250 3850 5250
Connection ~ 3850 5250
Wire Wire Line
	5000 4650 5000 4550
Wire Wire Line
	5000 4550 4050 4550
Wire Wire Line
	4050 4550 4050 4850
Connection ~ 4050 4850
Wire Wire Line
	5000 5550 5000 5600
Wire Wire Line
	5000 5600 4050 5600
Wire Wire Line
	4050 5600 4050 5250
Connection ~ 4050 5250
Text GLabel 4550 4950 0    50   Output ~ 0
Reset_B
Text GLabel 4550 5250 0    50   Output ~ 0
Reset_A
Wire Wire Line
	4600 4950 4550 4950
Wire Wire Line
	4600 5250 4550 5250
Wire Wire Line
	3850 5250 3850 5400
NoConn ~ 5400 4950
Wire Wire Line
	5000 4550 5500 4550
Wire Wire Line
	5500 4550 5500 5050
Wire Wire Line
	5500 5050 5400 5050
Connection ~ 5000 4550
Wire Wire Line
	5400 5150 5500 5150
Wire Wire Line
	5500 5150 5500 5050
Connection ~ 5500 5050
Text GLabel 5900 5250 2    50   Input ~ 0
Reset_Out
$Comp
L Device:R R12
U 1 1 5BB85891
P 5750 4950
F 0 "R12" V 5830 4950 50  0000 C CNN
F 1 "4k7" V 5750 4950 50  0000 C CNN
F 2 "Resistor_SMD:R_1206_3216Metric" V 5680 4950 50  0001 C CNN
F 3 "~" H 5750 4950 50  0001 C CNN
	1    5750 4950
	-1   0    0    1   
$EndComp
Wire Wire Line
	5400 5250 5750 5250
Wire Wire Line
	5750 5100 5750 5250
Connection ~ 5750 5250
Wire Wire Line
	5750 5250 5900 5250
Text GLabel 3250 2000 0    50   Input ~ 0
Reset_A
Text GLabel 3950 2000 2    50   Input ~ 0
Reset_B
$Comp
L Connector_Generic:Conn_02x05_Odd_Even J2
U 1 1 5BBA6294
P 3550 2200
F 0 "J2" H 3600 2617 50  0000 C CNN
F 1 "Conn_02x05_Odd_Even" H 3600 2526 50  0000 C CNN
F 2 "Connector_IDC:IDC-Header_2x05_P2.54mm_Vertical" H 3550 2200 50  0001 C CNN
F 3 "~" H 3550 2200 50  0001 C CNN
	1    3550 2200
	1    0    0    -1  
$EndComp
Text GLabel 3950 2100 2    50   Input ~ 0
Tx_B
Text GLabel 3250 2100 0    50   Input ~ 0
Tx_A
Text GLabel 3250 2200 0    50   Output ~ 0
Rx_A
Text GLabel 3950 2200 2    50   Output ~ 0
Rx_B
Text GLabel 3250 2300 0    50   Input ~ 0
Sync_A
Text GLabel 3950 2300 2    50   Input ~ 0
Sync_B
$Comp
L power:GND #PWR014
U 1 1 5BBA9943
P 3250 2450
F 0 "#PWR014" H 3250 2200 50  0001 C CNN
F 1 "GND" H 3250 2300 50  0000 C CNN
F 2 "" H 3250 2450 50  0001 C CNN
F 3 "" H 3250 2450 50  0001 C CNN
	1    3250 2450
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR020
U 1 1 5BBA9990
P 3950 2450
F 0 "#PWR020" H 3950 2200 50  0001 C CNN
F 1 "GND" H 3950 2300 50  0000 C CNN
F 2 "" H 3950 2450 50  0001 C CNN
F 3 "" H 3950 2450 50  0001 C CNN
	1    3950 2450
	1    0    0    -1  
$EndComp
Wire Wire Line
	3250 2000 3350 2000
Wire Wire Line
	3250 2100 3350 2100
Wire Wire Line
	3350 2200 3250 2200
Wire Wire Line
	3250 2300 3350 2300
Wire Wire Line
	3350 2400 3250 2400
Wire Wire Line
	3250 2400 3250 2450
Wire Wire Line
	3850 2400 3950 2400
Wire Wire Line
	3950 2400 3950 2450
Wire Wire Line
	3950 2300 3850 2300
Wire Wire Line
	3850 2200 3950 2200
Wire Wire Line
	3950 2100 3850 2100
Wire Wire Line
	3850 2000 3950 2000
$Comp
L power:+3.3V #PWR022
U 1 1 5BBFC5BF
P 5750 4650
F 0 "#PWR022" H 5750 4500 50  0001 C CNN
F 1 "+3.3V" H 5750 4790 50  0000 C CNN
F 2 "" H 5750 4650 50  0001 C CNN
F 3 "" H 5750 4650 50  0001 C CNN
	1    5750 4650
	1    0    0    -1  
$EndComp
Wire Wire Line
	5750 4650 5750 4800
Text GLabel 6250 3400 0    50   Input ~ 0
Rx
Text GLabel 10800 3150 2    50   Input ~ 0
Reset
Text GLabel 6250 3200 0    50   Output ~ 0
Tx
Text GLabel 6250 3100 0    50   Output ~ 0
Sync
Wire Wire Line
	5950 3000 6450 3000
Wire Wire Line
	6250 3100 6450 3100
Wire Wire Line
	6450 3200 6250 3200
Wire Wire Line
	6250 3400 6450 3400
Text GLabel 10800 3000 2    50   Output ~ 0
~MCLR
Text GLabel 10800 2850 2    50   Input ~ 0
Vpp
$Comp
L power:+5V #PWR028
U 1 1 5BC2DF3E
P 9950 2550
F 0 "#PWR028" H 9950 2400 50  0001 C CNN
F 1 "+5V" H 9950 2690 50  0000 C CNN
F 2 "" H 9950 2550 50  0001 C CNN
F 3 "" H 9950 2550 50  0001 C CNN
	1    9950 2550
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR029
U 1 1 5BC2DF8B
P 9950 3500
F 0 "#PWR029" H 9950 3250 50  0001 C CNN
F 1 "GND" H 9950 3350 50  0000 C CNN
F 2 "" H 9950 3500 50  0001 C CNN
F 3 "" H 9950 3500 50  0001 C CNN
	1    9950 3500
	1    0    0    -1  
$EndComp
$Comp
L Device:R R23
U 1 1 5BC2DFD8
P 9950 2750
F 0 "R23" V 10030 2750 50  0000 C CNN
F 1 "10k" V 9950 2750 50  0000 C CNN
F 2 "Resistor_SMD:R_1206_3216Metric" V 9880 2750 50  0001 C CNN
F 3 "~" H 9950 2750 50  0001 C CNN
	1    9950 2750
	1    0    0    -1  
$EndComp
$Comp
L Device:C C18
U 1 1 5BC2E050
P 9950 3250
F 0 "C18" H 9975 3350 50  0000 L CNN
F 1 "2.2u" H 9975 3150 50  0000 L CNN
F 2 "Capacitor_SMD:C_1206_3216Metric" H 9988 3100 50  0001 C CNN
F 3 "~" H 9950 3250 50  0001 C CNN
	1    9950 3250
	1    0    0    -1  
$EndComp
Wire Wire Line
	9950 2550 9950 2600
$Comp
L Device:R R22
U 1 1 5BC40325
P 9700 3250
F 0 "R22" V 9780 3250 50  0000 C CNN
F 1 "100k" V 9700 3250 50  0000 C CNN
F 2 "Resistor_SMD:R_1206_3216Metric" V 9630 3250 50  0001 C CNN
F 3 "~" H 9700 3250 50  0001 C CNN
	1    9700 3250
	1    0    0    -1  
$EndComp
Wire Wire Line
	9950 3400 9950 3450
Wire Wire Line
	9950 3450 9700 3450
Wire Wire Line
	9700 3450 9700 3400
Connection ~ 9950 3450
Wire Wire Line
	9950 3450 9950 3500
Wire Wire Line
	9950 2900 9950 3000
Wire Wire Line
	9950 3000 9700 3000
Wire Wire Line
	9700 3000 9700 3100
Connection ~ 9950 3000
Wire Wire Line
	9950 3000 9950 3100
$Comp
L Device:R R25
U 1 1 5BC65394
P 10600 2850
F 0 "R25" V 10680 2850 50  0000 C CNN
F 1 "470E" V 10600 2850 50  0000 C CNN
F 2 "Resistor_SMD:R_1206_3216Metric" V 10530 2850 50  0001 C CNN
F 3 "~" H 10600 2850 50  0001 C CNN
	1    10600 2850
	0    1    1    0   
$EndComp
$Comp
L Device:R R24
U 1 1 5BC6550E
P 10250 3000
F 0 "R24" V 10330 3000 50  0000 C CNN
F 1 "470E" V 10250 3000 50  0000 C CNN
F 2 "Resistor_SMD:R_1206_3216Metric" V 10180 3000 50  0001 C CNN
F 3 "~" H 10250 3000 50  0001 C CNN
	1    10250 3000
	0    1    1    0   
$EndComp
Wire Wire Line
	10100 3000 9950 3000
Wire Wire Line
	10400 3000 10450 3000
Wire Wire Line
	10800 3150 10450 3150
Wire Wire Line
	10450 3150 10450 3000
Connection ~ 10450 3000
Wire Wire Line
	10450 3000 10800 3000
Wire Wire Line
	10450 2850 10450 3000
Wire Wire Line
	10750 2850 10800 2850
$Comp
L Device:R R14
U 1 1 5BCB4849
P 7700 2400
F 0 "R14" V 7650 2250 50  0000 C CNN
F 1 "301E" V 7700 2400 50  0000 C CNN
F 2 "Resistor_SMD:R_1206_3216Metric" V 7630 2400 50  0001 C CNN
F 3 "~" H 7700 2400 50  0001 C CNN
	1    7700 2400
	0    1    1    0   
$EndComp
$Comp
L Device:R R15
U 1 1 5BCB4A35
P 7700 2500
F 0 "R15" V 7650 2350 50  0000 C CNN
F 1 "301E" V 7700 2500 50  0000 C CNN
F 2 "Resistor_SMD:R_1206_3216Metric" V 7630 2500 50  0001 C CNN
F 3 "~" H 7700 2500 50  0001 C CNN
	1    7700 2500
	0    1    1    0   
$EndComp
$Comp
L Device:R R16
U 1 1 5BCB4A95
P 7700 2600
F 0 "R16" V 7650 2450 50  0000 C CNN
F 1 "301E" V 7700 2600 50  0000 C CNN
F 2 "Resistor_SMD:R_1206_3216Metric" V 7630 2600 50  0001 C CNN
F 3 "~" H 7700 2600 50  0001 C CNN
	1    7700 2600
	0    1    1    0   
$EndComp
$Comp
L Device:R R17
U 1 1 5BCB4CD1
P 7700 2700
F 0 "R17" V 7650 2550 50  0000 C CNN
F 1 "301E" V 7700 2700 50  0000 C CNN
F 2 "Resistor_SMD:R_1206_3216Metric" V 7630 2700 50  0001 C CNN
F 3 "~" H 7700 2700 50  0001 C CNN
	1    7700 2700
	0    1    1    0   
$EndComp
$Comp
L Device:R R18
U 1 1 5BCB4D35
P 7700 2800
F 0 "R18" V 7650 2650 50  0000 C CNN
F 1 "301E" V 7700 2800 50  0000 C CNN
F 2 "Resistor_SMD:R_1206_3216Metric" V 7630 2800 50  0001 C CNN
F 3 "~" H 7700 2800 50  0001 C CNN
	1    7700 2800
	0    1    1    0   
$EndComp
Wire Wire Line
	7450 2400 7550 2400
Wire Wire Line
	7550 2500 7450 2500
Wire Wire Line
	7450 2600 7550 2600
Wire Wire Line
	7550 2700 7450 2700
Wire Wire Line
	7450 2800 7550 2800
$Comp
L Device:LED D1
U 1 1 5BCE82A4
P 8050 2400
F 0 "D1" H 7800 2350 50  0000 C CNN
F 1 "LED GR" H 7550 2400 50  0000 C CNN
F 2 "LED_SMD:LED_1206_3216Metric" H 8050 2400 50  0001 C CNN
F 3 "~" H 8050 2400 50  0001 C CNN
	1    8050 2400
	-1   0    0    1   
$EndComp
Wire Wire Line
	7900 2400 7850 2400
$Comp
L Device:LED D2
U 1 1 5BD07CAE
P 8050 2500
F 0 "D2" H 7800 2450 50  0000 C CNN
F 1 "LED YE" H 7550 2500 50  0000 C CNN
F 2 "LED_SMD:LED_1206_3216Metric" H 8050 2500 50  0001 C CNN
F 3 "~" H 8050 2500 50  0001 C CNN
	1    8050 2500
	-1   0    0    1   
$EndComp
$Comp
L Device:LED D3
U 1 1 5BD07D18
P 8050 2600
F 0 "D3" H 7800 2550 50  0000 C CNN
F 1 "LED RD" H 7550 2600 50  0000 C CNN
F 2 "LED_SMD:LED_1206_3216Metric" H 8050 2600 50  0001 C CNN
F 3 "~" H 8050 2600 50  0001 C CNN
	1    8050 2600
	-1   0    0    1   
$EndComp
$Comp
L Device:LED D4
U 1 1 5BD07D84
P 8050 2700
F 0 "D4" H 7800 2650 50  0000 C CNN
F 1 "LED GR" H 7550 2700 50  0000 C CNN
F 2 "LED_SMD:LED_1206_3216Metric" H 8050 2700 50  0001 C CNN
F 3 "~" H 8050 2700 50  0001 C CNN
	1    8050 2700
	-1   0    0    1   
$EndComp
$Comp
L Device:LED D5
U 1 1 5BD07DF2
P 8050 2800
F 0 "D5" H 7800 2750 50  0000 C CNN
F 1 "LED GR" H 7550 2800 50  0000 C CNN
F 2 "LED_SMD:LED_1206_3216Metric" H 8050 2800 50  0001 C CNN
F 3 "~" H 8050 2800 50  0001 C CNN
	1    8050 2800
	-1   0    0    1   
$EndComp
Wire Wire Line
	7850 2500 7900 2500
Wire Wire Line
	7900 2600 7850 2600
Wire Wire Line
	7850 2700 7900 2700
Wire Wire Line
	7900 2800 7850 2800
Wire Wire Line
	8200 2400 8400 2400
Wire Wire Line
	8400 2400 8400 2500
Wire Wire Line
	8200 2800 8400 2800
Connection ~ 8400 2800
Wire Wire Line
	8200 2700 8400 2700
Connection ~ 8400 2700
Wire Wire Line
	8400 2700 8400 2800
Wire Wire Line
	8200 2600 8400 2600
Connection ~ 8400 2600
Wire Wire Line
	8400 2600 8400 2700
Wire Wire Line
	8200 2500 8400 2500
Connection ~ 8400 2500
Wire Wire Line
	8400 2500 8400 2600
Text GLabel 2850 6600 2    50   Input ~ 0
Tx_En
$Comp
L Device:R R5
U 1 1 5BD76BC4
P 2700 6900
F 0 "R5" V 2780 6900 50  0000 C CNN
F 1 "4k7" V 2700 6900 50  0000 C CNN
F 2 "Resistor_SMD:R_1206_3216Metric" V 2630 6900 50  0001 C CNN
F 3 "~" H 2700 6900 50  0001 C CNN
	1    2700 6900
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR08
U 1 1 5BD76C56
P 2700 7150
F 0 "#PWR08" H 2700 6900 50  0001 C CNN
F 1 "GND" H 2700 7000 50  0000 C CNN
F 2 "" H 2700 7150 50  0001 C CNN
F 3 "" H 2700 7150 50  0001 C CNN
	1    2700 7150
	1    0    0    -1  
$EndComp
Wire Wire Line
	2250 6600 2700 6600
Wire Wire Line
	2700 6600 2700 6750
Wire Wire Line
	2700 7050 2700 7150
Wire Wire Line
	2850 6600 2700 6600
Connection ~ 2700 6600
Text GLabel 6250 3300 0    50   Output ~ 0
Tx_En
Wire Wire Line
	6250 3300 6450 3300
Text GLabel 9000 3300 2    50   Output ~ 0
SDO
Text GLabel 9000 2900 2    50   Output ~ 0
SCK1
Text GLabel 9000 3400 2    50   Input ~ 0
SDI
Text GLabel 9000 3200 2    50   Output ~ 0
SS1
Wire Wire Line
	7450 3400 7550 3400
$Comp
L power:+5V #PWR012
U 1 1 5BDDAAC6
P 3150 4450
F 0 "#PWR012" H 3150 4300 50  0001 C CNN
F 1 "+5V" H 3150 4590 50  0000 C CNN
F 2 "" H 3150 4450 50  0001 C CNN
F 3 "" H 3150 4450 50  0001 C CNN
	1    3150 4450
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR013
U 1 1 5BDDAB33
P 3150 5650
F 0 "#PWR013" H 3150 5400 50  0001 C CNN
F 1 "GND" H 3150 5500 50  0000 C CNN
F 2 "" H 3150 5650 50  0001 C CNN
F 3 "" H 3150 5650 50  0001 C CNN
	1    3150 5650
	1    0    0    -1  
$EndComp
$Comp
L Device:R R7
U 1 1 5BDDABA0
P 3150 4650
F 0 "R7" V 3230 4650 50  0000 C CNN
F 1 "3k9" V 3150 4650 50  0000 C CNN
F 2 "Resistor_SMD:R_1206_3216Metric" V 3080 4650 50  0001 C CNN
F 3 "~" H 3150 4650 50  0001 C CNN
	1    3150 4650
	-1   0    0    1   
$EndComp
$Comp
L Device:R R8
U 1 1 5BDDAC2A
P 3150 5050
F 0 "R8" V 3230 5050 50  0000 C CNN
F 1 "120E" V 3150 5050 50  0000 C CNN
F 2 "Resistor_SMD:R_1206_3216Metric" V 3080 5050 50  0001 C CNN
F 3 "~" H 3150 5050 50  0001 C CNN
	1    3150 5050
	-1   0    0    1   
$EndComp
$Comp
L Device:R R9
U 1 1 5BDF45A1
P 3150 5450
F 0 "R9" V 3230 5450 50  0000 C CNN
F 1 "1k00" V 3150 5450 50  0000 C CNN
F 2 "Resistor_SMD:R_1206_3216Metric" V 3080 5450 50  0001 C CNN
F 3 "~" H 3150 5450 50  0001 C CNN
	1    3150 5450
	-1   0    0    1   
$EndComp
Text GLabel 3000 4850 0    50   Output ~ 0
Rx_A
Text GLabel 3000 5250 0    50   Output ~ 0
Rx_B
$Comp
L Device:R R21
U 1 1 5BE426A3
P 8950 2700
F 0 "R21" V 9030 2700 50  0000 C CNN
F 1 "4k7" V 8950 2700 50  0000 C CNN
F 2 "Resistor_SMD:R_1206_3216Metric" V 8880 2700 50  0001 C CNN
F 3 "~" H 8950 2700 50  0001 C CNN
	1    8950 2700
	1    0    0    -1  
$EndComp
$Comp
L Device:R R19
U 1 1 5BE42CCF
P 8500 3700
F 0 "R19" V 8580 3700 50  0000 C CNN
F 1 "4k7" V 8500 3700 50  0000 C CNN
F 2 "Resistor_SMD:R_1206_3216Metric" V 8430 3700 50  0001 C CNN
F 3 "~" H 8500 3700 50  0001 C CNN
	1    8500 3700
	1    0    0    -1  
$EndComp
$Comp
L Device:C C14
U 1 1 5BE42DBF
P 7550 3700
F 0 "C14" H 7575 3800 50  0000 L CNN
F 1 "22p" H 7575 3600 50  0000 L CNN
F 2 "Capacitor_SMD:C_1206_3216Metric" H 7588 3550 50  0001 C CNN
F 3 "~" H 7550 3700 50  0001 C CNN
	1    7550 3700
	1    0    0    -1  
$EndComp
$Comp
L Device:C C16
U 1 1 5BE432AF
P 7950 3700
F 0 "C16" H 7975 3800 50  0000 L CNN
F 1 "22p" H 7975 3600 50  0000 L CNN
F 2 "Capacitor_SMD:C_1206_3216Metric" H 7988 3550 50  0001 C CNN
F 3 "~" H 7950 3700 50  0001 C CNN
	1    7950 3700
	1    0    0    -1  
$EndComp
Wire Wire Line
	7450 3200 7950 3200
Text GLabel 3950 1350 2    50   Input ~ 0
SCK1
Text GLabel 3950 1150 2    50   Input ~ 0
SS1
Text GLabel 3950 950  2    50   Input ~ 0
SDO
Text GLabel 3950 750  2    50   Output ~ 0
SDI
Text GLabel 4550 600  0    50   Output ~ 0
Reset_Out
$Comp
L power:GND #PWR021
U 1 1 5C082EC8
P 3900 1500
F 0 "#PWR021" H 3900 1250 50  0001 C CNN
F 1 "GND" H 3900 1350 50  0000 C CNN
F 2 "" H 3900 1500 50  0001 C CNN
F 3 "" H 3900 1500 50  0001 C CNN
	1    3900 1500
	1    0    0    -1  
$EndComp
NoConn ~ 7450 3100
$Comp
L power:GND #PWR026
U 1 1 5BE43337
P 8400 3950
F 0 "#PWR026" H 8400 3700 50  0001 C CNN
F 1 "GND" H 8400 3800 50  0000 C CNN
F 2 "" H 8400 3950 50  0001 C CNN
F 3 "" H 8400 3950 50  0001 C CNN
	1    8400 3950
	1    0    0    -1  
$EndComp
$Comp
L Device:C C15
U 1 1 5C160BF6
P 7750 3700
F 0 "C15" H 7775 3800 50  0000 L CNN
F 1 "22p" H 7775 3600 50  0000 L CNN
F 2 "Capacitor_SMD:C_1206_3216Metric" H 7788 3550 50  0001 C CNN
F 3 "~" H 7750 3700 50  0001 C CNN
	1    7750 3700
	1    0    0    -1  
$EndComp
$Comp
L Device:C C17
U 1 1 5C160D46
P 8150 3700
F 0 "C17" H 8175 3800 50  0000 L CNN
F 1 "22p" H 8175 3600 50  0000 L CNN
F 2 "Capacitor_SMD:C_1206_3216Metric" H 8188 3550 50  0001 C CNN
F 3 "~" H 8150 3700 50  0001 C CNN
	1    8150 3700
	1    0    0    -1  
$EndComp
Wire Wire Line
	8400 3900 8150 3900
Wire Wire Line
	7550 3900 7550 3850
Connection ~ 8400 3900
Wire Wire Line
	8400 3900 8400 3950
Wire Wire Line
	7750 3850 7750 3900
Connection ~ 7750 3900
Wire Wire Line
	7750 3900 7550 3900
Wire Wire Line
	7950 3850 7950 3900
Connection ~ 7950 3900
Wire Wire Line
	7950 3900 7750 3900
Wire Wire Line
	8150 3850 8150 3900
Connection ~ 8150 3900
Wire Wire Line
	8150 3900 7950 3900
Wire Wire Line
	7550 3400 7550 3550
Connection ~ 7550 3400
Wire Wire Line
	7750 3550 7750 3300
Wire Wire Line
	7750 3300 7450 3300
Connection ~ 7750 3300
Wire Wire Line
	7950 3550 7950 3200
Connection ~ 7950 3200
Wire Wire Line
	8400 2800 8400 3900
Wire Wire Line
	7450 2900 8150 2900
Wire Wire Line
	8150 3550 8150 2900
Wire Wire Line
	7950 3200 8950 3200
$Comp
L power:+5V #PWR027
U 1 1 5C2B698F
P 8950 2450
F 0 "#PWR027" H 8950 2300 50  0001 C CNN
F 1 "+5V" H 8950 2590 50  0000 C CNN
F 2 "" H 8950 2450 50  0001 C CNN
F 3 "" H 8950 2450 50  0001 C CNN
	1    8950 2450
	1    0    0    -1  
$EndComp
Wire Wire Line
	8950 2450 8950 2550
Wire Wire Line
	8950 2850 8950 3200
Connection ~ 8950 3200
Wire Wire Line
	8950 3200 9000 3200
Wire Wire Line
	9000 2900 8800 2900
Connection ~ 8150 2900
Wire Wire Line
	7600 2200 7450 2200
Wire Wire Line
	7450 2300 7600 2300
Wire Wire Line
	3150 4800 3150 4850
Wire Wire Line
	3000 4850 3150 4850
Connection ~ 3150 4850
Wire Wire Line
	3150 4850 3150 4900
Wire Wire Line
	3150 5200 3150 5250
Wire Wire Line
	3000 5250 3150 5250
Connection ~ 3150 5250
Wire Wire Line
	3150 5250 3150 5300
Wire Wire Line
	3150 5600 3150 5650
$Comp
L Device:R R20
U 1 1 5BC13326
P 8650 3700
F 0 "R20" V 8730 3700 50  0000 C CNN
F 1 "4k7" V 8650 3700 50  0000 C CNN
F 2 "Resistor_SMD:R_1206_3216Metric" V 8580 3700 50  0001 C CNN
F 3 "~" H 8650 3700 50  0001 C CNN
	1    8650 3700
	1    0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_02x08_Odd_Even J3
U 1 1 5BCE4FFE
P 4850 1050
F 0 "J3" H 4900 1450 50  0000 C CNN
F 1 "Conn_02x08_Top_Bottom" V 4900 50  50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_2x08_P2.54mm_Vertical" H 4850 1050 50  0001 C CNN
F 3 "~" H 4850 1050 50  0001 C CNN
	1    4850 1050
	1    0    0    -1  
$EndComp
Wire Wire Line
	4550 600  4650 600 
Wire Wire Line
	4650 600  4650 750 
Wire Wire Line
	3900 1500 3900 1450
Wire Wire Line
	3900 850  3850 850 
Wire Wire Line
	3850 1050 3900 1050
Connection ~ 3900 1050
Wire Wire Line
	3900 1050 3900 850 
Wire Wire Line
	3850 1250 3900 1250
Connection ~ 3900 1250
Wire Wire Line
	3900 1250 3900 1050
Wire Wire Line
	3850 1450 3900 1450
Connection ~ 3900 1450
Wire Wire Line
	3900 1450 3900 1250
NoConn ~ 4650 1450
NoConn ~ 4650 1350
NoConn ~ 4650 1250
NoConn ~ 4650 1150
NoConn ~ 4650 1050
NoConn ~ 4650 950 
NoConn ~ 4650 850 
Wire Wire Line
	3950 750  3850 750 
Wire Wire Line
	3850 950  3950 950 
Wire Wire Line
	3950 1150 3850 1150
Wire Wire Line
	3850 1350 3950 1350
$Comp
L Device:R R26
U 1 1 5BF74538
P 8800 3700
F 0 "R26" V 8880 3700 50  0000 C CNN
F 1 "4k7" V 8800 3700 50  0000 C CNN
F 2 "Resistor_SMD:R_1206_3216Metric" V 8730 3700 50  0001 C CNN
F 3 "~" H 8800 3700 50  0001 C CNN
	1    8800 3700
	1    0    0    -1  
$EndComp
Wire Wire Line
	7550 3400 8500 3400
Wire Wire Line
	7750 3300 8650 3300
Wire Wire Line
	8400 3900 8500 3900
Wire Wire Line
	8500 3850 8500 3900
Connection ~ 8500 3900
Wire Wire Line
	8500 3900 8650 3900
Wire Wire Line
	8650 3850 8650 3900
Connection ~ 8650 3900
Wire Wire Line
	8800 3900 8800 3850
Wire Wire Line
	8650 3900 8800 3900
Wire Wire Line
	8500 3550 8500 3400
Connection ~ 8500 3400
Wire Wire Line
	8500 3400 9000 3400
Wire Wire Line
	8650 3550 8650 3300
Connection ~ 8650 3300
Wire Wire Line
	8650 3300 9000 3300
Wire Wire Line
	8800 3550 8800 2900
Connection ~ 8800 2900
Wire Wire Line
	8800 2900 8150 2900
Wire Wire Line
	5500 1350 5600 1350
Wire Wire Line
	5500 2300 5500 1350
Wire Wire Line
	5200 2900 5200 850 
Wire Wire Line
	5300 2700 5300 950 
Wire Wire Line
	5400 1150 5600 1150
Wire Wire Line
	5400 2500 5400 1150
Wire Wire Line
	5300 950  5600 950 
Wire Wire Line
	5200 850  5600 850 
Wire Wire Line
	5250 750  5600 750 
Wire Wire Line
	5250 2800 5250 750 
Wire Wire Line
	5350 1050 5600 1050
Wire Wire Line
	5350 2600 5350 1050
Wire Wire Line
	5450 1250 5600 1250
Wire Wire Line
	5450 2400 5450 1250
Wire Wire Line
	5550 1450 5600 1450
Wire Wire Line
	5550 2200 5550 1450
Wire Wire Line
	6450 2500 5400 2500
Wire Wire Line
	6450 2800 5250 2800
Wire Wire Line
	6450 2900 5200 2900
Wire Wire Line
	6450 2700 5300 2700
Wire Wire Line
	6450 2600 5350 2600
Wire Wire Line
	6450 2400 5450 2400
Wire Wire Line
	6450 2300 5500 2300
Wire Wire Line
	6450 2200 5550 2200
$Comp
L Connector_Generic:Conn_01x08 J4
U 1 1 5BEE2E25
P 5800 1050
F 0 "J4" H 5880 1042 50  0000 L CNN
F 1 "Conn_01x08" H 5880 951 50  0000 L CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x08_P2.54mm_Vertical" H 5800 1050 50  0001 C CNN
F 3 "~" H 5800 1050 50  0001 C CNN
	1    5800 1050
	1    0    0    -1  
$EndComp
NoConn ~ 5150 1450
NoConn ~ 5150 1350
NoConn ~ 5150 1250
NoConn ~ 5150 1150
NoConn ~ 5150 1050
NoConn ~ 5150 950 
NoConn ~ 5150 850 
NoConn ~ 5150 750 
$EndSCHEMATC
