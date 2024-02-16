

#ifndef MTD_H
#define MTD_H

/* Include ********************************************************************/
/* Enums **********************************************************************/
/* Defines ********************************************************************/
#define NVRAM_BASE                          0xA0000000UL
#define SFLASH_BASE                         0xB0000000UL

/* Typedefs *******************************************************************/

typedef struct MTD_T MTD_T;
struct MTD_T
{
  uint32_t AddressDevice;
  uint32_t SizeDevice;
  uint32_t MaskAddress;
  const uint32_t* pStartSector; 
  uint32_t TimeOutWrite;  
  uint32_t TimeOutErase; 
  int32_t (*open) (MTD_T* ptMTD);
  int32_t (*read) (uint32_t Address, uint8_t* pData, uint32_t Size);
  int32_t (*write) (uint32_t Address, uint8_t* pData, uint32_t Size);
  int32_t (*erase) (uint32_t Address, uint32_t Size);
  int32_t (*close) (void);
};

/* Externs ********************************************************************/
extern const uint32_t   aFLASH_START_SECTOR[];
int32_t                 Init_SFLASH (void);
int32_t                 Init_VIRTUAL_EEPROM (void);
extern int32_t          Open_FLASH (MTD_T* ptMTD);
int32_t                 Open_IFLASH (MTD_T* ptMTD);
extern int32_t          Open_SFLASH (MTD_T* ptMTD);
extern int32_t          Open_EEPROM (MTD_T* ptMTD);
extern int32_t          Open_VIRTUAL_EEPROM (MTD_T* ptMTD);
extern int32_t          Open_NVRAM (MTD_T* ptMTD);

/* Prototypes *****************************************************************/
#if defined(__cplusplus)
extern "C" 
{
#endif

int32_t                 register_MTD (MTD_T* ptMTD);
int32_t                 write_MTD (uint32_t Address, uint8_t* pData, uint32_t Size);
int32_t                 read_MTD (uint32_t Address, uint8_t* pData, uint32_t Size);

#if defined(__cplusplus)
}
#endif

#endif

/* End of $Workfile: mtd.h$ */
