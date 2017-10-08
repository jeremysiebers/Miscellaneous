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
															case	Straight	:	Wl_Left_Str = 1;	break;
															case	Bend		:	Wl_Left_Bnd	= 1;	break;
															default				:	break;
														}
														break;
														
									case	Right	:	switch (Straight_Bend)
														{
															case	Straight	:	Wl_Right_Str = 1;	break;
															case	Bend		:	Wl_Right_Bnd = 1;	break;
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
								
		case	2			:	Wl_Left_Str = 0;
								Wl_Left_Bnd	= 0;
								Wl_Right_Str = 0;
								Wl_Right_Bnd = 0;
								Switch_Junction = 0;
								Return_Val = Finished;
								break;
		
		default				:	break;
	}
	
	return (Return_Val);
}