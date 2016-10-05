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
//#include <stdlib.h>
//#include <stdio.h>
#include <stdbool.h>

#include "main.h"
#include "Peripherals/config.h"
/*
const unsigned char GreenLeds0[16][16] = 
     {{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
      {1,1,1,1,0,0,1,1,1,1,1,1,1,1,1,1},
      {1,1,1,0,0,0,0,1,1,1,1,1,1,1,1,1},
      {1,1,1,1,0,0,1,1,1,1,1,1,1,1,1,1},
      {1,1,1,1,1,0,0,1,1,1,1,1,1,1,1,1},
      {1,1,1,1,1,0,0,0,0,1,1,1,1,1,1,1},
      {1,1,1,1,1,0,0,0,1,0,1,1,1,1,1,1},
      {1,1,1,1,0,1,0,0,1,1,0,1,1,1,1,1},
      {1,1,1,0,1,1,0,0,1,1,0,1,1,1,1,1},
      {1,1,1,1,1,1,0,0,0,1,1,1,1,1,1,1},
      {1,1,1,1,1,1,0,1,0,1,1,1,1,1,1,1},
      {1,1,1,1,1,0,1,1,1,0,0,1,1,1,1,1},
      {1,1,1,1,1,0,1,1,1,1,1,0,0,1,1,1},
      {1,1,1,1,1,0,1,1,1,1,1,1,0,1,1,1},
      {1,1,1,0,0,1,1,1,1,1,1,0,1,1,1,1},
      {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}};*/

const unsigned int GreenLeds0 [16] =
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
 0b1111111111111111};

/*
const unsigned int GreenLeds0[16][16] = 
     {{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
      {1,1,1,1,1,0,0,1,1,1,1,1,1,1,1,1},
      {1,1,1,1,0,0,0,0,1,1,1,1,1,1,1,1},
      {1,1,1,1,1,0,0,1,1,1,1,1,1,1,1,1},
      {1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,1},
      {1,1,1,1,1,1,0,0,0,1,1,1,1,1,1,1},
      {1,1,1,1,1,1,0,0,1,0,1,1,1,1,1,1},
      {1,1,1,1,1,0,0,0,0,1,0,1,1,1,1,1},
      {1,1,1,1,0,1,1,0,0,1,0,1,1,1,1,1},
      {1,1,1,1,1,1,1,0,0,0,1,1,1,1,1,1},
      {1,1,1,1,1,1,1,0,1,0,1,1,1,1,1,1},
      {1,1,1,1,1,1,0,1,1,1,0,1,1,1,1,1},
      {1,1,1,1,1,0,1,1,1,1,1,0,1,1,1,1},
      {1,1,1,1,1,1,0,0,1,1,1,1,0,1,1,1},
      {1,1,1,1,1,1,1,0,1,1,1,0,0,1,1,1},
      {1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,1}};

const unsigned int GreenLeds2[16][16] =
     {{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
      {1,1,1,1,1,0,0,1,1,1,1,1,1,1,1,1},
      {1,1,1,1,0,0,0,0,1,1,1,1,1,1,1,1},
      {1,1,1,1,1,0,0,1,1,1,1,1,1,1,1,1},
      {1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,1},
      {1,1,1,1,1,1,0,0,0,1,1,1,1,1,1,1},
      {1,1,1,1,1,1,0,0,1,0,1,1,1,1,1,1},
      {1,1,1,1,1,0,0,0,0,1,0,1,1,1,1,1},
      {1,1,1,1,0,1,1,0,0,1,0,1,1,1,1,1},
      {1,1,1,1,1,1,1,0,0,0,1,1,1,1,1,1},
      {1,1,1,1,1,1,1,0,1,0,1,1,1,1,1,1},
      {1,1,1,1,1,1,0,1,1,0,1,1,1,1,1,1},
      {1,1,1,1,1,0,1,1,1,1,0,0,1,1,1,1},
      {1,1,1,1,1,1,0,0,1,1,1,0,1,1,1,1},
      {1,1,1,1,1,1,1,1,0,1,0,0,1,1,1,1},
      {1,1,1,1,1,1,0,0,0,1,1,1,1,1,1,1}};

const unsigned int GreenLeds3[16][16] =
     {{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
      {1,1,1,1,1,0,0,1,1,1,1,1,1,1,1,1},
      {1,1,1,1,0,0,0,0,1,1,1,1,1,1,1,1},
      {1,1,1,1,1,0,0,1,1,1,1,1,1,1,1,1},
      {1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,1},
      {1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,1},
      {1,1,1,1,1,1,0,0,0,1,1,1,1,1,1,1},
      {1,1,1,1,1,1,0,0,1,0,1,1,1,1,1,1},
      {1,1,1,1,1,1,1,0,0,0,1,1,1,1,1,1},
      {1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1},
      {1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1},
      {1,1,1,1,1,1,0,1,0,1,1,1,1,1,1,1},
      {1,1,1,1,1,1,0,1,1,0,1,1,1,1,1,1},
      {1,1,1,1,1,1,1,0,1,1,0,1,1,1,1,1},
      {1,1,1,1,1,1,1,1,0,1,0,1,1,1,1,1},
      {1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1}};

const unsigned int GreenLeds4[16][16] =
     {{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
      {1,1,1,1,1,0,0,1,1,1,1,1,1,1,1,1},
      {1,1,1,1,0,0,0,0,1,1,1,1,1,1,1,1},
      {1,1,1,1,1,0,0,1,1,1,1,1,1,1,1,1},
      {1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,1},
      {1,1,1,1,1,1,0,0,0,1,1,1,1,1,1,1},
      {1,1,1,1,1,1,0,0,0,1,1,1,1,1,1,1},
      {1,1,1,1,1,1,0,0,0,1,1,1,1,1,1,1},
      {1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1},
      {1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1},
      {1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1},
      {1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1},
      {1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1},
      {1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1},
      {1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1},
      {1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1}};

const unsigned int GreenLeds5[16][16] =
     {{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
      {1,1,1,1,1,0,0,1,1,1,1,1,1,1,1,1},
      {1,1,1,1,0,0,0,0,1,1,1,1,1,1,1,1},
      {1,1,1,1,1,0,0,1,1,1,1,1,1,1,1,1},
      {1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,1},
      {1,1,1,1,1,1,0,0,0,1,1,1,1,1,1,1},
      {1,1,1,1,1,1,0,0,1,0,1,1,1,1,1,1},
      {1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1},
      {1,1,1,1,1,1,1,0,0,0,1,1,1,1,1,1},
      {1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1},
      {1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1},
      {1,1,1,1,1,1,0,0,0,1,1,1,1,1,1,1},
      {1,1,1,1,1,1,0,1,1,0,1,1,1,1,1,1},
      {1,1,1,1,1,1,1,0,1,1,0,1,1,1,1,1},
      {1,1,1,1,1,0,0,0,1,1,1,0,1,1,1,1},
      {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}};

const unsigned int GreenLeds6[16][16] =
     {{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
      {1,1,1,1,0,0,1,1,1,1,1,1,1,1,1,1},
      {1,1,1,0,0,0,0,1,1,1,1,1,1,1,1,1},
      {1,1,1,1,0,0,1,1,1,1,1,1,1,1,1,1},
      {1,1,1,1,1,0,0,1,1,1,1,1,1,1,1,1},
      {1,1,1,1,1,0,0,0,1,1,1,1,1,1,1,1},
      {1,1,1,1,1,0,0,0,0,1,1,1,1,1,1,1},
      {1,1,1,1,1,0,0,0,1,0,1,1,1,1,1,1},
      {1,1,1,1,1,1,0,0,1,0,1,1,1,1,1,1},
      {1,1,1,1,1,1,0,0,0,1,1,1,1,1,1,1},
      {1,1,1,1,1,1,0,1,0,1,1,1,1,1,1,1},
      {1,1,1,1,1,0,1,1,1,0,1,1,1,1,1,1},
      {1,1,1,1,1,0,1,1,1,1,0,1,1,1,1,1},
      {1,1,1,0,0,0,1,1,1,1,1,0,0,1,1,1},
      {1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1},
      {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}};


const unsigned int GreenLeds7[16][16] =
     {{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
      {1,1,1,1,0,0,1,1,1,1,1,1,1,1,1,1},
      {1,1,1,0,0,0,0,1,1,1,1,1,1,1,1,1},
      {1,1,1,1,0,0,1,1,1,1,1,1,1,1,1,1},
      {1,1,1,1,1,0,0,1,1,1,1,1,1,1,1,1},
      {1,1,1,1,1,0,0,0,0,1,1,1,1,1,1,1},
      {1,1,1,1,1,0,0,0,1,0,1,1,1,1,1,1},
      {1,1,1,1,0,1,0,0,1,1,0,1,1,1,1,1},
      {1,1,1,0,1,1,0,0,1,1,0,1,1,1,1,1},
      {1,1,1,1,1,1,0,0,0,1,1,1,1,1,1,1},
      {1,1,1,1,1,1,0,1,0,1,1,1,1,1,1,1},
      {1,1,1,1,1,0,1,1,1,0,0,0,1,1,1,1},
      {1,1,1,1,1,0,1,1,1,1,1,1,0,1,1,1},
      {1,1,1,1,1,0,1,1,1,1,1,0,0,1,1,1},
      {1,1,1,0,0,1,1,1,1,1,1,1,1,1,1,1},
      {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}};*/

bool NextFrame = true;
static unsigned char ActiveDisplayRow = 0xFF;

static unsigned char OperateLedsRow = 0;
static unsigned char OperateLedsRow2 = 0;

static unsigned char OperateImage = 0;

static unsigned char GreenCol1Byte = 0xFF;
static unsigned char GreenCol2Byte = 0xFF;
static unsigned char GreenCol3Byte = 0xFF;
static unsigned char GreenCol4Byte = 0xFF;

static unsigned char RedCol1Byte = 0xFF;
static unsigned char RedCol2Byte = 0xFF;
static unsigned char RedCol3Byte = 0xFF;
static unsigned char RedCol4Byte = 0xFF;


void main(void) {
    // Initialize the device
    SYSTEM_Initialize();
       
    while(1)
    {        
        if(PIR1bits.TMR1IF == false && NextFrame == true)
        {
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
            
            if (Select)
            {
                GreenCol1Byte = Byte( OperateLedsRow , 0);
                GreenCol2Byte = Byte( OperateLedsRow , 1);
                GreenCol3Byte = Byte( OperateLedsRow2, 0);
                GreenCol4Byte = Byte( OperateLedsRow2, 1);

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

                RedCol1Byte = Byte( OperateLedsRow , 0);
                RedCol2Byte = Byte( OperateLedsRow , 1);
                RedCol3Byte = Byte( OperateLedsRow2, 0);
                RedCol4Byte = Byte( OperateLedsRow2, 1);
            }
        }
    }
}
/*
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
 0b1111111111111111};*/

unsigned char Byte(unsigned char Row, unsigned char Index)
{
    unsigned char ReturnByte = 0;
    //unsigned char mIndex = 0;
    
    if(Index == 0){
        //mIndex = 0;
        ReturnByte |= (GreenLeds0[Row] & 0x8000) >> 15;
        ReturnByte |= (GreenLeds0[Row] & 0x4000) >> 14;
        ReturnByte |= (GreenLeds0[Row] & 0x2000) >> 13;
        ReturnByte |= (GreenLeds0[Row] & 0x1000) >> 12;
        ReturnByte |= (GreenLeds0[Row] & 0x0800) >> 11;
        ReturnByte |= (GreenLeds0[Row] & 0x0400) >> 10;
        ReturnByte |= (GreenLeds0[Row] & 0x0200) >> 9;
        ReturnByte |= (GreenLeds0[Row] & 0x0100) >> 8;        
    }
    else
    {
        ReturnByte |= (GreenLeds0[Row] & 0x0080) >> 7;
        ReturnByte |= (GreenLeds0[Row] & 0x0040) >> 6;
        ReturnByte |= (GreenLeds0[Row] & 0x0020) >> 5;
        ReturnByte |= (GreenLeds0[Row] & 0x0010) >> 4;
        ReturnByte |= (GreenLeds0[Row] & 0x0008) >> 3;
        ReturnByte |= (GreenLeds0[Row] & 0x0004) >> 2;
        ReturnByte |= (GreenLeds0[Row] & 0x0002) >> 1;
        ReturnByte |= (GreenLeds0[Row] & 0x0001); 
        //mIndex = 8; 
    }
    /*
    ReturnByte |= GreenLeds0[Row][mIndex];
    mIndex++;
    ReturnByte |= GreenLeds0[Row][mIndex] << 1;
    mIndex++;
    ReturnByte |= GreenLeds0[Row][mIndex] << 2;
    mIndex++;
    ReturnByte |= GreenLeds0[Row][mIndex] << 3;
    mIndex++;
    ReturnByte |= GreenLeds0[Row][mIndex] << 4;
    mIndex++;
    ReturnByte |= GreenLeds0[Row][mIndex] << 5;
    mIndex++;
    ReturnByte |= GreenLeds0[Row][mIndex] << 6;
    mIndex++;
    ReturnByte |= GreenLeds0[Row][mIndex] << 7;
    mIndex++;*/
    
    return (ReturnByte);
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
            Led1 = !Led1;
        }
        OperateLedsRow2 = OperateLedsRow + 8;
        
        TMR1H = 0xF4;                                                           // 0xF4 ~74Hz
        TMR1L = 0x00;
        NextFrame = true;
        PIR1bits.TMR1IF=0;
    }
}