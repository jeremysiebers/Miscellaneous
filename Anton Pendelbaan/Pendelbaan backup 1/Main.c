#include <p18f4550.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pwm.h>


#include <Main.h>
#include <State_Mchn.h>	//all movements program

//CONFIGURATION BITS//

#pragma config PLLDIV = 5
#pragma config CPUDIV = OSC2_PLL3	// 4 and 6 or 	1 and 2(48Mhz) 		2 and 3(32Mhz)
#pragma config USBDIV = 2
#pragma config FOSC = HSPLL_HS
#pragma config FCMEM = OFF
#pragma config IESO = OFF
#pragma config PWRT = ON
#pragma config BOR = OFF
#pragma config BORV = 43
#pragma config VREGEN = OFF
#pragma config WDT = OFF
#pragma config WDTPS = 1
#pragma config MCLRE = ON
#pragma config LPT1OSC = OFF
#pragma config PBADEN = OFF
#pragma config CCP2MX = ON
#pragma config STVREN = OFF
#pragma config LVP = OFF
#pragma config ICPRT = OFF
#pragma config XINST = OFF
#pragma config DEBUG = OFF
#pragma config CP0 = OFF
#pragma config CP1 = OFF
#pragma config CP2 = OFF
#pragma config CP3 = OFF
#pragma config CPB = OFF
#pragma config CPD = OFF
#pragma config WRT0 = OFF
#pragma config WRT1 = OFF
#pragma config WRT2 = OFF
#pragma config WRT3 = OFF
#pragma config WRTB = OFF
#pragma config WRTC = OFF
#pragma config WRTD = OFF
#pragma config EBTR0 = OFF
#pragma config EBTR1 = OFF
#pragma config EBTR2 = OFF
#pragma config EBTR3 = OFF
#pragma config EBTRB = OFF

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//DECLARATIONS//

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//DECLARATIONS//

#define InitPwm()					TRISCbits.TRISC2=0;TRISCbits.TRISC0=0;
#define Init_Led_Outputs()			TRISAbits.TRISA4=0;TRISDbits.TRISD5=0;TRISDbits.TRISD6=0;
#define Init_Wissel_Outputs()		TRISAbits.TRISA0=0;TRISAbits.TRISA1=0;TRISAbits.TRISA2=0;TRISAbits.TRISA3=0;
#define	Init_Switches()				TRISBbits.TRISB0=1;TRISBbits.TRISB1=1;TRISBbits.TRISB2=1;TRISBbits.TRISB3=1;TRISBbits.TRISB4=1;TRISBbits.TRISB5=1;TRISDbits.TRISD7=1;
#define Init_Reed_Contacts()		TRISDbits.TRISD2=1;TRISDbits.TRISD3=1;TRISDbits.TRISD0=1;TRISDbits.TRISD1=1;

static void Init_Timers(void);
static void Init_Pwm(void);

unsigned char 	Update_State_Machine = False;

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
	
	Init_Reed_Contacts()
	Init_Switches();
	Init_Pwm();
	Init_Timers();
			
	while(1)
	{
		if (True == Update_State_Machine)
		{
			Update_State_Machine = False;
			Update_StateMchn();
		}
	}
}



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Interrupt routines//

void high_isr(void);
#pragma code high_vector=0x8
void interrupt_at_high_vector (void)
{
	_asm goto high_isr _endasm
}
#pragma code
#pragma interrupt high_isr
void high_isr()
{
	if (INTCONbits.TMR0IF)
	{
		Led1 = !Led1;
		Update_State_Machine = True;
		INTCONbits.TMR0IF = 0;
	}
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Timer setup//

static void Init_Timers(void)
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
static void Init_Pwm(void)
{
	// PWM setup
	Brake = On;
	PR2=0xFF;				//PWM Period TMR2 zelfde voor PWM1 en PWM2
	CCPR1L = 0x7F;			//PWM Duty cycle PWM1
	CCP1CON = 0x0F;			//PWM Mode
	T2CON = 0x04;			//TMR2 Pre-scale	//0x04	//0x05	0x07
	InitPwm();
	
}

