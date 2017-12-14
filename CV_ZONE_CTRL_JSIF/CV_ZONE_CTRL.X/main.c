/*
 * File:   main.c
 * Author: Jeremy
 * CV FRANSEBAAN 105
 * Created on March 23, 2012, 7:31 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include "p18cxxx.h"


// PIC18F46K22 Configuration Bit Settings

#include <p18F46K22.h>

// CONFIG1H
#pragma config FOSC = INTIO67   // Oscillator Selection bits (Internal oscillator block)
#pragma config PLLCFG = OFF     // 4X PLL Enable (Oscillator used directly)
#pragma config PRICLKEN = ON    // Primary clock enable bit (Primary clock is always enabled)
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enable bit (Fail-Safe Clock Monitor disabled)
#pragma config IESO = OFF       // Internal/External Oscillator Switchover bit (Oscillator Switchover mode disabled)

// CONFIG2L
#pragma config PWRTEN = ON      // Power-up Timer Enable bit (Power up timer enabled)
#pragma config BOREN = SBORDIS  // Brown-out Reset Enable bits (Brown-out Reset enabled in hardware only (SBOREN is disabled))
#pragma config BORV = 285       // Brown Out Reset Voltage bits (VBOR set to 2.85 V nominal)

// CONFIG2H
#pragma config WDTEN = ON       // Watchdog Timer Enable bits (WDT is always enabled. SWDTEN bit has no effect)
#pragma config WDTPS = 512      // Watchdog Timer Postscale Select bits (1:512) = 2 seconds

// CONFIG3H
#pragma config CCP2MX = PORTC1  // CCP2 MUX bit (CCP2 input/output is multiplexed with RC1)
#pragma config PBADEN = OFF     // PORTB A/D Enable bit (PORTB<5:0> pins are configured as digital I/O on Reset)
#pragma config CCP3MX = PORTB5  // P3A/CCP3 Mux bit (P3A/CCP3 input/output is multiplexed with RB5)
#pragma config HFOFST = ON      // HFINTOSC Fast Start-up (HFINTOSC output and ready status are not delayed by the oscillator stable status)
#pragma config T3CMX = PORTC0   // Timer3 Clock input mux bit (T3CKI is on RC0)
#pragma config P2BMX = PORTD2   // ECCP2 B output mux bit (P2B is on RD2)
#pragma config MCLRE = EXTMCLR  // MCLR Pin Enable bit (MCLR pin enabled, RE3 input pin disabled)

// CONFIG4L
#pragma config STVREN = ON      // Stack Full/Underflow Reset Enable bit (Stack full/underflow will cause Reset)
#pragma config LVP = OFF        // Single-Supply ICSP Enable bit (Single-Supply ICSP disabled)
#pragma config XINST = OFF      // Extended Instruction Set Enable bit (Instruction set extension and Indexed Addressing mode disabled (Legacy mode))

// CONFIG5L
#pragma config CP0 = OFF        // Code Protection Block 0 (Block 0 (000800-003FFFh) not code-protected)
#pragma config CP1 = OFF        // Code Protection Block 1 (Block 1 (004000-007FFFh) not code-protected)
#pragma config CP2 = OFF        // Code Protection Block 2 (Block 2 (008000-00BFFFh) not code-protected)
#pragma config CP3 = OFF        // Code Protection Block 3 (Block 3 (00C000-00FFFFh) not code-protected)

// CONFIG5H
#pragma config CPB = OFF        // Boot Block Code Protection bit (Boot block (000000-0007FFh) not code-protected)
#pragma config CPD = OFF        // Data EEPROM Code Protection bit (Data EEPROM not code-protected)

// CONFIG6L
#pragma config WRT0 = OFF       // Write Protection Block 0 (Block 0 (000800-003FFFh) not write-protected)
#pragma config WRT1 = OFF       // Write Protection Block 1 (Block 1 (004000-007FFFh) not write-protected)
#pragma config WRT2 = OFF       // Write Protection Block 2 (Block 2 (008000-00BFFFh) not write-protected)
#pragma config WRT3 = OFF       // Write Protection Block 3 (Block 3 (00C000-00FFFFh) not write-protected)

// CONFIG6H
#pragma config WRTC = OFF       // Configuration Register Write Protection bit (Configuration registers (300000-3000FFh) not write-protected)
#pragma config WRTB = OFF       // Boot Block Write Protection bit (Boot Block (000000-0007FFh) not write-protected)
#pragma config WRTD = OFF       // Data EEPROM Write Protection bit (Data EEPROM not write-protected)

// CONFIG7L
#pragma config EBTR0 = OFF      // Table Read Protection Block 0 (Block 0 (000800-003FFFh) not protected from table reads executed in other blocks)
#pragma config EBTR1 = OFF      // Table Read Protection Block 1 (Block 1 (004000-007FFFh) not protected from table reads executed in other blocks)
#pragma config EBTR2 = OFF      // Table Read Protection Block 2 (Block 2 (008000-00BFFFh) not protected from table reads executed in other blocks)
#pragma config EBTR3 = OFF      // Table Read Protection Block 3 (Block 3 (00C000-00FFFFh) not protected from table reads executed in other blocks)

// CONFIG7H
#pragma config EBTRB = OFF      // Boot Block Table Read Protection bit (Boot Block (000000-0007FFh) not protected from table reads executed in other blocks)


#include "main.h"
#include "cv_controller.h"
#include "cv.h"

#define TMR2SEC                     30						// Internall osc dependent correction value to count seconds depending on chosen scaler of timer 0 together with OSCTUNE register

static void Init_IO(void);
static void Init_Osc(void);             					// Initialize and setup Oscillators
static void Init_Timers(void);							// Initialize Timers (0)

unsigned int pulses = 0;                                			// Pulses counter to achieve 1 sec update rate
unsigned int update_tick = 0;                           			// 1 sec update tick

void main (void)
{
    Init_IO();                                          			// Initialize all IO and onstraints
    Init_Osc();                                         			// Initialize Oscillator sub routine
    Init_Timers();                                      			// Initialize seconds timer
    WDTCONbits.SWDTEN = ON;                                                     // Enable Watchdog

	while(1)								// Infinite loop
	{
            if (update_tick == ON)						// When 1 second has passed
            {
                Led1 = !Led1;                                                   // Alive status
                //Led1 = ON;                                                      // Measure execution timing trigger start
                CVxCTRLxUPDATE();						// Update the cv control application
                //Led1 = OFF;                                                     // Measure execution timing trigger end
                update_tick = FALSE;						// Reset tick variable for next second
                ClrWdt();                                                       // Every second clear the WDT
            }
	}
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Interrupt routines//

void high_isr(void);								// Set high interrupt routine and map vector
#pragma code high_vector=0x8
void interrupt_at_high_vector (void)
{
	_asm goto high_isr _endasm
}
#pragma code
#pragma interrupt high_isr
void high_isr()
{
	if (INTCONbits.TMR0IF)							// If Timer 0 interrupt
	{
                pulses++;							// Increment the pulses counter until
                if (pulses > TMR2SEC)						// it has reached the correction value for 1 second
                {
                    //Led1 = !Led1;						// Toggle led for diagnostic purposes
                    update_tick = ON;						// set the update tick
                    pulses = 0;							// reset the pulses counter to start counting the next second
                }

                //Led1 = !Led1;							// Toggle led for diagnostic purposes
                
		INTCONbits.TMR0IF = OFF;					// Clear Timer 0 interrupt flag
	}
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


//MAIN SUBROUTINES//

static void Init_IO(void)
{
    PORTA = 0; PORTB = 0; PORTC = 0; PORTD = 0; PORTE = 0;			// Set all ports OFF to be sure
    TRISA = 0xFF; TRISB = 0xFF; TRISC = 0xFF; TRISD = 0xFF; TRISE = 0xFF;	// Set all ports to inputs
    TRISA = 0xFF;TRISB = 0xC0;TRISC = 0x07;TRISD = 0x03;TRISE = 0xFF;           // Configure IO
    ANSELA = 0x03;                                                              // Set RA0 and RA1 analog input
    ANSELB = 0x00;                                                              // Set as digital IO
    ANSELC = 0x00;                                                              // Set as digital IO
    ANSELD = 0x00;                                                              // Set as digital IO
    ANSELE = 0x00;                                                              // Set as digital IO
    ADCON1 = 0x0F;                                                              // Set analog ref to VDD/VSS
    ADCON0bits.ADON = 1;							// Set AD on
    ADCON2 = 0xBC;                                                              // Long time acquisition and log conversion
    CCP1CONbits.CCP1M = 0x00;                                                   // Set CCP1M off
    VREFCON1 = 0x00;                                                            // Disable DAC
    CTMUCONH = 0x00;                                                            // Disable CTMU
    INTCON2bits.RBPU = 0;							// Disable internall pullup resistors
    CM1CON = 0x00;                                                              // Disable Comparator
    CM2CON = 0x00;                                                              // Disable Comparator
    
}

static void Init_Osc(void)
{
    OSCCONbits.IDLEN    = 0;                                                    // Set the internall oscillator and put it to 8MHz
    OSCCONbits.IRCF0    = 0;
    OSCCONbits.IRCF1    = 1;
    OSCCONbits.IRCF2    = 1;
    OSCCONbits.SCS0     = 1;
    OSCCONbits.SCS1     = 1;
    OSCTUNEbits.TUN     = 0b00001110;                                           // Raise the internall OSC to aquire 1 second tick
}

static void Init_Timers(void)
{
	RCONbits.IPEN 		= 1;        					// dis/(en)able priority levels
	INTCONbits.GIEH		= 1;						// When IPEN = 1: 1 = Enables all high priority interrupts
	INTCONbits.GIEL		= 0;						// Disable low interrupts
	INTCONbits.TMR0IE 	= 1;						// TMR0 Interrupt enable
	INTCON2bits.TMR0IP	= 1;						// TMR0 High Interrupt
        INTCONbits.RBIE         = 0;                                            // PortB interrupt enable bit
	TMR0H = 0x0;                    					// clear timer0
	TMR0L = 0x0;                    					// clear timer0
	T0CONbits.TMR0ON 	= 1;						// Timer0 On/Off Control bit 1 is On
	T0CONbits.T08BIT	= 0;						// Timer0 8-Bit/16-Bit Control bit, 8Bit is 1
	T0CONbits.T0CS 		= 0;						// Timer0 Clock Source Select bit, 0 is internall instruction cycle
	T0CONbits.T0SE 		= 0;						// Timer0 Source Edge Select bit, 0 is low to high
	T0CONbits.PSA 		= 1;						// Timer0 Prescaler Assignment bit, 0 is On
	T0CONbits.T0PS2		= 0;						// Timer0 Prescaler Select bits, 111 -> 1:256
	T0CONbits.T0PS1		= 0;						// Timer0 Prescaler Select bits, 011 -> 1:16
	T0CONbits.T0PS0		= 0;						// Timer0 Prescaler Select bits, 000 -> 1:2
}
