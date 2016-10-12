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
    
}

void IO_Configuration(void) {    
    TRISA = 0xFF;
    TRISB = 0xFF;
    TRISC = 0xFF;
                        
    PORTB = 0x00;
    PORTA = 0x00;
    PORTC = 0x00;
        
    TRISBbits.TRISB5 = 1;                   // Select input
    TRISAbits.TRISA2 = 0;                   // Led1 output    
    TRISCbits.TRISC0 = 0;                   // Latch output
    TRISCbits.TRISC3 = 0;                   // Clock output
    TRISCbits.TRISC5 = 0;                   // Data output
}

void Interrupt_Configuration(){  
    INTCON = 0;
    INTCONbits.PEIE = 1;
    INTCONbits.GIE = 1;
}

void Timer1_Configuration(void){
    T1CONbits.T1CKPS = 0;
    T1CONbits.T1OSCEN = 0;
    T1CONbits.nT1SYNC = 1;
    T1CONbits.TMR1CS = 0;
    PIR1bits.TMR1IF = 0;
    PIE1bits.TMR1IE = 1;
    T1CONbits.TMR1ON = 1;    
}

void Adconverter_Configuration(){
    
    ADCON0bits.ADON = 0;
    ADCON1bits.PCFG = 7;
}

void MSSP_Configuration(){
    SSPSTATbits.CKE  = 1;            // 1 = Transmit occurs on transition from active to Idle clock state
    SSPSTATbits.SMP  = 0;            // 0 = Input data sampled at middle of data output time (master)
    
    SSPCONbits.CKP   = 0;            // 0 = Idle state for clock is a low level
    SSPCONbits.SSPM  = 0;            // SPI Master mode, clock = FOSC/4
    SSPCONbits.SSPEN = 1;            // Enables serial port and configures SCK, SDO, SDI and SS as serial port pins
    
    PIE1bits.SSPIE   = 0;            // 0 = Disables the SSP interrupt
}