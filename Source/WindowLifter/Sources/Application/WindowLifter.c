/*
 * WindowLifter.c
 *
 *  Created on: Oct 29, 2015
 *      Author: Jorge
 */

#include "Application\WindowLifter.h"
#include "HAL\stdtypedef.h"
#include "HAL\Mainconfig.h"
#include "MAL\Init_Interrupts.h"
#include "HAL\stmDvr.h"

T_ULONG rul_TimeMsCnt = 0, rul_TimeWait = 0, rub_ValidAntipinchCnt = 0, rul_TimeTransition = 0;
T_BOOLEAN rub_ValidPress = FALSE;
T_COMAND_WIN rub_CmdWindow = NO_OP;
T_BUTTON rub_ButtonPressed = NO_PRESS, rub_AntipinchButton = NO_PRESS;
T_DIRECTION rub_DirectionMove = NO_DIR;
T_STATE_WINDOW rub_StateWin = STATE_10_CLOSE;
T_DIRLED rub_DirectionIndicador ;


void WinLifterApp(void)
{
	ReadButtons();
	LED_Motion_StateMachine();
}




void Init_System(void)
{
	init_modes_and_clocks();
	initPeriClkGen();
	Config_IO();
	stm_init_fnc();
	init_stm_interruptCH0();
	init_ExtInterruptPE2();	
}


void Inputs_validation(void)
{
	if(rub_ButtonPressed == PRESS)
	{
		rul_TimeMsCnt++; 
		
		if(rul_TimeMsCnt >= 10)											/*Acording with req. 2.3 and 2.1*/
		{
			rub_ValidPress = TRUE;
		}
		
		if(rul_TimeMsCnt > 500)											/*Acording with req. 2.5 and 2.7*/
		{
			rub_CmdWindow = LONG_PUSH;		
			Motion_WinLed();
			if((rub_StateWin <= STATE_0_OPEN) || (rub_StateWin >= STATE_10_CLOSE))
			{
				StatusDir_LED(ALL_OFF);
			}
			else
			{
				StatusDir_LED(rub_DirectionMove);
			}
			rub_DirectionMove = NO_DIR;
		}
		
	}
	else
	{
		if((rul_TimeMsCnt <= 500) && (rul_TimeMsCnt > 10))				/*Asummtion acording with req. 2.6 and 2.8*/
		{
			rub_CmdWindow = SHORT_PUSH;
		}
		
		else if(rul_TimeMsCnt < 10)											/*Acording with req. 2.2 and 2.4*/
		{
			rub_ValidPress = FALSE;
		}
		rul_TimeMsCnt = 0;
		StatusDir_LED(ALL_OFF);
		if(rub_CmdWindow != SHORT_PUSH)
		{
			rub_DirectionMove = NO_DIR;
		}	
	}
	
	if(rub_CmdWindow == SHORT_PUSH)
	{
		if((rub_StateWin == STATE_0_OPEN) || (rub_StateWin == STATE_10_CLOSE))
		{
			StatusDir_LED(ALL_OFF);
		}
		else
		{
			StatusDir_LED(rub_DirectionMove);
		}
		Motion_WinLed();
	}
}

void Motion_WinLed(void)
{
	rul_TimeTransition++;												/*Acording with req. 1.5 */
	if((rub_DirectionMove == UP_DIR) && (rul_TimeTransition == 400))
	{
		rub_StateWin++;
		rul_TimeTransition = 0;
		if((rub_StateWin == STATE_10_CLOSE) && (rub_CmdWindow == LONG_PUSH))
		{
			rub_CmdWindow = NO_OP;
			rub_DirectionMove = NO_DIR;
			
		}
	}
	else if ((rub_DirectionMove == DOWN_DIR) && (rul_TimeTransition == 400))
	{
		rub_StateWin--;
		rul_TimeTransition = 0;
		if((rub_StateWin == STATE_0_OPEN) && (rub_CmdWindow == LONG_PUSH))
		{
			rub_CmdWindow = NO_OP;
			rub_DirectionMove = NO_DIR;
		}
	}
	
	
}


void AntiPinchFunc(void)							/*Acording with req. 3.2*/
{
	rub_AntipinchButton = read_Antipinch();
	if(rub_DirectionMove == UP_DIR)					/*Acording with req. 3.5*/
	{
		while(rub_AntipinchButton == PRESS)
		{
			rub_AntipinchButton = read_Antipinch();   
			if(FLAG_1MS)
			{
				rub_ValidAntipinchCnt++;
				reset_timer();
			}
		}	
	}											
	if(rub_ValidAntipinchCnt >= 10)			/*if the button was pressed at least 10ms is a valid antipinch Acording with req. 3.3*/
	{
			rub_CmdWindow = DOWN_DIR;
			StatusDir_LED(GREEN_ON_DW);			/*turn on the led green to indicate a down movement*/
			DownWinForAntipinch();
			AntipinchWait();
	}
	 
	rub_ValidAntipinchCnt = 0;					/*Acording with req. 3.4*/
	
}


void DownWinForAntipinch(void)					/*Acording with req. 3.6 : the LED bar will go down after than antipinch*/
{
	rul_TimeTransition = 0;
	while(rub_StateWin != STATE_0_OPEN)
	{
		
		if(FLAG_1MS)
		{
			rul_TimeTransition++;
			reset_timer();				
		}
		if(rul_TimeTransition == 400)
		{
			rub_StateWin--;
			LED_Motion_StateMachine();
			rul_TimeTransition = 0;
		}
	}
	rul_TimeTransition = 0;
	StatusDir_LED(ALL_OFF);						/*turn off all the leds to indicate it doesn't exist movement*/
}


void AntipinchWait(void)						/*Acording with req. 3.7, 3.8 : the module has to ignore during 5 seconds all button press*/
{												/* and after that time has to recognize every button press*/
	while(rul_TimeWait <= FIVE_SECONDS)
	{
		if(FLAG_1MS)
		{
			rul_TimeWait++;
			reset_timer();				
		}
	}
	rul_TimeWait = 0;
}


void ReadButtons(void)
{
	T_BUTTON lub_Up = NO_PRESS;
	T_BUTTON lub_Dw = NO_PRESS;
	
	lub_Up = read_Pb_Up();					/*read button UP and write in  lub_Up if the button has been pressed*/
	
	lub_Dw= read_Pb_Dw();					/*read button DOWN and write in  lub_Dw if the button has been pressed*/
		
	
	if(lub_Dw == lub_Up)					/*compare if the buttons have been pressed and if have the same value is considered as no valid*/
	{										/*acording to req.2.2 and 2.4*/
		rub_ButtonPressed = NO_PRESS;
		if((lub_Dw == PRESS) && (lub_Up == PRESS))
		{
			rub_CmdWindow = NO_OP;
		}
		
	}
	
	else
	{
		if(lub_Dw == PRESS)							/*Acording with req. 1.7*/
		{
			rub_DirectionMove = DOWN_DIR;
			rub_ButtonPressed = PRESS;
		}
		else if(lub_Up == PRESS)
		{
			rub_DirectionMove = UP_DIR;
			rub_ButtonPressed = PRESS;
		}
	}
}



/*STATE MACHINE*/										/*Acording to req. 1.4, 1.6*/
void LED_Motion_StateMachine(void)
{
	switch(rub_StateWin)
	{
		case STATE_0_OPEN:
			led_off(LED_1);
			led_off(LED_2);
			led_off(LED_3);
			led_off(LED_4);
			led_off(LED_5);
			led_off(LED_6);
			led_off(LED_7);
			led_off(LED_8);
			led_off(LED_9);
			led_off(LED_10);
			break;
	
		case STATE_1:
			led_on(LED_1);
			led_off(LED_2);
			led_off(LED_3);
			led_off(LED_4);
			led_off(LED_5);
			led_off(LED_6);
			led_off(LED_7);
			led_off(LED_8);
			led_off(LED_9);
			led_off(LED_10);
			break;
	
		case STATE_2:
			led_on(LED_1);
			led_on(LED_2);
			led_off(LED_3);
			led_off(LED_4);
			led_off(LED_5);
			led_off(LED_6);
			led_off(LED_7);
			led_off(LED_8);
			led_off(LED_9);
			led_off(LED_10);
			break;
	
		case STATE_3:
			led_on(LED_1);
			led_on(LED_2);
			led_on(LED_3);
			led_off(LED_4);
			led_off(LED_5);
			led_off(LED_6);
			led_off(LED_7);
			led_off(LED_8);
			led_off(LED_9);
			led_off(LED_10);
			break;
	
		case STATE_4:
			led_on(LED_1);
			led_on(LED_2);
			led_on(LED_3);
			led_on(LED_4);
			led_off(LED_5);
			led_off(LED_6);
			led_off(LED_7);
			led_off(LED_8);
			led_off(LED_9);
			led_off(LED_10);
			break;
	
		case STATE_5:
			led_on(LED_1);
			led_on(LED_2);
			led_on(LED_3);
			led_on(LED_4);
			led_on(LED_5);
			led_off(LED_6);
			led_off(LED_7);
			led_off(LED_8);
			led_off(LED_9);
			led_off(LED_10);
			break;
	
		case STATE_6:
			led_on(LED_1);
			led_on(LED_2);
			led_on(LED_3);
			led_on(LED_4);
			led_on(LED_5);
			led_on(LED_6);
			led_off(LED_7);
			led_off(LED_8);
			led_off(LED_9);
			led_off(LED_10);
			break;
	
		case STATE_7:
			led_on(LED_1);
			led_on(LED_2);
			led_on(LED_3);
			led_on(LED_4);
			led_on(LED_5);
			led_on(LED_6);
			led_on(LED_7);
			led_off(LED_8);
			led_off(LED_9);
			led_off(LED_10);
			break;
	
		case STATE_8:
			led_on(LED_1);
			led_on(LED_2);
			led_on(LED_3);
			led_on(LED_4);
			led_on(LED_5);
			led_on(LED_6);
			led_on(LED_7);
			led_on(LED_8);
			led_off(LED_9);
			led_off(LED_10);
			break;
	
		case STATE_9:
			led_on(LED_1);
			led_on(LED_2);
			led_on(LED_3);
			led_on(LED_4);
			led_on(LED_5);
			led_on(LED_6);
			led_on(LED_7);
			led_on(LED_8);
			led_on(LED_9);
			led_off(LED_10);
			break;
	
		case STATE_10_CLOSE:
			led_on(LED_1);
			led_on(LED_2);
			led_on(LED_3);
			led_on(LED_4);
			led_on(LED_5);
			led_on(LED_6);
			led_on(LED_7);
			led_on(LED_8);
			led_on(LED_9);
			led_on(LED_10);
			break;
			
		default:
			if(rub_StateWin < STATE_0_OPEN)
			{
				rub_StateWin = STATE_0_OPEN;
				rub_CmdWindow = NO_OP;
			}
			else
			{
				rub_StateWin = STATE_10_CLOSE;
				rub_CmdWindow = NO_OP;
			}
			break;
	}
}



void StatusDir_LED(T_DIRLED lub_Direction)			/*Acording to req. 1.8*/
{
	switch (lub_Direction)
	{
	case BLUE_ON_UP:
		led_on(LED_BLUE);
		led_off(LED_GREEN);
		break;
		
	case GREEN_ON_DW:
		led_on(LED_GREEN);
		led_off(LED_BLUE);
		break;
		
	case ALL_OFF:
		led_off(LED_BLUE);
		led_off(LED_GREEN);
		break;
		
	default:
		led_off(LED_BLUE);
		led_off(LED_GREEN);
		break;
		
	}
}

