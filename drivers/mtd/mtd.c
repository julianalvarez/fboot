

/* Include ********************************************************************/
#include <cfg.h>

//#include <environment.cfg>
#include <types32.h>
#include <mtd.h>
#include <cmsis_gcc.h>

/* Defines ********************************************************************/
#define MAX_MTD                             8U

/* Typedefs *******************************************************************/
/* Globals ********************************************************************/
/* Statics ********************************************************************/
static MTD_T            tMTD[MAX_MTD];

/* Prototypes *****************************************************************/
static MTD_T*           find_MTD (U32 Address);

/* Functions ******************************************************************/

/***************************************************************************//*!
[General description here]

\param Param1         [Param1 description here]
\param Param2         [Param2 description here]
\return               [Return description here]
\note                 When we register, we OPEN the device too.
*******************************************************************************/
S32 register_MTD (MTD_T* ptMTD)
{
  U32                   i;

  /* find an empty structure */
  i = 0U;
  while (tMTD[i].SizeDevice != 0U)
  {
    i++;
  }

  tMTD[i].open          = ptMTD->open;
  tMTD[i].AddressDevice = ptMTD->AddressDevice;
  tMTD[i].MaskAddress   = ptMTD->MaskAddress;
  tMTD[i].SizeDevice    = ptMTD->SizeDevice; 
  tMTD[i].pStartSector  = ptMTD->pStartSector; 
  tMTD[i].TimeOutWrite  = ptMTD->TimeOutWrite;  
  tMTD[i].TimeOutErase  = ptMTD->TimeOutErase; 

  /* call here the Open func ? */
//  tMTD[i].open (&tMTD[i]);
  
  return (0);
}

/***************************************************************************//*!
[General description here]

\param Param1         [Param1 description here]
\param Param2         [Param2 description here]
\return               [Return description here]
\note                 [Write notes here]
*******************************************************************************/
S32 read_MTD (U32 Address, U8* pData, U32 Size)
{
  MTD_T*                ptMTD;

  /* We have to sanity check ptMTD */
  ptMTD = find_MTD (Address);

  if (ptMTD == NULL) {
    return -1;
  }
  __disable_irq();
  ptMTD->open(ptMTD);

  Address &= ptMTD->MaskAddress;

  ptMTD->read (Address, pData, Size);

  ptMTD->close();
  __enable_irq();

  return (0);
}

/***************************************************************************//*!
[General description here]

\param Param1         [Param1 description here]
\param Param2         [Param2 description here]
\return               [Return description here]
\note                 [Write notes here]
*******************************************************************************/
S32 write_MTD (U32 Address, U8* pData, U32 Size)
{
    MTD_T*              ptMTD;

    /* We have to sanity check ptMTD */
    ptMTD = find_MTD (Address);

    if (ptMTD == NULL) {
        return -1;
    }

    ptMTD->open(ptMTD);

    Address &= ptMTD->MaskAddress;

    if (ptMTD->erase != 0) {
        ptMTD->erase (Address, Size);
    }

    ptMTD->write (Address, pData, Size);

    ptMTD->close();

    return (0);
}

/***************************************************************************//*!
[General description here]

\param Param1         [Param1 description here]
\param Param2         [Param2 description here]
\return               [Return description here]
\note                 [Write notes here]
*******************************************************************************/
static MTD_T* find_MTD (U32 Address)
{
  U8                    i;

  i = 0U;
  while (i < MAX_MTD)
  {
    if ((tMTD[i].AddressDevice <= Address) && 
        ((tMTD[i].AddressDevice + tMTD[i].SizeDevice) > Address)) 
    {
      return (&tMTD[i]);
    }
    i++;
  }

  return NULL;
}
        
/* End of $Workfile: mtd.c$ */

