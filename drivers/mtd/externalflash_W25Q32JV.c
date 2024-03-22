/* Include ********************************************************************/
#include <stdio.h>

#include "cfg.h"
#include "types32.h"
#include "mtd.h"

/*---CSP---*/
#include "sflash_W25Q32JV.h"

/* Defines ********************************************************************/
#define SECTOR_SIZE                         0x400U

#define SFLASH_SECTOR_SIZE                  0x10000U
#define SFLASH_START_ENTRY                  0x70030000U

/* Typedefs *******************************************************************/
/* Globals ********************************************************************/
/* Statics ********************************************************************/
static MTD_T*           pMTD;

/* Prototypes *****************************************************************/
static S32              Read_SFLASH (U32 Address, U8* pData, U32 Size);
static S32              Write_SFLASH (U32 Address, U8* pData, U32 Size);
static S32              EraseSector_SFLASH (U32 Address, U32 Size);
static S32              Close_SFLASH (void);

/* Functions ******************************************************************/

int32_t Open_SFLASH (MTD_T* ptMTD)
{
    pMTD         = ptMTD;
	ptMTD->read  = Read_SFLASH;
	ptMTD->write = Write_SFLASH;
    //ptMTD->erase = EraseSector_SFLASH;
    ptMTD->erase = 0;
    ptMTD->close = Close_SFLASH;
    
    return (Init_SFLASH());
}

int32_t Init_SFLASH (void)
{
	SFLASH_init();
    return (0);
}

static int32_t Read_SFLASH (uint32_t Address, uint8_t* pData, uint32_t Size)
{
    int32_t             Status;
   
    Status = _OK;

    /* Check if fit */
    if (Size <= pMTD->SizeDevice) {
        Status = Read_FLASH(Address, pData, Size);
    } else {
        Status = _ERROR;
    }

    return (Status);
}

int32_t Write_SFLASH (uint32_t Address, uint8_t* pData, uint32_t Size)
{
    S32 Status;
    U32 i;

    Status = _OK;
    
    if (Size != SECTOR_SIZE) {
        /* Cannot write if wrong size */
        return 2;
    }
    if (Size > pMTD->SizeDevice) {
        return 2;
    }
    if (Address < SFLASH_START_ENTRY){
        return 2;
    }
        
    EraseSector_SFLASH(Address, SECTOR_SIZE);
    __disable_irq();
    Address = Address - 0x70000000;
    for (i = 0; i < Size; i++) {
        if (SFLASH_WriteByte(BOARD_FLEXSPI,Address + i, pData[i]) != 0){
            return 2;
        }
    }
    __enable_irq();

    return Status; 
    
}

static int32_t EraseSector_SFLASH (uint32_t Address, uint32_t Size)
{
    int32_t             Status;

    Status = _OK;

    if (Address >= SFLASH_START_ENTRY) {
        if (((Address - SFLASH_START_ENTRY) & (SFLASH_SECTOR_SIZE - 1)) == 0) {
            Size /= SFLASH_SECTOR_SIZE;
            Address &= ~((U32)SFLASH_SECTOR_SIZE - 1U);
            do  
            {   
                Status = Erase_FLASH(Address, SFLASH_SECTOR_SIZE);
                if (Status != 0) {
                    return (_ERROR);
                }   
                Address += SFLASH_SECTOR_SIZE;
            } while (Size--);  
        }
    } else {
        Status = _ERROR;
    }
    
	return (Status);
}

int32_t Close_SFLASH (void)
{
    return (0);
}
/* End of $Workfile: sflash_W25Q32J.c$ */
