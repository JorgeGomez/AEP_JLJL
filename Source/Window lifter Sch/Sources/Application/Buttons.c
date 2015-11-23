/*============================================================================*/
/*                       		     AEP	                                  */
/*============================================================================*/
/*                        OBJECT SPECIFICATION                                */
/*============================================================================*/
/*!
 * $Source: Buttons.c $
 * $Revision: 1.0 $
 * $Author: Jorge Luis Gomez Gonzalez $
 * $Date: Nov/20/2015 $
 */
/*============================================================================*/
/* DESCRIPTION :                                                              */
/** \Buttons
    It contains the functions necessary to implement the window lifter project
     
    Software Design doc: 5.6 to 5.17
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
/*============================================================================*/
/*
 * $Log: Buttons.c  $
  ============================================================================*/


/* Includes */
/*============================================================================*/
#include "Application/Buttons.h"


/* Constants and types  */
/*============================================================================*/



/* Variables */
/*============================================================================*/
E_BUTTON rub_ButtonPressed = NO_PRESS, rub_AntipinchButton = NO_PRESS;
E_DIRECTION rub_DirectionMove = NO_DIR, rub_CommandWin = NO_DIR;
T_ULONG rul_TimePress = 0, rul_TimeTransition = 0, rul_Antipinch_Press = 0, rul_Timeout = 0;
E_STATE_WINDOW rub_StateWin = STATE_10_CLOSE;
E_TYPE_OF_PUSH rub_TypeOfPush = NO_PUSH;
E_STATES_ANTIPINCH rub_AntiPinchState = DOWN_ANTIPINCH;

E_STATES_WINDOWS_LIFTER rub_WindowLifterState = VALIDATION;
/* Private functions prototypes */
/*============================================================================*/



/* Inline functions */
/*============================================================================*/




/* Private functions */
/*============================================================================*/



/* Exported functions */
/*============================================================================*/

/**************************************************************
 *  Name                 :  ValidPress
 *  Description          :  It validates if the buttons have a valid press or not
 *  Parameters           :  void
 *  Return               :  void
 *  Precondition         :  The correct initialisation the system.
 *  Postcondition        :  Tells to the system if the press was given correctly, 
 *  						moves the state machine to Short_push.
 *  Software Design doc	 :	5.6
 *  Requirements		 :	2.2, 2.4
 **************************************************************/
 void ValidPress(void)
 {
	 if((rub_ButtonPressed == PRESS) && (rul_TimePress > T_10_MS))
	 {
		 rub_WindowLifterState = SHORT_PUSH;
	 }
	 else
	 {
		 /*Do nothing*/
	 }
	 led_off(LED_GREEN);
	 led_off(LED_BLUE);
 }
 
 /**************************************************************
  *  Name                 :  SelectionPush
  *  Description          :  Selects the type of push that it was given
  *  Parameters           :  void
  *  Return               :  void
  *  Precondition         :  A correct validation of a button.
  *  Postcondition        :  If the press is greater than 500ms moves the Window lifter state machine to Long_push.
  *  						 else selects the window movement, down or up in Short_push.
  *  Software Design doc  :	5.7
  *  Requirements		  :	2.5, 2.6, 2.7, 2.8
  **************************************************************/
 void SelectionPush(void)
 {
	 if((rub_ButtonPressed == PRESS) && (rul_TimePress >= T_500_MS))
	 {
		 rub_WindowLifterState = LONG_PUSH;
		 rub_TypeOfPush = L_PUSH;
	 }
	 else if(rub_ButtonPressed == NO_PRESS)
	 {
		 rub_WindowLifterState = SHORT_PUSH;
		 rub_TypeOfPush = S_PUSH;
		 SelectorDirection();
	 }
	 else
	 {
		 /*Do nothing*/
	 }
	 
	 if(rub_DirectionMove == UP)
	 {
		 rub_CommandWin = UP_DIR;
	 }
	 else if(rub_DirectionMove == DOWN)
	 {
		 rub_CommandWin = DOWN_DIR;
	 }
	 else
	 {
		 /*Do nothing*/
	 }
 }
 
 /**************************************************************
  *  Name                 :  SelectorDirection
  *  Description          :  Selects the direction that it was given
  *  Parameters           :  void
  *  Return               :  void
  *  Precondition         :  The correct transition to Long_push.
  *  Postcondition        :  The selection of the window movement for a Long push.
  *  Software Design doc  :	5.8
  *  Requirements		  :	1.7
  **************************************************************/
void SelectorDirection(void)
{
	if(rub_DirectionMove == UP)
	{
		rub_WindowLifterState = UP_DIR;
	}
	else if(rub_DirectionMove == DOWN)
	{
		rub_WindowLifterState = DOWN_DIR;
	}
	else
	{
		/*Do nothing*/
	}
}

/**************************************************************
 *  Name                 :  Up_Mov_Window
 *  Description          :  Selects the behaviour of the window depending of the type of push 
 *				 	 	    and evaluate the antipinch inside of the function.
 *  Parameters           :  void
 *  Return               :  void
 *  Precondition         :  A correct transition to the state Up_dir.
 *  Postcondition        :  The Command for the window is given.
 *  Software Design doc	 :	5.9
 *  Requirements		 :	1.7, 3.5
 **************************************************************/
void Up_Mov_Window(void)
{
	if(rub_TypeOfPush == L_PUSH)		/*Gives the command for an manual movement*/
	{
		if(rub_ButtonPressed == PRESS)
		{
			Antipinch_Validation();		/*If an antipinch occurs the next state of the window lifter state machine will be Antipinch*/
			rub_CommandWin = UP;
		}
		else
		{
			rub_WindowLifterState = VALIDATION;
			rub_CommandWin = NO_DIR;
		}
	}
	else if(rub_TypeOfPush == S_PUSH)	/*Gives the command for an automatic movement*/
	{
		if(rub_ButtonPressed == NO_PRESS)
		{
			Antipinch_Validation();		/*If an antipinch occurs the next state of the window lifter state machine will be Antipinch*/
			rub_CommandWin = UP;
		}
		else
		{
			rub_WindowLifterState = VALIDATION;
			rub_CommandWin = NO_DIR;
		}
	}
	else
	{
		/*Do nothing*/
	}
}

/**************************************************************
 *  Name                 :  Down_Mov_Window
 *  Description          :  Selects the behaviour of the window depending of the type of push.
 *  Parameters           :  void
 *  Return               :  void
 *  Precondition         :  A correct transition to the state Down_dir.
 *  Postcondition        :  The Command for the window is given.
 *  Software Design doc	 :	5.10
 *  Requirements		 :	1.7, 3.5
 **************************************************************/
void Down_Mov_Window(void)
{
	if(rub_TypeOfPush == L_PUSH)
	{
		if(rub_ButtonPressed == PRESS)
		{
				rub_CommandWin = DOWN;
		}
		else
		{
			rub_WindowLifterState = VALIDATION;
			rub_CommandWin = NO_DIR;
		}
	}
	else if(rub_TypeOfPush == S_PUSH)
	{
		if(rub_ButtonPressed == NO_PRESS)
		{
			rub_CommandWin = DOWN;
		}
		else
		{
			rub_WindowLifterState = VALIDATION;
			rub_CommandWin = NO_DIR;
		}
	}
	else
	{
		/*Do nothing*/
	}
}

/**************************************************************
 *  Name                 :  Antipinch_Validation
 *  Description          :  If an antipinch occurs the next state of the window lifter state machine will be Antipinch.
 *  Parameters           :  void
 *  Return               :  void
 *  Precondition         :  The movement of the window must be Up.
 *  Postcondition        :  The next state of the window lifter state machine will be Antipinch.
 *  Software Design doc	 :	5.11
 *  Requirements		 :	3.3
 **************************************************************/
void Antipinch_Validation(void)
{
	 if((rub_AntipinchButton == PRESS) && (rul_Antipinch_Press >= T_10_MS))
	 {
		 rub_WindowLifterState = ANTIPINCH;
		 rub_AntiPinchState = DOWN_ANTIPINCH;
		 rub_CommandWin = NO_DIR;
		 led_off(LED_BLUE);
	 }
	 else
	 {
		 /*Do nothing*/
	 }
}

/**************************************************************
 *  Name                 :  DownForAntipinch
 *  Description          :  Gives the order to the system of get down the window.
 *  Parameters           :  void
 *  Return               :  void
 *  Precondition         :  A valid press for an antipinch.
 *  Postcondition        :  The window must get down.
 *  Software Design doc	 :	5.12
 *  Requirements		 :	3.6
 **************************************************************/
void DownForAntipinch(void)
{
	rub_CommandWin = DOWN;
	if(rub_StateWin == STATE_0_OPEN)
	{
		rub_AntiPinchState = TIME_OUT;		/*If the window is completely open change the state of the Antipinch state machine to Time out */
	}
	else
	{
		/*Do nothing*/
	}
}

/**************************************************************
 *  Name                 :  Wait_5s
 *  Description          :  Gives the order to the system of wait 5 seconds before an antipinch
 *  Parameters           :  void
 *  Return               :  void
 *  Precondition         :  The window is completely open.
 *  Postcondition        :  Before 5 seconds the system can read new commands.
 *  Software Design doc	 :	5.13
 *  Requirements		 :	3.7
 **************************************************************/
void Wait_5s(void)
{
	rul_Timeout++;						/*Waits until the elapsed time is 5 seconds*/
	if(rul_Timeout >= T_5_SECONDS)
	{
		rub_WindowLifterState = VALIDATION;
		rub_AntiPinchState = DOWN_ANTIPINCH;	/*If the time is greater or equal to 5 seconds returns the control to the system*/
		rub_CommandWin = NO_DIR;
		rul_Timeout = 0;
	}
	else
	{
		rub_WindowLifterState = ANTIPINCH;
		rub_AntiPinchState = TIME_OUT;
	}
}

/**************************************************************
 *  Name                 :  ReadAntipinch
 *  Description          :  Read the value of the button antipinch. It must be executed every ms.
 *  Parameters           :  void
 *  Return               :  void
 *  Precondition         :  The correct initialisation of the system.
 *  Postcondition        :  A change on the global variable rub_AntipinchButton 
 *  						and increase the counter to validate the correct button press.
 *  Software Design doc	 :	5.14
 *  Requirements		 :	3.4
 **************************************************************/
void ReadAntipinch(void)
{
	E_BUTTON lub_AntiPinch = NO_PRESS;
	
	lub_AntiPinch = read_button(PUSHB_ANTIPINCH);	/*read button Antipinch and write in lub_Antipinch if the button has been pressed*/

	if(rub_StateWin != STATE_10_CLOSE)
	{
		if(lub_AntiPinch == PRESS)
		{
			rub_AntipinchButton = PRESS;
			rul_Antipinch_Press++;
		}
		else if(lub_AntiPinch == NO_PRESS)
		{
			rub_AntipinchButton = NO_PRESS;
			rul_Antipinch_Press = 0;
		}
		else
		{
			/*Do nothing*/
		}
	}
	else
	{
		/*Do nothing*/
	}
}

/**************************************************************
 *  Name                 :  ButtonsValidation
 *  Description          :  Read the value of the buttons, up and down. It must be executed every ms.
 *  Parameters           :  void
 *  Return               :  void
 *  Precondition         :  The correct initialisation of the system.
 *  Postcondition        :  A change on the global variable rub_ButtonPressed 
 *  						and increase the counter to validate the correct button press
 *  						and gives the command to select the direction.
 *  Software Design doc	 :	5.15
 *  Requirements		 :	2.1, 2.3
 **************************************************************/
void ButtonsValidation(void)
{
	E_BUTTON lub_Up = NO_PRESS;
	E_BUTTON lub_Dw = NO_PRESS;

		
	lub_Up = read_button(PUSHB_UP);					/*read button UP and write in  lub_Up if the button has been pressed*/
		
	lub_Dw= read_button(PUSHB_DOWN);				/*read button DOWN and write in  lub_Dw if the button has been pressed*/
	
	if(lub_Dw == lub_Up)							/*compare if the buttons have been pressed and if have the same value is considered as no valid*/
	{												/*acording to req.2.2 and 2.4*/
		rub_ButtonPressed = NO_PRESS;
		rul_TimePress = 0;
		if((lub_Dw == PRESS) && (lub_Up == PRESS) && (rub_WindowLifterState != ANTIPINCH))
		{
			rub_WindowLifterState = VALIDATION;
			rub_CommandWin = NO_DIR;
		}
		else
		{
			/*Do nothing*/
		}
		
	}
	
	else
	{
		if(lub_Dw == PRESS)							/*Acording with req. 1.7*/
		{

			rub_DirectionMove = DOWN;
			rub_ButtonPressed = PRESS;
			rul_TimePress++;
		}
		else if(lub_Up == PRESS)
		{
			rub_DirectionMove = UP;
			rub_ButtonPressed = PRESS;
			rul_TimePress++;
		}
		else
		{
			/*Do nothing*/
		}
	}
}

/**************************************************************
 *  Name                 :  LED_Motion_StateMachine
 *  Description          :  State machine of the LED Window.
 *  						It must be executed every 400 ms.
 *  Parameters           :  void
 *  Return               :  void
 *  Precondition         :  The correct initialisation of the system.
 *  Postcondition        :  Refreshes the State of the window.
 *  Software Design doc	 :	5.16
 *  Requirements		 :	1.4, 1.5, 1.6 
 **************************************************************/
void LED_Motion_StateMachine(void)
{	
	switch(rub_StateWin)
	{
		case STATE_0_OPEN:
			led_off_more(LED_1,LED_10);
			break;
	
		case STATE_1:
			led_on(LED_1);
			led_off_more(LED_2,LED_10);
			break;
	
		case STATE_2:
			led_on_more(LED_1,LED_2);
			led_off_more(LED_3,LED_10);
			break;
	
		case STATE_3:
			led_on_more(LED_1,LED_3);
			led_off_more(LED_4,LED_10);
			break;
	
		case STATE_4:
			led_on_more(LED_1,LED_4);
			led_off_more(LED_5,LED_10);
			break;
	
		case STATE_5:
			led_on_more(LED_1,LED_5);
			led_off_more(LED_6,LED_10);
			break;
	
		case STATE_6:
			led_on_more(LED_1,LED_6);
			led_off_more(LED_7,LED_10);
			break;
	
		case STATE_7:
			led_on_more(LED_1,LED_7);
			led_off_more(LED_8,LED_10);
			break;
	
		case STATE_8:
			led_on_more(LED_1,LED_8);
			led_off_more(LED_9,LED_10);
			break;
	
		case STATE_9:
			led_on_more(LED_1,LED_9);
			led_off(LED_10);
			break;
	
		case STATE_10_CLOSE:
			led_on_more(LED_1,LED_10);
			break;
			
		default:
			if(rub_StateWin < STATE_0_OPEN)
			{
				rub_StateWin = STATE_0_OPEN;
				rub_CommandWin = NO_DIR;
				led_off(LED_GREEN);
				if(rub_WindowLifterState != ANTIPINCH)
				{
					rub_WindowLifterState = VALIDATION;
				}
				else
				{
					/*Do nothing*/
				}
			}
			else if(rub_StateWin > STATE_10_CLOSE)
			{
				rub_StateWin = STATE_10_CLOSE;
				rub_CommandWin = NO_DIR;
				led_off(LED_BLUE);
				if(rub_WindowLifterState != ANTIPINCH)
				{
					rub_WindowLifterState = VALIDATION;
				}
				else
				{
					/*Do nothing*/
				}
			}
			else
			{
				/*Do nothing*/
			}
			break;
	}
}

/**************************************************************
 *  Name                 :  WindowLedCommander
 *  Description          :  Gives the different commands to the window.
 *  						It must be executed every 400 ms.
 *  Parameters           :  void
 *  Return               :  void
 *  Precondition         :  The correct initialisation of the system.
 *  Postcondition        :  Gives the State of the window.
 *  Software Design doc	 :	5.17
 *  Requirements		 :	1.7, 1.8
 **************************************************************/
void WindowLedCommander(void)
{
	if(rub_CommandWin == DOWN)
		{
			rub_StateWin--;
			led_on(LED_GREEN);		
			led_off(LED_BLUE);
		}
		else if(rub_CommandWin == UP)
		{
			rub_StateWin++;
			led_on(LED_BLUE);
			led_off(LED_GREEN);
		}
		else
		{
			/*Do nothing*/
		}
}

 /* Notice: the file ends with a blank new line to avoid compiler warnings */
