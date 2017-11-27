/*
 * File:   config.c
 * Author: Jeremy Siebers
 *
 * Created on Januari 20, 2011, 22:46 PM
 */

#include <xc.h>
#include "api.h"
#include "Main.h"
#include "terminal.h"
#include "io.h"

unsigned int API[APISIZE];                                                      // API RAM space
unsigned int API_EEPROM[APISIZE];                                               // EEPROM_API RAM space
unsigned int API_RW[APISIZE];                                                   // API Read/Write register, defines whether a location is writable and not read only (0 = read only)

/******************************************************************************
 * Function:        APIxInitialize
 *
 * PreCondition:    Execute once to init API
 *
 * Input:           None
 *
 * Output:          Sets Read only permissions for API[256] mem map
 *                  0 is readonly, 1 is writable
 *
 * Side Effects:    None
 *
 * Overview:        None
 *****************************************************************************/

void APIxInitialize(){
    
    unsigned int i;
    for(i = 0; i < (APISIZE); i++ )
    {
        API_RW[i] = 0;                                                          // Initialize RW_API with 0 to make sure all locations are Read Only at first
        API[i]    = 0;                                                          // Initialize API with 0 to make sure all locations are 0 at first
		API_EEPROM[i] = 0;                                                      // Initialize API_EEPROM with 0 to make sure all locations are 0 at first
    }
    
    /*  Set the RW directions */
    API_RW[API_SIZE]                =   RO;	      
	API_RW[TRAIN_WAIT_TIME]         =   RW;   
	API_RW[JUNCTION_WAIT_TIME]      =   RW;   
	API_RW[LIGHTS_ON_WAIT_TIME]     =   RW;   
	API_RW[STATIONARY_LEFT]         =   RW;   
	API_RW[STATIONARY_RIGHT]        =   RW;   
	API_RW[MAX_PWM_RIGHT]           =   RW;   
	API_RW[MAX_PWM_LEFT]            =   RW;   
	API_RW[MAX_JERK_PWM_BRAKE]      =   RW;   
	API_RW[MAX_JERK_PWM]            =   RW;   
	API_RW[INPUT_DEBOUNCE]          =   RW;   
	API_RW[RC_RB]					=   RO;
	API_RW[RC_RF]                   =   RO;
	API_RW[RC_LB]                   =   RO;
	API_RW[RC_LF]                   =   RO;
	API_RW[BTN_START]				=   RO;
	API_RW[BTN_STOP]                =   RO;
	API_RW[BTN_MID]                 =   RO;
	API_RW[BTN_LB] 	 	            =   RO;
	API_RW[BTN_LF]					=   RO;
	API_RW[BTN_RB]	                =   RO;
	API_RW[BTN_RF]	                =   RO;
	API_RW[TRAIN1_POS]              =   RW;
    API_RW[TRAIN2_POS]              =   RW;
	API_RW[RC_LMU]  				= 	RO;
	API_RW[RC_LMD]  				= 	RO;
	API_RW[RC_RMU]  				= 	RO;
	API_RW[RC_RMD]  				= 	RO;
	API_RW[MAX_PWM_RMU_RIGHT]		= 	RW;
	API_RW[MAX_PWM_RMU_LEFT]		= 	RW;
	API_RW[MAX_PWM_RMD_RIGHT]		= 	RW;
	API_RW[MAX_PWM_RMD_LEFT]		= 	RW;
	API_RW[MAX_PWM_LMU_RIGHT]		= 	RW;
	API_RW[MAX_PWM_LMU_LEFT]		= 	RW;
	API_RW[MAX_PWM_LMD_RIGHT]		= 	RW;
	API_RW[MAX_PWM_LMD_LEFT]		= 	RW;
	API_RW[DELAY_RMU_DOWN]			= 	RW;
	API_RW[DELAY_RMU_UP]			= 	RW;
	API_RW[DELAY_RMD_DOWN]			= 	RW;
	API_RW[DELAY_RMD_UP]			= 	RW;
	API_RW[DELAY_LMD_DOWN]			= 	RW;
	API_RW[DELAY_LMD_UP]			= 	RW;
	API_RW[DELAY_LMU_DOWN]			= 	RW;
	API_RW[DELAY_LMU_UP]			= 	RW;	
	API_RW[TRAIN_PATH_FROM]     	=	RO;
    API_RW[TRAIN_PATH_TO]       	=	RO;
	API_RW[MAIN_PROGRAM]			=	RO;
	API_RW[JUNCTION_LEFT_STR]  		=	RO;
	API_RW[JUNCTION_LEFT_BND]  		=	RO;
	API_RW[JUNCTION_RIGHT_STR] 		=	RO;
	API_RW[JUNCTION_RIGHT_BND] 		=	RO;
	API_RW[ACTUAL_PWM_SPEED]		=	RO;
	API_RW[PWM_BRAKE]				=	RO;
    API_RW[SW_START]                =   RW;
	API_RW[SW_STOP]                 =   RW;
    API_RW[SW_RESET]                =   RW;
	API_RW[SW_JUNCTION_LEFT_STR]    =   RW;
	API_RW[SW_JUNCTION_LEFT_BND]    =   RW;
	API_RW[SW_JUNCTION_RIGHT_STR]   =   RW;
	API_RW[SW_JUNCTION_RIGHT_BND]   =   RW;
	API_RW[SW_PWM_BRAKE_ON]         =   RW;
	API_RW[SW_PWM_BRAKE_OFF]        =   RW;
	API_RW[SW_ACTUAL_PWM_SPEED]     =   RW;
	API_RW[SWITCH_PROGRAM]          =   RO;
    API_RW[SW_PWM_DIRECTION]        =   RW;
	API_RW[JUNCTION_LEFT_STR_PREV] 	=   RO;
	API_RW[JUNCTION_LEFT_BND_PREV]	=   RO;
	API_RW[JUNCTION_RIGHT_STR_PREV]	=   RO;
	API_RW[JUNCTION_RIGHT_BND_PREV]	=   RO;
	API_RW[PWM_DIRECTION]			= 	RO;
	API_RW[SW_EEPROM_STORE]			=	RW;
    API_RW[HW_PWM_SPEED]            =   RO;
	
	
	/*  Set the API data */
    API[API_SIZE] = APISIZE;                                                    // Set the APISIZE on the API_SIZE location within API
	API[TRAIN_WAIT_TIME]            =   10000; 								
	API[JUNCTION_WAIT_TIME]         =   800;
	API[LIGHTS_ON_WAIT_TIME]        =   5000;
	API[STATIONARY_LEFT]            =   20;
	API[STATIONARY_RIGHT]           =   20;
	API[MAX_PWM_RIGHT]              =   107;
	API[MAX_PWM_LEFT]               =   107;
	API[MAX_JERK_PWM_BRAKE]         =   80;
	API[MAX_JERK_PWM]               =   45;
	API[INPUT_DEBOUNCE]             =   20;
	API[RC_RB]						=   Off;
	API[RC_RF]                      =   Off;
	API[RC_LB]                      =   Off;
	API[RC_LF]                      =   Off;
	API[BTN_START]					=   Off;
	API[BTN_STOP]	                =   Off;
	API[BTN_MID] 	                =   Off;
	API[BTN_LB] 	                =   Off;	
	API[BTN_LF]						=   Off;
	API[BTN_RB]		                =   Off;
	API[BTN_RF]		                =   Off;
	API[TRAIN1_POS]                 =   0;
    API[TRAIN2_POS]                 =   0;
	API[RC_LMU]						= 	Off;
	API[RC_LMD]						= 	Off;
	API[RC_RMU]						= 	Off;
	API[RC_RMD]			  			= 	Off;
	API[MAX_PWM_RMU_RIGHT]			= 	0;
	API[MAX_PWM_RMU_LEFT]			= 	80;
	API[MAX_PWM_RMD_RIGHT]			= 	120;
	API[MAX_PWM_RMD_LEFT]			= 	0;
	API[MAX_PWM_LMU_RIGHT]			= 	80;
	API[MAX_PWM_LMU_LEFT]			= 	0;
    API[MAX_PWM_LMD_RIGHT]			= 	0;
    API[MAX_PWM_LMD_LEFT]			= 	120;	
	API[DELAY_RMU_DOWN]				= 	100;
	API[DELAY_RMU_UP]				= 	100;
	API[DELAY_RMD_DOWN]				= 	100;
	API[DELAY_RMD_UP]				= 	100;
	API[DELAY_LMD_DOWN]				= 	100;
	API[DELAY_LMD_UP]				= 	100;
	API[DELAY_LMU_DOWN]				= 	100;
	API[DELAY_LMU_UP]				= 	100;	
	API[TRAIN_PATH_FROM]     		=	0;
	API[TRAIN_PATH_TO]       		=	0;
	API[MAIN_PROGRAM]				=	Init;
	API[JUNCTION_LEFT_STR]  		=	0;
	API[JUNCTION_LEFT_BND]  		=	0;
	API[JUNCTION_RIGHT_STR]  		=	0;
	API[JUNCTION_RIGHT_BND]  		=	0;
	API[ACTUAL_PWM_SPEED]			=	0;
	API[PWM_BRAKE]					=	On;
	API[SW_START]                   =   Off;
    API[SW_STOP]                    =   Off;
    API[SW_RESET]                   =   Off;
	API[SW_JUNCTION_LEFT_STR]       =   Off;
	API[SW_JUNCTION_LEFT_BND]       =   Off;
	API[SW_JUNCTION_RIGHT_STR]      =   Off;
	API[SW_JUNCTION_RIGHT_BND]      =   Off;
	API[SW_PWM_BRAKE_ON]            =   Off;     
	API[SW_PWM_BRAKE_OFF]           =   Off;     
	API[SW_ACTUAL_PWM_SPEED]        =   0; 
    API[SWITCH_PROGRAM]             =   0;
	API[SW_PWM_DIRECTION]           =   0;
	API[JUNCTION_LEFT_STR_PREV] 	=   1;
	API[JUNCTION_LEFT_BND_PREV]		=   0;
	API[JUNCTION_RIGHT_STR_PREV]	=   1;
	API[JUNCTION_RIGHT_BND_PREV]	=   0;
	API[PWM_DIRECTION]				= 	0;
	API[SW_EEPROM_STORE]			=	0;
    API[HW_PWM_SPEED]               =   511;
}

/******************************************************************************
 * Function:        unsigned char API_RW(unsigned int index)
 *
 * PreCondition:    None
 *
 * Input:           Index number to get RW/RO status
 *
 * Output:          returns RW/RO status on index position in API[]
 *
 * Side Effects:    None
 *
 * Overview:        None
 *****************************************************************************/

unsigned int GETxAPIxRW(unsigned int index){
	return API_RW[index];
}

void SETxAPIxVAL(unsigned int index, unsigned int value){
    if(API[index] != value){
        API[index] = value;
        SENDxMESSAGE(index, value);
    }    
}

void SETxAPIxVALxNoxRET(unsigned int index, unsigned int value){
    if(API[index] != value){
        API[index] = value;        
    }   
}

unsigned int GETxAPIxVAL(unsigned int index){
    return API[index];
}

void INCRxAPIxVAL(unsigned int index){
    unsigned int value;
    value = GETxAPIxVAL(index);
    value++;
    SETxAPIxVAL(index, value);
    SENDxMESSAGE(index, value);
}

void DECRxAPIxVAL(unsigned int index){
    unsigned int value;
    value = GETxAPIxVAL(index);
    value--;
    SETxAPIxVAL(index, value);
    SENDxMESSAGE(index, value);
}