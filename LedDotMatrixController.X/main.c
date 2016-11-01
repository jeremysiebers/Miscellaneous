/*
 * File:   main.c
 * Author: Jeremy Siebers
 *
 * Created on June 27 2016 10:24 PM
 */
// PIC16F76 Configuration Bit Settings

// 'C' source line config statements

#include <xc.h>

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

// CONFIG
#pragma config FOSC = HS        // Oscillator Selection bits (HS oscillator)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config CP = OFF         // FLASH Program Memory Code Protection bit (Code protection off)
#pragma config BOREN = OFF      // Brown-out Reset Enable bit (BOR disabled)

#include <xc.h>
//#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "main.h"
#include "Peripherals/config.h"
#include "Peripherals/uart1.h"
#include "default_pattern.h"

static bool NextFrame = true;
static unsigned char ActiveDisplayRow  = 0xFF;

static unsigned int OperateLedsRow = 0;
static unsigned int OperateLedsRow2 = 0;

static unsigned char OperateImage = 0;
static unsigned char iImage = 0;
static unsigned int iRunStop = 0;
static bool Run = true;
static bool Default_Pattern = true;

static unsigned char GreenCol1Byte = 0xFF;
static unsigned char GreenCol2Byte = 0xFF;
static unsigned char GreenCol3Byte = 0xFF;
static unsigned char GreenCol4Byte = 0xFF;

static unsigned char RedCol1Byte = 0xFF;
static unsigned char RedCol2Byte = 0xFF;
static unsigned char RedCol3Byte = 0xFF;
static unsigned char RedCol4Byte = 0xFF;

static unsigned int ImageFrameCounter = 0;
static unsigned int ImageFrameCounterValue = 90;

static unsigned char ReceivedByte = 0;
static unsigned char ReceivedTable[64];
static unsigned char ActualTable[64] = {
    0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
    0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
    0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
    0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
    0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
    0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
    0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
    0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF};

static unsigned char State = 0;

void main(void) {
    // Initialize the device
    SYSTEM_Initialize();
    
    __delay_ms(1000);                                                           // To prevent inrush on USB to serial converter while being detected by OS
    
    Latch = false;        
    SSPBUF = GreenCol4Byte;
    while(!SSPSTATbits.BF);
    SSPBUF = GreenCol3Byte;
    while(!SSPSTATbits.BF);
    SSPBUF = GreenCol2Byte;
    while(!SSPSTATbits.BF);
    SSPBUF = GreenCol1Byte;
    while(!SSPSTATbits.BF);
    SSPBUF = RedCol4Byte;
    while(!SSPSTATbits.BF);
    SSPBUF = RedCol3Byte;
    while(!SSPSTATbits.BF);
    SSPBUF = RedCol2Byte;
    while(!SSPSTATbits.BF);
    SSPBUF = RedCol1Byte;
    while(!SSPSTATbits.BF);
    SSPBUF = ActiveDisplayRow;
    while(!SSPSTATbits.BF);
    SSPBUF = ActiveDisplayRow;
    while(!SSPSTATbits.BF);
    Latch = true;
    OutputDisable = false;
    
    printf("\f");
    printf("Little green man started up!!!\n\r");
    
    if (EUSART1_DataReady > 0)
    {
        Default_Pattern = false;                                                // serial commands received stop with default pattern program
    }
       
    while(1)
    {
        
        switch (State){
            case 0 :
                if (EUSART1_DataReady > 0)                                      // 64 bytes data
                {
                    if (EUSART1_Read() == 0xA){
                        Default_Pattern = false;                                // serial commands received stop with default pattern program
                        ReceivedByte = 0;
                        State = 1;
                    }
                    else if (EUSART1_Read() == 0x5){                        
                        Default_Pattern = true;                                      
                    }
                }
                break;
                
            case 1 :
                if (EUSART1_DataReady > 0)                                      // 64 bytes data
                {
                    ActualTable[ReceivedByte] = EUSART1_Read();
                    ReceivedByte++;
                    if (ReceivedByte > 63)
                    {                        
                        Led1 ^= 1;
                        State = 0;
                    }            
                }
                break;
                
            default : break;
        }
        
        
        
        if(PIR1bits.TMR1IF == false && NextFrame == true && Default_Pattern == false)
        {            
            NextFrame = false;
            
            OperateLedsRow+= 8;
            if (OperateLedsRow > 56)
            {
                OperateLedsRow = 0;
                //Led1 ^= 1;
            }            
            
            if(OperateLedsRow == 0){
                ActiveDisplayRow = 0xFE;}
            if(OperateLedsRow == 8){
                ActiveDisplayRow = 0xFD;}
            if(OperateLedsRow == 16){
                ActiveDisplayRow = 0xFB;}
            if(OperateLedsRow == 24){
                ActiveDisplayRow = 0xF7;}
            if(OperateLedsRow == 32){
                ActiveDisplayRow = 0xEF;}
            if(OperateLedsRow == 40){
                ActiveDisplayRow = 0xDF;}
            if(OperateLedsRow == 48){
                ActiveDisplayRow = 0xBF;}
            if(OperateLedsRow == 56){
                ActiveDisplayRow = 0x7F;}
            
            
			GreenCol1Byte   = table[ActualTable[OperateLedsRow + 0]];
			GreenCol2Byte   = table[ActualTable[OperateLedsRow + 1]];
			GreenCol3Byte   = table[ActualTable[OperateLedsRow + 2]];
			GreenCol4Byte   = table[ActualTable[OperateLedsRow + 3]];
			
			RedCol1Byte     = table[ActualTable[OperateLedsRow + 4]];
            RedCol2Byte     = table[ActualTable[OperateLedsRow + 5]];
			RedCol3Byte     = table[ActualTable[OperateLedsRow + 6]];
			RedCol4Byte     = table[ActualTable[OperateLedsRow + 7]];
			
        }
        
        else if(PIR1bits.TMR1IF == false && NextFrame == true && Default_Pattern == true)
        {
            //Led1 = true;
            NextFrame = false;
            
            OperateLedsRow++;
            if (OperateLedsRow > 7)
            {
                OperateLedsRow = 0;
                //Led1 = !Led1;
            }
            OperateLedsRow2 = OperateLedsRow + 8;       
            ImageFrameCounter++; 
            
            if(OperateLedsRow == 0){
                ActiveDisplayRow = 0xFE;}
            if(OperateLedsRow == 1){
                ActiveDisplayRow = 0xFD;}
            if(OperateLedsRow == 2){
                ActiveDisplayRow = 0xFB;}
            if(OperateLedsRow == 3){
                ActiveDisplayRow = 0xF7;}
            if(OperateLedsRow == 4){
                ActiveDisplayRow = 0xEF;}
            if(OperateLedsRow == 5){
                ActiveDisplayRow = 0xDF;}
            if(OperateLedsRow == 6){
                ActiveDisplayRow = 0xBF;}
            if(OperateLedsRow == 7){
                ActiveDisplayRow = 0x7F;}
            
            if (Run)
            {
                GreenCol1Byte = table[(GreenLeds[OperateImage][OperateLedsRow]>>8)];
                GreenCol2Byte = table[(GreenLeds[OperateImage][OperateLedsRow])];
                GreenCol3Byte = table[(GreenLeds[OperateImage][OperateLedsRow2]>>8)];
                GreenCol4Byte = table[(GreenLeds[OperateImage][OperateLedsRow2])];

                RedCol1Byte = 0xFF;
                RedCol2Byte = 0xFF;
                RedCol3Byte = 0xFF;
                RedCol4Byte = 0xFF;
            }
            else
            {
                GreenCol1Byte = 0xFF;
                GreenCol2Byte = 0xFF;
                GreenCol3Byte = 0xFF;
                GreenCol4Byte = 0xFF;

                RedCol1Byte = table[(GreenLeds[OperateImage][OperateLedsRow]>>8)];
                RedCol2Byte = table[(GreenLeds[OperateImage][OperateLedsRow])];
                RedCol3Byte = table[(GreenLeds[OperateImage][OperateLedsRow2]>>8)];
                RedCol4Byte = table[(GreenLeds[OperateImage][OperateLedsRow2])];
            }
        
        
            // Sequence is 0,1, 2, 3, 4, 5, 6, 7, 2, 3, 4, 5, 7, --> 1 
            if (ImageFrameCounter > ImageFrameCounterValue){
                ImageFrameCounter = 0;
                Led1 ^= 1;

                iRunStop++;
                if (iRunStop > 130){
                    iImage = 13;
                }
                if (iRunStop > 260){
                    iImage = 0;
                    iRunStop = 0;
                }
                if (iRunStop < 130)
                {
                    iImage++;
                    if (iImage > 12){
                        iImage = 0;
                    }
                }
                if (Select){
                    iImage = 13;
                    iRunStop = 250;
                }
                switch (iImage)
                {
                    case 0  : OperateImage = 0;Run = true;break;
                    case 1  : OperateImage = 1;Run = true;break;
                    case 2  : OperateImage = 2;Run = true;break;
                    case 3  : OperateImage = 3;Run = true;break;
                    case 4  : OperateImage = 4;Run = true;break;
                    case 5  : OperateImage = 5;Run = true;break;
                    case 6  : OperateImage = 6;Run = true;break;
                    case 7  : OperateImage = 7;Run = true;break;
                    case 8  : OperateImage = 2;Run = true;break;
                    case 9  : OperateImage = 3;Run = true;break;
                    case 10 : OperateImage = 4;Run = true;break;
                    case 11 : OperateImage = 5;Run = true;break;
                    case 12 : OperateImage = 7;Run = true;break;
                    case 13 : OperateImage = 8;Run = false;break;
                    default : break;
                }

            }
        }
    }
}

void interrupt tc_int(void)
{
    if (PIR1bits.RCIF)
    {
        PIR1bits.RCIF = 0;
        EUSART1_Receive_ISR();
    }
    
    if (PIR1bits.TXIF)
    {
        PIR1bits.TXIF = 0;
        EUSART1_Transmit_ISR();
    }
    
    if (PIR1bits.TMR1IF)
    {
        TMR1H = 0xE8;                                                           // 0xE0 ~74Hz, 0xD0 ~50Hz, 0xF0 ~147Hz,  0xE8 ~100 Hz
        TMR1L = 0x00;
        PIR1bits.TMR1IF=0;
        
        Latch = false;        
        SSPBUF = GreenCol4Byte;
        while(!SSPSTATbits.BF);
        SSPBUF = GreenCol3Byte;
        while(!SSPSTATbits.BF);
        SSPBUF = GreenCol2Byte;
        while(!SSPSTATbits.BF);
        SSPBUF = GreenCol1Byte;
        while(!SSPSTATbits.BF);
        SSPBUF = RedCol4Byte;
        while(!SSPSTATbits.BF);
        SSPBUF = RedCol3Byte;
        while(!SSPSTATbits.BF);
        SSPBUF = RedCol2Byte;
        while(!SSPSTATbits.BF);
        SSPBUF = RedCol1Byte;
        while(!SSPSTATbits.BF);
        SSPBUF = ActiveDisplayRow;
        while(!SSPSTATbits.BF);
        SSPBUF = ActiveDisplayRow;
        while(!SSPSTATbits.BF);
        Latch = true;        
        NextFrame = true;
    }
}