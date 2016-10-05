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
    Interrupt_Configuration();
    Timer1_Configuration();    
    Adconverter_Configuration();
    MSSP_Configuration();
}

void OSCILLATOR_Initialize(void) {
    OSCCONbits.SCS = 0x00;
    OSCCONbits.IRCF = 0x7;                  //8MHz
}

void IO_Configuration(void) {    
    TRISA = 0xFF;                           // RA6 and RA7 output
    TRISB = 0xFF;                           // RB6 and RB7 inputs
    TRISC = 0x00;                           
    
    PORTC = 0x00;                           
    PORTB = 0x00;
    PORTA = 0x00;
    
    TRISBbits.TRISB5 = 0;                   // Led1 output    
}

void Interrupt_Configuration(){  
    INTCON = 0;
    INTCONbits.PEIE = 1;
    INTCONbits.GIE = 1;
}

void Timer1_Configuration(void){
    T1CONbits.T1CKPS = 0;
    T1CONbits.T1OSCEN = 0;
    T1CONbits.T1SYNC = 0;
    T1CONbits.TMR1CS = 0;
    PIR1bits.TMR1IF = 0;
    PIE1bits.TMR1IE = 1;
    T1CONbits.TMR1ON = 0;    
}

void Adconverter_Configuration(){
    
    ADCON1bits.ADFM = 1;            // Right justified
    ADCON1bits.ADCS2 = 0;           // no divide clock /2
    ADCON1bits.VCFG1 = 0;           // VREF- connected to VSS
    ADCON1bits.VCFG0 = 0;           // VREF+ connected to VDD (0) otherwise to RA3
    ADCON1bits.PCFG = 0xF;          // All IO digital except RA0/RA1 --> temp sensor1/2
    
    ADCON2bits.ACQT = 3;            // 20 Tad
    
    ADCON0bits.ADCS = 0;            // Fosc/8
    ADCON0bits.CHS = 0;             // Channel 00 (AN0)
    ADCON0bits.ADON = 0;            // Enable AD converter
}

void MSSP_Configuration(){
    SSPSTATbits.CKE  = 1;            // 1 = Transmit occurs on transition from active to Idle clock state
    SSPSTATbits.SMP  = 0;            // 0 = Input data sampled at middle of data output time (master)
    
    SSPCONbits.CKP   = 0;            // 0 = Idle state for clock is a low level
    SSPCONbits.SSPM  = 0;            // SPI Master mode, clock = FOSC/4
    SSPCONbits.SSPEN = 1;            // Enables serial port and configures SCK, SDO, SDI and SS as serial port pins
    
    PIE1bits.SSPIE   = 0;            // 0 = Disables the SSP interrupt
}