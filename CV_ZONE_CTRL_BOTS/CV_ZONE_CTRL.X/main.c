/*
 * File:   main.c
 * Author: Jeremy
 *
 * Created on March 23, 2012, 7:31 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include "p18cxxx.h"

// PIC18F4550 Configuration Bit Settings
// CONFIG1L
#pragma config PLLDIV = 2       	// PLL Prescaler Selection bits (No prescale (4 MHz oscillator input drives PLL directly))
#pragma config CPUDIV = OSC1_PLL2	// System Clock Postscaler Selection bits ([Primary Oscillator Src: /1][96 MHz PLL Src: /2])
#pragma config USBDIV = 2       	// USB Clock Selection bit (used in Full-Speed USB mode only; UCFG:FSEN = 1) (USB clock source comes directly from the primary oscillator block with no postscale)
// CONFIG1H
#pragma config FOSC = INTOSCIO_EC	// Oscillator Selection bits (Internal oscillator, port function on RA6, EC used by USB (INTIO))
#pragma config FCMEN = OFF      	// Fail-Safe Clock Monitor Enable bit (Fail-Safe Clock Monitor disabled)
#pragma config IESO = OFF       	// Internal/External Oscillator Switchover bit (Oscillator Switchover mode disabled)
// CONFIG2L
#pragma config PWRT = ON       		// Power-up Timer Enable bit (PWRT disabled)
#pragma config BOR = ON        		// Brown-out Reset Enable bits (Brown-out Reset disabled in hardware and software)
#pragma config BORV = 0         	// Brown-out Reset Voltage bits (Minimum setting)
#pragma config VREGEN = OFF     	// USB Voltage Regulator Enable bit (USB voltage regulator disabled)
// CONFIG2H
#pragma config WDT = OFF         	// Watchdog Timer Enable bit (WDT disabled (control is placed on the SWDTEN bit))
#pragma config WDTPS = 512              // Watchdog Timer Postscale Select bits (1:512) = 2 seconds
// CONFIG3H
#pragma config CCP2MX = ON      	// CCP2 MUX bit (CCP2 input/output is multiplexed with RC1)
#pragma config PBADEN = OFF     	// PORTB A/D Enable bit (PORTB<4:0> pins are configured as digital I/O on Reset)
#pragma config LPT1OSC = OFF    	// Low-Power Timer 1 Oscillator Enable bit (Timer1 configured for higher power operation)
#pragma config MCLRE = ON       	// MCLR Pin Enable bit (MCLR pin enabled; RE3 input pin disabled)
// CONFIG4L
#pragma config STVREN = ON      	// Stack Full/Underflow Reset Enable bit (Stack full/underflow will cause Reset)
#pragma config LVP = OFF        	// Single-Supply ICSP Enable bit (Single-Supply ICSP enabled)
#pragma config ICPRT = OFF      	// Dedicated In-Circuit Debug/Programming Port (ICPORT) Enable bit (ICPORT disabled)
#pragma config XINST = OFF      	// Extended Instruction Set Enable bit (Instruction set extension and Indexed Addressing mode disabled (Legacy mode))
// CONFIG5L
#pragma config CP0 = ON            	// Code Protection bit (Block 0 (000800-001FFFh) is not code-protected)
#pragma config CP1 = ON          	// Code Protection bit (Block 1 (002000-003FFFh) is not code-protected)
#pragma config CP2 = ON          	// Code Protection bit (Block 2 (004000-005FFFh) is not code-protected)
#pragma config CP3 = ON          	// Code Protection bit (Block 3 (006000-007FFFh) is not code-protected)
// CONFIG5H
#pragma config CPB = OFF        	// Boot Block Code Protection bit (Boot block (000000-0007FFh) is not code-protected)
#pragma config CPD = OFF        	// Data EEPROM Code Protection bit (Data EEPROM is not code-protected)
// CONFIG6L
#pragma config WRT0 = OFF       	// Write Protection bit (Block 0 (000800-001FFFh) is not write-protected)
#pragma config WRT1 = OFF       	// Write Protection bit (Block 1 (002000-003FFFh) is not write-protected)
#pragma config WRT2 = OFF       	// Write Protection bit (Block 2 (004000-005FFFh) is not write-protected)
#pragma config WRT3 = OFF       	// Write Protection bit (Block 3 (006000-007FFFh) is not write-protected)
// CONFIG6H
#pragma config WRTC = OFF       	// Configuration Register Write Protection bit (Configuration registers (300000-3000FFh) are not write-protected)
#pragma config WRTB = OFF       	// Boot Block Write Protection bit (Boot block (000000-0007FFh) is not write-protected)
#pragma config WRTD = OFF       	// Data EEPROM Write Protection bit (Data EEPROM is not write-protected)
// CONFIG7L
#pragma config EBTR0 = OFF      	// Table Read Protection bit (Block 0 (000800-001FFFh) is not protected from table reads executed in other blocks)
#pragma config EBTR1 = OFF      	// Table Read Protection bit (Block 1 (002000-003FFFh) is not protected from table reads executed in other blocks)
#pragma config EBTR2 = OFF      	// Table Read Protection bit (Block 2 (004000-005FFFh) is not protected from table reads executed in other blocks)
#pragma config EBTR3 = OFF      	// Table Read Protection bit (Block 3 (006000-007FFFh) is not protected from table reads executed in other blocks)
// CONFIG7H
#pragma config EBTRB = OFF      	// Boot Block Table Read Protection bit (Boot block (000000-0007FFh) is not protected from table reads executed in other blocks)

#include "main.h"
#include "cv_controller.h"
#include "cv.h"

#define TMR2SEC                     29						// Internall osc dependent correction value to count seconds depending on chosen scaler of timer 0

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
    TRISA = 0xFF; TRISB = 0xFF; TRISC = 0xFF; TRISD = 0xFF; TRISE = 0xFF;	// Set all ports to inputs
    ADCON1bits.PCFG = 0xD;							// Set only AN0 and AN1 (RA0 and RA1)
    ADCON1bits.VCFG0 = 0;                                                       // Set VDD voltage ref
    ADCON1bits.VCFG1 = 0;                                                       // Set VSS voltgae ref
    ADCON0bits.ADON = 1;							// Set AD off
    ADCON2 = 0xB8;                                                              // Long time acquisition and log conversion
    CCP1CONbits.CCP1M = 0x00;                                                   // Set CCP1M off
    UCONbits.USBEN = 0;                                                         // Disable USB
    UCFGbits.UTRDIS = 1;							// Disable internall USB transceiver
    INTCON2bits.RBPU = 0;							// Disable internall pullup resistors
    TRISA = 0xFF;TRISB = 0x00;TRISC = 0x3F;TRISD = 0x03;TRISE = 0xFF;           // Configure IO
    PORTA = 0; PORTB = 0; PORTC = 0; PORTD = 0; PORTE = 0;			// Set all ports OFF to be sure
}

static void Init_Osc(void)
{
    OSCCONbits.IDLEN    = 0;                                                    // Set the internall oscillator and put it to 8MHz
    OSCCONbits.IRCF0    = 1;
    OSCCONbits.IRCF1    = 1;
    OSCCONbits.IRCF2    = 1;
    OSCCONbits.SCS0     = 1;
    OSCCONbits.SCS1     = 1;
    OSCTUNEbits.TUN     = 0b11111;                                              // Raise the internall OSC to aquire 1 second tick
}

static void Init_Timers(void)
{
	RCONbits.IPEN 		= 1;        					// dis/(en)able priority levels
	INTCONbits.GIEH		= 1;						// When IPEN = 1: 1 = Enables all high priority interrupts
	INTCONbits.GIEL		= 0;						// Disable low interrupts
	INTCONbits.TMR0IE 	= 1;						// TMR0 Interrupt enable
	INTCON2bits.TMR0IP	= 1;						// TMR0 High Interrupt
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
