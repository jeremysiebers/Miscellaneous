#include "pumps.h"
#include "main.h"

#define PUMP_DELAY_OFF_0 120            //(2 min)                               // Pump turn off delay in seconds (default)
#define PUMP_DELAY_OFF_1 600            //(10 min)                              // Pump turn off delay in seconds
#define PUMP_DELAY_OFF_2 1200           //(20 min)                              // Pump turn off delay in seconds
#define PUMP_DELAY_OFF_3 1800           //(30 min)                              // Pump turn off delay in seconds
#define PUMP_PRT_CNT 86400              //(24 Hour)                             // Count every x seconds then run protection
#define PUMP_ON_PRT 60                  //(1 min)                               // Pump protection timer length of protection (every 24 Hours)

void DIPxSWT(void);

typedef enum {PUMP_IDLE, PUMP_EN, PUMP_PRT, PUMP_DIS};                          // pump_exec cases

typedef struct
{
	unsigned char 	pump_cmd,                                               // Command received from application
                        pump_actual,                                            // Actual PUMP status to output
                        pump_status,                                            // PUMP status to application
                        pump_exec,                                              // switch cases variable
                        pump_prt_en,
                        pump_on_prt;                                            // Pump protection on timer
        unsigned int    pump_delay_off;                                         // Off delay for each PUMP timer
       unsigned long int pump_prt_cnt;                                          // pump protection timer
}OUTPUT_VAR;

static OUTPUT_VAR PUMP_IO[2] = {{OFF,OFF,OFF,PUMP_IDLE,OFF,PUMP_ON_PRT,PUMP_DELAY_OFF_0,PUMP_PRT_CNT},
                                {OFF,OFF,OFF,PUMP_IDLE,OFF,PUMP_ON_PRT,PUMP_DELAY_OFF_0,PUMP_PRT_CNT}};

static unsigned char index = 0;                                                 // Index used for FOR LOOP
static unsigned char index2 = 0;                                                // Index2 used for AD switch
static unsigned char index3 = 0;                                                // Index3 used for pump AD selection
static int ad_result = 0;                                                       // AD result variable
static int ad_calc = 0;                                                         // Calc variable

void  PUMPxUPDATE(void)                                                         // Update tick from application
{
    PUMP_IO[0].pump_actual = pmp0_o;                                            // Read back the actual output value pump1
    PUMP_IO[1].pump_actual = pmp1_o;                                            // Read back the actual output value pump2
    PUMP_IO[0].pump_cmd = pmp0_en;                                              // Read the enable signal for pump1
    PUMP_IO[1].pump_cmd = pmp1_en;                                              // Read the enable signal for pump2

    DIPxSWT();

    for (index = 0; index < 2; index++)
    {
        switch (PUMP_IO[index].pump_exec)
        {
            case    PUMP_IDLE   :   if ((PUMP_IO[index].pump_actual != PUMP_IO[index].pump_cmd) && (PUMP_IO[index].pump_cmd == ON))
                                    {                                           // When actual is not equal to command and command is ON
                                        PUMP_IO[index].pump_exec = PUMP_EN;     // Goto the PUMP ENABLE state
                                        PUMP_IO[index].pump_status = ON;        // Report back that the pump is ON
                                    }
                                    else if ((PUMP_IO[index].pump_actual != PUMP_IO[index].pump_cmd) && (PUMP_IO[index].pump_cmd == OFF))
                                    {                                           // When actual is not equal to command and command is OFF
                                        PUMP_IO[index].pump_exec = PUMP_DIS;    // Goto the PUMP DISABLE state
                                        PUMP_IO[index].pump_status = OFF;       // Report back that the pump is OFF
                                    }
                                    else if (PUMP_IO[index].pump_prt_cnt < 1)   // If no command and the pump protection timer is 0
                                    {
                                        PUMP_IO[index].pump_prt_cnt = PUMP_PRT_CNT; // reset the timer to the PUMP_PRT_CNT value
                                        PUMP_IO[index].pump_exec = PUMP_PRT;    // Goto the PUMP PROTECTION state
                                        PUMP_IO[index].pump_status = ON;        //  Report back that the pump is ON
                                        PUMP_IO[index].pump_actual = ON;        // Switch the pump ON
                                    }
                                    else if (PUMP_IO[index].pump_prt_en == ON)  // When the protection is enabled countdown the timer
                                    {
                                        PUMP_IO[index].pump_prt_cnt--;          // Decrement timer with 1
                                    }
                                    else
                                    {
                                        PUMP_IO[index].pump_prt_cnt = PUMP_PRT_CNT; // If protection is not enabled reset the timer to the PUMP_PRT_CNT value
                                    }
                                    break;

            case    PUMP_EN     :   PUMP_IO[index].pump_actual = ON;            // Enable the pump
                                    PUMP_IO[index].pump_prt_cnt = PUMP_PRT_CNT; // reset the pump protection timer because the pump is used within the timer period
                                    PUMP_IO[index].pump_exec = PUMP_IDLE;       // Goto the PUMP IDLE state
                                    break;

            case    PUMP_PRT    :   if (PUMP_IO[index].pump_on_prt < 1)         // When the PUMP = ON protection timer has passed
                                    {
                                        PUMP_IO[index].pump_on_prt = PUMP_ON_PRT; // reset the timer back to the PUMP_ON_PRT timer value
                                        PUMP_IO[index].pump_actual = OFF;       // Disable the PUMP
                                        PUMP_IO[index].pump_status = OFF;       // Report back that the pump is off
                                        PUMP_IO[index].pump_exec = PUMP_IDLE;   // Goto the PUMP IDLE state
                                    }
                                    else if (PUMP_IO[index].pump_cmd == ON)     // Else if the command went ON during protection
                                    {
                                        PUMP_IO[index].pump_on_prt = PUMP_ON_PRT;   // Reset the PUMP ON PROTECTION timer
                                        PUMP_IO[index].pump_status = ON;        // Set the PUMP to ON (was already on but to be sure)
                                        PUMP_IO[index].pump_exec = PUMP_EN;     // Goto the PUMP ENABLE state to reset the protection timer there
                                    }
                                    else                                        // Else count down on the PROTECTION ON TIMER
                                    {
                                       PUMP_IO[index].pump_on_prt--;            // Decrement the PUMP ON PROTECTION timer with 1
                                    }
                                    break;

            case    PUMP_DIS    :   if (PUMP_IO[index].pump_delay_off < 1)      // When the PUMP OFF DELAY is 0
                                    {
                                        PUMP_IO[index].pump_actual = OFF;       // Then set the pump to the OFF state
                                        PUMP_IO[index].pump_prt_cnt = PUMP_PRT_CNT; // Reset the PUMP PROTECTION TIMER because the pump just went off
                                        PUMP_IO[index].pump_exec = PUMP_IDLE;   // Goto the PUMP IDLE state
                                    }
                                    else if (PUMP_IO[index].pump_cmd == ON)     // Else if the command went ON during protection
                                    {
                                        PUMP_IO[index].pump_on_prt = PUMP_ON_PRT;   // Reset the PUMP ON PROTECTION timer
                                        PUMP_IO[index].pump_status = ON;        // Set the PUMP to ON (was already on but to be sure)
                                        PUMP_IO[index].pump_exec = PUMP_EN;     // Goto the PUMP ENABLE state to reset the protection timer there
                                    }
                                    else
                                    {
                                        PUMP_IO[index].pump_delay_off--;        // Else count down the PUMP DELAY OFF TIMMER with 1
                                    }
                                    break;

            default             :   PUMP_IO[index].pump_exec = PUMP_IDLE;       // Default goto the PUMP IDLE state
                                    break;
        }        
    }
    
    pmp0_o = PUMP_IO[0].pump_actual;                                            // Set the actual output value pump1
    pmp1_o = PUMP_IO[1].pump_actual;                                            // Set the actual output value pump2
}

void DIPxSWT(void)
{
    switch (index2)
    {
        case    0   :   if (index3 == 0)                                        // If pump1
                        {
                            ADCON0 = 0x01;                                      // Select RA1 input for pump1 and enable AD (ADON)
                        }
                        else if (index3 == 1)                                   // if pump2
                        {
                            ADCON0 = 0x00;                                      // Select RA0 input for pump2 and enable AD (ADON)
                        }
                        index2 = 1;                                             // Goto the next state
                        break;
        case    1   :   ADCON0bits.GO = 1;                                      // Convert AD value
                        index2 = 2;                                             // Goto the next state
                        break;
        case    2   :   if (ADCON0bits.GO == 0)                                 // When conversion is ready
			{
                            //Led1 = !Led1;
                            ad_result = (((unsigned int)ADRESH)<<8)|(ADRESL);   // Readout the 2 registers and combine them in one result variable

                            if ((ad_result - 512) > 0)                          // If the protection switch is set
                            {
                                PUMP_IO[index3].pump_prt_en = ON;               // Enable the pump protection
                                if (PUMP_IO[index3].pump_exec != PUMP_DIS)      // When the PUMP DELAY OFF is not running
                                {
                                    PUMP_IO[index3].pump_delay_off = PUMP_DELAY_OFF_0; // Set the pump delay off to the next value
                                }
                                ad_result = ad_result - 512;                    // Subtract the switch value from the result to check for the other switch statusen
                            }
                            else if ((ad_result - 512) < 0)                     // When protection is off switch is not set
                            {
                                PUMP_IO[index3].pump_prt_en = OFF;              // Disable the pump protection
                                if (PUMP_IO[index3].pump_exec != PUMP_DIS)      // When the PUMP DELAY OFF is not running
                                {
                                    PUMP_IO[index3].pump_delay_off = PUMP_DELAY_OFF_0; // Set the pump delay off to the next value
                                }
                            }
                            if ((ad_result - 250) > 0)                          // If the first DELAY OFF switch is set
                            {
                                if (PUMP_IO[index3].pump_exec != PUMP_DIS)      // When the PUMP DELAY OFF is not running
                                {
                                    PUMP_IO[index3].pump_delay_off = PUMP_DELAY_OFF_1; // Set the pump delay off to the next value
                                }                                
                            }
                            else if ((ad_result - 120) > 0)                     // If the second DELAY OFF switch is set
                            {
                                if (PUMP_IO[index3].pump_exec != PUMP_DIS)      // When the PUMP DELAY OFF is not running
                                {
                                    PUMP_IO[index3].pump_delay_off = PUMP_DELAY_OFF_2; // Set the pump delay off to the next value
                                }
                            }
                            else if ((ad_result - 60) > 0)                      // If the third DELAY OFF switch is set
                            {
                                if (PUMP_IO[index3].pump_exec != PUMP_DIS)      // When the PUMP DELAY OFF is not running
                                {
                                    PUMP_IO[index3].pump_delay_off = PUMP_DELAY_OFF_3; // Set the pump delay off to the next value
                                }
                            }                        
                            index2 = 0;                                         // Reset the DIPxSWT switch back to idle
                            index3 = !index3;                                   // Check next time the other pump settings input
                        }
                        break;

        default     :   break;
    }

}