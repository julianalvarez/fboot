

#ifndef CFG_H
#define CFG_H

/* Include ********************************************************************/
/* Config *********************************************************************/

/* [DEF]
 *      Software Version
 */
#define MAYOR_VER                           3
#define MINOR_VER                           3
#define RELEASE_VER                         4
#define BUILD_VER                           00


/*******************************************
** CFG *************************************
*******************************************/
#ifdef MACH_IOHUB_SPIFI

/* ARCH ***********************************/
#define ARCH_ARM

/* CLOCK **********************************/

/* FLASH **********************************/

/* FWG ************************************/
/* #define FWG_SIZE_320x240 */
//#define FWG_SIZE_800x480

/* USB ************************************/
//#define USB_DEVICE

/* CAN ************************************/
#define CAN_DEVICE

/* SERIAL *********************************/
#define SERIAL_DEVICE

/* CONFIG *********************************/
//#define MININI
//#define FLASHFL

/* DEBUG **********************************/
#define DEBUG_PRINT

#endif

#endif
/* End of $Workfile: cfg.h$ */
