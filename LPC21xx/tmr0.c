#include <lpc210x.h>				//we use keil lpc210x
//#include "delay.h"
//#include "gpio.h"
#include "tmr0.h"					//we use tmr0

void (*_tmr0_func) (void);			//tmr0_function ptr

void _tmr0_func_empty(void) {
}

void tmr0_isr(void) __irq {
  	T0IR        = TxIR_ISRonMR0;			// Clear interrupt flag
  	VICVectAddr = 0;						// Acknowledge Interrupt by writting to it
	_tmr0_func();							//execute my isr
}

void tmr0_init(unsigned long prescaler, unsigned long period) {
  	T0TCR = 0;								//stop tmr0
	
	//set tmr parameters
	T0PR = prescaler;						//prescaler set user specification
  	T0MR0 = period;							//tmr0 channel 0, interrupt on match
  	T0MCR = (T0MCR & (~TxMCR_MaskMR0)) |	//clear t0mcr_mr0 bits
			TxMCR_ISRonMR0 |				//interrupt on mr0
			TxMCR_ResetonMR0;				//Reset on MR0
  	T0TC = 0;								//reset tmr0 timer/counter
  	
	//vector 0 used for tmr0
	VICVectAddr0 = (unsigned long)tmr0_isr;       // set interrupt vector in 0
  	VICVectCntl0 = (1<<5) | TMR0_ISR_CH;		// use it for Timer 0 Interrupt. irq4 + enable bits (0x20, bit 5)
  	VICIntEnable = (1<<TMR0_ISR_CH);			// Enable Timer0 Interrupt. turn on irq4

  	T0TCR = 1;						// Timer0 Enable

	_tmr0_func = _tmr0_func_empty;	//point to an empty ptr
}

void tmr0_act(void (*func_ptr)(void)) {
	_tmr0_func=func_ptr;
}

