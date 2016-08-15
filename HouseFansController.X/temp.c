/*
 * File:   temp.c
 * Author: Jeremy Siebers
 *
 * Created on August 12, 2016, 3:17 PM
 */

#include "Peripherals/config.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "display.h"

unsigned int iAdcConverter = 0;
unsigned int iAdcResult = 0;
unsigned int iOld_AdcResult = 0;
char chrStrTempBuf[8];
char cDecimalPoint = 0;


void UPDATExTEMP()
{
    if (ADCON0bits.GO == false)
    {        
        iAdcConverter = ((((unsigned int)ADRESH)<<8)|(ADRESL));      // 5V / 2^10  x 10000 =  48.82812 ( factor 10000 --> 48 up to 1365dec  Adconverter max is 1024 so no overflow for int )
        iAdcResult = (iAdcConverter * 48 + 99) / 100;                // The + 99 is to round off positively see: http://www.cs.nott.ac.uk/~psarb2/G51MPC/slides/NumberLogic.pdf --> if it is required to round up the result of dividing
                                                                     // m by n one should compute (m+n-1)/n .
        
        if (iOld_AdcResult != iAdcResult)                                       // check if temperature has changed
        {
            iOld_AdcResult = iAdcResult;
            
            itoa(chrStrTempBuf, iAdcResult, 10);                                // Convert the value to string only whole degrees of celsius

            if (iAdcResult < 1){                                                 // Determine the decimal point location
                cDecimalPoint = 0;
            }
            else if(iAdcResult < 10){
                cDecimalPoint = 1;
            }
            else if(iAdcResult < 100){
                cDecimalPoint = 2;
            }
            else{
                cDecimalPoint = 3;
            }

            HOUSExFANxTEMP(chrStrTempBuf, cDecimalPoint);

            Mot_Temp = iAdcResult;
        }
        
        ADCON0bits.GO = true;        
    }
}