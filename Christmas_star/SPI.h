/*------------------------------------------------------------------------
 * File    : spi.h
 * Author  : ing. M. de Waard
 * Version : 1.00
 * Date    : 11-Sep-2009
 * Purpose : 
 *
 * History :
 * Date         ver.   Comment
 *------------------------------------------------------------------------
 * 11-Sep-2009  V1.00  Creation
 *------------------------------------------------------------------------*/

#ifndef __spi_h__
#define __spi_h__

/* constants SPI related*/
#define CPOL               0               /* clock polarity */
#define CPHA               0               /* clock phase */
#define CS_TOGGLE_BETWEEN  0               /* toggle CS between bytes */

#if CPHA
   #define SCK_POST
   #if CPOL
      #define SCK_INIT   1
      #define SCK_PRE    SPI_SCK=0
      #define SCK_MID    SPI_SCK=1
   #else
      #define SCK_INIT   0
      #define SCK_PRE    SPI_SCK=1
      #define SCK_MID    SPI_SCK=0
   #endif
#else
   #define SCK_PRE
   #if CPOL
      #define SCK_INIT   1
      #define SCK_MID    SPI_SCK=0
      #define SCK_POST   SPI_SCK=1
   #else
      #define SCK_INIT   0
      #define SCK_MID    SPI_SCK=1
      #define SCK_POST   SPI_SCK=0
   #endif
#endif

#if CS_TOGGLE_BETWEEN
   #define CS_TOGGLE SPI_CS=1;SPI_CS=0
#else
   #define CS_TOGGLE
#endif

/* exported global variables */

/* exported functions */
extern void SPI_init (void);
extern void SPI_prepare (void);
extern void SPI_select_card (bit active);
extern void SPI_switch_off (void);

extern unsigned char SPI_read_write_byte (unsigned char outdata);

#endif
