#include <regx51.h>						//we use keil c51
#include "gpio.h"
#include "tmr0.h"						//we use tmr0

void (*_tmr0_isr_ptr)(void);			//function ptr

void _tmr0_isr(void) interrupt TF0_VECTOR {
	//clear the flag					//automatically done by hardware
	_tmr0_isr_ptr();					//call the handler
}

void tmr0_empty_ptr(void) {				//empty ptr
}

//initialize the timer
//prescaler not used - for compatability reasons only
//8-bit period
void tmr0_init(unsigned char prescaler, unsigned char period) {
	TR0=0;								//turn off the timer
	_tmr0_isr_ptr=tmr0_empty_ptr;		//point isr to the empty handler
	TMOD = (TMOD & 0xf0) | 0x02;		//tmr0 in mode 2: 16 bit tmr, auto reload TH0
	TH0=-period;						//set the autoreload period
	TL0=TH0;								//reset the timer / counter
	ET0=1;								//enable tmr0 interrupt
	TR0=1;								//turn on the timer
}

//set up the isr handler
void tmr0_act(void (*isr_ptr)(void)) {	//set up the isr pointer
	_tmr0_isr_ptr=isr_ptr;
}
