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
L Connector_Generic:Conn_02x08_Top_Bottom J?
U 1 1 5BCE4FC3
P 3550 1050
F 0 "J?" H 3600 1450 50  0000 C CNN
F 1 "Conn_02x08_Top_Bottom" H 3600 550 50  0000 C CNN
F 2 "" H 3550 1050 50  0001 C CNN
F 3 "~" H 3550 1050 50  0001 C CNN
	1    3550 1050
	1    0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_02x08_Top_Bottom J?
U 1 1 5BCE4FFE
P 3550 2200
F 0 "J?" H 3600 2600 50  0000 C CNN
F 1 "Conn_02x08_Top_Bottom" H 3600 1700 50  0000 C CNN
F 2 "" H 3550 2200 50  0001 C CNN
F 3 "~" H 3550 2200 50  0001 C CNN
	1    3550 2200
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5BCE50C5
P 3050 1550
F 0 "#PWR?" H 3050 1300 50  0001 C CNN
F 1 "GND" H 3050 1400 50  0000 C CNN
F 2 "" H 3050 1550 50  0001 C CNN
F 3 "" H 3050 1550 50  0001 C CNN
	1    3050 1550
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR?
U 1 1 5BCE5123
P 2900 700
F 0 "#PWR?" H 2900 550 50  0001 C CNN
F 1 "+5V" H 2900 840 50  0000 C CNN
F 2 "" H 2900 700 50  0001 C CNN
F 3 "" H 2900 700 50  0001 C CNN
	1    2900 700 
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR?
U 1 1 5BCE517A
P 2650 700
F 0 "#PWR?" H 2650 550 50  0001 C CNN
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
L MCU_Microchip_PIC16:PIC16F18854-SO U?
U 1 1 5BCE5566
P 6450 2700
F 0 "U?" H 6100 3450 50  0000 C CNN
F 1 "PIC16F18854-SO" H 6850 3450 50  0000 C CNN
F 2 "Package_SO:SOIC-28W_7.5x17.9mm_P1.27mm" H 6450 1600 50  0001 C CNN
F 3 "http://ww1.microchip.com/downloads/en/DeviceDoc/PIC16(L)F18854%20Data%20Sheet_DS40001826C.pdf" H 6750 2100 50  0001 C CNN
	1    6450 2700
	1    0    0    -1  
$EndComp
$Comp
L Device:R R?
U 1 1 5BCE55D2
P 6000 950
F 0 "R?" V 6080 950 50  0000 C CNN
F 1 "1E" V 6000 950 50  0000 C CNN
F 2 "Resistor_SMD:R_1206_3216Metric" V 5930 950 50  0001 C CNN
F 3 "~" H 6000 950 50  0001 C CNN
	1    6000 950 
	1    0    0    -1  
$EndComp
$Comp
L Device:C C?
U 1 1 5BCE56E1
P 6000 1350
F 0 "C?" H 6025 1450 50  0000 L CNN
F 1 "2.2u" H 6025 1250 50  0000 L CNN
F 2 "Capacitor_SMD:C_1206_3216Metric" H 6038 1200 50  0001 C CNN
F 3 "~" H 6000 1350 50  0001 C CNN
	1    6000 1350
	1    0    0    -1  
$EndComp
$Comp
L Device:C C?
U 1 1 5BCE5735
P 6200 1350
F 0 "C?" H 6225 1450 50  0000 L CNN
F 1 "100n" H 6225 1250 50  0000 L CNN
F 2 "Capacitor_SMD:C_1206_3216Metric" H 6238 1200 50  0001 C CNN
F 3 "~" H 6200 1350 50  0001 C CNN
	1    6200 1350
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5BCE5793
P 6000 1600
F 0 "#PWR?" H 6000 1350 50  0001 C CNN
F 1 "GND" H 6000 1450 50  0000 C CNN
F 2 "" H 6000 1600 50  0001 C CNN
F 3 "" H 6000 1600 50  0001 C CNN
	1    6000 1600
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR?
U 1 1 5BCE57EE
P 6000 750
F 0 "#PWR?" H 6000 600 50  0001 C CNN
F 1 "+5V" H 6000 890 50  0000 C CNN
F 2 "" H 6000 750 50  0001 C CNN
F 3 "" H 6000 750 50  0001 C CNN
	1    6000 750 
	1    0    0    -1  
$EndComp
Wire Wire Line
	6000 750  6000 800 
Wire Wire Line
	6000 1100 6000 1150
Wire Wire Line
	6200 1200 6200 1150
Wire Wire Line
	6200 1150 6000 1150
Connection ~ 6000 1150
Wire Wire Line
	6000 1150 6000 1200
Wire Wire Line
	6000 1500 6000 1550
Wire Wire Line
	6200 1500 6200 1550
Wire Wire Line
	6200 1550 6000 1550
Connection ~ 6000 1550
Wire Wire Line
	6000 1550 6000 1600
Wire Wire Line
	6450 1150 6450 1900
Connection ~ 6200 1150
Wire Wire Line
	6200 1150 6450 1150
$Comp
L power:GND #PWR?
U 1 1 5BCE6BFB
P 6450 3650
F 0 "#PWR?" H 6450 3400 50  0001 C CNN
F 1 "GND" H 6450 3500 50  0000 C CNN
F 2 "" H 6450 3650 50  0001 C CNN
F 3 "" H 6450 3650 50  0001 C CNN
	1    6450 3650
	1    0    0    -1  
$EndComp
Wire Wire Line
	6450 3650 6450 3500
$Comp
L Connector_Generic:Conn_01x08 J?
U 1 1 5BCE6F4B
P 10750 1500
F 0 "J?" H 10750 1900 50  0000 C CNN
F 1 "Conn_01x08" H 10750 1000 50  0000 C CNN
F 2 "" H 10750 1500 50  0001 C CNN
F 3 "~" H 10750 1500 50  0001 C CNN
	1    10750 1500
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR?
U 1 1 5BCE706E
P 10450 1050
F 0 "#PWR?" H 10450 900 50  0001 C CNN
F 1 "+5V" H 10450 1190 50  0000 C CNN
F 2 "" H 10450 1050 50  0001 C CNN
F 3 "" H 10450 1050 50  0001 C CNN
	1    10450 1050
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5BCE7087
P 10450 2150
F 0 "#PWR?" H 10450 1900 50  0001 C CNN
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
Text GLabel 5300 2900 0    50   Input ~ 0
~MCLR
Wire Wire Line
	5950 2900 5300 2900
Text GLabel 7850 2100 2    50   BiDi ~ 0
ICSPDAT
Text GLabel 7850 2200 2    50   Input ~ 0
ICSPCLK
Wire Wire Line
	6950 2100 7850 2100
Wire Wire Line
	7850 2200 6950 2200
$Comp
L Interface_UART:ST485EBDR U?
U 1 1 5BCEAD9E
P 1850 3600
F 0 "U?" H 1600 3950 50  0000 C CNN
F 1 "ST485EBDR" H 1950 3950 50  0000 L CNN
F 2 "Package_SO:SOIC-8_3.9x4.9mm_P1.27mm" H 1850 2700 50  0001 C CNN
F 3 "http://www.st.com/resource/en/datasheet/st485eb.pdf" H 1850 3650 50  0001 C CNN
	1    1850 3600
	-1   0    0    -1  
$EndComp
$Comp
L Device:R R?
U 1 1 5BCEBE99
P 700 3200
F 0 "R?" V 780 3200 50  0000 C CNN
F 1 "1E" V 700 3200 50  0000 C CNN
F 2 "Resistor_SMD:R_1206_3216Metric" V 630 3200 50  0001 C CNN
F 3 "~" H 700 3200 50  0001 C CNN
	1    700  3200
	1    0    0    -1  
$EndComp
$Comp
L Device:C C?
U 1 1 5BCEBE9F
P 700 3600
F 0 "C?" H 725 3700 50  0000 L CNN
F 1 "2.2u" H 725 3500 50  0000 L CNN
F 2 "Capacitor_SMD:C_1206_3216Metric" H 738 3450 50  0001 C CNN
F 3 "~" H 700 3600 50  0001 C CNN
	1    700  3600
	1    0    0    -1  
$EndComp
$Comp
L Device:C C?
U 1 1 5BCEBEA5
P 900 3600
F 0 "C?" H 925 3700 50  0000 L CNN
F 1 "100n" H 925 3500 50  0000 L CNN
F 2 "Capacitor_SMD:C_1206_3216Metric" H 938 3450 50  0001 C CNN
F 3 "~" H 900 3600 50  0001 C CNN
	1    900  3600
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5BCEBEAB
P 700 3950
F 0 "#PWR?" H 700 3700 50  0001 C CNN
F 1 "GND" H 700 3800 50  0000 C CNN
F 2 "" H 700 3950 50  0001 C CNN
F 3 "" H 700 3950 50  0001 C CNN
	1    700  3950
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR?
U 1 1 5BCEBEB1
P 700 3000
F 0 "#PWR?" H 700 2850 50  0001 C CNN
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
L Device:R R?
U 1 1 5BCF3B62
P 2550 3500
F 0 "R?" V 2630 3500 50  0000 C CNN
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
L Device:R R?
U 1 1 5BCF7A9A
P 2750 3700
F 0 "R?" V 2830 3700 50  0000 C CNN
F 1 "10k" V 2750 3700 50  0000 C CNN
F 2 "Resistor_SMD:R_1206_3216Metric" V 2680 3700 50  0001 C CNN
F 3 "~" H 2750 3700 50  0001 C CNN
	1    2750 3700
	-1   0    0    1   
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5BCF7ADB
P 2750 3950
F 0 "#PWR?" H 2750 3700 50  0001 C CNN
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
L Device:C C?
U 1 1 5BCFA0DF
P 2950 3700
F 0 "C?" H 2975 3800 50  0000 L CNN
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
L Device:Q_NMOS_GSD Q?
U 1 1 5BCFF801
P 3300 3500
F 0 "Q?" H 3500 3550 50  0000 L CNN
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
L power:GND #PWR?
U 1 1 5BD01049
P 3400 3950
F 0 "#PWR?" H 3400 3700 50  0001 C CNN
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
L Interface_UART:ST485EBDR U?
U 1 1 5BD0430D
P 1850 5050
F 0 "U?" H 1600 5400 50  0000 C CNN
F 1 "ST485EBDR" H 1950 5400 50  0000 L CNN
F 2 "Package_SO:SOIC-8_3.9x4.9mm_P1.27mm" H 1850 4150 50  0001 C CNN
F 3 "http://www.st.com/resource/en/datasheet/st485eb.pdf" H 1850 5100 50  0001 C CNN
	1    1850 5050
	-1   0    0    -1  
$EndComp
$Comp
L Device:R R?
U 1 1 5BD04314
P 700 4650
F 0 "R?" V 780 4650 50  0000 C CNN
F 1 "1E" V 700 4650 50  0000 C CNN
F 2 "Resistor_SMD:R_1206_3216Metric" V 630 4650 50  0001 C CNN
F 3 "~" H 700 4650 50  0001 C CNN
	1    700  4650
	1    0    0    -1  
$EndComp
$Comp
L Device:C C?
U 1 1 5BD0431B
P 700 5050
F 0 "C?" H 725 5150 50  0000 L CNN
F 1 "2.2u" H 725 4950 50  0000 L CNN
F 2 "Capacitor_SMD:C_1206_3216Metric" H 738 4900 50  0001 C CNN
F 3 "~" H 700 5050 50  0001 C CNN
	1    700  5050
	1    0    0    -1  
$EndComp
$Comp
L Device:C C?
U 1 1 5BD04322
P 900 5050
F 0 "C?" H 925 5150 50  0000 L CNN
F 1 "100n" H 925 4950 50  0000 L CNN
F 2 "Capacitor_SMD:C_1206_3216Metric" H 938 4900 50  0001 C CNN
F 3 "~" H 900 5050 50  0001 C CNN
	1    900  5050
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5BD04329
P 700 5400
F 0 "#PWR?" H 700 5150 50  0001 C CNN
F 1 "GND" H 700 5250 50  0000 C CNN
F 2 "" H 700 5400 50  0001 C CNN
F 3 "" H 700 5400 50  0001 C CNN
	1    700  5400
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR?
U 1 1 5BD0432F
P 700 4450
F 0 "#PWR?" H 700 4300 50  0001 C CNN
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
Reset_B
Text GLabel 1400 5250 0    50   Input ~ 0
Reset_A
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
L Interface_UART:ST485EBDR U?
U 1 1 5BD0A572
P 1850 6500
F 0 "U?" H 1600 6850 50  0000 C CNN
F 1 "ST485EBDR" H 1950 6850 50  0000 L CNN
F 2 "Package_SO:SOIC-8_3.9x4.9mm_P1.27mm" H 1850 5600 50  0001 C CNN
F 3 "http://www.st.com/resource/en/datasheet/st485eb.pdf" H 1850 6550 50  0001 C CNN
	1    1850 6500
	-1   0    0    -1  
$EndComp
$Comp
L Device:R R?
U 1 1 5BD0A579
P 700 6100
F 0 "R?" V 780 6100 50  0000 C CNN
F 1 "1E" V 700 6100 50  0000 C CNN
F 2 "Resistor_SMD:R_1206_3216Metric" V 630 6100 50  0001 C CNN
F 3 "~" H 700 6100 50  0001 C CNN
	1    700  6100
	1    0    0    -1  
$EndComp
$Comp
L Device:C C?
U 1 1 5BD0A580
P 700 6500
F 0 "C?" H 725 6600 50  0000 L CNN
F 1 "2.2u" H 725 6400 50  0000 L CNN
F 2 "Capacitor_SMD:C_1206_3216Metric" H 738 6350 50  0001 C CNN
F 3 "~" H 700 6500 50  0001 C CNN
	1    700  6500
	1    0    0    -1  
$EndComp
$Comp
L Device:C C?
U 1 1 5BD0A587
P 900 6500
F 0 "C?" H 925 6600 50  0000 L CNN
F 1 "100n" H 925 6400 50  0000 L CNN
F 2 "Capacitor_SMD:C_1206_3216Metric" H 938 6350 50  0001 C CNN
F 3 "~" H 900 6500 50  0001 C CNN
	1    900  6500
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5BD0A58E
P 700 6850
F 0 "#PWR?" H 700 6600 50  0001 C CNN
F 1 "GND" H 700 6700 50  0000 C CNN
F 2 "" H 700 6850 50  0001 C CNN
F 3 "" H 700 6850 50  0001 C CNN
	1    700  6850
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR?
U 1 1 5BD0A594
P 700 5900
F 0 "#PWR?" H 700 5750 50  0001 C CNN
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
Wire Wire Line
	2250 6600 2350 6600
Wire Wire Line
	2350 6600 2350 6500
Connection ~ 2350 6500
Text GLabel 2450 6700 2    50   Input ~ 0
Tx
Wire Wire Line
	2450 6700 2250 6700
$Comp
L Interface_UART:ST485EBDR U?
U 1 1 5BD29C15
P 4550 6500
F 0 "U?" H 4300 6850 50  0000 C CNN
F 1 "ST485EBDR" H 4650 6850 50  0000 L CNN
F 2 "Package_SO:SOIC-8_3.9x4.9mm_P1.27mm" H 4550 5600 50  0001 C CNN
F 3 "http://www.st.com/resource/en/datasheet/st485eb.pdf" H 4550 6550 50  0001 C CNN
	1    4550 6500
	-1   0    0    -1  
$EndComp
$Comp
L Device:R R?
U 1 1 5BD29C1C
P 3400 6100
F 0 "R?" V 3480 6100 50  0000 C CNN
F 1 "1E" V 3400 6100 50  0000 C CNN
F 2 "Resistor_SMD:R_1206_3216Metric" V 3330 6100 50  0001 C CNN
F 3 "~" H 3400 6100 50  0001 C CNN
	1    3400 6100
	1    0    0    -1  
$EndComp
$Comp
L Device:C C?
U 1 1 5BD29C23
P 3400 6500
F 0 "C?" H 3425 6600 50  0000 L CNN
F 1 "2.2u" H 3425 6400 50  0000 L CNN
F 2 "Capacitor_SMD:C_1206_3216Metric" H 3438 6350 50  0001 C CNN
F 3 "~" H 3400 6500 50  0001 C CNN
	1    3400 6500
	1    0    0    -1  
$EndComp
$Comp
L Device:C C?
U 1 1 5BD29C2A
P 3600 6500
F 0 "C?" H 3625 6600 50  0000 L CNN
F 1 "100n" H 3625 6400 50  0000 L CNN
F 2 "Capacitor_SMD:C_1206_3216Metric" H 3638 6350 50  0001 C CNN
F 3 "~" H 3600 6500 50  0001 C CNN
	1    3600 6500
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5BD29C31
P 3400 6850
F 0 "#PWR?" H 3400 6600 50  0001 C CNN
F 1 "GND" H 3400 6700 50  0000 C CNN
F 2 "" H 3400 6850 50  0001 C CNN
F 3 "" H 3400 6850 50  0001 C CNN
	1    3400 6850
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR?
U 1 1 5BD29C37
P 3400 5900
F 0 "#PWR?" H 3400 5750 50  0001 C CNN
F 1 "+5V" H 3400 6040 50  0000 C CNN
F 2 "" H 3400 5900 50  0001 C CNN
F 3 "" H 3400 5900 50  0001 C CNN
	1    3400 5900
	1    0    0    -1  
$EndComp
Wire Wire Line
	3400 5900 3400 5950
Wire Wire Line
	3400 6250 3400 6300
Wire Wire Line
	3600 6350 3600 6300
Wire Wire Line
	3600 6300 3400 6300
Connection ~ 3400 6300
Wire Wire Line
	3400 6300 3400 6350
Wire Wire Line
	3400 6650 3400 6700
Wire Wire Line
	3600 6650 3600 6700
Wire Wire Line
	3600 6700 3400 6700
Connection ~ 3400 6700
Wire Wire Line
	4550 6100 4550 6000
Wire Wire Line
	4550 6000 3600 6000
Wire Wire Line
	3600 6000 3600 6300
Connection ~ 3600 6300
Wire Wire Line
	4550 7000 4550 7050
Wire Wire Line
	4550 7050 3600 7050
Wire Wire Line
	3600 7050 3600 6700
Connection ~ 3600 6700
Text GLabel 4100 6400 0    50   Output ~ 0
Tx_B
Text GLabel 4100 6700 0    50   Output ~ 0
Tx_A
Wire Wire Line
	4150 6400 4100 6400
Wire Wire Line
	4150 6700 4100 6700
Wire Wire Line
	3400 6700 3400 6850
NoConn ~ 4950 6400
Wire Wire Line
	4550 6000 5050 6000
Wire Wire Line
	5050 6000 5050 6500
Wire Wire Line
	5050 6500 4950 6500
Connection ~ 4550 6000
Wire Wire Line
	4950 6600 5050 6600
Wire Wire Line
	5050 6600 5050 6500
Connection ~ 5050 6500
Text GLabel 5150 6700 2    50   Input ~ 0
Tx
Wire Wire Line
	5150 6700 4950 6700
$Comp
L Interface_UART:ST485EBDR U?
U 1 1 5BD2F9D2
P 4550 5050
F 0 "U?" H 4300 5400 50  0000 C CNN
F 1 "ST485EBDR" H 4650 5400 50  0000 L CNN
F 2 "Package_SO:SOIC-8_3.9x4.9mm_P1.27mm" H 4550 4150 50  0001 C CNN
F 3 "http://www.st.com/resource/en/datasheet/st485eb.pdf" H 4550 5100 50  0001 C CNN
	1    4550 5050
	-1   0    0    -1  
$EndComp
$Comp
L Device:R R?
U 1 1 5BD2F9D9
P 3400 4650
F 0 "R?" V 3480 4650 50  0000 C CNN
F 1 "1E" V 3400 4650 50  0000 C CNN
F 2 "Resistor_SMD:R_1206_3216Metric" V 3330 4650 50  0001 C CNN
F 3 "~" H 3400 4650 50  0001 C CNN
	1    3400 4650
	1    0    0    -1  
$EndComp
$Comp
L Device:C C?
U 1 1 5BD2F9E0
P 3400 5050
F 0 "C?" H 3425 5150 50  0000 L CNN
F 1 "2.2u" H 3425 4950 50  0000 L CNN
F 2 "Capacitor_SMD:C_1206_3216Metric" H 3438 4900 50  0001 C CNN
F 3 "~" H 3400 5050 50  0001 C CNN
	1    3400 5050
	1    0    0    -1  
$EndComp
$Comp
L Device:C C?
U 1 1 5BD2F9E7
P 3600 5050
F 0 "C?" H 3625 5150 50  0000 L CNN
F 1 "100n" H 3625 4950 50  0000 L CNN
F 2 "Capacitor_SMD:C_1206_3216Metric" H 3638 4900 50  0001 C CNN
F 3 "~" H 3600 5050 50  0001 C CNN
	1    3600 5050
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5BD2F9EE
P 3400 5400
F 0 "#PWR?" H 3400 5150 50  0001 C CNN
F 1 "GND" H 3400 5250 50  0000 C CNN
F 2 "" H 3400 5400 50  0001 C CNN
F 3 "" H 3400 5400 50  0001 C CNN
	1    3400 5400
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR?
U 1 1 5BD2F9F4
P 3400 4450
F 0 "#PWR?" H 3400 4300 50  0001 C CNN
F 1 "+5V" H 3400 4590 50  0000 C CNN
F 2 "" H 3400 4450 50  0001 C CNN
F 3 "" H 3400 4450 50  0001 C CNN
	1    3400 4450
	1    0    0    -1  
$EndComp
Wire Wire Line
	3400 4450 3400 4500
Wire Wire Line
	3400 4800 3400 4850
Wire Wire Line
	3600 4900 3600 4850
Wire Wire Line
	3600 4850 3400 4850
Connection ~ 3400 4850
Wire Wire Line
	3400 4850 3400 4900
Wire Wire Line
	3400 5200 3400 5250
Wire Wire Line
	3600 5200 3600 5250
Wire Wire Line
	3600 5250 3400 5250
Connection ~ 3400 5250
Wire Wire Line
	4550 4650 4550 4550
Wire Wire Line
	4550 4550 3600 4550
Wire Wire Line
	3600 4550 3600 4850
Connection ~ 3600 4850
Wire Wire Line
	4550 5550 4550 5600
Wire Wire Line
	4550 5600 3600 5600
Wire Wire Line
	3600 5600 3600 5250
Connection ~ 3600 5250
Text GLabel 4100 4950 0    50   Output ~ 0
Tx_B
Text GLabel 4100 5250 0    50   Output ~ 0
Tx_A
Wire Wire Line
	4150 4950 4100 4950
Wire Wire Line
	4150 5250 4100 5250
Wire Wire Line
	3400 5250 3400 5400
NoConn ~ 4950 4950
Wire Wire Line
	4550 4550 5050 4550
Wire Wire Line
	5050 4550 5050 5050
Wire Wire Line
	5050 5050 4950 5050
Connection ~ 4550 4550
Wire Wire Line
	4950 5150 5050 5150
Wire Wire Line
	5050 5150 5050 5050
Connection ~ 5050 5050
Text GLabel 5150 5250 2    50   Input ~ 0
Tx
Wire Wire Line
	5150 5250 4950 5250
$EndSCHEMATC
