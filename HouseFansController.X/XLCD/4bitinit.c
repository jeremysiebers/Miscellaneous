#include <xc.h>
#include "xlcd.h"
#define cmd1 3
#define cmd2 2
/********************************************************************
*       Function Name:  WriteCmdXLCD                                *
*       Return Value:   void                                        *
*       Parameters:     none						                *
*       Description:    This routine initializes the Hitachi		*
*                       HD44780 LCD controller in 4BIT interface    *
*						mode!!!										*
********************************************************************/
void LCD4BitInit()
{
#ifdef UPPER                            // Upper nibble interface
    TRIS_DATA_PORT &= 0x0f;
    DATA_PORT &= 0x0f;
    DATA_PORT |= (cmd1<<4)&0xf0;    	// Reset LCD 
#else                                   // Lower nibble interface
    TRIS_DATA_PORT &= 0xf0;
    DATA_PORT &= 0xf0;
    DATA_PORT |= cmd1&0x0f;             // Reset LCD    
#endif
    RW_PIN = 0;                     	// Set control signals for command
    RS_PIN = 0;
    DelayFor18TCY();
    E_PIN = 1;                      	// Clock command in
    DelayFor18TCY();
    E_PIN = 0;
    DelayPORXLCD();    
    
    DelayFor18TCY();
    E_PIN = 1;                      	// Clock command in
    DelayFor18TCY();
    E_PIN = 0;
    DelayPORXLCD();    
    
    DelayFor18TCY();
    E_PIN = 1;                      	// Clock command in
    DelayFor18TCY();
    E_PIN = 0;
    DelayPORXLCD();

#ifdef UPPER                            // Upper nibble interface    
    DATA_PORT &= 0x0f;
    DATA_PORT |= (cmd2<<4)&0xf0;    	// Set LCD to 4BIT mode!
#else                                   // Lower nibble interface  
    DATA_PORT &= 0xf0;
    DATA_PORT |= cmd2&0x0f;             // Set LCD to 4BIT mode!
#endif
        
    DelayFor18TCY();
    E_PIN = 1;                      	// Clock command in
    DelayFor18TCY();
    E_PIN = 0;
    DelayPORXLCD(); 
	
#ifdef UPPER                            // Make data nibble input
        TRIS_DATA_PORT |= 0xf0;
#else
        TRIS_DATA_PORT |= 0x0f;
#endif
}

