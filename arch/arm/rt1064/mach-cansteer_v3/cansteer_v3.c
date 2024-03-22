/* Include ********************************************************************/
#include <stdio.h>

#include "fsl_debug_console.h"

#include "cfg.h"
#include "types32.h"
#include "mach/cansteer_v3/cansteer_v3.h"
#include "timeout.h"
#include "can.h"
#include "j1939.h"
#include "mtd.h"

/* Defines ********************************************************************/
/* Typedefs *******************************************************************/
/* Globals ********************************************************************/

/* Statics ********************************************************************/
const uint32_t aFLASH_START_SECTOR[] = {0};
/*
*                         MEMORY MAP
*   Type                 Start         End         Size
* ----------------------------------------------------------
* E_FBOOT          -  0x70000000U - 0x7000FFFFU -  64 kB
* E_VIRTUAL_EEPROM -  0x70010000U - 0x7002FFFFU -  128 kB
* E_FLASH          -  0x70030000U - 0x70FFFFFFU -  (4 MB - 64kB - 128 kB)
*/

//INTERNAL FLASH MEMORY MAPPING
//VIRTUAL EEPROM MEMORY MAPPING
MTD_T                   VIRTUAL_EEPROM =
{
  0x90000000U,
  0x400U,
  0xFFFU,
  0,
  0,
  0,
  Open_VIRTUAL_EEPROM,
  0,
  0,
  0,
  0,
};

//EXTERNAL FLASH MEMORY MAPPING
MTD_T                   EFLASH =
{
  0x70030000U,
  0x003D0000U,
  0xFFFFFFFFU,
  aFLASH_START_SECTOR,
  0,
  0,
  Open_SFLASH,
  0,
  0,
  0,
  0,
};

/* Prototypes *****************************************************************/
/* Functions ******************************************************************/

S32 Open_CANSTEER_V3 (void)
{
	/* Register Memories */
	register_MTD (&VIRTUAL_EEPROM);
    PRINTF("Virtual EEPROM registered \r\n");

	register_MTD (&EFLASH);
    PRINTF("FLASH registered \r\n");

    SystemCoreClockUpdate();

    Open_TIMEOUT();
    
#ifdef CAN_DEVICE
    Open_CAN(0);
#endif

	/* Address Device */ 
    read_MTD (EFLASH_BASE + EEPROM_J1939_ADDRESS, &J1939_SrcAddress, 1U);
    
	RxFilter_CAN (0U, ((((U32)J1939_PGN_BOOTLOADER) << 8) | ((U32)J1939_SrcAddress) << 8));
	
	/* Address Host */
	J1939_DstAddress = J1939_ADDRESS_FBOOT;

	return (0);
}
/* End of $Workfile: canseed.c$ */

