
/* Include ********************************************************************/
#include <cfg.h>
#include <stdio.h>

//#include <environment.cfg>
#include <typedef.h>
#include <types32.h>
//#include <usbh.h>
//#include <chip.h>
#include <mach/cansteer_v3/cansteer_v3.h>
#include <timeout.h>
#include <can.h>
#include <mtd.h>
#include <j1939.h>
#include <dbl.h>

/* Defines ********************************************************************/
#if defined ARCH_ARM
#define Mode_SVC                            0x13
#define I_Bit                               0x80 /* when I bit is set, IRQ is disabled */
#define F_Bit                               0x40 /* when F bit is set, FIQ is disabled */
#endif

/* Typedefs *******************************************************************/
/* Globals ********************************************************************/
/* Statics ********************************************************************/
#ifdef ARCH_PIC
#pragma udata           gprm
#endif

#ifdef ARCH_ARM
//static  CHAR            str[100];
#endif

#if defined (MACH_VDU) || defined (MACH_SBOX) || defined (MACH_SBOXPLUS) || defined (MACH_EOS)
U8                      aBUFFER[MEMORY_TRANSFER_MAX];
#else
//U8                      aBUFFER[MEMORY_BUFFER_SIZE_USB];
#endif

void                    App (void);

/* Prototypes *****************************************************************/
/* Functions ******************************************************************/
//__weak void SYSTEM_Close(void) { }

/***************************************************************************//*!
[General description here]

\param Param1         [Param1 description here]
\param Param2         [Param2 description here]
\return               [Return description here]
\note          TXmsg = 0 ST0 ST1 ST2 ST3 MT0 MT1 MT2 
                  ST = Status Memory.
                  MT = Memory Transfer in Bytes.
               RXmsg = CMD AD0 AD1 AD2 AD3 MT0 MT1 MT2 
                 CMD = Command. 
                  AD = Address.
                  MT = Memory Transfer in Bytes.
*******************************************************************************/
/*
S32 DeviceCAN_BL (void)
{
    CMD_BL_E            eCMD_BL;
    U32                 uAddress;
    U32                 uSize;
    PFV                 pReset;
    U32                 i;
    BOOL32              if_timeout;

    eCMD_BL  = RDY_CMD_BL;
    uAddress = 0U;
    uSize    = 0U;

    PutCmdBL_J1939 (RDY_CMD_BL, 0U, MEMORY_TRANSFER_MAX);

#if defined (MACH_CANSEEDRADAR)
    Console_Led (LED_IDLE);
#endif

    // See if we enter in BOOTLOAD Mode
    if_timeout = GetCmdBL_J1939 ((U8*)&eCMD_BL, &uAddress, &uSize, 250U); 

    while (if_timeout == 0) {
        switch (eCMD_BL)
        {
            case RUN_CMD_BL:
            {
#if defined (MACH_CANSEEDRADAR)
                Console_Led (LED_RUN);
#endif
#ifdef ARCH_ARM 
                sprintf (str, "> Run   [ Start: 0x%08X ]", uAddress);      
                Console (str);
#endif
                // Delay 4 Sec.
                do {} while_timeout (4000U, 0);
#ifdef ARCH_ARM
                __DISABLE_FIQ();
                __DISABLE_IRQ();
#else
                DisableFIQ_P18F8680();
                DisableIRQ_P18F8680();
#endif
              Reset();
            } break;

            case READ_CMD_BL:
            {
#if defined (MACH_CANSEEDRADAR)
                Console_Led (LED_READ);
#endif
                if (read_MTD (uAddress, aBUFFER, uSize) == 0) {
#ifdef ARCH_ARM 
                    sprintf (str, "> Read   [ Start: 0x%08X   Size: 0x%08X ]", 
                             uAddress, 
                             uSize);
                    Console (str);
#if defined (MACH_DD)
                    Console_Led (LED_2_TOGGLE);
#endif
#endif
                } else {
#ifdef ARCH_ARM 
                    sprintf (str, "> Error   [ Start: 0x%08X   Size: 0x%08X ]", 
                             uAddress, 
                             uSize);
                    Console (str);
                    // Invalidate Data
                    for (i = 0; i < uSize; i++) {
                        aBUFFER[i] = 0;
                    }
#endif
                }                
                txBL_J1939 (aBUFFER, uSize);         
            } break;

            case WRITE_CMD_BL:
            {
#if defined (MACH_CANSEEDRADAR)
                Console_Led (LED_WRITE);
#endif      
                rxBL_J1939 (aBUFFER, uSize, 0U);                
                if (write_MTD (uAddress, aBUFFER, uSize) == 0) {
                    // This was moved before rxBL_J1939 because we already has send
                    //RDY, and we lose packets if we are drawing in the screen
#ifdef ARCH_ARM 
                    sprintf (str, "> Write   [ Start: 0x%08X   Size: 0x%08X ]", 
                             uAddress, 
                             uSize);
                    Console (str);
#if defined (MACH_DD)
                    Console_Led (LED_1_TOGGLE);
#endif
#endif
                } else {
#ifdef ARCH_ARM 
                    sprintf (str, "> Error   [ Start: 0x%08X   Size: 0x%08X ]", 
                             uAddress, 
                             uSize);
                    Console (str);                  
                }
#endif               
            } break;
            
            default: {} break;
        }
        
        //Send RDY
        PutCmdBL_J1939 (RDY_CMD_BL, 0U, MEMORY_TRANSFER_MAX);
#if defined (MACH_CANSEEDRADAR)
        Console_Led (LED_IDLE);
#endif 
#ifdef ARCH_ARM 
        sprintf (str, "< Rdy" );      
        Console (str);
#endif
        // Get CMD
        if_timeout = GetCmdBL_J1939 ((U8*)&eCMD_BL, &uAddress, &uSize, 0U);
    }

  
    return (0);
}
*/
/***************************************************************************//*!
[General description here]

\param Param1         [Param1 description here]
\param Param2         [Param2 description here]
\return               [Return description here]
\note                 [Write notes here]
*******************************************************************************/
void Run_BL (void)
{
    U32                 uStatusMemory;
    //U32                 Mayor_Ver;
    //U32                 Minor_Ver;
    //U32                 Release_Ver;
    //U32                 Build_Ver;
    U32                 uAppIDECU;
    U32                 uSoftVerECU;
    
#define MEMORY_READ_BASE EEPROM_BASE

    read_MTD (MEMORY_READ_BASE + EEPROM_STATUS_MEMORY, (U8*)&uStatusMemory, 4U);
 
    if (uStatusMemory == SIGNATURE_STATUS_MEMORY_OK){
        /* Check Application ID */
        read_MTD (MEMORY_READ_BASE + EEPROM_APPLICATION_ID, (U8*)&uAppIDECU, 1U);
        uAppIDECU &= 0xFFU;

        /* Check Software Version in Device */
        read_MTD (MEMORY_READ_BASE + EEPROM_SOFTWARE_VER_INFO, (U8*)&uSoftVerECU, 3U);
/*
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
        

        Close_TIMEOUT();
        Close_CAN();
*/
        App ();



    } else {
        //sprintf (str, "Status: INVALID program");


    }
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

