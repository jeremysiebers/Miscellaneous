// PIC18F4550 Configuration Bit Settings

// 'C' source line config statements

#include <xc.h>

// CONFIG1L
#pragma config PLLDIV = 5       // PLL Prescaler Selection bits (Divide by 5 (20 MHz oscillator input))
#pragma config CPUDIV = OSC2_PLL3// System Clock Postscaler Selection bits ([Primary Oscillator Src: /2][96 MHz PLL Src: /3])
#pragma config USBDIV = 2       // USB Clock Selection bit (used in Full-Speed USB mode only; UCFG:FSEN = 1) (USB clock source comes from the 96 MHz PLL divided by 2)

// CONFIG1H
#pragma config FOSC = HSPLL_HS  // Oscillator Selection bits (HS oscillator, PLL enabled (HSPLL))
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enable bit (Fail-Safe Clock Monitor disabled)
#pragma config IESO = OFF       // Internal/External Oscillator Switchover bit (Oscillator Switchover mode disabled)

// CONFIG2L
#pragma config PWRT = ON        // Power-up Timer Enable bit (PWRT enabled)
#pragma config BOR = ON         // Brown-out Reset Enable bits (Brown-out Reset disabled in hardware and software)
#pragma config BORV = 1         // Brown-out Reset Voltage bits (Minimum setting 4.59V)
#pragma config VREGEN = OFF     // USB Voltage Regulator Enable bit (USB voltage regulator disabled)

// CONFIG2H
#pragma config WDT = OFF        // Watchdog Timer Enable bit (WDT disabled (control is placed on the SWDTEN bit))
#pragma config WDTPS = 1        // Watchdog Timer Postscale Select bits (1:1)

// CONFIG3H
#pragma config CCP2MX = ON      // CCP2 MUX bit (CCP2 input/output is multiplexed with RC1)
#pragma config PBADEN = OFF     // PORTB A/D Enable bit (PORTB<4:0> pins are configured as digital I/O on Reset)
#pragma config LPT1OSC = OFF    // Low-Power Timer 1 Oscillator Enable bit (Timer1 configured for higher power operation)
#pragma config MCLRE = ON       // MCLR Pin Enable bit (MCLR pin enabled; RE3 input pin disabled)

// CONFIG4L
#pragma config STVREN = ON      // Stack Full/Underflow Reset Enable bit (Stack full/underflow will cause Reset)
#pragma config LVP = OFF        // Single-Supply ICSP Enable bit (Single-Supply ICSP disabled)
#pragma config ICPRT = OFF      // Dedicated In-Circuit Debug/Programming Port (ICPORT) Enable bit (ICPORT disabled)
#pragma config XINST = OFF      // Extended Instruction Set Enable bit (Instruction set extension and Indexed Addressing mode disabled (Legacy mode))

// CONFIG5L
#pragma config CP0 = OFF        // Code Protection bit (Block 0 (000800-001FFFh) is not code-protected)
#pragma config CP1 = OFF        // Code Protection bit (Block 1 (002000-003FFFh) is not code-protected)
#pragma config CP2 = OFF        // Code Protection bit (Block 2 (004000-005FFFh) is not code-protected)
#pragma config CP3 = OFF        // Code Protection bit (Block 3 (006000-007FFFh) is not code-protected)

// CONFIG5H
#pragma config CPB = OFF        // Boot Block Code Protection bit (Boot block (000000-0007FFh) is not code-protected)
#pragma config CPD = OFF        // Data EEPROM Code Protection bit (Data EEPROM is not code-protected)

// CONFIG6L
#pragma config WRT0 = OFF       // Write Protection bit (Block 0 (000800-001FFFh) is not write-protected)
#pragma config WRT1 = OFF       // Write Protection bit (Block 1 (002000-003FFFh) is not write-protected)
#pragma config WRT2 = OFF       // Write Protection bit (Block 2 (004000-005FFFh) is not write-protected)
#pragma config WRT3 = OFF       // Write Protection bit (Block 3 (006000-007FFFh) is not write-protected)

// CONFIG6H
#pragma config WRTC = OFF       // Configuration Register Write Protection bit (Configuration registers (300000-3000FFh) are not write-protected)
#pragma config WRTB = OFF       // Boot Block Write Protection bit (Boot block (000000-0007FFh) is not write-protected)
#pragma config WRTD = OFF       // Data EEPROM Write Protection bit (Data EEPROM is not write-protected)

// CONFIG7L
#pragma config EBTR0 = OFF      // Table Read Protection bit (Block 0 (000800-001FFFh) is not protected from table reads executed in other blocks)
#pragma config EBTR1 = OFF      // Table Read Protection bit (Block 1 (002000-003FFFh) is not protected from table reads executed in other blocks)
#pragma config EBTR2 = OFF      // Table Read Protection bit (Block 2 (004000-005FFFh) is not protected from table reads executed in other blocks)
#pragma config EBTR3 = OFF      // Table Read Protection bit (Block 3 (006000-007FFFh) is not protected from table reads executed in other blocks)

// CONFIG7H
#pragma config EBTRB = OFF      // Boot Block Table Read Protection bit (Boot block (000000-0007FFh) is not protected from table reads executed in other blocks)

//#include <p18f4550.h>
//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
 
#include "Main.h"
#include "State_Mchn.h"
#include "eusart1.h"
#include "terminal.h"
#include "api.h"
#include "io.h"
#include "eeprom_settings.h"


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//DECLARATIONS//

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//DECLARATIONS//
 #define _XTAL_FREQ 24000000

#define InitPwm()					TRISCbits.TRISC2=0;TRISCbits.TRISC0=0;
#define Init_Led_Outputs()			TRISAbits.TRISA4=0;TRISDbits.TRISD5=0;TRISDbits.TRISD6=0;
#define Init_Wissel_Outputs()		TRISAbits.TRISA0=0;TRISAbits.TRISA1=0;TRISAbits.TRISA2=0;TRISAbits.TRISA3=0;
#define	Init_Switches()				TRISBbits.TRISB0=1;TRISBbits.TRISB1=1;TRISBbits.TRISB2=1;TRISBbits.TRISB3=1;TRISBbits.TRISB4=1;TRISBbits.TRISB5=1;TRISDbits.TRISD7=1;
#define Init_Reed_Contacts()		TRISDbits.TRISD2=1;TRISDbits.TRISD3=1;TRISDbits.TRISD0=1;TRISDbits.TRISD1=1;TRISCbits.TRISC1=1;TRISDbits.TRISD4=1;TRISEbits.TRISE0=1;TRISEbits.TRISE1=1;

#define Led1_Blink 	100
#define Led1_Off	700

void Init_Timers(void);
void Init_Pwm(void);

volatile unsigned char 	Update_State_Machine = False;                           // volatile because it can get set in interrupt
volatile unsigned int	Led1_Counter = 0;                                       // volatile because it can get set in interrupt

//MAIN ROUTINE/////////////////////////////////////////////////////////////////////////////////////////

void main (void)
{
	TRISA = 0xFF;TRISB = 0xFF;TRISC = 0xFF;TRISD = 0xFF;TRISE = 0xFF;	//	All IO are inputs
	ADCON1=0x0F;						//AD OFF
	CMCON=0x07;							//COMP OFF
	Init_Led_Outputs();
	Led1 = 0;
	Green = 0;
	Red = 0;
	
	Init_Wissel_Outputs();
	Wl_Left_Str = 0;
	Wl_Left_Bnd = 0;
	Wl_Right_Str = 0;
	Wl_Right_Bnd = 0;
	
	Init_Reed_Contacts();
	Init_Switches();
    APIxInitialize();
    __delay_ms(1000);
    while(EEPROMxREAD() == Off){
        continue;
    };
	Init_Pwm();
	Init_Timers();
    EUSART1_Initialize();
	
			
	while(1)
	{
		if (True == Update_State_Machine)
		{
			Update_State_Machine = False;
			Update_StateMchn();                       
		}        
        READxRECEIVEDxMESSAGE();
        DIAGNOSTICxTOxPC(); 
	}
}



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Interrupt routines//

void interrupt low_priority tc_low(void) {
// process any other low priority sources here
}

void interrupt high_priority tc_high(void) {
    
	if (INTCONbits.TMR0IF)
	{
		if(Led1_Counter <= Led1_Blink)
		{
			Led1 = 1;            
		}
		else
		{
			Led1 = 0;
		}
		if(Led1_Counter >= Led1_Off)
		{
			Led1_Counter = 0;            
		}
		Led1_Counter++;
		Update_State_Machine = True;
		INTCONbits.TMR0IF = 0;
	}
    
    if (PIE1bits.RC1IE == 1 && PIR1bits.RC1IF == 1) {
        EUSART1_Receive_ISR();
    } 
    if (PIE1bits.TX1IE == 1 && PIR1bits.TX1IF == 1) {
        EUSART1_Transmit_ISR();
    }
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Timer setup//

void Init_Timers(void)
{
	RCONbits.IPEN = 1;            	//dis/(en)able priority levels
	INTCON = 0xA0;/*0x80;*/       	//When IPEN = 1: 1 = Enables all high priority interrupts and enable TMR0 overflow interrupt 0xA0 is timer0 On 0x80 is timer0 Off
	INTCON2 = 0x84;
	TMR0H = 0x0;                    //clear timer0
	TMR0L = 0x0;                    //clear timer0
	T0CON = 0xC3;/*0xC4; 0x84;  */       //set up timer0	0xC stands for tmr ON, 8bit timer, CLKO, low to high
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//MAIN SUBROUTINES//
void Init_Pwm(void)
{
	// PWM setup
    SETxAPIxVAL(PWM_BRAKE, On);
	PR2=0xFF;				//PWM Period TMR2 zelfde voor PWM1 en PWM2
	CCPR1L = 0x7F;			//PWM Duty cycle PWM1
	CCP1CON = 0x0F;			//PWM Mode
	T2CON = 0x04;			//TMR2 Pre-scale	//0x04	//0x05	0x07
	InitPwm();
	
}