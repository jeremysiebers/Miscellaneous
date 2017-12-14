/* 
 * File:   main.c
 * Author: Jeremy
 *
 * Created on December 10, 2012, 9:36 PM
 */

#include <stdio.h>
#include <stdlib.h>



// PIC18F4455 Configuration Bit Settings

#include <p18F4455.h>

// CONFIG1L
#pragma config PLLDIV = 5       // PLL Prescaler Selection bits (Divide by 5 (20 MHz oscillator input))
#pragma config CPUDIV = OSC1_PLL2// System Clock Postscaler Selection bits ([Primary Oscillator Src: /1][96 MHz PLL Src: /2])
#pragma config USBDIV = 1       // USB Clock Selection bit (used in Full-Speed USB mode only; UCFG:FSEN = 1) (USB clock source comes directly from the primary oscillator block with no postscale)

// CONFIG1H
#pragma config FOSC = HSPLL_HS  // Oscillator Selection bits (HS oscillator, PLL enabled (HSPLL))
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enable bit (Fail-Safe Clock Monitor disabled)
#pragma config IESO = OFF       // Internal/External Oscillator Switchover bit (Oscillator Switchover mode disabled)

// CONFIG2L
#pragma config PWRT = OFF       // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOR = OFF        // Brown-out Reset Enable bits (Brown-out Reset disabled in hardware and software)
#pragma config BORV = 3         // Brown-out Reset Voltage bits (Minimum setting)
#pragma config VREGEN = OFF     // USB Voltage Regulator Enable bit (USB voltage regulator disabled)

// CONFIG2H
#pragma config WDT = OFF        // Watchdog Timer Enable bit (WDT disabled (control is placed on the SWDTEN bit))
#pragma config WDTPS = 32768    // Watchdog Timer Postscale Select bits (1:32768)

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



#include <main.h>

static void Init_IO(void);
static void Init_Osc(void);             					// Initialize and setup Oscillators
static void Init_Timers(void);							// Initialize Timers (0)

static unsigned char Kolum_Selector = 0;
int x=0;

void main (void)
{
    Init_IO();                                          			// Initialize all IO and onstraints
    Init_Osc();                                         			// Initialize Oscillator sub routine
    Init_Timers();                                      			// Initialize seconds timer

    Led = 0x00;

	while(1)								// Infinite loop
	{
            switch (Kolum_Selector)
            {
                    case    0   :   Led = 0x10;
                                    
                    break;
                    case    1   :   Led = 0x00;
                                    
                    break;
                    case    2   :   Led = 0x00;
                                    
                    break;
                    case    3   :   Led = 0x00;
                                    
                    break;
                    case    4   :   Led = 0x00;
                                    
                    break;
                    case    5   :   Led = 0x00;
                                    
                    break;
                    default     :  
                    break;
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
            Ledx = !Ledx;

            switch (Kolum_Selector)
            {
                    case    0   :   Kolum = 0xFF;
                                    Kolum = 0xFD;
                                    Kolum_Selector = 1;
                                    break;
                    case    1   :   Kolum = 0xFF;
                                    Kolum = 0xFB;
                                    Kolum_Selector = 2;
                                    break;
                    case    2   :   Kolum = 0xFF;
                                    Kolum = 0xF7;
                                    Kolum_Selector = 3;
                                    break;
                    case    3   :   Kolum = 0xFF;
                                    Kolum = 0xEF;
                                    Kolum_Selector = 4;
                                    break;
                    case    4   :   Kolum = 0xFF;
                                    Kolum = 0xDF;
                                    Kolum_Selector = 5;
                                    break;
                    case    5   :   Kolum = 0xFF;
                                    Kolum = 0xFE;
                                    Kolum_Selector = 0;
                                    break;
                    default     :   Kolum = 0xFF;
                                    Kolum_Selector = 0;
                                    break;
            }

            
            TMR0L = 0x7E;                                               // A0 = 81.3Hz // 90 = 69.69Hz // 80 = 60.99Hz // 7E = 60.05Hz -> 16.7% time on of 1 second

            INTCONbits.TMR0IF = OFF;					// Clear Timer 0 interrupt flag
	}
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


//MAIN SUBROUTINES//

static void Init_IO(void)
{
    TRISA = 0xFF; TRISB = 0xFF; TRISC = 0xFF; TRISD = 0xFF; TRISE = 0xFF;	// Set all ports to inputs
    ADCON0 = 0x00;
    ADCON1 = 0x0F;
    ADCON2 = 0x00;
    UCFGbits.UTRDIS = 1;							// Disable internall USB transceiver
    INTCON2bits.RBPU = 0;							// Disable internall pullup resistors
    TRISA = 0xFF;TRISB = 0x00;TRISC = 0xFF;TRISD = 0x00;TRISE = 0x00;           // Configure IO
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
	INTCONbits.GIEL		= 0;						// Disable low interrupts
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
}