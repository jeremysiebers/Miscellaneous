#include "terminal.h"
#include "eusart1.h"
#include <xc.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "api.h"
#include "io.h"

char                Received_Data           = 0;
unsigned char       RxSwitch                = 0;
unsigned char const DataLen                 = 10;
unsigned char       Data[DataLen];
unsigned char       *pData, *pLen;
unsigned char       Message_To_Translate    = 0;
unsigned char       TrSwitch                = 0;


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
                pLen  = &Data[DataLen - 1];
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
                    //*pData = Received_Data;
                    //pData++;
                    while(pLen > pData){
                       *pData = '\0';
                       pData++;
                    }
                    printf("\r\nX0\r\n");
                    RxSwitch = 3;
                    Message_To_Translate = 1;
                }
                else{
                    *pData = Received_Data;
                    if (pData > pLen){
                        printf("\r\nE#10\r\n");
                        RxSwitch = 0;
                    }
                    else{
                        pData++;
                        RxSwitch = 2;
                    }
                }
                break;
                
            case 3 :                                
                break;
                
            default :
                break;
        }
    }
    
    if (Message_To_Translate == 1){
        TranslateMessage();
        Message_To_Translate = 0;
        RxSwitch = 0;
    }
}

/******************************************************************************
 * Function:        void TranslateMessage(void)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          Checks if a g(GET) or s(SET) is received and act 
 *                  accordingly
 *
 * Side Effects:    None
 *
 * Overview:        None
 *****************************************************************************/
void TranslateMessage(void){
    
    unsigned int Value, Index;
    
    if(Data[0] == 's'){
      
        pData = &Data[2];
        Index = atoi (pData);
        pData = &Data[5];
        Value = atoi (pData);
        
        if (GETxAPIxRW(Index) == RO){
            printf("\r\nE#11\r\n");
        }
        else if (Index < 0xF){
            printf("\r\nE#12\r\n");
        }
        else if (Index > APISIZE){
            printf("\r\nE#13\r\n");
        }
        else if (Value > 0xFFFE){
            printf("\r\nE#14\r\n");
        }
        else{
            SETxAPIxVAL(Index, Value);
        }
    }
    
    else if (Data[0] == 'g'){                                                   // A get from API can only contain up to 0xFF
         
        pData = &Data[2];   
        Index = atoi (pData);
        
        if (Index < 0xF){
            printf("\r\nE#12\r\n");
        }
        else if (Index > APISIZE){
            printf("\r\nE#13\r\n");
        }
        else{
            Value = GETxAPIxVAL(Index);        
            SENDxMESSAGE(Index, Value);    
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
        
    //unsigned char high = value >> 8;
    //unsigned char low = value;
    
    //printf("\r\nM#%d %d%d\r\n", index, high, low);
    printf("\r\nM#%d %d\r\n", index, value);
}