/* 
 * File:   rain.h
 * Author: Jeremy
 *
 * Created on December 17, 2012, 12:17 PM
 */

#ifndef RAIN_H
#define	RAIN_H

extern char EXECUTExEFFECT(unsigned char Active_Kolum);
extern void UPDATExLEDSTAT(unsigned char Kolum_Selector);

typedef struct
{
    unsigned char Led;
    unsigned char Prog:3;
    unsigned char Speed;

    unsigned char Prog_State:4;
    unsigned char Iteration;

}LEDBIT;

extern LEDBIT Led_Bit[48];
extern unsigned char Illumination[48];

#endif	/* RAIN_H */

