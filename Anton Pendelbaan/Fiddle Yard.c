/** I N C L U D E S **********************************************************/
#include <p18f4550.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <delays.h>
#include <pwm.h>
#include <usart.h>
#include <Fiddle_Yard.h>
#include <Shift_Register.h>
#include <Command_Machine.h>	// serial commands
#include <State_Machine.h>	//all movements and fidle yard program
#include <Diagnostic_ret.h>
#include <Var_Out.h>

//CONFIGURATION BITS//

#pragma config PLLDIV = 5
#pragma config CPUDIV = OSC1_PLL2	// 4 and 6 or 1 and 2
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

#define Init_Shift()				TRISDbits.TRISD0=1;TRISDbits.TRISD1=0;TRISDbits.TRISD2=0;TRISDbits.TRISD3=0;TRISDbits.TRISD4=0;
#define Init_RS232_Pins()			TRISCbits.TRISC6=0;TRISCbits.TRISC7=1;
#define InitPwm()					TRISCbits.TRISC2=0;TRISCbits.TRISC0=0;TRISCbits.TRISC1=0;TRISEbits.TRISE2=0;
#define Init_TestOutputs()			TRISBbits.TRISB5=0,TRISBbits.TRISB4=0,TRISBbits.TRISB3=0,TRISBbits.TRISB2=0,TRISBbits.TRISB1=0;
#define Output_Enable				PORTBbits.RB1

static void Init_Timers(void);
static void Init_Pwm(void);
static void Init_RS232(void);

static unsigned char Enable_State_Machine_Update =1;

//MAIN ROUTINE/////////////////////////////////////////////////////////////////////////////////////////
void main()
{	
	TRISA = 0xFF;TRISB = 0xFF;TRISC = 0xFF;TRISD = 0xFF;TRISE = 0xFF;	//	All IO are inputs
	ADCON1=0x0F;						//AD OFF
	CMCON=0x07;							//COMP OFF
	
	Led1=0,Led2=0,Led3=0,Led4=0;	
	Init_Timers();
	Init_Shift();
	Init_Pwm();	
	Init_TestOutputs();
	Init_RS232();
	Shift_Serial_In();
	Shift_Serial_Out();
	Output_Enable = 1; Led1=1;
	
					
	while(1)
    {
	    if (PIR1bits.TXIF)
		{
			Diagnostic();
		} 
				
		if (Enable_State_Machine_Update == 1)
		{
			Led3=1;
			State_Machine_Update(TOP);
			State_Machine_Update(BOTTOM);
			Enable_State_Machine_Update = 0;
			Led3=0;			
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
	if (PIR1bits.RCIF)
	{
		Command(RCREG);
	}
			
	if (INTCONbits.TMR0IF)						//PIR1bits.TMR1IF == 1)
	{
		Led2=1;
		Shift_Serial_In();
		Shift_Serial_Out();
		Enable_State_Machine_Update = 1;
		INTCONbits.TMR0IF = 0; 					//PIR1bits.TMR1IF=0;
		TMR0L = 0x00;
		TMR0H = 0x00;//0xF3
		Led2=0;
	}
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//MAIN SUBROUTINES//

void Init_Timers()
{
	
	IPR1 = 0x01;					//Timer 1 high priority
	IPR2 = 0x00;					//others low priority
	RCONbits.IPEN = 1;            	//dis/(en)able priority levels
	INTCON = 0xA0;/*0x80;*/       	//When IPEN = 1: 1 = Enables all high priority interrupts and enable TMR0 overflow interrupt 0xA0 									is timer0 On 0x80 is timer0 Off
	INTCON2 = 0x84;               	//TMR0 high priority
	PIE1 = 0x00;					//TMR1 overflow interrupt enable on=0x1 off=0x00
	TMR0H = 0x0;                    //clear timer0
	TMR0L = 0x0;                    //clear timer0
	TMR1H = 0x0;
	TMR1L = 0x0;
	T0CON = 0xC3;/*0xC4; 0x84;  */       //set up timer0	0xC stands for tmr ON, 8bit timer, CLKO, low to high
	T1CON = 0x81;					// 0xB1 = 1:8(40mS), 0xA1 = 1:4(22.5mS), 0x91 = 1:2(11mS), 0x81 = 1:1(5.5mS)

}

void Init_Pwm()
{
	// PWM setup
	Pwm_Brake_TOP = 1;
	PR2=0xff;				//PWM Period TMR2 zelfde voor PWM1 en PWM2
	CCPR1L = 0x7F;			//PWM Duty cycle PWM1
	CCP1CON = 0x0F;			//PWM Mode
	T2CON = 0x04;			//TMR2 Pre-scale
	Pwm_Brake_BOTTOM = 1;
	CCPR2L = 0x7F;			//PWM Duty cycle PWM2
	CCP2CON = 0x0F;			//PWM Mode
	InitPwm();
//
}

void Init_RS232()
{
	Init_RS232_Pins();
	OpenUSART	(USART_TX_INT_OFF & USART_RX_INT_ON & USART_ASYNCH_MODE & USART_EIGHT_BIT & 
				USART_CONT_RX & USART_BRGH_LOW, 12); //77=9600 12=57600 5(6)=115200
	//baudUSART (BAUD_IDLE_CLK_HIGH & BAUD_16_BIT_RATE & BAUD_WAKEUP_ON & BAUD_AUTO_ON);
	IPR1bits.RCIP = 1; //Receive interrupt high
	IPR1bits.TXIP = 1; //Transmit interrupt high
}


////////////////////////////////////////////////////////////////////////////////////////////////////