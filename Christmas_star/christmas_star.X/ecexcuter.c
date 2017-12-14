#include "main.h"
#include "executer.h"

char Effect_Prog(unsigned char Prog, unsigned char Led);
char Effect_Prog0(unsigned char Led);
char Effect_Prog1(unsigned char Led);
char Effect_Prog2(unsigned char Led);
char Effect_Prog3(unsigned char Led);
char Effect_Prog4(unsigned char Led);
char Effect_Prog5(unsigned char Led);
char EXECUTExEFFECT(unsigned char Active_Kolum);
void UPDATExLEDSTAT(unsigned char Kolum_Selector);

enum
{
    Prog0,Prog1,Prog2,Prog3,Prog4,Prog5                                         // enumeration for different program cases
};

/******************************************************************************/
/*          GLOBAL VARIABLES                                                  */
/******************************************************************************/


typedef struct
{
    unsigned char Led;                                                          // Holds the value to be for a Led
    unsigned char Prog:3;                                                       // Program to run on a selected Led
    unsigned char Speed;                                                        // setting on how fast to change a led on time, should be lower than 254

    unsigned char Prog_State:4;                                                 // Memory to hold a actual program status
    unsigned char Iteration;                                                    // Counter to flow over Speed setting

}LEDBIT;

#pragma idata main_struct1
LEDBIT Led_Bit[48] =        {{0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0},
                             {0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0},
                             {0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0},
                             {0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0},
                             {0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0},
                             {0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0}};


//                            {{0,2,20,0,0},{0,2,33,0,0},{0,2,47,0,0},{0,2,27,0,0},{0,2,25,0,0},{0,2,5,0,0},{0,2,25,0,0},{0,2,39,0,0},
//                             {0,2,5,0,0},{0,2,27,0,0},{0,2,25,0,0},{0,2,39,0,0},{0,2,33,0,0},{0,2,20,0,0},{0,2,47,0,0},{0,2,25,0,0},
//                             {0,2,33,0,0},{0,2,25,0,0},{0,2,20,0,0},{0,2,5,0,0},{0,2,47,0,0},{0,2,27,0,0},{0,2,39,0,0},{0,2,25,0,0},
//                             {0,2,25,0,0},{0,2,39,0,0},{0,2,47,0,0},{0,2,25,0,0},{0,2,20,0,0},{0,2,5,0,0},{0,2,27,0,0},{0,2,33,0,0},
//                             {0,2,47,0,0},{0,2,20,0,0},{0,2,27,0,0},{0,2,33,0,0},{0,2,5,0,0},{0,2,25,0,0},{0,2,39,0,0},{0,2,25,0,0},
//                             {0,2,39,0,0},{0,2,25,0,0},{0,2,5,0,0},{0,2,27,0,0},{0,2,25,0,0},{0,2,47,0,0},{0,2,33,0,0},{0,2,20,0,0}};

//                            {{0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0},
//                             {0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0},
//                             {0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0},
//                             {0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0},
//                             {0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0},
//                             {0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0}};

#pragma idata

#pragma idata main_struct2
unsigned char Illumination[48] = {0,0,0,0,0,0,0,0,0,0,                          // This variable holds the 8 bit illumination value for all leds
                                      0,0,0,0,0,0,0,0,0,0,                      // when a led is 0% lid, the value is 0
                                      0,0,0,0,0,0,0,0,0,0,                      // When a led is 100% lid, the value is 255
                                      0,0,0,0,0,0,0,0,0,0,
                                      0,0,0,0,0,0,0,0};
#pragma idata

/******************************************************************************/
/*          LOCAL VARIABLES                                                   */
/******************************************************************************/

#pragma idata main_struct3
unsigned char Illumination_ptr[48] = {0,0,0,0,0,0,0,0,0,0,                      // This variable holds the pointer value to which bit in the Illumination[x]
                                          0,0,0,0,0,0,0,0,0,0,                  // must be updated and put out als value to be shown on a selected led
                                          0,0,0,0,0,0,0,0,0,0,
                                          0,0,0,0,0,0,0,0,0,0,
                                          0,0,0,0,0,0,0,0};
#pragma idata

static unsigned char x = 0;
static char Return_Val = Busy;

char EXECUTExEFFECT(unsigned char Active_Kolum)
{
    Return_Val = Busy;                                                          // set report default to busy, override in case of finished
    
    switch(Active_Kolum)
    {
        case    0   :   for(x=0;x<8;x++)                                        // When first kolum is active, update all the led values in Led_Bit[x].Led accordingly
                        {
                            Return_Val += Effect_Prog(Led_Bit[x].Prog, x);      // Add al return values, call the program that was set for this led
                        }
                        if(Return_Val <= -8)                                    // when value is lower or equal to -8 all sub routines are finished
                        {
                            Return_Val = Finished;                              // Return finished
                        }
                        else                                                    // when a subroutine is still busy, this subroutine will be called again until finished is reported back
                        {
                            Return_Val = Busy;
                        }
                        break;
        case    1   :   for(x=8;x<16;x++)
                        {
                            Return_Val += Effect_Prog(Led_Bit[x].Prog, x);
                        }
                        if(Return_Val <= -8)
                        {
                            Return_Val = Finished;
                        }
                        else
                        {
                            Return_Val = Busy;
                        }
                        break;
        case    2   :   for(x=16;x<24;x++)
                        {
                            Return_Val += Effect_Prog(Led_Bit[x].Prog, x);
                        }
                        if(Return_Val <= -8)
                        {
                            Return_Val = Finished;
                        }
                        else
                        {
                            Return_Val = Busy;
                        }
                        break;
        case    3   :   for(x=24;x<32;x++)
                        {
                            Return_Val += Effect_Prog(Led_Bit[x].Prog, x);
                        }
                        if(Return_Val <= -8)
                        {
                            Return_Val = Finished;
                        }
                        else
                        {
                            Return_Val = Busy;
                        }
                        break;
        case    4   :   for(x=32;x<40;x++)
                        {
                            Return_Val += Effect_Prog(Led_Bit[x].Prog, x);
                        }
                        if(Return_Val <= -8)
                        {
                            Return_Val = Finished;
                        }
                        else
                        {
                            Return_Val = Busy;
                        }
                        break;
        case    5   :   for(x=40;x<48;x++)
                        {
                            Return_Val += Effect_Prog(Led_Bit[x].Prog, x);
                        }
                        if(Return_Val <= -8)
                        {
                            Return_Val = Finished;
                        }
                        else
                        {
                            Return_Val = Busy;
                        }
                        break;

        default     :   break;
    }

    return(Return_Val);
    
}

char Effect_Prog(unsigned char Prog, unsigned char Led)
{
    switch (Prog)                                                               // Start the selected program for the pointed led
    {
        case    Prog0   :   return(Effect_Prog0(Led));                          // return also the status of the subroutine that is called
                            break;

        case    Prog1   :   return(Effect_Prog1(Led));
                            break;

        case    Prog2   :   return(Effect_Prog2(Led));
                            break;

        case    Prog3   :   return(Effect_Prog3(Led));
                            break;

        case    Prog4   :   return(Effect_Prog4(Led));
                            break;

        case    Prog5   :   return(Effect_Prog5(Led));
                            break;
            
        default         :
                            break;

    }

}

/******************************************************************************/
/*          Program 0 = Led off                                               */
/******************************************************************************/
char Effect_Prog0(unsigned char Led)
{
    Led_Bit[Led].Led = OFF;                                                     // Set led bit to off and all associated reg
    Led_Bit[Led].Speed = OFF;
    Led_Bit[Led].Prog_State = OFF;
    Led_Bit[Led].Iteration = OFF;
    Illumination[Led] = OFF;
    return(Finished);
}

/******************************************************************************/
/*          Program 1 = Led on                                               */
/******************************************************************************/
char Effect_Prog1(unsigned char Led)
{
    Led_Bit[Led].Led = ON;                                                      // Set led bit to on
    return(Finished);
}

/******************************************************************************/
/*          Program 2 Led slow on - slow off - slow on                        */
/******************************************************************************/
char Effect_Prog2(unsigned char Led)
{
    char Return_Val = Busy;

    switch (Led_Bit[Led].Prog_State)
    {
        case    0   :   Led_Bit[Led].Iteration = 0;                             // Program init state
                        Illumination[Led] = 0;                                  // Set Illumination reg to 0
                        Led_Bit[Led].Prog_State = 1;                            // Goto next program state
                        Return_Val = Busy;                                      // let caller know that routine is not ready yet
                        break;

        case    1   :   Led_Bit[Led].Iteration++;                               // increment iteration counter
                        if (Illumination[Led] > ROW_UPDATE_CNT)                 // When leds is 100% on goto off program part
                        {
                            Led_Bit[Led].Iteration = 1;                         // pre-set the iteration counter to 1 because 1 cycle is missed by switching to the other case
                            Led_Bit[Led].Prog_State = 2;                        // Go next time dimm the led
                            Return_Val = Finished;
                            break;
                        }
                        if (Led_Bit[Led].Iteration > Led_Bit[Led].Speed)        // When updates is equal to Speed setting then make Led bit On in illumination reg
                        {
                            Led_Bit[Led].Iteration = 0;                         // restet iteration counter
                            Illumination[Led] = Illumination[Led] << 1;         // shift the value of the illumination reg 1 to the left
                            Illumination[Led] |= 1;                             // add a 1 into the illumination value, by adding this 1 the "ON" time for the selected led is increased by 1/8
                            Led_Bit[Led].Prog_State = 1;                        // keep in this program state
                            Return_Val = Finished;                              // return that execution is finished for this update period of timer1
                            break;
                        }
                        Return_Val = Finished;
                        break;

        case    2   :   Led_Bit[Led].Iteration++;
                        if (Illumination[Led] < 0x1)                            // When leds is 0% on goto off program part
                        {
                            Led_Bit[Led].Iteration = 1;
                            Led_Bit[Led].Prog_State = 1;
                            Return_Val = Finished;
                            break;
                        }
                        if (Led_Bit[Led].Iteration > Led_Bit[Led].Speed)        // When updates is equal to Speed setting then make Led bit On in illumination reg
                        {
                            Led_Bit[Led].Iteration = 0;
                            Illumination[Led] = Illumination[Led] >> 1;
                            Led_Bit[Led].Prog_State = 2;
                            Return_Val = Finished;
                            break;
                        }
                        Return_Val = Finished;
                        break;

        default     :   Led_Bit[Led].Prog_State = 0;

    }

    Illumination_ptr[Led] = 1;                                                  // after every period update of timer1, update the Led_Bit[x].Led value with the actual update counter Row_Updater which runs from 0 to 7
    Illumination_ptr[Led] = Illumination_ptr[Led] << (Row_Updater - 1);         // In order to point to the correct actual state of timer1 (Row_Updater) shift the pointer 1 value as much as the value of Row_Updater -1
    Led_Bit[Led].Led = (Illumination[Led] & Illumination_ptr[Led]) >> (Row_Updater - 1); // if the pointed bit in Illumination[x] by Illumination_ptr is 1, then the Led_Bit[x] = 1

    return(Return_Val);
}

/******************************************************************************/
/*          Program 3 Led Blinking                                            */
/******************************************************************************/
char Effect_Prog3(unsigned char Led)
{
    char Return_Val = Busy;

    switch (Led_Bit[Led].Prog_State)
    {
        case    0   :   Led_Bit[Led].Iteration = 0;                             // Program init state
                        Illumination[Led] = ON;                                 // Set Illumination reg to 100% on
                        Led_Bit[Led].Prog_State = 1;                            // Goto next program state
                        Return_Val = Busy;
                        break;

        case    1   :   Led_Bit[Led].Iteration++;
                        if (Led_Bit[Led].Iteration > Led_Bit[Led].Speed)        // When updates is equal to Speed setting then make Led bit On in illumination reg
                        {
                            Led_Bit[Led].Iteration = 0;
                            Illumination[Led] = !Illumination[Led];             // toggle the last status of the current selected led
                            Led_Bit[Led].Prog_State = 1;
                            Return_Val = Finished;
                            break;
                        }
                        Return_Val = Finished;
                        break;

        default     :   Led_Bit[Led].Prog_State = 0;

    }

    Led_Bit[Led].Led = Illumination[Led];                                       // Blinking a led is to set the whole period to ON or OFF, no PWM

    return(Return_Val);
}

/******************************************************************************/
/*          Program 4 Led off - slow on                                       */
/******************************************************************************/
char Effect_Prog4(unsigned char Led)
{
    char Return_Val = Busy;

    switch (Led_Bit[Led].Prog_State)
    {
        case    0   :   Led_Bit[Led].Iteration = 0;                             // Program init state
                        Illumination[Led] = 0;                                  // Set Illumination reg to 0
                        Led_Bit[Led].Prog_State = 1;                            // Goto next program state
                        Return_Val = Busy;
                        break;

        case    1   :   Led_Bit[Led].Iteration++;
                        if (Illumination[Led] > ROW_UPDATE_CNT)                 // When leds is 100% on keep on
                        {
                            Led_Bit[Led].Iteration = 0;
                            Led_Bit[Led].Prog_State = 1;
                            Return_Val = Finished;
                            break;
                        }
                        if (Led_Bit[Led].Iteration > Led_Bit[Led].Speed)        // When updates is equal to Speed setting then make Led bit On in illumination reg
                        {
                            Led_Bit[Led].Iteration = 0;
                            Illumination[Led] = Illumination[Led] << 1;
                            Illumination[Led] |= 1;
                            Led_Bit[Led].Prog_State = 1;
                            Return_Val = Finished;
                            break;
                        }
                        Return_Val = Finished;
                        break;

        default     :   Led_Bit[Led].Prog_State = 0;

    }

    Illumination_ptr[Led] = 1;
    Illumination_ptr[Led] = Illumination_ptr[Led] << (Row_Updater - 1);
    Led_Bit[Led].Led = (Illumination[Led] & Illumination_ptr[Led]) >> (Row_Updater - 1);

    return(Return_Val);
}

/******************************************************************************/
/*          Program 5 Led on - slow off                                       */
/******************************************************************************/
char Effect_Prog5(unsigned char Led)
{
    char Return_Val = Busy;

    switch (Led_Bit[Led].Prog_State)
    {
        case    0   :   Led_Bit[Led].Iteration = 0;                             // Program init state
                        Illumination[Led] = ROW_UPDATE_CNT;                     // Set Illumination reg to 100%
                        Led_Bit[Led].Prog_State = 1;                            // Goto next program state
                        Return_Val = Busy;
                        break;

        case    1   :   Led_Bit[Led].Iteration++;
                        if (Illumination[Led] < 0x1)                            // When leds is 0% on goto off program part
                        {
                            Led_Bit[Led].Iteration = 0;
                            Led_Bit[Led].Prog_State = 1;                       // When leds is 100% off keep off
                            Return_Val = Finished;
                            break;
                        }
                        if (Led_Bit[Led].Iteration > Led_Bit[Led].Speed)       // When updates is equal to Speed setting then make Led bit On in illumination reg
                        {
                            Led_Bit[Led].Iteration = 0;
                            Illumination[Led] = Illumination[Led] >> 1;
                            Led_Bit[Led].Prog_State = 1;
                            Return_Val = Finished;
                            break;
                        }
                        Return_Val = Finished;
                        break;

        default     :   Led_Bit[Led].Prog_State = 0;

    }

    Illumination_ptr[Led] = 1;
    Illumination_ptr[Led] = Illumination_ptr[Led] << (Row_Updater - 1);
    Led_Bit[Led].Led = (Illumination[Led] & Illumination_ptr[Led]) >> (Row_Updater - 1);

    return(Return_Val);
}

/******************************************************************************/
/*          Update the LED output array with new value                        */
/******************************************************************************/
/*
 * This program is executed when the group of 8 leds from the EXECUTExEFFECT routine is finished.
 * The new calculated values of Led_Bit[x] are put into the Led array for the selected kolum which is active
 * There are only 44 leds connected on the Star, even though all 48 leds are set.
 *
*/
void UPDATExLEDSTAT(unsigned char Kolum_Selector)
{
    switch(Kolum_Selector)
    {
        case    0   :   Led[Kolum_Selector] = OFF;
                        Led[Kolum_Selector] = Led[Kolum_Selector] | Led_Bit[7].Led;
                        Led[Kolum_Selector] = (Led[Kolum_Selector] << 1) | Led_Bit[6].Led;
                        Led[Kolum_Selector] = (Led[Kolum_Selector] << 1) | Led_Bit[5].Led;
                        Led[Kolum_Selector] = (Led[Kolum_Selector] << 1) | Led_Bit[4].Led;
                        Led[Kolum_Selector] = (Led[Kolum_Selector] << 1) | Led_Bit[3].Led;
                        Led[Kolum_Selector] = (Led[Kolum_Selector] << 1) | Led_Bit[2].Led;
                        Led[Kolum_Selector] = (Led[Kolum_Selector] << 1) | Led_Bit[1].Led;
                        Led[Kolum_Selector] = (Led[Kolum_Selector] << 1) | Led_Bit[0].Led;
                        break;

        case    1   :   Led[Kolum_Selector] = OFF;
                        Led[Kolum_Selector] = Led[Kolum_Selector] | Led_Bit[15].Led;
                        Led[Kolum_Selector] = (Led[Kolum_Selector] << 1) | Led_Bit[14].Led;
                        Led[Kolum_Selector] = (Led[Kolum_Selector] << 1) | Led_Bit[13].Led;
                        Led[Kolum_Selector] = (Led[Kolum_Selector] << 1) | Led_Bit[12].Led;
                        Led[Kolum_Selector] = (Led[Kolum_Selector] << 1) | Led_Bit[11].Led;
                        Led[Kolum_Selector] = (Led[Kolum_Selector] << 1) | Led_Bit[10].Led;
                        Led[Kolum_Selector] = (Led[Kolum_Selector] << 1) | Led_Bit[9].Led;
                        Led[Kolum_Selector] = (Led[Kolum_Selector] << 1) | Led_Bit[8].Led;
                        break;

        case    2   :   Led[Kolum_Selector] = OFF;
                        Led[Kolum_Selector] = Led[Kolum_Selector] | Led_Bit[23].Led;
                        Led[Kolum_Selector] = (Led[Kolum_Selector] << 1) | Led_Bit[22].Led;
                        Led[Kolum_Selector] = (Led[Kolum_Selector] << 1) | Led_Bit[21].Led;
                        Led[Kolum_Selector] = (Led[Kolum_Selector] << 1) | Led_Bit[20].Led;
                        Led[Kolum_Selector] = (Led[Kolum_Selector] << 1) | Led_Bit[19].Led;
                        Led[Kolum_Selector] = (Led[Kolum_Selector] << 1) | Led_Bit[18].Led;
                        Led[Kolum_Selector] = (Led[Kolum_Selector] << 1) | Led_Bit[17].Led;
                        Led[Kolum_Selector] = (Led[Kolum_Selector] << 1) | Led_Bit[16].Led;
                        break;

        case    3   :   Led[Kolum_Selector] = OFF;
                        Led[Kolum_Selector] = Led[Kolum_Selector] | Led_Bit[31].Led;
                        Led[Kolum_Selector] = (Led[Kolum_Selector] << 1) | Led_Bit[30].Led;
                        Led[Kolum_Selector] = (Led[Kolum_Selector] << 1) | Led_Bit[29].Led;
                        Led[Kolum_Selector] = (Led[Kolum_Selector] << 1) | Led_Bit[28].Led;
                        Led[Kolum_Selector] = (Led[Kolum_Selector] << 1) | Led_Bit[27].Led;
                        Led[Kolum_Selector] = (Led[Kolum_Selector] << 1) | Led_Bit[26].Led;
                        Led[Kolum_Selector] = (Led[Kolum_Selector] << 1) | Led_Bit[25].Led;
                        Led[Kolum_Selector] = (Led[Kolum_Selector] << 1) | Led_Bit[24].Led;
                        break;

        case    4   :   Led[Kolum_Selector] = OFF;
                        Led[Kolum_Selector] = Led[Kolum_Selector] | Led_Bit[39].Led;
                        Led[Kolum_Selector] = (Led[Kolum_Selector] << 1) | Led_Bit[38].Led;
                        Led[Kolum_Selector] = (Led[Kolum_Selector] << 1) | Led_Bit[37].Led;
                        Led[Kolum_Selector] = (Led[Kolum_Selector] << 1) | Led_Bit[36].Led;
                        Led[Kolum_Selector] = (Led[Kolum_Selector] << 1) | Led_Bit[35].Led;
                        Led[Kolum_Selector] = (Led[Kolum_Selector] << 1) | Led_Bit[34].Led;
                        Led[Kolum_Selector] = (Led[Kolum_Selector] << 1) | Led_Bit[33].Led;
                        Led[Kolum_Selector] = (Led[Kolum_Selector] << 1) | Led_Bit[32].Led;
                        break;

        case    5   :   Led[Kolum_Selector] = OFF;
                        Led[Kolum_Selector] = Led[Kolum_Selector] | Led_Bit[47].Led;
                        Led[Kolum_Selector] = (Led[Kolum_Selector] << 1) | Led_Bit[46].Led;
                        Led[Kolum_Selector] = (Led[Kolum_Selector] << 1) | Led_Bit[45].Led;
                        Led[Kolum_Selector] = (Led[Kolum_Selector] << 1) | Led_Bit[44].Led;
                        Led[Kolum_Selector] = (Led[Kolum_Selector] << 1) | Led_Bit[43].Led;
                        Led[Kolum_Selector] = (Led[Kolum_Selector] << 1) | Led_Bit[42].Led;
                        Led[Kolum_Selector] = (Led[Kolum_Selector] << 1) | Led_Bit[41].Led;
                        Led[Kolum_Selector] = (Led[Kolum_Selector] << 1) | Led_Bit[40].Led;
                        break;

        default     :   break;
    }
}