/*
 * File:   config.c
 * Author: Jeremy Siebers
 *
 * Created on 27-06-2016
 */

#include "xc.h"
#include "config.h"

void SYSTEM_Initialize(void) {
    OSCILLATOR_Initialize();
    IO_Configuration();    
    Timer1_Configuration();
    Interrupt_Configuration();
    Adconverter_Configuration();
}

void OSCILLATOR_Initialize(void) {
    OSCCONbits.SCS = 0x00;
    OSCCONbits.IRCF = 0x6;//0x7;            //8MHz
}

void IO_Configuration(void) {    
    TRISA = 0x3F;                           // RA6 and RA7 output
    TRISB = 0xC0;                           // RB6 and RB7 inputs
    TRISC = 0xFF;                           
    
    PORTC = 0x00;                           
    PORTB = 0x00;
    PORTA = 0x00;
    
    TRISBbits.TRISB5 = 0;                   // Led1 output
    PORTAbits.RA6 = 0;                      // Set Default FAN ERROR
}

void Interrupt_Configuration(){  
    INTCON = 0;
    INTCONbits.PEIE = 1;
    INTCONbits.GIE = 1;
}

void Timer1_Configuration(void){
    T1CONbits.T1CKPS = 3;
    T1CONbits.T1OSCEN = 0;
    T1CONbits.T1SYNC = 0;
    T1CONbits.TMR1CS = 0;
    PIR1bits.TMR1IF = 0;
    PIE1bits.TMR1IE = 1;
    T1CONbits.TMR1ON = 1;    
}

void Adconverter_Configuration(){
    
    ADCON1bits.ADFM = 1;            // Right justified
    ADCON1bits.ADCS2 = 0;           // no divide clock /2
    ADCON1bits.VCFG1 = 0;           // VREF- connected to VSS
    ADCON1bits.VCFG0 = 0;           // VREF+ connected to VDD (0) otherwise to RA3
    ADCON1bits.PCFG = 0xD;          // All IO digital except RA0/RA1 --> temp sensor1/2
    
    ADCON2bits.ACQT = 3;            // 20 Tad
    
    ADCON0bits.ADCS = 0;            // Fosc/8
    ADCON0bits.CHS = 0;             // Channel 00 (AN0)
    ADCON0bits.ADON = 1;            // Enable AD converter
}