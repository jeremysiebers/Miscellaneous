#include "valve.h"
#include "main.h"

#define VALVE_DELAY_OFF 120                 //(2 min)                           // Valve turn off delay in seconds (to create overlap between transition of one valve closing and another opening)
#define VALVE_INRUSH_DELAY 60               //(1 min)                           // Valve inrush delay in seconds (turn on delay)

typedef enum {VALVE_IDLE, VALVE_EN, VALVE_ASS, VALVE_DIS};                      // valve_exec cases

typedef struct
{
	unsigned char 	valve_cmd,                                              // Command received from application
                        valve_actual,                                           // Actual valve status to output
                        valve_status,                                           // Valve status to application
                        valve_exec,                                             // switch cases variable
                        valve_que;                                              // que no when more valves are enabled when first valve is still busy(inrush)
        unsigned int    valve_delay_off;                                        // Off delay for each valve
}OUTPUT_VAR;

static OUTPUT_VAR VALVE_IO[12] = {{OFF,OFF,OFF,VALVE_IDLE,0,VALVE_DELAY_OFF},{OFF,OFF,OFF,VALVE_IDLE,0,VALVE_DELAY_OFF},
                                  {OFF,OFF,OFF,VALVE_IDLE,0,VALVE_DELAY_OFF},{OFF,OFF,OFF,VALVE_IDLE,0,VALVE_DELAY_OFF},
                                  {OFF,OFF,OFF,VALVE_IDLE,0,VALVE_DELAY_OFF},{OFF,OFF,OFF,VALVE_IDLE,0,VALVE_DELAY_OFF},
                                  {OFF,OFF,OFF,VALVE_IDLE,0,VALVE_DELAY_OFF},{OFF,OFF,OFF,VALVE_IDLE,0,VALVE_DELAY_OFF},
                                  {OFF,OFF,OFF,VALVE_IDLE,0,VALVE_DELAY_OFF},{OFF,OFF,OFF,VALVE_IDLE,0,VALVE_DELAY_OFF},
                                  {OFF,OFF,OFF,VALVE_IDLE,0,VALVE_DELAY_OFF},{OFF,OFF,OFF,VALVE_IDLE,0,VALVE_DELAY_OFF}};

static unsigned char index = 0;                                                 // Index couter for first FOR loop
static unsigned char index2 = 0;                                                // Index counter for second FOR loop

static unsigned int valve_inrush_delay = VALVE_INRUSH_DELAY;                    // Valve inrush delay to be decremented after switching on a valve to prevent enabling second valve simultaneously
static unsigned char valve_busy = OFF;                                          // Busy flag to indicate an other valve is already opening
static unsigned char valve_que_no = 1;                                          // Que number to que valve open requests
static unsigned char valve_que_sub = OFF;                                       // when a valve is opened all valves in the que are decremented by 1 to shift the que towards 0

void  VALVExUPDATE(void)                                                        // Update tick from application
{
    VALVE_IO[0].valve_actual = vlv0;                                            // Read all actual output statuses
    VALVE_IO[1].valve_actual = vlv1;
    VALVE_IO[2].valve_actual = vlv2;
    VALVE_IO[3].valve_actual = vlv3;
    VALVE_IO[4].valve_actual = vlv4;
    VALVE_IO[5].valve_actual = vlv5;
    VALVE_IO[6].valve_actual = vlv6;
    VALVE_IO[7].valve_actual = vlv7;
    VALVE_IO[8].valve_actual = vlv8;
    VALVE_IO[9].valve_actual = vlv9;
    VALVE_IO[10].valve_actual = vlv10;
    VALVE_IO[11].valve_actual = vlv11;
    
   for (index = 0; index < 12; index++)                                         // Start 12 times the valve check loop
   {
       switch (VALVE_IO[index].valve_exec)                                      // Check the valve update status, IDLE, EN, DIS, ASS etc
       {
           case     VALVE_IDLE  :   if ((VALVE_IO[index].valve_actual != VALVE_IO[index].valve_cmd) && (VALVE_IO[index].valve_cmd == ON))   // If the actual valve status is not equal to the valve command from the applivation,
                                    {                                                                                                       // and the command is ON then put the valve update status valve_exec to valve enable
					VALVE_IO[index].valve_status = ON;																	// Tell the application that the valve is ON
                                        VALVE_IO[index].valve_exec = VALVE_EN;                                                              // Go to the enable state
                                    }
                                    else if ((VALVE_IO[index].valve_actual != VALVE_IO[index].valve_cmd) && (VALVE_IO[index].valve_cmd == OFF)) // If the actual valve status is not equal to the valve command from the applivation,
                                    {  																										// and the command is OFF then put the valve update status valve_exec to valve enable
					VALVE_IO[index].valve_status = OFF;																	// Tell the application that the valve is OFF
                                        VALVE_IO[index].valve_exec = VALVE_DIS;                                                             // go to the disable state
                                    }
                                    else if (VALVE_IO[index].valve_actual == VALVE_IO[index].valve_cmd)                                     // When no change between actual and command or a inrush or delayed off function have been aborted
                                    {
                                        VALVE_IO[index].valve_status = VALVE_IO[index].valve_actual;                                        // tell the application the valve is equal to its output
                                    }
                                    break;

           case     VALVE_EN    :   if (VALVE_IO[index].valve_actual == VALVE_IO[index].valve_cmd)                                          // check while qued if the condition to enable the valve is still true
                                    {
                                        VALVE_IO[index].valve_que = 0;                                                                      // When not true, reset the que value of the current valve
                                        valve_que_sub = ON;                                                                                 // When a valve is removed then the que of all other valves must be subtracted
					VALVE_IO[index].valve_exec = VALVE_IDLE;                                                            // Reset the current valve execute case to IDLE
									
                                    }
                                    else
                                    {
                                        if (valve_busy == ON && VALVE_IO[index].valve_que == 0)                                             // When already a valve is opening(ASSERTED) and the current selected valve's que is not filled in (0)
                                        {
                                            VALVE_IO[index].valve_que = valve_que_no;                                                       // then set the valve_que number to the current actual new que value.
                                            valve_que_no++;																					// Increment the que value for the next quable valve
					}
					else if (valve_busy == OFF && VALVE_IO[index].valve_que < 2)                                        // When no valve is ASSERTED and the valve is next, que is < 2, then set the
                                        {                                                                                                   // the valve actual value to ON and set the valve_busy flag ON.
                                            VALVE_IO[index].valve_que = 0;                                                                  // Reset the que value for the enabled valve
                                            VALVE_IO[index].valve_actual = ON;                                                              // The "que < 2" is required due to first time valve enable when busy flag is OFF and no que is required (0 and 1 are ok to enable a valve)
                                            valve_busy = ON;																				// Set the busy flag to ON to indicate a valve is opening (ASSERTED_
                                            VALVE_IO[index].valve_exec = VALVE_ASS;                                                         // go to the ASSERTED STATE
					}
                                    }
                                    break;

           case     VALVE_ASS   :   if (valve_inrush_delay < 1)                                                                             // Check if the inrush time has passed
                                    {
                                         valve_busy = OFF;                                                                                  // If passed the valve_busy flag is OFF
                                         valve_inrush_delay = VALVE_INRUSH_DELAY;                                                           // The inrush delay is reset for the next valve
                                         valve_que_sub = ON;                                                                                // Que subtract routine must check if que was used
                                         VALVE_IO[index].valve_exec = VALVE_IDLE;                                                           // Valve goes to the IDLE state
                                    }
                                    else if ((VALVE_IO[index].valve_actual != VALVE_IO[index].valve_cmd) && (VALVE_IO[index].valve_cmd == OFF)) // Check if the termostat is still ON while inrushing
                                    {
                                         valve_busy = OFF;                                                                                  // If passed the valve_busy flag is OFF
                                         valve_inrush_delay = VALVE_INRUSH_DELAY;                                                           // The inrush delay is reset for the next valve
                                         valve_que_sub = ON;                                                                                // Que subtract routine must check if que was used
                                         VALVE_IO[index].valve_actual = OFF;                                                                // When thermostat is OFF while inrushing prevention the valve is disabled directly to free up other potential enables
                                         VALVE_IO[index].valve_exec = VALVE_IDLE;                                                           // Valve goes to the IDLE state
                                    }
                                    else
                                    {
                                        valve_inrush_delay--;                                                                               // When inrush time has not passed yet subtract the counter with 1
                                        valve_busy = ON;                                                                                    // Keep the valve_busy flag ON
                                    }
                                    break;

           case     VALVE_DIS   :   if ( VALVE_IO[index].valve_delay_off < 1)                                                               // Check if the delayed OFF time has passed
                                    {
                                        VALVE_IO[index].valve_actual = OFF;                                                                 // When delayed OFF has passed set the current valve OFF
                                        VALVE_IO[index].valve_delay_off = VALVE_DELAY_OFF;                                                  // Reset the delayed OFF counter for next time use
                                        VALVE_IO[index].valve_exec = VALVE_IDLE;                                                            // Valve goes to the IDLE state
                                    }
                                    else if ((VALVE_IO[index].valve_actual == VALVE_IO[index].valve_cmd) && (VALVE_IO[index].valve_cmd == ON)) // Check if the termostat is still OFF while delayed OFF
                                    {
                                        VALVE_IO[index].valve_actual = ON;                                                                  // When thermostat is ON again while delayed OFF counter is running, the valve is enabled directly and put into idle state
                                        VALVE_IO[index].valve_delay_off = VALVE_DELAY_OFF;                                                  // Reset the delayed OFF counter for next time use
                                        VALVE_IO[index].valve_exec = VALVE_IDLE;                                                            // Valve goes to the IDLE state
                                    }
                                    else
                                    {
                                        VALVE_IO[index].valve_delay_off--;                                                                  // Else subtract the delayed OFF counter with 1
                                    }
                                    break;

           default              :   VALVE_IO[index].valve_exec = VALVE_IDLE;
                                    break;
       }

       if (valve_que_sub == ON)                                                 // When a valve is set to ON the que needs to be checked if it was used
       {
           valve_que_sub = OFF;

           if (valve_que_no > 1)                                                // When que number was used, the value should be greater then 1 therefore subtract it by 1
           {
               valve_que_no--;                                                  // Subtract with 1
           }
           
           for (index2 = 0; index2 < 12; index2++)                              // Check all valve_que memories if they also are required to be subtracted by 1
           {
               if (VALVE_IO[index2].valve_que > 0)                              // When a valve has a que value, it also has to be subtracted by 1 to ensure shifting of que levels
               {
                   VALVE_IO[index2].valve_que--;				// Decrement que value of each valve that has been qued
               }
           }
       }
    }
   
    
    vlv0 = VALVE_IO[0].valve_actual;                                            // Write all valve_actual values from memory to outputs to keep them justified
    vlv1 = VALVE_IO[1].valve_actual;
    vlv2 = VALVE_IO[2].valve_actual;
    vlv3 = VALVE_IO[3].valve_actual;
    vlv4 = VALVE_IO[4].valve_actual;
    vlv5 = VALVE_IO[5].valve_actual;
    vlv6 = VALVE_IO[6].valve_actual;
    vlv7 = VALVE_IO[7].valve_actual;
    vlv8 = VALVE_IO[8].valve_actual;
    vlv9 = VALVE_IO[9].valve_actual;
    vlv10 = VALVE_IO[10].valve_actual;
    vlv11 = VALVE_IO[11].valve_actual; 


    //Led1 = valve_busy;  // for debug purposes only
}


unsigned char VALVExSTAT(unsigned char INDEX)
{
    return VALVE_IO[INDEX].valve_status;                                        // Return the valve commanded value but not the real output value because,
}                                                                               // the application does not need to know if a inrush protection or a delayed OFF function is running

void VALVExCMD(unsigned char VALVE, unsigned char COMMAND)
{
    if ((COMMAND == ON || COMMAND == OFF) && (VALVE < 12))                      // Check if command from application meets requirements and set the command to the correct valve
    {
        VALVE_IO[VALVE].valve_cmd = COMMAND;
        VALVE_IO[VALVE].valve_status = COMMAND;                                 // because the switch to status == command takes too long
    }                                                                           // In the mean while the application could read an old value...
}