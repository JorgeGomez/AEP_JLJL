/*
 * Init_Interrupts.c
 *
 *  Created on: Oct 29, 2015
 *      Author: Jorge
 */
#include "HAL\IntcInterrupts.h"
#include "HAL\MPC5606B.h"
#include "HAL\stmDvr.h"
#include "HAL\MainConfig.h"
#include "MAL\Init_Interrupts.h"
#include "Application\WindowLifter.h"

void init_stm_interruptCH0(void)
{
	INTC_InstallINTCInterruptHandler(STM_Int_isr,30,1); /* vector30 for STM CH 0 */
}

void init_ExtInterruptPE2(void)
{
	INTC_InstallINTCInterruptHandler(SIUL_Ext_Int_isr,43,2); /* vector43 for EIRQ21 */
	DEF_PRI;
}

void STM_Int_isr(void)
{    		
			
		if(FLAG_1MS)  
		{			
			Inputs_validation();
			reset_timer();
		}
		else
		{
			/* ... */
		}

}

void SIUL_Ext_Int_isr(void)
{    		
	/* There's single interrupt vector for 8 IRQs. Test if interrupt comes from IRQ0: */
	if(FLAG_EXT_INTRP) // antes el 0 para el pa3 y 21 para el pe2
	{			
		AntiPinchFunc();
		reset_ExtIntrpFlag();
	}
	else
	{
		/* ... */
	}

}
