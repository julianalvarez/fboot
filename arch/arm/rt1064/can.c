

/* Include ********************************************************************/
#include <cfg.h>
//#include <environment.cfg>
#include <types32.h>
//#include <lpc_types.h>
//#include <arch/arm/lpc29xx/lpc29xx.h>
#include <can.h>
#include "fsl_debug_console.h"
#include "fsl_flexcan.h"
#include "board/pin_mux.h"
#include "board/peripherals.h"


/* Defines ********************************************************************/
#define PCLK                                120000000
#define MAX_PGN_FILTERS                     3
#define CAN_MAX_BUS_NR                      3U

#define TX_MESSAGE_BUFFER_NUM (2)
#define RX_MESSAGE_BUFFER_NUM (1)
#define TS_CAN CAN2

#define BOARD_CAN2_PERIPHERAL CAN2
/* Definition of the clock source frequency */
#define BOARD_CAN2_CLOCK_SOURCE 40000000UL
/* CAN2 interrupt vector ID (number). */
#define BOARD_CAN2_FLEXCAN_IRQN CAN2_IRQn
/* CAN2 interrupt handler identifier. */
#define BOARD_CAN2_FLEXCAN_IRQHANDLER CAN2_IRQHandler
/* Globals ********************************************************************/
/* Statics ********************************************************************/
U32              aPGN_FILTER[MAX_PGN_FILTERS];
volatile bool txComplete = false;
volatile bool rxComplete = false;
flexcan_handle_t flexcanHandle;
flexcan_mb_transfer_t txXfer, rxXfer;
flexcan_frame_t rxframe;

//static CAN_REGS_T*      __pCAN;

/* Prototypes *****************************************************************/
/* Functions ******************************************************************/

/*******************************************************************************
 *    Function Name:  .
 *    Parameters:     .
 *    Return Value:   .
 *
 *    Description:    .
 *
 *    Notes:					.
 ******************************************************************************//*
U8 MsgReady_CAN (void)
{
  	// Return true if msg ready, false if not
  	return (__pCAN->GS & (1 << 0));
}
*/
/*******************************************************************************
 *    Function Name:  .
 *    Parameters:     .
 *    Return Value:   .
 *
 *    Description:    .
 *
 *    Notes:					.
 ******************************************************************************//*
U8 WaitIdle_CAN (void)
{
  	// Return true if buffer is available, false if not
    return ((__pCAN->STAT & (1 << 2)) ? 0 : 1);
}
*/
/*******************************************************************************
 *    Function Name:  .
 *    Parameters:     .
 *    Return Value:   .
 *
 *    Description:    .
 *
 *    Notes:					.
 ******************************************************************************/
void ReleaseBF_CAN (void)
{
    //__pCAN->CMD = (1 << 2);                   /* Release receive buffer */
}

/*******************************************************************************
 *    Function Name:  .
 *    Parameters:     .
 *    Return Value:   .
 *
 *    Description:    .
 *
 *    Notes:					.
 ******************************************************************************/
void TxRequest_CAN (void)
{  

}

/*******************************************************************************
 *    Function Name:  .
 *    Parameters:     .
 *    Return Value:   .
 *
 *    Description:    .
 *
 *    Notes:					.
 ******************************************************************************/
void DisableINTRx_CAN (void)
{   

}

/*******************************************************************************
 *    Function Name:  .
 *    Parameters:     .
 *    Return Value:   .
 *
 *    Description:    .
 *
 *    Notes:					.
 ******************************************************************************/
void EnableINTRx_CAN (void)
{  
}

/*******************************************************************************
 *    Function Name:  .
 *    Parameters:     .
 *    Return Value:   .
 *
 *    Description:    .
 *
 *    Notes:					.
 ******************************************************************************/
void DisableINTTx_CAN (void)
{
}

/*******************************************************************************
 *    Function Name:  .
 *    Parameters:     .
 *    Return Value:   .
 *
 *    Description:    .
 *
 *    Notes:					.
 ******************************************************************************/
void EnableINTTx_CAN (void)
{

}

/*******************************************************************************
 *    Function Name:  .
 *    Parameters:     .
 *    Return Value:   .
 *
 *    Description:    .
 *
 *    Notes:					.
 ******************************************************************************/
void DisableINT_CAN (void)
{
}

/*******************************************************************************
 *    Function Name:  .
 *    Parameters:     .
 *    Return Value:   .
 *
 *    Description:    .
 *
 *    Notes:					.
 ******************************************************************************/
void EnableINT_CAN (void)
{
}

/*******************************************************************************
 *    Function Name:  .
 *    Parameters:     .
 *    Return Value:   .
 *
 *    Description:    .
 *
 *    Notes:					.
 ******************************************************************************/
void SetAddressFilter_CAN (U8 Address)
{

}

/*******************************************************************************
 *    Function Name:  .
 *    Parameters:     .
 *    Return Value:   .
 *
 *    Description:    .
 *
 *    Notes:					.
 ******************************************************************************/
void SelectRxBuffer_CAN (void)
{

}

/*******************************************************************************
 *    Function Name:  .
 *    Parameters:     .
 *    Return Value:   .
 *
 *    Description:    .
 *
 *    Notes:					.
 ******************************************************************************/
void SelectTxBuffer_CAN (U8 Window)
{

}

/*******************************************************************************
 *    Function Name:    .                            
 *    Parameters:  	    .
 *    Return Value: 	  .                                              
 *
 *    Description:      .
 *                           					            
 *    Notes:            CAN INTERRUPT Shall be ENABLED before ENABLE_IRQ
 *                      
 ******************************************************************************/

S32 Open_CAN (U32 ctrl)
{
	BOARD_InitPins_CAN2();
	BOARD_InitCAN2();
	FLEXCAN_SetRxMbGlobalMask(BOARD_CAN2_PERIPHERAL, FLEXCAN_RX_MB_EXT_MASK(0, 0, 0));

    return 0;

}

/*******************************************************************************
 *    Function Name:  .
 *    Parameters:     .
 *    Return Value:   .
 *
 *    Description:    .
 *
 *    Notes:					.
 ******************************************************************************/
void Close_CAN (void)
{

}

/*******************************************************************************
 *    Function Name:    .                            
 *    Parameters:  	    .
 *    Return Value: 	.                                              
 *
 *    Description:      .
 *                           					            
 *    Notes:       Byte3:  SID10 SID09 SID08 SID07 SID06 SID05 SID04 SID03
 *       									 bit28 bit27 bit26 bit25 bit24 bit23 bit22 bit21    					            
 *                 Byte2:  SID02 SID01 SID00 EID17 EID16 EID15 EID14 EID13
 *       									 bit20 bit19 bit18 bit17 bit16 bit15 bit14 bit13
 *                 Byte1:  EID12 EID11 EID10 EID09 EID08 EID07 EID06 EID05
 *       									 bit12 bit11 bit10 bit09 bit08 bit07 bit06 bit05
 *                 Byte0:  EID04 EID03 EID02 EID01 EID00  xx    xx    xx   
 *       									 bit04 bit03 bit02 bit01 bit00  xx    xx    xx  
 ******************************************************************************/
S8 RxFilter_CAN (U8 FilterN, U32 Data)
{
    aPGN_FILTER[FilterN] = Data;
    return 0; 
}

/*******************************************************************************
 *    Function Name:    .                            
 *    Parameters:  	    .
 *    Return Value: 	  .                                              
 *
 *    Description:      .
 *                           					            
 *    Notes:           
 *            Byte0:  BIT7 BIT6 BIT5 BIT4 BIT3 BIT2 BIT1 BIT0 
 *                     FF   RTR  x    x   DLC3 DLC2 DLC1 DLC0 
 *            Byte1:  BIT7 BIT6 BIT5 BIT4 BIT3 BIT2 BIT1 BIT0 
 *                     x    x    x   ID28 ID27 ID26 ID25 ID24    
 *            Byte2:  BIT7 BIT6 BIT5 BIT4 BIT3 BIT2 BIT1 BIT0 
 *                    ID23 ID22 ID21 ID20 ID19 ID18 ID17 ID16   
 *            Byte3:  BIT7 BIT6 BIT5 BIT4 BIT3 BIT2 BIT1 BIT0 
 *                    ID15 ID14 ID13 ID12 ID11 ID10 ID09 ID08   
 *            Byte4:  BIT7 BIT6 BIT5 BIT4 BIT3 BIT2 BIT1 BIT0
 *                    ID07 ID06 ID05 ID04 ID03 ID02 ID01 ID00
 ******************************************************************************/
BOOL8 GetMSG_CAN (J1939MESSAGE_T* pMSG)
{
	uint32_t msgId;

	if(rxComplete){
		msgId = rxframe.id;

		pMSG->Priority = (msgId & 0x1C0000) >> 26;
		pMSG->PDUFormat = (msgId & 0x3FF0000) >> 16;
		pMSG->PDUSpecific = (msgId & 0xFF00) >> 8;
		pMSG->SourceAddress = msgId & 0xFF;
		pMSG->DataLength = rxframe.length;
		// DATA FRAME
		*(uint8_t*) &pMSG->Data.Byte[0] = rxframe.dataByte0;
		*(uint8_t*) &pMSG->Data.Byte[1] = rxframe.dataByte1;
		*(uint8_t*) &pMSG->Data.Byte[2] = rxframe.dataByte2;
		*(uint8_t*) &pMSG->Data.Byte[3] = rxframe.dataByte3;
		*(uint8_t*) &pMSG->Data.Byte[4] = rxframe.dataByte4;
		*(uint8_t*) &pMSG->Data.Byte[5] = rxframe.dataByte5;
		*(uint8_t*) &pMSG->Data.Byte[6] = rxframe.dataByte6;
		*(uint8_t*) &pMSG->Data.Byte[7] = rxframe.dataByte7;
		rxComplete = false;
		return 1;
	}
	else
	{
		return 0;
	}

}


void PutMSG_CAN (J1939MESSAGE_T* pMSG)
{
	flexcan_frame_t frame;

	frame.format = pMSG->PDUFormat;
	frame.type = kFLEXCAN_FrameTypeData;
	frame.id =  FLEXCAN_ID_EXT((((uint32_t)pMSG->Priority) << 26)  |
               (((uint32_t)pMSG->PDUFormat) << 16) |
               (((uint32_t)pMSG->PDUSpecific) << 8)|
               (uint32_t)pMSG->SourceAddress);
	frame.length = pMSG->DataLength;

	frame.dataByte0 = pMSG->Data.Byte[0];
	frame.dataByte1 = pMSG->Data.Byte[1];
	frame.dataByte2 = pMSG->Data.Byte[2];
	frame.dataByte3 = pMSG->Data.Byte[3];
	frame.dataByte4 = pMSG->Data.Byte[4];
	frame.dataByte5 = pMSG->Data.Byte[5];
	frame.dataByte6 = pMSG->Data.Byte[6];
	frame.dataByte7 = pMSG->Data.Byte[7];

	FLEXCAN_TransferSendBlocking(TS_CAN, TX_MESSAGE_BUFFER_NUM, &frame);
}



void BOARD_CAN2_FLEXCAN_IRQHANDLER(void)
{
	if (FLEXCAN_GetMbStatusFlags(TS_CAN,1<<RX_MESSAGE_BUFFER_NUM))
	{
		FLEXCAN_ClearMbStatusFlags(CAN2,1<<RX_MESSAGE_BUFFER_NUM);
		FLEXCAN_ReadRxMb(TS_CAN,RX_MESSAGE_BUFFER_NUM,&rxframe);
		rxComplete=true;
	}
}
/* End of $Workfile: can.c$ */
