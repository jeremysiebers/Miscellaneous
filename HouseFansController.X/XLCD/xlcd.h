#ifndef __XLCD_H
#define __XLCD_H
#include <xc.h>
/* PIC18 XLCD peripheral routines.
 *
 * 
 * IMPORTANT!!!!! ----->>>
 *          Check if (old) display has 5x7 characters, single line OR
 *          5x7 characters, multiple line !!!!
 *          Then check to set 8Bit or 4Bit interface
 * 
 * 
 *   Notes:
 *      - These libraries routines are written to support the
 *        Hitachi HD44780 LCD controller.
 *      - The user must define the following items:
 *          - The LCD interface type (4- or 8-bits)
 *          - If 4-bit mode
 *              - whether using the upper or lower nibble
 *          - The data port
 *              - The tris register for data port
 *              - The control signal ports and pins
 *              - The control signal port tris and pins
 *          - The user must provide three delay routines:
 *              - DelayFor18TCY() provides a 18 Tcy delay
 *              - DelayPORXLCD() provides at least 15ms delay
 *              - DelayXLCD() provides at least 5ms delay
 */
//------------------------------------------------------------------------------
/* Interface type 8-bit or 4-bit
 * For 8-bit operation uncomment the #define BIT8
 */
//#define BIT8

/* When in 4-bit interface define if the data is in the upper
 * or lower nibble.  For lower nibble, comment the #define UPPER
 */
//#define UPPER


/* When in 4-bit interface define if the RW line is used or not
 * When no RW line (RW connected to GND) uncomment the #define NO_RW
 */
#define NO_RW

/* DATA_PORT defines the port to which the LCD data lines are connected */
 #define DATA_PORT      		PORTC
 #define TRIS_DATA_PORT 		TRISC

//------------------------------------------------------------------------------

/* CTRL_PORT defines the port where the control lines are connected.
 * These are just samples, change to match your application.
 */
#ifdef NO_RW                                /* when no RW line available */
 char RW_PIN;                               /* create dummy RW_PIN */
 char TRIS_RW;                              /* create dummy TRIS_RW */
#else
 #define RW_PIN   PORTBbits.RB0             /* PORT for RW */
 #define TRIS_RW  TRISBbits.TRISB0          /* TRIS for RW */
#endif

 #define RS_PIN   PORTBbits.RB1             /* PORT for RS */
 #define TRIS_RS  TRISBbits.TRISB1          /* TRIS for RS */

 #define E_PIN    PORTBbits.RB2             /* PORT for D  */
 #define TRIS_E   TRISBbits.TRISB2          /* TRIS for E  */

/* Display ON/OFF Control defines */
#define DON         0b00001111  /* Display on      */
#define DOFF        0b00001011  /* Display off     */
#define CURSOR_ON   0b00001111  /* Cursor on       */
#define CURSOR_OFF  0b00001101  /* Cursor off      */
#define BLINK_ON    0b00001111  /* Cursor Blink    */
#define BLINK_OFF   0b00001110  /* Cursor No Blink */

/* Cursor or Display Shift defines */
#define SHIFT_CUR_LEFT    0b00000100  /* Cursor shifts to the left   */
#define SHIFT_CUR_RIGHT   0b00000101  /* Cursor shifts to the right  */
#define SHIFT_DISP_LEFT   0b00000110  /* Display shifts to the left  */
#define SHIFT_DISP_RIGHT  0b00000111  /* Display shifts to the right */

/* Function Set defines */
#define FOUR_BIT   ((unsigned char)0b00101100)  /* 4-bit Interface               */
#define EIGHT_BIT  ((unsigned char)0b00111100)  /* 8-bit Interface               */
#define LINE_5X7   ((unsigned char)0b00110000)  /* 5x7 characters, single line   */
#define LINE_5X10  ((unsigned char)0b00110100)  /* 5x10 characters               */
#define LINES_5X7  ((unsigned char)0b00111000)  /* 5x7 characters, multiple line */

//#define MEM_MODEL far  /* Change this to near for small memory model */

/* OpenXLCD
 * Configures I/O pins for external LCD
 */
void OpenXLCD(unsigned char);

/* SetCGRamAddr
 * Sets the character generator address
 */
void SetCGRamAddr(unsigned char);

/* SetDDRamAddr
 * Sets the display data address
 */
void SetDDRamAddr(unsigned char);

/* BusyXLCD
 * Returns the busy status of the LCD
 */
unsigned char BusyXLCD(void);

/* ReadAddrXLCD
 * Reads the current address
 */
unsigned char ReadAddrXLCD(void);

/* ReadDataXLCD
 * Reads a byte of data
 */
char ReadDataXLCD(void);

/* WriteCmdXLCD
 * Writes a command to the LCD
 */
void WriteCmdXLCD(unsigned char);

/* WriteDataXLCD
 * Writes a data byte to the LCD
 */
void WriteDataXLCD(char);

/* putcXLCD
 * A putc is a write
 */
#define putcXLCD WriteDataXLCD

/* putsXLCD
 * Writes a string of characters to the LCD
 */
void putsXLCD(char *);

/* putrsXLCD
 * Writes a string of characters in ROM to the LCD
 */
void putrsXLCD(const char *);

/* Clear Display
 * Writes Clear Display Command to the LCD
 */
void ClearDisplay(void);

/* LCD 4Bit Initialize
 * LCD init for 4 Bit interface mode 
 */
void LCD4BitInit(void);

/* User defines these routines according to the oscillator frequency */
extern void DelayFor18TCY(void);
extern void DelayPORXLCD(void);
extern void DelayXLCD(void);
#endif
