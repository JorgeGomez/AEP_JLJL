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

T_UBYTE rub_TimeMsCnt = 0, rub_TimeWait = 0, rub_ValidAntipinchCnt = 0;
T_BOOLEAN rub_ValidPress = FALSE;
T_COMAND_WIN rub_CmdWindow = NO_OP;
T_BUTTON rub_ButtonPressed = NO_PRESS, rub_AntipinchButton = NO_PRESS;
T_DIRECTION rub_DirectionMove = NO_DIR;



void WinLifterApp(void)
{
	ReadButtons();
	Inputs_validation();
	StatusDir_LED(rub_DirectionMove);
	
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

void Inputs_validation()
{
	if(rub_ButtonPressed == PRESS)
	{
		rub_TimeMsCnt++; 
		if(rub_TimeMsCnt >= 10)				//Acording with req. 2.3 and 2.1
		{
			rub_ValidPress = TRUE;
		}
		else if(rub_TimeMsCnt > 500)		//Acording with req. 2.5 and 2.7
		{
			rub_CmdWindow = LONG_PUSH;		//falta agregar el cambio manual
		}
	}
	else
	{
		if(rub_TimeMsCnt <= 500)			//Asummtion acording with req. 2.6 and 2.8
		{
			rub_CmdWindow = SHORT_PUSH;
		}
		else if(rub_TimeMsCnt < 10)			//Acording with req. 2.2 and 2.4
		{
			rub_ValidPress = FALSE;
		}
		rub_TimeMsCnt = 0;
		
	}
}

void AntiPinchFunc(void)		//Acording with req. 3.0
{
	rub_AntipinchButton = read_Antipinch();
		
	while(rub_AntipinchButton == PRESS)
	{
		rub_AntipinchButton = read_Antipinch();
		if(FLAG_1MS)
		{
			rub_ValidAntipinchCnt++;
			reset_timer();
		}
	}	
												
	if(rub_AntipinchButton >= 10)			//Acording with req. 3.3
	{
		AntipinchWait();																					
	}
	else
	{
		rub_ValidAntipinchCnt = 0;			//Acording with req. 3.4
	}
}

void ReadButtons(void)
{
	T_BUTTON lub_Up = NO_PRESS;
	T_BUTTON lub_Dw = NO_PRESS;
	
	lub_Up = read_Pb_Up();					//read button UP and write in  lub_Up if the button has been pressed
	
	lub_Dw= read_Pb_Dw();					//read button DOWN and write in  lub_Dw if the button has been pressed
		
	if(lub_Dw == lub_Up)					//compare if the buttons have been pressed and if have the same value is considered as no valid
	{										//acording to req.2.2 and 2.4
		rub_ButtonPressed = NO_PRESS;
		rub_DirectionMove = NO_DIR;
	}
	
	else
	{
		if(lub_Dw == PRESS)							//Acording with req. 1.7
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


void AntipinchWait(void)	//Acording with req. 3.5
{
	if(rub_DirectionMove == UP_DIR)
		{
			rub_DirectionMove = DOWN_DIR;
			
			//TO DO: add the state machine of the LED Bar
			
			while(rub_TimeWait == FIVE_SECONDS)
			{
				if(FLAG_1MS)
				{
					rub_TimeWait++;
					reset_timer();				
				}
			}
			rub_TimeWait = 0;
		}
		else
		{

		}
}


void LED_Motion(void)
{
	
}

void StatusDir_LED(T_BUTTON lub_Direction)
{
	if(rub_ValidPress == TRUE)
	{
		if(lub_Direction == UP_DIR)
		{
			led_on(LED_BLUE);
			led_off(LED_GREEN);
		}
		else if(lub_Direction == DOWN_DIR)
		{
			led_on(LED_GREEN);
			led_off(LED_BLUE);
		}
		else
		{
			led_off(LED_BLUE);
			led_off(LED_GREEN);
		}
	}
}

/*
 * To Do: 
 * 


#define LED_1_ON 	SIU.GPDO[LED_1].R = 0;



if(rub_DirectionMove == UP_DIR)
	{
		rub_DirectionMove = DOWN_DIR;
		
		//TO DO: add the state machine of the LED Bar
		
		while(rub_TimeWait == FIVE_SECONDS)
		{
			if(FLAG_1MS)
			{
				rub_TimeWait++;
				reset_timer();				
			}
		}
		rub_TimeWait = 0;
	}
	else
	{

	}
	
 */

