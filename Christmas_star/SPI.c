/*------------------------------------------------------------------------
 * File    : SPI.c
 * Author  : ing. M. de Waard
 * Version : 1.00
 * Date    : 11-Sep-2009
 * Purpose : SPI bitbanged...
 *
 * Notes   : Copied from the SPI module of the LCDisplay project. Made specific
 *           for SPI I/O only. The SDCard module now holds the SD specific stuff.
 *
 * History :
 * Date         ver.   Comment
 *------------------------------------------------------------------------
 * 11-Sep-2009  V1.00  Creation
 *------------------------------------------------------------------------*/

/* system includes */
#include <REGX52.h>

/* own includes */
#include "spi.h"

/* other includes */
#include "generic.h"

/* global data SPI related */
unsigned char bdata spiOut;
              sbit  spiOut7 = spiOut ^ 7;
              sbit  spiOut6 = spiOut ^ 6;
              sbit  spiOut5 = spiOut ^ 5;
              sbit  spiOut4 = spiOut ^ 4;
              sbit  spiOut3 = spiOut ^ 3;
              sbit  spiOut2 = spiOut ^ 2;
              sbit  spiOut1 = spiOut ^ 1;
              sbit  spiOut0 = spiOut ^ 0;
unsigned char bdata spiIn;
              sbit  spiIn7 = spiIn ^ 7;
              sbit  spiIn6 = spiIn ^ 6;
              sbit  spiIn5 = spiIn ^ 5;
              sbit  spiIn4 = spiIn ^ 4;
              sbit  spiIn3 = spiIn ^ 3;
              sbit  spiIn2 = spiIn ^ 2;
              sbit  spiIn1 = spiIn ^ 1;
              sbit  spiIn0 = spiIn ^ 0;

/*--------------------*/
/* exported functions */
/*--------------------*/

/*------------------------------------------------------------------------*/
/* Function: SPI_init
 * Purpose : SPI port initialisation.
 * Notes   : 
 */
void SPI_init (void)
{
   /* initialise local stuff: MISO port should always be on to make sure
    * it doesn't short out the readback signal from the SD card */
   SPI_MISO = 1;

   /* switch off SPI port */
   SPI_switch_off ();
}

/*------------------------------------------------------------------------*/
/* Function: SPI_prepare
 * Purpose : Prepare the SPI port for a new card
 * Notes   : 
 */
void SPI_prepare (void)
{
   SPI_CS   = 1;     // deactivate CS
   SPI_MISO = 1;     // prepare MISO for input function
   SPI_SCK  = 0;     // prepare clock for proper first transfer
}

/*------------------------------------------------------------------------*/
/* Function: SPI_switch_off
 * Purpose : Put the SPI port into a safe situation for card removal and
 *           insertion
 * Notes   : 
 */
void SPI_switch_off (void)
{
   SPI_CS   = 1;    // switch SPI stuff to 0 to avoid surges
   SPI_SCK  = 0;    // over the I/O pins during insert or
   SPI_MOSI = 0;    // removal of the card
}

/*------------------------------------------------------------------------*/
/* Function: SPI_select_card
 * Purpose : (De-)activate the card select signal
 * Notes   : 
 */
void SPI_select_card (bit active)
{
   /* the meaning of 'active' is that the card should be selected; this is the
    * inverse function (select is active low) */
   SPI_CS = !active;
}

/*------------------------------------------------------------------------*/
/* Function: SPI_read_write_byte
 * Purpose : Read and write a single byte from the SPI interface. The client must
 *           take care of CS!
 * Notes   : 
 */
unsigned char SPI_read_write_byte (unsigned char outdata)
{
   /* set byte to output */
   spiOut = outdata;

   /* output byte and read in new byte at the same time */
   SCK_PRE; SPI_MOSI=spiOut7; SCK_MID; spiIn7=SPI_MISO; SCK_POST;     // MSBit   
   SCK_PRE; SPI_MOSI=spiOut6; SCK_MID; spiIn6=SPI_MISO; SCK_POST;
   SCK_PRE; SPI_MOSI=spiOut5; SCK_MID; spiIn5=SPI_MISO; SCK_POST;
   SCK_PRE; SPI_MOSI=spiOut4; SCK_MID; spiIn4=SPI_MISO; SCK_POST;
   SCK_PRE; SPI_MOSI=spiOut3; SCK_MID; spiIn3=SPI_MISO; SCK_POST;
   SCK_PRE; SPI_MOSI=spiOut2; SCK_MID; spiIn2=SPI_MISO; SCK_POST;
   SCK_PRE; SPI_MOSI=spiOut1; SCK_MID; spiIn1=SPI_MISO; SCK_POST;
   SCK_PRE; SPI_MOSI=spiOut0; SCK_MID; spiIn0=SPI_MISO; SCK_POST;     // LSBit

   /* return read value */
   return (spiIn);
}

/*-----------------*/
/* local functions */
/*-----------------*/

