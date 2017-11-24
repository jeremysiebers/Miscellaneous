#include "Main.h"
#include "io.h"
#include <xc.h>
#include "api.h"

#define LIST_SIZE = 28;						// Amount of variables specified in ApiList[], must be kept < 128 EEPROM == 256 bytes (integer = 2 bytes 0xFFFF)

unsigned int ApiList[LIST_SIZE] = {			// List containing the writable variables that require storage in EEPROM
	TRAIN_WAIT_TIME,       
	JUNCTION_WAIT_TIME,    
	LIGHTS_ON_WAIT_TIME,   
	STATIONARY_LEFT,       
	STATIONARY_RIGHT,      
	MAX_PWM_RIGHT,         
	MAX_PWM_LEFT,          
	MAX_JERK_PWM_BRAKE,    
	MAX_JERK_PWM,          
	INPUT_DEBOUNCE,      
	TRAIN1_POS,         
	TRAIN2_POS,         	
	MAX_PWM_RMU_RIGHT,	
	MAX_PWM_RMU_LEFT,	
	MAX_PWM_RMD_RIGHT,	
	MAX_PWM_RMD_LEFT,	
	MAX_PWM_LMU_RIGHT,	
	MAX_PWM_LMU_LEFT,	
	MAX_PWM_LMD_RIGHT,	
	MAX_PWM_LMD_LEFT,	
	DELAY_RMU_DOWN,		
	DELAY_RMU_UP,		
	DELAY_RMD_DOWN,		
	DELAY_RMD_UP,		
	DELAY_LMD_DOWN,		
	DELAY_LMD_UP,		
	DELAY_LMU_DOWN,		
	DELAY_LMU_UP		
};

/******************************************************************************
 * Function:        EEPROMxREAD(void)
 *                  Read program values in EEPROM at startup
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    Initialize program variables from EEPROM
 *
 * Overview:        None
 *****************************************************************************/
void EEPROMxREAD(void)
{
	unsigned int i;
	unsigned int Data;
	
	for(i = 0; i < (LIST_SIZE); i++ )
    {
		Data = Eeprom_Read(i);							// read the data on the location according to the variables numbered in the ApiList		
		//API[ApiList[i]] = Data;							// Store the data in API to be used by the program	
		//API_EEPROM[ApiList[i]] = Data;					// Store the data in API_EEPROM to be used for determining update of EEPROM val in EEPROMxSTORE()
		// temporary rule as long as EEPROM is not configured yet --> to be deleted and above 2 lines uncommented
    }
}

/******************************************************************************
 * Function:        unsigned int Eeprom_Read(unsigned int Location)
 *                  Read program values in EEPROM
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    Reads vital program variables from EEPROM
 *
 * Overview:        None
 *****************************************************************************/
unsigned int Eeprom_Read(unsigned int Location)
{
	unsigned int Location_High_Byte = Location * 2;
	unsigned int Location_Low_Byte  = Location_High_Byte + 1;
	unsigned int Return_Data = 0;
	
	EECON1bits.EEPGD = 0; 
	EEADR = char(Location_High_Byte);           
	EECON1bits.RD = 1;    
	Return_Data = EEDATA;  
	Return_Data = Return_Data << 8;
	
	EECON1bits.EEPGD = 0; 
	EEADR = char(Location_Low_Byte);           
	EECON1bits.RD = 1;   
	Return_Data = Return_Data | EEDATA;
	
	return (Return_Data);
}

/******************************************************************************
 * Function:        EEPROMxSTORE(void)
 *                  Store program values in EEPROM if a value is changed
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
void EEPROMxSTORE(void)
{
	unsinged int i;
	
	for(i = 0; i < (LIST_SIZE); i++ )
    {
		if (API[ApiList[i]] != API_EEPROM[ApiList[i]])	// compare the data on the location according to the variables numbered in the ApiList
		{
			Eeprom_Store(i, API[ApiList[i]]); 			// Send list index number as Location and the API[address].value to be stored.
			API_EEPROM[ApiList[i]] = API[ApiList[i]]    // Store the new value also in te API_EEPROM for next comparisson
		}
    }
}

/******************************************************************************
 * Function:        Eeprom_Store(unsigned int Location, unsigned int Value)
 *                  Store program values in EEPROM if a value is changed
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
void Eeprom_Store(unsigned int Location, unsigned int Value)
{	
	unsigned int Location_High_Byte = Location * 2;
	unsigned int Location_Low_Byte  = Location_High_Byte + 1;
	
	INTCON = 0x00;
	
	EECON1bits.EEPGD = 0;
	EECON1bits.WREN = 1; 
	EEADR = char(Location_Low_Byte);
	EEDATA = Value;
	EECON2 = 0x55;
	EECON2 = 0xaa;
	EECON1bits.WR = 1;
	while (!PIR2bits.EEIF);
	PIR2bits.EEIF = 0;
															
	EECON1bits.EEPGD = 0;
	EECON1bits.WREN = 1; 
	EEADR = char(Location_High_Byte);
	EEDATA = Value >> 8;
	EECON2 = 0x55;
	EECON2 = 0xaa;
	EECON1bits.WR = 1;
	while (!PIR2bits.EEIF);
	PIR2bits.EEIF = 0;

	INTCON = 0xA0;
}
/*	Location	Location_High_Byte				Location_Low_Byte
	0 > 		0 					and 		1
										
	1 > 		2 					and 		3
										
	2 > 		4 					and 		5
										
	3 > 		6 					and 		7
										
	4 > 		8 					and 		9
										
	5 > 		10					and			11
*/