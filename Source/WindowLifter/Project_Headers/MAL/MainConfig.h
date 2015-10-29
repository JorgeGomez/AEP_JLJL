/*
 * MainConfig.h
 *
 *  Created on: Oct 29, 2015
 *      Author: Jorge
 */

#ifndef MAINCONFIG_H_
#define MAINCONFIG_H_

#include "MAL\MPC5606B.h"


/****Macros and Variables****/
#define FREC 	9000000
#define ON 		0
#define OFF 	1


/****LEDS Direction GPIO's****/
#define LED_GREEN 		112
#define LED_BLUE 		113

/****LEDS Bar GPIO's****/

#define LED_1 		48
#define LED_2 		49
#define LED_3 		50
#define LED_4 		51
#define LED_5 		52
#define LED_6 		53
#define LED_7 		54
#define LED_8 		55
#define LED_9 		56
#define LED_10 		57


#define PUSHB_UP 	64
#define PUSHB_DOWN 	65

#define PUSHB_ANTIPINCH 	67


void init_modes_and_clocks(void);
void disableWatchdog(void);
void initPeriClkGen(void);
void Config_IO(void);



#endif /* MAINCONFIG_H_ */
