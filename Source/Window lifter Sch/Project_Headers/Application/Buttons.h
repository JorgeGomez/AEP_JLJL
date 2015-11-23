/*============================================================================*/
/*                       		     AEP	                                  */
/*============================================================================*/
/*                        OBJECT SPECIFICATION                                */
/*============================================================================*/
/*!
 * $Source: Buttons.h $
 * $Revision: version $
 * $Author: author $
 * $Date: date $
 */
/*============================================================================*/
/* DESCRIPTION :                                                              */
/** \file
    short description in one sentence end with dot.
    detailed
    multiline
    description of the file
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
/*                     |    			  	|            	                  */
/*============================================================================*/
/*                    			OBJECT HISTORY                          	  */
/*============================================================================*/
/*  REVISION 	|  		DATE  	|     COMMENT	     	 	   |AUTHOR 	  	  */
/*----------------------------------------------------------------------------*/
/* version 1.0  | 11/13/2015    |  creation of the file        |Jorge Gomez	  */
/*----------------------------------------------------------------------------*/
/* version 1.1  | 11/13/2015    |  	added new functionalities  |Jorge Gomez	  */
/*----------------------------------------------------------------------------*/
/*
 * $Log: filename.h  $
  ============================================================================*/
#ifndef BUTTONS_H_
#define BUTTONS_H_


/* Includes */
/*============================================================================*/
#include "HAL/MainConfig.h"
#include "HAL/stdtypedef.h"
#include "Application/WindowLifter.h"

/* Constants and types */
/*============================================================================*/
#define T_10_MS 	10		/* Count for 10 ms*/
#define T_500_MS 	500		/* Count for 500 ms*/
#define T_5_SECONDS 100		/* Count for 5 seconds*/

typedef enum
{
	NO_DIR,
	UP,
	DOWN
}E_DIRECTION;

typedef enum
{
	ALL_OFF,
	BLUE_ON_UP,
	GREEN_ON_DW
}E_DIRLED;

typedef enum
{
   UP_WIN = 0,
   DOWN_WIN
}E_MOV_WIN;

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
}E_STATE_WINDOW;

typedef enum
{
   NO_PUSH,
   S_PUSH,
   L_PUSH
}E_TYPE_OF_PUSH;


/* Exported Variables */
/*============================================================================*/


/* Exported functions prototypes */
/*============================================================================*/

/*For WindowLifter*/
void ValidPress(void);
void SelectionPush(void);
void SelectorDirection(void);
void Down_Mov_Window(void);
void Up_Mov_Window(void);
void Antipinch_Validation(void);
void DownForAntipinch(void);
void Wait_5s(void);

/*For Tasks*/
void ButtonsValidation(void);
void ReadAntipinch(void);
void LED_Motion_StateMachine(void);
void WindowLedCommander(void);

#endif /* BUTTONS_H_ */  /* Notice: the file ends with a blank new line to avoid compiler warnings */




