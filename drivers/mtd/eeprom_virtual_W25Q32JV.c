/* Include ********************************************************************/
#include <cfg.h>
#include <stdio.h>
#include <types32.h>
#include <mtd.h>
//#include <chip.h>
#include <eeprom_virtual.h>

/* Defines ********************************************************************/
#define VIRTUAL_EEPROM_NUMBER_OF_VARIABLES          512

/* Typedefs *******************************************************************/
/* Globals ********************************************************************/

/* Statics ********************************************************************/
static MTD_T*           pMTD;

/* Prototypes *****************************************************************/
static S32              Read_VIRTUAL_EEPROM (U32 Address, U8* pData, U32 Size);
static S32              Write_VIRTUAL_EEPROM (U32 Address, U8* pData, U32 Size);
static S32              Erase_VIRTUAL_EEPROM (U32 Address, U32 Size);
static S32              Close_VIRTUAL_EEPROM (void);

/* Functions ******************************************************************/

/*******************************************************************************
*    Function Name:  .
*    Parameters:     .
*    Return Value:   .
*
*    Description:    .
*
*    Notes:          .
*******************************************************************************/
int32_t Open_VIRTUAL_EEPROM (MTD_T* ptMTD)
{    
    pMTD         = ptMTD;
	ptMTD->read  = Read_VIRTUAL_EEPROM;
	ptMTD->write = Write_VIRTUAL_EEPROM;
    ptMTD->erase = Erase_VIRTUAL_EEPROM;
    ptMTD->close = Close_VIRTUAL_EEPROM;
    
    return (Init_VIRTUAL_EEPROM());
}

/*******************************************************************************
*    Function Name:  .
*    Parameters:     .
*    Return Value:   .
*
*    Description:    .
*
*    Notes:          .
*******************************************************************************/
int32_t Init_VIRTUAL_EEPROM (void)
{
    EE_Init(VIRTUAL_EEPROM_NUMBER_OF_VARIABLES);
    return (0);     
}

/*******************************************************************************
*    Function Name:  .
*    Parameters:     .
*    Return Value:   .
*
*    Description:    .
*
*    Notes:          .
*******************************************************************************/
static int32_t Read_VIRTUAL_EEPROM (uint32_t Address, uint8_t* pData, uint32_t Size)
{
    int32_t  Status;
    uint16_t Data16;
    uint32_t  i;
   
    Status = _OK;
    
    Data16 = 0xFFFF;
    
    /* Check if fit */
    if (Size <= pMTD->SizeDevice) {
        for (i = 0; i < Size; i++){
            Status = EE_ReadVariable((uint16_t)Address + i, &Data16);
            if (Status != 0){
                return _ERROR;
            }
            *pData = (uint8_t) Data16;
            pData++;
        }
        
    } else {
        Status = _ERROR;
    }

    return (Status);
}

/*******************************************************************************
*    Function Name:  .
*    Parameters:     .
*    Return Value:   .
*
*    Description:    .
*
*    Notes:          Size <= 256 Bytes.
*******************************************************************************/
int32_t Write_VIRTUAL_EEPROM (uint32_t Address, uint8_t* pData, uint32_t Size)
{
    S32       Status;
    uint16_t Data16;
    uint32_t i;

    Status = _OK;

    /* Check if fit */
    if (Size <= pMTD->SizeDevice) {
        for (i = 0; i < Size; i++){
            Data16 = (uint16_t) *pData;
            Status = EE_WriteVariable((uint16_t)Address + i, Data16);
            pData++;
        }
    } else {
        Status = _ERROR;
	}
  
    return (Status);
}

/*******************************************************************************
*    Function Name:  .
*    Parameters:     .
*    Return Value:   .
*
*    Description:    .
*
*    Notes:          Size multiple of SFLASH_SECTOR_SIZE
*******************************************************************************/
static int32_t Erase_VIRTUAL_EEPROM (uint32_t Address, uint32_t Size)
{
    return (0);
}

/*******************************************************************************
*    Function Name:  .
*    Parameters:     .
*    Return Value:   .
*
*    Description:    .
*
*    Notes:          .
*******************************************************************************/
int32_t Close_VIRTUAL_EEPROM (void)
{
    return (0);
}

/* End of $Workfile: EEPROM_S25FL128S.c$ */

