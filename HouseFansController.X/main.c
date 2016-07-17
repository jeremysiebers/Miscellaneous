/*
 * File:   main.c
 * Author: Jeremy Siebers
 *
 * Created on June 27, 2016, 10:24 PM
 */
// PIC16F737 Configuration Bit Settings

// 'C' source line config statements

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

// CONFIG1
#pragma config FOSC = INTOSCIO  // Oscillator Selection bits (INTRC oscillator; port I/O function on OSC1/CLKI/RA7 and OSC2/CLKO/RA6)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = ON       // MCLR/VPP/RE3 Pin Function Select bit (MCLR/VPP/RE3 pin function is MCLR)
#pragma config BOREN = OFF      // Brown-out Reset Enable bit (Disabled)
#pragma config BORV = 45        // Brown-out Reset Voltage bits (VBOR set to 4.5V)
#pragma config CCP2MX = RC1     // CCP2 Multiplex bit (CCP2 is on RC1)
#pragma config CP = OFF         // Flash Program Memory Code Protection bits (Code protection off)


// CONFIG2
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enable bit (Fail-Safe Clock Monitor disabled)
#pragma config IESO = OFF       // Internal External Switchover bit (Internal External Switchover mode disabled)
#pragma config BORSEN = OFF     // Brown-out Reset Software Enable bit (Disabled)

#include <xc.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "main.h"
#include "Peripherals/config.h"
#include "XLCD/xlcd.h"

#define _XTAL_FREQ 4000000

//int Temperature = 0;
unsigned int iAdcConverter = 0;
unsigned int iAdcResult = 0;
char chrStrTempBuf[8];
char iDecimalPoint = 0;
char icntDecimalPoint = 0;
bool bConvertTemp = false;

void main(void) {
    // Initialize the device
    SYSTEM_Initialize();
    LCD_Initialize();
    
    while(1)
    {
        if (ADCON0bits.GO == false && bConvertTemp == true)
        {
            bConvertTemp = false;
            iAdcConverter = ((((unsigned int)ADRESH)<<8)|(ADRESL));              // 5V / 2^10  x 10000 =  48.82812 ( factor 10000 --> 48 up to 1365dec  Adconverter max is 1024 so no overflow for int )
            iAdcResult = (iAdcConverter * 48 + 99) / 100;                         // The + 99 is to round off positively see: http://www.cs.nott.ac.uk/~psarb2/G51MPC/slides/NumberLogic.pdf --> if it is required to round up the result of dividing
                                                                                // m by n one should compute (m+n-1)/n .
            itoa(chrStrTempBuf, iAdcResult, 10);                                    // Convert the value to string only whole degrees of celsius
            
            if (iAdcResult < 1){                                                 // Determine the decimal point location, AdcResult above 100 degrees celsius? With a factor of 4883, lower then 1000 is not posible (1(bit) * 4883)
                iDecimalPoint = 0;
            }
            else if(iAdcResult < 10){
                iDecimalPoint = 1;
            }
            else if(iAdcResult < 100){
                iDecimalPoint = 2;
            }
            else{
                iDecimalPoint = 3;
            }
            
            if (iDecimalPoint == 0){
                putrsXLCD("0");
                while(BusyXLCD());                                              // Wait if LCD busy
            }
            else{
                for(icntDecimalPoint = 0; icntDecimalPoint != iDecimalPoint; icntDecimalPoint++){                    
                    WriteDataXLCD(chrStrTempBuf[icntDecimalPoint]);
                    while(BusyXLCD());                                          // Wait if LCD busy
                }
            }
            /*
            //while(BusyXLCD());                                                  // Wait if LCD busy
            //putrsXLCD(StrTempBuf);                                              // Put the value before the . on the display
            while(BusyXLCD());                                                  // Wait if LCD busy
            putrsXLCD(".");                                                     // print the .
            while(BusyXLCD());                                                  // Wait if LCD busy
            
            //Temperature = (AdcResult - ((AdcResult / 10000) * 10000)) / 100;    // Take the original AdcResult and subtract de TOP value which was printed before the . also divide by 100 to get 2 decimals(25.8799 - 25.000 / 100 = 88)
            
            //ltoa(StrTempBuf, AdcResult, 10);                                    // Convert the rest value to string
            
            //putrsXLCD(&StrTempBuf[DecimalPoint]);                               // Print the remaining value on the display
            WriteDataXLCD(StrTempBuf[DecimalPoint+1]);
            WriteDataXLCD(StrTempBuf[DecimalPoint+2]);
            
            */
            while(BusyXLCD());                                                  // Wait if LCD busy
            WriteDataXLCD(0b11011111);                                          // Write the °            
            while(BusyXLCD());                                                  // Wait if LCD busy
            putrsXLCD("C ");                                                     // print the C and a space in case a previous value was 100 en the next is 99
            while(BusyXLCD());                                                  // Wait if LCD busy
            SetDDRamAddr(0x87);                                                 // Set cursor back to start position for (over)writing temp value            
            ADCON0bits.GO = true;        
        }
    }
}

void interrupt tc_int(void)
{
    if (PIE1bits.TMR1IE && PIR1bits.TMR1IF) 
    {
        PIR1bits.TMR1IF=0;
        Led1 = !Led1;
        bConvertTemp = true;
    }
}

void LCD_Initialize(void){
    __delay_ms(100);                // Wait in case LCD power up
    OpenXLCD(FOUR_BIT & LINES_5X7);
    putrsXLCD("Fan Ctrl Started");
    while(BusyXLCD());              // Wait if LCD busy
    SetDDRamAddr(0x40);
    while(BusyXLCD());              // Wait if LCD busy
    putrsXLCD("SW version 1.0");
    __delay_ms(2000);
    //Clear display
    while(BusyXLCD());              // Wait if LCD busy
    WriteCmdXLCD(0x01);             // Clear display
    while(BusyXLCD());              // Wait if LCD busy
    SetDDRamAddr(0x80);  
    while(BusyXLCD());              // Wait if LCD busy
    putrsXLCD("Temp = ");
}

void DelayFor18TCY(void)
{    
    __delay_us(1);
}
void DelayPORXLCD(void)
{
    __delay_ms(50);
}

void DelayXLCD(void)
{
    __delay_ms(1);
}
