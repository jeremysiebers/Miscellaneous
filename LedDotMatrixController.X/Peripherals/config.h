#ifndef CONFIG_H
#define	CONFIG_H

#include <xc.h>
#include <stdbool.h>

#define _XTAL_FREQ          8000000

#define Led1                RB5
#define Select              RB0
#define Latch               RC2


#ifdef	__cplusplus
extern "C" {
#endif /* __cplusplus */

void SYSTEM_Initialize(void);
void OSCILLATOR_Initialize(void);
void IO_Configuration(void);
void Timer1_Configuration(void);
void Interrupt_Configuration(void);
void Adconverter_Configuration(void);
void MSSP_Configuration(void);

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif	/* CONFIG_H */

