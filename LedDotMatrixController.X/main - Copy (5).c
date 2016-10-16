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

const unsigned char table[] = {
    0x00, 0x80, 0x40, 0xc0, 0x20, 0xa0, 0x60, 0xe0,
    0x10, 0x90, 0x50, 0xd0, 0x30, 0xb0, 0x70, 0xf0,
    0x08, 0x88, 0x48, 0xc8, 0x28, 0xa8, 0x68, 0xe8,
    0x18, 0x98, 0x58, 0xd8, 0x38, 0xb8, 0x78, 0xf8,
    0x04, 0x84, 0x44, 0xc4, 0x24, 0xa4, 0x64, 0xe4,
    0x14, 0x94, 0x54, 0xd4, 0x34, 0xb4, 0x74, 0xf4,
    0x0c, 0x8c, 0x4c, 0xcc, 0x2c, 0xac, 0x6c, 0xec,
    0x1c, 0x9c, 0x5c, 0xdc, 0x3c, 0xbc, 0x7c, 0xfc,
    0x02, 0x82, 0x42, 0xc2, 0x22, 0xa2, 0x62, 0xe2,
    0x12, 0x92, 0x52, 0xd2, 0x32, 0xb2, 0x72, 0xf2,
    0x0a, 0x8a, 0x4a, 0xca, 0x2a, 0xaa, 0x6a, 0xea,
    0x1a, 0x9a, 0x5a, 0xda, 0x3a, 0xba, 0x7a, 0xfa,
    0x06, 0x86, 0x46, 0xc6, 0x26, 0xa6, 0x66, 0xe6,
    0x16, 0x96, 0x56, 0xd6, 0x36, 0xb6, 0x76, 0xf6,
    0x0e, 0x8e, 0x4e, 0xce, 0x2e, 0xae, 0x6e, 0xee,
    0x1e, 0x9e, 0x5e, 0xde, 0x3e, 0xbe, 0x7e, 0xfe,
    0x01, 0x81, 0x41, 0xc1, 0x21, 0xa1, 0x61, 0xe1,
    0x11, 0x91, 0x51, 0xd1, 0x31, 0xb1, 0x71, 0xf1,
    0x09, 0x89, 0x49, 0xc9, 0x29, 0xa9, 0x69, 0xe9,
    0x19, 0x99, 0x59, 0xd9, 0x39, 0xb9, 0x79, 0xf9,
    0x05, 0x85, 0x45, 0xc5, 0x25, 0xa5, 0x65, 0xe5,
    0x15, 0x95, 0x55, 0xd5, 0x35, 0xb5, 0x75, 0xf5,
    0x0d, 0x8d, 0x4d, 0xcd, 0x2d, 0xad, 0x6d, 0xed,
    0x1d, 0x9d, 0x5d, 0xdd, 0x3d, 0xbd, 0x7d, 0xfd,
    0x03, 0x83, 0x43, 0xc3, 0x23, 0xa3, 0x63, 0xe3,
    0x13, 0x93, 0x53, 0xd3, 0x33, 0xb3, 0x73, 0xf3,
    0x0b, 0x8b, 0x4b, 0xcb, 0x2b, 0xab, 0x6b, 0xeb,
    0x1b, 0x9b, 0x5b, 0xdb, 0x3b, 0xbb, 0x7b, 0xfb,
    0x07, 0x87, 0x47, 0xc7, 0x27, 0xa7, 0x67, 0xe7,
    0x17, 0x97, 0x57, 0xd7, 0x37, 0xb7, 0x77, 0xf7,
    0x0f, 0x8f, 0x4f, 0xcf, 0x2f, 0xaf, 0x6f, 0xef,
    0x1f, 0x9f, 0x5f, 0xdf, 0x3f, 0xbf, 0x7f, 0xff,
};

const unsigned int GreenLeds[9][16] ={
{0b1111111111111111,
 0b1111001111111111,
 0b1110000111111111,
 0b1111001111111111,
 0b1111100111111111,
 0b1111100001111111,
 0b1111100010111111,
 0b1111010011011111,
 0b1110110011011111,
 0b1111110001111111,
 0b1111110101111111,
 0b1111101110011111,
 0b1111101111100111,
 0b1111101111110111,
 0b1110011111101111,
 0b1111111111111111},
 
 {0b1111111111111111,
  0b1111100111111111,
  0b1111000011111111,
  0b1111100111111111,
  0b1111110011111111,
  0b1111110001111111,
  0b1111110010111111,
  0b1111100001011111,
  0b1111011001011111,
  0b1111111000111111,
  0b1111111010111111,
  0b1111110111011111,
  0b1111101111101111,
  0b1111110011110111,
  0b1111111011100111,
  0b1111110011111111},

 {0b1111111111111111,
  0b1111100111111111,
  0b1111000011111111,
  0b1111100111111111,
  0b1111110011111111,
  0b1111110001111111,
  0b1111110010111111,
  0b1111100001011111,
  0b1111011001011111,
  0b1111111000111111,
  0b1111111010111111,
  0b1111110110111111,
  0b1111101111001111,
  0b1111110011101111,
  0b1111111101001111,
  0b1111110001111111},
  
 {0b1111111111111111,
  0b1111100111111111,
  0b1111000011111111,
  0b1111100111111111,
  0b1111110011111111,
  0b1111110011111111,
  0b1111110001111111,
  0b1111110010111111,
  0b1111111000111111,
  0b1111111001111111,
  0b1111111001111111,
  0b1111110101111111,
  0b1111110110111111,
  0b1111111011011111,
  0b1111111101011111,
  0b1111111001111111}, 

 {0b1111111111111111,
  0b1111100111111111,
  0b1111000011111111,
  0b1111100111111111,
  0b1111110011111111,
  0b1111110001111111,
  0b1111110001111111,
  0b1111110001111111,
  0b1111111001111111,
  0b1111111001111111,
  0b1111111001111111,
  0b1111111001111111,
  0b1111111101111111,
  0b1111111101111111,
  0b1111111101111111,
  0b1111111001111111}, 

 {0b1111111111111111,
  0b1111100111111111,
  0b1111000011111111,
  0b1111100111111111,
  0b1111110011111111,
  0b1111110001111111,
  0b1111110010111111,
  0b1111110000111111,
  0b1111111000111111,
  0b1111111001111111,
  0b1111111001111111,
  0b1111110001111111,
  0b1111110110111111,
  0b1111111011011111,
  0b1111100011101111,
  0b1111111111111111},
  
 {0b1111111111111111,
  0b1111001111111111,
  0b1110000111111111,
  0b1111001111111111,
  0b1111100111111111,
  0b1111100011111111,
  0b1111100001111111,
  0b1111100010111111,
  0b1111110010111111,
  0b1111110001111111,
  0b1111110101111111,
  0b1111101110111111,
  0b1111101111011111,
  0b1110001111100111,
  0b1111111111110111,
  0b1111111111111111},   

 {0b1111111111111111,
  0b1111001111111111,
  0b1110000111111111,
  0b1111001111111111,
  0b1111100111111111,
  0b1111100001111111,
  0b1111100010111111,
  0b1111010011011111,
  0b1110110011011111,
  0b1111110001111111,
  0b1111110101111111,
  0b1111101110001111,
  0b1111101111110111,
  0b1111101111100111,
  0b1110011111111111,
  0b1111111111111111},
  
 {0b1111111001111111,
  0b1111110000111111,
  0b1111111001111111,
  0b1111111001111111,
  0b1111110000111111,
  0b1111110000111111,
  0b1111100000011111,
  0b1111100000011111,
  0b1111001001001111,
  0b1111001001001111,
  0b1111011001101111,
  0b1111011001101111,
  0b1111110110111111,
  0b1111100110011111,
  0b1111100110011111,
  0b1110000110000111}
 };

static bool NextFrame = true;
static unsigned char ActiveDisplayRow  = 0xFF;

static unsigned int OperateLedsRow = 0;
static unsigned int OperateLedsRow2 = 0;

static unsigned char OperateImage = 0;
static unsigned char iImage = 0;
static unsigned int iRunStop = 0;
static bool Run = true;

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