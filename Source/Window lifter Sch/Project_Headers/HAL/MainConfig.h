/*============================================================================*/
/*                                 AEP                                        */
/*============================================================================*/
/*                        OBJECT SPECIFICATION 
 * This file provides the headers of the functions of file MainConfig.c       */
/*============================================================================*/
/*!
 * $Source: MainConfig.h
 * $Revision: version 1.0
 * $Author: Jose Luis Martinez Vicuña
 * $Date: Nov/13/2015
 */
/*============================================================================*/
/* DESCRIPTION :                                                              */
/** \
 * This file provides the headers of the functions of general configuration as
 * system configuration with init_system, Pad Data In to pins with  read_button
 * and power on, power off and toggle to pins, also it contains definitions of 
 * the pins where some pins are mapped general purpose
*/
/*============================================================================*/
/* COPYRIGHT (C) CONTINENTAL AUTOMOTIVE 2014                                  */
/* AUTOMOTIVE GROUP, Interior Division, Body and Security                     */
/* ALL RIGHTS RESERVED                                                        */
/*                                                                            */
/* The reproduction, transmission, or use of this document or its content is  */
/* not permitted without express written authority. Offenders will be liable  */
/* for damages.                                                               */
/* All rights, including rights created by patent grant or registration of a  */
/* utility model or design, are reserved.                                     */
/*                                                                            */
/*============================================================================*/
/*============================================================================*/
/*                    REUSE HISTORY - taken over from                         */
/*============================================================================*/
/*  DATABASE           |        PROJECT     | FILE VERSION (AND INSTANCE)     */
/*----------------------------------------------------------------------------*/
/*                     |       Scheduler    |              1.0                */
/*					   |					|      Project_Headers/HAL        */
/*============================================================================*/
/*                               OBJECT HISTORY 							  */
/* version 1.0		   |     11/13/2015     |  Jose Luis Martinez Vicuña      */
/*============================================================================*/
/*
 * $Log: MainConfig.h  $
  ============================================================================*/
#ifndef MAINCONFIG_H_
#define MAINCONFIG_H_

/* Includes */
/*============================================================================*/
#include "HAL\MPC5606B.h"
#include "HAL\stdtypedef.h"


/* Constants and types */
/*============================================================================*/
typedef enum
{
   PRESS = 0,
   NO_PRESS
}E_BUTTON;

/****Macros****/
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

/* Exported Variables */
/*============================================================================*/
 

/* Exported functions prototypes */
/*============================================================================*/

/* Functions prototypes */
/*============================================================================*/
void init_system(void);
E_BUTTON read_button(T_UBYTE lub_Ch);
void led_on(T_UBYTE lub_Ch);
void led_off(T_UBYTE lub_Ch);
void led_toggle(T_UBYTE lub_Ch);

#endif /* MAINCONFIG_H_ */ /* Notice: the file ends with a blank new line to avoid compiler warnings */
