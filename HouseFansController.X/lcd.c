#include "xc.h"
#include "lcd.h"

int OpenLCD_Case=0, OpenLCDReady=0, WriteCmdLCD_Case=0, WriteCmdLCDReady=0,
	SetDDRamAddr_Case=0, SetDDRamAddrReady=0, WriteDataLCD_Case=0, WriteDataLCDReady=0,
	putrsLCD_Case=0, putrsLCDReady=0, putsLCD_Case=0, putsLCDReady=0;

const char *buffer2;
char *buffer3;

unsigned char OpenLCD(unsigned char lcdtype)
{
	switch(OpenLCD_Case)
	{
		case	0	:	TRIS_DATA_PORT |= 0x0f;			// needed for soft reset mcu without powersupply reboot
						E_PIN = 1;						// needed for soft reset mcu without powersupply reboot
						OpenLCD_Case=1;
						OpenLCDReady=0;
						break;
						
		case	1	:	DATA_PORT &= 0xf0;				//lower nibble Outputs to 0
        				TRIS_DATA_PORT |= 0x0f;			//lower nibble inputs
        				TRIS_RW = 0;                    // All control signals made outputs
				        TRIS_RS = 0;
				        TRIS_E = 0;
				        RW_PIN = 0;                     // R/W pin made low
				        RS_PIN = 0;                     // Register select pin made low
				        E_PIN = 0;                      // Clock pin made low
						// Delay for 15ms to allow for LCD Power on reset
						OpenLCD_Case=2;
						OpenLCDReady=0;
						break;
						
		case	2	:	TRIS_DATA_PORT &= 0xf0;			// lower nibble output
						DATA_PORT &= 0xf0;				// 
				        DATA_PORT |= 0b00000010;        // Function set cmd(4-bit interface send 3 times)
		       			E_PIN = 1;						// Clock cmd in
		       			OpenLCD_Case=3;
		       			OpenLCDReady=0;
		       			break;
		       			
		case	3	:	E_PIN = 0;
						OpenLCD_Case=4;
						OpenLCDReady=0;					
						break;
						
		case	4	:	OpenLCD_Case=5;					//Wait for at least 4.1ms
						OpenLCDReady=0;
						break;
						
		case	5	:	DATA_PORT &= 0xf0;
				        DATA_PORT |= 0b00000010;        // Function set cmd(4-bit interface send 3 times)
		       			E_PIN = 1;						// Clock cmd in
		       			OpenLCD_Case=6;
		       			OpenLCDReady=0;
		       			break;
		       			
		case	6	:	E_PIN = 0;
						OpenLCD_Case=7;
						OpenLCDReady=0;					
						break;
						
		case	7	:	OpenLCD_Case=8;					//Wait for at least 4.1ms
						OpenLCDReady=0;
						break;	

		case	8	:	DATA_PORT &= 0xf0;
				        DATA_PORT |= 0b00000010;        // Function set cmd(4-bit interface send 3 times)
		       			E_PIN = 1;						// Clock cmd in
		       			OpenLCD_Case=9;
		       			OpenLCDReady=0;
		       			break;
		       			
		case	9	:	E_PIN = 0;
						TRIS_DATA_PORT |= 0x0f;			// lower nibble input Init 4 bit Done
						OpenLCD_Case=10;
						OpenLCDReady=0;					
						break;
						
		case	10	:	if ( WriteCmdLCD(lcdtype)==1)   // Set data interface width, # lines, font
						{
							OpenLCD_Case=11;
						}
						else OpenLCD_Case=10;
						OpenLCDReady=0;
						break;
	
		case	11	:	if ( WriteCmdLCD(DOFF&CURSOR_OFF&BLINK_OFF)==1)   // Display OFF/Blink OFF
						{
							OpenLCD_Case=12;
						}
						else OpenLCD_Case=11;
						OpenLCDReady=0;
						break;
	
		case	12	:	if ( WriteCmdLCD(DON&CURSOR_OFF&BLINK_OFF)==1)   // Display ON/Blink ON
						{
							OpenLCD_Case=13;
						}
						else OpenLCD_Case=12;
						OpenLCDReady=0;
						break;
	
		case	13	:	if ( WriteCmdLCD(0x01)==1)   // Clear display
						{
							OpenLCD_Case=14;
						}
						else OpenLCD_Case=13;
						OpenLCDReady=0;
						break;
	
		case	14	:	if ( WriteCmdLCD(SHIFT_CUR_LEFT)==1)   // Entry Mode
						{
							OpenLCD_Case=15;
						}
						else OpenLCD_Case=14;
						OpenLCDReady=0;
						break;
						
		case	15	:	if ( SetDDRamAddr(0) == 1 )                // Set Display data ram address to 0
						{
							OpenLCD_Case=16;
						}
						else OpenLCD_Case=15;
						break;
						
		case	16	:	OpenLCD_Case=0;
						OpenLCDReady=1;
						break;
						
		default		:	OpenLCD_Case=0;
						OpenLCDReady=0;
						break;
	}
	
	if ( OpenLCDReady == 1)
	{
		OpenLCDReady=0;
		return 1;
	}
	else return 0;
}	
		
/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

unsigned char WriteCmdLCD(unsigned char cmd)
{
	switch (WriteCmdLCD_Case)
	{
		case	0	:	TRIS_DATA_PORT &= 0xf0;
				        DATA_PORT &= 0xf0;
				        DATA_PORT |= (cmd>>4)&0x0f;
				        RW_PIN = 0;                     // Set control signals for command
        				RS_PIN = 0;
        				WriteCmdLCD_Case=1;
        				WriteCmdLCDReady=0;
        				break;
        				
        case	1	:	E_PIN = 1;
        				WriteCmdLCD_Case=2;
        				WriteCmdLCDReady=0;
        				break;
        				
        case	2	:	E_PIN = 0;
        				DATA_PORT &= 0xf0;
        				DATA_PORT |= cmd&0x0f;
        				WriteCmdLCD_Case=3;
        				WriteCmdLCDReady=0;
        				break;
        				
        case	3	:	E_PIN = 1;
        				WriteCmdLCD_Case=4;
        				WriteCmdLCDReady=0;
        				break;
        				
        case	4	:	E_PIN = 0;
        				TRIS_DATA_PORT |= 0x0f;
        				WriteCmdLCD_Case=0;
        				WriteCmdLCDReady=1;
        				break;
        				
/*        case	5	:	WriteCmdLCD_Case=0;
        				WriteCmdLCDReady=1;
        				break;*/
        				
        default		:	WriteCmdLCD_Case=0;
        				WriteCmdLCDReady=0;
        				break;
        				
	}
	
	if ( WriteCmdLCDReady == 1)
	{
		WriteCmdLCDReady=0;
		return 1;
	}
	else return 0;
}

/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

unsigned char SetDDRamAddr(unsigned char DDaddr)
{
	switch ( SetDDRamAddr_Case )
	{
		case	0	:	TRIS_DATA_PORT &= 0xf0;                 // Make port output
        				DATA_PORT &= 0xf0;                      // and write lower nibble
        				DATA_PORT |= (((DDaddr | 0b10000000)>>4) & 0x0f);
        				RW_PIN = 0;                             // Set control bits
        				RS_PIN = 0;
        				SetDDRamAddr_Case=1;
        				SetDDRamAddrReady=0;
        				break;
        				
        case	1	:	E_PIN = 1;
        				SetDDRamAddr_Case=2;
        				SetDDRamAddrReady=0;
        				break;
        				
		case	2	:	E_PIN = 0;
						DATA_PORT &= 0xf0;                      // Write lower nibble
        				DATA_PORT |= (DDaddr&0x0f);
        				SetDDRamAddr_Case=3;
        				SetDDRamAddrReady=0;
        				break;
        				
        case	3	:	E_PIN = 1;
        				SetDDRamAddr_Case=4;
        				SetDDRamAddrReady=0;
        				break;
        				
        case	4	:	E_PIN = 0;
        				TRIS_DATA_PORT |= 0x0f;                 // Make port input
        				SetDDRamAddr_Case=0;
        				SetDDRamAddrReady=1;
        				break;
        				
 /*       case	5	:	SetDDRamAddr_Case=0;
        				SetDDRamAddrReady=1;
        				break;*/
        				
        default		:	SetDDRamAddr_Case=0;
        				SetDDRamAddrReady=0;
        				break;
	}
	
	if ( SetDDRamAddrReady == 1 )
	{
		SetDDRamAddrReady=0;
		return 1;
	}
	else return 0;
}

/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

unsigned char putrsLCD(const char *buffer)
{
       switch (putrsLCD_Case)
       {
	       case	0	:	buffer2=buffer;
	       				putrsLCD_Case=1;
	               		putrsLCDReady=0;
	               		break;
	       
	       case	1	:	if(*buffer2)
	       				{
		       				putrsLCD_Case=2;
	               			putrsLCDReady=0;
	           			}
	           			else putrsLCDReady=1;
	           			break;		    		
	       
	       case	2	:	if(WriteDataLCD(*buffer2)) 	// Write character to LCD
                		{
	               			putrsLCD_Case=3;
	               			putrsLCDReady=0;
                		}
                		else putrsLCD_Case=1;
                		break;
                	
			case 3	:	buffer2++;               	// Increment buffer
						putrsLCD_Case=1;
	               		putrsLCDReady=0;
	               		break;
                	
			default	:	putrsLCD_Case=0;
	               		putrsLCDReady=0;
	               		break;
		}
		
		if (putrsLCDReady == 1)
		{
			putrsLCDReady=0;
			putrsLCD_Case=0;
			return 1;
		}
		else return 0;
}
/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

unsigned char putsLCD(char *buffer)
{
	switch (putsLCD_Case)
	{
		case	0	:	buffer3=buffer;
	       				putsLCD_Case=1;
	               		putsLCDReady=0;
	               		break;
	       
	       case	1	:	if(*buffer3)
	       				{
		       				putsLCD_Case=2;
	               			putsLCDReady=0;
	           			}
	           			else putsLCDReady=1;
	           			break;		    		
	       
	       case	2	:	if(WriteDataLCD(*buffer3)) 	// Write character to LCD
                		{
	               			putsLCD_Case=3;
	               			putsLCDReady=0;
                		}
                		else putrsLCD_Case=1;
                		break;
                	
			case 3	:	buffer3++;               	// Increment buffer
						putsLCD_Case=1;
	               		putsLCDReady=0;
	               		break;
                	
			default	:	putsLCD_Case=0;
	               		putsLCDReady=0;
	               		break;
		}
		
		if (putsLCDReady == 1)
		{
			putsLCDReady=0;
			putsLCD_Case=0;
			return 1;
		}
		else return 0;
}	

/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

unsigned char WriteDataLCD(char data)
{
	switch (WriteDataLCD_Case)
	{
		case	0	:	TRIS_DATA_PORT &= 0xf0;
				        DATA_PORT &= 0xf0;
	        			DATA_PORT |= ((data>>4)&0x0f);
	        			RS_PIN = 1;                     // Set control bits
        				RW_PIN = 0;
        				WriteDataLCD_Case=1;
        				WriteDataLCDReady=0;
        				break;
        				
        case	1	:	E_PIN = 1;
        				WriteDataLCD_Case=2;
        				WriteDataLCDReady=0;
        				break;
        				
        case	2	:	E_PIN = 0;
				        DATA_PORT &= 0xf0;
				        DATA_PORT |= (data&0x0f);
        				WriteDataLCD_Case=3;
        				WriteDataLCDReady=0;
        				break;
        				
        case	3	:	E_PIN = 1;
        				WriteDataLCD_Case=4;
        				WriteDataLCDReady=0;
        				break;
        				
        case	4	:	E_PIN = 0;
				        TRIS_DATA_PORT |= 0x0f;
        				WriteDataLCD_Case=0;
        				WriteDataLCDReady=1;
        				break;
        				
 /*       case	5	:	WriteDataLCD_Case=0;
        				WriteDataLCDReady=1;
        				break;*/
        				
        default		:	WriteDataLCD_Case=0;
        				WriteDataLCDReady=0;
        				break;
	}
	
	if (WriteDataLCDReady == 1)
	{
		WriteDataLCDReady=0;
		return 1;
	}
	else return 0;
}

/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////