#include "termostat.h"
#include "main.h"

#define DEBOUNCE_VAL 2                                                          // After 3 times high then termostat is high

typedef struct
{
	unsigned char 	termostat_io,						// The real io status of a input
                        termostat_actual,
                        termostat_counter;
}INPUT_VAR;

static INPUT_VAR TERMOSTAT_IO[12] = {{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
                                    {0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0}};

static unsigned char index = 0;


void  TERMOSTATxUPDATE()							// Update tick from cv_controller
{
    TERMOSTAT_IO[0].termostat_io = term0;					// Copy io status to termostat_io
    TERMOSTAT_IO[1].termostat_io = term1;
    TERMOSTAT_IO[2].termostat_io = term2;
    TERMOSTAT_IO[3].termostat_io = term3;
    TERMOSTAT_IO[4].termostat_io = term4;
    TERMOSTAT_IO[5].termostat_io = term5;
    TERMOSTAT_IO[6].termostat_io = term6;
    TERMOSTAT_IO[7].termostat_io = term7;
    TERMOSTAT_IO[8].termostat_io = term8;
    TERMOSTAT_IO[9].termostat_io = term9;
    TERMOSTAT_IO[10].termostat_io = term10;
    TERMOSTAT_IO[11].termostat_io = term11;
    
    for (index = 0; index < 12; index++)					// Check 12 times for each valve if the variable may be updated
    {
        if (TERMOSTAT_IO[index].termostat_actual == TERMOSTAT_IO[index].termostat_io) // If there is no difference between the actual and the real io value
        {
             TERMOSTAT_IO[index].termostat_counter = 0;				// then no change is required and the debounce counter is reset
        }
        else
        {
             TERMOSTAT_IO[index].termostat_counter++;				// When a termostat input has changed increment the debounce counter 
             if (TERMOSTAT_IO[index].termostat_counter > DEBOUNCE_VAL)		// Verify if the changed value has occured "DEBOUNCE_VAL" times
             {
                 TERMOSTAT_IO[index].termostat_actual = TERMOSTAT_IO[index].termostat_io; // then make the actual variable equal to the io value
                 TERMOSTAT_IO[index].termostat_counter = 0;			// reset the debounce counter
             }
        }
   }
}

unsigned char TERMOSTATxACTUAL(unsigned char INDEX)
{
    return TERMOSTAT_IO[INDEX].termostat_actual;				// Return to the application the actual valve status
}