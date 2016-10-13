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
//#include <stdio.h>
#include <stdbool.h>

#include "main.h"
#include "Peripherals/config.h"

const unsigned int GreenLeds[9][16] ={
{0b1111111111111111^0xFFFF,
 0b1111001111111111^0xFFFF,
 0b1110000111111111^0xFFFF,
 0b1111001111111111^0xFFFF,
 0b1111100111111111^0xFFFF,
 0b1111100001111111^0xFFFF,
 0b1111100010111111^0xFFFF,
 0b1111010011011111^0xFFFF,
 0b1110110011011111^0xFFFF,
 0b1111110001111111^0xFFFF,
 0b1111110101111111^0xFFFF,
 0b1111101110011111^0xFFFF,
 0b1111101111100111^0xFFFF,
 0b1111101111110111^0xFFFF,
 0b1110011111101111^0xFFFF,
 0b1111111111111111^0xFFFF},
 
 {0b1111111111111111^0xFFFF,
  0b1111100111111111^0xFFFF,
  0b1111000011111111^0xFFFF,
  0b1111100111111111^0xFFFF,
  0b1111110011111111^0xFFFF,
  0b1111110001111111^0xFFFF,
  0b1111110010111111^0xFFFF,
  0b1111100001011111^0xFFFF,
  0b1111011001011111^0xFFFF,
  0b1111111000111111^0xFFFF,
  0b1111111010111111^0xFFFF,
  0b1111110111011111^0xFFFF,
  0b1111101111101111^0xFFFF,
  0b1111110011110111^0xFFFF,
  0b1111111011100111^0xFFFF,
  0b1111110011111111^0xFFFF},
                    
 {0b1111111111111111^0xFFFF,
  0b1111100111111111^0xFFFF,
  0b1111000011111111^0xFFFF,
  0b1111100111111111^0xFFFF,
  0b1111110011111111^0xFFFF,
  0b1111110001111111^0xFFFF,
  0b1111110010111111^0xFFFF,
  0b1111100001011111^0xFFFF,
  0b1111011001011111^0xFFFF,
  0b1111111000111111^0xFFFF,
  0b1111111010111111^0xFFFF,
  0b1111110110111111^0xFFFF,
  0b1111101111001111^0xFFFF,
  0b1111110011101111^0xFFFF,
  0b1111111101001111^0xFFFF,
  0b1111110001111111^0xFFFF},
                    
 {0b1111111111111111^0xFFFF,
  0b1111100111111111^0xFFFF,
  0b1111000011111111^0xFFFF,
  0b1111100111111111^0xFFFF,
  0b1111110011111111^0xFFFF,
  0b1111110011111111^0xFFFF,
  0b1111110001111111^0xFFFF,
  0b1111110010111111^0xFFFF,
  0b1111111000111111^0xFFFF,
  0b1111111001111111^0xFFFF,
  0b1111111001111111^0xFFFF,
  0b1111110101111111^0xFFFF,
  0b1111110110111111^0xFFFF,
  0b1111111011011111^0xFFFF,
  0b1111111101011111^0xFFFF,
  0b1111111001111111^0xFFFF}, 
                    
 {0b1111111111111111^0xFFFF,
  0b1111100111111111^0xFFFF,
  0b1111000011111111^0xFFFF,
  0b1111100111111111^0xFFFF,
  0b1111110011111111^0xFFFF,
  0b1111110001111111^0xFFFF,
  0b1111110001111111^0xFFFF,
  0b1111110001111111^0xFFFF,
  0b1111111001111111^0xFFFF,
  0b1111111001111111^0xFFFF,
  0b1111111001111111^0xFFFF,
  0b1111111001111111^0xFFFF,
  0b1111111101111111^0xFFFF,
  0b1111111101111111^0xFFFF,
  0b1111111101111111^0xFFFF,
  0b1111111001111111^0xFFFF}, 
                    
 {0b1111111111111111^0xFFFF,
  0b1111100111111111^0xFFFF,
  0b1111000011111111^0xFFFF,
  0b1111100111111111^0xFFFF,
  0b1111110011111111^0xFFFF,
  0b1111110001111111^0xFFFF,
  0b1111110010111111^0xFFFF,
  0b1111110000111111^0xFFFF,
  0b1111111000111111^0xFFFF,
  0b1111111001111111^0xFFFF,
  0b1111111001111111^0xFFFF,
  0b1111110001111111^0xFFFF,
  0b1111110110111111^0xFFFF,
  0b1111111011011111^0xFFFF,
  0b1111100011101111^0xFFFF,
  0b1111111111111111^0xFFFF},
                    
 {0b1111111111111111^0xFFFF,
  0b1111001111111111^0xFFFF,
  0b1110000111111111^0xFFFF,
  0b1111001111111111^0xFFFF,
  0b1111100111111111^0xFFFF,
  0b1111100011111111^0xFFFF,
  0b1111100001111111^0xFFFF,
  0b1111100010111111^0xFFFF,
  0b1111110010111111^0xFFFF,
  0b1111110001111111^0xFFFF,
  0b1111110101111111^0xFFFF,
  0b1111101110111111^0xFFFF,
  0b1111101111011111^0xFFFF,
  0b1110001111100111^0xFFFF,
  0b1111111111110111^0xFFFF,
  0b1111111111111111^0xFFFF},   
                    
 {0b1111111111111111^0xFFFF,
  0b1111001111111111^0xFFFF,
  0b1110000111111111^0xFFFF,
  0b1111001111111111^0xFFFF,
  0b1111100111111111^0xFFFF,
  0b1111100001111111^0xFFFF,
  0b1111100010111111^0xFFFF,
  0b1111010011011111^0xFFFF,
  0b1110110011011111^0xFFFF,
  0b1111110001111111^0xFFFF,
  0b1111110101111111^0xFFFF,
  0b1111101110001111^0xFFFF,
  0b1111101111110111^0xFFFF,
  0b1111101111100111^0xFFFF,
  0b1110011111111111^0xFFFF,
  0b1111111111111111^0xFFFF},
                    
 {0b1111111001111111^0xFFFF,
  0b1111110000111111^0xFFFF,
  0b1111111001111111^0xFFFF,
  0b1111111001111111^0xFFFF,
  0b1111110000111111^0xFFFF,
  0b1111110000111111^0xFFFF,
  0b1111100000011111^0xFFFF,
  0b1111100000011111^0xFFFF,
  0b1111001001001111^0xFFFF,
  0b1111001001001111^0xFFFF,
  0b1111011001101111^0xFFFF,
  0b1111011001101111^0xFFFF,
  0b1111110110111111^0xFFFF,
  0b1111100110011111^0xFFFF,
  0b1111100110011111^0xFFFF,
  0b1110000110000111^0xFFFF}
 };

static bool NextFrame = true;
static unsigned char ActiveDisplayRow  = 0xFF;

static unsigned int OperateLedsRow = 0;
static unsigned int OperateLedsRow2 = 0;

static unsigned char OperateImage = 0;
static unsigned char iImage = 0;
static unsigned int iRunStop = 0;
static bool Run = true;

static unsigned int *pToGreenLed;

static unsigned char GreenCol1Byte = 0xFF;
static unsigned char GreenCol2Byte = 0xFF;
static unsigned char GreenCol3Byte = 0xFF;
static unsigned char GreenCol4Byte = 0xFF;

static unsigned char RedCol1Byte = 0xFF;
static unsigned char RedCol2Byte = 0xFF;
static unsigned char RedCol3Byte = 0xFF;
static unsigned char RedCol4Byte = 0xFF;

static unsigned int ImageFrameCounter = 0;

void main(void) {
    // Initialize the device
    SYSTEM_Initialize();
       
    while(1)
    {
        Led1 = false;
        
        if(PIR1bits.TMR1IF == false && NextFrame == true)
        {
            Led1 = true;
            NextFrame = false;
            
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
                pToGreenLed = &(GreenLeds[OperateImage][OperateLedsRow]);
                GreenCol1Byte = *pToGreenLed;
                
                pToGreenLed++;
                GreenCol2Byte = *pToGreenLed;
                
                //GreenCol1Byte = table[(GreenLeds[OperateImage][OperateLedsRow]>>8)];
                //GreenCol2Byte = table[(GreenLeds[OperateImage][OperateLedsRow])];
                //GreenCol3Byte = table[(GreenLeds[OperateImage][OperateLedsRow2]>>8)];
                //GreenCol4Byte = table[(GreenLeds[OperateImage][OperateLedsRow2])];

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

                //RedCol1Byte = table[(GreenLeds[OperateImage][OperateLedsRow]>>8)];
                //RedCol2Byte = table[(GreenLeds[OperateImage][OperateLedsRow])];
                //RedCol3Byte = table[(GreenLeds[OperateImage][OperateLedsRow2]>>8)];
                //RedCol4Byte = table[(GreenLeds[OperateImage][OperateLedsRow2])];
            }
        }
        
        // Sequence is 0,1, 2, 3, 4, 5, 6, 7, 2, 3, 4, 5, 7, --> 1 
        if (ImageFrameCounter > 50){
            ImageFrameCounter = 0;
            
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
            if (!Select){
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

void interrupt tc_int(void)
{
    if (PIE1bits.TMR1IE && PIR1bits.TMR1IF) 
    {
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
        
        OperateLedsRow++;
        if (OperateLedsRow > 7)
        {
            OperateLedsRow = 0;
            //Led1 = !Led1;
        }
        OperateLedsRow2 = OperateLedsRow + 8;
        
        TMR1H = 0xE0;                                                           // 0xE0 ~74Hz
        TMR1L = 0x00;
        NextFrame = true;        
        ImageFrameCounter++;
        PIR1bits.TMR1IF=0;
    }
}