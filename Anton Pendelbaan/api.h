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

#define APISIZE 63                                                              // Size of the API array
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
#define     API_SIZE                    0                                       // Size of the API stored here in location 0
#define     WATCHDOG                    1                                       // Variable in API will be written and read by master to verify communication on both sides
#define     TRAIN_WAIT_TIME             2                                       // Time to wait before departure/lightsoff
#define     JUNCTION_WAIT_TIME          3                                       // Junction switing delay time
#define     LIGHTS_ON_WAIT_TIME         4                                       // Lights on time before departure
#define     STATIONARY_LEFT             5                                       // Stationary PWM dutycycle for left drive
#define     STATIONARY_RIGHT            6                                       // Stationary PWM dutycycle for right drive
#define     MAX_PWM_RIGHT               7                                       // PWM right (dutycycle) speed setting
#define     MAX_PWM_LEFT                8                                       // PWM left (dutycycle) speed setting
#define     MAX_JERK_PWM_BRAKE          9                                       // braking speed (deceleration)
#define     MAX_JERK_PWM                10                                      // acceleration speed
#define     INPUT_DEBOUNCE              11                                      // input signal debouncing filter
#define		RC_RB						12										// Reed Contact Right Back
#define		RC_RF						13										// Reed Contact Right Front
#define		RC_LB						14										// Reed Contact Left Back
#define		RC_LF						15										// Reed Contact Left Front
#define		BTN_START					16										// Buttont Start
#define		BTN_STOP					17										// Buttont Stop
#define		BTN_MID  					18										// Buttont Middle
#define		BTN_LB 						19										// Buttont Left Back
#define		BTN_LF						20										// Buttont Left Front
#define		BTN_RB						21										// Buttont Right Back
#define		BTN_RF						22										// Buttont Right Front
#define 	TRAIN1_POS					23										// Train 1 Position
#define 	TRAIN2_POS					24										// Train 2 Position
#define		RC_LMU						25										// Reed Contact Left Mountain Up
#define		RC_LMD						26										// Reed Contact Left Mountain Down
#define		RC_RMU						27										// Reed Contact Right Mountain Up
#define		RC_RMD						28										// Reed Contact Right Mountain Down
#define		MAX_PWM_RMU_RIGHT			29										// Speed at RC RMU Right
#define		MAX_PWM_RMU_LEFT			30										// Speed at RC RMU Left
#define		MAX_PWM_RMD_RIGHT			31										// Speed at RC RMD Right
#define		MAX_PWM_RMD_LEFT			32										// Speed at RC RMD Left
#define		MAX_PWM_LMU_RIGHT 			33										// Speed at RC LMU Right
#define		MAX_PWM_LMU_LEFT			34										// Speed at RC LMU Left
#define		MAX_PWM_LMD_RIGHT			35										// Speed at RC LMD Right
#define		MAX_PWM_LMD_LEFT			36										// Speed at RC LMD Left
#define		DELAY_RMU_DOWN				37										// Delay at RC RMU (for going down)
#define		DELAY_RMU_UP				38										// Delay at RC RMU (for going up)
#define		DELAY_RMD_DOWN				39										// Delay at RC RMU (for going down)
#define		DELAY_RMD_UP				40										// Delay at RC RMU (for going up)
#define		DELAY_LMD_DOWN				41										// Delay at RC RMU (for going down)
#define		DELAY_LMD_UP				42										// Delay at RC RMU (for going up)
#define		DELAY_LMU_DOWN				43										// Delay at RC RMU (for going down)
#define		DELAY_LMU_UP				44										// Delay at RC RMU (for going up)


#ifdef	__cplusplus
extern "C" {
#endif /* __cplusplus */

    // TODO If C++ is being used, regular C code needs function names to have C 
    // linkage so the functions can be used by the c code. 

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif	/* XC_HEADER_TEMPLATE_H */