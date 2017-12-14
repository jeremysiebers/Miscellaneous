#ifndef __valve_H
#define __valve_H

extern void VALVExCMD(unsigned char VALVE, unsigned char COMMAND);		// Use this routine to set a valve's output to ON or OFF
extern unsigned char VALVExSTAT(unsigned char INDEX);				// Use this routine to readback the current status of a valve
extern void  VALVExUPDATE(void);						// Update tick to update valve statemachine

#endif