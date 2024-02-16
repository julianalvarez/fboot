

#ifndef TIMEOUT_H
#define TIMEOUT_H
#include "types32.h"
/* Include ********************************************************************/
/* Enums **********************************************************************/
/* Defines ********************************************************************/
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
