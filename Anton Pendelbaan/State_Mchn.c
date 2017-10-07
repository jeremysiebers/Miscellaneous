#include "Main.h"
#include "State_Mchn.h"
#include <xc.h>
#include "api.h"

#define Straight	0
#define Bend		1
#define Left		0
#define Right		1

//#define Start_Move	0
//#define Brake_Move	3


#define ERROR (char)0xEE	// general switch case when error
#define Busy (char)-1
#define Finished (char)0

#define AdjustSpeed 20
  
#define Init 0
#define Run2 1
#define Run1 2

#define RB_LB 0	//drive path presets
#define RB_LF 1
#define RF_LB 2
#define RF_LF 3
#define LB_RB 4
#define LB_RF 5
#define LF_RB 6
#define LF_RF 7

#define LB 0	//to create drive path
#define LF 1
#define RB 2
#define RF 3
#define Middle 4
#define OneTrain 9

#define Blink 2
#define BlinkHz 3000
#define Blink1 3
#define BlinkHz1 1000
#define ActivateControlsTime 10000

#define LMU 1
#define LMD 2
#define RMD 3
#define RMU 4

unsigned char 	Switch_Junction = 0,
				Switch_Train_Move = 0,
				Switch_Main = Init,
				Switch_Main_Old = 0,
				Switch_Program = 0,				
				Switch_Program_Old = 0,
				Switch_Train_Path = 0,
				Switch_Adjust_LB = 0,
				Switch_Adjust_LF = 0,
				Switch_Adjust_RB = 0,
				Switch_Adjust_RF = 0,
				Switch_Init = 0,							
				Switch_Activate_Controls = 0,
                Stop_Program = Off,	
                Reed_Contact_LF_Counter = 0,
				Reed_Contact_LB_Counter = 0,
				Reed_Contact_RF_Counter = 0,
				Reed_Contact_RB_Counter = 0,
				Reed_Contact_LMU_Counter = 0,
				Reed_Contact_LMD_Counter = 0,
				Reed_Contact_RMU_Counter = 0,
				Reed_Contact_RMD_Counter = 0,
				Button_Contact_Counter_Start = 0,
				Button_Contact_Counter_Stop = 0,
				Button_Contact_Counter_Middle = 0,
				Button_Contact_Counter_LB = 0,
				Button_Contact_Counter_LF = 0,
				Button_Contact_Counter_RB = 0,
				Button_Contact_Counter_RF = 0;
				
				
unsigned int	Train_Move_Pwm_Count = 511,
				Train_Move_Pwm_Fast_Count = 0,
				Adjust_Counter = 0,
				Green_Led_Counter = 0,
				Red_Led_Counter = 0,
				Activate_Controls_Counter = 0;


static char Junction(unsigned char Left_Right, unsigned char Straight_Bend);
static char Train_Move_Right_Start(void);
static char Right_Mountain_From_The_Right(unsigned char rc);
static char Left_Mountain_From_The_Right(unsigned char rc);
static char Left_Mountain_From_The_Left(unsigned char rc);
static char Right_Mountain_From_The_Left(unsigned char rc);
static char Train_Move_Right_Brake(void);
static char Train_Move_Left_Start(void);
static char Train_Move_Left_Brake(void);
static char Train_Path(unsigned char From, unsigned char To);
static void Debounce_Inputs(void);
static void Eeprom_Store(void);
static void Green_Led(unsigned char Operation);
static void Red_Led(unsigned char Operation);

/******************************************************************************
 * Function:        void Update_StateMchn(void)
 *                  Main state machine routine
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        None
 *****************************************************************************/
void Update_StateMchn(void)
{
	Debounce_Inputs();
	
	switch (Switch_Main)
			{
				case	Init	:	switch(Switch_Init)
									{
										case	0	:	Green_Led(Off);
														Red_Led(Off);
														Switch_Init = 1;
														break;
														
										case	1	:	if(GETxAPIxVAL(BTN_LB))
														{
															SETxAPIxVAL(TRAIN1_POS, LB);
															Switch_Init = 2;
															break;
														}
														if(GETxAPIxVAL(BTN_LF))
														{
															SETxAPIxVAL(TRAIN1_POS, LF);
															Switch_Init = 2;
															break;
														}
														if(GETxAPIxVAL(BTN_RB))
														{
															SETxAPIxVAL(TRAIN1_POS, RB);
															Switch_Init = 2;
															break;
														}
														if(GETxAPIxVAL(BTN_RF))
														{
															SETxAPIxVAL(TRAIN1_POS, RF);
															Switch_Init = 2;
															break;															
														}
														if(GETxAPIxVAL(BTN_MID))
														{
															SETxAPIxVAL(TRAIN1_POS, Middle);
															Switch_Init = 2;
															break;
														}
														Switch_Init = 1;														
														Green_Led(Blink);
														break;
														
										case	2	:	if(!GETxAPIxVAL(BTN_LB) && !GETxAPIxVAL(BTN_LF) && !GETxAPIxVAL(BTN_RB) && !GETxAPIxVAL(BTN_RF) && !GETxAPIxVAL(BTN_MID) && !GETxAPIxVAL(BTN_START))
														{
															Switch_Init = 3;
														}
														Red_Led(Off);
														Green_Led(Blink);
														break;
														
										case	3	:	if(GETxAPIxVAL(BTN_LB))
														{
															SETxAPIxVAL(TRAIN2_POS, LB);
															Switch_Init = 4;
															break;
														}
														if(GETxAPIxVAL(BTN_LF))
														{
															SETxAPIxVAL(TRAIN2_POS, LF);
															Switch_Init = 4;
															break;
														}
														if(GETxAPIxVAL(BTN_RB))
														{
															SETxAPIxVAL(TRAIN2_POS, RB);
															Switch_Init = 4;
															break;
														}
														if(GETxAPIxVAL(BTN_RF))
														{
															SETxAPIxVAL(TRAIN2_POS, RF);
															Switch_Init = 4;
															break;															
														}
														if(GETxAPIxVAL(BTN_MID))
														{
															SETxAPIxVAL(TRAIN2_POS, Middle);
															Switch_Init = 4;
															break;
														}
														if(GETxAPIxVAL(BTN_START))
														{
															SETxAPIxVAL(TRAIN2_POS, OneTrain);
															Switch_Init = 4;
															break;
														}
														Green_Led(Blink);
														Switch_Init = 3;
														break;
														
										case	4	:	if(!GETxAPIxVAL(BTN_LB) && !GETxAPIxVAL(BTN_LF) && !GETxAPIxVAL(BTN_RB) && !GETxAPIxVAL(BTN_RF) && !GETxAPIxVAL(BTN_MID) && !GETxAPIxVAL(BTN_START))
														{
															if(GETxAPIxVAL(TRAIN1_POS) == GETxAPIxVAL(TRAIN2_POS))
															{
																Red_Led(On);
																Switch_Init = 1;
															}
															if(GETxAPIxVAL(TRAIN1_POS) != GETxAPIxVAL(TRAIN2_POS))
															{
																Switch_Init = 5;
															}
														}
														Green_Led(Blink);
														break;
														
										case	5	:	if(GETxAPIxVAL(TRAIN2_POS) != OneTrain)
														{
															Switch_Init = 6;	//2Trains
														}
														if(GETxAPIxVAL(TRAIN2_POS) == OneTrain)
														{
															Switch_Init = 9;	//1Train
														}
														break;
														
										case	6	:	Switch_Init = 8;														
														break;
														
										case	7	:	if(GETxAPIxVAL(BTN_START))	// 2Trains Start
														{
															Switch_Main = Run2;
															Switch_Init = 0;
															Stop_Program = Off;
														}
														Green_Led(Blink1);
														Red_Led(Off);
														break;
														
										case	8	:	if(GETxAPIxVAL(TRAIN1_POS) == Middle)		// 2 Trains NEW MODE
														{
															switch(GETxAPIxVAL(TRAIN2_POS))
															{
																case	LB	:	Switch_Program = 1;
																				Switch_Init = 7;
																				break;
																case	LF	:	Switch_Program = 5;
																				Switch_Init = 7;
																				break;
																case	RB	:	Switch_Program = 2;
																				Switch_Init = 7;
																				break;
																case	RF	:	Switch_Program = 3;
																				Switch_Init = 7;
																				break;
																default		:	Switch_Init = 8;
																				Red_Led(On);
																				break;	
															}
														}
														if(GETxAPIxVAL(TRAIN2_POS) == Middle)
														{
															switch(GETxAPIxVAL(TRAIN1_POS))
															{
																case	LB	:	Switch_Program = 1;
																				Switch_Init = 7;
																				break;
																case	LF	:	Switch_Program = 5;
																				Switch_Init = 7;
																				break;
																case	RB	:	Switch_Program = 2;
																				Switch_Init = 7;
																				break;
																case	RF	:	Switch_Program = 3;
																				Switch_Init = 7;
																				break;
																default		:	Switch_Init = 8;
																				Red_Led(On);
																				break;	
															}
														}
														if((GETxAPIxVAL(TRAIN1_POS) != Middle) && (GETxAPIxVAL(TRAIN2_POS) != Middle))
														{
															switch(GETxAPIxVAL(TRAIN1_POS))
															{
																case	LB	:	switch(GETxAPIxVAL(TRAIN2_POS))
																				{
																					case	LB	:	Switch_Init = 0;
																									break;
																					case	LF	:	Switch_Program = 1;
																									Switch_Init = 7;
																									break;
																					case	RB	:	Switch_Program = 2;
																									Switch_Init = 7;
																									break;
																					case	RF	:	Switch_Program = 4;
																									Switch_Init = 7;
																									break;
																					default		:	Switch_Init = 8;
																									Red_Led(On);
																									break;	
																				}
																				break;
																case	LF	:	switch(GETxAPIxVAL(TRAIN2_POS))
																				{
																					case	LB	:	Switch_Program = 1;
																									Switch_Init = 7;
																									break;
																					case	LF	:	Switch_Init = 0;
																									break;
																					case	RB	:	Switch_Program = 0;
																									Switch_Init = 7;
																									break;
																					case	RF	:	Switch_Program = 6;
																									Switch_Init = 7;
																									break;
																					default		:	Switch_Init = 8;
																									Red_Led(On);
																									break;	
																				}
																				break;
																case	RB	:	switch(GETxAPIxVAL(TRAIN2_POS))
																				{
																					case	LB	:	Switch_Program = 2;
																									Switch_Init = 7;
																									break;
																					case	LF	:	Switch_Program = 0;
																									Switch_Init = 7;
																									break;
																					case	RB	:	Switch_Init = 0;
																									break;
																					case	RF	:	Switch_Program = 3;
																									Switch_Init = 7;
																									break;
																					default		:	Switch_Init = 8;
																									Red_Led(On);
																									break;	
																				}
																				break;
																case	RF	:	switch(GETxAPIxVAL(TRAIN2_POS))
																				{
																					case	LB	:	Switch_Program = 4;
																									Switch_Init = 7;
																									break;
																					case	LF	:	Switch_Program = 6;
																									Switch_Init = 7;
																									break;
																					case	RB	:	Switch_Program = 3;
																									Switch_Init = 7;
																									break;
																					case	RF	:	Switch_Init = 0;
																									break;
																					default		:	Switch_Init = 8;
																									Red_Led(On);
																									break;	
																				}
																				break;
																default		:	Switch_Init = 8;
																				Red_Led(On);
																				break;	
															}
														}
														break;
														
										case	9	:	Switch_Init = 11;
														break;
										
										case	10	:	if(GETxAPIxVAL(BTN_START))	// 1Train Start
														{
															Switch_Main = Run1;
															Switch_Init = 0;
															Stop_Program = Off;
														}
														Green_Led(Blink1);
														Red_Led(Off);
														break;
										
										case	11	:	if(GETxAPIxVAL(TRAIN1_POS) == Middle)		// 1 Train NEW MODE
														{
															Switch_Program = 0;
															Switch_Init = 10;
														}
														else switch(GETxAPIxVAL(TRAIN1_POS))
														{
															case	LB	:	Switch_Program = 1;Switch_Init = 10; break;
															case	LF	:	Switch_Program = 3;Switch_Init = 10; break; 
															case	RB	:	Switch_Program = 0;Switch_Init = 10; break;
															case	RF	:	Switch_Program = 2;Switch_Init = 10; break;
															default		:	Switch_Init = 11;
																			Red_Led(On);
																			break;
														}
														break;
										
										default		:	Switch_Init = 0;
														Red_Led(On);
														break;
									}
									break;
				
				case	Run2	:	switch (Switch_Program)
									{
										case	0	: 	if (Train_Path(RB,LB) == Finished)
														{
															Switch_Program = 1;
															Eeprom_Store();
															if(Stop_Program == On)
															{
																Switch_Main = Init;
																//Stop_Program = Off;
															}
														}
														break;
														
										case	1	: 	if (Train_Path(LF,RB) == Finished)
														{
															Switch_Program = 2;
															Eeprom_Store();
															if(Stop_Program == On)
															{
																Switch_Main = Init;
																//Stop_Program = Off;
															}
														}
														break;
														
										case	2	: 	if (Train_Path(LB,RF) == Finished)
														{
															Switch_Program = 3;
															Eeprom_Store();
															if(Stop_Program == On)
															{
																Switch_Main = Init;
																//Stop_Program = Off;
															}
														}
														break;
														
										case	3	: 	if (Train_Path(RB,LB) == Finished)
														{
															Switch_Program = 4;
															Eeprom_Store();
															if(Stop_Program == On)
															{
																Switch_Main = Init;
																//Stop_Program = Off;
															}
														}
														break;
														
										case	4	: 	if (Train_Path(RF,LF) == Finished)
														{
															Switch_Program = 5;
															Eeprom_Store();
															if(Stop_Program == On)
															{
																Switch_Main = Init;
																//Stop_Program = Off;
															}
														}
														break;
														
										case	5	: 	if (Train_Path(LB,RF) == Finished)
														{
															Switch_Program = 6;
															Eeprom_Store();
															if(Stop_Program == On)
															{
																Switch_Main = Init;
																//Stop_Program = Off;
															}
														}
														break;
														
										case	6	: 	if (Train_Path(LF,RB) == Finished)
														{
															Switch_Program = 7;
															Eeprom_Store();
															if(Stop_Program == On)
															{
																Switch_Main = Init;
																//Stop_Program = Off;
															}
														}
														break;
														
										case	7	: 	if (Train_Path(RF,LF) == Finished)
														{
															Switch_Program = 0;
															Eeprom_Store();
															if(Stop_Program == On)
															{
																Switch_Main = Init;
																//Stop_Program = Off;
															}
														}
														break;
														
										
										
										default		:	break;
									}
									
									switch(Switch_Activate_Controls)
									{
										case	0	:	if(GETxAPIxVAL(BTN_LF) && GETxAPIxVAL(BTN_RF))
														{
															Switch_Activate_Controls = 1;
															Red_Led(Blink1);
														}
														else 
														{
															Switch_Activate_Controls = 0;
															Red_Led(Off);
														}
														break;
														
										case	1	:	if(!GETxAPIxVAL(BTN_LF) && !GETxAPIxVAL(BTN_RF))
														{
															Switch_Activate_Controls = 2;
															Red_Led(Blink1);
														}
														else 	
														{	
															Switch_Activate_Controls = 1;
															Red_Led(Blink1);
														}
														Activate_Controls_Counter = ActivateControlsTime;
														break;
										
										case	2	:	if(!GETxAPIxVAL(BTN_LF) && !GETxAPIxVAL(BTN_RF) && !GETxAPIxVAL(BTN_RB) && !GETxAPIxVAL(BTN_LB))
														{
															Activate_Controls_Counter--;
														}
														else
														{
															Activate_Controls_Counter = ActivateControlsTime;
														}
														
														Red_Led(Blink1);
														
														switch(GETxAPIxVAL(BTN_LB))	//slower
														{
															case	Off	:	Switch_Adjust_LB = 0;
																			break;
															
															case	On	:	switch(Switch_Adjust_LB)
																			{
																				case	0	:	if(GETxAPIxVAL(MAX_PWM_RIGHT) >= GETxAPIxVAL(STATIONARY_RIGHT))
																								{																				
																									DECRxAPIxVAL(MAX_PWM_RIGHT);
																								}
																								if(GETxAPIxVAL(MAX_PWM_LEFT) <= GETxAPIxVAL(STATIONARY_LEFT))
																								{
																									INCRxAPIxVAL(MAX_PWM_LEFT);
																								}
																								Switch_Adjust_LB = 1;
																								break;
																								
																				case	1	:	if(Adjust_Counter >= AdjustSpeed)
																								{
																									Adjust_Counter = 0;
																									Switch_Adjust_LB = 0;
																									break;
																								}
																								else {Adjust_Counter++;}
																								break;
																								
																				default		:	Switch_Adjust_LB = 0;
																								break;
																			}
																			break;
															
															default		:	break;
														}
																						
														
														switch(GETxAPIxVAL(BTN_LF))	//faster
														{
															case	Off	:	Switch_Adjust_LF = 0;
																			break;
															
															case	On	:	switch(Switch_Adjust_LF)
																			{
																				case	0	:	if(GETxAPIxVAL(MAX_PWM_RIGHT) <= 1022)
																								{																				
																									INCRxAPIxVAL(MAX_PWM_RIGHT);
																								}
																								if(GETxAPIxVAL(MAX_PWM_LEFT) >= 1)
																								{
																									DECRxAPIxVAL(MAX_PWM_LEFT);
																								}
																								Switch_Adjust_LF = 1;
																								break;
																								
																				case	1	:	if(Adjust_Counter >= AdjustSpeed)
																								{
																									Adjust_Counter = 0;
																									Switch_Adjust_LF = 0;
																									break;
																								}
																								else {Adjust_Counter++;}
																								break;
																								
																				default		:	Switch_Adjust_LF = 0;
																								break;
																			}
																			break;
															
															default		:	break;
														}
														
														switch(GETxAPIxVAL(BTN_RB))	//slower braking
														{
															case	Off	:	Switch_Adjust_RB = 0;
																			break;
															
															case	On	:	switch(Switch_Adjust_RB)
																			{
																				case	0	:	if(GETxAPIxVAL(MAX_JERK_PWM_BRAKE) <= 250)
																								{																				
																									INCRxAPIxVAL(MAX_JERK_PWM_BRAKE);
																								}
																								Switch_Adjust_RB = 1;
																								break;
																								
																				case	1	:	if(Adjust_Counter >= AdjustSpeed)
																								{
																									Adjust_Counter = 0;
																									Switch_Adjust_RB = 0;
																									break;
																								}
																								else {Adjust_Counter++;}
																								break;
																								
																				default		:	Switch_Adjust_RB = 0;
																								break;
																			}
																			break;
															
															default		:	break;
														}
																						
														
														switch(GETxAPIxVAL(BTN_RF))	//faster braking
														{
															case	Off	:	Switch_Adjust_RF = 0;
																			break;
															
															case	On	:	switch(Switch_Adjust_RF)
																			{
																				case	0	:	if(GETxAPIxVAL(MAX_JERK_PWM_BRAKE) >= 1)
																								{
																									DECRxAPIxVAL(MAX_JERK_PWM_BRAKE);
																								}																								Switch_Adjust_RF = 1;
																								break;
																								
																				case	1	:	if(Adjust_Counter >= AdjustSpeed)
																								{
																									Adjust_Counter = 0;
																									Switch_Adjust_RF = 0;
																									break;
																								}
																								else {Adjust_Counter++;}
																								break;
																								
																				default		:	Switch_Adjust_RF = 0;
																								break;
																			}
																			break;
															
															default		:	break;
														}
														if(Activate_Controls_Counter <= 1)
														{
															Switch_Activate_Controls = 0;
															Red_Led(Off);
														}
														break;
														
										default		:	Switch_Activate_Controls = 0;
														Red_Led(Off);
														break;
									}
							
									if(GETxAPIxVAL(BTN_STOP))
									{
										Stop_Program = On;
									}
									
									if(Stop_Program == On)
									{
										Red_Led(Blink);
									}
									
									Green_Led(On);
									
									break;
									
									
				case	Run1	:	switch (Switch_Program)
									{
										case	0	: 	if (Train_Path(RB,LB) == Finished)
														{
															Switch_Program = 1;
															Eeprom_Store();
															if(Stop_Program == On)
															{
																Switch_Main = Init;
																//Stop_Program = Off;
															}
														}
														break;
														
										case	1	: 	if (Train_Path(LB,RF) == Finished)
														{
															Switch_Program = 2;
															Eeprom_Store();
															if(Stop_Program == On)
															{
																Switch_Main = Init;
																//Stop_Program = Off;
															}
														}
														break;
														
										case	2	: 	if (Train_Path(RF,LF) == Finished)
														{
															Switch_Program = 3;
															Eeprom_Store();
															if(Stop_Program == On)
															{
																Switch_Main = Init;
																//Stop_Program = Off;
															}
														}
														break;
														
										case	3	: 	if (Train_Path(LF,RB) == Finished)
														{
															Switch_Program = 0;
															Eeprom_Store();
															if(Stop_Program == On)
															{
																Switch_Main = Init;
																//Stop_Program = Off;
															}
														}
														break;
																				
										default		:	break;
									}
									
									switch(Switch_Activate_Controls)
									{
										case	0	:	if(GETxAPIxVAL(BTN_LF) && GETxAPIxVAL(BTN_RF))
														{
															Switch_Activate_Controls = 1;
															Red_Led(Blink1);
														}
														else 
														{
															Switch_Activate_Controls = 0;
															Red_Led(Off);
														}
														break;
														
										case	1	:	if(!GETxAPIxVAL(BTN_LF) && !GETxAPIxVAL(BTN_RF))
														{
															Switch_Activate_Controls = 2;
															Red_Led(Blink1);
														}
														else 	
														{	
															Switch_Activate_Controls = 1;
															Red_Led(Blink1);
														}
														Activate_Controls_Counter = ActivateControlsTime;
														break;
										
										case	2	:	if(!GETxAPIxVAL(BTN_LF) && !GETxAPIxVAL(BTN_RF) && !GETxAPIxVAL(BTN_RB) && !GETxAPIxVAL(BTN_LB))
														{
															Activate_Controls_Counter--;
														}
														else
														{
															Activate_Controls_Counter = ActivateControlsTime;
														}
														
														Red_Led(Blink1);
														
														switch(GETxAPIxVAL(BTN_LB))	//slower
														{
															case	Off	:	Switch_Adjust_LB = 0;
																			break;
															
															case	On	:	switch(Switch_Adjust_LB)
																			{
																				case	0	:	if(GETxAPIxVAL(MAX_PWM_RIGHT) >= GETxAPIxVAL(STATIONARY_RIGHT))
																								{																				
																									DECRxAPIxVAL(MAX_PWM_RIGHT);
																								}
																								if(GETxAPIxVAL(MAX_PWM_LEFT) <= GETxAPIxVAL(STATIONARY_LEFT))
																								{
																									INCRxAPIxVAL(MAX_PWM_LEFT);
																								}
																								Switch_Adjust_LB = 1;
																								break;
																								
																				case	1	:	if(Adjust_Counter >= AdjustSpeed)
																								{
																									Adjust_Counter = 0;
																									Switch_Adjust_LB = 0;
																									break;
																								}
																								else {Adjust_Counter++;}
																								break;
																								
																				default		:	Switch_Adjust_LB = 0;
																								break;
																			}
																			break;
															
															default		:	break;
														}
																						
														
														switch(GETxAPIxVAL(BTN_LF))	//faster
														{
															case	Off	:	Switch_Adjust_LF = 0;
																			break;
															
															case	On	:	switch(Switch_Adjust_LF)
																			{
																				case	0	:	if(GETxAPIxVAL(MAX_PWM_RIGHT) <= 1022)
																								{																				
																									INCRxAPIxVAL(MAX_PWM_RIGHT);
																								}
																								if(GETxAPIxVAL(MAX_PWM_LEFT) >= 1)
																								{
																									DECRxAPIxVAL(MAX_PWM_LEFT);
																								}
																								Switch_Adjust_LF = 1;
																								break;
																								
																				case	1	:	if(Adjust_Counter >= AdjustSpeed)
																								{
																									Adjust_Counter = 0;
																									Switch_Adjust_LF = 0;
																									break;
																								}
																								else {Adjust_Counter++;}
																								break;
																								
																				default		:	Switch_Adjust_LF = 0;
																								break;
																			}
																			break;
															
															default		:	break;
														}
														
														switch(GETxAPIxVAL(BTN_RB))	//slower braking
														{
															case	Off	:	Switch_Adjust_RB = 0;
																			break;
															
															case	On	:	switch(Switch_Adjust_RB)
																			{
																				case	0	:	if(GETxAPIxVAL(MAX_JERK_PWM_BRAKE) <= 250)
																								{																				
																									INCRxAPIxVAL(MAX_JERK_PWM_BRAKE);
																								}
																								Switch_Adjust_RB = 1;
																								break;
																								
																				case	1	:	if(Adjust_Counter >= AdjustSpeed)
																								{
																									Adjust_Counter = 0;
																									Switch_Adjust_RB = 0;
																									break;
																								}
																								else {Adjust_Counter++;}
																								break;
																								
																				default		:	Switch_Adjust_RB = 0;
																								break;
																			}
																			break;
															
															default		:	break;
														}
																						
														
														switch(GETxAPIxVAL(BTN_RF))	//faster braking
														{
															case	Off	:	Switch_Adjust_RF = 0;
																			break;
															
															case	On	:	switch(Switch_Adjust_RF)
																			{
																				case	0	:	if(GETxAPIxVAL(MAX_JERK_PWM_BRAKE) >= 1)
																								{
																									DECRxAPIxVAL(MAX_JERK_PWM_BRAKE);
																								}
																								Switch_Adjust_RF = 1;
																								break;
																								
																				case	1	:	if(Adjust_Counter >= AdjustSpeed)
																								{
																									Adjust_Counter = 0;
																									Switch_Adjust_RF = 0;
																									break;
																								}
																								else {Adjust_Counter++;}
																								break;
																								
																				default		:	Switch_Adjust_RF = 0;
																								break;
																			}
																			break;
															
															default		:	break;
														}
														if(Activate_Controls_Counter <= 1)
														{
															Switch_Activate_Controls = 0;
															Red_Led(Off);
														}
														break;
														
										default		:	Switch_Activate_Controls = 0;
														Red_Led(Off);
														break;
									}
				
				default			:	break;
			}
}

/******************************************************************************
 * Function:        static void Green_Led(unsigned char Operation)
 *                  Blinking routine for green led
 *
 * PreCondition:    None
 *
 * Input:           Blinking speed
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        None
 *****************************************************************************/
static void Green_Led(unsigned char Operation)
{
	switch(Operation)
	{
		case	Off		:	Green = Off; 	break;
		
		case	On		:	Green = On;		break;
		
		case	Blink	:	Green_Led_Counter++;
							if(Green_Led_Counter >= BlinkHz)
							{
								Green_Led_Counter = 0;
							}
							if(Green_Led_Counter >= BlinkHz/2)
							{
								Green = On;
							}
							else {Green = Off;}
							break;
							
		case	Blink1	:	Green_Led_Counter++;
							if(Green_Led_Counter >= BlinkHz1)
							{
								Green_Led_Counter = 0;
							}
							if(Green_Led_Counter >= BlinkHz1/2)
							{
								Green = On;
							}
							else {Green = Off;}
							break;
							
		default			:	break;
	}
}

/******************************************************************************
 * Function:        static void Red_Led(unsigned char Operation)
 *                  Blinking routine for red led
 *
 * PreCondition:    None
 *
 * Input:           Blinking speed
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        None
 *****************************************************************************/
static void Red_Led(unsigned char Operation)
{
	switch(Operation)
	{
		case	Off		:	Red = Off; 	break;
		
		case	On		:	Red = On; 	break;
		
		case	Blink	:	Red_Led_Counter++;
							if(Red_Led_Counter >= BlinkHz)
							{
								Red_Led_Counter = 0;
							}
							if(Red_Led_Counter >= BlinkHz/2)
							{
								Red = On;
							}
							else {Red = Off;}
							break;
							
		case	Blink1	:	Red_Led_Counter++;
							if(Red_Led_Counter >= BlinkHz1)
							{
								Red_Led_Counter = 0;
							}
							if(Red_Led_Counter >= BlinkHz1/2)
							{
								Red = On;
							}
							else {Red = Off;}
							break;
							
		default			:	break;
	}
}

/******************************************************************************
 * Function:        static char Train_Path(unsigned char From, unsigned char To)
 *                  Sent the Train accordingly to the desired path
 *
 * PreCondition:    None
 *
 * Input:           From station, To station
 *
 * Output:          busy or finished
 *
 * Side Effects:    None
 *
 * Overview:        None
 *****************************************************************************/
static char Train_Path(unsigned char From, unsigned char To)
{
	static char Return_Val = Busy;
	
	switch(Switch_Train_Path)
	{
		case	0	:	switch(From)
						{
							case	RB	:	if(Junction(Right, Straight) == Finished)
											{
												Switch_Train_Path = 1;
												Return_Val = Busy;
											}
											Return_Val = Busy;
											break;
							case	RF	:	if(Junction(Right, Bend) == Finished)
											{
												Switch_Train_Path = 1;
												Return_Val = Busy;
											}
											Return_Val = Busy;
											break;
							case	LB	:	if(Junction(Left, Bend) == Finished)
											{
												Switch_Train_Path = 1;
												Return_Val = Busy;
											}
											Return_Val = Busy;
											break;
							case	LF	:	if(Junction(Left, Straight) == Finished)
											{
												Switch_Train_Path = 1;
												Return_Val = Busy;
											}
											Return_Val = Busy;
											break;
							default		:	break;
						}
						break;
						
		case	1	:	switch(To)
						{
							case	RB	:	if(Junction(Right, Straight) == Finished)
											{
												Switch_Train_Path = 2;
												Return_Val = Busy;
											}
											Return_Val = Busy;
											break;
							case	RF	:	if(Junction(Right, Bend) == Finished)
											{
												Switch_Train_Path = 2;
												Return_Val = Busy;
											}
											Return_Val = Busy;
											break;
							case	LB	:	if(Junction(Left, Bend) == Finished)
											{
												Switch_Train_Path = 2;
												Return_Val = Busy;
											}
											Return_Val = Busy;
											break;
							case	LF	:	if(Junction(Left, Straight) == Finished)
											{
												Switch_Train_Path = 2;
												Return_Val = Busy;
											}
											Return_Val = Busy;
											break;
							default		:	break;
						}
						break;
						
		case	2	:	switch(To)
						{
							case	RB	:	if(Train_Move_Right_Start() == Finished)
											{
												Switch_Train_Path = 3;
												Return_Val = Busy;
											}
											Return_Val = Busy;
											break;
							case	RF	:	if(Train_Move_Right_Start() == Finished)
											{
												Switch_Train_Path = 3;
												Return_Val = Busy;
											}
											Return_Val = Busy;
											break;
							case	LB	:	if(Train_Move_Left_Start() == Finished)
											{
												Switch_Train_Path = 3;
												Return_Val = Busy;
											}
											Return_Val = Busy;
											break;
							case	LF	:	if(Train_Move_Left_Start() == Finished)
											{
												Switch_Train_Path = 3;
												Return_Val = Busy;
											}
											Return_Val = Busy;
											break;
							default		:	break;
						}
						break;
						
		case	3	:	switch(To)
						{
							case	RB	:	if(GETxAPIxVAL(RC_RB) == On){
                                                Switch_Train_Path = 4;		    // End of station stop the train
											}
                                            else if(GETxAPIxVAL(RC_LMU) == On){ // Left Mountain up encountered while driving to the right
                                                Switch_Train_Path = 5;	        
                                            }                                            
                                            else if(GETxAPIxVAL(RC_LMD) == On){ // Left Mountain down encountered while driving to the right
                                                Switch_Train_Path = 6;
                                            }
                                            else if(GETxAPIxVAL(RC_RMD) == On){ // Right Mountain down encountered while driving to the right
                                                Switch_Train_Path = 7;
                                            }
                                            else if(GETxAPIxVAL(RC_RMU) == On){ // Right Mountain down encountered while driving to the right
                                                Switch_Train_Path = 8;
                                            }
                                            else{
                                                SetDCPWM1(GETxAPIxVAL(MAX_PWM_RIGHT));
                                                Train_Move_Pwm_Count = GETxAPIxVAL(MAX_PWM_RIGHT);
                                            }
											Return_Val = Busy;
											break;
							case	RF	:	if(GETxAPIxVAL(RC_RF) == On){
												Switch_Train_Path = 4;		    // End of station stop the train
											}
                                            else if(GETxAPIxVAL(RC_LMU) == On){ // Left Mountain up encountered while driving to the right
                                                Switch_Train_Path = 5;	        
                                            }                                            
                                            else if(GETxAPIxVAL(RC_LMD) == On){ // Left Mountain down encountered while driving to the right
                                                Switch_Train_Path = 6;
                                            }
                                            else if(GETxAPIxVAL(RC_RMD) == On){ // Right Mountain down encountered while driving to the right
                                                Switch_Train_Path = 7;
                                            }
                                            else if(GETxAPIxVAL(RC_RMU) == On){ // Right Mountain down encountered while driving to the right
                                                Switch_Train_Path = 8;
                                            }
                                            else{
                                                SetDCPWM1(GETxAPIxVAL(MAX_PWM_RIGHT));
                                                Train_Move_Pwm_Count = GETxAPIxVAL(MAX_PWM_RIGHT);
                                            }
											Return_Val = Busy;
											break;
							case	LB	:	if(GETxAPIxVAL(RC_LB) == On)
											{
												Switch_Train_Path = 4;		    // End of station stop the train
											}
                                            else if(GETxAPIxVAL(RC_LMU) == On){ // Left Mountain up encountered while driving to the left
                                                Switch_Train_Path = 9;	        
                                            }                                            
                                            else if(GETxAPIxVAL(RC_LMD) == On){ // Left Mountain down encountered while driving to the left
                                                Switch_Train_Path = 10;
                                            }
                                            else if(GETxAPIxVAL(RC_RMD) == On){ // Right Mountain down encountered while driving to the left
                                                Switch_Train_Path = 11;
                                            }
                                            else if(GETxAPIxVAL(RC_RMU) == On){ // Right Mountain down encountered while driving to the left
                                                Switch_Train_Path = 12;
                                            }
                                            else{
                                                SetDCPWM1(GETxAPIxVAL(MAX_PWM_LEFT));
                                                Train_Move_Pwm_Count = GETxAPIxVAL(MAX_PWM_LEFT);
                                            }
											Return_Val = Busy;
											break;
							case	LF	:	if(GETxAPIxVAL(RC_LF) == On)
											{
												Switch_Train_Path = 4;		    // End of station stop the train
											}
                                            else if(GETxAPIxVAL(RC_LMU) == On){ // Left Mountain up encountered while driving to the left
                                                Switch_Train_Path = 9;	        
                                            }                                            
                                            else if(GETxAPIxVAL(RC_LMD) == On){ // Left Mountain down encountered while driving to the left
                                                Switch_Train_Path = 10;
                                            }
                                            else if(GETxAPIxVAL(RC_RMD) == On){ // Right Mountain down encountered while driving to the left
                                                Switch_Train_Path = 11;
                                            }
                                            else if(GETxAPIxVAL(RC_RMU) == On){ // Right Mountain down encountered while driving to the left
                                                Switch_Train_Path = 12;
                                            }
                                            else{
                                                SetDCPWM1(GETxAPIxVAL(MAX_PWM_LEFT));
                                                Train_Move_Pwm_Count = GETxAPIxVAL(MAX_PWM_LEFT);
                                            }
											Return_Val = Busy;
											break;
							default		:	break;
						}
						break;
						
		case	4	:	switch(To)
						{
							case	RB	:	if(Train_Move_Right_Brake() == Finished)
											{
												Switch_Train_Path = 0;
												Return_Val = Finished;
												break;
											}
											Return_Val = Busy;
											break;
							case	RF	:	if(Train_Move_Right_Brake() == Finished)
											{
												Switch_Train_Path = 0;
												Return_Val = Finished;
												break;
											}
											Return_Val = Busy;
											break;
							case	LB	:	if(Train_Move_Left_Brake() == Finished)
											{
												Switch_Train_Path = 0;
												Return_Val = Finished;
												break;
											}
											Return_Val = Busy;
											break;
							case	LF	:	if(Train_Move_Left_Brake() == Finished)
											{
												Switch_Train_Path = 0;
												Return_Val = Finished;
												break;
											}
											Return_Val = Busy;
											break;
							default		:	break;
						}
						break;
                        
        case    5   :   //to the right
                        if(Left_Mountain_From_The_Left(LMU) == Finished){
                            Switch_Train_Path = 3;
                            Return_Val = Busy;
                        }
                        break;
            
        case    6   :   //to the right
                        if(Left_Mountain_From_The_Left(LMD) == Finished){
                            Switch_Train_Path = 3;
                            Return_Val = Busy;
                        }
                        break;
                        
        case    7   :   //to the right
                        if(Right_Mountain_From_The_Left(RMD) == Finished){
                            Switch_Train_Path = 3;
                            Return_Val = Busy;
                        }
                        break;
            
        case    8   :   //to the right
                        if(Right_Mountain_From_The_Left(RMU) == Finished){
                            Switch_Train_Path = 3;
                            Return_Val = Busy;
                        }
                        break;
                        
        case    9   :   //to the left
                        if(Right_Mountain_From_The_Right(RMU) == Finished){
                            Switch_Train_Path = 3;
                            Return_Val = Busy;
                        }
                        break;
            
        case    10  :   //to the left
                        if(Right_Mountain_From_The_Right(RMD) == Finished){
                            Switch_Train_Path = 3;
                            Return_Val = Busy;
                        }
                        break;
                        
        case    11  :   //to the left
                        if(Left_Mountain_From_The_Right(LMD) == Finished){
                            Switch_Train_Path = 3;
                            Return_Val = Busy;
                        }
                        break;
            
        case    12  :   //to the left
                        if(Left_Mountain_From_The_Right(LMU) == Finished){
                            Switch_Train_Path = 3;
                            Return_Val = Busy;
                        }
                        break;
                        
        
		
		default		:	Switch_Train_Path = 0;	break;
	}
	
	return(Return_Val);
}


/******************************************************************************
 * Function:        static char Train_Move_Left_Start(void)
 *                  Start moving the train to the left
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          returns busy or finished
 *
 * Side Effects:    None
 *
 * Overview:        None
 *****************************************************************************/
static char Train_Move_Left_Start(void)
{
	static char Return_Val = Busy;
	static unsigned int Train_Move_Wait_Time = 0;
	
	switch(Switch_Train_Move)
	{
		////////////////When Starting jumping to case 0 (Start_Move)////////////////////////////
		
		case	0	:	if(Train_Move_Wait_Time >= GETxAPIxVAL(LIGHTS_ON_WAIT_TIME))
						{
							Switch_Train_Move = 1;
							Train_Move_Wait_Time = 0;
							Return_Val = Busy;
							break;
						}
						Train_Move_Wait_Time++;
						Switch_Train_Move = 0;
						Return_Val = Busy;
						break;
		
		case	1	:	SetDCPWM1(GETxAPIxVAL(STATIONARY_LEFT));
						Train_Move_Pwm_Count = GETxAPIxVAL(STATIONARY_LEFT);
						Brake = 0;
						Switch_Train_Move = 2;
						Return_Val = Busy;
						break;
						
		case	2	:	if(Train_Move_Wait_Time >= GETxAPIxVAL(TRAIN_WAIT_TIME))
						{
							Switch_Train_Move = 3;
							Train_Move_Wait_Time = 0;
							Return_Val = Busy;
							break;
						}
						Train_Move_Wait_Time++;
						Switch_Train_Move = 2;
						Return_Val = Busy;
						break;
						
		case	3	:	SetDCPWM1(Train_Move_Pwm_Count);
						Return_Val = Busy;
						if (Train_Move_Pwm_Count <= GETxAPIxVAL(MAX_PWM_LEFT))
						{
							Switch_Train_Move = 0;
							Return_Val = Finished;
							break;
						}
						if (Train_Move_Pwm_Fast_Count >= GETxAPIxVAL(MAX_JERK_PWM))
						{
							Train_Move_Pwm_Count--;
							Train_Move_Pwm_Fast_Count = 0;
						}
						Train_Move_Pwm_Fast_Count++;
						break;
			default		:	break;
	}
	
	return(Return_Val);	
	
}

/******************************************************************************
 * Function:        static char Right_Mountain_From_The_Right(unsigned char rc)
 *                  Encountering right mountain from the right
 *
 * PreCondition:    None
 *
 * Input:           Reed contact
 *
 * Output:          returns busy or finished
 *
 * Side Effects:    None
 *
 * Overview:        None
 *****************************************************************************/
static char Right_Mountain_From_The_Right(unsigned char rc)
{
    static char Return_Val = Busy;
    if(rc == RMU){
        SetDCPWM1(Train_Move_Pwm_Count);        
        if (Train_Move_Pwm_Count >= GETxAPIxVAL(MAX_PWM_RMU_LEFT))              // when actual speed is adjusted for going down at RMU
        {
            Switch_Train_Move = 0;
            Return_Val = Finished;            
        }
        if (Train_Move_Pwm_Fast_Count >= GETxAPIxVAL(MAX_JERK_PWM))
        {
            Train_Move_Pwm_Count++;
            Train_Move_Pwm_Fast_Count = 0;
        }
        Train_Move_Pwm_Fast_Count++;
    }
    else if (rc == RMD){
        SetDCPWM1(Train_Move_Pwm_Count);        
        if (Train_Move_Pwm_Count <= GETxAPIxVAL(MAX_PWM_LEFT))                  // when actual speed is adjusted to normal speed
        {
            Switch_Train_Move = 0;
            Return_Val = Finished;            
        }
        if (Train_Move_Pwm_Fast_Count >= GETxAPIxVAL(MAX_JERK_PWM))
        {
            Train_Move_Pwm_Count--;
            Train_Move_Pwm_Fast_Count = 0;
        }
        Train_Move_Pwm_Fast_Count++;
    }
    return(Return_Val);
}

/******************************************************************************
 * Function:        static char Left_Mountain_From_The_Right(unsigned char rc)
 *                  Encountering left mountain from the right
 *
 * PreCondition:    None
 *
 * Input:           Reed contact
 *
 * Output:          returns busy or finished
 *
 * Side Effects:    None
 *
 * Overview:        None
 *****************************************************************************/
static char Left_Mountain_From_The_Right(unsigned char rc)
{
    static char Return_Val = Busy;
    return(Return_Val);
}

/******************************************************************************
 * Function:        static char Left_Mountain_From_The_Left(unsigned char rc)
 *                  Encountering left mountain from the left
 *
 * PreCondition:    None
 *
 * Input:           Reed contact
 *
 * Output:          returns busy or finished
 *
 * Side Effects:    None
 *
 * Overview:        None
 *****************************************************************************/
static char Left_Mountain_From_The_Left(unsigned char rc)
{
    static char Return_Val = Busy;
    return(Return_Val);
}

/******************************************************************************
 * Function:        static char Right_Mountain_From_The_Left(unsigned char rc)
 *                  Encountering right mountain from the left
 *
 * PreCondition:    None
 *
 * Input:           Reed contact
 *
 * Output:          returns busy or finished
 *
 * Side Effects:    None
 *
 * Overview:        None
 *****************************************************************************/
static char Right_Mountain_From_The_Left(unsigned char rc)
{
    static char Return_Val = Busy;
    return(Return_Val);
}

/******************************************************************************
 * Function:        static char Train_Move_Left_Brake(void)
 *                  Stop moving the train to the left
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          returns busy or finished
 *
 * Side Effects:    None
 *
 * Overview:        None
 *****************************************************************************/
static char Train_Move_Left_Brake(void)
{
	static char Return_Val = Busy;
	static unsigned int Train_Move_Wait_Time = 0;
	
	switch(Switch_Train_Move)
	{
		case	0	:	SetDCPWM1(Train_Move_Pwm_Count);
						Return_Val = Busy;
						if (Train_Move_Pwm_Count >= GETxAPIxVAL(STATIONARY_LEFT))
						{
							Switch_Train_Move = 1;
							Return_Val = Busy;
							break;
						}
						if (Train_Move_Pwm_Fast_Count >= GETxAPIxVAL(MAX_JERK_PWM_BRAKE))
						{
							Train_Move_Pwm_Count++;
							Train_Move_Pwm_Fast_Count = 0;
						}
						Train_Move_Pwm_Fast_Count++;
						break;
						
		case	1	:	if(Train_Move_Wait_Time >= GETxAPIxVAL(TRAIN_WAIT_TIME))
						{
							Switch_Train_Move = 2;
							Train_Move_Wait_Time = 0;
							Return_Val = Busy;
							break;
						}
						Return_Val = Busy;
						Train_Move_Wait_Time++;
						Switch_Train_Move = 1;
						break;
						
		case	2	:	SetDCPWM1(GETxAPIxVAL(STATIONARY_LEFT));
						Brake = 1;
						Train_Move_Pwm_Count = GETxAPIxVAL(STATIONARY_LEFT);
						Switch_Train_Move = 3;
						Return_Val = Busy;
						break;
						
		case	3	:	if(Train_Move_Wait_Time >= GETxAPIxVAL(LIGHTS_ON_WAIT_TIME))
						{
							Switch_Train_Move = 0;
							Train_Move_Wait_Time = 0;
							Return_Val = Finished;
							break;
						}
						Train_Move_Wait_Time++;
						Switch_Train_Move = 3;
						Return_Val = Busy;
						break;
						
		default		:	break;
	}
	
	return(Return_Val);	
	
}


/******************************************************************************
 * Function:        static char Train_Move_Right_Start(void)
 *                  Start moving the train to the right
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          returns busy or finished
 *
 * Side Effects:    None
 *
 * Overview:        None
 *****************************************************************************/
static char Train_Move_Right_Start(void)
{
	static char Return_Val = Busy;
	static unsigned int Train_Move_Wait_Time = 0;
	
	switch(Switch_Train_Move)
	{
		////////////////When Starting jumping to case 0 (Start_Move)////////////////////////////
		
		case	0	:	if(Train_Move_Wait_Time >= GETxAPIxVAL(LIGHTS_ON_WAIT_TIME))
						{
							Switch_Train_Move = 1;
							Train_Move_Wait_Time = 0;
							Return_Val = Busy;
							break;
						}
						Train_Move_Wait_Time++;
						Switch_Train_Move = 0;
						Return_Val = Busy;
						break;
		
		case	1	:	SetDCPWM1(GETxAPIxVAL(STATIONARY_RIGHT));
						Train_Move_Pwm_Count = GETxAPIxVAL(STATIONARY_RIGHT);
						Brake = 0;
						Return_Val = Busy;
						Switch_Train_Move = 2;						
						break;
						
		case	2	:	if(Train_Move_Wait_Time >= GETxAPIxVAL(TRAIN_WAIT_TIME))
						{
							Switch_Train_Move = 3;
							Train_Move_Wait_Time = 0;
							Return_Val = Busy;
							break;
						}
						Return_Val = Busy;
						Train_Move_Wait_Time++;
						Switch_Train_Move = 2;
						break;
						
		case	3	:	SetDCPWM1(Train_Move_Pwm_Count);
						if (Train_Move_Pwm_Count >= GETxAPIxVAL(MAX_PWM_RIGHT))
						{
							Switch_Train_Move = 0;
							Return_Val = Finished;
							break;
						}
						if (Train_Move_Pwm_Fast_Count >= GETxAPIxVAL(MAX_JERK_PWM))
						{
							Train_Move_Pwm_Count++;
							Train_Move_Pwm_Fast_Count = 0;
						}
						Train_Move_Pwm_Fast_Count++;
						Return_Val = Busy;
						break;
						
		default		:	break;
	}
	
	return(Return_Val);	
	
}

/******************************************************************************
 * Function:        static char Train_Move_Right_Brake(void)
 *                  Stop moving the train to the right
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          returns busy or finished
 *
 * Side Effects:    None
 *
 * Overview:        None
 *****************************************************************************/
static char Train_Move_Right_Brake(void)
{
	static char Return_Val = Busy;
	static unsigned int Train_Move_Wait_Time = 0;
	
	switch(Switch_Train_Move)
	{
	case	0	:		SetDCPWM1(Train_Move_Pwm_Count);
						if (Train_Move_Pwm_Count <= GETxAPIxVAL(STATIONARY_RIGHT))
						{
							Switch_Train_Move = 1;
							Return_Val = Busy;
							break;
						}
						if (Train_Move_Pwm_Fast_Count >= GETxAPIxVAL(MAX_JERK_PWM_BRAKE))
						{
							Train_Move_Pwm_Count--;
							Train_Move_Pwm_Fast_Count = 0;
						}
						Train_Move_Pwm_Fast_Count++;
						Return_Val = Busy;
						break;
						
		case	1	:	if(Train_Move_Wait_Time >= GETxAPIxVAL(TRAIN_WAIT_TIME))
						{
							Switch_Train_Move = 2;
							Train_Move_Wait_Time = 0;
							Return_Val = Busy;
							break;
						}
						Return_Val = Busy;
						Train_Move_Wait_Time++;
						Switch_Train_Move = 1;
						break;
						
		case	2	:	SetDCPWM1(GETxAPIxVAL(STATIONARY_RIGHT));
						Brake = 1;
						Train_Move_Pwm_Count = GETxAPIxVAL(STATIONARY_RIGHT);
						Switch_Train_Move = 3;
						Return_Val = Busy;
						break;
						
		case	3	:	if(Train_Move_Wait_Time >= GETxAPIxVAL(LIGHTS_ON_WAIT_TIME))
						{
							Switch_Train_Move = 0;
							Train_Move_Wait_Time = 0;
							Return_Val = Finished;
							break;
						}
						Train_Move_Wait_Time++;
						Switch_Train_Move = 3;
						Return_Val = Busy;
						break;
						
		default		:	break;
	}
	
	return(Return_Val);	
	
}

/******************************************************************************
 * Function:        static char Junction(unsigned char Junction_Left_Right, 
 *                                              unsigned char Straight_Bend)
 *                  Set the junction accordingly
 *
 * PreCondition:    None
 *
 * Input:           Junction Left or right, straight or bend the junction
 *
 * Output:          returns busy or finished
 *
 * Side Effects:    None
 *
 * Overview:        None
 *****************************************************************************/
static char Junction(unsigned char Junction_Left_Right, unsigned char Straight_Bend)
{
	static char Return_Val = Busy;
	static unsigned int Junction_Switch_Time = 0;
	
	switch (Switch_Junction)
	{
		case	0			:	Return_Val = Busy;
								switch (Junction_Left_Right)
								{
									case	Left	:	switch (Straight_Bend)
														{
															case	Straight	:	Wl_Left_Str = 1;	break;
															case	Bend		:	Wl_Left_Bnd	= 1;	break;
															default				:	break;
														}
														break;
														
									case	Right	:	switch (Straight_Bend)
														{
															case	Straight	:	Wl_Right_Str = 1;	break;
															case	Bend		:	Wl_Right_Bnd = 1;	break;
															default				:	break;
														}
														break;
														
									default			:	break;
								}
								Switch_Junction = 1;
								break;	
								
		case	1			:	if (Junction_Switch_Time >= GETxAPIxVAL(JUNCTION_WAIT_TIME))	
								{
									Switch_Junction = 2;
									Junction_Switch_Time = 0;
									Return_Val = Busy;
									break;
								}
								Return_Val = Busy;
								Switch_Junction = 1;
								Junction_Switch_Time++;
								break;
								
		case	2			:	Wl_Left_Str = 0;
								Wl_Left_Bnd	= 0;
								Wl_Right_Str = 0;
								Wl_Right_Bnd = 0;
								Switch_Junction = 0;
								Return_Val = Finished;
								break;
		
		default				:	break;
	}
	
	return (Return_Val);
}


/******************************************************************************
 * Function:        static void Debounce_Inputs(void)
 *                  Debounce all the inputs
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    Updates API[index] accordingly
 *
 * Overview:        None
 *****************************************************************************/
static void Debounce_Inputs(void)
{
	switch(Reed_Contact_LF)
	{
		case	On	:	Reed_Contact_LF_Counter = 0;
						SETxAPIxVAL(RC_LF, Off);
						break;
						
		case	Off	:	if(Reed_Contact_LF_Counter <= GETxAPIxVAL(INPUT_DEBOUNCE))
						{
							Reed_Contact_LF_Counter++;
							break;
						}
						else {SETxAPIxVAL(RC_LF, On);}
						break;
		
		default		:	break;
	}
	
	
	switch(Reed_Contact_LB)
	{
		case	On	:	Reed_Contact_LB_Counter = 0;
						SETxAPIxVAL(RC_LB, Off);
						break;
						
		case	Off	:	if(Reed_Contact_LB_Counter <= GETxAPIxVAL(INPUT_DEBOUNCE))
						{
							Reed_Contact_LB_Counter++;
							break;
						}
						else {SETxAPIxVAL(RC_LB, On);}
						break;
		
		default		:	break;
	}
	
	
	switch(Reed_Contact_RF)
	{
		case	On	:	Reed_Contact_RF_Counter = 0;
						SETxAPIxVAL(RC_RF, Off);
						break;
						
		case	Off	:	if(Reed_Contact_RF_Counter <= GETxAPIxVAL(INPUT_DEBOUNCE))
						{
							Reed_Contact_RF_Counter++;
							break;
						}
						else {SETxAPIxVAL(RC_RF, On);}
						break;
		
		default		:	break;
	}
	

	switch(Reed_Contact_RB)
	{
		case	On	:	Reed_Contact_RB_Counter = 0;
						SETxAPIxVAL(RC_RB, Off);
						break;
						
		case	Off	:	if(Reed_Contact_RB_Counter <= GETxAPIxVAL(INPUT_DEBOUNCE))
						{
							Reed_Contact_RB_Counter++;
							break;
						}
						else {SETxAPIxVAL(RC_RB, On);}
						break;
		
		default		:	break;
	}
	
	
	switch(But_Start)
	{
		case	On	:	if(Button_Contact_Counter_Start <= GETxAPIxVAL(INPUT_DEBOUNCE))
						{
							Button_Contact_Counter_Start++;
							break;
						}
						else {SETxAPIxVAL(BTN_START, On); }
						break;
		
		case	Off	:	Button_Contact_Counter_Start = 0;
						SETxAPIxVAL(BTN_START, Off);
						break;
						
		default		:	break;
	}
	
	
	switch(But_Stop)
	{
		case	On	:	if(Button_Contact_Counter_Stop <= GETxAPIxVAL(INPUT_DEBOUNCE))
						{
							Button_Contact_Counter_Stop++;
							break;
						}
						else {SETxAPIxVAL(BTN_STOP, On); }
						break;
		
		case	Off	:	Button_Contact_Counter_Stop = 0;
						SETxAPIxVAL(BTN_STOP, Off);
						break;
						
		default		:	break;
	}
	
	
	switch(But_Middle)
	{
		case	On	:	if(Button_Contact_Counter_Middle <= GETxAPIxVAL(INPUT_DEBOUNCE))
						{
							Button_Contact_Counter_Middle++;
							break;
						}
						else {SETxAPIxVAL(BTN_MID, On); }
						break;
		
		case	Off	:	Button_Contact_Counter_Middle = 0;
						SETxAPIxVAL(BTN_MID, Off);
						break;
						
		default		:	break;
	}
	
	
	switch(But_LB)
	{
		case	On	:	if(Button_Contact_Counter_LB <= GETxAPIxVAL(INPUT_DEBOUNCE))
						{
							Button_Contact_Counter_LB++;
							break;
						}
						else {SETxAPIxVAL(BTN_LB, On); }
						break;
		
		case	Off	:	Button_Contact_Counter_LB = 0;
						SETxAPIxVAL(BTN_LB, Off);
						break;
						
		default		:	break;
	}
	
	
	switch(But_LF)
	{
		case	On	:	if(Button_Contact_Counter_LF <= GETxAPIxVAL(INPUT_DEBOUNCE))
						{
							Button_Contact_Counter_LF++;
							break;
						}
						else {SETxAPIxVAL(BTN_LF, On); }
						break;
		
		case	Off	:	Button_Contact_Counter_LF = 0;
						SETxAPIxVAL(BTN_LF, Off);
						break;
						
		default		:	break;
	}
	
	
	switch(But_RB)
	{
		case	On	:	if(Button_Contact_Counter_RB <= GETxAPIxVAL(INPUT_DEBOUNCE))
						{
							Button_Contact_Counter_RB++;
							break;
						}
						else {SETxAPIxVAL(BTN_RB, On); }
						break;
		
		case	Off	:	Button_Contact_Counter_RB = 0;
						SETxAPIxVAL(BTN_RB, Off);
						break;
						
		default		:	break;
	}
	
	
		switch(But_RF)
	{
		case	On	:	if(Button_Contact_Counter_RF <= GETxAPIxVAL(INPUT_DEBOUNCE))
						{
							Button_Contact_Counter_RF++;
							break;
						}
						else {SETxAPIxVAL(BTN_RF, On); }
						break;
		
		case	Off	:	Button_Contact_Counter_RF = 0;
						SETxAPIxVAL(BTN_RF, Off);
						break;
						
		default		:	break;
	}
	
	
	switch(Reed_Contact_LMU)
	{
		case	On	:	if(Reed_Contact_LMU_Counter <= GETxAPIxVAL(INPUT_DEBOUNCE))
						{
							Reed_Contact_LMU_Counter++;
							break;
						}
						else {SETxAPIxVAL(RC_LMU, On); }
						break;
		
		case	Off	:	Reed_Contact_LMU_Counter = 0;
						SETxAPIxVAL(RC_LMU, Off);
						break;
						
		default		:	break;
	}
	
	
	switch(Reed_Contact_LMD)
	{
		case	On	:	if(Reed_Contact_LMD_Counter <= GETxAPIxVAL(INPUT_DEBOUNCE))
						{
							Reed_Contact_LMD_Counter++;
							break;
						}
						else {SETxAPIxVAL(RC_LMD, On); }
						break;
		
		case	Off	:	Reed_Contact_LMD_Counter = 0;
						SETxAPIxVAL(RC_LMD, Off);
						break;
						
		default		:	break;
	}
	
	
	switch(Reed_Contact_RMU)
	{
		case	On	:	if(Reed_Contact_RMU_Counter <= GETxAPIxVAL(INPUT_DEBOUNCE))
						{
							Reed_Contact_RMU_Counter++;
							break;
						}
						else {SETxAPIxVAL(RC_RMU, On); }
						break;
		
		case	Off	:	Reed_Contact_RMU_Counter = 0;
						SETxAPIxVAL(RC_RMU, Off);
						break;
						
		default		:	break;
	}
	
	
	switch(Reed_Contact_RMD)
	{
		case	On	:	if(Reed_Contact_RMD_Counter <= GETxAPIxVAL(INPUT_DEBOUNCE))
						{
							Reed_Contact_RMD_Counter++;
							break;
						}
						else {SETxAPIxVAL(RC_RMD, On); }
						break;
		
		case	Off	:	Reed_Contact_RMD_Counter = 0;
						SETxAPIxVAL(RC_RMD, Off);
						break;
						
		default		:	break;
	}
}

/******************************************************************************
 * Function:        static void Eeprom_Store(void)
 *                  Store program values in EEPROM
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    Stores vital program variables in EEPROM
 *
 * Overview:        None
 *****************************************************************************/
static void Eeprom_Store(void)
{
	INTCON = 0x00;
	
		EECON1bits.EEPGD = 0;
		EECON1bits.WREN = 1; 
		EEADR = 0x01;
		EEDATA = GETxAPIxVAL(MAX_PWM_RIGHT);
		EECON2 = 0x55;
		EECON2 = 0xaa;
		EECON1bits.WR = 1;
		while (!PIR2bits.EEIF);
		PIR2bits.EEIF = 0;
																
		EECON1bits.EEPGD = 0;
		EECON1bits.WREN = 1; 
		EEADR = 0x00;
		EEDATA = GETxAPIxVAL(MAX_PWM_RIGHT)>>8;
		EECON2 = 0x55;
		EECON2 = 0xaa;
		EECON1bits.WR = 1;
		while (!PIR2bits.EEIF);
		PIR2bits.EEIF = 0;

		EECON1bits.EEPGD = 0;
		EECON1bits.WREN = 1; 
		EEADR = 0x03;
		EEDATA = GETxAPIxVAL(MAX_PWM_LEFT);
		EECON2 = 0x55;
		EECON2 = 0xaa;
		EECON1bits.WR = 1;
		while (!PIR2bits.EEIF);
		PIR2bits.EEIF = 0;
																
		EECON1bits.EEPGD = 0;
		EECON1bits.WREN = 1; 
		EEADR = 0x02;
		EEDATA = GETxAPIxVAL(MAX_PWM_LEFT)>>8;
		EECON2 = 0x55;
		EECON2 = 0xaa;
		EECON1bits.WR = 1;
		while (!PIR2bits.EEIF);
		PIR2bits.EEIF = 0;

		EECON1bits.EEPGD = 0;
		EECON1bits.WREN = 1; 
		EEADR = 0x04;
		EEDATA = GETxAPIxVAL(MAX_JERK_PWM_BRAKE);
		EECON2 = 0x55;
		EECON2 = 0xaa;
		EECON1bits.WR = 1;
		while (!PIR2bits.EEIF);
		PIR2bits.EEIF = 0;
			
															
	INTCON = 0xA0;
}