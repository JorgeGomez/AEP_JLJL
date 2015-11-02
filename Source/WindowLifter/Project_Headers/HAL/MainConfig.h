/*
 * MainConfig.h
 *
 *  Created on: Oct 29, 2015
 *      Author: Jorge
 */

#ifndef MAINCONFIG_H_
#define MAINCONFIG_H_

#include "HAL\MPC5606B.h"
#include "HAL\stdtypedef.h"

typedef enum
{
   NO_OP,
   SHORT_PUSH,
   LONG_PUSH
}T_COMAND_WIN;

typedef enum
{
   PRESS = 0,
   NO_PRESS
}T_BUTTON;

typedef enum
{
	ALL_OFF,
	BLUE_ON_UP,
	GREEN_ON_DW
}T_DIRLED;

typedef enum
{
	NO_DIR,
	UP_DIR,
	DOWN_DIR
}T_DIRECTION;

typedef enum
{
	STATE_0_OPEN = 1,
	STATE_1,
	STATE_2,
	STATE_3,
	STATE_4,
	STATE_5,
	STATE_6,
	STATE_7,
	STATE_8,
	STATE_9,
	STATE_10_CLOSE
}T_STATE_WINDOW;

/****Macros and Variables****/
#define ON 		0
#define OFF 	1


/****LEDS Direction GPIO's****/
#define LED_GREEN 		15
#define LED_BLUE 		14

/****LEDS Bar GPIO's****/

#define LED_1 		0
#define LED_2 		1
#define LED_3 		2
#define LED_4 		3
#define LED_5 		4
#define LED_6 		5
#define LED_7 		6
#define LED_8 		7
#define LED_9 		8
#define LED_10 		9


#define PUSHB_UP 	64
#define PUSHB_DOWN 	65

#define PUSHB_ANTIPINCH 	66
 
void init_modes_and_clocks(void);
void disableWatchdog(void);
void initPeriClkGen(void);
void Config_IO(void);
void reset_ExtIntrpFlag(void);
T_BUTTON read_Pb_Dw(void);
T_BUTTON read_Pb_Up(void);
T_BUTTON read_Antipinch(void);
void led_on(T_UBYTE lub_Ch);
void led_off(T_UBYTE lub_Ch);


#endif /* MAINCONFIG_H_ */
