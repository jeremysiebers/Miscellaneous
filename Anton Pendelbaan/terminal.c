#include "terminal.h"
#include "eusart1.h"
#include <xc.h>
#include <string.h>
#include <stdio.h>

char            Received_Data  = 0;
unsigned char   RxSwitch       = 0;
unsigned char const   DataLen  = 10;
unsigned char   Data[DataLen];
unsigned char   *pData;

/******************************************************************************
 * Function:        void READxRECEIVEDxMESSAGE(void)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        None
 *****************************************************************************/
void READxRECEIVEDxMESSAGE(void){
    
    if (EUSART1_DataReady > 0){
        
        
        Received_Data = EUSART1_Read();
        
        switch (RxSwitch){
            case 0 : 
                pData = &Data[0];
                if (Received_Data == 's' || Received_Data == 'g'){
                    *pData = Received_Data;
                    *pData++;
                    RxSwitch = 1;  
                }
                else{
                   RxSwitch = 0;
                }                
                break;
            
            case 1 :
                if (Received_Data == 'x'){
                    *pData = Received_Data;
                    *pData++;
                    RxSwitch = 2;                    
                }
                else{
                   RxSwitch = 0;
                }
                break; 
                
            case 2 :
                if (Received_Data == 'G'){
                    *pData = Received_Data;
                    pData++;
                    *pData = '\0';
                    printf("\r\X0\r\n");
                    RxSwitch = 0;
                }
                else{
                    *pData = Received_Data;
                    pData++;
                    RxSwitch = 2;
                }
                break;
                
            default :
                break;
        }
    }
        
        
        
}

/******************************************************************************
 * Function:        SENDxMESSAGE(unsigned char index, unsigned int value)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          Sends a message to uart from the API[index].value
 *
 * Side Effects:    None
 *
 * Overview:        None
 *****************************************************************************/
void SENDxMESSAGE(unsigned char index, unsigned int value){
        
    unsigned char high = value >> 8;
    unsigned char low = value;
    
    printf("\r\nM#%x %x%x\r\n", index, high, low);
}