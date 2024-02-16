/*******************************************************************************
** $Revision: 1$
** $Date: 31/01/2011 04:04:57 p.m.$
** $Author: Admin Leandro Gentili$
**                                 COPYRIGHT (C) FORKWORKS. All rights reserved.
*******************************************************************************/
#ifndef _TYPEDEF_H
#define _TYPEDEF_H

/* Include ********************************************************************/
#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

/* Enums **********************************************************************/
/* Defines ********************************************************************/
/* Move this to a Compiler Adaptation */
#ifdef __arm__
#define PACKED                              __packed
#define inline								__inline
#endif

/* Typedefs *******************************************************************/
typedef union   {
    uint8_t  b[2];
    uint16_t w;
} tBw;

typedef union   {
    uint8_t  b[4];
    uint16_t w[2];
    uint32_t dw;
} tDw;

typedef struct {
    int32_t  l1ms;
    uint16_t w1us;
} tTime;

/* Externs ********************************************************************/
/* Prototypes *****************************************************************/

#endif

/* End of $Workfile: typedef.h$ */

