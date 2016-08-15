/*
 * File:   display.c
 * Author: Jeremy Siebers
 *
 * Created on August 15, 2016, 2:22 PM
 */
#include "display.h"
#include "XLCD/xlcd.h"
#include "Peripherals/config.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define SOFTWARE_VERSION "SW version 1.0"
#define CELSIUS 0b11011111

/* http://web.alfredstate.edu/weimandn/lcd/lcd_addressing/lcd_addressing_index.html
  
   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9
  
 00* * * * * * * * * * * * * * * * * * * *13 
 
 40* * * * * * * * * * * * * * * * * * * *53 
  
 14* * * * * * * * * * * * * * * * * * * *27 
  
 54* * * * * * * * * * * * * * * * * * * *67 
  
 */

void LCDxINIT()
{    
    __delay_ms(200);                // Wait in case LCD power up
    OpenXLCD(FOUR_BIT & LINES_5X7); // Init LCD
    putrsXLCD("Fan Ctrl Started");  // Welcome message after power cycle
    while(BusyXLCD());              // Wait if LCD busy
    SetDDRamAddr(0x40);             // Set Cursor on first loc
    while(BusyXLCD());              // Wait if LCD busy
    putrsXLCD(SOFTWARE_VERSION);    // Software version
    __delay_ms(4000);               // Wait with start of program    
    ClearDisplay();
    DelayPORXLCD();
    BATHROOMxFANxINIT();
    HOUSExFANxINIT();
}

void DelayFor18TCY(void)
{   __delay_us(1);}

void DelayPORXLCD(void)
{   __delay_ms(50);}

void DelayXLCD(void)
{   __delay_ms(1);}



void BATHROOMxFANxINIT()
{
    SetDDRamAddr(0x00);
    while(BusyXLCD());
    putrsXLCD("Bathroom Fan:"); // 13 char
    while(BusyXLCD());    
}

void BATHROOMxFANxMODE(unsigned int mode)
{
    SetDDRamAddr(0x11);
    while(BusyXLCD());
    if (mode == 0)
    {
        putrsXLCD("LOW");
    }
    else if (mode == 1)
    {
        putrsXLCD("MID");
    }
    else if (mode == 2)
    {
        putrsXLCD("HGH");
    }
    while(BusyXLCD());
}
/*------------------------------------------------------------------------------
 * 
 * House Fan Stat M.tmp
 * 40
 * 
 * Power OFF Strt 100{C
 * 14 
 * 
 */

char cntDecimalPoint = 0;

void HOUSExFANxINIT()
{
    SetDDRamAddr(0x40);
    while(BusyXLCD());
    putrsXLCD("House_Fan Stat M.tmp");    // 20 char
    /*         40    47 494C  4E 53       */
    while(BusyXLCD()); 
    SetDDRamAddr(0x14);
    while(BusyXLCD());
    putrsXLCD("Power:");
    while(BusyXLCD());
}

void HOUSExFANxPOWER(bool status)
{
    SetDDRamAddr(0x1A);
    while(BusyXLCD());
    if (status == false)
    {
        putrsXLCD("OFF");
    }
    else if (status == true)
    {
        putrsXLCD("ON ");
    }    
    while(BusyXLCD());
}

void HOUSExFANxSTATUS(bool status)
{
    SetDDRamAddr(0x1E);
    while(BusyXLCD());
    if (status == true)
    {
        putrsXLCD("Strt");
    }
    else if (status == false)
    {
        putrsXLCD("Stop");
    }    
    while(BusyXLCD());
}

void HOUSExFANxTEMP(char *temp, char decimalpoint)
{
    SetDDRamAddr(0x23);
    
    if (decimalpoint == 2)
    {
        putrsXLCD(" ");
        while(BusyXLCD());
    }
    else if (decimalpoint == 1)
    {
        putrsXLCD("  ");
        while(BusyXLCD());
    }
    
    for(cntDecimalPoint = 0; cntDecimalPoint != decimalpoint; cntDecimalPoint++)
    {
        WriteDataXLCD(temp[cntDecimalPoint]);        
        while(BusyXLCD());
    }
    WriteDataXLCD(CELSIUS);                                                     // Write the °            
    while(BusyXLCD());                                                          // Wait if LCD busy
    putrsXLCD("C");                                                             // print the C 
    while(BusyXLCD());
}

char tempbuff[5];

void HOUSExFANxERROR(char error)
{
    SetDDRamAddr(0x54);
    
    if (error == NO_ERROR)
    {
        putrsXLCD("                    ");
        while(BusyXLCD());
    }
    else if (error == MOTOR_TEMP_ERROR)
    {
        itoa(tempbuff, Mot_Temp, 10);
        putrsXLCD("Motor too HOT!:");
        while(BusyXLCD());
        putrsXLCD(tempbuff);
        while(BusyXLCD());
        WriteDataXLCD(CELSIUS);                                                     // Write the °            
        while(BusyXLCD());                                                          // Wait if LCD busy
        putrsXLCD("C");                                                             // print the C 
        while(BusyXLCD());
    }
    else if (error == VFD_FAULT)
    {
        putrsXLCD("VFD Fault Out High!");
        while(BusyXLCD());
    }
}