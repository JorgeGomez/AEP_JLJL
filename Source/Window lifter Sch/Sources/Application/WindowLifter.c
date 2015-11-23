/*============================================================================*/
/*                       		     AEP	                                  */
/*============================================================================*/
/*                        OBJECT SPECIFICATION                                */
/*============================================================================*/
/*!
 * $Source: WindowLifter.c $
 * $Revision: 2.0 $
 * $Author: Jose Luis Matrinez $
 * $Date: Nov/20/2015 $
 */
/*============================================================================*/
/* DESCRIPTION :                                                              */
/** \WindowLifter
    It contains the state machine of the windowlifter and Antipinch. 
    Software Design doc: 5.3, 5.6
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
 * $Log: WindowLifter.c  $
  ============================================================================*/

/* Includes */
/*============================================================================*/
#include "Application/WindowLifter.h"


/* Constants and types  */
/*============================================================================*/



/* Variables */
/*============================================================================*/

PUBLIC_DATA E_STATES_ANTIPINCH rub_AntiPinchState;
PUBLIC_DATA E_STATE_WINDOW rub_StateWin;
PUBLIC_DATA E_STATES_WINDOWS_LIFTER rub_WindowLifterState;

/* Private functions prototypes */
/*============================================================================*/

/**************************************************************
 *  Name                 :  WindowLifter_StateMachine
 *  Description          :  State machine of the window lifter behaviour. it must be executed every 50 ms
 *  Parameters           :  void
 *  Return               :  void
 *  Precondition         :  The correct initialization of the startup code.
 *  Postcondition        :  The application start to run.
 *  Software Design doc	 :	5.3
 **************************************************************/
void WindowLifter_StateMachine(void)
{
	switch(rub_WindowLifterState)
	{
		case VALIDATION:
				ValidPress();				/*Validates if the buttons have a valid press or not */
			break;
			
		case SHORT_PUSH:
				SelectionPush();			/*Selects the type of push that it was given*/
			break;
			
		case LONG_PUSH:
				SelectorDirection();		/*Selects the direction that it was given*/
			break;
			
		case UP_DIR:
				
				Up_Mov_Window();			/*Selects the behaviour of the window depending of the type of push 
				 	 	 	 	 	 	 	 *and evaluate the antipinch inside of the function*/
			break;	
				
		case DOWN_DIR:
				Down_Mov_Window();			/*Selects the behaviour of the window depending of the type of push*/
			break;
			
		case ANTIPINCH:
				AntiPinch_StateMachine();	/*If an antipinch it was given correctly, It calls the state machine of antipinch*/
			break;
			
		default:
			rub_WindowLifterState = VALIDATION;	/*Default state*/
		break;
	}
}

/**************************************************************
 *  Name                 :  AntiPinch_StateMachine
 *  Description          :  State machine of antipinch gives to the system the down movement and the time out
 *  Parameters           :  void
 *  Return               :  void
 *  Precondition         :  An antipinch occurs and it must be valid.
 *  Postcondition        :  The system is going to go down and wait 5 seconds and 
 *  						before that the system can read new commands.
 *  Software Design doc	 :	5.6
 **************************************************************/

void AntiPinch_StateMachine(void)
{
	switch(rub_AntiPinchState)
	{
		case DOWN_ANTIPINCH:
				DownForAntipinch();	/*Gives the order to the system of get down the window*/
			break;
			
		case TIME_OUT:
				Wait_5s();			/*Gives the order to the system of wait 5 seconds before an antipinch*/
			break;
			
		default:
			rub_AntiPinchState = DOWN_ANTIPINCH;
			break;
	}
}



/* Inline functions */
/*============================================================================*/




/* Private functions */
/*============================================================================*/




/* Exported functions */
/*============================================================================*/



 /* Notice: the file ends with a blank new line to avoid compiler warnings */
