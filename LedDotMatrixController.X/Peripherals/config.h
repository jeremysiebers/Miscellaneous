#ifndef CONFIG_H
#define	CONFIG_H

#include <xc.h>
#include <stdbool.h>

#define _XTAL_FREQ          20000000

#define Led1                RA2
#define Select              RB5
#define Latch               RC0
#define Clock               RC3
#define Data                RC5


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

