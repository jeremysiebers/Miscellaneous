#ifndef CONFIG_H
#define	CONFIG_H

#include <xc.h>
#include <stdbool.h>

#define _XTAL_FREQ          8000000
#define Max_Mot_Temp        60          // Max temp seen with surrounding temp of 30 degrees --> 48 degrees celsius mot temp
#define NO_ERROR            0
#define MOTOR_TEMP_ERROR    1
#define VFD_FAULT           2

#define SOFTWARE_VERSION "SW version 1.1"

unsigned int iSeconds;      // Seconds timer, can be read by sub programs to count down without using delay rotines

/*
 *      Mot_Temp            RA0
 *      Temp_Spare          RA1
*/
#define Vfd_Fault_In        !RA2    // Inverted, after power ON, relay is switched internally in vfd
#define Bathroom_Sw_In      RA3
#define Kitchen_Sw_In       RA4
#define Vfd_Enable_In       !RA5    // Inverted input (switched to ground by RGBW controller)
#define Vfd_Fan_Ok_Out      RA6     // true (1) is safe
#define Vfd_Supp_En_Out     RA7

unsigned int Mot_Temp;      // Motor temperature readout
bool bVfd_Fault_In;         // Debounced input in boolean
bool bBathroom_Sw_In;       // Debounced input in boolean
bool bKitchen_Sw_In;        // Debounced input in boolean
bool bBathroom_Sw_In_Lat;   // Latched input in boolean
bool bKitchen_Sw_In_Lat;    // Latched input in boolean
bool bVfd_Enable_In;        // Debounced input in boolean

/*
 *      RS_LCD              RB0
 *      E_LCD               RB1
 */
#define Vfd_Start_Out       RB2
#define Douche_Fan_Mid_Out  RB3
#define Douche_Fan_High_Out RB4
#define Led1                RB5
/*
 *      PGC                 RB6
 *      PGD                 RB7
 * 
 *      D4_LCD              RC0
 *      D5_LCD              RC1
 *      D6_LCD              RC2
 *      D7_LCD              RC3
 */
#define Fgs_Q1_Mid_In       RC4
#define Fgs_Q2_High_In      RC5
#define RC6_Spare           RC6
#define RC7_Spare           RC7
/*
 *      MCLR                RE3
 */

#ifdef	__cplusplus
extern "C" {
#endif /* __cplusplus */

void SYSTEM_Initialize(void);
void OSCILLATOR_Initialize(void);
void IO_Configuration(void);
void Timer1_Configuration(void);
void Interrupt_Configuration(void);
void Adconverter_Configuration(void);

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif	/* CONFIG_H */

