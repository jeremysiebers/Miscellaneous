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

unsigned int   		Diag_Comm=0,				// Switch for read in to be sended command
					Comm_List[8][2],			//	Command buffer array
					*Pcomm_List,				//	Pointer to array command buffer
					*Pcomm_List2,				//	Pointer 2 to array command buffer to write out 
					Diag_Comm2=0,				// Switch for write command
                    DelayCounter = 0;           // Determines sent speed


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
                    //printf("X0\r\n");
                    RxSwitch = 3;
                    Message_To_Translate = 1;
                }
                else{
                    *pData = Received_Data;
                    if (pData > pLen){
                        printf("E#10\r\n");
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
        Index = (unsigned int)atoi (pData);
        pData = &Data[5];
        Value = (unsigned int)atoi (pData);
        
        if (GETxAPIxRW(Index) == RO){
            printf("E#11\r\n");
        }
        else if (Index < 0xF){
            printf("E#12\r\n");
        }
        else if (Index > APISIZE){
            printf("E#13\r\n");
        }
        else if (Value > 0xFFFE){
            printf("E#14\r\n");
        }
        else{
            SETxAPIxVALxNoxRET(Index, Value);
        }
    }
    
    else if (Data[0] == 'g'){                                                   // A get from API can only contain up to 0xFF
         
        pData = &Data[2];   
        Index = (unsigned int)atoi (pData);
        
        if (Index < 0xF){
            printf("E#12\r\n");
        }
        else if (Index > APISIZE){
            printf("E#13\r\n");
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
void SendMessage(unsigned char index, unsigned int value){
        
    //unsigned char high = value >> 8;
    //unsigned char low = value;
    
    //printf("M#%d %d%d\r\n", index, high, low);
    printf("M#%d %d\r\n", index, value);
}

void DIAGNOSTICxTOxPC(void)
{
    if (DelayCounter > 10000){
		DelayCounter = 0;
        
		switch (Diag_Comm2)
		{
			case	0	:	Pcomm_List = &Comm_List[0][0];			//Init pointers 1 time
							Pcomm_List2 = &Comm_List[0][0];
							Diag_Comm2 = 1;
							break;
							
			case	1	:	Pcomm_List2 = &Comm_List[0][0];
							if (Pcomm_List2 != Pcomm_List)
							{
								SendMessage(Comm_List[0][0], Comm_List[0][1]);	
								Pcomm_List2+=2;
								Diag_Comm2 = 2;
							}
							break;
							
			case	2	:	if (Pcomm_List2 != Pcomm_List)
							{
								SendMessage(Comm_List[1][0], Comm_List[1][1]);	
								Pcomm_List2+=2;
								Diag_Comm2 = 3;
							}
							break;
							
			case	3	:	if (Pcomm_List2 != Pcomm_List)
							{
								SendMessage(Comm_List[2][0], Comm_List[2][1]);	
								Pcomm_List2+=2;
								Diag_Comm2 = 4;							
							}
							break;
			
			case	4	:	if (Pcomm_List2 != Pcomm_List)
							{
								SendMessage(Comm_List[3][0], Comm_List[3][1]);
								Pcomm_List2+=2;
								Diag_Comm2 = 5;
							}
							break;
							
			case	5	:	if (Pcomm_List2 != Pcomm_List)
							{
								SendMessage(Comm_List[4][0], Comm_List[4][1]);	
								Pcomm_List2+=2;
								Diag_Comm2 = 6;
							}
							break;
							
			case	6	:	if (Pcomm_List2 != Pcomm_List)
							{
								SendMessage(Comm_List[5][0], Comm_List[5][1]);
								Pcomm_List2+=2;							
								Diag_Comm2 = 7;
							}
							break;
							
			case	7	:	if (Pcomm_List2 != Pcomm_List)
							{
								SendMessage(Comm_List[6][0], Comm_List[6][1]);	
								Pcomm_List2+=2;
								Diag_Comm2 = 8;
							}
							break;
							
							
			case	8	:	if (Pcomm_List2 != Pcomm_List)
							{
								SendMessage(Comm_List[7][0], Comm_List[7][1]);
								Pcomm_List2 = &Comm_List[0][0];	// point to Comm_List[0]
								Diag_Comm2 = 1;
							}
							break; 
							
			default		:	break;
		}
    }
	else{
		DelayCounter++;
	}
}

void SENDxMESSAGE(unsigned char index, unsigned int value)
{
	switch (Diag_Comm)
	{
		case	0	:	Pcomm_List = &Comm_List[0][0];	// point to Comm_List[0]
						*Pcomm_List = index;
						Pcomm_List++;
						*Pcomm_List = value;
						Pcomm_List++;						
						Diag_Comm = 1;
						break;
						
		case	1	:	*Pcomm_List = index;
						Pcomm_List++;
						*Pcomm_List = value;
						Pcomm_List++;	
						Diag_Comm = 2;
						break;
						
		case	2	:	*Pcomm_List = index;
						Pcomm_List++;
						*Pcomm_List = value;
						Pcomm_List++;	
						Diag_Comm = 3;
						break;
						
		case	3	:	*Pcomm_List = index;
						Pcomm_List++;
						*Pcomm_List = value;
						Pcomm_List++;	
						Diag_Comm = 4;
						break;
		
		case	4	:	*Pcomm_List = index;
						Pcomm_List++;
						*Pcomm_List = value;
						Pcomm_List++;	
						Diag_Comm = 5;
						break;
		
		case	5	:	*Pcomm_List = index;
						Pcomm_List++;
						*Pcomm_List = value;
						Pcomm_List++;	
						Diag_Comm = 6;
						break;
		
		case	6	:	*Pcomm_List = index;
						Pcomm_List++;
						*Pcomm_List = value;
						Pcomm_List++;	
						Diag_Comm = 7;
						break;
		
		case	7	:	*Pcomm_List = index;
						Pcomm_List++;
						*Pcomm_List = value;
						Pcomm_List++;												
						Pcomm_List = &Comm_List[0][0];	// point to Comm_List[0]
						Diag_Comm = 0;
						break;
		
						
		default		:	break;
	}
				
}