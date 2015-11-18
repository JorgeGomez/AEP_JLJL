/*
 * stdtypedef.h
 *
 *  Created on: Oct 9, 2015
 *      Author: Jorge
 */

#ifndef STDTYPEDEF_H_
#define STDTYPEDEF_H_


typedef unsigned char     T_UBYTE;				/*1 Byte 	0..255 					*/
typedef unsigned short    T_UWORD;				/*2 Byte 	0..65535				*/
typedef unsigned int      T_ULONG;				/*4 Byte 	0..FFFFFFFFh 			*/
typedef signed char       T_SBYTE;				/*1 Byte 	-128..127				*/
typedef signed short      T_SWORD;				/*2 Byte 	-32768..32767			*/
typedef signed int        T_SLONG;				/*4 Byte 	-80000000h...7FFFFFFFh	*/
typedef unsigned int      T_FLAG_ARRAY;
typedef unsigned int      T_BIT_STRUCT;

/* table of entry pochars */
typedef void(*T_PPROC)(void);

/* basic type pointers */
typedef T_UBYTE * PTR_UBYTE;
typedef T_UWORD * PTR_UWORD;
typedef T_ULONG * PTR_ULONG;
typedef T_SBYTE * PTR_SBYTE;
typedef T_SWORD * PTR_SWORD;
typedef T_SLONG * PTR_SLONG;

typedef T_UBYTE T_BOOLEAN;

/* Carrier of 8 bits */
typedef struct {
	unsigned int	bit0:1;
	unsigned int	bit1:1;
	unsigned int	bit2:1;
	unsigned int	bit3:1;
	unsigned int	bit4:1;
	unsigned int	bit5:1;
	unsigned int	bit6:1;
	unsigned int	bit7:1;
}T_BITFLD8;

/* Carrier of 16 bits */
typedef struct {
    unsigned int	bit0:1;
	unsigned int	bit1:1;
	unsigned int	bit2:1;
	unsigned int	bit3:1;
	unsigned int	bit4:1;
	unsigned int	bit5:1;
	unsigned int	bit6:1;
	unsigned int	bit7:1;    
	unsigned int	bit8:1;
	unsigned int	bit9:1;
	unsigned int	bit10:1;
	unsigned int	bit11:1;
	unsigned int	bit12:1;
	unsigned int	bit13:1;
	unsigned int	bit14:1;
	unsigned int	bit15:1;

}T_BITFLD16;

/* Carrier of 32 bits */
typedef struct {
    unsigned int	bit0:1;
	unsigned int	bit1:1;
	unsigned int	bit2:1;
	unsigned int	bit3:1;
	unsigned int	bit4:1;
	unsigned int	bit5:1;
	unsigned int	bit6:1;
	unsigned int	bit7:1;    
	unsigned int	bit8:1;
	unsigned int	bit9:1;
	unsigned int	bit10:1;
	unsigned int	bit11:1;
	unsigned int	bit12:1;
	unsigned int	bit13:1;
	unsigned int	bit14:1;
	unsigned int	bit15:1;
    unsigned int	bit16:1;
	unsigned int	bit17:1;
	unsigned int	bit18:1;
	unsigned int	bit19:1;
	unsigned int	bit20:1;
	unsigned int	bit21:1;
	unsigned int	bit22:1;
	unsigned int	bit23:1;    
	unsigned int	bit24:1;
	unsigned int	bit25:1;
	unsigned int	bit26:1;
	unsigned int	bit27:1;
	unsigned int	bit28:1;
	unsigned int	bit29:1;
	unsigned int	bit30:1;
	unsigned int	bit31:1;
}T_BITFLD32;

/* Word with msb and lsb handling */
typedef union{
	T_UWORD	wo;
	struct{
        T_UBYTE	lsb;   
		T_UBYTE	msb;
		}by;
}T_BYTEFLD;

/* Long with word and byte handling */
typedef union{
	T_ULONG lo;
    struct {
             T_UBYTE highword_lsb;
             T_UBYTE highword_msb;
             T_UBYTE lowword_lsb;
             T_UBYTE lowword_msb;
            } by;
        
    struct {
             T_UWORD lowword;
             T_UWORD highword;
           } wo;
               
}T_BYTEFLD32;

/* Carrier of 8 bits with byte handling */
typedef union {
	T_UBYTE by;
	T_BITFLD8 bi;
}T_FLAG8;

/* Carrier of 16 bits with word or byte (msb & lsb) carrier handling */
typedef union {
	T_BYTEFLD cr;
	T_BITFLD16 bi;
}T_FLAG16;

/* Carrier of 32 bits with word or byte (msb & lsb) carrier handling */
typedef union {
	T_BYTEFLD32 cr;
	T_BITFLD32 bi;
}T_FLAG32;

/* Boolean enum, recomended to use instead of TRUE/FALSE macro */
typedef enum
{
	BFALSE = 0u,
	BTRUE	
}E_BOOLEAN;

/* Error code type definition */
typedef enum
{
  E_SWP_OK,
  E_ADC_BUSY,
  E_INVALID_TIMER,
  E_TIMER_ALREADY_RUNNING,
  E_TIMER_ALREADY_STOPPED,
  E_EEP_BUSY,
  E_EEP_INIT_FAIL,
  E_EEP_COMP,
  E_EEP_ERROR,
  E_SPI_BUSY,
  E_SPI_NOK,
  E_FORCE_MINDELAY,
  E_FORCE_MAXDELAY,
  E_INVALID_PARAMETER,
  E_CTLRAM_OK,
  E_CTLRAM_NOK
}T_ERROR_CODE;
typedef enum
{
  E_IS_UNDER = 0U,
  E_IS_OVER = 1U
} T_BAT_THRD;

/* register monitoring variables */
/* TAG : SWR_C_CORE_09_005 Covers_SWR_D_CORE_09_005
*/

/* Timer type definitions */

typedef T_UWORD T_FAST_TIMER_DELAY;
typedef T_UBYTE TimerType;
typedef T_UBYTE T_SLOW_TIMER_DELAY;
/***** Macros definition *****/
#ifndef FALSE
#define FALSE ((T_BOOLEAN)0u)
#endif

#ifndef TRUE
#define TRUE ((T_BOOLEAN)1u)
#endif

#ifndef NULL
#define NULL 0U
#endif

/***** Compiler customization *****/
/** Memory macros definition **/
#define IRAM                            /* RAM declaration into internal RAM */
#define NEAR __near                     /* RAM declaration into near RAM */
#define FAR  __far                      /* RAM declaration into near RAM */
#define PRIVATE_DATA static             /* static data definition */
#define PRIVATE_FCT static              /* private function definition */
#define PUBLIC_DATA extern              /* Public (extern) data definition */
#define PUBLIC_FCT extern               /* Public (extern) function definition */
#define NEAR_FCT   __near_func          /* near function definition */
#define FAR_FCT                         /* far function definition */
#define INLINE_FCT inline               /* inline function definition */ 

/* table of entry pochars */
//typedef void (NEAR_FCT *T_PPROC_NEAR)(void);
//typedef void(FAR_FCT *T_PPROC_FAR)(void);

#endif /* STDTYPEDEF_H_ */
