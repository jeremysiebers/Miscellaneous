#include "terminal.h"
#include "eusart1.h"
#include <xc.h>

#define Height 40
#define Width 22

//static bank1 unsigned char Matrix[Height][Width];

//http://www.termsys.demon.co.uk/vtansi.htm

void INIT_TERMINAL(){
    int i = 0;
    for (i=0; i<Width; i++){
        
    }
}



void UPDATExTERMINAL(){
    EUSART1_Write('A');
}