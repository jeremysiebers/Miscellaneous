#include "Main.h"
#include "io.h"
#include <xc.h>
#include "api.h"


/******************************************************************************
 * Function:        static void Eeprom_Store(void)
 *                  Store program values in EEPROM
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    Stores vital program variables in EEPROM
 *
 * Overview:        None
 *****************************************************************************/
void Eeprom_Store(void)
{
	INTCON = 0x00;
	
		EECON1bits.EEPGD = 0;
		EECON1bits.WREN = 1; 
		EEADR = 0x01;
		EEDATA = GETxAPIxVAL(MAX_PWM_RIGHT);
		EECON2 = 0x55;
		EECON2 = 0xaa;
		EECON1bits.WR = 1;
		while (!PIR2bits.EEIF);
		PIR2bits.EEIF = 0;
																
		EECON1bits.EEPGD = 0;
		EECON1bits.WREN = 1; 
		EEADR = 0x00;
		EEDATA = GETxAPIxVAL(MAX_PWM_RIGHT)>>8;
		EECON2 = 0x55;
		EECON2 = 0xaa;
		EECON1bits.WR = 1;
		while (!PIR2bits.EEIF);
		PIR2bits.EEIF = 0;

		EECON1bits.EEPGD = 0;
		EECON1bits.WREN = 1; 
		EEADR = 0x03;
		EEDATA = GETxAPIxVAL(MAX_PWM_LEFT);
		EECON2 = 0x55;
		EECON2 = 0xaa;
		EECON1bits.WR = 1;
		while (!PIR2bits.EEIF);
		PIR2bits.EEIF = 0;
																
		EECON1bits.EEPGD = 0;
		EECON1bits.WREN = 1; 
		EEADR = 0x02;
		EEDATA = GETxAPIxVAL(MAX_PWM_LEFT)>>8;
		EECON2 = 0x55;
		EECON2 = 0xaa;
		EECON1bits.WR = 1;
		while (!PIR2bits.EEIF);
		PIR2bits.EEIF = 0;

		EECON1bits.EEPGD = 0;
		EECON1bits.WREN = 1; 
		EEADR = 0x04;
		EEDATA = GETxAPIxVAL(MAX_JERK_PWM_BRAKE);
		EECON2 = 0x55;
		EECON2 = 0xaa;
		EECON1bits.WR = 1;
		while (!PIR2bits.EEIF);
		PIR2bits.EEIF = 0;
			
															
	INTCON = 0xA0;
}