/*
 * Init_Interrupts.h
 *
 *  Created on: Oct 29, 2015
 *      Author: Jorge
 */

#ifndef INIT_INTERRUPTS_H_
#define INIT_INTERRUPTS_H_

#define FLAG_1MS			STM.CH[0].CIR.B.CIF == 1
#define FLAG_EXT_INTRP		SIU.ISR.B.EIF21 == 1
#define DEF_PRI				INTC.CPR.R = 0

void init_stm_interruptCH0(void);
void init_ExtInterruptPE2(void);
void SIUL_Ext_Int_isr(void);
void STM_Int_isr(void);


#endif /* INIT_INTERRUPTS_H_ */
