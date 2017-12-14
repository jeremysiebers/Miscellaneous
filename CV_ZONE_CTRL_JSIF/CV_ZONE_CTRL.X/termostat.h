#ifndef __termostat_H
#define __termostat_H

extern unsigned char TERMOSTATxACTUAL(unsigned char INDEX);			// Use this routine to readback the current status of a termostat
extern void  TERMOSTATxUPDATE(void);						// Update tick to update termostat statemachine

#endif