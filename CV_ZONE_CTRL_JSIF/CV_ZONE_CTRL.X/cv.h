#ifndef __cv_H
#define __cv_H

extern unsigned char CVxSTAT(unsigned char STATUS);				// Use this routine to readback the current status of a termostat
extern void  CVxCMD(unsigned char COMMAND);					// Use this routine to set the cv_o output


#endif