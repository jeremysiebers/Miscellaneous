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
#include "io.h"
#include "vfd.h"
#include "temp.h"

#define SOFTWARE_VERSION "SW version 1.0"

#define CELSIUS 0b11011111

unsigned int ReadTemp = 0;
unsigned int SecondsCounter = 0;
bool UpdateTemp = false;

void main(void) {
    // Initialize the device
    SYSTEM_Initialize();    
    READxIO();
    UPDATExTEMP();
    LCD_Initialize();
    
    while(1)
    {
        UPDATExVFD();
        
        if (UpdateTemp == true)
        {            
            UPDATExTEMP();
            UpdateTemp = false;
        }
    }
}

void interrupt tc_int(void)
{
    if (PIE1bits.TMR1IE && PIR1bits.TMR1IF) 
    {  
        PIR1bits.TMR1IF=0;                      // Clearing the flag as soon as possible results in restarting the timer
                                                // Make sure the execution of the interrupt content is faster that the timer base (30 Hz)
        READxIO();
        
        ReadTemp++;
        if (ReadTemp >= 10){
            ReadTemp = 0;
            UpdateTemp = true;
        }
        
        SecondsCounter++;
        if (SecondsCounter >= 30){
            SecondsCounter = 0;
            iSeconds++;                          // rolls over to 0 when int is full!
            Led1 = !Led1;                       // blink the led every 2 seconds
        }
    }
}

void LCD_Initialize(void){
    __delay_ms(100);                // Wait in case LCD power up
    OpenXLCD(FOUR_BIT & LINES_5X7); // Init LCD
    putrsXLCD("Fan Ctrl Started");  // Welcome message after power cycle
    while(BusyXLCD());              // Wait if LCD busy
    SetDDRamAddr(0x40);             // Set Cursor on first loc
    while(BusyXLCD());              // Wait if LCD busy
    putrsXLCD(SOFTWARE_VERSION);    // Software version
    __delay_ms(4000);               // Wait with start of program
}

void DelayFor18TCY(void)
{    
    __delay_us(1);
}
void DelayPORXLCD(void)
{
    __delay_ms(50);}

void DelayXLCD(void)
{
    __delay_ms(1);
}
