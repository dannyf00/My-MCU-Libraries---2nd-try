#include <lpc210x.h>				//we use keil lpc210x
//#include "gpio.h"
#include "tmr1.h"					//we use tmr1

void (*_tmr1_func) (void);			//tmr0_function ptr

void _tmr1_func_empty(void) {
}

void tmr1_isr(void) __irq {
  	T1IR        = TxIR_ISRonMR0;	// Clear interrupt flag
  	VICVectAddr = 0;				// Acknowledge Interrupt by writting to it
	_tmr1_func();					//execute my isr
}

void tmr1_init(unsigned long prescaler, unsigned long period) {
	T1TCR = 0;					//stop the timer

	//set up the tmr parameters
  	T1PR = prescaler;					//prescaler set user specification
  	T1MR0 = period;					//tmr1 channel 0, interrupt on match
  	T1MCR = (T1MCR & (~TxMCR_MaskMR0)) |	//clear t0mcr_mr0 bits
			(TxMCR_ISRonMR0) |				//interrupt on mr0
			(TxMCR_ResetonMR0);					//Reset on MR0
  	T1TC=0;							//reset tmr1 timer/counter
  	
	VICVectAddr1 = (unsigned long)tmr1_isr;       // set interrupt vector in 0
  	VICVectCntl1 = (1<<5) | TMR1_ISR_CH;		// use it for Timer 1 Interrupt. irq5 + enable bits (0x20, bit 5)
  	VICIntEnable = (1<<TMR1_ISR_CH);			// Enable Timer1 Interrupt. turn on irq4

  	T1TCR = 1;						// Timer1 Enable
	_tmr1_func = _tmr1_func_empty;	//point to an empty ptr

}

void tmr1_act(void (*func_ptr)(void)) {
	_tmr1_func=func_ptr;
}

