#include "main.h"
#include "executer.h"
#include "design_random.h"
#include "design_all_leds_off.h"
#include "sequence.h"

#define INIT 0xFFFF

void RUNxDISPLAY(unsigned char Program_Selector);
char UPDATExDESIGN(unsigned int Seq);
char EXECxTIME(unsigned int Time);

/******************************************************************************/
/*          DESIGN LOCAL VARIABLES                                            */
/******************************************************************************/
enum
{
    Prog0, Prog1, Prog2, Prog3, Prog4, Prog5, Prog6, Prog7, Prog8, Prog9, Prog10, Prog11, Prog12, Prog13, Prog14, Prog15
                                                                                // Enum to enumerate different program cases
};

static unsigned char Sequence_Program = 0;                                      // Variabe to hold the actual switch state of this program
static unsigned int Counter = 0;                                                // Used for counting down the wait time between updates of programs for the leds
static unsigned int Sequencer = INIT;                                           // counter used for loading next sequence state
static unsigned int Time = 0;                                                   // Variable used for calculating the wait time
static unsigned char Return_Val = Busy;                                         // Return variable to stop current routine when finished
static unsigned int index = 0;
static unsigned char Program_Selector_Old = 9;

const rom unsigned int Run_Display0[] = {
    ALL_LED_OFF,
    MAIN_START,
    FINISHED
};

const rom unsigned int Run_Display1[] = {
    ALL_LED_OFF,
    MAIN_START,
    RANDOM_START,
    DELAY5,
    ALL_LED_OFF,
    LINE_AROUND_ON,
    LINE_AROUND_OFF,
    LINE_AROUND_ON,
    LINE_AROUND_OFF,
    SLOW_BLINK_OUT_LED,
    DELAY3,
    ALL_LED_OFF,
    SLOW_BLINK_ALL_LED,
    DELAY1,
    ALL_LED_OFF,
    SPIRAL_CLK_WISE_ON,
    SPIRAL_CCLK_WISE_OFF,
    SPIRAL_CLK_WISE_ON,
    SPIRAL_CCLK_WISE_OFF,
    SPIRAL_CLK_WISE_ON,
    SPIRAL_CCLK_WISE_OFF,
    DELAY1,
    SLOW_BLINK_CNTR_LED,
    DELAY5,
    ALL_LED_OFF,
    TW0_ON,
    TW0_OFF,
    TW1_ON,
    TW1_OFF,
    TW2_ON,
    TW2_OFF,
    TW3_ON,
    TW3_OFF,
    TW4_ON,
    TW4_OFF,
    TW5_ON,
    TW5_OFF,
    TW6_ON,
    TW6_OFF,
    TW7_ON,
    TW7_OFF,

    TW0_ON,
    TW0_OFF,
    TW1_ON,
    TW1_OFF,
    TW2_ON,
    TW2_OFF,
    TW3_ON,
    TW3_OFF,
    TW4_ON,
    TW4_OFF,
    TW5_ON,
    TW5_OFF,
    TW6_ON,
    TW6_OFF,
    TW7_ON,
    TW7_OFF,

    TW0_ON,
    TW0_OFF,
    TW1_ON,
    TW1_OFF,
    TW2_ON,
    TW2_OFF,
    TW3_ON,
    TW3_OFF,
    TW4_ON,
    TW4_OFF,
    TW5_ON,
    TW5_OFF,
    TW6_ON,
    TW6_OFF,
    TW7_ON,
    TW7_OFF,

    TW0_ON,
    TW0_OFF,
    TW1_ON,
    TW1_OFF,
    TW2_ON,
    TW2_OFF,
    TW3_ON,
    TW3_OFF,
    TW4_ON,
    TW4_OFF,
    TW5_ON,
    TW5_OFF,
    TW6_ON,
    TW6_OFF,
    TW7_ON,
    TW7_OFF,

    TW0_ON,
    TW1_ON,
    TW2_ON,
    TW3_ON,
    TW4_ON,
    TW5_ON,
    TW6_ON,
    TW7_ON,
    DELAY1,
    ALL_LED_OFF,

    TW7_ON,
    TW7_OFF,
    TW6_ON,
    TW6_OFF,
    TW5_ON,
    TW5_OFF,
    TW4_ON,
    TW4_OFF,
    TW3_ON,
    TW3_OFF,
    TW2_ON,
    TW2_OFF,
    TW1_ON,
    TW1_OFF,
    TW0_ON,
    TW0_OFF,

    TW7_ON,
    TW7_OFF,
    TW6_ON,
    TW6_OFF,
    TW5_ON,
    TW5_OFF,
    TW4_ON,
    TW4_OFF,
    TW3_ON,
    TW3_OFF,
    TW2_ON,
    TW2_OFF,
    TW1_ON,
    TW1_OFF,
    TW0_ON,
    TW0_OFF,
    TW7_ON,
    TW7_OFF,
    TW6_ON,
    TW6_OFF,
    TW5_ON,
    TW5_OFF,
    TW4_ON,
    TW4_OFF,
    TW3_ON,
    TW3_OFF,
    TW2_ON,
    TW2_OFF,
    TW1_ON,
    TW1_OFF,
    TW0_ON,
    TW0_OFF,
    TW7_ON,
    TW7_OFF,
    TW6_ON,
    TW6_OFF,
    TW5_ON,
    TW5_OFF,
    TW4_ON,
    TW4_OFF,
    TW3_ON,
    TW3_OFF,
    TW2_ON,
    TW2_OFF,
    TW1_ON,
    TW1_OFF,
    TW0_ON,
    TW0_OFF,
    
    TW7_ON,
    TW6_ON,
    TW5_ON,
    TW4_ON,
    TW3_ON,
    TW2_ON,
    TW1_ON,
    TW0_ON,
    DELAY1,
    ALL_LED_OFF,

    FINISHED
};

const rom unsigned int Run_Display2[] = {
    RANDOM_START, 
    DELAY5,
    DELAY5,
    DELAY5,
    DELAY5,
    DELAY5,
    DELAY5,
    DELAY5,
    DELAY5,
    DELAY5,
    DELAY5,
    DELAY5,
    DELAY5,
    DELAY5,
    DELAY5,
    DELAY5,
    DELAY5,
    DELAY5,
    DELAY5,
    DELAY5,
    DELAY5,
    DELAY5,
    DELAY5,
    DELAY5,
    DELAY5,
    DELAY5,
    DELAY5,
    DELAY5,
    DELAY5,
    DELAY5,
    DELAY5,
    DELAY5,
    DELAY5,
    DELAY5,
    DELAY5,
    FINISHED
};

const rom unsigned int Run_Display3[] = {
    ALL_LED_OFF,
    
    SLOW_BLINK_CNTR_LED,
    DELAY1, 
    SLOW_BLINK_ALL_LED,
    DELAY1,
    ALL_LED_OFF,
//----------------------------------------------------------------------------//    
    TW0_ON,
    TW0_OFF,
    TW1_ON,
    TW1_OFF,
    TW2_ON,
    TW2_OFF,
    TW3_ON,
    TW3_OFF,
    TW4_ON,
    TW4_OFF,
    TW5_ON,
    TW5_OFF,
    TW6_ON,
    TW6_OFF,
    TW7_ON,
    TW7_OFF,
    
    TW0_ON,
    TW0_OFF,
    TW1_ON,
    TW1_OFF,
    TW2_ON,
    TW2_OFF,
    TW3_ON,
    TW3_OFF,
    TW4_ON,
    TW4_OFF,
    TW5_ON,
    TW5_OFF,
    TW6_ON,
    TW6_OFF,
    TW7_ON,
    TW7_OFF,
    
    TW0_ON,
    TW0_OFF,
    TW1_ON,
    TW1_OFF,
    TW2_ON,
    TW2_OFF,
    TW3_ON,
    TW3_OFF,
    TW4_ON,
    TW4_OFF,
    TW5_ON,
    TW5_OFF,
    TW6_ON,
    TW6_OFF,
    TW7_ON,
    TW7_OFF,
    
    TW0_ON,
    TW0_OFF,
    TW1_ON,
    TW1_OFF,
    TW2_ON,
    TW2_OFF,
    TW3_ON,
    TW3_OFF,
    TW4_ON,
    TW4_OFF,
    TW5_ON,
    TW5_OFF,
    TW6_ON,
    TW6_OFF,
    TW7_ON,
    TW7_OFF,
    
    TW0_ON,
    TW0_OFF,
    TW1_ON,
    TW1_OFF,
    TW2_ON,
    TW2_OFF,
    TW3_ON,
    TW3_OFF,
    TW4_ON,
    TW4_OFF,
    TW5_ON,
    TW5_OFF,
    TW6_ON,
    TW6_OFF,
    TW7_ON,
    TW7_OFF,
//----------------------------------------------------------------------------//    
    TW0_ON,    
    TW1_ON,
    TW2_ON,
    TW3_ON,
    TW4_ON,
    TW5_ON,
    TW6_ON,
    TW7_ON,
//----------------------------------------------------------------------------//    
    
    TW0_OFF,
    TW0_ON, 
    TW1_OFF,
    TW1_ON,
    TW2_OFF,
    TW2_ON,
    TW3_OFF,
    TW3_ON,
    TW4_OFF,
    TW4_ON,
    TW5_OFF,
    TW5_ON,
    TW6_OFF,
    TW6_ON,
    TW7_OFF,
    TW7_ON,
    
    TW0_OFF,
    TW0_ON, 
    TW1_OFF,
    TW1_ON,
    TW2_OFF,
    TW2_ON,
    TW3_OFF,
    TW3_ON,
    TW4_OFF,
    TW4_ON,
    TW5_OFF,
    TW5_ON,
    TW6_OFF,
    TW6_ON,
    TW7_OFF,
    TW7_ON,
    
    TW0_OFF,
    TW0_ON, 
    TW1_OFF,
    TW1_ON,
    TW2_OFF,
    TW2_ON,
    TW3_OFF,
    TW3_ON,
    TW4_OFF,
    TW4_ON,
    TW5_OFF,
    TW5_ON,
    TW6_OFF,
    TW6_ON,
    TW7_OFF,
    TW7_ON,
    
    TW0_OFF,
    TW0_ON, 
    TW1_OFF,
    TW1_ON,
    TW2_OFF,
    TW2_ON,
    TW3_OFF,
    TW3_ON,
    TW4_OFF,
    TW4_ON,
    TW5_OFF,
    TW5_ON,
    TW6_OFF,
    TW6_ON,
    TW7_OFF,
    TW7_ON,
    
    TW0_OFF,
    TW0_ON, 
    TW1_OFF,
    TW1_ON,
    TW2_OFF,
    TW2_ON,
    TW3_OFF,
    TW3_ON,
    TW4_OFF,
    TW4_ON,
    TW5_OFF,
    TW5_ON,
    TW6_OFF,
    TW6_ON,
    TW7_OFF,
    TW7_ON,
//----------------------------------------------------------------------------// 
    
    ALL_LED_OFF,
    ALL_LED_ON,
    ALL_LED_OFF,
    ALL_LED_ON,
    ALL_LED_OFF,
    ALL_LED_ON,
    ALL_LED_OFF,
    ALL_LED_ON,
    ALL_LED_OFF,
    ALL_LED_ON,
    ALL_LED_OFF,
    ALL_LED_ON,
    ALL_LED_OFF,
 //----------------------------------------------------------------------------//
    
    SPIRAL_CLK_WISE_ON,
    SPIRAL_CCLK_WISE_OFF,
    SLOW_BLINK_CNTR_LED,
    SPIRAL_CLK_WISE_ON,
    SPIRAL_CCLK_WISE_OFF,
    SPIRAL_CLK_WISE_ON,
    SPIRAL_CCLK_WISE_OFF,
    
    ALL_LED_OFF,
    LINE_AROUND_ON,
    LINE_AROUND_OFF,
    SLOW_BLINK_CNTR_LED,
    LINE_AROUND_ON,
    LINE_AROUND_OFF,
    LINE_AROUND_ON,
    LINE_AROUND_OFF,
    LINE_AROUND_ON,
    LINE_AROUND_OFF,
    
//----------------------------------------------------------------------------//   
    
    ALL_LED_ON,
    ALL_LED_OFF,
    ALL_LED_ON,
    ALL_LED_OFF,
    ALL_LED_ON,
    ALL_LED_OFF,
    ALL_LED_ON,
    ALL_LED_OFF,
    ALL_LED_ON,
    ALL_LED_OFF,
    ALL_LED_ON,
    ALL_LED_OFF,
    LINE_AROUND_ON,
    TW0_ON,
    TW0_OFF,
    TW1_ON,
    TW1_OFF,
    SPIRAL_CLK_WISE_ON,
    TW2_ON,
    TW2_OFF,
    TW3_ON,
    TW3_OFF,
    SPIRAL_CCLK_WISE_OFF,
    ALL_LED_ON,
    ALL_LED_OFF,
    ALL_LED_ON,
    ALL_LED_OFF,
    ALL_LED_ON,
    ALL_LED_OFF,
    ALL_LED_ON,
    ALL_LED_OFF,
    ALL_LED_ON,
    ALL_LED_OFF,
    ALL_LED_ON,
    ALL_LED_OFF,
    TW4_ON,
    TW4_OFF,
    TW5_ON,
    TW5_OFF,
    SPIRAL_CLK_WISE_ON,
    TW6_ON,
    TW6_OFF,
    TW7_ON,
    TW7_OFF,
    SPIRAL_CCLK_WISE_OFF,
    ALL_LED_ON,
    ALL_LED_OFF,
    ALL_LED_ON,
    ALL_LED_OFF,
    ALL_LED_ON,
    ALL_LED_OFF,
    ALL_LED_ON,
    ALL_LED_OFF,
    ALL_LED_ON,
    ALL_LED_OFF,
    ALL_LED_ON,
    ALL_LED_OFF,
    
    FINISHED
};

/******************************************************************************/
/*          RUN DISPLAY                                                       */
/******************************************************************************/

void RUNxDISPLAY(unsigned char Program_Selector)
{
    if (Program_Selector != Program_Selector_Old){
        Program_Selector_Old = Program_Selector;
        index = 0;
    }
    
    switch (Program_Selector){
        
        case 0 :
            if (Run_Display0[index] == FINISHED)
            {
                index = 0;
            }    
            if (UPDATExDESIGN(Run_Display0[index]) == Finished)
            {
                index++;
            }
            break;
            
        case 1 :
            if (Run_Display1[index] == FINISHED)
            {
                index = 0;
            }    
            if (UPDATExDESIGN(Run_Display1[index]) == Finished)
            {
                index++;
            }
            break;
            
        case 2 :
            if (Run_Display2[index] == FINISHED)
            {
                index = 0;
            }    
            if (UPDATExDESIGN(Run_Display2[index]) == Finished)
            {
                index++;
            }
            break;
            
        case 3 :
            if (Run_Display3[index] == FINISHED)
            {
                index = 0;
            }    
            if (UPDATExDESIGN(Run_Display3[index]) == Finished)
            {
                index++;
            }
            break;
            
        default :
            break;
    }
}

/******************************************************************************/
/*          DESIGN SEQUENCER                                                  */
/******************************************************************************/

char UPDATExDESIGN(unsigned int Seq)
{
    Return_Val = Busy;                                                          // When display routine is finished return finished to RUNxDISPLAY

    switch (Sequence_Program)
    {
        case    0   :   Sequencer = Seq;                                        // Pass index number of effect in the struct.
                        Sequence_Program = 1;
                        break;
                        
        case    1   :   switch(Sequence[Sequencer].Prog)                        // Lookup the program to be started in the sequence array (struct of bitfields fo unsigned long int)
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

                            case    Prog14  :   Return_Val = Finished;          // When display routine is finished call for next routine to run
                                                Sequence_Program = 0;           // reset Sequence program for next start
                                                break;

                            case    Prog15  :   break;                          // To add extra wait time
                                            
                            default         :   break;
                        }
                        if (Return_Val == Busy)                                 // When finished do not set the sequence_program to 1 for time calculation
                        {
                        Time = 0;                                               // Reset the Time variable to 0
                        Time += Sequence[Sequencer].Time1;                      // lookup the first part of the time and add it to Time
                        Time += Sequence[Sequencer].Time2;                      // lookup the second part of the time and add it to Time
                        Sequence_Program = 2;                                   // go next time to the execute wait time case
                        }
                        break;
                        
        case    2   :   if (Return_Val == Finished)
                        {
                            break;                                              // When finished stop program
                        }
                        if (EXECxTIME(Time)== Finished)                         // call subroutine for couning down the time to wait before the next update may take place
                        {
                            Sequence_Program = 1;                               // stay in this case unti the wait time is past
                            break;
                        }
                        Sequence_Program = 2;                                   // stay in this case unti the wait time is past
                        break;

        default     :   break;
    }
    return(Return_Val);
}

/******************************************************************************/
/*          DESIGN CYCLE TIME                                                 */
/******************************************************************************/

char EXECxTIME(unsigned int Time)
{
    char Return_Val = Busy;
    Counter++;                                                                  // increment counter value
    if(Counter > Time * tSEC)                                                   // when the Time value is still larger then the counter value -> keep on counting
    {
        Sequencer++;                                                            // Call the next sequence
        Counter = 0;                                                            // reset the counter
        Return_Val = Finished;
    }

    return(Return_Val);
}