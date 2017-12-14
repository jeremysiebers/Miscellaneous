/* 
 * File:   main.h
 * Author: Jeremy
 *
 * Created on December 10, 2012, 9:35 PM
 */

#ifndef MAIN_H
#define	MAIN_H

#include "p18cxxx.h"

#define Ledx                        LATEbits.LATE0                              // Activity status output Timer0
#define Ledy                        LATEbits.LATE1                              // Activity status output Timer1
#define Ledz                        LATEbits.LATE2                              // Activity status output Update_Star
#define Ledw                        LATAbits.LATA5                              // Activity status output osc meas.

#define Row                         LATD                                        // All Rows(8)
#define Kol1                        LATB                                        // Kolums(4)
#define Kol2                        LATC                                        // Kolums(2)

#define ON 1
#define OFF 0

#define TRUE 1
#define FALSE 0

#define Finished -1
#define Busy 0

#define FORWARD 1
#define BACKWARD 0

#define tSEC 32                                                                 // 0.01 tSECond counter value

#define ROW_UPDATE_VAL 7                                                        // 7 - Updates per 1/60s 0 -> 7 = 8 updates!!!
#define ROW_UPDATE_CNT 127                                                      // 127 - ROW_UPDATE_VAL 7 -> 0b0111 1111 because the use of x > ROW_UPDATE_CNT -> 0b1111 1111 bits are shifted in!!!

extern unsigned char Led[6];                                                    // Global array which helds the value to be written to the PORT
extern unsigned char Row_Updater;                                               // Global iteration counter value of PWM
extern unsigned char Iteration_Cycle;                                           // Every 8 updates of 1/60 refresh rate -> 1/7.5 min update pulse for progs
extern unsigned char Program_Selector;                                   // Rotary knob determines program to be executed

#endif	/* MAIN_H */

