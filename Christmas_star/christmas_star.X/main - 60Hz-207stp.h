/* 
 * File:   main.h
 * Author: Jeremy
 *
 * Created on December 10, 2012, 9:35 PM
 */

#ifndef MAIN_H
#define	MAIN_H

#define Ledx                        PORTEbits.RE0                               // Activity status Led Timer0
#define Ledy                        PORTEbits.RE1                               // Activity status Led Timer1
#define Ledz                        PORTEbits.RE2                               // Activity status Led Update_Star

#define Row0                        PORTDbits.RD0                               // Row selector
#define Row1                        PORTDbits.RD1                               // Row selector
#define Row2                        PORTDbits.RD2                               // Row selector
#define Row3                        PORTDbits.RD3                               // Row selector
#define Row4                        PORTDbits.RD4                               // Row selector
#define Row5                        PORTDbits.RD5                               // Row selector
#define Row6                        PORTDbits.RD6                               // Row selector
#define Row7                        PORTDbits.RD7                               // Row selector
#define Row                         LATD                                        // All Rows(8)

#define Kol0                        PORTBbits.RB0                               // Kolom selector
#define Kol1                        PORTBbits.RB1                               // Kolom selector
#define Kol2                        PORTBbits.RB2                               // Kolom selector
#define Kol3                        PORTBbits.RB3                               // Kolom selector
#define Kol4                        PORTBbits.RB4                               // Kolom selector
#define Kol5                        PORTBbits.RB5                               // Kolom selector
#define Kolum                       LATB                                        // All Kolums(6)

#define ON 1
#define OFF 0

#define TRUE 1
#define FALSE 0



#endif	/* MAIN_H */

