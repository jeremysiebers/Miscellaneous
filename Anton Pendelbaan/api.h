/* 
 * File:   
 * Author: 
 * Comments:
 * Revision history: 
 */
 
#ifndef XC_HEADER_TEMPLATE_H
#define	XC_HEADER_TEMPLATE_H

extern void APIxInitialize(void);
extern unsigned int GETxAPIxRW(unsigned char index);
extern void SETxAPIxVAL(unsigned char index, unsigned int value);
extern void INCRxAPIxVAL(unsigned char index);
extern void DECRxAPIxVAL(unsigned char index);
extern unsigned int GETxAPIxVAL(unsigned char index);
extern unsigned int  API[];



/******************************************************************************
 * Function:        API
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        Here all API addresses are declared
 *****************************************************************************/
#define     API_SIZE                    16	   	// Size of the API stored here in location 0
#define     WATCHDOG                    17	   	// Variable in API will be written and read by master to verify communication on both sides
#define     TRAIN_WAIT_TIME             18	   	// Time to wait before departure/lightsoff
#define     JUNCTION_WAIT_TIME          19	   	// Junction switing delay time
#define     LIGHTS_ON_WAIT_TIME         20	   	// Lights on time before departure
#define     STATIONARY_LEFT             21	   	// Stationary PWM dutycycle for left drive
#define     STATIONARY_RIGHT            22	   	// Stationary PWM dutycycle for right drive
#define     MAX_PWM_RIGHT               23	   	// PWM right (dutycycle) speed setting
#define     MAX_PWM_LEFT                24	   	// PWM left (dutycycle) speed setting
#define     MAX_JERK_PWM_BRAKE          25	   	// braking speed (deceleration)
#define     MAX_JERK_PWM                26	  	// acceleration speed
#define     INPUT_DEBOUNCE              27	  	// input signal debouncing filter
#define		RC_RB						28		// Reed Contact Right Back
#define		RC_RF						29		// Reed Contact Right Front
#define		RC_LB						30		// Reed Contact Left Back
#define		RC_LF						31		// Reed Contact Left Front
#define		BTN_START					32		// Buttont Start
#define		BTN_STOP					33		// Buttont Stop
#define		BTN_MID  					34		// Buttont Middle
#define		BTN_LB 						35		// Buttont Left Back
#define		BTN_LF						36		// Buttont Left Front
#define		BTN_RB						37		// Buttont Right Back
#define		BTN_RF						38		// Buttont Right Front
#define 	TRAIN1_POS					39		// Train 1 Position
#define 	TRAIN2_POS					40		// Train 2 Position
#define		RC_LMU						41		// Reed Contact Left Mountain Up
#define		RC_LMD						42		// Reed Contact Left Mountain Down
#define		RC_RMU						43		// Reed Contact Right Mountain Up
#define		RC_RMD						44		// Reed Contact Right Mountain Down
#define		MAX_PWM_RMU_RIGHT			45		// Speed at RC RMU Right
#define		MAX_PWM_RMU_LEFT			46		// Speed at RC RMU Left
#define		MAX_PWM_RMD_RIGHT			47		// Speed at RC RMD Right
#define		MAX_PWM_RMD_LEFT			48		// Speed at RC RMD Left
#define		MAX_PWM_LMU_RIGHT 			49		// Speed at RC LMU Right
#define		MAX_PWM_LMU_LEFT			50		// Speed at RC LMU Left
#define		MAX_PWM_LMD_RIGHT			51		// Speed at RC LMD Right
#define		MAX_PWM_LMD_LEFT			52		// Speed at RC LMD Left
#define		DELAY_RMU_DOWN				53		// Delay at RC RMU (for going down)
#define		DELAY_RMU_UP				54		// Delay at RC RMU (for going up)
#define		DELAY_RMD_DOWN				55		// Delay at RC RMU (for going down)
#define		DELAY_RMD_UP				56		// Delay at RC RMU (for going up)
#define		DELAY_LMD_DOWN				57		// Delay at RC RMU (for going down)
#define		DELAY_LMD_UP				58		// Delay at RC RMU (for going up)
#define		DELAY_LMU_DOWN				59		// Delay at RC RMU (for going down)
#define		DELAY_LMU_UP				60		// Delay at RC RMU (for going up)
#define		TRAIN_PATH_FROM				61		// Train path origine
#define     TRAIN_PATH_TO  				62		// Train path destination
#define 	MAIN_PROGRAM				63		// Status of Main Program in Update_StateMchn
#define		JUNCTION_LEFT_STR			64		// Left junction Straight Coil
#define		JUNCTION_LEFT_BND			65		// Left junction Bend Coil
#define		JUNCTION_RIGHT_STR			66		// Right junction Straight Coil
#define		JUNCTION_RIGHT_BND			67		// Right junction Bend Coil
#define		ACTUAL_PWM_SPEED			68		// Actual PWM duty cycle set
#define		PWM_BRAKE					69		// Actual PWM H-Bridge Brake Input
#define     SW_START                    70      // Start command via SW after TRAIN1_POS and TRAIN2_POS are set
#define     SW_STOP                     71      // Stop command via SW
#define     SW_RESET                    72      // SW Reset to reset whole microcontroller
#define		SW_JUNCTION_LEFT_STR		73		// SW activation of Left junction Straight Coil
#define		SW_JUNCTION_LEFT_BND		74		// SW activation of Left junction Bend Coil
#define		SW_JUNCTION_RIGHT_STR		75		// SW activation of Right junction Straight Coil
#define		SW_JUNCTION_RIGHT_BND		76		// SW activation of Right junction Bend Coil
#define     SW_PWM_BRAKE_ON             77      // SW Brake activation
#define     SW_PWM_BRAKE_OFF            78      // SW Brake deactivation
#define     SW_ACTUAL_PWM_SPEED         79      // SW PWM control
                                        
#ifdef	__cplusplus
extern "C" {
#endif /* __cplusplus */

    // TODO If C++ is being used, regular C code needs function names to have C 
    // linkage so the functions can be used by the c code. 

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif	/* XC_HEADER_TEMPLATE_H */