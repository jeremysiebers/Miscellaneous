#include "main.h"
#include "executer.h"
#include "design_random.h"
#include "design_all_leds_off.h"
#include "sequence.h"

#define START_SEQ 0

void RUNxDISPLAY(void);
void UPDATExDESIGN(void);
void EXECxTIME(unsigned int Time);

/******************************************************************************/
/*          DESIGN LOCAL VARIABLES                                            */
/******************************************************************************/
enum
{
    Prog0, Prog1, Prog2, Prog3, Prog4, Prog5, Prog6, Prog7, Prog8, Prog9, Prog15
                                                                                // Enum to enumerate different program cases
};

static unsigned char Sequence_Program = 0;                                      // Variabe to hold the actual switch state of this program
static unsigned int Counter = 0;                                                // Used for counting down the wait time between updates of programs for the leds
static unsigned int Sequencer = START_SEQ;                                      // counter used for loading next sequence state
static unsigned int Time = 0;                                                   // Variable used for calculating the wait time

/******************************************************************************/
/*          RUN DISPLAY                                                       */
/******************************************************************************/

void RUNxDISPLAY(void)
{
    
    
}

/******************************************************************************/
/*          DESIGN SEQUENCER                                                  */
/******************************************************************************/

void UPDATExDESIGN(void)
{
    switch (Sequence_Program)
    {
        case    0   :   if(Sequencer >= NO_OF_SEQUENCES)                        // When all sequences are past, restart with the first one
                        {
                            Sequencer = START_SEQ;                              // reset to 0 to the first sequence
                        }
                        
                        switch(Sequence[Sequencer].Prog)                        // Lookup the program to be started in the sequence array (struct of bitfields fo unsigned long int)
                        {
                            case    Prog0   :   Led_Bit[Sequence[Sequencer].Led].Prog = 0;  // Start program 0 for the selected Led
                                                break;

                            case    Prog1   :   Led_Bit[Sequence[Sequencer].Led].Prog = 1;  // Start program 1 for the selected Led
                                                break;

                            case    Prog2   :   Led_Bit[Sequence[Sequencer].Led].Prog = 2;  // Start program 2 for the selected Led
                                                Led_Bit[Sequence[Sequencer].Led].Speed = Sequence[Sequencer].Speed; // Pass the speed setting for the selected led
                                                break;

                            case    Prog3   :   Led_Bit[Sequence[Sequencer].Led].Prog = 3;  // Start program 3 for the selected Led
                                                Led_Bit[Sequence[Sequencer].Led].Speed = Sequence[Sequencer].Speed; // Pass the speed setting for the selected led
                                                break;

                            case    Prog4   :   Led_Bit[Sequence[Sequencer].Led].Prog = 4;  // Start program 4 for the selected Led
                                                Led_Bit[Sequence[Sequencer].Led].Speed = Sequence[Sequencer].Speed; // Pass the speed setting for the selected led
                                                break;

                            case    Prog5   :   Led_Bit[Sequence[Sequencer].Led].Prog = 5;  // Start program 5 for the selected Led
                                                Led_Bit[Sequence[Sequencer].Led].Speed = Sequence[Sequencer].Speed; // Pass the speed setting for the selected led
                                                break;

                            case    Prog6   :   DESIGNxALLxLEDSxOFF();          // in order to make all leds OFF easier and cheaper call this program
                                                break;
                            
                            case    Prog7   :   DESIGNxRANDOM();                // Start the random pattern by calling special function
                                                break;

                            case    Prog8   :   DESIGNxALLxLEDSxON();           // in order to make all leds ON easier and cheaper call this program
                                                break;

                            case    Prog9   :   DESIGNxALLxLEDSxSLBLNK();       // in order to make all leds slow blink on easier and cheaper
                                                break;

                            case    Prog15  :   break;                          // To add extra wait time
                                            
                            default         :   break;
                        }
                        Time = 0;                                               // Reset the Time variable to 0
                        Time += Sequence[Sequencer].Time1;                      // lookup the first part of the time and add it to Time
                        Time += Sequence[Sequencer].Time2;                      // lookup the second part of the time and add it to Time
                        Sequence_Program = 1;                                   // go next time to the execute wait time case
                        break;
                        
        case    1   :   Sequence_Program = 1;                                   // stay in this case unti the wait time is past
                        EXECxTIME(Time);                                        // call subroutine for couning down the time to wait before the next update may take place
                        break;

        default     :   break;
    }
}

/******************************************************************************/
/*          DESIGN CYCLE TIME                                                 */
/******************************************************************************/

void EXECxTIME(unsigned int Time)
{
    Counter++;                                                                  // increment counter value
    if(Counter > Time * tSEC)                                                   // when the Time value is still larger then the counter value -> keep on counting
    {
        Sequence_Program = 0;                                                   // time past, call case 0 again for the next update
        Sequencer++;                                                            // Call the next sequence
        Counter = 0;                                                            // reset the counter
    }
}

/*case    0   :   if(DESIGNxRANDOM() == Finished)
                        {
                            Sequence_Program++;
                        }
                        break;

        case    1   :   EXECxTIME(300);
                        break;

        case    2   :   DESIGNxALLxLEDSxOFF();
                        Sequence_Program++;
                        break;

        case    3   :   EXECxTIME(1);
                        break;

        case    4   :   if(DESIGNxDRAWxFIGURE(FORWARD,'F',11) == Finished)
                        {
                            Sequence_Program++;
                        }
                        break;

        case    5   :   if(DESIGNxDRAWxFIGURE(FORWARD,'C',11) == Finished)
                        {
                            Sequence_Program++;
                        }
                        break;

        case    6   :   if(DESIGNxDRAWxFIGURE(FORWARD,'D',11) == Finished)
                        {
                            Sequence_Program++;
                        }
                        break;

        case    7   :   if(DESIGNxDRAWxFIGURE(FORWARD,'B',11) == Finished)
                        {
                            Sequence_Program++;
                        }
                        break;

        case    8   :   if(DESIGNxDRAWxFIGURE(FORWARD,'A',11) == Finished)
                        {
                            Sequence_Program++;
                        }
                        break;

        case    9   :   if(DESIGNxDRAWxFIGURE(BACKWARD,'F',11) == Finished)
                        {
                            Sequence_Program++;
                        }
                        break;

        case    10  :   if(DESIGNxDRAWxFIGURE(BACKWARD,'C',11) == Finished)
                        {
                            Sequence_Program++;
                        }
                        break;

        case    11  :   if(DESIGNxDRAWxFIGURE(BACKWARD,'D',11) == Finished)
                        {
                            Sequence_Program++;
                        }
                        break;

        case    12  :   if(DESIGNxDRAWxFIGURE(BACKWARD,'B',11) == Finished)
                        {
                            Sequence_Program++;
                        }
                        break;

        case    13  :   if(DESIGNxDRAWxFIGURE(BACKWARD,'A',11) == Finished)
                        {
                            Sequence_Program++;
                        }
                        break;

        case    14  :   EXECxTIME(20);
                        break;

        case    15  :   Sequence_Program = 0;
                        break;

        default     :   break;*/