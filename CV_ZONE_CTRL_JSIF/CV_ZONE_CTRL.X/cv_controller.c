#include "cv_controller.h"
#include "main.h"
#include "cv.h"
#include "termostat.h"
#include "valve.h"
#include "pumps.h"

#define CV_ON_DELAY 120                         //(2 min)                       // Delay before enabling the Central Heater
#define LAST_VALVE_OFF_DELAY 600                //(10 min)                      // When the last valve is true an extra off delay is added to allow circulation and after run of the central heater build in pump

typedef enum {IDLE, ENABLE, LAST, DISABLE};                                     // Cv controller_exec cases

typedef struct
{
	unsigned char 	exec,                                                   // switch cases variable
                        cv_cmd_que;                                             // When the last valve is to be disabled
                       
}OUTPUT_VAR;

static OUTPUT_VAR cvctrl_IO[12] = {{IDLE, OFF},{IDLE, OFF},{IDLE, OFF},{IDLE, OFF},{IDLE, OFF},{IDLE, OFF},
                                    {IDLE, OFF},{IDLE, OFF},{IDLE, OFF},{IDLE, OFF},{IDLE, OFF},{IDLE, OFF},};

static unsigned char index = 0;                                                 // Index couter for first FOR loop
static unsigned char last_valve = OFF;                                          // Last valve boolean, when a valve is the last one to be enabled, it becomes the last valve -> ON
static unsigned int cv_on_delay = CV_ON_DELAY;                                  // The central heater on delay counter
static unsigned int last_valve_off_delay = LAST_VALVE_OFF_DELAY;                // When the last_valve is ON then it will be disabled after this counter value

void  CVxCTRLxUPDATE(void)
{
    TERMOSTATxUPDATE();                                                         // Update the statuses of all termostats (inputs)
    
    for (index = 0; index < 12; index++)                                        // Check all 12 termostats if a valve must be anabled
    {
        switch (cvctrl_IO[index].exec)
        {
            case    IDLE    :   if (TERMOSTATxACTUAL(index) == ON)              // If a termostat is ON then everytime during this loop the ENABLE state is called
                                {
                                    cvctrl_IO[index].exec = ENABLE;             // goto the ENABLE state
                                    last_valve = OFF;                           // If a last_valve is active, cancel it because a new valve is to be enabled
                                }
                                else if (TERMOSTATxACTUAL(index) == OFF)        // If a termostat is OFF then everytime during this loop the DISABLE state is called
                                {
                                    cvctrl_IO[index].exec = DISABLE;            // goto the DISABLE state
                                }
                                break;
                                
            case    ENABLE  :   VALVExCMD(index,ON);                            // Set the ENABLE (ON) state to the current selected valve on the current selected termostat
                                cvctrl_IO[index].cv_cmd_que = ON;               // Set the cv_cmd_que value to ON indicating the Central Heater has to be enabled
                                cvctrl_IO[index].exec = IDLE;                   // Next time for the current valve goto the IDLE state
                                break;
                                
            case    LAST    :   if ((last_valve == OFF) || (TERMOSTATxACTUAL(index) == ON)) // When the last_valve is disabled during a last valve run OR the termostat of the current valve is ON again
                                {                                                           // (this must be checked because the current termostat value is not read in the IDLE state)
                                    if (TERMOSTATxACTUAL(index) == OFF)         // In case the current valve's termostat was not the one to go ON,
                                    {
                                        VALVExCMD(index,OFF);                   // then disable the current valve because this valve was on during the last_valve delay off program
                                        
                                    }
                                    last_valve_off_delay = LAST_VALVE_OFF_DELAY;// Reset the last_valve_off_delay to its original delay value
                                    last_valve = OFF;                           // Reset the last_valve boolean to OFF
                                    cvctrl_IO[index].exec = ENABLE;             // Set the current valve status to IDLE
                                }
                                else if (last_valve_off_delay < 1)              // If the current valve delay off timer has expired,
                                {
                                    last_valve_off_delay = LAST_VALVE_OFF_DELAY;// Reset the last_valve_off_delay to its original delay value
                                    VALVExCMD(index,OFF);                       // Set the current selected valve status to OFF
                                    cvctrl_IO[index].exec = IDLE;               // Set the current valve status to IDLE
                                    last_valve = OFF;                           // Reset the last valve boolean to OFF.
                                }
                                else                                            // Otherwise decrement the last_valve_off_delay timer value with 1
                                {
                                    last_valve_off_delay--;                     // Decrement with 1
                                }
                                break;
                                
            case    DISABLE :   if (cvctrl_IO[0].cv_cmd_que + cvctrl_IO[1].cv_cmd_que + cvctrl_IO[2].cv_cmd_que +       // If there are more then  1 valve active while entering this state,
                                    cvctrl_IO[3].cv_cmd_que + cvctrl_IO[4].cv_cmd_que + cvctrl_IO[5].cv_cmd_que +
                                    cvctrl_IO[6].cv_cmd_que + cvctrl_IO[7].cv_cmd_que + cvctrl_IO[8].cv_cmd_que +
                                    cvctrl_IO[9].cv_cmd_que + cvctrl_IO[10].cv_cmd_que + cvctrl_IO[11].cv_cmd_que > 1)
                                {
                                    VALVExCMD(index,OFF);                       // then set the selected valve (termostat no) to OFF
                                    cvctrl_IO[index].cv_cmd_que = OFF;          // Set the cv_cmd_que of the current valve to OFF
                                    cvctrl_IO[index].exec = IDLE;               // Set the selected termostat state to IDLE
                                }
                                else if (cvctrl_IO[index].cv_cmd_que == ON)     // else if there is only one valve ON and the cv_cmd_que is still ON
                                {
                                    cvctrl_IO[index].cv_cmd_que = OFF;          // Then set the que to OFF
                                    cvctrl_IO[index].exec = LAST;               // Set the current valve status to LAST indicating it is the last valve to be ON
                                    last_valve = ON;                            // Set the variable last_valve to ON to indicate a last valve off delay is carried out
                                }
                                else
                                {
                                   cvctrl_IO[index].exec = IDLE;                // When the cv_cmd_que should be already OFF the set the current valve state to IDLE
                                }
                                break;
                                
            default         :   cvctrl_IO[index].exec = IDLE;                   // Default goto the IDLE state
                                break;
        }
    }

    //Led1 = last_valve;

    if (cvctrl_IO[0].cv_cmd_que == OFF && cvctrl_IO[0].cv_cmd_que == OFF && cvctrl_IO[1].cv_cmd_que == OFF &&
        cvctrl_IO[0].cv_cmd_que == OFF && cvctrl_IO[2].cv_cmd_que == OFF && cvctrl_IO[3].cv_cmd_que == OFF &&
        cvctrl_IO[0].cv_cmd_que == OFF && cvctrl_IO[4].cv_cmd_que == OFF && cvctrl_IO[5].cv_cmd_que == OFF &&
        cvctrl_IO[0].cv_cmd_que == OFF && cvctrl_IO[6].cv_cmd_que == OFF && cvctrl_IO[7].cv_cmd_que == OFF &&
        cvctrl_IO[0].cv_cmd_que == OFF && cvctrl_IO[8].cv_cmd_que == OFF && cvctrl_IO[9].cv_cmd_que == OFF &&
        cvctrl_IO[0].cv_cmd_que == OFF && cvctrl_IO[10].cv_cmd_que == OFF && cvctrl_IO[11].cv_cmd_que == OFF)
    {
        CVxCMD(OFF);
        cv_on_delay = CV_ON_DELAY;
    }
    else
    {
        if (cv_on_delay < 2)
            {
                CVxCMD(ON);
                cv_on_delay = 1;
            }
            else
            {
                cv_on_delay--;
            }
    }

    /*//////////////////////////////////////////////////////////////////////////// Watchdog timer lockup test
    if (TERMOSTATxACTUAL(11) == ON)
    {
        while(1);
    }
    *///////////////////////////////////////////////////////////////////////////

    VALVExUPDATE();                                                             // Update the statuses of all valves
    PUMPxUPDATE();                                                              // Update the statuses of all pumps

}