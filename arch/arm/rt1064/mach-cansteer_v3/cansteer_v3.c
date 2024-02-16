
             
/* Include ********************************************************************/
#include <cfg.h>
//#include <environment.cfg>
#include <types32.h>
#include <stdio.h>
#include <mach/cansteer_v3/cansteer_v3.h>
//#include <mach/iohubspifi/board_iohub.h>
//#include <timeout.h>
//#include <can.h>
//#include <usbh.h>
//#include <ohci.h>
#include <j1939.h>
#include <mtd.h>
//#include <fat.h>
//#include <chip.h>
//#include <board_api.h>

/* Defines ********************************************************************/
/* Typedefs *******************************************************************/
/* Globals ********************************************************************/
/*
 * Serial Number = 0001
 * Manufacture date = 03/09 
 * Hardware version = 1.2.0
 * Software version = 1.0.0 - build 1
 * J1939 Address = 233
 * Signature = Invalid Program 
 */

/* Statics ********************************************************************/
const uint32_t aFLASH_START_SECTOR[] = {0};
/*
*                         MEMORY MAP
*   Type                 Start         End         Size
* ----------------------------------------------------------
* E_FBOOT          -  0x70000000U - 0x7000FFFFU -  64 kB
* E_VIRTUAL_EEPROM -  0x70010000U - 0x7002FFFFU -  128 kB
* E_FLASH          -  0x70030000U - 0x70FFFFFFU -  (16 MB - 64kB - 128 kB)
*/

/* INTERNAL FLASH MEMORY MAPPING */
/* VIRTUAL EEPROM MEMORY MAPPING */
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
  0x00FD0000U,
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
/*
void HardFault_Handler(void)
{
    int i;
    while (1) {
        i = i;
        i++;
    }
}
*/
/***************************************************************************//*!
[General description here]

\param Param1         [Param1 description here]
\param Param2         [Param2 description here]
\return               [Return description here]
\note                 [Write notes here]
*******************************************************************************/
S32 Open_CANSTEER_V3 (void)
{
  	CHAR                str[24];

	/* Register Memories */
	register_MTD (&VIRTUAL_EEPROM);
	register_MTD (&EFLASH);
    
    SystemCoreClockUpdate();
    
    //Chip_GPIO_Init(LPC_GPIO_PORT);
	
	/* HW init */
    //IOHUB_Port_Init(0);
    //IOHUB_PowerMode(POWER_MODE_ON);
	//Open_TIMEOUT();
#ifdef CAN_DEVICE
    //Open_CAN(0);
#endif

	/* Address Device */ 
    read_MTD (EFLASH_BASE + EEPROM_J1939_ADDRESS, &J1939_SrcAddress, 1U);
    
	//RxFilter_CAN (0U, ((((U32)J1939_PGN_BOOTLOADER) << 8) | ((U32)J1939_SrcAddress) << 8));
	
	/* Address Host */
	J1939_DstAddress = J1939_ADDRESS_FBOOT; 
    /*
	// Print Version
	sprintf (str, "FBOOT %1d.%02d.%02x-build%02x", MAYOR_VER, MINOR_VER, RELEASE_VER,
	         BUILD_VER);
	Console (str);

	// Print Address Host
	sprintf (str, "CANbus Address [0x%02X]", J1939_SrcAddress);
	Console (str);
	*/
	return (0);
}
/*
void SYSTEM_Close(void) {
    IOHUB_PowerMode(POWER_MODE_STANDBY);
}
*/
/***************************************************************************//*!
[General description here]

\param Param1         [Param1 description here]
\param Param2         [Param2 description here]
\return               [Return description here]
\note                 [Write notes here]
*******************************************************************************/
/*
void Console (CHAR* pTEXT)
{
    PRINT_Log (pTEXT); 
    PRINT_Log ("\n"); 
}
*/
/***************************************************************************//*!
[General description here]

\param Param1         [Param1 description here]
\param Param2         [Param2 description here]
\return               [Return description here]
\note                 [Write notes here]
*******************************************************************************/
/*
char ConsoleGetChar (void)
{
    return Board_UARTGetChar();
}*/
/***************************************************************************//*!
[General description here]

\param Param1         [Param1 description here]
\param Param2         [Param2 description here]
\return               [Return description here]
\note                 [Write notes here]
*******************************************************************************/
/*
void Console_Led (LED_E eLed)
{
    static uint8_t i;
    
    switch (eLed) {
        case LED_1_TOGGLE:
            i++;
            break;

        case LED_2_TOGGLE:
            break;

        default:
            i = 0;
            break;
    }
#ifdef FOR_VDU7

#else
    // Disabled for compatibility with vdu7
    //Chip_GPIO_WritePortBit(LPC_GPIO_PORT, 1, 2, i&0x1); // Backlight
#endif
    Chip_GPIO_WritePortBit(LPC_GPIO_PORT, 5,15, i&0x1); // Blue Led 1
    Chip_GPIO_WritePortBit(LPC_GPIO_PORT, 5,16, i&0x1); // Blue Led 2
}
*/
/* End of $Workfile: canseed.c$ */

