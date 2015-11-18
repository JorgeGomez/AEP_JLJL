/*============================================================================*/
/*                               AEP                                          */
/*============================================================================*/
/*                        OBJECT SPECIFICATION                                */
/*============================================================================*/
/*!
 * $Source: BlinkingLedsApp.h
 * $Revision: version 1.0
 * $Author: Jose Luis Martinez Vicuña
 * $Date: Nov/13/2015
 */
/*============================================================================*/
/* DESCRIPTION :                                                              */
/** \
 * This file provides the headers of the functions of application which send to
 * call MainConfig.c where the funtion is used led_toggle which it operates whit
 * a OR to change the status bit in off and on
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
/*                     |          Scheduler          |           1.0          */
/* 					   |							 |Project_Headers/Aplication*/
/*============================================================================*/
/*                               OBJECT HISTORY 							  */
/* version 1.0			|        11/13/2015		|  Jose Luis Martinez Vicuña  */
/*============================================================================*/
/*
 * $Log: BlinkingLedsApp.h  $
  ============================================================================*/
#ifndef BLINKINGLEDSAPP_H_
#define BLINKINGLEDSAPP_H_

/* Includes */
/*============================================================================*/
#include "HAL/stdtypedef.h"
#include "HAL/MainConfig.h"

/* Constants and types */
/*============================================================================*/


/* Exported Variables */
/*============================================================================*/


/* Exported functions prototypes */
/*============================================================================*/
PUBLIC_FCT void led_toggle(T_UBYTE lub_Ch);

/* Functions prototypes */
/*============================================================================*/
void toggle_led1(void);
void toggle_led2(void);
void toggle_led3(void);
void toggle_led4(void);

#endif /* BLINKINGLEDSAPP_H_ */  /* Notice: the file ends with a blank new line to avoid compiler warnings */
