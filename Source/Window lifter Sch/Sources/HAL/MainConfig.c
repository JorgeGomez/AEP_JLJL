/*============================================================================*/
/*                         			AEP		                                  */
/*============================================================================*/
/*                        OBJECT SPECIFICATION                                */
/*============================================================================*/
/*!
 * $Source: MainConfig.c $
 * $Revision: 1.0 $
 * $Author: Jorge Gomez $
 * $Date: Nov/12/15 $
 */
/*============================================================================*/
/* DESCRIPTION :                                                              */
/** \MainConfig
    Provide the function to initialize the differents periphereals of the uc.
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
/*                    			OBJECT HISTORY                          	  */
/*============================================================================*/
/*  REVISION 	|  		DATE  		|     	COMMENT     	  |		AUTHOR 	  */
/*----------------------------------------------------------------------------*/
/*   1.0 		|  	Nov/13/15		| initialize the GPIO     |  Jorge Gomez  */
/*============================================================================*/
/*                              					                          */
/*============================================================================*/
/*
 * $Log: MainConfig.c  $
  ============================================================================*/

/* Includes */
/*============================================================================*/
#include "HAL/MPC5606B.h"
#include "HAL/MainConfig.h"
#include "HAL/IntcInterrupts.h"
#include "HAL/stdtypedef.h"


/* Constants and types  */
/*============================================================================*/



/* Variables */
/*============================================================================*/
T_BOOLEAN rbi_TickFlag = FALSE;

/* Private functions prototypes */
/*============================================================================*/
void init_modes_and_clocks(void);
void disableWatchdog(void);
void initPeriClkGen(void);
void config_IO(void);
void pit_config_fnc(void);
void pit_isr(void);
void init_pit_interrupts(void);


/* Inline functions */
/*============================================================================*/




/* Private functions */
/*============================================================================*/

/**************************************************************
 *  Name                 :  init_modes_and_clocks
 *  Description          :  Init function of Scheduler module
 *  Parameters           :  void
 *  Return               :  void
 *  Precondition         :  This function must be called on the cpu initialization.
 *  Postcondition        :  The cpu are running on RUN mode 1.
 **************************************************************/
void init_modes_and_clocks(void) 
{
	ME.MER.R = 0x0000001D;          	/* Enable DRUN, RUN0, SAFE, RESET modes */
	
	/* Initialize PLL before turning it on: */
	CGM.FMPLL_CR.R = 0x02400100;    	/* 8 MHz xtal: Set PLL0 to 64 MHz */   
	ME.RUN[0].R = 0x001F0074;       	/* RUN0 cfg: 16MHzIRCON,OSC0ON,PLL0ON,syclk=PLL0 */
	ME.RUNPC[1].R = 0x00000010; 	  	/* Peri. Cfg. 1 settings: only run in RUN0 mode */
  	ME.PCTL[68].R = 0x01; 	    		/*MPC56xxB/S SIU: select ME.RUNPC[1] */  
  	ME.PCTL[92].R = 0x01; 	      		/* MPC56xxB/S PIT: select ME.RUNPC[1] */	
  	
  	/* Mode Transition to enter RUN0 mode: */
  	ME.MCTL.R = 0x40005AF0;         /* Enter RUN0 Mode & Key */
  	ME.MCTL.R = 0x4000A50F;         /* Enter RUN0 Mode & Inverted Key */  
  	while (ME.GS.B.S_MTRANS) {}     /* Wait for mode transition to complete */    
                                  	
  	/* Note: could wait here using timer and/or I_TC IRQ */
  	while(ME.GS.B.S_CURRENTMODE != 4) {} /* Verify RUN0 is the current mode */
}

/**************************************************************
 *  Name                 :  disableWatchdog
 *  Description          :  Function to disable the watchdog
 *  Parameters           :  void
 *  Return               :  void
 *  Precondition         :  This function must be called after cpu initialization.
 *  Postcondition        :  The watchdog is disabled.
 **************************************************************/
void disableWatchdog(void) 
{
	SWT.SR.R = 0x0000c520;     /* Write keys to clear soft lock bit */
  	SWT.SR.R = 0x0000d928; 
  	SWT.CR.R = 0x8000010A;     /* Clear watchdog enable (WEN) */
}        

/**************************************************************
 *  Name                 :  initPeriClkGen
 *  Description          :  Init function of peripherials set 
 *  Parameters           :  void
 *  Return               :  void
 *  Precondition         :  This function must be called on the cpu initialization.
 *  Postcondition        :  The pheripherial set can be used.
 **************************************************************/
void initPeriClkGen(void) 
{
	/* Use the following code as required for MPC56xxB or MPC56xxS:*/
  	CGM.SC_DC2.R = 0x80;   /* MPC56xxB/S: Enable peri set 3 sysclk divided by 1  omg */
}

/**************************************************************
 *  Name                 :  config_Emb_IO
 *  Description          :  Init function of GPIO embedded
 *  Parameters           :  void
 *  Return               :  void
 *  Precondition         :  This function must be called on the cpu initialization.
 *  Postcondition        :  The GPIOs can be used.
 **************************************************************/
void config_IO(void)
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
  	SIU.PCR[PUSHB_ANTIPINCH].R = 0x0100;

	/*Bar leds is seted  off */
	SIU.GPDO[LED_1].R = ON;	
	SIU.GPDO[LED_2].R = ON;
	SIU.GPDO[LED_3].R = ON;
	SIU.GPDO[LED_4].R = ON;
	SIU.GPDO[LED_5].R = ON;
	SIU.GPDO[LED_6].R = ON;
	SIU.GPDO[LED_7].R = ON;
	SIU.GPDO[LED_8].R = ON;
	SIU.GPDO[LED_9].R = ON;
	SIU.GPDO[LED_10].R = ON;

	/* Direction leds are seted off */
	SIU.GPDO[LED_GREEN].R = OFF;
	SIU.GPDO[LED_BLUE].R = OFF;

} 



/* Exported functions */
/*============================================================================*/

/**************************************************************
 *  Name                 :  init_system
 *  Description          :  Initialize all the modules of the cpu
 *  Parameters           :  void
 *  Return               :  void
 *  Precondition         :  This function must be called after correct startup.
 *  Postcondition        :  All the cpu and the peripherials are initialized.
 **************************************************************/
void init_system(void)
{
	init_modes_and_clocks();
	initPeriClkGen();
	config_IO();
	init_pit_interrupts();
}

/**************************************************************
 *  Name                 :  read_button
 *  Description          :  Read the status of a selected button
 *  Parameters           :  T_UBYTE
 *  Return               :  E_BUTTON
 *  Precondition         :  This function must be called after cpu initialization.
 *  Postcondition        :  Return the value of the input.
 **************************************************************/
E_BUTTON read_button(T_UBYTE lub_Ch)
{
	return SIU.GPDI[lub_Ch].B.PDI;
}

/**************************************************************
 *  Name                 :  led_on
 *  Description          :  Turn on the selected LED
 *  Parameters           :  T_UBYTE
 *  Return               :  void
 *  Precondition         :  This function must be called after cpu initialization.
 *  Postcondition        :  The LED selected is going to turn on.
 **************************************************************/
void led_on(T_UBYTE lub_Ch_On)
{
	SIU.GPDO[lub_Ch_On].R = ON;
}

/**************************************************************
 *  Name                 :  led_off
 *  Description          :  Turn off the selected LED
 *  Parameters           :  T_UBYTE
 *  Return               :  void
 *  Precondition         :  This function must be called after cpu initialization.
 *  Postcondition        :  The selected LED  is going to turn off.
 **************************************************************/
void led_off(T_UBYTE lub_Ch_Off)
{
	SIU.GPDO[lub_Ch_Off].R = OFF;
}

/**************************************************************
 *  Name                 :  led_toggle
 *  Description          :  Toggle the LED status selected
 *  Parameters           :  T_UBYTE
 *  Return               :  void
 *  Precondition         :  This function must be called after cpu initialization.
 *  Postcondition        :  The selected LED is going to toggle its status.
 **************************************************************/
void led_toggle(T_UBYTE lub_Ch_Toogle)
{
	SIU.GPDO[lub_Ch_Toogle].R ^= 1;
}

/**************************************************************
 *  Name                 :  led_on_more
 *  Description          :  Turns on the selected LEDs, from start LED to end LED
 *  Parameters           :  lub_Ch_On_Start, lub_Ch_On_End
 *  Return               :  void
 *  Precondition         :  This function must be called after cpu initialization.
 *  Postcondition        :  The selected LEDs are going to turn off.
 **************************************************************/
void led_on_more(T_UBYTE lub_Ch_On_Start, T_UBYTE lub_Ch_On_End)
{
	T_UBYTE lub_DeltaOn = 0, lub_CountOn = 0;
	
	lub_DeltaOn = lub_Ch_On_End - lub_Ch_On_Start;	/*Calculate the difference between the start LED and end LED*/
	
	for(lub_CountOn = lub_Ch_On_Start; lub_CountOn <=(lub_Ch_On_Start + lub_DeltaOn); lub_CountOn++)
	{
		SIU.GPDO[lub_CountOn].R = ON;
	}

}

/**************************************************************
 *  Name                 :  led_off_more
 *  Description          :  Turns off the selected LEDs from start LED to end LED
 *  Parameters           :  lub_Ch_Off_Start, lub_Ch_Off_End
 *  Return               :  void
 *  Precondition         :  This function must be called after cpu initialization.
 *  Postcondition        :  The selected LED  is going to turn off.
 **************************************************************/
void led_off_more(T_UBYTE lub_Ch_Off_Start, T_UBYTE lub_Ch_Off_End)
{
	T_UBYTE lub_DeltaOff = 0, lub_CountOff = 0;
	
	lub_DeltaOff = lub_Ch_Off_End - lub_Ch_Off_Start;	/*Calculate the difference between the start LED and end LED*/
	
	for(lub_CountOff =lub_Ch_Off_Start; lub_CountOff <= (lub_Ch_Off_Start + lub_DeltaOff); lub_CountOff++)
	{
		SIU.GPDO[lub_CountOff].R = OFF;
	}

}

/**************************************************************
 *  Name                 :  pit_config_fnc
 *  Description          :  Init function of PIT module
 *  Parameters           :  void
 *  Return               :  void
 *  Precondition         :  This function must be called on the cpu initialization.
 *  Postcondition        :  Function init_pit_interrupts can be called.
 **************************************************************/
void pit_config_fnc(void)
{
    PIT.PITMCR.B.MDIS   = 1;    
        /*Disable PIT for initialization         */

    PIT.CH[0].LDVAL.R  = 64000;    
        /*value loaded in the Timer0: 64k    */

    PIT.CH[0].TCTRL.B.TIE  = 1;    
        /*Timer 0 Interrupt : Enable    */

    PIT.CH[0].TCTRL.B.TEN = 1;    
        /*Start Timer 0 is : Enable    */ 
    
    PIT.PITMCR.B.FRZ = 1;
    	/*Freeze enable*/

    PIT.PITMCR.B.MDIS = 0;    
        /*PIT Module : Enable        */

}

/**************************************************************
 *  Name                 :  init_pit_interrupts
 *  Description          :  Init function of PIT interrupt
 *  Parameters           :  void
 *  Return               :  void
 *  Precondition         :  This function must be called after the function pit_config_fnc.
 *  Postcondition        :  The Interrupt Service Routine can be called.
 **************************************************************/
void init_pit_interrupts(void)
{
	pit_config_fnc();
	INTC_InstallINTCInterruptHandler(pit_isr,59,1); 
		/* vector59 for PIT Timer 0 */
	INTC.CPR.R = 0;
		/*assign the priority*/
}

/**************************************************************
 *  Name                 :  pit_isr
 *  Description          :  Interrupt service routine for PIT
 *  Parameters           :  void
 *  Return               :  void
 *  Precondition         :  This function must be called every ms.
 *  Postcondition        :  The TickFlag is setted.
 **************************************************************/
void pit_isr(void)
{    		
		/* There's single interrupt for the ch0 of the pit: */
	
		if(PIT.CH[0].TFLG.B.TIF == 1)  
		{			
			rbi_TickFlag = TRUE;		/* toggle LED */
			PIT.CH[0].TFLG.B.TIF = 1;	/* Clear interrupt flag */ 
		}
		else
		{
			/* ... */
		}
}



 /* Notice: the file ends with a blank new line to avoid compiler warnings */
