#include "Main.h"
#include "io.h"
#include <xc.h>
#include "api.h"




unsigned char 	Reed_Contact_LF_Counter = 0,
				Reed_Contact_LB_Counter = 0,
				Reed_Contact_RF_Counter = 0,
				Reed_Contact_RB_Counter = 0,
				Reed_Contact_LMU_Counter = 0,
				Reed_Contact_LMD_Counter = 0,
				Reed_Contact_RMU_Counter = 0,
				Reed_Contact_RMD_Counter = 0,
				Button_Contact_Counter_Start = 0,
				Button_Contact_Counter_Stop = 0,
				Button_Contact_Counter_Middle = 0,
				Button_Contact_Counter_LB = 0,
				Button_Contact_Counter_LF = 0,
				Button_Contact_Counter_RB = 0,
				Button_Contact_Counter_RF = 0;
				
				
unsigned int	Green_Led_Counter = 0,
				Red_Led_Counter = 0;





/******************************************************************************
 * Function:        static void Green_Led(unsigned char Operation)
 *                  Blinking routine for green led
 *
 * PreCondition:    None
 *
 * Input:           Blinking speed
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        None
 *****************************************************************************/
void Green_Led(unsigned char Operation)
{
	switch(Operation)
	{
		case	Off		:	Green = Off; 	break;
		
		case	On		:	Green = On;		break;
		
		case	Blink	:	Green_Led_Counter++;
							if(Green_Led_Counter >= BlinkHz)
							{
								Green_Led_Counter = 0;
							}
							if(Green_Led_Counter >= BlinkHz/2)
							{
								Green = On;
							}
							else {Green = Off;}
							break;
							
		case	Blink1	:	Green_Led_Counter++;
							if(Green_Led_Counter >= BlinkHz1)
							{
								Green_Led_Counter = 0;
							}
							if(Green_Led_Counter >= BlinkHz1/2)
							{
								Green = On;
							}
							else {Green = Off;}
							break;
							
		default			:	break;
	}
}

/******************************************************************************
 * Function:        static void Red_Led(unsigned char Operation)
 *                  Blinking routine for red led
 *
 * PreCondition:    None
 *
 * Input:           Blinking speed
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        None
 *****************************************************************************/
void Red_Led(unsigned char Operation)
{
	switch(Operation)
	{
		case	Off		:	Red = Off; 	break;
		
		case	On		:	Red = On; 	break;
		
		case	Blink	:	Red_Led_Counter++;
							if(Red_Led_Counter >= BlinkHz)
							{
								Red_Led_Counter = 0;
							}
							if(Red_Led_Counter >= BlinkHz/2)
							{
								Red = On;
							}
							else {Red = Off;}
							break;
							
		case	Blink1	:	Red_Led_Counter++;
							if(Red_Led_Counter >= BlinkHz1)
							{
								Red_Led_Counter = 0;
							}
							if(Red_Led_Counter >= BlinkHz1/2)
							{
								Red = On;
							}
							else {Red = Off;}
							break;
							
		default			:	break;
	}
}


/******************************************************************************
 * Function:        static void Debounce_Inputs(void)
 *                  Debounce all the inputs
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    Updates API[index] accordingly
 *
 * Overview:        None
 *****************************************************************************/
void Debounce_Inputs(void)
{
	switch(Reed_Contact_LF)
	{
		case	On	:	if(Reed_Contact_LF_Counter > 0)
						{
							Reed_Contact_LF_Counter--;
							break;
						}
						else {SETxAPIxVAL(RC_LF, Off);}
						break;
						
		case	Off	:	if(Reed_Contact_LF_Counter <= GETxAPIxVAL(INPUT_DEBOUNCE))
						{
							Reed_Contact_LF_Counter++;
							break;
						}
						else {SETxAPIxVAL(RC_LF, On);}
						break;
		
		default		:	break;
	}
	
	
	switch(Reed_Contact_LB)
	{
		case	On	:	if(Reed_Contact_LB_Counter > 0)
						{
							Reed_Contact_LB_Counter--;
							break;
						}
						else {SETxAPIxVAL(RC_LB, Off);}
						break;
						
		case	Off	:	if(Reed_Contact_LB_Counter <= GETxAPIxVAL(INPUT_DEBOUNCE))
						{
							Reed_Contact_LB_Counter++;
							break;
						}
						else {SETxAPIxVAL(RC_LB, On);}
						break;
		
		default		:	break;
	}
	
	
	switch(Reed_Contact_RF)
	{
		case	On	:	if(Reed_Contact_RF_Counter > 0)
						{
							Reed_Contact_RF_Counter--;
							break;
						}
						else {SETxAPIxVAL(RC_RF, Off);}
						break;
						
		case	Off	:	if(Reed_Contact_RF_Counter <= GETxAPIxVAL(INPUT_DEBOUNCE))
						{
							Reed_Contact_RF_Counter++;
							break;
						}
						else {SETxAPIxVAL(RC_RF, On);}
						break;
		
		default		:	break;
	}
	

	switch(Reed_Contact_RB)
	{
		case	On	:	if(Reed_Contact_RB_Counter > 0)
						{
							Reed_Contact_RB_Counter--;
							break;
						}
						else {SETxAPIxVAL(RC_RB, Off);}
						break;
						
		case	Off	:	if(Reed_Contact_RB_Counter <= GETxAPIxVAL(INPUT_DEBOUNCE))
						{
							Reed_Contact_RB_Counter++;
							break;
						}
						else {SETxAPIxVAL(RC_RB, On);}
						break;
		
		default		:	break;
	}
	
	
	switch(But_Start)
	{
		case	On	:	if(Button_Contact_Counter_Start <= GETxAPIxVAL(INPUT_DEBOUNCE))
						{
							Button_Contact_Counter_Start++;
							break;
						}
						else {SETxAPIxVAL(BTN_START, On); }
						break;
		
		case	Off	:	if(Button_Contact_Counter_Start > 0)
						{
							Button_Contact_Counter_Start--;
							break;
						}
						else {SETxAPIxVAL(BTN_START, Off);}
						break;
						
		default		:	break;
	}
	
	
	switch(But_Stop)
	{
		case	On	:	if(Button_Contact_Counter_Stop <= GETxAPIxVAL(INPUT_DEBOUNCE))
						{
							Button_Contact_Counter_Stop++;
							break;
						}
						else {SETxAPIxVAL(BTN_STOP, On); }
						break;
		
		case	Off	:	if(Button_Contact_Counter_Stop > 0)
						{
							Button_Contact_Counter_Stop--;
							break;
						}
						else {SETxAPIxVAL(BTN_STOP, Off);}
						break;
						
		default		:	break;
	}
	
	
	switch(But_Middle)
	{
		case	On	:	if(Button_Contact_Counter_Middle <= GETxAPIxVAL(INPUT_DEBOUNCE))
						{
							Button_Contact_Counter_Middle++;
							break;
						}
						else {SETxAPIxVAL(BTN_MID, On); }
						break;
		
		case	Off	:	if(Button_Contact_Counter_Middle > 0)
						{
							Button_Contact_Counter_Middle--;
							break;
						}
						else {SETxAPIxVAL(BTN_MID, Off);}
						break;
						
		default		:	break;
	}
	
	
	switch(But_LB)
	{
		case	On	:	if(Button_Contact_Counter_LB <= GETxAPIxVAL(INPUT_DEBOUNCE))
						{
							Button_Contact_Counter_LB++;
							break;
						}
						else {SETxAPIxVAL(BTN_LB, On); }
						break;
		
		case	Off	:	if(Button_Contact_Counter_LB > 0)
						{
							Button_Contact_Counter_LB--;
							break;
						}
						else {SETxAPIxVAL(BTN_LB, Off);}
						break;
						
		default		:	break;
	}
	
	
	switch(But_LF)
	{
		case	On	:	if(Button_Contact_Counter_LF <= GETxAPIxVAL(INPUT_DEBOUNCE))
						{
							Button_Contact_Counter_LF++;
							break;
						}
						else {SETxAPIxVAL(BTN_LF, On); }
						break;
		
		case	Off	:	if(Button_Contact_Counter_LF > 0)
						{
							Button_Contact_Counter_LF--;
							break;
						}
						else {SETxAPIxVAL(BTN_LF, Off);}
						break;
						
		default		:	break;
	}
	
	
	switch(But_RB)
	{
		case	On	:	if(Button_Contact_Counter_RB <= GETxAPIxVAL(INPUT_DEBOUNCE))
						{
							Button_Contact_Counter_RB++;
							break;
						}
						else {SETxAPIxVAL(BTN_RB, On); }
						break;
		
		case	Off	:	if(Button_Contact_Counter_RB > 0)
						{
							Button_Contact_Counter_RB--;
							break;
						}
						else {SETxAPIxVAL(BTN_RB, Off);}
						break;
						
		default		:	break;
	}
	
	
		switch(But_RF)
	{
		case	On	:	if(Button_Contact_Counter_RF <= GETxAPIxVAL(INPUT_DEBOUNCE))
						{
							Button_Contact_Counter_RF++;
							break;
						}
						else {SETxAPIxVAL(BTN_RF, On); }
						break;
		
		case	Off	:	if(Button_Contact_Counter_RF > 0)
						{
							Button_Contact_Counter_RF--;
							break;
						}
						else {SETxAPIxVAL(BTN_RF, Off);}
						break;
						
		default		:	break;
	}
	
	
	switch(Reed_Contact_LMU)
	{
		case	Off	:	if(Reed_Contact_LMU_Counter <= GETxAPIxVAL(INPUT_DEBOUNCE))
						{
							Reed_Contact_LMU_Counter++;
							break;
						}
						else {SETxAPIxVAL(RC_LMU, On); }
						break;
		
		case	On	:	if(Reed_Contact_LMU_Counter > 0)
						{
							Reed_Contact_LMU_Counter--;
							break;
						}
						else {SETxAPIxVAL(RC_LMU, Off);}
						break;
						
		default		:	break;
	}
	
	
	switch(Reed_Contact_LMD)
	{
		case	Off	:	if(Reed_Contact_LMD_Counter <= GETxAPIxVAL(INPUT_DEBOUNCE))
						{
							Reed_Contact_LMD_Counter++;
							break;
						}
						else {SETxAPIxVAL(RC_LMD, On); }
						break;
		
		case	On	:	if(Reed_Contact_LMD_Counter > 0)
						{
							Reed_Contact_LMD_Counter--;
							break;
						}
						else {SETxAPIxVAL(RC_LMD, Off);}
						break;
						
		default		:	break;
	}
	
	
	switch(Reed_Contact_RMU)
	{
		case	Off	:	if(Reed_Contact_RMU_Counter <= GETxAPIxVAL(INPUT_DEBOUNCE))
						{
							Reed_Contact_RMU_Counter++;
							break;
						}
						else {SETxAPIxVAL(RC_RMU, On); }
						break;
		
		case	On	:	if(Reed_Contact_RMU_Counter > 0)
						{
							Reed_Contact_RMU_Counter--;
							break;
						}
						else {SETxAPIxVAL(RC_RMU, Off);}
						break;
						
		default		:	break;
	}
	
	
	switch(Reed_Contact_RMD)
	{
		case	Off	:	if(Reed_Contact_RMD_Counter <= GETxAPIxVAL(INPUT_DEBOUNCE))
						{
							Reed_Contact_RMD_Counter++;
							break;
						}
						else {SETxAPIxVAL(RC_RMD, On); }
						break;
		
		case	On	:	if(Reed_Contact_RMD_Counter > 0)
						{
							Reed_Contact_RMD_Counter--;
							break;
						}
						else {SETxAPIxVAL(RC_RMD, Off);}
						break;
						
		default		:	break;
	}
}