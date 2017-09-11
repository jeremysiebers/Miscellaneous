#include <Shift_Register.h>
#include <htc.h>

void Shift_Serial_Clk(void);
void Shift_Serial_In_Latch(void);
	

						
////////////////////////////////////////////////////////////////////////////////////////////////////
extern void Shift_Serial_In(void)
{
	Shift_Serial_In_Latch();
	
	Rd_Lb = !Shift_Serial_In_Hct;		//D7 inverted because active low
	Shift_Serial_Clk();
	
	Rd_Lf = !Shift_Serial_In_Hct;		//D6 inverted because active low
	Shift_Serial_Clk();
	
	Rd_Rb = !Shift_Serial_In_Hct;		//D5 inverted because active low
	Shift_Serial_Clk();
	
	Rd_Rf = !Shift_Serial_In_Hct;		//D4 inverted because active low
	Shift_Serial_Clk();
	///////////////////////////////	
	Bt_Lb = Shift_Serial_In_Hct;		//D3
	Shift_Serial_Clk();
	
	Bt_Lf = Shift_Serial_In_Hct;		//D2
	Shift_Serial_Clk();
	
	Bt_Rb = Shift_Serial_In_Hct;		//D1
	Shift_Serial_Clk();
	
	Bt_Rf = Shift_Serial_In_Hct;		//D0
	Shift_Serial_Clk();
	
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Shift_Serial_In_Latch(void)
{
	Shift_Serial_In_Latch_Hct=0;
	//Delay1TCY();
	Shift_Serial_Clk();
	//Delay1TCY();
	Shift_Serial_In_Latch_Hct=1;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Shift_Serial_Clk(void)
{	
	Shift_Serial_Clk_Hct=1;
	//Delay1TCY();
	Shift_Serial_Clk_Hct=0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
