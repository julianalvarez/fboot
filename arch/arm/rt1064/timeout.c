

/* Include ********************************************************************/
#include <typedef.h>
#include <timeout.h>

/* Defines ********************************************************************/
#define PERIOD_TIMER                        1U

/* Globals ********************************************************************/
volatile bool	        HasTimeout;

/* Statics ********************************************************************/
static bool             _init = false;
static uint16_t         TimeOut;
static uint16_t	        CounterTimeOut;
static void 		    (*FunctionTM) (void);

/* Prototypes *****************************************************************/
/* Functions ******************************************************************/

const pit_config_t BOARD_PIT_boot_config = {
  .enableRunInDebug = false
};
void Open_TIMEOUT (void)
{
	/* Initialize the PIT. */
	PIT_Init(BOARD_PIT_PERIPHERAL, &BOARD_PIT_boot_config);
	/* Set channel 0 period to 1 ms (75000 ticks). */
	PIT_SetTimerPeriod(BOARD_PIT_PERIPHERAL, BOARD_PIT_CHANNEL_0, BOARD_PIT_CHANNEL_0_TICKS);
	/* Enable interrupts from channel 0. */
	PIT_EnableInterrupts(BOARD_PIT_PERIPHERAL, BOARD_PIT_CHANNEL_0, kPIT_TimerInterruptEnable);
	/* Enable interrupt BOARD_PIT_IRQN request in the NVIC */
	EnableIRQ(BOARD_PIT_IRQN);
	/* Start channel 0. */
	PIT_StartTimer(BOARD_PIT_PERIPHERAL, BOARD_PIT_CHANNEL_0);
}

void Close_TIMEOUT (void)
{
    NVIC_DisableIRQ(BOARD_PIT_IRQN);
}

/* PIT_IRQn interrupt handler */
void BOARD_PIT_IRQHANDLER(void) {
	uint32_t status;

	status = PIT_GetStatusFlags(PIT, kPIT_Chnl_0);
	if(status & kPIT_TimerFlag){
		PIT_ClearStatusFlags(BOARD_PIT_PERIPHERAL,BOARD_PIT_CHANNEL_0,kPIT_TimerFlag);
			/* TIMEOUT */
		if (TimeOut > 0U) {

			CounterTimeOut++;
			if (CounterTimeOut >= TimeOut) {
				TimeOut    = 0U;
				HasTimeout = true;
				if (FunctionTM != NULL) {
					FunctionTM();
				}
			}
		}
	}
}

bool timeout (uint32_t TimeInMSeconds, void (*pfv)(void))
{    
    __disable_irq();
    if (_init == false) {
		_init          = true;
        TimeOut        = (uint16_t)(TimeInMSeconds / PERIOD_TIMER);
        CounterTimeOut = 0U;
        FunctionTM     = pfv;
        HasTimeout     = false;
    }
    __enable_irq();
    return (HasTimeout);
}

void reset_timeout (void)
{
    __disable_irq();
    _init          = false;
    TimeOut        = 0U;
    CounterTimeOut = 0U;
    FunctionTM     = 0U;
    __enable_irq();
}

bool if_has_timeout (void)
{
    bool                result;

    result = HasTimeout;

    HasTimeout = false;

    return (result);
}

/* End of $Workfile: timeout.c$ */
