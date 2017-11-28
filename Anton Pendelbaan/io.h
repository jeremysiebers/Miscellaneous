#ifndef __io_H
#define __io_H

//#define DEBUG

#define Brake						PORTCbits.RC0
#define Wl_Left_Str					PORTAbits.RA3
#define Wl_Left_Bnd					PORTAbits.RA2
#define Wl_Right_Str				PORTAbits.RA1
#define Wl_Right_Bnd				PORTAbits.RA0
#define	But_Start					!PORTBbits.RB0
#define	But_Stop					!PORTDbits.RD7
#define	But_Middle					!PORTBbits.RB1
#define	But_LB						!PORTBbits.RB5
#define	But_LF						!PORTBbits.RB4
#define	But_RB						!PORTBbits.RB3
#define	But_RF						!PORTBbits.RB2
#define Reed_Contact_RB				PORTDbits.RD2
#define Reed_Contact_RF				PORTDbits.RD3
#define Reed_Contact_LB				PORTDbits.RD0
#define Reed_Contact_LF				PORTDbits.RD1
#define Reed_Contact_LMU     		PORTCbits.RC1
#define Reed_Contact_LMD     		PORTDbits.RD4
#define Reed_Contact_RMU     		PORTEbits.RE1
#define Reed_Contact_RMD     		PORTEbits.RE0
#define Red							PORTDbits.RD5
#define Green						PORTDbits.RD6

#define Blink 2
#define BlinkHz 3000
#define Blink1 3
#define BlinkHz1 1000

#define LMU 1
#define LMD 2
#define RMD 3
#define RMU 4

#define ERROR    2	// general switch case when error
#define Busy     1
#define Finished 0

#define Straight	0
#define Bend		1
#define Left		0
#define Right		1

#define AdjustSpeed 20  
#define Init 1
#define Run2 2
#define Run1 3

#define RB_LB 0	//drive path presets
#define RB_LF 1
#define RF_LB 2
#define RF_LF 3
#define LB_RB 4
#define LB_RF 5
#define LF_RB 6
#define LF_RF 7

#define LB 1	//to create drive path
#define LF 2
#define RB 3
#define RF 4
#define Middle 5
#define OneTrain 9

#define ActivateControlsTime 10000

unsigned int	Train_Move_Pwm_Count;

extern void Debounce_Inputs(void);
extern void Green_Led(unsigned char Operation);
extern void Red_Led(unsigned char Operation);

#endif