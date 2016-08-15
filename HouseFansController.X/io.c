/*
 * File:   io.c
 * Author: Jeremy Siebers
 *
 * Created on August 12, 2016, 2:28 PM
 */
#include "Peripherals/config.h"
#include <stdbool.h>

#define Debounce 0

unsigned int iVfd_Fault_In_Counter = 0;
unsigned int iBathroom_Sw_In_Counter = 0;
unsigned int iVfd_Enable_In_Counter = 0;

void INITxIOxVAR()
{
    bVfd_Fault_In = false;
    
    bBathroom_Sw_In = false;    
    bBathroom_Sw_In_Lat = false;
    
    bKitchen_Sw_In = false;    
    bKitchen_Sw_In_Lat = false;
    
    bVfd_Enable_In = false;
}

void READxIO()
{   
    switch (Vfd_Fault_In)
    {
        case 0  :   iVfd_Fault_In_Counter = 0;
                    bVfd_Fault_In = false;
                    break;
                    
        case 1  :   if(iVfd_Fault_In_Counter <= Debounce)
                    {
                        iVfd_Fault_In_Counter++;
                    }
                    else {
                        bVfd_Fault_In = true;
                    }
                    
        default :   break;
    }
    
    switch (Bathroom_Sw_In)
    {
        case 0  :   if (bBathroom_Sw_In == true)
                    {
                        bBathroom_Sw_In_Lat = true;
                    }
                    iBathroom_Sw_In_Counter = 0;
                    bBathroom_Sw_In = false;
                    break;
                    
        case 1  :   if(iBathroom_Sw_In_Counter <= Debounce)
                    {
                        iBathroom_Sw_In_Counter++;
                    }
                    else {
                        bBathroom_Sw_In = true;
                    }
                    
        default :   break;
    }
    
    switch (bKitchen_Sw_In)
    {
        case false  :   if (Kitchen_Sw_In != bKitchen_Sw_In)
                        {
                            bKitchen_Sw_In = true;
                            bKitchen_Sw_In_Lat = true;
                        }                        
                    break;
                    
        case true  :    if (Kitchen_Sw_In != bKitchen_Sw_In)
                        {
                            bKitchen_Sw_In = false;
                            bKitchen_Sw_In_Lat = true;
                        }                              
                    break;
                        
        default :   break;
    }
 
    switch (Vfd_Enable_In)
    {
        case 0  :   iVfd_Enable_In_Counter = 0;
                    bVfd_Enable_In = false;
                    break;
                    
        case 1  :   if(iVfd_Enable_In_Counter <= Debounce)
                    {
                        iVfd_Enable_In_Counter++;
                    }
                    else {
                        bVfd_Enable_In = true;
                    }
                    
        default :   break;
    }           
}