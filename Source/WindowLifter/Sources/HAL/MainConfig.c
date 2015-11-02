/*
 * MainConfig.c
 *
 *  Created on: Oct 29, 2015
 *      Author: Jorge
 */

/*
 * MainConfig.c
 *
 *  Created on: Oct 9, 2015
 *      Author: Jorge
 */
#include "HAL\MPC5606B.h"
#include "HAL\MainConfig.h"

/****Functions****/
void init_modes_and_clocks(void) 
{
	ME.MER.R = 0x0000001D;          	/* Enable DRUN, RUN0, SAFE, RESET modes */
	
	/* Initialize PLL before turning it on: */
	CGM.FMPLL_CR.R = 0x02400100;    	/* 8 MHz xtal: Set PLL0 to 64 MHz */   
	ME.RUN[0].R = 0x001F0074;       	/* RUN0 cfg: 16MHzIRCON,OSC0ON,PLL0ON,syclk=PLL0 */
	ME.RUNPC[1].R = 0x00000010; 	  	/* Peri. Cfg. 1 settings: only run in RUN0 mode */
  	ME.PCTL[68].R = 0x01; 	    /*MPC56xxB/S SIU: select ME.RUNPC[1] */   
  	
  	/* Mode Transition to enter RUN0 mode: */
  	ME.MCTL.R = 0x40005AF0;         /* Enter RUN0 Mode & Key */
  	ME.MCTL.R = 0x4000A50F;         /* Enter RUN0 Mode & Inverted Key */  
  	while (ME.GS.B.S_MTRANS) {}     /* Wait for mode transition to complete */    
                                  	
  	/* Note: could wait here using timer and/or I_TC IRQ */
  	while(ME.GS.B.S_CURRENTMODE != 4) {} /* Verify RUN0 is the current mode */
}


void disableWatchdog(void) 
{
	SWT.SR.R = 0x0000c520;     /* Write keys to clear soft lock bit */
  	SWT.SR.R = 0x0000d928; 
  	SWT.CR.R = 0x8000010A;     /* Clear watchdog enable (WEN) */
}        



void initPeriClkGen(void) 
{
	/* Use the following code as required for MPC56xxB or MPC56xxS:*/
  	CGM.SC_DC2.R = 0x80;   /* MPC56xxB/S: Enable peri set 3 sysclk divided by 1  omg */
}


void Config_IO(void)
{
	/*Bar leds are seted as outputs */
	SIU.PCR[LED_1].R = 0x200;	
  	SIU.PCR[LED_2].R = 0x200;
  	SIU.PCR[LED_3].R = 0x200;
  	SIU.PCR[LED_4].R = 0x200;
  	SIU.PCR[LED_5].R = 0x200;
  	SIU.PCR[LED_6].R = 0x200;
  	SIU.PCR[LED_7].R = 0x200;
  	SIU.PCR[LED_8].R = 0x200;
  	SIU.PCR[LED_9].R = 0x200;
  	SIU.PCR[LED_10].R = 0x200;

  	/* Direction leds are seted as outputs */
  	SIU.PCR[LED_GREEN].R = 0x200;
  	SIU.PCR[LED_BLUE].R = 0x200;
  		
  	/* Embedded board buttons are seted as inputs */
  	SIU.PCR[PUSHB_UP].R = 0x100;	
  	SIU.PCR[PUSHB_DOWN].R = 0x100;
 	
  	
  	SIU.PCR[PUSHB_ANTIPINCH].R = 0x0100;	/* Pin PE[2]-EIRQ21 configured as GPIO, input, pull up enable */
	SIU.IFEER.B.IFEE21 = 1;	/* Enable falling edge event on EIRQ21 */	
	SIU.IRER.B.IRE21 = 1;		/* Enable interrupt EIRQ21 */
	
	/*Bar leds is seted as off */
	SIU.GPDO[LED_1].R = 1;	
	SIU.GPDO[LED_2].R = 1;
	SIU.GPDO[LED_3].R = 1;
	SIU.GPDO[LED_4].R = 1;
	SIU.GPDO[LED_5].R = 1;
	SIU.GPDO[LED_6].R = 1;
	SIU.GPDO[LED_7].R = 1;
	SIU.GPDO[LED_8].R = 1;
	SIU.GPDO[LED_9].R = 1;
	SIU.GPDO[LED_10].R = 1;

	  	/* Direction leds are seted as off */
	SIU.GPDO[LED_GREEN].R = 1;
	SIU.GPDO[LED_BLUE].R = 1;

}

void reset_ExtIntrpFlag(void)
{
	SIU.ISR.B.EIF21 = 1;	/* Clear interrupt flag */
}

T_BUTTON read_Pb_Dw(void)
{
	return SIU.GPDI[PUSHB_DOWN].B.PDI;
}

T_BUTTON read_Pb_Up(void)
{
	return SIU.GPDI[PUSHB_UP].B.PDI;
}

T_BUTTON read_Antipinch(void)
{
	return SIU.GPDI[PUSHB_ANTIPINCH].B.PDI;
}

void led_on(T_UBYTE lub_Ch)
{
	SIU.GPDO[lub_Ch].R = ON;
}

void led_off(T_UBYTE lub_Ch)
{
	SIU.GPDO[lub_Ch].R = OFF;
}

