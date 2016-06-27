#ifndef __lcd_H
#define __lcd_H

// PIC18 LCD peripheral routines.

/* When in 4-bit interface is in the lower nibble. 

/* DATA_PORT defines the port to which the LCD data lines are connected */
#define DATA_PORT      PORTA
#define TRIS_DATA_PORT TRISA

/* CTRL_PORT defines the port where the control lines are connected.
 * These are just samples, change to match your application.
 */
#define RW_PIN   PORTAbits.RA5   /* PORT for RW */
#define TRIS_RW  DDRAbits.RA5    /* TRIS for RW */
#define RS_PIN   PORTAbits.RA4   /* PORT for RS */
#define TRIS_RS  DDRAbits.RA4    /* TRIS for RS */
#define E_PIN    PORTEbits.RE0   /* PORT for E  */
#define TRIS_E   DDREbits.RE0    /* TRIS for E  */

/* Display ON/OFF Control defines */
#define DON         0b00001111  /* Display on      */
#define DOFF        0b00001011  /* Display off     */
#define CURSOR_ON   0b00001111  /* Cursor on       */
#define CURSOR_OFF  0b00001101  /* Cursor off      */
#define BLINK_ON    0b00001111  /* Cursor Blink    */
#define BLINK_OFF   0b00001110  /* Cursor No Blink */
#define CLS 0x01				/* Clear Screen	   */

/* Cursor or Display Shift defines */
#define SHIFT_CUR_LEFT    0b00010011  /* Cursor shifts to the left   */
#define SHIFT_CUR_RIGHT   0b00010111  /* Cursor shifts to the right  */
#define SHIFT_DISP_LEFT   0b00011011  /* Display shifts to the left  */
#define SHIFT_DISP_RIGHT  0b00011111  /* Display shifts to the right */

/* Function Set defines */
#define FOUR_BIT   0b00101111  /* 4-bit Interface               */
#define EIGHT_BIT  0b00111111  /* 8-bit Interface               */
#define LINE_5X7   0b00110011  /* 5x7 characters, single line   */
#define LINE_5X10  0b00110111  /* 5x10 characters               */
#define LINES_5X7  0b00111011  /* 5x7 characters, multiple line */

/* LCD Line CMD */
#define LINE1	0x00
#define LINE2	0x40
#define LINE3	0x10
#define LINE4	0x50

#define PARAM_SCLASS auto
#define MEM_MODEL far  /* Change this to near for small memory model */

/* OpenLCD
 * Configures I/O pins for external LCD
 */
unsigned char OpenLCD(PARAM_SCLASS unsigned char);

/* SetCGRamAddr
 * Sets the character generator address
 */
//void SetCGRamAddr(PARAM_SCLASS unsigned char);

/* SetDDRamAddr
 * Sets the display data address
 */
unsigned char SetDDRamAddr(PARAM_SCLASS unsigned char);

/* BusyLCD
 * Returns the busy status of the LCD
 */
//unsigned char BusyLCD(void);

/* ReadAddrLCD
 * Reads the current address
 */
//unsigned char ReadAddrLCD(void);

/* ReadDataLCD
 * Reads a byte of data
 */
//char ReadDataLCD(void);

/* WriteCmdLCD
 * Writes a command to the LCD
 */
unsigned char WriteCmdLCD(PARAM_SCLASS unsigned char);

/* WriteDataLCD
 * Writes a data byte to the LCD
 */
unsigned char WriteDataLCD(PARAM_SCLASS char);

/* putcLCD
 * A putc is a write
 */
#define putcLCD WriteDataLCD

/* putsLCD
 * Writes a string of characters to the LCD
 */
unsigned char putsLCD(PARAM_SCLASS char *);

/* putrsLCD
 * Writes a string of characters in ROM to the LCD
 */
unsigned char putrsLCD(PARAM_SCLASS const MEM_MODEL rom char *);

#endif


