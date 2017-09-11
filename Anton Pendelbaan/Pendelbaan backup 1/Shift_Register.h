#ifndef __Shift_Register_H
#define __Shift_Register_H

#define Shift_Serial_In_Hct			RA3	//Input
#define Shift_Serial_In_Latch_Hct	RA4	//Output
#define Shift_Serial_Clk_Hct		RA2	//Output


extern void Shift_Serial_In(void);

unsigned char			Rd_Lb = 0,
						Rd_Lf = 0,
						Rd_Rb = 0,
						Rd_Rf = 0,
						Bt_Lb = 0,
						Bt_Lf = 0,
						Bt_Rb = 0,
						Bt_Rf = 0;

#endif








