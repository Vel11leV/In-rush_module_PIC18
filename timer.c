
#include <p18cxxx.h>

volatile unsigned Timer1;

void InterruptHandlerHigh (void);

void timer2init(void)
{


RCONbits.IPEN=0b1;					//only interrupts of high priority

INTCONbits.GIEH=0b1;				//ALL INTERRAPTS

PIE1bits.TMR2IE=1;					// флаг розрешения прерывания от таймера2

IPR1bits.TMR2IP=0b1;				//PRIORITY OF INTERRUPTION FOR TIMER2 1 IS HIGH
	
/*-----------------------------*/
PR2=49;								//register of timer interruption(it was 50)
	
/*----------PRESCALE-----------*/
T2CONbits.T2CKPS1 = 0b0;
T2CONbits.T2CKPS0 = 0b1;

/*--------POSTSCALE-----------*/
T2CONbits.T2OUTPS0 = 0b0;
T2CONbits.T2OUTPS1 = 0b0;
T2CONbits.T2OUTPS2 = 0b0;
T2CONbits.T2OUTPS3 = 0b0;
/*-----------------------------*/

T2CONbits.TMR2ON = 0b1;			//timer is on

Timer1=0;						//	инициализация переменных
}

/*----------------------INTERRUPTION----------------------------------------*/
//---------------------------------------------------------------------
// High priority interrupt routine

#pragma interrupt InterruptHandlerHigh

void InterruptHandlerHigh ()
{
  if (PIR1bits.TMR2IF)
    {
	PIR1bits.TMR2IF=0;
	 Timer1--;                                 
      
    }
}

//-----------------------------------------------------------------------
// High priority interrupt vector

#pragma code InterruptVectorHigh = 0x08
void InterruptVectorHigh (void)
{
  _asm
    goto InterruptHandlerHigh //jump to interrupt routine
  _endasm
}

#pragma code

//-----------------------------------------------------------------------













