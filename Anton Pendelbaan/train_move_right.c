#include "Main.h"
#include "io.h"
#include <xc.h>
#include "api.h"
#include "set_pwm.h"

unsigned char 	Switch_Train_Move = 0,
                Switch_Moutain = 0;

unsigned int	Train_Move_Pwm_Fast_Count = 0,
                Mountain_Delay_Counter = 0;

/******************************************************************************
 * Function:        static char Train_Move_Right_Start(void)
 *                  Start moving the train to the right
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          returns busy or finished
 *
 * Side Effects:    None
 *
 * Overview:        None
 *****************************************************************************/
char Train_Move_Right_Start(void)
{
	static char Return_Val = Busy;
	static unsigned int Train_Move_Wait_Time = 0;
	
	switch(Switch_Train_Move)
	{
		////////////////When Starting jumping to case 0 (Start_Move)////////////////////////////
		
		case	0	:	if(Train_Move_Wait_Time >= GETxAPIxVAL(LIGHTS_ON_WAIT_TIME))
						{
							Switch_Train_Move = 1;
							Train_Move_Wait_Time = 0;
							Return_Val = Busy;
							break;
						}
						Train_Move_Wait_Time++;
						Switch_Train_Move = 0;
						Return_Val = Busy;
						break;
		
		case	1	:	SETxPWM(GETxAPIxVAL(STATIONARY_RIGHT), Right);
						Train_Move_Pwm_Count = GETxAPIxVAL(STATIONARY_RIGHT);
						SETxAPIxVAL(PWM_BRAKE, Off);;
						Return_Val = Busy;
						Switch_Train_Move = 2;						
						break;
						
		case	2	:	if(Train_Move_Wait_Time >= GETxAPIxVAL(TRAIN_WAIT_TIME))
						{
							Switch_Train_Move = 3;
							Train_Move_Wait_Time = 0;
							Return_Val = Busy;
							break;
						}
						Return_Val = Busy;
						Train_Move_Wait_Time++;
						Switch_Train_Move = 2;
						break;
						
		case	3	:	SETxPWM(Train_Move_Pwm_Count, Right);
						if (Train_Move_Pwm_Count >= GETxAPIxVAL(MAX_PWM_RIGHT))
						{
							Switch_Train_Move = 0;
							Return_Val = Finished;
							break;
						}
						if (Train_Move_Pwm_Fast_Count >= GETxAPIxVAL(MAX_JERK_PWM))
						{
							Train_Move_Pwm_Count++;
							Train_Move_Pwm_Fast_Count = 0;
						}
						Train_Move_Pwm_Fast_Count++;
						Return_Val = Busy;
						break;
						
		default		:	break;
	}
	
	return(Return_Val);	
	
}

/******************************************************************************
 * Function:        static char Left_Mountain_From_The_Left(unsigned char rc)
 *                  Encountering left mountain from the left
 *
 * PreCondition:    None
 *
 * Input:           Reed contact
 *
 * Output:          returns busy or finished
 *
 * Side Effects:    None
 *
 * Overview:        None
 *****************************************************************************/
char Left_Mountain_From_The_Left(unsigned char rc)
{
    static char Return_Val = Busy;
    
    switch (Switch_Moutain){
        case 0: if (rc == LMD){                                                 // when train arrives up on left mountain no delay is required
                    Switch_Moutain = 1;
                    Mountain_Delay_Counter = 0;
                }
                else if(Mountain_Delay_Counter >= GETxAPIxVAL(DELAY_LMU_DOWN)){
                    Switch_Moutain = 1;
                    Mountain_Delay_Counter = 0;
                }
                else{
                    Mountain_Delay_Counter++;
                }  
                Return_Val = Busy;
                break;
            
        case 1: if(rc == LMU){
                    SETxPWM(Train_Move_Pwm_Count, Right);        
                    if (Train_Move_Pwm_Count <= GETxAPIxVAL(MAX_PWM_LMU_RIGHT)) // when actual speed is too high for going down at LMU
                    {
                        Switch_Train_Move = 0;
                        Switch_Moutain = 0;
                        Return_Val = Finished; 
                        break;
                    }
                    else if (Train_Move_Pwm_Fast_Count >= GETxAPIxVAL(MAX_JERK_PWM))
                    {
                        Train_Move_Pwm_Count--;                                 // Less current is required
                        Train_Move_Pwm_Fast_Count = 0;
                    }
                    else{Train_Move_Pwm_Fast_Count++;}
                }
                else if (rc == LMD){
                    SETxPWM(Train_Move_Pwm_Count, Right);        
                    if (Train_Move_Pwm_Count >= GETxAPIxVAL(MAX_PWM_RIGHT))     // when actual speed is slower then normal speed
                    {
                        Switch_Train_Move = 0;
                        Switch_Moutain = 0;
                        Return_Val = Finished;
                        break;
                    }
                    else if (Train_Move_Pwm_Fast_Count >= GETxAPIxVAL(MAX_JERK_PWM))
                    {
                        Train_Move_Pwm_Count++;
                        Train_Move_Pwm_Fast_Count = 0;
                    }
                    else {Train_Move_Pwm_Fast_Count++;}
                }
                Return_Val = Busy;
                break;
            
        default:
            break;
    }   
    
    return(Return_Val);
}

/******************************************************************************
 * Function:        static char Right_Mountain_From_The_Left(unsigned char rc)
 *                  Encountering right mountain from the left
 *
 * PreCondition:    None
 *
 * Input:           Reed contact
 *
 * Output:          returns busy or finished
 *
 * Side Effects:    None
 *
 * Overview:        None
 *****************************************************************************/
char Right_Mountain_From_The_Left(unsigned char rc)
{
    static char Return_Val = Busy;
    
    switch (Switch_Moutain){
        case 0: if (rc == RMU){                                                 // when train arrives up on right mountain no delay is required
                    Switch_Moutain = 1;
                    Mountain_Delay_Counter = 0;
                }
                else if(Mountain_Delay_Counter >= GETxAPIxVAL(DELAY_RMD_UP)){
                    Switch_Moutain = 1;
                    Mountain_Delay_Counter = 0;
                }
                else{
                    Mountain_Delay_Counter++;
                }
                Return_Val = Busy;
                break;
            
        case 1: if(rc == RMD){
                    SETxPWM(Train_Move_Pwm_Count, Right);        
                    if (Train_Move_Pwm_Count >= GETxAPIxVAL(MAX_PWM_RMD_RIGHT)) // when actual speed is adjusted for going up at RMU
                    {
                        Switch_Train_Move = 0;
                        Switch_Moutain = 0;
                        Return_Val = Finished;
                        break;
                    }
                    else if (Train_Move_Pwm_Fast_Count >= GETxAPIxVAL(MAX_JERK_PWM))
                    {
                        Train_Move_Pwm_Count++;                                 // More current is required
                        Train_Move_Pwm_Fast_Count = 0;
                    }
                    else{Train_Move_Pwm_Fast_Count++;}
                }
                else if (rc == RMU){
                    SETxPWM(Train_Move_Pwm_Count, Right);        
                    if (Train_Move_Pwm_Count <= GETxAPIxVAL(MAX_PWM_RIGHT))     // when actual speed is higher then normal speed
                    {
                        Switch_Train_Move = 0;
                        Switch_Moutain = 0;
                        Return_Val = Finished;   
                        break;
                    }
                    else if (Train_Move_Pwm_Fast_Count >= GETxAPIxVAL(MAX_JERK_PWM))
                    {
                        Train_Move_Pwm_Count--;                                 // Less current is required
                        Train_Move_Pwm_Fast_Count = 0;
                    }
                    else{Train_Move_Pwm_Fast_Count++;}
                }
                Return_Val = Busy;
                break;
            
        default:
            break;
    }   
    
    return(Return_Val);
}

/******************************************************************************
 * Function:        static char Train_Move_Right_Brake(void)
 *                  Stop moving the train to the right
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          returns busy or finished
 *
 * Side Effects:    None
 *
 * Overview:        None
 *****************************************************************************/
char Train_Move_Right_Brake(void)
{
	static char Return_Val = Busy;
	static unsigned int Train_Move_Wait_Time = 0;
	
	switch(Switch_Train_Move)
	{
	case	0	:		SETxPWM(Train_Move_Pwm_Count, Right);
						if (Train_Move_Pwm_Count <= GETxAPIxVAL(STATIONARY_RIGHT))
						{
							Switch_Train_Move = 1;
							Return_Val = Busy;
							break;
						}
						if (Train_Move_Pwm_Fast_Count >= GETxAPIxVAL(MAX_JERK_PWM_BRAKE))
						{
							Train_Move_Pwm_Count--;
							Train_Move_Pwm_Fast_Count = 0;
						}
                        else{Train_Move_Pwm_Fast_Count++;}
						Return_Val = Busy;
						break;
						
		case	1	:	if(Train_Move_Wait_Time >= GETxAPIxVAL(TRAIN_WAIT_TIME))
						{
							Switch_Train_Move = 2;
							Train_Move_Wait_Time = 0;
							Return_Val = Busy;
							break;
						}
						Return_Val = Busy;
						Train_Move_Wait_Time++;
						Switch_Train_Move = 1;
						break;
						
		case	2	:	SETxPWM(GETxAPIxVAL(STATIONARY_RIGHT), Right);
						SETxAPIxVAL(PWM_BRAKE, On);;
						Train_Move_Pwm_Count = GETxAPIxVAL(STATIONARY_RIGHT);
						Switch_Train_Move = 3;
						Return_Val = Busy;
						break;
						
		case	3	:	if(Train_Move_Wait_Time >= GETxAPIxVAL(LIGHTS_ON_WAIT_TIME))
						{
							Switch_Train_Move = 0;
							Train_Move_Wait_Time = 0;
							Return_Val = Finished;
							break;
						}
						Train_Move_Wait_Time++;
						Switch_Train_Move = 3;
						Return_Val = Busy;
						break;
						
		default		:	break;
	}
	
	return(Return_Val);	
	
}