
/* Include ********************************************************************/
#include <cfg.h>
#include <stdio.h>
#include <typedef.h>
#include <types32.h>
#include <cmsis_gcc.h>
#include <mach/cansteer_v3/cansteer_v3.h>
#include <timeout.h>
#include <can.h>
#include <mtd.h>
#include <j1939.h>
#include <dbl.h>
#include "fsl_debug_console.h"

/* Defines ********************************************************************/
#if defined ARCH_ARM
#define Mode_SVC                            0x13
#define I_Bit                               0x80 /* when I bit is set, IRQ is disabled */
#define F_Bit                               0x40 /* when F bit is set, FIQ is disabled */
#endif

/* Typedefs *******************************************************************/
/* Globals ********************************************************************/
/* Statics ********************************************************************/

#define MEMORY_BUFFER_SIZE_USB              4096U  /* Size of Memory for general use */

U8                      aBUFFER[MEMORY_BUFFER_SIZE_USB];

void                    App (void);

/* Prototypes *****************************************************************/
/* Functions ******************************************************************/

S32 DeviceCAN_BL (void)
{
    CMD_BL_E            eCMD_BL;
    U32                 uAddress;
    U32                 uSize;
    U32                 i;
    BOOL32              if_timeout;

    eCMD_BL  = RDY_CMD_BL;
    uAddress = 0U;
    uSize    = 0U;

    PutCmdBL_J1939 (RDY_CMD_BL, 0U, MEMORY_TRANSFER_MAX);

    // See if we enter in BOOTLOAD Mode
    if_timeout = GetCmdBL_J1939 ((U8*)&eCMD_BL, &uAddress, &uSize, 250U); 

    while (if_timeout == 0) {
        switch (eCMD_BL)
        {
            case RUN_CMD_BL:
            {
                PRINTF( "> Run   [ Start: 0x%08X ]", uAddress);
                // Delay 4 Sec.
                do {} while_timeout (4000U, 0);
                //__DISABLE_FIQ();
                __disable_irq();
              Reset();
            } break;

            case READ_CMD_BL:
            {
                if (read_MTD (uAddress, aBUFFER, uSize) == 0) {
                	PRINTF( "> Read   [ Start: 0x%08X   Size: 0x%08X ]",
                             uAddress, 
                             uSize);
                } else {
                	PRINTF( "> Error   [ Start: 0x%08X   Size: 0x%08X ]",
                             uAddress, 
                             uSize);
                    // Invalidate Data
                    for (i = 0; i < uSize; i++) {
                        aBUFFER[i] = 0;
                    }
                }                
                txBL_J1939 (aBUFFER, uSize);         
            } break;

            case WRITE_CMD_BL:
            {
                rxBL_J1939 (aBUFFER, uSize, 0U);                
                if (write_MTD (uAddress, aBUFFER, uSize) == 0) {
                    // This was moved before rxBL_J1939 because we already has send
                    //RDY, and we lose packets if we are drawing in the screen
                	PRINTF( "> Write   [ Start: 0x%08X   Size: 0x%08X ]",
                             uAddress, 
                             uSize);

                } else {
                	PRINTF( "> Error   [ Start: 0x%08X   Size: 0x%08X ]",
                             uAddress, 
                             uSize);
                }
            } break;
            
            default: {} break;
        }
        
        //Send RDY
        PutCmdBL_J1939 (RDY_CMD_BL, 0U, MEMORY_TRANSFER_MAX);
        PRINTF("< Rdy" );
        // Get CMD
        if_timeout = GetCmdBL_J1939 ((U8*)&eCMD_BL, &uAddress, &uSize, 0U);
    }


    return (0);
}

void Run_BL (void)
{/*
    U32                 uStatusMemory;
    //U32                 Mayor_Ver;
    //U32                 Minor_Ver;
    //U32                 Release_Ver;
    //U32                 Build_Ver;
    U32                 uAppIDECU;
    U32                 uSoftVerECU;
    
#define MEMORY_READ_BASE EEPROM_BASE

    read_MTD (MEMORY_READ_BASE + EEPROM_STATUS_MEMORY, (U8*)&uStatusMemory, 4U);
 
    //if (uStatusMemory == SIGNATURE_STATUS_MEMORY_OK){
        // Check Application ID
        read_MTD (MEMORY_READ_BASE + EEPROM_APPLICATION_ID, (U8*)&uAppIDECU, 1U);
        uAppIDECU &= 0xFFU;

        // Check Software Version in Device
        read_MTD (MEMORY_READ_BASE + EEPROM_SOFTWARE_VER_INFO, (U8*)&uSoftVerECU, 3U);

        Build_Ver   = (uSoftVerECU >> 16) & 0xFFU;
        Mayor_Ver   = (uSoftVerECU >> 12) & 0x0FU;
        Minor_Ver   = (uSoftVerECU >>  4) & 0x0FU;
        Release_Ver =  uSoftVerECU        & 0x0FU;

        // Jump to Application
        sprintf (str, "Running SW AppID: %2d Ver: %1d.%1d.%1d-build%2d", 
                 uAppIDECU, Mayor_Ver, Minor_Ver, Release_Ver, Build_Ver);
        Console (str);
        // Delay 100ms to wait the print in console before jump to program.
        do {} while_timeout (100U, 0);
        



*/
		Close_TIMEOUT();
		Close_CAN();
        App ();



    //} else {
        //sprintf (str, "Status: INVALID program");


   // }
}

#if defined (MACH_CANSEED) || (MACH_CANSEEDRADAR) || defined(MACH_SMARTANTENNA) || defined(MACH_CANLIGHT) || defined (MACH_IOHUB) || defined (MACH_IOHUB_SPIFI) || defined (MACH_ECUROW) || defined(MACH_ACTIVESINGULATION)
typedef struct{ 
  uint32_t stack_address;       //initial value of stack pointer is stored at top of vector table
  void (*reset_address)(void);  //reset vector with entry address is located at second 32-bit word  
}vector_table_layout;

void App (void)
{
  vector_table_layout const*const user_vector_table=(vector_table_layout*)FLASH_START_ENTRY;  

  __disable_irq();                  //no interrupt should be enabled by bootloader, but disable interrupts to be on safe side
  SCB->VTOR = FLASH_START_ENTRY;    //set vector table offset to user code
  __enable_irq();
    
  __set_MSP(user_vector_table->stack_address);//load stackpointer with initial value  
  (user_vector_table->reset_address)();       //call user code
}
#endif



/* End of $Workfile: dblcan.c$ */

