/*
 * File:   vfd.c
 * Author: Jeremy Siebers
 *
 * Created on August 12, 2016, 2:28 PM
 */
#include "Peripherals/config.h"
#include "display.h"
#include <stdbool.h>
#include <limits.h>

#define DecelerationTime    20          // in seconds
#define EnableTime          5           // in seconds

unsigned int iSecondsCounter = 0;
unsigned int iSeconds = 0;
static unsigned int iSequencer = 0;
unsigned int iSecondSnapshot = 0;

void UPDATExVFDxSECONDS()
{
    iSecondsCounter++;
    if (iSecondsCounter >= 30){
        iSecondsCounter = 0;
        iSeconds++;                                                             // rolls over to 0 when int is full!            
    }
}

void INITxVFD()
{
    if (Mot_Temp > Max_Mot_Temp)// && Vfd_Fault_In == false)
    {
        Vfd_Fan_Ok_Out = false;
        HOUSExFANxERROR(MOTOR_TEMP_ERROR);
    }    
    else 
    { 
        Vfd_Fan_Ok_Out = true;
        HOUSExFANxERROR(NO_ERROR);
    }    
    HOUSExFANxPOWER(false);
    HOUSExFANxSTATUS(false);
}

void UPDATExVFD()
{
    switch (iSequencer)
    {
        case 0  :   if (bVfd_Enable_In == true && Mot_Temp < Max_Mot_Temp && Vfd_Fan_Ok_Out == true && Vfd_Fault_In == true)
                    {
                        iSequencer = 1;
                        HOUSExFANxERROR(NO_ERROR);
                    }
                    if (bVfd_Enable_In == false && Mot_Temp < Max_Mot_Temp && Vfd_Fan_Ok_Out == false && Vfd_Fault_In == true)
                    {
                        Vfd_Fan_Ok_Out = true;                                  // Reset function of error latch
                        HOUSExFANxERROR(NO_ERROR);
                    }
        
                    if (Mot_Temp > Max_Mot_Temp)
                    {
                        HOUSExFANxERROR(MOTOR_TEMP_ERROR);
                    }                    
            break;
                    
        case 1  :   Vfd_Supp_En_Out = true;
                    HOUSExFANxPOWER(true);
                    if (iSeconds > (UINT_MAX - EnableTime - 1))
                    {                            
                        iSeconds = 0;                                           // When a rollover is detected, force iSeconds to 0!
                    }                        
                    iSecondSnapshot = iSeconds + EnableTime;
                    iSequencer = 2;                    
            break;
            
        case 2  :   if (Mot_Temp > Max_Mot_Temp)                                // Check if after enabling 230VAC if all preconditions are still met
                    {
                        HOUSExFANxERROR(MOTOR_TEMP_ERROR);
                        Vfd_Fan_Ok_Out = false;   
                        Vfd_Supp_En_Out = false;
                        HOUSExFANxPOWER(false);
                        iSequencer = 0;
                    }
                    /*
                    else if (Vfd_Fault_In == true)
                    {
                        HOUSExFANxERROR(VFD_FAULT);
                        Vfd_Fan_Ok_Out = false; 
                        Vfd_Supp_En_Out = false;
                        HOUSExFANxPOWER(false);
                        iSequencer = 0;
                    }*/
                    else
                    {
                        iSequencer = 3;
                    }
            break;
            
        case 3  :   if(iSeconds >= iSecondSnapshot)
                    {
                        Vfd_Start_Out = true;
                        HOUSExFANxSTATUS(true);
                        iSequencer = 4;
                    }
            break;
            
        case 4  :   if (bVfd_Enable_In == false)
                    {                         
                        iSequencer = 5;
                    }
                    else if (Mot_Temp > Max_Mot_Temp)
                    {
                        HOUSExFANxERROR(MOTOR_TEMP_ERROR);
                        Vfd_Fan_Ok_Out = false;  
                        iSequencer = 5;
                    }
                    else if (Vfd_Fault_In == true)
                    {
                        HOUSExFANxERROR(VFD_FAULT);
                        Vfd_Fan_Ok_Out = false;
                        iSequencer = 5;                        
                    }                    
            break;
            
        case 5  :   Vfd_Start_Out = false;
                    HOUSExFANxSTATUS(false);
                    if (iSeconds > (UINT_MAX - DecelerationTime - 1))
                    {                            
                        iSeconds = 0;                                           // When a rollover is detected, force iSeconds to 0!
                    }                        
                    iSecondSnapshot = iSeconds + DecelerationTime;
                    iSequencer = 6;
            break;
            
        case 6  :   if(iSeconds >= iSecondSnapshot)
                    {
                        Vfd_Supp_En_Out = false;
                        HOUSExFANxPOWER(false);
                        iSequencer = 0;
                    }
            break;
            
        default : 
            break;
    }
}