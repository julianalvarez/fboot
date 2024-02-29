

#ifndef CAN_H
#define CAN_H

/* Include ********************************************************************/
/*
#include <board/pin_mux.h>
#include <board/peripherals.h>
#include <board/board.h>
*/
#include "j1939.h"
/* Enums **********************************************************************/
/* Defines ********************************************************************/
/* Typedefs *******************************************************************/
/* Externs ********************************************************************/
/* Prototypes *****************************************************************/



#if defined(__cplusplus)
extern "C" 
{
#endif

U8	                    MsgReady_CAN (void);
U8                      WaitIdle_CAN (void);
void                    ReleaseBF_CAN (void);

S8                      RxFilter_CAN (U8 FilterN, U32 Data); 

S32                     Open_CAN (U32 ctrl);
void                    Close_CAN (void);

BOOL8                   GetMSG_CAN (J1939MESSAGE_T* pMSG);
void                    PutMSG_CAN (J1939MESSAGE_T* pMSG);

bool 					CAN_GetTxComplete (void);
bool 					CAN_GetRxComplete (void);

#if defined(__cplusplus)
}
#endif

#endif /* end CAN_H */

/* End of $Workfile: can.h$ */
