#include <pwm.h>
#include <Main.h>
#include <State_Mchn.h>	//all movements and fidle yard program

#define Straight	0
#define Bend		1
#define Left		0
#define Right		1
#define Start_Move	0
#define Brake_Move	3
#define Debounce	20

#define ERROR 0xEE	// general switch case when error
#define Busy -1
#define Finished 0

#define TrainWaitTime 10000
#define JunctionWaitTime 800
#define LightsOnWaitTime 5000
#define StationaryLeft 460
#define StationaryRight 550
#define AdjustSpeed 10
#define MaxJerkPwm 45

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
#define BuzTime 500

unsigned char 	MaxJerkPwm_Brake = 80,
				MaxJerkPwm_Brake_Old = 80,
				Switch_Junction = 0,
				Switch_Train_Move = 0,
				Switch_Main = Init,
				Switch_Main_Old = 0,
				Switch_Program = 0,
				Switch_Program_Old = 0,
				Switch_Train_Path = 0,
				Reed_Contact_LF_Counter = 0,
				Reed_Contact_LB_Counter = 0,
				Reed_Contact_RF_Counter = 0,
				Reed_Contact_RB_Counter = 0,
				Rd_Rb = Off,
				Rd_Rf = Off,
				Rd_Lb = Off,
				Rd_Lf = Off,
				Button_Contact_Counter_Start = 0,
				Button_Contact_Counter_Stop = 0,
				Button_Contact_Counter_Middle = 0,
				Button_Contact_Counter_LB = 0,
				Button_Contact_Counter_LF = 0,
				Button_Contact_Counter_RB = 0,
				Button_Contact_Counter_RF = 0,
				Button_Start = Off,
				Button_Stop = Off,
				Button_Middle = Off,
				Button_LB = Off,
				Button_LF = Off,
				Button_RB = Off,
				Button_RF = Off,
				Switch_Adjust_LB = 0,
				Switch_Adjust_LF = 0,
				Switch_Adjust_RB = 0,
				Switch_Adjust_RF = 0,
				Switch_Init = 0,
				Stop_Program = Off,
				Train_Pos1 = 0,
				Train_Pos2 = 0;
				
				
unsigned int	MaxPwmRight = 725,
				MaxPwmRight_Old = 725,
				MaxPwmLeft = 307,
				MaxPwmLeft_Old = 307,
				Train_Move_Pwm_Count = 511,
				Train_Move_Pwm_Fast_Count = 0,
				Adjust_Counter = 0,
				Green_Led_Counter = 0,
				Red_Led_Counter = 0;


static char Junction(unsigned char Left_Right, unsigned char Straight_Bend);
static char Train_Move_Right_Start(void);
static char Train_Move_Right_Brake(void);
static char Train_Move_Left_Start(void);
static char Train_Move_Left_Brake(void);
static char Train_Path(unsigned char From, unsigned char To);
static void Debounce_Inputs(void);
static void Eeprom_Store(void);
static void Green_Led(unsigned char Operation);
static void Red_Led(unsigned char Operation);

void Update_StateMchn(void)
{
	Debounce_Inputs();
	
	switch (Switch_Main)
			{
				case	Init	:	switch(Switch_Init)
									{
										case	0	:	EECON1bits.EEPGD = 0; 
														EEADR = 0x00;           
														EECON1bits.RD = 1;    
														MaxPwmRight = EEDATA;  
														MaxPwmRight = MaxPwmRight<<8;
														EECON1bits.EEPGD = 0; 
														EEADR = 0x01;           
														EECON1bits.RD = 1;   
														MaxPwmRight = MaxPwmRight | EEDATA;
														
														EECON1bits.EEPGD = 0;  
														EEADR = 0x02;             
														EECON1bits.RD = 1;    
														MaxPwmLeft = EEDATA;  
														MaxPwmLeft = MaxPwmLeft<<8;
														EECON1bits.EEPGD = 0; 
														EEADR = 0x03;  
														EECON1bits.RD = 1;  
														MaxPwmLeft = MaxPwmLeft | EEDATA;
														
														EECON1bits.EEPGD = 0;  
														EEADR = 0x04;             
														EECON1bits.RD = 1;    
														MaxJerkPwm_Brake = EEDATA;  
														
														EECON1bits.EEPGD = 0;  
														EEADR = 0x05;             
														EECON1bits.RD = 1;    
														Switch_Main_Old = EEDATA; 
														
														EECON1bits.EEPGD = 0;  
														EEADR = 0x06;             
														EECON1bits.RD = 1;    
														Switch_Program_Old = EEDATA; 
																												
														
														
														MaxPwmRight_Old = MaxPwmRight;
														MaxPwmLeft_Old = MaxPwmLeft;
														MaxJerkPwm_Brake_Old = MaxJerkPwm_Brake;													
														
														Green_Led(Off);
														Red_Led(Off);
														
														if(Stop_Program == On && Switch_Main_Old == Run2)
														{
															Switch_Init = 7;
														}
														else if(Stop_Program == On && Switch_Main_Old == Run1)
														{
															Switch_Init = 10;
														}
														else {Switch_Init = 1;}
														break;
														
										case	1	:	if(Button_LB)
														{
															Train_Pos1 = LB;
															Switch_Init = 2;
															break;
														}
														if(Button_LF)
														{
															Train_Pos1 = LF;
															Switch_Init = 2;
															break;
														}
														if(Button_RB)
														{
															Train_Pos1 = RB;
															Switch_Init = 2;
															break;
														}
														if(Button_RF)
														{
															Train_Pos1 = RF;
															Switch_Init = 2;
															break;															
														}
														if(Button_Middle)
														{
															Train_Pos1 = Middle;
															Switch_Init = 2;
															break;
														}
														Switch_Init = 1;														
														Green_Led(Blink);
														break;
														
										case	2	:	if(!Button_LB && !Button_LF && !Button_RB && !Button_RF && !Button_Middle)
														{
															Switch_Init = 3;
														}
														Red_Led(Off);
														Green_Led(Blink);
														break;
														
										case	3	:	if(Train_Pos1 == Middle)
														{
															if(Button_LB || Button_LF || Button_RB || Button_RF)
															{
																if(Button_LB)
																{
																	Train_Pos2 = LB;
																	Switch_Init = 4;
																}
																if(Button_LF)
																{
																	Train_Pos2 = LF;
																	Switch_Init = 4;
																}
																if(Button_RB)
																{
																	Train_Pos2 = RB;
																	Switch_Init = 4;
																}
																if(Button_RF)
																{
																	Train_Pos2 = RF;
																	Switch_Init = 4;															
																}
																
															}
														}
														else //if(Train_Pos1 != Middle)
														{
															if(Button_LB || Button_LF || Button_RB || Button_RF || Button_Middle || Button_Start)
															{
																if(Button_LB)
																{
																	Train_Pos2 = LB;
																	Switch_Init = 4;
																}
																if(Button_LF)
																{
																	Train_Pos2 = LF;
																	Switch_Init = 4;
																}
																if(Button_RB)
																{
																	Train_Pos2 = RB;
																	Switch_Init = 4;
																}
																if(Button_RF)
																{
																	Train_Pos2 = RF;
																	Switch_Init = 4;															
																}
																if(Button_Middle)
																{
																	Train_Pos2 = Middle;
																	Switch_Init = 4;
																}
																if(Button_Start)
																{
																	Train_Pos2 = OneTrain;
																	Switch_Init = 4;
																}
																
															}
														}
														Green_Led(Blink);
														break;
														
										case	4	:	if(!Button_LB && !Button_LF && !Button_RB && !Button_RF && !Button_Middle && !Button_Start)
														{
															if(Train_Pos1 == Train_Pos2)
															{
																Red_Led(On);
																Switch_Init = 1;
															}
															else if(Train_Pos1 != Train_Pos2)
															{
																Switch_Init = 5;
															}
														}
														Green_Led(Blink);
														break;
														
										case	5	:	if(Train_Pos2 != OneTrain)
														{
															Switch_Init = 6;	//2Trains
														}
														else if(Train_Pos2 == OneTrain)
														{
															Switch_Init = 9;	//1Train
														}
														break;
														
										case	6	:	switch(Switch_Program_Old)	// 2 Trains OLD MODE
														{
															case	0	:	if((Train_Pos1 == LF) && (Train_Pos2 == RB))
																			{
																				Switch_Program = Switch_Program_Old;
																				Switch_Init = 7;
																			}
																			else {Switch_Init = 8;}
																			break;
															case	1	:	if((Train_Pos1 == LF) && (Train_Pos2 == LB))
																			{
																				Switch_Program = Switch_Program_Old;
																				Switch_Init = 7;
																			}
																			else {Switch_Init = 8;}
																			break;
															case	2	:	if((Train_Pos1 == LB) && (Train_Pos2 == RB))
																			{
																				Switch_Program = Switch_Program_Old;
																				Switch_Init = 7;
																			}
																			else {Switch_Init = 8;}
																			break;
															case	3	:	if((Train_Pos1 == RB) && (Train_Pos2 == RF))
																			{
																				Switch_Program = Switch_Program_Old;
																				Switch_Init = 7;
																			}
																			else {Switch_Init = 8;}
																			break;
															case	4	:	if((Train_Pos1 == LB) && (Train_Pos2 == RF))
																			{
																				Switch_Program = Switch_Program_Old;
																				Switch_Init = 7;
																			}
																			else {Switch_Init = 8;}
																			break;
															case	5	:	if((Train_Pos1 == LB) && (Train_Pos2 == LF))
																			{
																				Switch_Program = Switch_Program_Old;
																				Switch_Init = 7;
																			}
																			else {Switch_Init = 8;}
																			break;
															case	6	:	if((Train_Pos1 == LF) && (Train_Pos2 == RF))
																			{
																				Switch_Program = Switch_Program_Old;
																				Switch_Init = 7;
																			}
																			else {Switch_Init = 8;}
																			break;
															case	7	:	if((Train_Pos1 == RF) && (Train_Pos2 == RB))
																			{
																				Switch_Program = Switch_Program_Old;
																				Switch_Init = 7;
																			}
																			else {Switch_Init = 8;}
																			break;
															
															default		:	Switch_Init = 0;
																			break;
														}
														break;
														
										case	7	:	if(Button_Start)	// 2Trains Start
														{
															Switch_Main = Run2;
															Switch_Init = 0;
															Stop_Program = Off;
														}
														Green_Led(Blink1);
														Red_Led(Off);
														break;
														
										case	8	:	if(Train_Pos1 == Middle)		// 2 Trains NEW MODE
														{
															switch(Train_Pos2)
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
																default		:	Switch_Init = 0;
																				break;	
															}
														}
														if(Train_Pos2 == Middle)
														{
															switch(Train_Pos1)
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
																default		:	Switch_Init = 0;
																				break;	
															}
														}
														if((Train_Pos1 != Middle) && (Train_Pos2 != Middle))
														{
															switch(Train_Pos1)
															{
																case	LB	:	switch(Train_Pos2)
																				{
																					case	LB	:	Switch_Init = 0;
																									break;
																					case	LF	:	Switch_Program = 1;
																									Switch_Init = 7;
																									break;
																					case	RB	:	Switch_Program = 2;
																									Switch_Init = 7;
																									break;
																					case	RF	:	Switch_Program = 3;
																									Switch_Init = 7;
																									break;
																					default		:	Switch_Init = 0;
																									break;	
																				}
																				break;
																case	LF	:	switch(Train_Pos2)
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
																					default		:	Switch_Init = 0;
																									break;	
																				}
																				break;
																case	RB	:	switch(Train_Pos2)
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
																					default		:	Switch_Init = 0;
																									break;	
																				}
																				break;
																case	RF	:	switch(Train_Pos2)
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
																					default		:	Switch_Init = 0;
																									break;	
																				}
																				break;
																default		:	Switch_Init = 0;
																				break;	
															}
														}
														break;
														
										case	9	:	switch(Switch_Program_Old)	// 1 Train OLD MODE
														{
															case	0	:	if(Train_Pos1 == RB)
																			{
																				Switch_Program = Switch_Program_Old;
																				Switch_Init = 10;
																			}
																			else {Switch_Init = 11;}
																			break;
															case	1	:	if(Train_Pos1 == LB)
																			{
																				Switch_Program = Switch_Program_Old;
																				Switch_Init = 10;
																			}
																			else {Switch_Init = 11;}
																			break;
															case	2	:	if(Train_Pos1 == RF)
																			{
																				Switch_Program = Switch_Program_Old;
																				Switch_Init = 10;
																			}
																			else {Switch_Init = 11;}
																			break;
															case	3	:	if(Train_Pos1 == LF)
																			{
																				Switch_Program = Switch_Program_Old;
																				Switch_Init = 10;
																			}
																			else {Switch_Init = 11;}
																			break;
																			
															default		:	Switch_Init = 0;
																			break;
														}
														break;
										
										case	10	:	if(Button_Start)	// 1Train Start
														{
															Switch_Main = Run1;
															Switch_Init = 0;
															Stop_Program = Off;
														}
														Green_Led(Blink1);
														Red_Led(Off);
														break;
										
										case	11	:	if(Train_Pos1 == Middle)		// 1 Train NEW MODE
														{
															Switch_Program = 0;
															Switch_Init = 10;
														}
														else switch(Train_Pos1)
														{
															case	LB	:	Switch_Program = 1;Switch_Init = 10; break;
															case	LF	:	Switch_Program = 3;Switch_Init = 10; break; 
															case	RB	:	Switch_Program = 0;Switch_Init = 10; break;
															case	RF	:	Switch_Program = 2;Switch_Init = 10; break;
															default		:	Switch_Init = 0;
																			break;
														}
														break;
										
										default		:	Switch_Init = 0;
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
									
									switch(Button_LB)	//slower
									{
										case	Off	:	Switch_Adjust_LB = 0;
														break;
										
										case	On	:	switch(Switch_Adjust_LB)
														{
															case	0	:	if(MaxPwmRight >= StationaryRight)
																			{																				
																				MaxPwmRight--;
																			}
																			if(MaxPwmLeft <= StationaryLeft)
																			{
																				MaxPwmLeft++;
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
																	
									
									switch(Button_LF)	//faster
									{
										case	Off	:	Switch_Adjust_LF = 0;
														break;
										
										case	On	:	switch(Switch_Adjust_LF)
														{
															case	0	:	if(MaxPwmRight <= 1022)
																			{																				
																				MaxPwmRight++;
																			}
																			if(MaxPwmLeft >= 1)
																			{
																				MaxPwmLeft--;
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
									
									switch(Button_RB)	//slower
									{
										case	Off	:	Switch_Adjust_RB = 0;
														break;
										
										case	On	:	switch(Switch_Adjust_RB)
														{
															case	0	:	if(MaxJerkPwm_Brake <= 250)
																			{																				
																				MaxJerkPwm_Brake++;
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
																	
									
									switch(Button_RF)	//faster
									{
										case	Off	:	Switch_Adjust_RF = 0;
														break;
										
										case	On	:	switch(Switch_Adjust_RF)
														{
															case	0	:	if(MaxJerkPwm_Brake >= 1)
																			{
																				MaxJerkPwm_Brake--;
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
									
									if(Button_Stop)
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
									
									switch(Button_LB)	//slower
									{
										case	Off	:	Switch_Adjust_LB = 0;
														break;
										
										case	On	:	switch(Switch_Adjust_LB)
														{
															case	0	:	if(MaxPwmRight >= StationaryRight)
																			{																				
																				MaxPwmRight--;
																			}
																			if(MaxPwmLeft <= StationaryLeft)
																			{
																				MaxPwmLeft++;
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
																	
									
									switch(Button_LF)	//faster
									{
										case	Off	:	Switch_Adjust_LF = 0;
														break;
										
										case	On	:	switch(Switch_Adjust_LF)
														{
															case	0	:	if(MaxPwmRight <= 1022)
																			{																				
																				MaxPwmRight++;
																			}
																			if(MaxPwmLeft >= 1)
																			{
																				MaxPwmLeft--;
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
									
									switch(Button_RB)	//slower
									{
										case	Off	:	Switch_Adjust_RB = 0;
														break;
										
										case	On	:	switch(Switch_Adjust_RB)
														{
															case	0	:	if(MaxJerkPwm_Brake <= 250)
																			{																				
																				MaxJerkPwm_Brake++;
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
																	
									
									switch(Button_RF)	//faster
									{
										case	Off	:	Switch_Adjust_RF = 0;
														break;
										
										case	On	:	switch(Switch_Adjust_RF)
														{
															case	0	:	if(MaxJerkPwm_Brake >= 1)
																			{
																				MaxJerkPwm_Brake--;
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
									
									if(Button_Stop)
									{
										Stop_Program = On;
									}
									
									if(Stop_Program == On)
									{
										Red_Led(Blink);
									}
									
									Green_Led(On);
									
									break;
				
				default			:	break;
			}
}

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
							case	RB	:	if(Rd_Rb == On)
											{
												Switch_Train_Path = 4;
												Return_Val = Busy;
											}
											SetDCPWM1(MaxPwmRight);
											Train_Move_Pwm_Count = MaxPwmRight;
											Return_Val = Busy;
											break;
							case	RF	:	if(Rd_Rf == On)
											{
												Switch_Train_Path = 4;
												Return_Val = Busy;
											}
											SetDCPWM1(MaxPwmRight);
											Train_Move_Pwm_Count = MaxPwmRight;
											Return_Val = Busy;
											break;
							case	LB	:	if(Rd_Lb == On)
											{
												Switch_Train_Path = 4;
												Return_Val = Busy;
											}
											SetDCPWM1(MaxPwmLeft);
											Train_Move_Pwm_Count = MaxPwmLeft;
											Return_Val = Busy;
											break;
							case	LF	:	if(Rd_Lf == On)
											{
												Switch_Train_Path = 4;
												Return_Val = Busy;
											}
											SetDCPWM1(MaxPwmLeft);
											Train_Move_Pwm_Count = MaxPwmLeft;
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
		
		default		:	Switch_Train_Path = 0;	break;
	}
	
	return(Return_Val);
}

static char Train_Move_Left_Start(void)
{
	static char Return_Val = Busy;
	static unsigned int Train_Move_Wait_Time = 0;
	
	switch(Switch_Train_Move)
	{
		////////////////When Starting jumping to case 0 (Start_Move)////////////////////////////
		
		case	0	:	if(Train_Move_Wait_Time >= LightsOnWaitTime)
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
		
		case	1	:	SetDCPWM1(StationaryLeft);
						Train_Move_Pwm_Count = StationaryLeft;
						Brake = 0;
						Switch_Train_Move = 2;
						Return_Val = Busy;
						break;
						
		case	2	:	if(Train_Move_Wait_Time >= TrainWaitTime)
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
						if (Train_Move_Pwm_Count <= MaxPwmLeft)
						{
							Switch_Train_Move = 0;
							Return_Val = Finished;
							break;
						}
						if (Train_Move_Pwm_Fast_Count >= MaxJerkPwm)
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

static char Train_Move_Left_Brake(void)
{
	static char Return_Val = Busy;
	static unsigned int Train_Move_Wait_Time = 0;
	
	switch(Switch_Train_Move)
	{
		case	0	:	SetDCPWM1(Train_Move_Pwm_Count);
						Return_Val = Busy;
						if (Train_Move_Pwm_Count >= StationaryLeft)
						{
							Switch_Train_Move = 1;
							Return_Val = Busy;
							break;
						}
						if (Train_Move_Pwm_Fast_Count >= MaxJerkPwm_Brake)
						{
							Train_Move_Pwm_Count++;
							Train_Move_Pwm_Fast_Count = 0;
						}
						Train_Move_Pwm_Fast_Count++;
						break;
						
		case	1	:	if(Train_Move_Wait_Time >= TrainWaitTime)
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
						
		case	2	:	SetDCPWM1(StationaryLeft);
						Brake = 1;
						Train_Move_Pwm_Count = StationaryLeft;
						Switch_Train_Move = 3;
						Return_Val = Busy;
						break;
						
		case	3	:	if(Train_Move_Wait_Time >= LightsOnWaitTime)
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

static char Train_Move_Right_Start(void)
{
	static char Return_Val = Busy;
	static unsigned int Train_Move_Wait_Time = 0;
	
	switch(Switch_Train_Move)
	{
		////////////////When Starting jumping to case 0 (Start_Move)////////////////////////////
		
		case	0	:	if(Train_Move_Wait_Time >= LightsOnWaitTime)
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
		
		case	1	:	SetDCPWM1(StationaryRight);
						Train_Move_Pwm_Count = StationaryRight;
						Brake = 0;
						Return_Val = Busy;
						Switch_Train_Move = 2;						
						break;
						
		case	2	:	if(Train_Move_Wait_Time >= TrainWaitTime)
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
						if (Train_Move_Pwm_Count >= MaxPwmRight)
						{
							Switch_Train_Move = 0;
							Return_Val = Finished;
							break;
						}
						if (Train_Move_Pwm_Fast_Count >= MaxJerkPwm)
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

static char Train_Move_Right_Brake(void)
{
	static char Return_Val = Busy;
	static unsigned int Train_Move_Wait_Time = 0;
	
	switch(Switch_Train_Move)
	{
	case	0	:		SetDCPWM1(Train_Move_Pwm_Count);
						if (Train_Move_Pwm_Count <= StationaryRight)
						{
							Switch_Train_Move = 1;
							Return_Val = Busy;
							break;
						}
						if (Train_Move_Pwm_Fast_Count >= MaxJerkPwm_Brake)
						{
							Train_Move_Pwm_Count--;
							Train_Move_Pwm_Fast_Count = 0;
						}
						Train_Move_Pwm_Fast_Count++;
						Return_Val = Busy;
						break;
						
		case	1	:	if(Train_Move_Wait_Time >= TrainWaitTime)
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
						
		case	2	:	SetDCPWM1(StationaryRight);
						Brake = 1;
						Train_Move_Pwm_Count = StationaryRight;
						Switch_Train_Move = 3;
						Return_Val = Busy;
						break;
						
		case	3	:	if(Train_Move_Wait_Time >= LightsOnWaitTime)
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

static char Junction(unsigned char Left_Right, unsigned char Straight_Bend)
{
	static char Return_Val = Busy;
	static unsigned int Junction_Switch_Time = 0;
	
	switch (Switch_Junction)
	{
		case	0			:	Return_Val = Busy;
								switch (Left_Right)
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
								
		case	1			:	if (Junction_Switch_Time >= JunctionWaitTime)	
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

static void Debounce_Inputs(void)
{
	switch(Reed_Contact_LF)
	{
		case	On	:	Reed_Contact_LF_Counter = 0;
						Rd_Lf = Off;
						break;
						
		case	Off	:	if(Reed_Contact_LF_Counter <= Debounce)
						{
							Reed_Contact_LF_Counter++;
							break;
						}
						else {Rd_Lf = On;}
						break;
		
		default		:	break;
	}
	
	
	switch(Reed_Contact_LB)
	{
		case	On	:	Reed_Contact_LB_Counter = 0;
						Rd_Lb = Off;
						break;
						
		case	Off	:	if(Reed_Contact_LB_Counter <= Debounce)
						{
							Reed_Contact_LB_Counter++;
							break;
						}
						else {Rd_Lb = On;}
						break;
		
		default		:	break;
	}
	
	
	switch(Reed_Contact_RF)
	{
		case	On	:	Reed_Contact_RF_Counter = 0;
						Rd_Rf = Off;
						break;
						
		case	Off	:	if(Reed_Contact_RF_Counter <= Debounce)
						{
							Reed_Contact_RF_Counter++;
							break;
						}
						else {Rd_Rf = On;}
						break;
		
		default		:	break;
	}
	

	switch(Reed_Contact_RB)
	{
		case	On	:	Reed_Contact_RB_Counter = 0;
						Rd_Rb = Off;
						break;
						
		case	Off	:	if(Reed_Contact_RB_Counter <= Debounce)
						{
							Reed_Contact_RB_Counter++;
							break;
						}
						else {Rd_Rb = On;}
						break;
		
		default		:	break;
	}
	
	
	switch(But_Start)
	{
		case	On	:	if(Button_Contact_Counter_Start <= Debounce)
						{
							Button_Contact_Counter_Start++;
							break;
						}
						else {Button_Start = On; }
						break;
		
		case	Off	:	Button_Contact_Counter_Start = 0;
						Button_Start = Off;
						break;
						
		default		:	break;
	}
	
	
	switch(But_Stop)
	{
		case	On	:	if(Button_Contact_Counter_Stop <= Debounce)
						{
							Button_Contact_Counter_Stop++;
							break;
						}
						else {Button_Stop = On; }
						break;
		
		case	Off	:	Button_Contact_Counter_Stop = 0;
						Button_Stop = Off;
						break;
						
		default		:	break;
	}
	
	
	switch(But_Middle)
	{
		case	On	:	if(Button_Contact_Counter_Middle <= Debounce)
						{
							Button_Contact_Counter_Middle++;
							break;
						}
						else {Button_Middle = On; }
						break;
		
		case	Off	:	Button_Contact_Counter_Middle = 0;
						Button_Middle = Off;
						break;
						
		default		:	break;
	}
	
	
	switch(But_LB)
	{
		case	On	:	if(Button_Contact_Counter_LB <= Debounce)
						{
							Button_Contact_Counter_LB++;
							break;
						}
						else {Button_LB = On; }
						break;
		
		case	Off	:	Button_Contact_Counter_LB = 0;
						Button_LB = Off;
						break;
						
		default		:	break;
	}
	
	
	switch(But_LF)
	{
		case	On	:	if(Button_Contact_Counter_LF <= Debounce)
						{
							Button_Contact_Counter_LF++;
							break;
						}
						else {Button_LF = On; }
						break;
		
		case	Off	:	Button_Contact_Counter_LF = 0;
						Button_LF = Off;
						break;
						
		default		:	break;
	}
	
	
	switch(But_RB)
	{
		case	On	:	if(Button_Contact_Counter_RB <= Debounce)
						{
							Button_Contact_Counter_RB++;
							break;
						}
						else {Button_RB = On; }
						break;
		
		case	Off	:	Button_Contact_Counter_RB = 0;
						Button_RB = Off;
						break;
						
		default		:	break;
	}
	
	
		switch(But_RF)
	{
		case	On	:	if(Button_Contact_Counter_RF <= Debounce)
						{
							Button_Contact_Counter_RF++;
							break;
						}
						else {Button_RF = On; }
						break;
		
		case	Off	:	Button_Contact_Counter_RF = 0;
						Button_RF = Off;
						break;
						
		default		:	break;
	}
		
}


static void Eeprom_Store(void)
{
	INTCON = 0x00;
	
	//if (MaxPwmRight == !MaxPwmRight_Old)
	//{
		EECON1bits.EEPGD = 0;
		EECON1bits.WREN = 1; 
		EEADR = 0x01;
		EEDATA = MaxPwmRight;
		EECON2 = 0x55;
		EECON2 = 0xaa;
		EECON1bits.WR = 1;
		while (!PIR2bits.EEIF);
		PIR2bits.EEIF = 0;
																
		EECON1bits.EEPGD = 0;
		EECON1bits.WREN = 1; 
		EEADR = 0x00;
		EEDATA = MaxPwmRight>>8;
		EECON2 = 0x55;
		EECON2 = 0xaa;
		EECON1bits.WR = 1;
		while (!PIR2bits.EEIF);
		PIR2bits.EEIF = 0;
	//}
	
	//if (MaxPwmLeft == !MaxPwmLeft_Old)
	//{
		EECON1bits.EEPGD = 0;
		EECON1bits.WREN = 1; 
		EEADR = 0x03;
		EEDATA = MaxPwmLeft;
		EECON2 = 0x55;
		EECON2 = 0xaa;
		EECON1bits.WR = 1;
		while (!PIR2bits.EEIF);
		PIR2bits.EEIF = 0;
																
		EECON1bits.EEPGD = 0;
		EECON1bits.WREN = 1; 
		EEADR = 0x02;
		EEDATA = MaxPwmLeft>>8;
		EECON2 = 0x55;
		EECON2 = 0xaa;
		EECON1bits.WR = 1;
		while (!PIR2bits.EEIF);
		PIR2bits.EEIF = 0;
//	}
		
	//if (MaxJerkPwm_Brake == !MaxJerkPwm_Brake_Old)
	//{
		EECON1bits.EEPGD = 0;
		EECON1bits.WREN = 1; 
		EEADR = 0x04;
		EEDATA = MaxJerkPwm_Brake;
		EECON2 = 0x55;
		EECON2 = 0xaa;
		EECON1bits.WR = 1;
		while (!PIR2bits.EEIF);
		PIR2bits.EEIF = 0;
	//}
	
	//if (Switch_Main == !Switch_Main_Old)
	//{				
		EECON1bits.EEPGD = 0;
		EECON1bits.WREN = 1; 
		EEADR = 0x05;
		EEDATA = Switch_Main;
		EECON2 = 0x55;
		EECON2 = 0xaa;
		EECON1bits.WR = 1;
		while (!PIR2bits.EEIF);
		PIR2bits.EEIF = 0;
	//}
	
//	if (Switch_Program == !Switch_Program_Old)
	//{
		EECON1bits.EEPGD = 0;
		EECON1bits.WREN = 1; 
		EEADR = 0x06;
		EEDATA = Switch_Program;
		EECON2 = 0x55;
		EECON2 = 0xaa;
		EECON1bits.WR = 1;
		while (!PIR2bits.EEIF);
		PIR2bits.EEIF = 0;
	//}					
															
	INTCON = 0xA0;
}