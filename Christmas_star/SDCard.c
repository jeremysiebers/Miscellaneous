/*------------------------------------------------------------------------
 * File    : SDCard.c
 * Author  : ing. M. de Waard
 * Version : 1.00
 * Date    : 11-Sep-2009
 * Purpose : SD card functionality
 *
 * Notes   : Module supplying SD card functionality. This module is derived
 *           from the SPI.c module of the LCDisplay application. It holds
 *           all SD card specific stuff including reading the filesystem.
 *
 * History :
 * Date         ver.   Comment
 *------------------------------------------------------------------------
 * 11-Sep-2009  V1.00  Creation
 *------------------------------------------------------------------------*/

/* system includes */
#include <REGX52.h>

/* own includes */
#include "sdcard.h"
#include "spi.h"

/* other includes */
#include "generic.h"
#include "dcf77.h"

/* global data: controlling bits */
volatile bit                  SD_card_present;
volatile bit                  SD_card_failed;
volatile bit                  SD_new_card;
volatile bit                  SD_card_ready;

/* global data: MBR, FAT, DIR and temporary structures */
static char xdata             SD_tmp [512];        // used for elementary disk I/O
static char xdata             SD_fat [512];        // local copy of (part of) the FAT
static SD_MBR_struct xdata    SD_mbr;              // local copy of the master boot record
static char xdata             SD_dir [512];        // one sector from the directory

/* global data: numbers to find specific sectors and indices into the directory */
static unsigned long xdata    SD_mbr_start;        // sector number of MBR, read from partition table
static unsigned long xdata    SD_root_start;       // first sector number of root directory
static unsigned long xdata    SD_fat_start;        // first sector number of File Allocation Table
static unsigned long xdata    SD_data_start;       // first sector number of the data

/* global data: communication with SD card */
static   unsigned char xdata  SD_response [5];     // response data from SD card command
static   unsigned char xdata  SD_argument [4];     // argument data for SD card command
volatile unsigned char xdata  SD_last_error;       // errorcode, should be 0

/* local function prototypes */
char sd_read_sector (long sector, unsigned char xdata *dest);
char sd_card_inserted (void);
char sd_check_response (char required_response);
void sd_read_response (unsigned char resptype);
void sd_send_command (unsigned char cmdtype, unsigned char resptype);

/*--------------------*/
/* exported functions */
/*--------------------*/

/*------------------------------------------------------------------------*/
/* Function: SD_init
 * Purpose : SD card initialisation.
 * Notes   : 
 */
void SD_init (void)
{
   /* initialise local stuff */
   SD_card_present = 0;
   SD_card_failed  = 0;
   SD_card_ready   = 0;
   SD_new_card     = 0;
   SD_last_error   = 0;

   /* initialise SPI port */
   SPI_init ();
}

/*------------------------------------------------------------------------*/
/* Function: SD_cycle
 * Purpose : Check if an SD card is present. If so, read a new image from
 *           from the SD card every minute and feed it to the display
 *           memory.
 * Notes   : SPI_CARD_DETECT has negative logic!
 */
void SD_cycle (void)
{
   if ( (!SD_card_present) && (!SPI_CARD_DETECT) )
   {
      /* a new card was put into the slot ... */
      SPI_prepare ();

      /* wait 100 ms to stabilise the SD card */
      GE_start_timer (100);
      while (!GE_timer_expired);

      /* handle card insertion ... */
      if (sd_card_inserted () == OK)
      {
         /* The new card's partition table and MBR have been read */
         SD_card_failed = 0;
         SD_last_error  = 0;
         SD_new_card    = 1;
         SD_card_ready  = 1;
         DCF_sync       = 0;     // card will be read on next actual sync
      }
      else
      {
         /* reading the partition table and MBR failed */
         SD_card_failed = 1;
      }

      /* don't need to repeat this... */
      SD_card_present = 1;
   }

   if ( (SD_card_present) && (SPI_CARD_DETECT) )
   {
      /* card was removed again...
       * Actually, according to physical spec, MOSI, SCK, CS should be
       * low during removing of card. However, since we can't predict
       * when the card is removed we cannot adhere to this specification.
       * When the SPI_CARD_DETECT input detects card removed, it already
       * is removed from the socket. */
      SD_card_present = 0;
      SD_last_error   = 0;
      SD_card_failed  = 0;
      SD_card_ready   = 0;
      SPI_switch_off ();
   }
}

/*------------------------------------------------------------------------*/
/* Function: SD_get_dir_entry
 * Purpose : Read the entry with number 'entry' from the directory.
 * Notes   : 
 */
void SD_get_dir_entry (int entry, SD_DIR_struct xdata *dest)
{
   int offset_in_sector;

   /* calculate the offset into the directory: each entry is 32 bytes in size,
    * each directory sector is 512 bytes. So, a total of 512 / 32 = 16 entries
    * fit in one sector of the directory. So entry div 16 gives the offset of
    * the directory entry sector wrt to 'root-start'. Entry mod 16 gives the
    * offset of the required entry in the sector. */
   offset_in_sector = entry % 16;
   entry /= 16;

   /* read the directory entry */
   sd_read_sector ((SD_root_start + entry), SD_dir);

   /* return the pointer to the required entry */
   *dest = *((SD_DIR_struct xdata *)&SD_dir [(offset_in_sector * 32)]);
}

/*------------------------------------------------------------------------*/
/* Function: SD_get_next_fat_entry
 * Purpose : This function finds the sector of the fat that holds the current
 *           entry. Then it finds that entry in that sector and returns the
 *           value that is at that location.
 * Notes   : 
 */
void SD_get_next_fat_entry (int entry, int *next_entry)
{
   int offset_in_fat;
   int sector_of_fat;

   /* there are 512 bytes in the fat, 256 integer values (!) */
   offset_in_fat = (entry % 256) * 2;
   sector_of_fat = entry / 256;
   sd_read_sector ((SD_fat_start + sector_of_fat), SD_fat);

   /* return and convert the next entry in the fat */
   *next_entry = *((int *)&SD_fat [offset_in_fat]);
   GE_int2big_endian (next_entry);
}

/*------------------------------------------------------------------------*/
/* Function: SD_read_data_sector
 * Purpose : Read a cluster of sectors from the data area. Returns the total
 *           number of bytes read.
 * Notes   : 
 */
int SD_read_data_cluster (int cluster, unsigned char xdata *dest)
{
   char cnt;
   int  total_bytes_read;
   int  sector_offset;
   
   /* calculate the sector offset (to the start of the data) in the SD card */
   sector_offset = cluster * (int)SD_mbr.header.spc;

   /* in a loop read the required amount of sectors to complete the cluster */
   total_bytes_read = 0;
   for (cnt = 0; cnt < SD_mbr.header.spc; cnt++)
   {
      /* read each sector and increment total bytes read and the destination pointer */
      sd_read_sector ((SD_data_start + sector_offset + cnt), dest);
      total_bytes_read += SD_mbr.header.bps;
      dest             += SD_mbr.header.bps;
   }

   return total_bytes_read;
}

/*-----------------*/
/* local functions */
/*-----------------*/

/*------------------------------------------------------------------------*/
/* Function: sd_read_sector
 * Purpose : Read a sector off the SD card. The sector number is the absolute
 *           sector index on the card (0 being the partition table).
 * Notes   : 
 */
char sd_read_sector (long sector, unsigned char xdata *dest)
{
   unsigned char *psecnum;
   char           result = OK;
   int            cnt;

   /* the sector number actually must be translated into a 512 byte offset
    * in the SD card memory map */
   sector <<= 9;

   /* put the sector number into the SD_argument */
   psecnum = (unsigned char *)(&sector);
   SD_argument [0] = *psecnum;
   psecnum++;
   SD_argument [1] = *psecnum;
   psecnum++;
   SD_argument [2] = *psecnum;
   psecnum++;
   SD_argument [3] = *psecnum;

   /* send the command, indicate we'll handle the result here */
   sd_send_command (SD_CMD_READ_SINGLE_BLOCK, 255);

   /* now we await a specific response */
   result = sd_check_response (0x00);

   if (result == OK)
   {
      /* now we wait for the start of data token */
      cnt = SD_TIMEOUT;
      do
      {
         result = sd_check_response (0xFE);
         cnt--;
      } while ( (result != OK) && (cnt > 0) );

      if (cnt == 0)
      {
         result = ERROR;
      }
   }

   if (result == OK)
   {
      /* now we can start clocking in the data ... */
      for (cnt = 0; cnt < 512; cnt++)
      {
         *dest = SPI_read_write_byte (0xFF);
         dest++;
      }

      /* read but ignore the two checksum bytes */
      SPI_read_write_byte (0xFF);
      SPI_read_write_byte (0xFF);
         
      /* do some dummy clocking */
      SPI_select_card (0);
      SPI_read_write_byte (0xFF);
      SPI_select_card (1);
   }

   return (result);
}

/*------------------------------------------------------------------------*/
/* Function: sd_send_command
 * Purpose : Send a command to the SD card and await the response.
 * Notes   : SD_argument and SD_response are used globally.
 */
void sd_send_command (unsigned char cmdtype, unsigned char resptype)
{
   char cnt;

   /* command type bit 7 and 6 always 01 */
   cmdtype &= 0x3F;
   cmdtype |= 0x40;

   /* send command ... */
   SPI_read_write_byte (cmdtype);

   /* ... send arguments (must have been preset!) ... */
   for (cnt = 0; cnt < 4; cnt++)
   {
      SPI_read_write_byte (SD_argument [cnt]);
   }

   /* ... send (fixed) checksum */
   SPI_read_write_byte (0x95);

   /* clock out one dummy byte for the card statemachine */
   SPI_read_write_byte (0xFF);

   /* read a response */
   sd_read_response (resptype);
}

/*------------------------------------------------------------------------*/
/* Function: sd_card_inserted
 * Purpose : A new SD card has been put into the clock. Read the MBR, find the
 *           FAT and initialise local data.
 * Notes   : 
 */
char sd_card_inserted (void)
{
   char result = OK;
   char partition;
   unsigned int cnt;

   /* first clockout some idle data; see physical layer spec: SPI_CS should be
    * INactive (i.e. logic high) during this period! */
   SPI_select_card (0);
   for (cnt = 0; cnt < 10; cnt++)
   {
      SPI_read_write_byte (0xFF);
   }
   SPI_select_card (1);

   /* send go to idle state command, initialise arguments to 0 */
   cnt = SD_TIMEOUT;
   do
   {
      SD_argument [0] = 0x00;
      SD_argument [1] = 0x00;
      SD_argument [2] = 0x00;
      SD_argument [3] = 0x00;

      /* send go-idle command */
      sd_send_command (SD_CMD_GO_IDLE_STATE, 255);
      cnt--;
   } while ( ((result = sd_check_response (0x01)) != OK) && (cnt > 0) );

   /* did we get the response? */
   if (cnt == 0)
   {
      result = ERROR;
      SD_last_error = SD_GO_IDLE_TIMEOUT;
   }

   if (result == OK)
   {
      /* wait 1 second ... */
      GE_start_timer (1000);
      while (!GE_timer_expired);

      /* now wait for the card to finish initialisation */
      cnt = SD_TIMEOUT;
      do
      {
         SD_argument [0] = 0x00;
         SD_argument [1] = 0x00;
         SD_argument [2] = 0x00;
         SD_argument [3] = 0x00;

         /* send 'get operational condition', when the reply == 0, the card is ready */
         sd_send_command (SD_CMD_SEND_OP_COND, 255);
         cnt--;
      } while ( ((result = sd_check_response (0x00)) != OK) && (cnt > 0) );

      /* check result */
      if (cnt == 0)
      {
         result = ERROR;
         SD_last_error = SD_GET_OPCOND_ERROR;
      }
   }

   /* set-blocklength to 512 */
   if (result == OK)
   {
      SD_argument [0] = 0x00; /* most significant argument */
      SD_argument [1] = 0x00;
      SD_argument [2] = 0x02;
      SD_argument [3] = 0x00; /* least significant argument */
      sd_send_command (SD_CMD_SET_BLOCKLEN, 255);

      /* we need a specific response again */
      result = sd_check_response (0x00);

      if (result != OK)
      {
         SD_last_error = SD_SET_BLOCKLEN_ERROR;
      }
   }

   /* read the file allocation table and get the sector number of the MBR */
   if (result == OK)
   {
      /* read the partition table... */
      result = sd_read_sector (0, SD_tmp);
      if (result == OK)
      {
         SD_mbr_start = 0;
         partition    = 0;
         while ( (SD_mbr_start == 0) && (partition < 4) )
         {
            /* We have the partition table, find the sector of the MBR (see
             * abstract for more details) */
            GE_long2big_endian ((long *)(&SD_tmp [0x1C6 + (partition * 16)]));
            SD_mbr_start = *((long *)(&SD_tmp [0x1C6 + (partition * 16)]));
            partition++;
         }

         /* there are 4 partitions, did we find one? */
         if (SD_mbr_start == 0)
         {
            /* nope... */
            result = ERROR;
            SD_last_error = SD_INVALID_PARTITION_TABLE;
         }
      }
      else
      {
         /* read-sector command failed */
         SD_last_error = SD_READ_PARTITION_TABLE_ERROR;
      }
   }

   /* now load the MBR into XDATA, we keep it there to be able to find the
    * root directory */
   if (result == OK)
   {
      /* read the MBR */
      result = sd_read_sector (SD_mbr_start, (char *)&SD_mbr);
      if (result == OK)
      {
         /* check if we really have a FAT16 filesystem here */
         if ( (SD_mbr.header.fattype [3] != '1') || (SD_mbr.header.fattype [4] != '6') )
         {
            /* Note: this mbr header struct is arranged according to FAT16. If the filesystem
             *       is not FAT16, the entire structure will differ and these two locations
             *       will hold something else than '16' */
            result        = ERROR;
            SD_last_error = SD_NOT_FAT16;
         }

         /* we have the MBR, convert some numbers */
         if (result == OK)
         {
            GE_int2big_endian ((int *)(&SD_mbr.header.bps));             // number of bytes per sector
            GE_int2big_endian ((int *)(&SD_mbr.header.rsect));           // number of sectors before first FAT
            GE_int2big_endian ((int *)(&SD_mbr.header.maxrootentries));  // maximum number of entries in the root
            GE_int2big_endian ((int *)(&SD_mbr.header.sectpfat));        // number of sectors per fat

            /* calculate the starting sector of the rootdirectory and the FAT */
            SD_fat_start  = SD_mbr_start  + SD_mbr.header.rsect;
            SD_root_start = SD_fat_start  + ((long)SD_mbr.header.nbrfat * (long)SD_mbr.header.sectpfat);
            SD_data_start = SD_root_start + (32 * (long)SD_mbr.header.maxrootentries / (long)SD_mbr.header.bps);
   
            /* check the number of sectors per cluster: total bytes should not exceed 16 KB */
            if (((int)SD_mbr.header.spc * SD_mbr.header.bps) > SD_MAX_CLUSTERSIZE)
            {
               /* cluser size is sectors per cluster multiplied by bytes per sector; can't handle
                * more than 16 KB */
               result        = ERROR;
               SD_last_error = SD_CLUSTERS_TOO_LARGE;
            }
         }      
      }
      else
      {
         SD_last_error = SD_READ_MBR_ERROR;
      }
   }

   if (result == OK)
   {
      /* read the first sector of the root directory */
      result = sd_read_sector (SD_root_start, SD_dir);
      if (result != OK)
      {
         /*-----
          * Note: we do not start converting numbers here yet, because we haven't determined
          *       the size of the root-dir yet and which entry we need. Therefore, the dir itself
          *       is regarded as a dynamic structure and LE --> BE converstion will take
          *       place on the local variable after it is taken from the dir. The dir structure
          *       itself will not be converted in situ.
          */
         SD_last_error = SD_READ_ROOT_DIR_ERROR;
      }
   }

   if (result == OK)
   {
      /* read the first sector of the FAT */
      result = sd_read_sector (SD_fat_start, SD_fat);
      if (result != OK)
      {
         /*-----
          * Note: we do not start converting numbers here yet, because we haven't determined
          *       the size of the FAT yet and which entry we need. Therefore, the fat itself
          *       is regarded as a dynamic structure and LE --> BE converstion will take
          *       place on the local variable after it is taken from the FAT. The FAT structure
          *       itself will not be converted in situ.
          */
         SD_last_error = SD_READ_FAT_ERROR;
      }
   }

   return (result);
}

/*------------------------------------------------------------------------*/
/* Function: sd_read_response
 * Purpose : Read a response from the SD card.
 * Notes   : If the response type is unequal to 1, 2 or 3, no response will
 *           be handled. If the response type is 1, 2 or 3, the corresponding
 *           R<resptype> will be handled.
 */
void sd_read_response (unsigned char resptype)
{
   char cnt;

   switch (resptype)
   {
      case 1:
         /* handle R1 response */
         SD_response [0] = SPI_read_write_byte (0xFF);
         break;

      case 2:
         /* handle R2 */
         SD_response [0] = SPI_read_write_byte (0xFF);
         SD_response [1] = SPI_read_write_byte (0xFF);
         break;

      case 3:
         /* handle R3 response */
         for (cnt = 0; cnt < 5; cnt++)
         {
            SD_response [cnt] = SPI_read_write_byte (0xFF);
         }
         break;
      
      default:
         // do nothing
         break;
   }
}

/*------------------------------------------------------------------------*/
/* Function: sd_check_response
 * Purpose : Check for a specific response from the SD card. Return OK when
 *           received, error when timeout occurred
 * Notes   : Can be used for R1 responses only
 */
char sd_check_response (char required_response)
{
   char result = OK;
   
   /* clock-in response */
   SD_response [0] = SPI_read_write_byte (0xFF);

   /* check what happened */
   if (SD_response [0] != required_response)
   {
      result = ERROR;
   }

   return (result);
}

