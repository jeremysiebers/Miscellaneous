#include <xc.h>
#include "xlcd.h"
/********************************************************************
*       Function Name:  ClearDisplay
*       Return Value:   void
*       Parameters:     none
*       Description:    This routine writes a Clear Display to the
*                       Hitachi HD44780 LCD controller. The user
*                       must check to see if the LCD controller is
*                       busy before calling this routine.
*						In case of NO_RW, give the LCD 3ms time to 
*						clear
********************************************************************/
void ClearDisplay()
{
        WriteCmdXLCD(0x01);             // Clear display
}

