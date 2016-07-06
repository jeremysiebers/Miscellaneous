#ifndef CONFIG_H
#define	CONFIG_H

#include <xc.h>
/*
#include "uart1.h"
#include "pwm.h"
*/

#define Led1    RB5   

#ifdef	__cplusplus
extern "C" {
#endif /* __cplusplus */

void SYSTEM_Initialize(void);
void OSCILLATOR_Initialize(void);
void IO_Configuration(void);
void Timer1_Configuration(void);
void Interrupt_Configuration(void);

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif	/* CONFIG_H */

