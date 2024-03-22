/* Include ********************************************************************/
#include <stdio.h>

#include "board.h"
#include "clock_config.h"
#include "MIMXRT1064.h"
#include "fsl_debug_console.h"

#include "cfg.h"
#include "types32.h"
#include "mach/cansteer_v3/cansteer_v3.h"
#include "dbl.h"

/* Defines ********************************************************************/
/* Typedefs *******************************************************************/
/* Globals ********************************************************************/
/* Statics ********************************************************************/
/* Prototypes *****************************************************************/

/* Functions ******************************************************************/
int main(void) {

    /* Init board hardware. */
    BOARD_ConfigMPU();
    BOARD_InitBootClocks();
#ifndef BOARD_INIT_DEBUG_CONSOLE_PERIPHERAL
    /* Init FSL debug console. */
    BOARD_InitDebugConsole();
#endif
    PRINTF("Bootloader Init\r\n");

    Open_CANSTEER_V3();

    while(1) {
    	DeviceCAN_BL();
    	Run_BL();

        __asm volatile ("nop");
    }
    return 0 ;
}
/* End of $Workfile: main.c$ */
