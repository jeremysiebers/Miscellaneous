#ifndef CONFIG_H
#define	CONFIG_H

#include <xc.h>
#include <stdbool.h>

/* check if build is for a real debug tool */
#if defined(__DEBUG) && !defined(__MPLAB_ICD2_) && !defined(__MPLAB_ICD3_) && \
   !defined(__MPLAB_PICKIT2__) && !defined(__MPLAB_PICKIT3__) && \
   !defined(__MPLAB_REALICE__) && \
   !defined(__MPLAB_DEBUGGER_REAL_ICE) && \
   !defined(__MPLAB_DEBUGGER_ICD3) && \
   !defined(__MPLAB_DEBUGGER_PK3) && \
   !defined(__MPLAB_DEBUGGER_PICKIT2) && \
   !defined(__MPLAB_DEBUGGER_PIC32MXSK)
    #warning Debug with broken MPLAB simulator
    #define USING_SIMULATOR
#endif

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

