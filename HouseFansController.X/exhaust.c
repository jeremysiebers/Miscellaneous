/*
 * File:   exhaust.c
 * Author: Jeremy Siebers
 *
 * Created on August 15, 2016, 9:43 AM
 */

#include "exhaust.h"
#include "Peripherals/config.h"
#include <stdbool.h>
#include "display.h"

#define SET                     50

const unsigned int IDLE     =   0;
const unsigned int MID      =   1;
const unsigned int HIGH     =   2;

static unsigned int iSequencer = 0;

void INITxEXHAUST()
{
    if (Fgs_Q1_Mid_In == true)
    {
        BATHROOMxFANxMODE(MID);
        iSequencer = MID;
    }
    else if (Fgs_Q2_High_In == true)
    {
        BATHROOMxFANxMODE(HIGH);
        iSequencer = HIGH;
    }
    else 
    { 
        BATHROOMxFANxMODE(IDLE);
        iSequencer = IDLE; 
    }
}

void UPDATExEXHAUST()
{
    switch (iSequencer)
    {
        case 0  :   if (bBathroom_Sw_In_Lat == true)
                    {                        
                        SETxEXHAUSTxSPEED(HIGH);
                        BATHROOMxFANxMODE(HIGH);
                        bBathroom_Sw_In_Lat = false;
                        iSequencer = HIGH;
                    }
                    else if (bKitchen_Sw_In_Lat == true)
                    {
                        SETxEXHAUSTxSPEED(HIGH);
                        BATHROOMxFANxMODE(HIGH);
                        bKitchen_Sw_In_Lat = false;                        
                        iSequencer = HIGH;
                    }
                    else if (Fgs_Q1_Mid_In == true)
                    {
                        BATHROOMxFANxMODE(MID);
                        iSequencer = MID;
                    }
                    else if (Fgs_Q2_High_In == true)
                    {
                        BATHROOMxFANxMODE(HIGH);
                        iSequencer = HIGH;
                    }
            break;
            
        case 1  :   if (bBathroom_Sw_In_Lat == true)
                    {                        
                        SETxEXHAUSTxSPEED(HIGH);
                        BATHROOMxFANxMODE(HIGH);
                        bBathroom_Sw_In_Lat = false;
                        iSequencer = HIGH;
                    }
                    else if (bKitchen_Sw_In_Lat == true)
                    {
                        SETxEXHAUSTxSPEED(HIGH);
                        BATHROOMxFANxMODE(HIGH);
                        bKitchen_Sw_In_Lat = false;
                        iSequencer = HIGH;
                    }
                    
                    if (Fgs_Q2_High_In == true)                                 // When during MID, a HIGH is set via domoticz, set the High output causing the MID to be reset
                    {
                        SETxEXHAUSTxSPEED(HIGH);
                        BATHROOMxFANxMODE(HIGH);
                        iSequencer = HIGH;
                    }
                    else if (Fgs_Q1_Mid_In == false && Fgs_Q2_High_In == false) // When time specified by domoticz has expired, reset iSequencer to idle speed
                    {
                        BATHROOMxFANxMODE(IDLE);
                        iSequencer = IDLE;
                    }
            break;
            
        case 2  :   if (bBathroom_Sw_In_Lat == true)
                    {
                        SETxEXHAUSTxSPEED(MID);
                        BATHROOMxFANxMODE(MID);
                        bBathroom_Sw_In_Lat = false;
                        iSequencer = MID;
                    }
                    else if (bKitchen_Sw_In_Lat == true)
                    {
                        SETxEXHAUSTxSPEED(MID);
                        BATHROOMxFANxMODE(MID);
                        bKitchen_Sw_In_Lat = false;
                        iSequencer = MID;
                    }
        
                    if (Fgs_Q1_Mid_In == true)                                  // When during HIGH, a MID is set via domoticz, set the MID output causing the HIGH to be reset
                    {
                        SETxEXHAUSTxSPEED(MID);
                        BATHROOMxFANxMODE(MID);
                        iSequencer = MID;
                    }                    
                    else if (Fgs_Q1_Mid_In == false && Fgs_Q2_High_In == false) // When time specified by domoticz has expired, reset iSequencer to idle speed
                    {
                        BATHROOMxFANxMODE(IDLE);
                        iSequencer = IDLE;
                    }
            break;            
        
        default :   
            break;
    }
}

void SETxEXHAUSTxSPEED(unsigned int iSpeed)
{
    switch (iSpeed)
    {
        case 0  :   if (Fgs_Q1_Mid_In == true)                                  // if MID was running before setting IDLE(0) reset MID output(Q1) of FGS222
                    {
                        Douche_Fan_Mid_Out = true;
                        __delay_ms(SET);
                        Douche_Fan_Mid_Out = false;
                    }
                    if (Fgs_Q2_High_In == true)                                 // if HIGH was running before setting IDLE(0) reset HIGH output(Q2) of FGS222
                    {
                        Douche_Fan_High_Out = true;
                        __delay_ms(SET);
                        Douche_Fan_High_Out = false;
                    }
                    __delay_ms(SET);
            break;
            
        case 1  :   if (Fgs_Q2_High_In == true)                                 // if HIGH was running before setting MID(1) reset HIGH output(Q2) of FGS222
                    {
                        Douche_Fan_High_Out = true;
                        __delay_ms(SET);
                        Douche_Fan_High_Out = false;
                    }
                    if (Fgs_Q1_Mid_In == false)                                 // if MID is not already running, set MID speed
                    {
                        Douche_Fan_Mid_Out = true;
                        __delay_ms(SET);
                        Douche_Fan_Mid_Out = false;
                    }
                    __delay_ms(SET);
            break;
        
        case 2  :   if (Fgs_Q1_Mid_In == true)                                  // if MID is running, reset MID speed
                    {
                        Douche_Fan_Mid_Out = true;
                        __delay_ms(SET);
                        Douche_Fan_Mid_Out = false;
                    }
                    if (Fgs_Q2_High_In == false)                                // if HIGH is not running set HIGH output(Q2) of FGS222
                    {
                        Douche_Fan_High_Out = true;
                        __delay_ms(SET);
                        Douche_Fan_High_Out = false;
                    }
                    __delay_ms(SET);
            break;
            
        default :
            break;
    }
    
    
    
    
    /*
    switch (iSequencer)
    {
        case 0  :   if (Fgs_Q1_Mid_In == true)
                    {
                        
                    }
                    else if (Fgs_Q2_High_In == true)
                    {
                        
                    }
            break;
        
        default :
            break;
    }*/
}