/* 
 * File:   main.h
 * Author: Jeremy
 *
 * Created on December 10, 2012, 9:35 PM
 */

#ifndef MAIN_H
#define	MAIN_H

#define Ledx                        PORTEbits.RE0                               // Activity status Led

#define Led0                        PORTDbits.RD0                               // Led selector
#define Led1                        PORTDbits.RD1                               // Led selector
#define Led2                        PORTDbits.RD2                               // Led selector
#define Led3                        PORTDbits.RD3                               // Led selector
#define Led4                        PORTDbits.RD4                               // Led selector
#define Led5                        PORTDbits.RD5                               // Led selector
#define Led6                        PORTDbits.RD6                               // Led selector
#define Led7                        PORTDbits.RD7                               // Led selector
#define Led                         PORTD                                       // All Leds

#define  Kol0                       PORTBbits.RB0                                // Kolom selector
#define  Kol1                       PORTBbits.RB1                                // Kolom selector
#define  Kol2                       PORTBbits.RB2                                // Kolom selector
#define  Kol3                       PORTBbits.RB3                                // Kolom selector
#define  Kol4                       PORTBbits.RB4                                // Kolom selector
#define  Kol5                       PORTBbits.RB5                                // Kolom selector
#define  Kolum                      PORTB                                        // Whole byte

#define ON 1
#define OFF 0

#define TRUE 1
#define FALSE 0

/*
#define Led1                        PORTBbits.RB5				// Activity status Led
#define vlv0                        PORTDbits.RD2				// Valve 1 output
#define vlv1                        PORTDbits.RD3				// Valve 2 output
#define vlv2                        PORTBbits.RB6				// Valve 3 output
#define vlv3                        PORTBbits.RB7				// Valve 4 output
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
#define pmp0_en                     PORTCbits.RC4				// Pump2 enable via diode OR-port
#define pmp1_en                     PORTCbits.RC5				// Pump1 enable via diode OR-port

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

#define ON  1
#define OFF 0

#define TRUE 1
#define FALSE 0
*/
#endif	/* MAIN_H */

