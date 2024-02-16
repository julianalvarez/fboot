

#ifndef TYPES32_H
#define TYPES32_H

/* Include ********************************************************************/
#include <stdint.h>
#include <stdbool.h>

/* Enums **********************************************************************/
/* Defines ********************************************************************/

typedef enum {FALSE = 0, TRUE = !FALSE} Bool;

/*
 * Size Array calculation macro
 */
#define sizearray(a)  (sizeof(a) / sizeof((a)[0]))

/* _BIT(n) sets the bit at position "n"
 * _BIT(n) is intended to be used in "OR" and "AND" expressions:
 * e.g., "(_BIT(3) | _BIT(7))".
 */
#ifndef _BIT
/* Set bit macro */
#define _BIT(n)	(((U32)(1)) << (n))
#endif

/* _CLEARBIT(n) clear the bit at position "n" */
#ifndef _CLEARBIT
/* Clear bit macro */
#define _CLEARBIT(n)	(((U32)(0)) << (n))
#endif

/* _SBF(f,v) sets the bit field starting at position "f" to value "v".
 * _SBF(f,v) is intended to be used in "OR" and "AND" expressions:
 * e.g., "((_SBF(5,7) | _SBF(12,0xF)) & 0xFFFF)"
 */ 
#ifndef _SBF
/* Set bit field macro */
#define _SBF(f,v) (((U32)(v)) << (f))
#endif

/* _BITMASK constructs a symbol with 'field_width' least significant
 * bits set.
 * e.g., _BITMASK(5) constructs '0x1F', _BITMASK(16) == 0xFFFF
 * The symbol is intended to be used to limit the bit field width
 * thusly:
 * <a_register> = (any_expression) & _BITMASK(x), where 0 < x <= 32.
 * If "any_expression" results in a value that is larger than can be
 * contained in 'x' bits, the bits above 'x - 1' are masked off.  When
 * used with the _SBF example above, the example would be written:
 * a_reg = ((_SBF(5,7) | _SBF(12,0xF)) & _BITMASK(16))
 * This ensures that the value written to a_reg is no wider than 
 * 16 bits, and makes the code easier to read and understand.
 */ 
/*#undef _BITMASK*/
/* Bitmask creation macro */
#ifndef _BITMASK
#define _BITMASK(field_width) ( _BIT(field_width) - 1)
#endif

/* OK macro */
#define _OK                                 0
/* ERROR macro */
#define _ERROR                              -1
/* SUCCESS macro 
#define SUCCESS                             _OK */
/* NO_ERROR macro */
#define _NO_ERROR                           _OK

#if 0
#ifndef FALSE
/* FALSE macro */
#ifdef __cplusplus
  #define FALSE false
#else
  #define FALSE (0==1)
#endif
#endif

#ifndef TRUE
/* TRUE macro */
#ifdef ___cplusplus
  #define TRUE true
#endif
  #define TRUE (!(FALSE))
#endif
#endif

/* NULL pointer */
#ifndef NULL
#ifdef __cplusplus
  #define NULL 0
#else
  #define NULL ((void*)0)
#endif
#endif 

/* NULL number */
#ifndef ZERO
#define ZERO ((U32)0)
#endif
	
/* High Byte */
/*#undef _HIGH_BYTE*/
#define _HIGH_BYTE(x)                       ((x) >> 8)

/* Low Byte */
/*#undef _LOW_BYTE*/
#define _LOW_BYTE(x)                        ((x) & 0x00FFU)	

/* Number of elements in an array 
#define NELEMENTS(array)  (sizeof (array) / sizeof (array[0]))*/

/* General interfaces modes 
#define SET                                 (11111U)
#define GET                                 (22222U)
#define ON                                  1
#define OFF                                 0*/

/* Typedefs *******************************************************************/

/* FW type for void and void* */
typedef void VOID;
typedef void *LPVOID;

#ifndef _CHAR_TYPEDEF
#define _CHAR_TYPEDEF
/* FW type for character type */
typedef char CHAR;
#endif

/* FW type for 8 bit unsigned value */
#ifndef _U8_TYPEDEF
#define _U8_TYPEDEF
typedef unsigned char U8;
#endif
/* FW type for 8 bit signed value */
#ifndef _S8_TYPEDEF
#define _S8_TYPEDEF
typedef signed char S8;
#endif
/* FW type for 16 bit unsigned value */
#ifndef _U16_TYPEDEF
#define _U16_TYPEDEF
typedef	unsigned short U16;
#endif
/* FW type for 16 bit signed value */
#ifndef _S16_TYPEDEF
#define _S16_TYPEDEF
typedef	signed short S16;
#endif
/* FW type for 32 bit unsigned value */
#ifndef _U32_TYPEDEF
#define _U32_TYPEDEF
typedef	unsigned int U32;
#endif
/* FW type for 32 bit signed value */
#ifndef _S32_TYPEDEF
#define _S32_TYPEDEF
typedef	signed int S32;
#endif
/* FW type for 64 bit unsigned value */
#ifndef _U64_TYPEDEF
#define _U64_TYPEDEF
typedef unsigned long long U64;
#endif
/* FW type for 64 bit signed value */
#ifndef _S64_TYPEDEF
#define _S64_TYPEDEF
typedef long long S64;
#endif
/* 64 bits float */
#ifndef _F64_TYPEDEF
#define _F64_TYPEDEF
typedef double F64;
#endif
/* 32 bit boolean type */
#ifndef _BOOL32_TYPEDEF
#define _BOOL32_TYPEDEF
typedef U32 BOOL32;
#endif
/* 16 bit boolean type */
#ifndef _BOOL16_TYPEDEF
#define _BOOL16_TYPEDEF
typedef U16 BOOL16;
#endif
/* 8 bit boolean type */
#ifndef _BOOL8_TYPEDEF
#define _BOOL8_TYPEDEF
typedef U8 BOOL8;
#endif
/* 32 bit float type */
#ifndef _F32_TYPEDEF
#define _F32_TYPEDEF
typedef float F32;
#endif

/* size type */
#ifdef __arm
typedef U32 size_t;
#endif
#ifdef __cplusplus
  /* Pointer to Function returning Void (any number of parameters) */
  typedef void (*PFV)(...);

  /* Pointer to Function returning U32 (any number of parameters) */
  typedef U32 (*PFU)(...);

  /* Pointer to Function returning S32 (any number of parameters) */
  typedef S32 (*PFS)(...);

  /* bool type */
  typedef bool BOOL;
#else
  /* Pointer to Function returning Void (any number of parameters) */
  typedef void (*PFV)();

  /* Pointer to Function returning U32 (any number of parameters) */
  typedef U32 (*PFU)();

  /* Pointer to Function returning S32 (any number of parameters) */
  typedef S32 (*PFS)();

typedef unsigned int BOOL;
#endif

typedef union tagWordDAT 
{ 
  U16 Word;
  struct tagBYTE
  {
    U8 Low;
    U8 High;
  } Byte;        
} WORD_DATA_U; 

typedef union tagDWordDAT 
{ 
  U32 DWord;
  struct tagWord
  {
    U16 Low;
    U16 High;
  } Word;        
} DWORD_DATA_U;

typedef union tagQWordDAT
{
  U64 QWord;
  struct tagDWord
  {
    U32 Low;
    U32 High;
  } DWord;
} QWORD_DATA_U;

#endif /* TYPES32_H */ 
