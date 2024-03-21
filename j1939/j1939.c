
/* Include ********************************************************************/
#include <cfg.h>
#include <typedef.h>
#include <types32.h>
#include <timeout.h>
#include <can.h>
#include <j1939.h>
#include <stdio.h>
#include "fsl_debug_console.h"

/*                  
 *  FIXME: Check SA and DA every Packet.
 */ 

/* Defines ********************************************************************/
/* Globals ********************************************************************/
U8                      J1939_SrcAddress;
U8                      J1939_DstAddress;

/* Statics ********************************************************************/
/* Prototypes *****************************************************************/
/* Functions ******************************************************************/

void txBL_J1939 (U8* pData, U32 Size)
{
  U32                   tmp;

  while (Size)
  {
    if (Size >= 8U)
    {
      tmp = 8U;
    }
    else
    {
      tmp = Size;
    }

    TransmitMessage_J1939 (J1939_PGN_BOOTLOADER | J1939_DstAddress,
                           J1939_BOOTLOADER_PRIORITY, 
                           pData,
                           tmp); 
    pData += 8U;
    Size -= tmp;
  }
}

S32 rxBL_J1939 (U8* pData, U32 Size, U32 Timeout)
{
  J1939MESSAGE_T        OneMessage;
  U32                   tmp;

  while (Size)
  {
    if (Size >= 8U)
    {
      tmp = 8U;
    }
    else
    {
      tmp = Size;
    }

    do
    {
      if (ReceiveMessages_J1939 (&OneMessage) == TRUE)
      {
        /* Check If MSG comes from our Remote Ecu */
        if (OneMessage.SourceAddress == J1939_DstAddress)
        {
          mmemcpy (OneMessage.Data.Byte, pData, tmp);
          pData += tmp;
          break_timeout;
        }
      }
    } while_timeout (Timeout, 0);

    if (if_has_timeout() == TRUE)
    {
      break;
    }

    Size -= tmp;
  }

  return (if_has_timeout());
}

void PutCmdBL_J1939 (U8 Cmd, U32 Address, U32 Size) 
{
  U8                    Data[8];

  Data[0] = Cmd;
  mmemcpy ((U8*)&Address, &Data[1], 4U);
  /* Data[6] = 0U; What this? */
  mmemcpy ((U8*)&Size, &Data[5], 3U);          
  TransmitMessage_J1939 (J1939_PGN_BOOTLOADER | J1939_DstAddress, 
                         J1939_BOOTLOADER_PRIORITY, 
                         Data,
                         8U);
}

S32 GetCmdBL_J1939 (U8* Cmd, U32* Address, U32* Size, U32 Timeout) 
{
  J1939MESSAGE_T        OneMessage;
  
  do
  {
    if (ReceiveMessages_J1939 (&OneMessage) == TRUE)
    {
      /* Check If MSG comes from our Remote Ecu */
      if (OneMessage.SourceAddress == J1939_DstAddress)
      {
        *Cmd = OneMessage.Data.Byte[0];
        mmemcpy (&OneMessage.Data.Byte[1], (U8*)Address, 4U);
        *Size = 0U;
        mmemcpy (&OneMessage.Data.Byte[5], (U8*)Size, 3U);
        break_timeout;
      }
    } 
  } while_timeout (Timeout, 0);
       
  return ((S32)if_has_timeout());
}

void TransmitMessage_J1939 (U16 Pgn, U8 Prio, U8* pData, U32 Size)
{
  J1939MESSAGE_T 				OneMessage;

  OneMessage.bfEFF    = TRUE;
  OneMessage.bfRTR    = FALSE;
  OneMessage.Rvd      = 0U;
  OneMessage.Rvd2     = 0U;
  OneMessage.Rvd3     = 0U;		
  OneMessage.DataPage = 0U;

  OneMessage.Priority      = Prio;
  OneMessage.DataLength    = Size;
  OneMessage.PDUFormat     = Pgn >> 8; 
  OneMessage.PDUSpecific   = Pgn & 0xFFU;
  OneMessage.SourceAddress = J1939_SrcAddress;

  mmemcpy (pData, OneMessage.Data.Byte, Size);

  do 
  {
        PutMSG_CAN (&OneMessage);
        break_timeout;
  } while_timeout (1000, 0);
}

S32 ReceiveMessages_J1939 (J1939MESSAGE_T* pOneMessage)
{
	BOOL8                 bfPutInReceive = FALSE;

	while (MsgReady_CAN() != 0U)
	{
		/* Get the Message */
		bfPutInReceive = GetMSG_CAN (pOneMessage);
	}
	return (bfPutInReceive);
}

void mmemcpy (U8* pSrc, U8* pDst, U8 Size)
{
  while (Size--)
  {
    *pDst++ = *pSrc++;
  } 
}

/* End of $Workfile: j1939.c$ */

