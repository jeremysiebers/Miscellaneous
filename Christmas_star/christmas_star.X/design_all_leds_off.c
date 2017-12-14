#include "main.h"
#include "executer.h"
#include "design_all_leds_off.h"

void DESIGNxALLxLEDSxOFF(void);
void DESIGNxALLxLEDSxON(void);
void DESIGNxALLxLEDSxSLBLNK(void);

/******************************************************************************/
/*          DESIGN ALL LEDS OFF                                               */
/******************************************************************************/

void DESIGNxALLxLEDSxOFF(void)
{
    unsigned char x = 0;

    for(x=0;x<48;x++)
    {
        Led_Bit[x].Prog = 0;                                                    // Set led OFF
    }
}

/******************************************************************************/
/*          DESIGN ALL LEDS ON                                               */
/******************************************************************************/

void DESIGNxALLxLEDSxON(void)
{
    unsigned char x = 0;

    for(x=0;x<48;x++)
    {
        Led_Bit[x].Prog = 1;                                                    // Set Led ON
    }
}

/******************************************************************************/
/*          DESIGN ALL LEDS ON SLBLNK                                         */
/******************************************************************************/

void DESIGNxALLxLEDSxSLBLNK(void)
{
    unsigned char x = 0;

    for(x=0;x<48;x++)
    {
        Led_Bit[x].Prog = 2;                                                    // Set Led ON
        Led_Bit[x].Speed = 50;                                                  // set fixed speed
    }
}