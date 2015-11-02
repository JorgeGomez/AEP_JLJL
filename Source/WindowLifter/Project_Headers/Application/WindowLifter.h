/*
 * WindowLifter.h
 *
 *  Created on: Oct 29, 2015
 *      Author: Jorge
 */

#ifndef WINDOWLIFTER_H_
#define WINDOWLIFTER_H_

#include "HAL\MainConfig.h"


#define FIVE_SECONDS		5000
#define FLAG_1MS			STM.CH[0].CIR.B.CIF == 1

void Init_System(void);
void WinLifterApp(void);
void Inputs_validation(void);
void ReadButtons(void);
void AntipinchWait(void);
void DownWinForAntipinch(void);
void AntiPinchFunc(void);
void LED_Motion_StateMachine(void);
void StatusDir_LED(T_DIRLED lub_Direction);
void Motion_WinLed(void);


#endif /* WINDOWLIFTER_H_ */
