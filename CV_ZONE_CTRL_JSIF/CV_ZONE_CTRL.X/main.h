#ifndef __Main_H
#define __Main_H

#include "p18cxxx.h"

#define Led1                        PORTBbits.RB5				// Activity status Led
#define vlv0                        PORTDbits.RD2				// Valve 1 output
#define vlv1                        PORTDbits.RD3				// Valve 2 output
#define nc                          PORTCbits.RC3				// Not connected
#define vlv2                        PORTCbits.RC4				// Valve 3 output
#define vlv3                        PORTCbits.RC5				// Valve 4 output
#define vlv4                        PORTCbits.RC6				// Valve 5 output
#define vlv5                        PORTCbits.RC7				// Valve 6 output
#define vlv6                        PORTDbits.RD4				// Valve 7 output
#define vlv7                        PORTDbits.RD5				// Valve 8 output
#define vlv8                        PORTDbits.RD6				// Valve 9 output
#define vlv9                        PORTDbits.RD7				// Valve 10 output
#define vlv10                       PORTBbits.RB0				// Valve 11 output
#define vlv11                       PORTBbits.RB1				// Valve 12 output
#define cv_o                        PORTBbits.RB2				// Central Heating contact
#define pmp1_o                      PORTBbits.RB4				// Pump2 output
#define pmp0_o                      PORTBbits.RB3				// Pump1 output
#define pmp0_en                     PORTBbits.RB6				// Pump1 enable via diode OR-port
#define pmp1_en                     PORTBbits.RB7				// Pump2 enable via diode OR-port

#define term0                       PORTAbits.RA2       			// Termostat 1 input
#define term1                       PORTAbits.RA3       			// Termostat 2 input
#define term2                       PORTAbits.RA4       			// Termostat 3 input
#define term3                       PORTAbits.RA5       			// Termostat 4 input
#define term4                       PORTEbits.RE0       			// Termostat 5 input
#define term5                       PORTEbits.RE1       			// Termostat 6 input
#define term6                       PORTEbits.RE2       			// Termostat 7 input
#define term7                       PORTCbits.RC0       			// Termostat 8 input
#define term8                       PORTCbits.RC1       			// Termostat 9 input
#define term9                       PORTCbits.RC2       			// Termostat 10 input
#define term10                      PORTDbits.RD0       			// Termostat 11 input
#define term11                      PORTDbits.RD1       			// Termostat 12 input
						
//#define p2                        PORTAbits.RA0       			// Pump2 mode AN input for protectin mode and delay time
//#define p1                        PORTAbits.RA1       			// Pump1 mode AN input for protectin mode and delay time

#define ON  1
#define OFF 0

#define TRUE 1
#define FALSE 0

#endif