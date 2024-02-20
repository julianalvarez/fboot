

/* Include ********************************************************************/
#include <typedef.h>
#include <timeout.h>
//#include <chip.h>

/* Defines ********************************************************************/
#define PERIOD_TIMER                        1U

/* Globals ********************************************************************/
volatile bool	        HasTimeout;

/* Statics ********************************************************************/
/*static bool             _init = false;
static uint16_t         TimeOut;
static uint16_t	        CounterTimeOut;
static void 		    (*FunctionTM) (void);*/
#if 0
/* Prototypes *****************************************************************/
/* Functions ******************************************************************/

/*******************************************************************************
 *    Function Name:  
 *    Parameters:     
 *    Return Value:   
 *
 *    Description:    
 *                     
 *    Notes:          Timer: 1000 Hz (1000 us period)       
 *
 ******************************************************************************/
void Open_TIMEOUT (void)
{
    Chip_RIT_Init(LPC_RITIMER);
    
    Chip_RIT_SetTimerInterval(LPC_RITIMER,1);
    
	/* Clear interrupt */
	Chip_RIT_ClearInt(LPC_RITIMER);
    
    NVIC_EnableIRQ(RITIMER_IRQn);
    
    __enable_irq(); // Ensure this is set for timing to work
}

/*******************************************************************************
 *    Function Name:  .
 *    Parameters:     .
 *    Return Value:   .
 *
 *    Description:    .
 *
 *    Notes:          .
 ******************************************************************************/
void Close_TIMEOUT (void)
{
    NVIC_DisableIRQ(RITIMER_IRQn);
    
    Chip_RIT_DeInit(LPC_RITIMER);
    
	/* Clear interrupt */
	Chip_RIT_ClearInt(LPC_RITIMER);
}

/*******************************************************************************
*    Function Name:  Isr_TIMER2
*    Parameters:     None.
*    Return Value:   None.
*
*    Description:    Service the SW timers.
*
*    Notes:          .
******************************************************************************/
void RIT_IRQHandler (void)
{  
	/* Clearn interrupt */
	Chip_RIT_ClearInt(LPC_RITIMER);

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

/***************************************************************************//*!
[General description here]

\param Param1         [Param1 description here]
\param Param2         [Param2 description here]
\return               [Return description here]
\note                 
*******************************************************************************/
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

/***************************************************************************//*!
[General description here]

\param Param1         [Param1 description here]
\param Param2         [Param2 description here]
\return               [Return description here]
\note                 
*******************************************************************************/
void reset_timeout (void)
{
    __disable_irq();
    _init          = false;
    TimeOut        = 0U;
    CounterTimeOut = 0U;
    FunctionTM     = 0U;
    __enable_irq();
}

/***************************************************************************//*!
[General description here]

\param Param1         [Param1 description here]
\param Param2         [Param2 description here]
\return               [Return description here]
\note                 
*******************************************************************************/
bool if_has_timeout (void)
{
    bool                result;

    result = HasTimeout;

    HasTimeout = false;

    return (result);
}
#endif
/* End of $Workfile: timeout.c$ */
