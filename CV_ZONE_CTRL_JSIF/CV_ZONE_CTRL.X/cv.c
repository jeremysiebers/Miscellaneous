#include "cv.h"
#include "main.h"

unsigned char CVxSTAT(unsigned char STATUS)
{
    return cv_o; 								// Return to the application the current cv_o output value}
}

void  CVxCMD(unsigned char COMMAND)
{	
    cv_o = COMMAND;								// Set the cv_o output to the commanded value of the application
}