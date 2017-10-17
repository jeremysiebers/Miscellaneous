#include "terminal.h"
#include "eusart1.h"
#include <xc.h>
#include <string.h>
#include <stdio.h>

#define Height 40
#define Width 22

//static bank1 unsigned char Matrix[Height][Width];

//http://www.termsys.demon.co.uk/vtansi.htm



void SENDxMESSAGE(unsigned char index, unsigned int value){
        
    unsigned char high = value >> 8;
    unsigned char low = value;
    
    printf("\r\nM#%x %x%x\r\n", index, high, low);  
}