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
#include <float.h>

#include "main.h"
#include "Peripherals/config.h"
#include "XLCD/xlcd.h"

#define _XTAL_FREQ 8000000

int Temperature = 0;
unsigned long int AdcResult = 0;

char StrTempBuf[3];
int status;

void main(void) {
    // Initialize the device
    SYSTEM_Initialize();
    LCD_Initialize();
    
    while(1)
    {
        if (ADCON0bits.GO == false)
        {
            AdcResult = ((((unsigned long int)ADRESH)<<8)|(ADRESL)) * 4883;     // 5V / 2^10  x 1000000. (example 258.799 --> 25.8799 degrees celsius)
            
            Temperature = (int)(AdcResult / 10000);                             // Get the TOP degrees before the . so divide this with 10000 (also use (int) to truncate and not to round of (258.799 / 10.000 = 26)
            
            itoa(StrTempBuf, Temperature, 10);                                  // Convert the value to string
            
            while(BusyXLCD());                                                  // Wait if LCD busy
            putrsXLCD(StrTempBuf);                                              // Put the value before the . on the display
            while(BusyXLCD());                                                  // Wait if LCD busy
            putrsXLCD(".");                                                     // print the .
            while(BusyXLCD());                                                  // Wait if LCD busy
            
            Temperature = (AdcResult - ((AdcResult / 10000) * 10000)) / 100;    // Take the original AdcResult and subtract de TOP value which was printed before the . also divide by 100 to get 2 decimals(25.8799 - 25.000 / 100 = 88)
            
            itoa(StrTempBuf, Temperature, 10);                                  // Convert the rest value to string
            
            putrsXLCD(StrTempBuf);                                              // Print the remaining value on the display
            
            while(BusyXLCD());                                                  // Wait if LCD busy
            WriteDataXLCD(0b11011111);                                          // Write the °            
            while(BusyXLCD());                                                  // Wait if LCD busy
            putrsXLCD("C");                                                     // print the C
            while(BusyXLCD());                                                  // Wait if LCD busy
            SetDDRamAddr(0x87);                                                 // Set cursor back to start position for (over)writing temp value            
            ADCON0bits.GO = true;        
        }
    }
}

void interrupt   tc_int  (void)
{
    if (PIE1bits.TMR1IE && PIR1bits.TMR1IF) 
    {
        PIR1bits.TMR1IF=0;
        Led1 = !Led1;
    }
}

void LCD_Initialize(void){
    OpenXLCD(EIGHT_BIT & LINES_5X7);
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
    __delay_us(50);
}
void DelayPORXLCD(void)
{
    __delay_ms(50);
}
void DelayXLCD(void)
{
    __delay_ms(5);
}
