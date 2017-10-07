#ifndef __State_Mchn_H
#define __State_Mchn_H

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
#define Reed_Contact_LF				PORTDbits.RD2
#define Reed_Contact_LB				PORTDbits.RD3
#define Reed_Contact_RF				PORTDbits.RD0
#define Reed_Contact_RB				PORTDbits.RD1
#define Reed_Contact_LMU     		PORTCbits.RC1
#define Reed_Contact_LMD     		PORTDbits.RD4
#define Reed_Contact_RMU     		PORTCbits.RC4
#define Reed_Contact_RMD     		PORTCbits.RC5
#define Red							PORTDbits.RD5
#define Green						PORTDbits.RD6

extern void Update_StateMchn(void);

#endif