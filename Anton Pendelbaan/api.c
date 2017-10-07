/*
 * File:   config.c
 * Author: Jeremy Siebers
 *
 * Created on Januari 20, 2011, 22:46 PM
 */

#include <xc.h>
#include "api.h"
#include "Main.h"

unsigned int API[APISIZE];                                                      // API RAM space
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
    for(i = 0; i < (APISIZE + 1); i++ )
    {
        API_RW[i] = 0;                                                          // Initialize RW_API with 0 to make sure all locations are Read Only at first
        API[i]    = 0;                                                          // Initialize API with 0 to make sure all locations are 0 at first
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
	
    
	/*  Set the API data */
    API[API_SIZE] = APISIZE;                                                    // Set the APISIZE on the API_SIZE location within API
	API[TRAIN_WAIT_TIME]            =   10000; 								
	API[JUNCTION_WAIT_TIME]         =   800;
	API[LIGHTS_ON_WAIT_TIME]        =   5000;
	API[STATIONARY_LEFT]            =   460;
	API[STATIONARY_RIGHT]           =   550;
	API[MAX_PWM_RIGHT]              =   725;
	API[MAX_PWM_LEFT]               =   307;
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
	API[TRAIN1_POS]                 =   9;
    API[TRAIN2_POS]                 =   9;
	API[RC_LMU]						= 	Off;
	API[RC_LMD]						= 	Off;
	API[RC_RMU]						= 	Off;
	API[RC_RMD]			  			= 	Off;
	API[MAX_PWM_RMU_RIGHT]			= 	725;
	API[MAX_PWM_RMU_LEFT]			= 	307;
	API[MAX_PWM_RMD_RIGHT]			= 	725;
	API[MAX_PWM_RMD_LEFT]			= 	307;
	API[MAX_PWM_LMU_RIGHT]			= 	725;
	API[MAX_PWM_LMU_LEFT]			= 	307;
    API[MAX_PWM_LMD_RIGHT]			= 	725;
    API[MAX_PWM_LMD_LEFT]			= 	307;	
	API[DELAY_RMU_DOWN]				= 	100;
	API[DELAY_RMU_UP]				= 	100;
	API[DELAY_RMD_DOWN]				= 	100;
	API[DELAY_RMD_UP]				= 	100;
	API[DELAY_LMD_DOWN]				= 	100;
	API[DELAY_LMD_UP]				= 	100;
	API[DELAY_LMU_DOWN]				= 	100;
	API[DELAY_LMU_UP]				= 	100;
	
	
}

/******************************************************************************
 * Function:        unsigned char API_RW(unsigned char index)
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

unsigned int GETxAPIxRW(unsigned char index){
	return API_RW[index];
}

void SETxAPIxVAL(unsigned char index, unsigned int value){
    API[index] = value;
}
unsigned int GETxAPIxVAL(unsigned char index){
    return API[index];
}

void INCRxAPIxVAL(unsigned char index){
    unsigned int value;
    value = GETxAPIxVAL(index);
    value++;
    SETxAPIxVAL(index, value);
}

void DECRxAPIxVAL(unsigned char index){
    unsigned int value;
    value = GETxAPIxVAL(index);
    value--;
    SETxAPIxVAL(index, value);
}