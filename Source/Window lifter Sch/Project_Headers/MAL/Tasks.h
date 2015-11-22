/*============================================================================*/
/*                                  AEP                                       */
/*============================================================================*/
/*                        OBJECT SPECIFICATION                                */
/*      This file provides the headers of the functions of Tasks.c            */
/*============================================================================*/
/*!
 * $Source: Tasks.h $
 * $Revision: version 1.0 $
 * $Author: Jose Luis Martinez Vicuña $
 * $Date: Nov/13/2015 $
 */
/*============================================================================*/
/* DESCRIPTION :                                                              */
/** \file
 * This file provides the headers of the functions of the Tasks which are defined
 * in Tasks.c, also is the structure S__TASK which receives the function, period
 * and an offset and the number of tasks to be executed.
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
/*                     |      Scheduler     |            1.0                  */
/*					   |					|      Project_Headers/MAL  	  */
/*============================================================================*/
/*                               OBJECT HISTORY                               */
/* version 1.0		   |     11/13/2015     |  Jose Luis Martinez Vicuña      */
/*============================================================================*/
/*
 * $Log: Tasks.h  $
  ============================================================================*/
#ifndef TASKS_H_
#define TASKS_H_

/* Includes */
/*============================================================================*/
#include "HAL/stdtypedef.h"

/* Constants and types */
/*============================================================================*/
typedef void(*T_PFUNC)(void);

typedef struct{
	T_PFUNC PtrFunc;
	T_ULONG Period;
	T_UBYTE Offset;
}S_TASK;

typedef enum {
	TASK1,
	TASK2,
	TASK3,
	/*number of task*/
	NUMBER_OF_TASKS
}E_NUMTASK;

/* Exported Variables */
/*============================================================================*/



/* Exported functions prototypes */
/*============================================================================*/
PUBLIC_FCT void ButtonsValidation(void);
PUBLIC_FCT void WindowLifter_StateMachine(void);
PUBLIC_FCT void LED_Motion_StateMachine(void);
PUBLIC_FCT void ReadAntipinch(void);
PUBLIC_FCT void WindowLedCommander(void);

/* Functions prototypes */
/*============================================================================*/
void Task1_1ticks(void);
void Task2_50ticks(void);
void Task3_400ticks(void);

#endif /* TASKS_H_ */  /* Notice: the file ends with a blank new line to avoid compiler warnings */
