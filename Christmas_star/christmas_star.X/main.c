/* 
 * File:   main.c
 * Author: Jeremy
 *
 * Created on December 10, 2012, 9:36 PM
 */

#include "p18F4455.h"
#include <stdio.h>
#include <stdlib.h>

/******************************************************************************/
/*          PIC18F4455 Configuration Bit Settings                             */
/******************************************************************************/
 
// CONFIG1L
#pragma config PLLDIV = 5       // PLL Prescaler Selection bits (Divide by 5 (20 MHz oscillator input))
#pragma config CPUDIV = OSC1_PLL2// System Clock Postscaler Selection bits ([Primary Oscillator Src: /1][96 MHz PLL Src: /2])
#pragma config USBDIV = 1       // USB Clock Selection bit (used in Full-Speed USB mode only; UCFG:FSEN = 1) (USB clock source comes directly from the primary oscillator block with no postscale)

// CONFIG1H
#pragma config FOSC = HSPLL_HS  // Oscillator Selection bits (HS oscillator, PLL enabled (HSPLL))
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enable bit (Fail-Safe Clock Monitor disabled)
#pragma config IESO = OFF       // Internal/External Oscillator Switchover bit (Oscillator Switchover mode disabled)

// CONFIG2L
#pragma config PWRT = ON        // Power-up Timer Enable bit (PWRT enabled)
#pragma config BOR = ON         // Brown-out Reset Enable bits (Brown-out Reset enabled in hardware only (SBOREN is disabled))
#pragma config BORV = 0         // Brown-out Reset Voltage bits (Maximum setting)
#pragma config VREGEN = OFF     // USB Voltage Regulator Enable bit (USB voltage regulator disabled)

// CONFIG2H
#pragma config WDT = ON         // Watchdog Timer Enable bit (WDT enabled)
#pragma config WDTPS = 256      // Watchdog Timer Postscale Select bits (1:256)

// CONFIG3H
#pragma config CCP2MX = ON      // CCP2 MUX bit (CCP2 input/output is multiplexed with RC1)
#pragma config PBADEN = OFF     // PORTB A/D Enable bit (PORTB<4:0> pins are configured as digital I/O on Reset)
#pragma config LPT1OSC = OFF    // Low-Power Timer 1 Oscillator Enable bit (Timer1 configured for higher power operation)
#pragma config MCLRE = ON       // MCLR Pin Enable bit (MCLR pin enabled; RE3 input pin disabled)

// CONFIG4L
#pragma config STVREN = OFF      // Stack Full/Underflow Reset Enable bit (Stack full/underflow will cause Reset)
#pragma config LVP = OFF        // Single-Supply ICSP Enable bit (Single-Supply ICSP disabled)
#pragma config ICPRT = OFF      // Dedicated In-Circuit Debug/Programming Port (ICPORT) Enable bit (ICPORT disabled)
#pragma config XINST = OFF      // Extended Instruction Set Enable bit (Instruction set extension and Indexed Addressing mode disabled (Legacy mode))

// CONFIG5L
#pragma config CP0 = OFF        // Code Protection bit (Block 0 (000800-001FFFh) is not code-protected)
#pragma config CP1 = OFF        // Code Protection bit (Block 1 (002000-003FFFh) is not code-protected)
#pragma config CP2 = OFF        // Code Protection bit (Block 2 (004000-005FFFh) is not code-protected)

// CONFIG5H
#pragma config CPB = OFF        // Boot Block Code Protection bit (Boot block (000000-0007FFh) is not code-protected)
#pragma config CPD = OFF        // Data EEPROM Code Protection bit (Data EEPROM is not code-protected)

// CONFIG6L
#pragma config WRT0 = OFF       // Write Protection bit (Block 0 (000800-001FFFh) is not write-protected)
#pragma config WRT1 = OFF       // Write Protection bit (Block 1 (002000-003FFFh) is not write-protected)
#pragma config WRT2 = OFF       // Write Protection bit (Block 2 (004000-005FFFh) is not write-protected)

// CONFIG6H
#pragma config WRTC = OFF       // Configuration Register Write Protection bit (Configuration registers (300000-3000FFh) are not write-protected)
#pragma config WRTB = OFF       // Boot Block Write Protection bit (Boot block (000000-0007FFh) is not write-protected)
#pragma config WRTD = OFF       // Data EEPROM Write Protection bit (Data EEPROM is not write-protected)

// CONFIG7L
#pragma config EBTR0 = OFF      // Table Read Protection bit (Block 0 (000800-001FFFh) is not protected from table reads executed in other blocks)
#pragma config EBTR1 = OFF      // Table Read Protection bit (Block 1 (002000-003FFFh) is not protected from table reads executed in other blocks)
#pragma config EBTR2 = OFF      // Table Read Protection bit (Block 2 (004000-005FFFh) is not protected from table reads executed in other blocks)

// CONFIG7H
#pragma config EBTRB = OFF      // Boot Block Table Read Protection bit (Boot block (000000-0007FFh) is not protected from table reads executed in other blocks)


#include "main.h"
#include "executer.h"
#include "design.h"


/******************************************************************************/
/*          DEFINES                                                           */
/******************************************************************************/

#define TIMER0_VAL 0x7E                                                         // A0 = 81.3Hz // 90 = 69.69Hz // 80 = 60.99Hz // 7E = 60.05Hz -> 16.7% time on of 1 second
#define TIMER1_VAL 0xFE00                                                       // 0xFE00 for 8 updates per 1/60 refresh rate
#define COUNT 50


/******************************************************************************/
/*          GLOBAL VARIABLES                                                  */
/******************************************************************************/

unsigned char Led[6] = {0,0,0,0,0,0};                                           // Row of 8 leds variable
unsigned char Row_Updater = 0;                                                  // Update the row information multipl times while the selected Kolum is enabled
unsigned char Kolum_Selector = 0;                                               // Select which Kolum should be lid
unsigned char Program_Selector = 0;                                             // Rotary knob determines program to be executed

/******************************************************************************/
/*          LOCAL VARIABLES                                                   */
/******************************************************************************/

static void Init_IO(void);                                                      // Initialize required IO
static void Init_Osc(void);             					// Initialize and setup Oscillators
static void Init_Timers(void);							// Initialize Timers (0)

static unsigned char Update_Star = 0;                                           // In 1 periode off enabled Kolum, the rows are updated 16 times to get PWM
//static unsigned char x = 0;                                                   // used for the FOR-Loop delay before selecting a new kolum

/******************************************************************************/
/*          MAIN ROUTINE INIT                                                 */
/******************************************************************************/

void main (void)
{
    Init_IO();                                          			// Initialize all IO and onstraints
    Init_Osc();                                         			// Initialize Oscillator sub routine
    Init_Timers();                                      			// Initialize seconds timer

    Row = 0x00;                                                                 // All Rows off(8)
    Kol1 = 0xFF & 0xFC;                                                         // Kolums off(4)
    Kol2 = 0xFF & 0x03;                                                         // Kolums off(2)

/******************************************************************************/
/*          MAIN ROUTINE INFINITE LOOP                                        */
/******************************************************************************/

    while(1)                                                                    // Infinite loop
    {
//        Ledw = !Ledw;                                                           // Toggle to measure cpu load

        if (ON == Update_Star)                                                  // When timer1 has updated the active row, the next values must be calculated
        {
            Ledz = ON;            
            if (EXECUTExEFFECT(Kolum_Selector) == Finished )                    // When all switch cases are stable in the underlying routines, finished is pushed back
            {
                UPDATExLEDSTAT(Kolum_Selector);                                 // Write the contents of Led_Bit[x].Led to the active kolum Led[x]
                RUNxDISPLAY();                                                  // Update the design program
                Update_Star = OFF;                                              // Set to OFF for next update of timer1
            }            
        
            switch (PORTA & 0x0F)
            {
                case 14 : Program_Selector = 0; break;
                case 13 : Program_Selector = 1; break;
                case 11 : Program_Selector = 2; break;
                case 7  : Program_Selector = 3; break;
            }

            Ledz = OFF;
            ClrWdt();                                                           // Reset Watchdog, timer1 update = 350us, timer0 update rate is 2.75ms, watchdog timeout value is 4ms

        }        
    }
}

/******************************************************************************/
/*          INTERRUPT ROUTINE HIGH                                            */
/*****************************************************************************/

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
    unsigned int x=0;

    if (INTCONbits.TMR0IF)							// If Timer 0 interrupt (2.66us duration of interrupt)
    {
	Ledx = 1;
        T1CONbits.TMR1ON = OFF;                                                 // Disable Timer1

//        Kolum = 0xFF;                                                           // First disable to prevent ghosting
//        Row = 0x00;                                                             // First disable to prevent ghosting
//        for(x=0;x<5;x++);                                                       // Extra wait time to disable leds before new value is applied

	switch (Kolum_Selector)
	{
            case    0   :   Kol1 = 0xFD & 0xFC;
                            Kol2 = 0xFD & 0x03;
                            Kolum_Selector = 1;
                            break;
            case    1   :   Kol1 = 0xFB & 0xFC;
                            Kol2 = 0xFB & 0x03;
                            Kolum_Selector = 2;
                            break;
            case    2   :   Kol1 = 0xF7 & 0xFC;
                            Kol2 = 0xF7 & 0x03;
                            Kolum_Selector = 3;
                            break;
            case    3   :   Kol1 = 0xEF & 0xFC;
                            Kol2 = 0xEF & 0x03;
                            Kolum_Selector = 4;
                            break;
            case    4   :   Kol1 = 0xDF & 0xFC;
                            Kol2 = 0xDF & 0x03;
                            Kolum_Selector = 5;
                            break;
            case    5   :   Kol1 = 0xFE & 0xFC;
                            Kol2 = 0xFE & 0x03;
                            Kolum_Selector = 0;
                            break;

            default     :   Kol1 = 0xFF & 0xFC;
                            Kol2 = 0xFF & 0x03;
                            Row = 0x00;
                            Kolum_Selector = 0;
                            break;
	}
	
	TMR0L = TIMER0_VAL;                                                     // A0 = 81.3Hz // 90 = 69.69Hz // 80 = 60.99Hz // 7E = 60.05Hz -> 16.7% time on of 1 second
	INTCONbits.TMR0IF = OFF;                                                // Clear Timer 0 interrupt flag

        Row_Updater = 0;                                                        // Clear for next illum
        TMR1H = 0xFF;                                                           // Force direct activation of timer1 (takes min 4us measured)
        TMR1L = 0xFF;                                                           // Force direct activation of timer1 (takes min 4us measured)        
        T1CONbits.TMR1ON = ON;                                                  // Enable Timer1        
        Ledx = 0;
    }

    if (PIR1bits.TMR1IF)                                                        // If Timer 1 interrupt
    {

        Ledy = 0;
        
        if (Row_Updater > ROW_UPDATE_VAL)                                       // If updates are done within time of timer0
        {
            Row_Updater = 0;
            T1CONbits.TMR1ON = OFF;
            Ledy = 0;
            Row = OFF;                                                          // All leds off

        }
        else
        {
            Row = Led[Kolum_Selector];
            Row_Updater++;                                                      // Update start again
            Ledy = 1;                                                           // Status led
            Update_Star = ON;                                                   // Set enable for calculation of next row led value
            T1CONbits.TMR1ON = ON;
            TMR1H = TIMER1_VAL >> 8;                                            // Pre-set timer1 register
            TMR1L = TIMER1_VAL;                                                 // Pre-set timer1 register
        }

        PIR1bits.TMR1IF = OFF;                                                  // Clear timer 1 interrupt flag
    }
}

/******************************************************************************/
/*          INTERRUPT ROUTINE LOW                                             */
/******************************************************************************/

void low_isr(void);                                                             // Set low interrupt routine and map vector
#pragma code low_vector=0x18
void interrupt_at_low_vector (void)
{
	_asm goto low_isr _endasm
}
#pragma code
#pragma interrupt low_isr
void low_isr()
{
    
}

/******************************************************************************/
/*          MAIN ROUTINES                                                     */
/******************************************************************************/

static void Init_IO(void)
{
    TRISA = 0xFF; TRISB = 0xFF; TRISC = 0xFF; TRISD = 0xFF; TRISE = 0xFF;	// Set all ports to inputs
    ADCON0 = 0x00;
    ADCON1 = 0x0F;
    ADCON2 = 0x00;
    UCFGbits.UTRDIS = 1;							// Disable internall USB transceiver
    INTCON2bits.RBPU = 0;							// Disable internall pullup resistors
    TRISA = 0xDF;TRISB = 0x00;TRISC = 0xFC;TRISD = 0x00;TRISE = 0x00;           // Configure IO
    PORTA = 0; PORTB = 0; PORTC = 0; PORTD = 0; PORTE = 0;			// Set all ports OFF to be sure
}

static void Init_Osc(void)
{
    OSCCON = 0x0;
}

static void Init_Timers(void)
{
	RCONbits.IPEN 		= 1;        					// dis/(en)able priority levels
	INTCONbits.GIEH		= 1;						// When IPEN = 1: 1 = Enables all high priority interrupts
	INTCONbits.GIEL		= 0;						// Enable low interrupts
	INTCONbits.TMR0IE 	= 1;						// TMR0 Interrupt enable
	INTCON2bits.TMR0IP	= 1;						// TMR0 High Interrupt
	TMR0H = 0x0;                    					// clear timer0
	TMR0L = 0x0;                    					// clear timer0
	T0CONbits.TMR0ON 	= 1;						// Timer0 On/Off Control bit 1 is On
	T0CONbits.T08BIT	= 1;						// Timer0 8-Bit/16-Bit Control bit, 8Bit is 1
	T0CONbits.T0CS 		= 0;						// Timer0 Clock Source Select bit, 0 is internall instruction cycle
	T0CONbits.T0SE 		= 0;						// Timer0 Source Edge Select bit, 0 is low to high
	T0CONbits.PSA 		= 0;						// Timer0 Prescaler Assignment bit, 0 is On
	T0CONbits.T0PS2		= 1;						// Timer0 Prescaler Select bits, 111 -> 1:256
	T0CONbits.T0PS1		= 1;						// Timer0 Prescaler Select bits, 011 -> 1:16
	T0CONbits.T0PS0		= 1;						// Timer0 Prescaler Select bits, 000 -> 1:2

        PIE1bits.TMR1IE         = 1;                                            // Timer1 Interrupt enable
        IPR1bits.TMR1IP         = 1;                                            // Timer1 Low Interrupt=0, High Interrupt=1
        TMR1H = 0x0;                                                            // clear timer1
        TMR1L = 0x0;                                                            // clear timer1
        T1CONbits.NOT_T1SYNC    = 0;                                            // Timer1 External Clock Input Synchronization Select bit
        T1CONbits.RD16          = 0;                                            // 16-Bit Read/Write Mode Enable bit
        T1CONbits.T1CKPS0       = 1;                                            // Timer1 Input Clock Prescale Select bit0
        T1CONbits.T1CKPS1       = 1;                                            // Timer1 Input Clock Prescale Select bit1
        T1CONbits.T1OSCEN       = 0;                                            // Timer1 Oscillator Enable bit
        T1CONbits.T1RUN         = 0;                                            // Timer1 System Clock Status bit
        T1CONbits.T1SYNC        = 0;                                            // Timer1 External Clock Input Synchronization Select bit
        T1CONbits.TMR1CS        = 0;                                            // Timer1 Clock Source Select bit
        T1CONbits.TMR1ON        = 0;                                            // Timer1 On bit
}