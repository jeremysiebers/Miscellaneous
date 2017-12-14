#include "main.h"
#include "executer.h"
#include <stdio.h>
#include <stdlib.h>
#include <p18F4455.h>

#define Finished -1
#define Busy 0

char Effect_Prog(unsigned char Prog, unsigned char Led);
char Effect_Prog0(unsigned char Led);
char Effect_Prog1(unsigned char Led);
char Effect_Prog2(unsigned char Led);
char Effect_Prog3(unsigned char Led);
char Effect_Prog4(unsigned char Led);
char EXECUTExEFFECT(unsigned char Active_Kolum);
void UPDATExLEDSTAT(unsigned char Kolum_Selector);

enum
{
    Prog0,Prog1,Prog2,Prog3,Prog4
};

/******************************************************************************/
/*          GLOBAL VARIABLES                                                  */
/******************************************************************************/


typedef struct
{
    unsigned char Led;
    unsigned char Prog:3;
    unsigned char Speed;

}LEDBIT;

#pragma idata main_struct1
LEDBIT Led_Bit[48] =        {{0,1,10},{0,1,33},{0,1,47},{0,1,17},{0,1,15},{0,1,5},{0,1,25},{0,1,39},
                             {0,1,5},{0,1,17},{0,1,15},{0,1,39},{0,1,33},{0,1,10},{0,1,47},{0,1,25},
                             {0,1,33},{0,1,25},{0,1,10},{0,1,5},{0,1,47},{0,1,17},{0,1,39},{0,1,15},
                             {0,1,25},{0,1,39},{0,1,47},{0,1,15},{0,1,10},{0,1,5},{0,1,17},{0,1,33},
                             {0,1,47},{0,1,10},{0,1,17},{0,1,33},{0,1,5},{0,1,15},{0,1,39},{0,1,25},
                             {0,1,39},{0,1,15},{0,1,5},{0,1,17},{0,1,25},{0,1,47},{0,1,33},{0,1,10}};


//                             {{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
//                             {0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
//                             {0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
//                             {0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
//                             {0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
//                             {0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0}};

//                             {{0,4,60},{0,4,60},{0,4,60},{0,4,60},{0,4,60},{0,4,60},{0,4,60},{0,4,60},
//                             {0,3,60},{0,3,60},{0,3,60},{0,3,60},{0,3,60},{0,3,60},{0,3,60},{0,3,60},
//                             {0,3,60},{0,4,60},{0,4,60},{0,4,60},{0,4,60},{0,4,60},{0,4,60},{0,4,60},
//                             {0,3,60},{0,3,60},{0,3,60},{0,3,60},{0,3,60},{0,3,60},{0,3,60},{0,3,60},
//                             {0,4,60},{0,4,60},{0,4,60},{0,3,60},{0,4,60},{0,4,60},{0,4,60},{0,4,60},
//                             {0,3,60},{0,3,60},{0,3,60},{0,3,60},{0,3,60},{0,3,60},{0,3,60},{0,3,60}};

//                             {{0,4,40},{0,4,33},{0,4,47},{0,4,47},{0,4,45},{0,4,5},{0,4,25},{0,4,39},
//                             {0,3,5},{0,3,47},{0,3,45},{0,3,39},{0,3,33},{0,3,40},{0,3,47},{0,3,25},
//                             {0,3,33},{0,4,25},{0,4,40},{0,4,5},{0,4,47},{0,4,47},{0,4,39},{0,4,45},
//                             {0,3,25},{0,3,39},{0,3,47},{0,3,45},{0,3,40},{0,3,5},{0,3,47},{0,3,33},
//                             {0,4,47},{0,4,40},{0,4,47},{0,3,33},{0,4,5},{0,4,45},{0,4,39},{0,4,25},
//                             {0,3,39},{0,3,45},{0,3,5},{0,3,47},{0,3,25},{0,3,47},{0,3,33},{0,3,40}};

//                             {{0,1,10},{0,1,33},{0,1,47},{0,1,17},{0,1,15},{0,1,5},{0,1,25},{0,1,39},
//                             {0,1,5},{0,1,17},{0,1,15},{0,1,39},{0,1,33},{0,1,10},{0,1,47},{0,1,25},
//                             {0,1,33},{0,1,25},{0,1,10},{0,1,5},{0,1,47},{0,1,17},{0,1,39},{0,1,15},
//                             {0,1,25},{0,1,39},{0,1,47},{0,1,15},{0,1,10},{0,1,5},{0,1,17},{0,1,33},
//                             {0,1,47},{0,1,10},{0,1,17},{0,1,33},{0,1,5},{0,1,15},{0,1,39},{0,1,25},
//                             {0,1,39},{0,1,15},{0,1,5},{0,1,17},{0,1,25},{0,1,47},{0,1,33},{0,1,10}};

//                            {{0,1,75},{0,1,75},{0,1,75},{0,1,75},{0,1,75},{0,1,75},{0,1,75},{0,1,75},
//                            {0,1,75},{0,1,75},{0,1,75},{0,1,75},{0,1,75},{0,1,75},{0,1,75},{0,1,75},
//                            {0,1,75},{0,1,75},{0,1,75},{0,1,75},{0,1,75},{0,1,75},{0,1,75},{0,1,75},
//                            {0,1,75},{0,1,75},{0,1,75},{0,1,75},{0,1,75},{0,1,75},{0,1,75},{0,1,75},
//                            {0,1,75},{0,1,75},{0,1,75},{0,1,75},{0,1,75},{0,1,75},{0,1,75},{0,1,75},
//                            {0,1,75},{0,1,75},{0,1,75},{0,1,75},{0,1,75},{0,1,75},{0,1,75},{0,1,75}};
#pragma idata


/******************************************************************************/
/*          LOCAL VARIABLES                                                   */
/******************************************************************************/

typedef struct
{
    unsigned char bla:4;
    unsigned char Prog_State:4;
    unsigned char Iteration;
}PROGBIT;

#pragma idata main_struct2
static PROGBIT Prog_Bit[48] = {{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
                               {0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
                               {0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
                               {0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
                               {0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
                               {0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0}};
#pragma idata

#pragma idata main_struct3
unsigned int Illumination[48] = {0,0,0,0,0,0,0,0,0,0,
                                      0,0,0,0,0,0,0,0,0,0,
                                      0,0,0,0,0,0,0,0,0,0,
                                      0,0,0,0,0,0,0,0,0,0,
                                      0,0,0,0,0,0,0,0};
#pragma

#pragma idata main_struct4
unsigned char Illumination_ptr[48] = {0,0,0,0,0,0,0,0,0,0,
                                          0,0,0,0,0,0,0,0,0,0,
                                          0,0,0,0,0,0,0,0,0,0,
                                          0,0,0,0,0,0,0,0,0,0,
                                          0,0,0,0,0,0,0,0};
#pragma

static unsigned char x = 0;
static char Return_Val = Busy;

char EXECUTExEFFECT(unsigned char Active_Kolum)
{
    Return_Val = Busy;
    
    switch(Active_Kolum)
    {
        case    0   :   for(x=0;x<8;x++)
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
    switch (Prog)
    {
        case    Prog0   :   return(Effect_Prog0(Led));
                            break;

        case    Prog1   :   return(Effect_Prog1(Led));
                            break;

        case    Prog2   :   return(Effect_Prog2(Led));
                            break;

        case    Prog3   :   return(Effect_Prog3(Led));
                            break;

        case    Prog4   :   return(Effect_Prog4(Led));
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
    Led_Bit[Led].Led = OFF;
    return(Finished);
}

/******************************************************************************/
/*          Program 1 Led slow on - slow off                                  */
/******************************************************************************/
char Effect_Prog1(unsigned char Led)
{
    char Return_Val = Busy;

    switch (Prog_Bit[Led].Prog_State)
    {
        case    0   :   Prog_Bit[Led].Iteration = 0;                            // Program init state
                        Illumination[Led] = 0;                                  // Set Illumination reg to 0
                        Prog_Bit[Led].Prog_State = 1;                           // Goto next program state
                        Return_Val = Busy;
                        break;

        case    1   :   Prog_Bit[Led].Iteration++;
                        if (Illumination[Led] > Row_Update_Cnt)                 // When leds is 100% on goto off program part
                        {
                            Prog_Bit[Led].Iteration = 0;
                            Prog_Bit[Led].Prog_State = 2;
                            Return_Val = Finished;
                            break;
                        }
                        if (Prog_Bit[Led].Iteration > Led_Bit[Led].Speed)       // When updates is equal to Speed setting then make Led bit On in illumination reg
                        {
                            Prog_Bit[Led].Iteration = 0;
                            Illumination[Led] = Illumination[Led] << 1;
                            Illumination[Led] |= 1;                           
                            Prog_Bit[Led].Prog_State = 1;
                            Return_Val = Finished;
                            break;
                        }
                        Return_Val = Finished;
                        break;

        case    2   :   Prog_Bit[Led].Iteration++;
                        if (Illumination[Led] < 0x1)                       // When leds is 0% on goto off program part
                        {
                            Prog_Bit[Led].Iteration = 0;
                            Prog_Bit[Led].Prog_State = 1;
                            Return_Val = Finished;
                            break;
                        }
                        if (Prog_Bit[Led].Iteration > Led_Bit[Led].Speed)       // When updates is equal to Speed setting then make Led bit On in illumination reg
                        {
                            Prog_Bit[Led].Iteration = 0;
                            Illumination[Led] = Illumination[Led] >> 1;
                            Prog_Bit[Led].Prog_State = 2;
                            Return_Val = Finished;
                            break;
                        }
                        Return_Val = Finished;
                        break;

        default     :   Prog_Bit[Led].Prog_State = 0;

    }

    Illumination_ptr[Led] = 1;
    Illumination_ptr[Led] = Illumination_ptr[Led] << (Row_Updater - 1);
    Led_Bit[Led].Led = (Illumination[Led] & Illumination_ptr[Led]) >> (Row_Updater - 1);

    return(Return_Val);
}

/******************************************************************************/
/*          Program 2 Led Blinking                                            */
/******************************************************************************/
char Effect_Prog2(unsigned char Led)
{
    char Return_Val = Busy;

    switch (Prog_Bit[Led].Prog_State)
    {
        case    0   :   Prog_Bit[Led].Iteration = 0;                            // Program init state
                        Illumination[Led] = ON;                                 // Set Illumination reg to 100% on
                        Prog_Bit[Led].Prog_State = 1;                           // Goto next program state
                        Return_Val = Busy;
                        break;

        case    1   :   Prog_Bit[Led].Iteration++;
                        if (Prog_Bit[Led].Iteration > Led_Bit[Led].Speed)       // When updates is equal to Speed setting then make Led bit On in illumination reg
                        {
                            Prog_Bit[Led].Iteration = 0;
                            Illumination[Led] = !Illumination[Led];
                            //Illumination[Led] |= 1;
                            Prog_Bit[Led].Prog_State = 1;
                            Return_Val = Finished;
                            break;
                        }
                        Return_Val = Finished;
                        break;

        default     :   Prog_Bit[Led].Prog_State = 0;

    }

    Led_Bit[Led].Led = Illumination[Led];

    return(Return_Val);
}

/******************************************************************************/
/*          Program 3 Led slow on - on                                        */
/******************************************************************************/
char Effect_Prog3(unsigned char Led)
{
    char Return_Val = Busy;

    switch (Prog_Bit[Led].Prog_State)
    {
        case    0   :   Prog_Bit[Led].Iteration = 0;                            // Program init state
                        Illumination[Led] = 0;                                  // Set Illumination reg to 0
                        Prog_Bit[Led].Prog_State = 1;                           // Goto next program state
                        Return_Val = Busy;
                        break;

        case    1   :   Prog_Bit[Led].Iteration++;
                        if (Illumination[Led] > Row_Update_Cnt)                 // When leds is 100% on keep on
                        {
                            Prog_Bit[Led].Iteration = 0;
                            Prog_Bit[Led].Prog_State = 1;
                            Return_Val = Finished;
                            break;
                        }
                        if (Prog_Bit[Led].Iteration > Led_Bit[Led].Speed)       // When updates is equal to Speed setting then make Led bit On in illumination reg
                        {
                            Prog_Bit[Led].Iteration = 0;
                            Illumination[Led] = Illumination[Led] << 1;
                            Illumination[Led] |= 1;
                            Prog_Bit[Led].Prog_State = 1;
                            Return_Val = Finished;
                            break;
                        }
                        Return_Val = Finished;
                        break;

        default     :   Prog_Bit[Led].Prog_State = 0;

    }

    Illumination_ptr[Led] = 1;
    Illumination_ptr[Led] = Illumination_ptr[Led] << (Row_Updater - 1);
    Led_Bit[Led].Led = (Illumination[Led] & Illumination_ptr[Led]) >> (Row_Updater - 1);

    return(Return_Val);
}

/******************************************************************************/
/*          Program 4 Led on slow off                                         */
/******************************************************************************/
char Effect_Prog4(unsigned char Led)
{
    char Return_Val = Busy;

    switch (Prog_Bit[Led].Prog_State)
    {
        case    0   :   Prog_Bit[Led].Iteration = 0;                            // Program init state
                        Illumination[Led] = 0xFFFF;                             // Set Illumination reg to 100%
                        Prog_Bit[Led].Prog_State = 1;                           // Goto next program state
                        Return_Val = Busy;
                        break;

        case    1   :   Prog_Bit[Led].Iteration++;
                        if (Illumination[Led] < 0x1)                            // When leds is 0% on goto off program part
                        {
                            Prog_Bit[Led].Iteration = 0;
                            Prog_Bit[Led].Prog_State = 1;                       // When leds is 100% off keep off
                            Return_Val = Finished;
                            break;
                        }
                        if (Prog_Bit[Led].Iteration > Led_Bit[Led].Speed)       // When updates is equal to Speed setting then make Led bit On in illumination reg
                        {
                            Prog_Bit[Led].Iteration = 0;
                            Illumination[Led] = Illumination[Led] >> 1;
                            Prog_Bit[Led].Prog_State = 1;
                            Return_Val = Finished;
                            break;
                        }
                        Return_Val = Finished;
                        break;

        default     :   Prog_Bit[Led].Prog_State = 0;

    }

    Illumination_ptr[Led] = 1;
    Illumination_ptr[Led] = Illumination_ptr[Led] << (Row_Updater - 1);
    Led_Bit[Led].Led = (Illumination[Led] & Illumination_ptr[Led]) >> (Row_Updater - 1);

    return(Return_Val);
}

/******************************************************************************/
/*          Update the LED output array with new value                        */
/******************************************************************************/
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