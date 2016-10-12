/*
 * File:   main.c
 * Author: Jeremy Siebers
 *
 * Created on June 27 2016 10:24 PM
 */
// PIC16F648A Configuration Bit Settings

// 'C' source line config statements

#include <xc.h>

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

// CONFIG
#pragma config FOSC = HS        // Oscillator Selection bits (HS oscillator: High-speed crystal/resonator on RA6/OSC2/CLKOUT and RA7/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = OFF      // RA5/MCLR/VPP Pin Function Select bit (RA5/MCLR/VPP pin function is digital input, MCLR internally tied to VDD)
#pragma config BOREN = OFF      // Brown-out Detect Enable bit (BOD disabled)
#pragma config LVP = OFF        // Low-Voltage Programming Enable bit (RB4/PGM pin has digital I/O function, HV on MCLR must be used for programming)
#pragma config CPD = OFF        // Data EE Memory Code Protection bit (Data memory code protection off)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)


#include <xc.h>
//#include <stdlib.h>
//#include <stdio.h>
#include <stdbool.h>

#include "main.h"
#include "Peripherals/config.h"

const unsigned int GreenLeds[8][16] ={
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
 };

bool NextFrame = true;
static unsigned char ActiveDisplayRow  = 0xFF;
static unsigned char ActiveDisplayRow2 = 0xFF;

static unsigned int OperateLedsRow = 0;
static unsigned int OperateLedsRow2 = 0;

static unsigned char OperateImage = 0;

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
                ActiveDisplayRow = 0xFE;ActiveDisplayRow2 = 0xFE;}
            if(OperateLedsRow == 1){
                ActiveDisplayRow = 0xFD;ActiveDisplayRow2 = 0xFD;}
            if(OperateLedsRow == 2){
                ActiveDisplayRow = 0xFB;ActiveDisplayRow2 = 0xFB;}
            if(OperateLedsRow == 3){
                ActiveDisplayRow = 0xFB;ActiveDisplayRow2 = 0xFB;}
            if(OperateLedsRow == 4){
                ActiveDisplayRow = 0xEF;ActiveDisplayRow2 = 0xEF;}
            if(OperateLedsRow == 5){
                ActiveDisplayRow = 0xDF;ActiveDisplayRow2 = 0xDF;}
            if(OperateLedsRow == 6){
                ActiveDisplayRow = 0xBF;ActiveDisplayRow2 = 0xBF;}
            if(OperateLedsRow == 7){
                ActiveDisplayRow = 0x7F;ActiveDisplayRow2 = 0x7F;}
            
            if (Select)
            {
                GreenCol1Byte = Byte(OperateImage, OperateLedsRow,  0);
                GreenCol2Byte = Byte(OperateImage, OperateLedsRow,  1);
                GreenCol3Byte = Byte(OperateImage, OperateLedsRow2, 0);
                GreenCol4Byte = Byte(OperateImage, OperateLedsRow2, 1);

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

                RedCol1Byte = Byte(OperateImage, OperateLedsRow , 0);
                RedCol2Byte = Byte(OperateImage, OperateLedsRow , 1);
                RedCol3Byte = Byte(OperateImage, OperateLedsRow2, 0);
                RedCol4Byte = Byte(OperateImage, OperateLedsRow2, 1);
            }
        }
        
        if (ImageFrameCounter > 50)
        {
            ImageFrameCounter = 0;
            
            OperateImage++;
            if (OperateImage > 7)
            {
                OperateImage = 0;
            }
        }
    }
}

unsigned int Byte(unsigned char Image,unsigned char Row, unsigned char Index)
{
    unsigned int ReturnByte = 0;
    //unsigned char mIndex = 0;
    
    if(Index == 0){
        //mIndex = 0;
        ReturnByte |= ((GreenLeds[Image][Row] & 0x8000) >> 8);//>> 15);
        ReturnByte |= ((GreenLeds[Image][Row] & 0x4000) >> 8);//>> 13);
        ReturnByte |= ((GreenLeds[Image][Row] & 0x2000) >> 8);//>> 11);
        ReturnByte |= ((GreenLeds[Image][Row] & 0x1000) >> 8);//>> 9);
        ReturnByte |= ((GreenLeds[Image][Row] & 0x0800) >> 8);//>> 7);
        ReturnByte |= ((GreenLeds[Image][Row] & 0x0400) >> 8);//>> 5);
        ReturnByte |= ((GreenLeds[Image][Row] & 0x0200) >> 8);//>> 3);
        ReturnByte |= ((GreenLeds[Image][Row] & 0x0100) >> 8);//>> 1);        
    }                           
    else                        
    {                           
        ReturnByte |= ((GreenLeds[Image][Row] & 0x0080));// >> 7);
        ReturnByte |= ((GreenLeds[Image][Row] & 0x0040));// >> 5);
        ReturnByte |= ((GreenLeds[Image][Row] & 0x0020));// >> 3);
        ReturnByte |= ((GreenLeds[Image][Row] & 0x0010));// >> 1);
        ReturnByte |= ((GreenLeds[Image][Row] & 0x0008));// << 1);
        ReturnByte |= ((GreenLeds[Image][Row] & 0x0004));// << 3);
        ReturnByte |= ((GreenLeds[Image][Row] & 0x0002));// << 5);
        ReturnByte |= ((GreenLeds[Image][Row] & 0x0001));// << 7);         
        //mIndex = 8; 
    }
    return (ReturnByte);
}

void interrupt tc_int(void)
{
    if (PIE1bits.TMR1IE && PIR1bits.TMR1IF) 
    {
        char i, Buf;
                
        Latch = false;
        /*
        for(i=8; i > 0; i--){
            //Buf = GreenCol4Byte >> (i-1);
            //Buf &= 0x01;
            Data = ((GreenCol4Byte >> (i-1)) & 0x01);
            //__delay_us(1);
            Clock = 1;    
            //__delay_us(1);
            Clock = 0;    
            //__delay_us(1);
        }*/
        
        Data = GreenCol4Byte & 0x01;
        Clock = 1;
        Clock = 0;
        GreenCol4Byte = GreenCol4Byte >> 1;
        
        Data = GreenCol4Byte & 0x01;
        Clock = 1;
        Clock = 0;
        GreenCol4Byte = GreenCol4Byte >> 1;
        
        Data = GreenCol4Byte & 0x01;
        Clock = 1;
        Clock = 0;
        GreenCol4Byte = GreenCol4Byte >> 1;
        
        Data = GreenCol4Byte & 0x01;
        Clock = 1;
        Clock = 0;
        GreenCol4Byte = GreenCol4Byte >> 1;
        
        Data = GreenCol4Byte & 0x01;
        Clock = 1;
        Clock = 0;
        GreenCol4Byte = GreenCol4Byte >> 1;
        
        Data = GreenCol4Byte & 0x01;
        Clock = 1;
        Clock = 0;
        GreenCol4Byte = GreenCol4Byte >> 1;
        
        Data = GreenCol4Byte & 0x01;
        Clock = 1;
        Clock = 0;
        GreenCol4Byte = GreenCol4Byte >> 1;
        
        Data = GreenCol4Byte & 0x01;
        Clock = 1;
        Clock = 0;               

        
        Data = GreenCol3Byte & 0x01;
        Clock = 1;
        Clock = 0;
        GreenCol3Byte = GreenCol3Byte >> 1;
        
        Data = GreenCol3Byte & 0x01;
        Clock = 1;
        Clock = 0;
        GreenCol3Byte = GreenCol3Byte >> 1;
        
        Data = GreenCol3Byte & 0x01;
        Clock = 1;
        Clock = 0;
        GreenCol3Byte = GreenCol3Byte >> 1;
        
        Data = GreenCol3Byte & 0x01;
        Clock = 1;
        Clock = 0;
        GreenCol3Byte = GreenCol3Byte >> 1;
        
        Data = GreenCol3Byte & 0x01;
        Clock = 1;
        Clock = 0;
        GreenCol3Byte = GreenCol3Byte >> 1;
        
        Data = GreenCol3Byte & 0x01;
        Clock = 1;
        Clock = 0;
        GreenCol3Byte = GreenCol3Byte >> 1;
        
        Data = GreenCol3Byte & 0x01;
        Clock = 1;
        Clock = 0;
        GreenCol3Byte = GreenCol3Byte >> 1;
        
        Data = GreenCol3Byte & 0x01;
        Clock = 1;
        Clock = 0;               

        
        Data = GreenCol2Byte & 0x01;
        Clock = 1;
        Clock = 0;
        GreenCol2Byte = GreenCol2Byte >> 1;
        
        Data = GreenCol2Byte & 0x01;
        Clock = 1;
        Clock = 0;
        GreenCol2Byte = GreenCol2Byte >> 1;
        
        Data = GreenCol2Byte & 0x01;
        Clock = 1;
        Clock = 0;
        GreenCol2Byte = GreenCol2Byte >> 1;
        
        Data = GreenCol2Byte & 0x01;
        Clock = 1;
        Clock = 0;
        GreenCol2Byte = GreenCol2Byte >> 1;
        
        Data = GreenCol2Byte & 0x01;
        Clock = 1;
        Clock = 0;
        GreenCol2Byte = GreenCol2Byte >> 1;
        
        Data = GreenCol2Byte & 0x01;
        Clock = 1;
        Clock = 0;
        GreenCol2Byte = GreenCol2Byte >> 1;
        
        Data = GreenCol2Byte & 0x01;
        Clock = 1;
        Clock = 0;
        GreenCol2Byte = GreenCol2Byte >> 1;
        
        Data = GreenCol2Byte & 0x01;
        Clock = 1;
        Clock = 0;               

        
        Data = GreenCol1Byte & 0x01;
        Clock = 1;
        Clock = 0;
        GreenCol1Byte = GreenCol1Byte >> 1;
        
        Data = GreenCol1Byte & 0x01;
        Clock = 1;
        Clock = 0;
        GreenCol1Byte = GreenCol1Byte >> 1;
        
        Data = GreenCol1Byte & 0x01;
        Clock = 1;
        Clock = 0;
        GreenCol1Byte = GreenCol1Byte >> 1;
        
        Data = GreenCol1Byte & 0x01;
        Clock = 1;
        Clock = 0;
        GreenCol1Byte = GreenCol1Byte >> 1;
        
        Data = GreenCol1Byte & 0x01;
        Clock = 1;
        Clock = 0;
        GreenCol1Byte = GreenCol1Byte >> 1;
        
        Data = GreenCol1Byte & 0x01;
        Clock = 1;
        Clock = 0;
        GreenCol1Byte = GreenCol1Byte >> 1;
        
        Data = GreenCol1Byte & 0x01;
        Clock = 1;
        Clock = 0;
        GreenCol1Byte = GreenCol1Byte >> 1;
        
        Data = GreenCol1Byte & 0x01;
        Clock = 1;
        Clock = 0;               

        
        Data = RedCol4Byte & 0x01;
        Clock = 1;
        Clock = 0;
        RedCol4Byte = RedCol4Byte >> 1;
        
        Data = RedCol4Byte & 0x01;
        Clock = 1;
        Clock = 0;
        RedCol4Byte = RedCol4Byte >> 1;
        
        Data = RedCol4Byte & 0x01;
        Clock = 1;
        Clock = 0;
        RedCol4Byte = RedCol4Byte >> 1;
        
        Data = RedCol4Byte & 0x01;
        Clock = 1;
        Clock = 0;
        RedCol4Byte = RedCol4Byte >> 1;
        
        Data = RedCol4Byte & 0x01;
        Clock = 1;
        Clock = 0;
        RedCol4Byte = RedCol4Byte >> 1;
        
        Data = RedCol4Byte & 0x01;
        Clock = 1;
        Clock = 0;
        RedCol4Byte = RedCol4Byte >> 1;
        
        Data = RedCol4Byte & 0x01;
        Clock = 1;
        Clock = 0;
        RedCol4Byte = RedCol4Byte >> 1;
        
        Data = RedCol4Byte & 0x01;
        Clock = 1;
        Clock = 0;               

        
        Data = RedCol3Byte & 0x01;
        Clock = 1;
        Clock = 0;
        RedCol3Byte = RedCol3Byte >> 1;
        
        Data = RedCol3Byte & 0x01;
        Clock = 1;
        Clock = 0;
        RedCol3Byte = RedCol3Byte >> 1;
        
        Data = RedCol3Byte & 0x01;
        Clock = 1;
        Clock = 0;
        RedCol3Byte = RedCol3Byte >> 1;
        
        Data = RedCol3Byte & 0x01;
        Clock = 1;
        Clock = 0;
        RedCol3Byte = RedCol3Byte >> 1;
        
        Data = RedCol3Byte & 0x01;
        Clock = 1;
        Clock = 0;
        RedCol3Byte = RedCol3Byte >> 1;
        
        Data = RedCol3Byte & 0x01;
        Clock = 1;
        Clock = 0;
        RedCol3Byte = RedCol3Byte >> 1;
        
        Data = RedCol3Byte & 0x01;
        Clock = 1;
        Clock = 0;
        RedCol3Byte = RedCol3Byte >> 1;
        
        Data = RedCol3Byte & 0x01;
        Clock = 1;
        Clock = 0;               

        
        Data = RedCol2Byte & 0x01;
        Clock = 1;
        Clock = 0;
        RedCol2Byte = RedCol2Byte >> 1;
        
        Data = RedCol2Byte & 0x01;
        Clock = 1;
        Clock = 0;
        RedCol2Byte = RedCol2Byte >> 1;
        
        Data = RedCol2Byte & 0x01;
        Clock = 1;
        Clock = 0;
        RedCol2Byte = RedCol2Byte >> 1;
        
        Data = RedCol2Byte & 0x01;
        Clock = 1;
        Clock = 0;
        RedCol2Byte = RedCol2Byte >> 1;
        
        Data = RedCol2Byte & 0x01;
        Clock = 1;
        Clock = 0;
        RedCol2Byte = RedCol2Byte >> 1;
        
        Data = RedCol2Byte & 0x01;
        Clock = 1;
        Clock = 0;
        RedCol2Byte = RedCol2Byte >> 1;
        
        Data = RedCol2Byte & 0x01;
        Clock = 1;
        Clock = 0;
        RedCol2Byte = RedCol2Byte >> 1;
        
        Data = RedCol2Byte & 0x01;
        Clock = 1;
        Clock = 0;               

        
        Data = RedCol1Byte & 0x01;
        Clock = 1;
        Clock = 0;
        RedCol1Byte = RedCol1Byte >> 1;
        
        Data = RedCol1Byte & 0x01;
        Clock = 1;
        Clock = 0;
        RedCol1Byte = RedCol1Byte >> 1;
        
        Data = RedCol1Byte & 0x01;
        Clock = 1;
        Clock = 0;
        RedCol1Byte = RedCol1Byte >> 1;
        
        Data = RedCol1Byte & 0x01;
        Clock = 1;
        Clock = 0;
        RedCol1Byte = RedCol1Byte >> 1;
        
        Data = RedCol1Byte & 0x01;
        Clock = 1;
        Clock = 0;
        RedCol1Byte = RedCol1Byte >> 1;
        
        Data = RedCol1Byte & 0x01;
        Clock = 1;
        Clock = 0;
        RedCol1Byte = RedCol1Byte >> 1;
        
        Data = RedCol1Byte & 0x01;
        Clock = 1;
        Clock = 0;
        RedCol1Byte = RedCol1Byte >> 1;
        
        Data = RedCol1Byte & 0x01;
        Clock = 1;
        Clock = 0;               

        
        Data = ActiveDisplayRow & 0x01;
        Clock = 1;
        Clock = 0;
        ActiveDisplayRow = ActiveDisplayRow >> 1;
        
        Data = ActiveDisplayRow & 0x01;
        Clock = 1;
        Clock = 0;
        ActiveDisplayRow = ActiveDisplayRow >> 1;
        
        Data = ActiveDisplayRow & 0x01;
        Clock = 1;
        Clock = 0;
        ActiveDisplayRow = ActiveDisplayRow >> 1;
        
        Data = ActiveDisplayRow & 0x01;
        Clock = 1;
        Clock = 0;
        ActiveDisplayRow = ActiveDisplayRow >> 1;
        
        Data = ActiveDisplayRow & 0x01;
        Clock = 1;
        Clock = 0;
        ActiveDisplayRow = ActiveDisplayRow >> 1;
        
        Data = ActiveDisplayRow & 0x01;
        Clock = 1;
        Clock = 0;
        ActiveDisplayRow = ActiveDisplayRow >> 1;
        
        Data = ActiveDisplayRow & 0x01;
        Clock = 1;
        Clock = 0;
        ActiveDisplayRow = ActiveDisplayRow >> 1;
        
        Data = ActiveDisplayRow & 0x01;
        Clock = 1;
        Clock = 0;               

        
        Data = ActiveDisplayRow2 & 0x01;
        Clock = 1;
        Clock = 0;
        ActiveDisplayRow2 = ActiveDisplayRow2 >> 1;
        
        Data = ActiveDisplayRow2 & 0x01;
        Clock = 1;
        Clock = 0;
        ActiveDisplayRow2 = ActiveDisplayRow2 >> 1;
        
        Data = ActiveDisplayRow2 & 0x01;
        Clock = 1;
        Clock = 0;
        ActiveDisplayRow2 = ActiveDisplayRow2 >> 1;
        
        Data = ActiveDisplayRow2 & 0x01;
        Clock = 1;
        Clock = 0;
        ActiveDisplayRow2 = ActiveDisplayRow2 >> 1;
        
        Data = ActiveDisplayRow2 & 0x01;
        Clock = 1;
        Clock = 0;
        ActiveDisplayRow2 = ActiveDisplayRow2 >> 1;
        
        Data = ActiveDisplayRow2 & 0x01;
        Clock = 1;
        Clock = 0;
        ActiveDisplayRow2 = ActiveDisplayRow2 >> 1;
        
        Data = ActiveDisplayRow2 & 0x01;
        Clock = 1;
        Clock = 0;
        ActiveDisplayRow2 = ActiveDisplayRow2 >> 1;
        
        Data = ActiveDisplayRow2 & 0x01;
        Clock = 1;
        Clock = 0;     
        /*
        for(i=8; i > 0; i--){
            Data = ((GreenCol3Byte >> (i-1)) & 0x01);
            //__delay_us(1);
            Clock = 1;
            //__delay_us(1);
            Clock = 0;
            //__delay_us(1);
        }
        for(i=8; i > 0; i--){
            Data = ((GreenCol2Byte >> (i-1)) & 0x01);
            //__delay_us(1);
            Clock = 1;
            //__delay_us(1);
            Clock = 0;
            //__delay_us(1);
        }
        for(i=8; i > 0; i--){
            Data = ((GreenCol1Byte >> (i-1)) & 0x01);
            //__delay_us(1);
            Clock = 1;
            //__delay_us(1);
            Clock = 0;
            //__delay_us(1);
        }
        for(i=8; i > 0; i--){
            Data = ((RedCol4Byte >> (i-1)) & 0x01);
            //__delay_us(1);
            Clock = 1;
            //__delay_us(1);
            Clock = 0;
            //__delay_us(1);
        }
        for(i=8; i > 0; i--){
            Data = ((RedCol3Byte >> (i-1)) & 0x01);
            //__delay_us(1);
            Clock = 1;
            //__delay_us(1);
            Clock = 0;
            //__delay_us(1);
        }
        for(i=8; i > 0; i--){
            Data = ((RedCol2Byte >> (i-1)) & 0x01);
            //__delay_us(1);
            Clock = 1;
            //__delay_us(1);
            Clock = 0;
            //__delay_us(1);
        }
        for(i=8; i > 0; i--){
            Data = ((RedCol1Byte >> (i-1)) & 0x01);
            //__delay_us(1);
            Clock = 1;
            //__delay_us(1);
            Clock = 0;
            //__delay_us(1);
        }
        for(i=8; i > 0; i--){
            Data = ((ActiveDisplayRow >> (i-1)) & 0x01);
            //__delay_us(1);
            Clock = 1;
            //__delay_us(1);
            Clock = 0;
            //__delay_us(1);
        }
        for(i=8; i > 0; i--){
            Data = ((ActiveDisplayRow >> (i-1)) & 0x01);
            //__delay_us(1);
            Clock = 1;
            //__delay_us(1);
            Clock = 0;
            //__delay_us(1);
        }*/
        Data = 0;        
        Latch = true;
        
        OperateLedsRow++;
        if (OperateLedsRow > 7)
        {
            OperateLedsRow = 0;
            //Led1 = !Led1;
        }
        OperateLedsRow2 = OperateLedsRow + 8;
        
        TMR1H = 0xE8;                                                           // 0xF4 ~74Hz
        TMR1L = 0x00;
        NextFrame = true;        
        ImageFrameCounter++;
        PIR1bits.TMR1IF=0;
    }
}