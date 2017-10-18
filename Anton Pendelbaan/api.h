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

#define APISIZE 0xFF                            // Size of the API array
#define RO	0
#define RW	1

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
#define     API_SIZE                    0x10   	// Size of the API stored here in location 0
#define     WATCHDOG                    0x11   	// Variable in API will be written and read by master to verify communication on both sides
#define     TRAIN_WAIT_TIME             0x12   	// Time to wait before departure/lightsoff
#define     JUNCTION_WAIT_TIME          0x13   	// Junction switing delay time
#define     LIGHTS_ON_WAIT_TIME         0x14   	// Lights on time before departure
#define     STATIONARY_LEFT             0x15   	// Stationary PWM dutycycle for left drive
#define     STATIONARY_RIGHT            0x16   	// Stationary PWM dutycycle for right drive
#define     MAX_PWM_RIGHT               0x17   	// PWM right (dutycycle) speed setting
#define     MAX_PWM_LEFT                0x18   	// PWM left (dutycycle) speed setting
#define     MAX_JERK_PWM_BRAKE          0x19   	// braking speed (deceleration)
#define     MAX_JERK_PWM                0x1A  	// acceleration speed
#define     INPUT_DEBOUNCE              0x1B  	// input signal debouncing filter
#define		RC_RB						0x1C	// Reed Contact Right Back
#define		RC_RF						0x1D	// Reed Contact Right Front
#define		RC_LB						0x1E	// Reed Contact Left Back
#define		RC_LF						0x1F	// Reed Contact Left Front
#define		BTN_START					0x20	// Buttont Start
#define		BTN_STOP					0x21	// Buttont Stop
#define		BTN_MID  					0x22	// Buttont Middle
#define		BTN_LB 						0x23	// Buttont Left Back
#define		BTN_LF						0x24	// Buttont Left Front
#define		BTN_RB						0x25	// Buttont Right Back
#define		BTN_RF						0x26	// Buttont Right Front
#define 	TRAIN1_POS					0x27	// Train 1 Position
#define 	TRAIN2_POS					0x28	// Train 2 Position
#define		RC_LMU						0x29	// Reed Contact Left Mountain Up
#define		RC_LMD						0x2A	// Reed Contact Left Mountain Down
#define		RC_RMU						0x2B	// Reed Contact Right Mountain Up
#define		RC_RMD						0x2C	// Reed Contact Right Mountain Down
#define		MAX_PWM_RMU_RIGHT			0x2D	// Speed at RC RMU Right
#define		MAX_PWM_RMU_LEFT			0x2E	// Speed at RC RMU Left
#define		MAX_PWM_RMD_RIGHT			0x2F	// Speed at RC RMD Right
#define		MAX_PWM_RMD_LEFT			0x30	// Speed at RC RMD Left
#define		MAX_PWM_LMU_RIGHT 			0x31	// Speed at RC LMU Right
#define		MAX_PWM_LMU_LEFT			0x32	// Speed at RC LMU Left
#define		MAX_PWM_LMD_RIGHT			0x33	// Speed at RC LMD Right
#define		MAX_PWM_LMD_LEFT			0x34	// Speed at RC LMD Left
#define		DELAY_RMU_DOWN				0x35	// Delay at RC RMU (for going down)
#define		DELAY_RMU_UP				0x36	// Delay at RC RMU (for going up)
#define		DELAY_RMD_DOWN				0x37	// Delay at RC RMU (for going down)
#define		DELAY_RMD_UP				0x38	// Delay at RC RMU (for going up)
#define		DELAY_LMD_DOWN				0x39	// Delay at RC RMU (for going down)
#define		DELAY_LMD_UP				0x3A	// Delay at RC RMU (for going up)
#define		DELAY_LMU_DOWN				0x3B	// Delay at RC RMU (for going down)
#define		DELAY_LMU_UP				0x3C	// Delay at RC RMU (for going up)
#define		TRAIN_PATH_FROM				0x3D	// Train path origine
#define     TRAIN_PATH_TO  				0x3E	// Train path destination
#define 	MAIN_PROGRAM				0x3F	// Status of Main Program in Update_StateMchn
#define		JUNCTION_LEFT_STR			0x40	// Left junction Straight
#define		JUNCTION_LEFT_BND			0x41	// Left junction Bend
#define		JUNCTION_RIGHT_STR			0x42	// Right junction Straight
#define		JUNCTION_RIGHT_BND			0x43	// Right junction Bend
#define		ACTUAL_PWM_SPEED			0x44	// Actual PWM duty cycle set
#define		PWM_BRAKE					0x45	// Actual PWM H-Bridge Brake Input 
                                        
#ifdef	__cplusplus
extern "C" {
#endif /* __cplusplus */

    // TODO If C++ is being used, regular C code needs function names to have C 
    // linkage so the functions can be used by the c code. 

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif	/* XC_HEADER_TEMPLATE_H */