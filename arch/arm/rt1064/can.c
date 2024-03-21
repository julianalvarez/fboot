
/* Include ********************************************************************/
#include <cfg.h>
#include <types32.h>
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

/* Prototypes *****************************************************************/
/* Functions ******************************************************************/

S32 Open_CAN (U32 ctrl)
{
	BOARD_InitPins_CAN2();
	BOARD_InitCAN2();
	FLEXCAN_SetRxMbGlobalMask(BOARD_CAN2_PERIPHERAL, FLEXCAN_RX_MB_EXT_MASK(0, 0, 0));

    return 0;
}

void Close_CAN (void)
{
	FLEXCAN_Deinit(CAN2);
}

S8 RxFilter_CAN (U8 FilterN, U32 Data)
{
    aPGN_FILTER[FilterN] = Data;
    return 0; 
}

BOOL8 GetMSG_CAN (J1939MESSAGE_T* pMSG)
{
    uint32_t msgId;
    uint32_t i;
    BOOL8               match;

    match = FALSE;
    msgId = rxframe.id;

	pMSG->Priority = (msgId & 0x1C0000) >> 26;
	pMSG->PDUFormat = (msgId & 0x3FF0000) >> 16;
	pMSG->PDUSpecific = (msgId & 0xFF00) >> 8;
	pMSG->SourceAddress = msgId & 0xFF;
	pMSG->DataLength = rxframe.length;

    // Filter PGNS'
    msgId &= 0x1FFFF00;
    for (i = 0; i < MAX_PGN_FILTERS; i++) {
            if (aPGN_FILTER[i] == msgId) {
                match = true;
                break;
            }
    }

    if(match){
		// DATA FRAME
		*(uint8_t*) &pMSG->Data.Byte[0] = rxframe.dataByte0;
		*(uint8_t*) &pMSG->Data.Byte[1] = rxframe.dataByte1;
		*(uint8_t*) &pMSG->Data.Byte[2] = rxframe.dataByte2;
		*(uint8_t*) &pMSG->Data.Byte[3] = rxframe.dataByte3;
		*(uint8_t*) &pMSG->Data.Byte[4] = rxframe.dataByte4;
		*(uint8_t*) &pMSG->Data.Byte[5] = rxframe.dataByte5;
		*(uint8_t*) &pMSG->Data.Byte[6] = rxframe.dataByte6;
		*(uint8_t*) &pMSG->Data.Byte[7] = rxframe.dataByte7;
//    	if(rxframe.dataByte0 == 0x0 && rxframe.dataByte2 == 0x7e)
//    	{
//    		PRINTF("AFGAAGA");
//    	}
	    rxComplete = FALSE;
		return 1;
    }
    else{
        rxComplete = FALSE;
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
	while (!FLEXCAN_GetMbStatusFlags(TS_CAN, 1 << RX_MESSAGE_BUFFER_NUM));
	FLEXCAN_ReadRxMb(TS_CAN,RX_MESSAGE_BUFFER_NUM,&rxframe);
	rxComplete=true;
	while(!rxComplete);
	FLEXCAN_ClearMbStatusFlags(CAN2,1<<RX_MESSAGE_BUFFER_NUM);
}

U8 MsgReady_CAN (void)
{
  	/* Return true if msg ready, false if not */
  	return (rxComplete);
}

/* End of $Workfile: can.c$ */
