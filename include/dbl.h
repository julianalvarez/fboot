

#ifndef DBL_H
#define DBL_H

/* Include ********************************************************************/
/* Enums **********************************************************************/
typedef enum
{
  RDY_CMD_BL,
  RUN_CMD_BL,
  READ_CMD_BL,
  WRITE_CMD_BL
} CMD_BL_E;

/* Defines ********************************************************************/
#define SIGNATURE_STATUS_MEMORY_OK          0xDEADBEEFL


#define FLASH_START_ENTRY_ARCH_ARM          0x70010000L

#define FLASH_START_ENTRY_ARCH_PIC          0x00002000L

/* Typedefs *******************************************************************/
/* Externs ********************************************************************/
//extern U8               aBUFFER[MEMORY_TRANSFER_MAX];
extern U8               aBUFFER[];

/* Prototypes *****************************************************************/

#if defined(__cplusplus)
extern "C" 
{
#endif

S32                     DeviceCAN_BL (void);
S32                     DeviceUSB_BL (void);
S32                     DeviceSERIAL_BL (void);
void                    Run_BL (void);

#if defined(__cplusplus)
}
#endif

#endif /* DBL_H */

/* End of $Workfile: dbl.h$ */
