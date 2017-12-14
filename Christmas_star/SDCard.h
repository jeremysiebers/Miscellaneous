/*------------------------------------------------------------------------
 * File    : SDCard.h
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

#ifndef __sdcard_h__
#define __sdcard_h__

/* constants */
#define SD_MAX_CLUSTERSIZE          16384
#define SD_TIMEOUT                    512          // number of tries before a timeout is signalled
#define SD_INIT_ERROR                   1
#define SD_GO_IDLE_TIMEOUT              2
#define SD_SEND_IFCOND_TIMEOUT          3
#define SD_GET_OPCOND_ERROR             4
#define SD_SET_BLOCKLEN_ERROR           5
#define SD_READ_PARTITION_TABLE_ERROR   6
#define SD_NO_DATA_START                7
#define SD_INVALID_PARTITION_TABLE      8
#define SD_READ_MBR_ERROR               9
#define SD_READ_ROOT_DIR_ERROR         10
#define SD_READ_FAT_ERROR              11
#define SD_NOT_FAT16                   12
#define SD_CLUSTERS_TOO_LARGE          13

/* SD command bytes */
#define SD_CMD_GO_IDLE_STATE            0
#define SD_CMD_SEND_OP_COND             1
#define SD_CMD_SEND_IF_COND             8
#define SD_CMD_SEND_CSD                 9
#define SD_CMD_SEND_CID                10
#define SD_CMD_STOP_TRANSMISSION       12
#define SD_CMD_SEND_STATUS             13
#define SD_CMD_SET_BLOCKLEN            16
#define SD_CMD_READ_SINGLE_BLOCK       17
#define SD_CMD_READ_MULTIPLE_BLOCK     18
#define SD_CMD_WRITE_SINGLE_BLOCK      24
#define SD_CMD_WRITE_MULTIPLE_BLOCK    25
#define SD_CMD_PROGRAM_CSD             27
#define SD_CMD_SET_WRITE_PROT          28
#define SD_CMD_CLEAR_WRITE_PROT        29
#define SD_CMD_SEND_WRITE_PROT         30
#define SD_CMD_TAG_SECTOR_START        32
#define SD_CMD_TAG_SECTOR_END          33
#define SD_CMD_UNTAG_SECTOR            34
#define SD_CMD_TAG_ERASE_GROUP_START   35
#define SD_CMD_TAG_ERASE_GROUP_END     36
#define SD_CMD_UNTAG_ERASE             37
#define SD_CMD_ERASE                   38
#define SD_CMD_LOCK_UNLOCK             42
#define SD_CMD_APP_CMD                 55
#define SD_CMD_READ_OCR                58
#define SD_CMD_CRC_ON_OFF              59
#define SD_ACMD_SEND_OP_COND           41

/* local typedefs */
typedef struct
{
   /* for 8051, int=2 bytes, long=4 bytes; on SD numbers are little endian, 8051
    * uses big endian */
   char bootjump [3];      // jump instruction to boot record
   char OEM_name [8];      // string without terminator!
   int  bps;               // bytes per sector, LITTLE ENDIAN when read from SD!
   char spc;               // sectors per cluster
   int  rsect;             // reserved number of sectors before first FAT
   char nbrfat;            // number of FATs
   int  maxrootentries;    // maximum number of entries in the root LITTLE ENDIAN
   int  inumsect;          // number of sectors, when 0 use value at offset 0x20
   char mediadesc;         // media descriptor
   int  sectpfat;          // sectors per FAT
   int  sectptrack;        // sectors per track
   int  numheads;          // number of heads
   long numhidden;         // number of hidden sectors
   long lnumsect;          // number of sectors when inumsect == 0
   char physdrvnum;        // physical drive number
   char reserved1;         // reserved
   char extbootsign;       // extended boot signature
   long serialnum;         // serial number
   char volumelabel [11];  // volume label, string without terminator
   char fattype [8];       // FAT type, string without terminator
} SD_MBR_header_struct;

typedef struct
{
   SD_MBR_header_struct  header;
   char                  bootcode [512 - sizeof (SD_MBR_header_struct) - sizeof (int)];
   int                   bootsignature;
} SD_MBR_struct;

typedef struct
{
   unsigned char filename [8];
   char          fileext [3];
   char          attribute;
   char          reserved [10];
   int           timechanged;
   int           datechanged;
   int           firstcluster;
   long          filesize;
} SD_DIR_struct;

/* exported global variables */
extern volatile bit SD_card_present;
extern volatile bit SD_card_failed;
extern volatile bit SD_new_card;
extern volatile bit SD_card_ready;
extern unsigned char xdata SD_last_error;

/* exported functions */
extern void  SD_init (void);
extern void  SD_cycle (void);
extern void  SD_get_dir_entry (int entry, SD_DIR_struct xdata *dest);
extern void  SD_get_next_fat_entry (int entry, int *next_entry);
extern int   SD_read_data_cluster (int cluster, unsigned char xdata *dest);

#endif
