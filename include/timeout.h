

#ifndef TIMEOUT_H
#define TIMEOUT_H
#include "types32.h"
#include "fsl_pit.h"

/* Include ********************************************************************/
/* Enums **********************************************************************/
/* Defines ********************************************************************/
#define BOARD_PIT_PERIPHERAL PIT
/* Definition of clock source frequency. */
#define BOARD_PIT_CLK_FREQ 75000000UL
/* Definition of ticks count for channel 0 - deprecated. */
#define BOARD_PIT_0_TICKS 75000U
/* PIT interrupt vector ID (number) - deprecated. */
#define BOARD_PIT_0_IRQN PIT_IRQn
/* PIT interrupt handler identifier - deprecated. */
#define BOARD_PIT_0_IRQHANDLER PIT0_IRQHandler
/* Definition of channel number for channel 0. */
#define BOARD_PIT_CHANNEL_0 kPIT_Chnl_0
/* Definition of ticks count for channel 0. */
#define BOARD_PIT_CHANNEL_0_TICKS 75000U
/* PIT interrupt vector ID (number). */
#define BOARD_PIT_IRQN PIT_IRQn
/* PIT interrupt handler identifier. */
#define BOARD_PIT_IRQHANDLER PIT_IRQHandler

#define while_timeout(x, y)       \
while (timeout (x, y) == false);  \
reset_timeout()

#define break_timeout             \
HasTimeout = false;               \
reset_timeout();                  \
break

/* Typedefs *******************************************************************/
/* Externs ********************************************************************/
extern volatile bool	HasTimeout;

/* Prototypes *****************************************************************/

#if defined(__cplusplus)
extern "C" 
{
#endif

void                    Open_TIMEOUT (void);
void                    Close_TIMEOUT (void);
bool                    timeout (uint32_t TimeInMSeconds, void (*FunctionTM)(void));
void                    reset_timeout (void);
bool                    if_has_timeout (void);
void                    delayMS (uint32_t delay);

#if defined(__cplusplus)
}
#endif

#endif /* TIMEOUT_H */

/* End of $Workfile: timeout.h$ */
