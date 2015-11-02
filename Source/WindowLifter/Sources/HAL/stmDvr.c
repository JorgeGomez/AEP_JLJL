/*
 * stmDvr.c
 *
 *  Created on: Oct 29, 2015
 *      Author: Jorge
 */

#include "HAL\stmDvr.h"
#include "HAL\MainConfig.h"


void stm_init_fnc(void)
{

    STM.CR.B.TEN = 0x0;    
        /* Disable System Timer Module for initialization          */
    STM.CR.B.FRZ = 0x1;
    	/*Freeze. Allows the timer counter to be stopped when the device enters debug mode.  	 */
    
/* ----------------------------------------------------------- */
/*                     Configure Counter Prescaler                */
/* ----------------------------------------------------------- */

    STM.CR.B.CPS = 0;    
        /* Counter Prescaler is 1        */

/* ----------------------------------------------------------- */
/*                     Configure System Timer Registers                */
/* ----------------------------------------------------------- */

    STM.CH[0].CMP.R = COMP_1MS_64MHZ;    
        /* System Timer Channel 0's Compare value is :64M   */
    
    STM.CH[0].CCR.B.CEN =0x1;    
        /* System Timer Channel 0: Enable    */
        
    STM.CH[1].CMP.R =0x00000000;    
        /* System Timer Channel 1's Compare value is :0    */
    
    STM.CH[1].CCR.B.CEN =0x0;    
        /* System Timer Channel 1: Disabled    */
    
    STM.CH[2].CMP.R =0x00000000;    
        /* System Timer Channel 2's Compare value is :0    */
    
    STM.CH[2].CCR.B.CEN =0x0;    
        /* System Timer Channel 2: Disabled    */
    
    STM.CH[3].CMP.R =0x00000000;    
        /* System Timer Channel 3's Compare value is :0    */
    
    STM.CH[3].CCR.B.CEN =0x0;    
        /* System Timer Channel 3: Disabled    */
    


    STM.CR.B.TEN = 1;    
    
        /* System Timer Module is:  Enable        */

}

void reset_timer(void)
{
	STM.CH[0].CIR.B.CIF = 1;	/* Clear interrupt flag */ 
	STM.CNT.R = 0;
}




