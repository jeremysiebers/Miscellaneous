#include "Main.h"
#include "io.h"
#include <xc.h>
#include "api.h"

unsigned char 	Switch_Junction = 0;

/******************************************************************************
 * Function:        static char Junction(unsigned char Junction_Left_Right, 
 *                                              unsigned char Straight_Bend)
 *                  Set the junction accordingly
 *
 * PreCondition:    None
 *
 * Input:           Junction Left or right, straight or bend the junction
 *
 * Output:          returns busy or finished
 *
 * Side Effects:    None
 *
 * Overview:        None
 *****************************************************************************/



char Junction(unsigned char Junction_Left_Right, unsigned char Straight_Bend)
{
	static char Return_Val = Busy;
	static unsigned int Junction_Switch_Time = 0;
	
	switch (Switch_Junction)
	{
		case	0			:	Return_Val = Busy;
								switch (Junction_Left_Right)
								{
									case	Left	:	switch (Straight_Bend)
														{
															case	Straight	:	SETxAPIxVAL(JUNCTION_LEFT_STR, On);
                                                                                    SETxAPIxVAL(JUNCTION_LEFT_STR_PREV, On);
                                                                                    SETxAPIxVAL(JUNCTION_LEFT_BND_PREV, Off);
                                                                                    break;
															case	Bend		:	SETxAPIxVAL(JUNCTION_LEFT_BND, On);
                                                                                    SETxAPIxVAL(JUNCTION_LEFT_STR_PREV, Off);
                                                                                    SETxAPIxVAL(JUNCTION_LEFT_BND_PREV, On);	
                                                                                    break;
															default				:	break;
														}
														break;
														
									case	Right	:	switch (Straight_Bend)
														{
															case	Straight	:	SETxAPIxVAL(JUNCTION_RIGHT_STR,On);
                                                                                    SETxAPIxVAL(JUNCTION_RIGHT_STR_PREV, On);
                                                                                    SETxAPIxVAL(JUNCTION_RIGHT_BND_PREV, Off);
                                                                                    break;
															case	Bend		:	SETxAPIxVAL(JUNCTION_RIGHT_BND,On);
                                                                                    SETxAPIxVAL(JUNCTION_RIGHT_STR_PREV, Off);
                                                                                    SETxAPIxVAL(JUNCTION_RIGHT_BND_PREV, On);
                                                                                    break;
															default				:	break;
														}
														break;
														
									default			:	break;
								}
								Switch_Junction = 1;
								break;	
								
		case	1			:	if (Junction_Switch_Time >= GETxAPIxVAL(JUNCTION_WAIT_TIME))	
								{
									Switch_Junction = 2;
									Junction_Switch_Time = 0;
									Return_Val = Busy;
									break;
								}
								Return_Val = Busy;
								Switch_Junction = 1;
								Junction_Switch_Time++;
								break;
								
		case	2			:	SETxAPIxVAL(JUNCTION_LEFT_STR, Off);
								SETxAPIxVAL(JUNCTION_LEFT_BND, Off);
								SETxAPIxVAL(JUNCTION_RIGHT_STR,Off);
								SETxAPIxVAL(JUNCTION_RIGHT_BND,Off);
								Switch_Junction = 0;
								Return_Val = Finished;
								break;
		
		default				:	break;
	}
	
	return (Return_Val);
}





