#include "main.h"
#include "executer.h"
#include "design_draw_figure.h"

char DESIGNxDRAWxFIGURE(unsigned char Direction, char Group, unsigned char Speed);

/******************************************************************************/
/*          DESIGN DRAW FIGURE Line                                           */
/******************************************************************************/

static unsigned char Draw_Figure = 0;
static unsigned int Draw_Figure_Cnt = 0;
static char x = 0;

char DESIGNxDRAWxFIGURE(unsigned char Direction, char Group, unsigned char Speed)
{
    char Return_Val = Busy;
    switch (Draw_Figure)
    {
        case    0   :   if(FORWARD == Direction)
                        {
                            Draw_Figure = 1;
                        }
                        else if(BACKWARD == Direction)
                        {
                            Draw_Figure = 2;
                        }
                        switch(Group)
                        {
                            case 'A' :  x = 0; break;
                            case 'B' :  x = 8; break;
                            case 'C' :  x = 16; break;
                            case 'D' :  x = 24; break;
                            case 'E' :  x = 32; break;
                            case 'F' :  x = 40; break;

                        }
                        Return_Val = Busy;
                        break;

        case    1   :   Return_Val = Busy;
                        Draw_Figure_Cnt++;
                        if(Draw_Figure_Cnt > Speed * tSEC)
                        {
                            Draw_Figure_Cnt = 0;
                            switch(Group)
                            {
                                case 'A' :  Led_Bit[x].Prog = 1;
                                            x++;
                                            if(x > 7)
                                            {
                                                Return_Val = Finished;
                                                Draw_Figure = 0;
                                            }
                                            break;

                                case 'B' :  Led_Bit[x].Prog = 1;
                                            x++;
                                            if(x > 15)
                                            {
                                                Return_Val = Finished;
                                                Draw_Figure = 0;
                                            }
                                            break;

                                case 'C' :  Led_Bit[x].Prog = 1;
                                            x++;
                                            if(x > 23)
                                            {
                                                Return_Val = Finished;
                                                Draw_Figure = 0;
                                            }
                                            break;

                                case 'D' :  Led_Bit[x].Prog = 1;
                                            x++;
                                            if(x > 31)
                                            {
                                                Return_Val = Finished;
                                                Draw_Figure = 0;
                                            }
                                            break;

                                case 'E' :  Led_Bit[x].Prog = 1;
                                            x++;
                                            if(x > 39)
                                            {
                                                Return_Val = Finished;
                                                Draw_Figure = 0;
                                            }
                                            break;

                                case 'F' :  Led_Bit[x].Prog = 1;
                                            x++;
                                            if(x > 47)
                                            {
                                                Return_Val = Finished;
                                                Draw_Figure = 0;
                                            }
                                            break;

                                default  :  break;
                            }


                        }
                        break;

        case    2   :   Return_Val = Busy;
                        Draw_Figure_Cnt++;
                        if(Draw_Figure_Cnt > Speed * tSEC)
                        {
                            Draw_Figure_Cnt = 0;
                            switch(Group)
                            {
                                case 'A' :  Led_Bit[x].Prog = 0;
                                            x++;
                                            if(x > 7)
                                            {
                                                Return_Val = Finished;
                                                Draw_Figure = 0;
                                            }
                                            break;

                                case 'B' :  Led_Bit[x].Prog = 0;
                                            x++;
                                            if(x > 15)
                                            {
                                                Return_Val = Finished;
                                                Draw_Figure = 0;
                                            }
                                            break;

                                case 'C' :  Led_Bit[x].Prog = 0;
                                            x++;
                                            if(x > 23)
                                            {
                                                Return_Val = Finished;
                                                Draw_Figure = 0;
                                            }
                                            break;

                                case 'D' :  Led_Bit[x].Prog = 0;
                                            x++;
                                            if(x > 31)
                                            {
                                                Return_Val = Finished;
                                                Draw_Figure = 0;
                                            }
                                            break;

                                case 'E' :  Led_Bit[x].Prog = 0;
                                            x++;
                                            if(x > 39)
                                            {
                                                Return_Val = Finished;
                                                Draw_Figure = 0;
                                            }
                                            break;

                                case 'F' :  Led_Bit[x].Prog = 0;
                                            x++;
                                            if(x > 47)
                                            {
                                                Return_Val = Finished;
                                                Draw_Figure = 0;
                                            }
                                            break;

                                default  :  break;
                            }
                        }
                        break;

        default     :   Draw_Figure = 0;
                        break;
    }

    return(Return_Val);
}