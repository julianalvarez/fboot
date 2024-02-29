
#include <stdio.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MIMXRT1064.h"
#include "fsl_debug_console.h"
/* TODO: insert other include files here. */
#include <cfg.h>
#include <types32.h>
#include <mach/cansteer_v3/cansteer_v3.h>
#include <dbl.h>

/* TODO: insert other definitions and declarations here. */

/*
 * @brief   Application entry point.
 */

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
