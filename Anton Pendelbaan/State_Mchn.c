#include "Main.h"
#include "State_Mchn.h"
#include <xc.h>
#include "api.h"
#include "io.h"
#include "eeprom_settings.h"
#include "junction.h"
#include "train_move_left.h"
#include "train_move_right.h"

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

#define ActivateControlsTime 10000

unsigned char   Switch_Main = Init,
                Switch_Init = 0,
                Switch_Program = 0,
                Switch_Activate_Controls = 0,
                Switch_Adjust_LB = 0,
				Switch_Adjust_LF = 0,
				Switch_Adjust_RB = 0,
				Switch_Adjust_RF = 0,
                Switch_Train_Path = 0,
                Stop_Program = Off;
				
unsigned int	Adjust_Counter = 0,
                Activate_Controls_Counter = 0;
               

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
char Train_Path(unsigned char From, unsigned char To)
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
											Return_Val = Busy;
											break;
							case	LB	:	if(GETxAPIxVAL(RC_LB) == On)
											{
												Switch_Train_Path = 4;		    // End of station stop the train
											}
                                            else if(GETxAPIxVAL(RC_LMU) == On){ // Left Mountain up encountered while driving to the left
                                                Switch_Train_Path = 12;	        
                                            }                                            
                                            else if(GETxAPIxVAL(RC_LMD) == On){ // Left Mountain down encountered while driving to the left
                                                Switch_Train_Path = 11;
                                            }
                                            else if(GETxAPIxVAL(RC_RMD) == On){ // Right Mountain down encountered while driving to the left
                                                Switch_Train_Path = 10;
                                            }
                                            else if(GETxAPIxVAL(RC_RMU) == On){ // Right Mountain down encountered while driving to the left
                                                Switch_Train_Path = 9;
                                            }                                            
											Return_Val = Busy;
											break;
							case	LF	:	if(GETxAPIxVAL(RC_LF) == On)
											{
												Switch_Train_Path = 4;		    // End of station stop the train
											}
                                            else if(GETxAPIxVAL(RC_LMU) == On){ // Left Mountain up encountered while driving to the left
                                                Switch_Train_Path = 12;	        
                                            }                                            
                                            else if(GETxAPIxVAL(RC_LMD) == On){ // Left Mountain down encountered while driving to the left
                                                Switch_Train_Path = 11;
                                            }
                                            else if(GETxAPIxVAL(RC_RMD) == On){ // Right Mountain down encountered while driving to the left
                                                Switch_Train_Path = 10;
                                            }
                                            else if(GETxAPIxVAL(RC_RMU) == On){ // Right Mountain down encountered while driving to the left
                                                Switch_Train_Path = 9;
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
                        }
                        Return_Val = Busy;
                        break;
            
        case    6   :   //to the right
                        if(Left_Mountain_From_The_Left(LMD) == Finished){
                            Switch_Train_Path = 3;
                        }
                        Return_Val = Busy;
                        break;
                        
        case    7   :   //to the right
                        if(Right_Mountain_From_The_Left(RMD) == Finished){
                            Switch_Train_Path = 3;
                        }
                        Return_Val = Busy;
                        break;
            
        case    8   :   //to the right
                        if(Right_Mountain_From_The_Left(RMU) == Finished){
                            Switch_Train_Path = 3;
                        }
                        Return_Val = Busy;
                        break;
                        
        case    9   :   //to the left
                        if(Right_Mountain_From_The_Right(RMU) == Finished){
                            Switch_Train_Path = 3;
                        }
                        Return_Val = Busy;
                        break;
            
        case    10  :   //to the left
                        if(Right_Mountain_From_The_Right(RMD) == Finished){
                            Switch_Train_Path = 3;
                        }
                        Return_Val = Busy;
                        break;
                        
        case    11  :   //to the left
                        if(Left_Mountain_From_The_Right(LMD) == Finished){
                            Switch_Train_Path = 3;
                        }
                        Return_Val = Busy;
                        break;
            
        case    12  :   //to the left
                        if(Left_Mountain_From_The_Right(LMU) == Finished){
                            Switch_Train_Path = 3;
                        }
                        Return_Val = Busy;
                        break;
                        
		default		:	Switch_Train_Path = 0; Return_Val = Busy;	break;
	}
	
	return(Return_Val);
}