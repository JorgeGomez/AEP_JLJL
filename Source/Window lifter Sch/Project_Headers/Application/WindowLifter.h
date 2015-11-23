/*============================================================================*/
/*                       		     AEP	                                  */
/*============================================================================*/
/*                        OBJECT SPECIFICATION                                */
/*============================================================================*/
/*!
 * $Source: WindowLifter.h $
 * $Revision: 2.0 $
 * $Author: Jose Luis Matrinez $
 * $Date: Nov/20/2015 $
 */
/*============================================================================*/
/* DESCRIPTION :                                                              */
/** \WindowLifter
    It contains the headers of the state machine of the windowlifter and Antipinch 
    SoftwareDesign doc: 5.x
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
/*                     |    WindowLifter  	|            1.20                 */
/*============================================================================*/
/*                    			OBJECT HISTORY                          	  */
/*============================================================================*/
/*  REVISION 	|  		DATE  	|     COMMENT	     	 	   |AUTHOR 	  	  */
/*----------------------------------------------------------------------------*/
/* version 1.10 | 11/13/2015    |  added new functionalities   |Jorge Gomez	  */
/*----------------------------------------------------------------------------*/
/* version 1.15 | 11/13/2015    |  		added corrections	   |Jose Martinez */
/*----------------------------------------------------------------------------*/
/* version 1.20 | 11/13/2015    |  		first release		   |Jorge Gomez	  */
/*----------------------------------------------------------------------------*/
/* version 2.0	| 11/13/2015    | new version with scheduler   |Jose Martinez */
/*============================================================================*/
/*
 * $Log: WindowLifter.h  $
  ============================================================================*/
#ifndef WINDOWLIFTER_H_
#define WINDOWLIFTER_H_


/* Includes */
/*============================================================================*/
#include "HAL/stdtypedef.h"
#include "HAL/MainConfig.h"
#include "Application/Buttons.h"

/* Constants and types */
/*============================================================================*/
typedef enum
{
	VALIDATION,
	SHORT_PUSH,
	LONG_PUSH,
	UP_DIR,
	DOWN_DIR,
	ANTIPINCH
	
}E_STATES_WINDOWS_LIFTER; 	/*states for window lifter state machine*/

typedef enum
{
	DOWN_ANTIPINCH,
	TIME_OUT
}E_STATES_ANTIPINCH;		/*states for antipinch state machine*/


/* Exported Variables */
/*============================================================================*/



/* Exported functions prototypes */
/*============================================================================*/

PUBLIC_FCT void ValidPress(void);
PUBLIC_FCT void SelectionPush(void);
PUBLIC_FCT void SelectorDirection(void);
PUBLIC_FCT void Down_Mov_Window(void);
PUBLIC_FCT void Up_Mov_Window(void);
PUBLIC_FCT void DownForAntipinch(void);
PUBLIC_FCT void Wait_5s(void);

void WindowLifter_StateMachine(void);
void AntiPinch_StateMachine(void);


#endif /* WINDOWLIFTER_H_ */ /* Notice: the file ends with a blank new line to avoid compiler warnings */




