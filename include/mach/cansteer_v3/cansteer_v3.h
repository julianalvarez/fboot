
#ifndef _CANSTEER_V3_H
#define _CANSTEER_V3_H

/* Include ********************************************************************/
#include <types32.h>
#include "fsl_common.h"

/* Enums **********************************************************************/
typedef enum {
    LED_GREEN_OFF,
    LED_GREEN_ON,
    LED_RED_OFF,
    LED_RED_ON
} LED_E;

/* Defines ********************************************************************/
/************************* EEPROM MAP ******************************************
Serial Number  : 0x00 0x01
Month          : 0x02 
Year           : 0x03
HW SW ver      : 0x04 0x05 0x06
Build          : 0x07
J1939 Address  : 0x08
Magic Number   : 0x09 0x0A 0x0B 0x0C
Application ID : 0x0D
Reserved       : 0x0E 0x0F
*******************************************************************************/
#define MEMORY_TRANSFER_MAX                 0x00000400L
#define FLASH_START_ENTRY                   0x70030000
#define FLASH_SPIFI_BASE                    0x70000000
#define EEPROM_BASE                         0x90000000L
#define EFLASH_BASE                         0x90000000L
#define EEPROM_SOFTWARE_VER_INFO            0x00000005L
#define EEPROM_J1939_ADDRESS                0x00000008L
#define EEPROM_STATUS_MEMORY                0x00000009L
#define EEPROM_APPLICATION_ID               0x0000000DL 


#define LED_1_TOGGLE 1
#define LED_2_TOGGLE 0

/* Typedefs *******************************************************************/
/* Externs ********************************************************************/
/* Prototypes *****************************************************************/
#if defined(__cplusplus)
extern "C" 
{
#endif

S32                     Open_CANSTEER_V3(void);

static inline void Reset() {
	__NVIC_SystemReset();
}

#if defined(__cplusplus)
}
#endif

#endif

/* End of $Workfile: iohub.h$ */
