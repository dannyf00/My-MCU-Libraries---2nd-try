#include <regx51.h>						//we use keil c51
#include "gpio.h"
#include "tmr0.h"						//we use tmr0

void (*_tmr0_isr_ptr)(void);			//function ptr
unsigned short _tmr0_period;

void _tmr0_isr(void) interrupt TF0_VECTOR {
	//clear the flag					//automatically done by hardware
#ifdef TMR0_16BIT
	TH0+=(_tmr0_period) >> 8;					//set the autoreload period
	TL0+=_tmr0_period;						//reset the timer / counter
#endif
	_tmr0_isr_ptr();					//call the handler
}

void tmr0_empty_ptr(void) {				//empty ptr
}

#ifdef TMR0_16BIT
//initialize the timer
//prescaler not used - for compatability reasons only
//16-bit period
void tmr0_init(unsigned char prescaler, unsigned short period) {
	TR0=0;								//turn off the timer
	_tmr0_isr_ptr=tmr0_empty_ptr;		//point isr to the empty handler
	TMOD = (TMOD & 0xf0) | 0x01;		//tmr0 in mode 2: 16 bit tmr, auto reload TH0
	_tmr0_period=-period;
	TH0=(_tmr0_period) >> 8;			//set the autoreload period
	TL0=_tmr0_period;					//reset the timer / counter
	ET0=1;								//enable tmr0 interrupt
	TR0=1;								//turn on the timer
}
#else
//initialize the timer
//prescaler not used - for compatability reasons only
//8-bit period
void tmr0_init(unsigned char prescaler, unsigned char period) {
	TR0=0;								//turn off the timer
	_tmr0_isr_ptr=tmr0_empty_ptr;		//point isr to the empty handler
	TMOD = (TMOD & 0xf0) | 0x02;		//tmr0 in mode 2: 16 bit tmr, auto reload TH0
	_tm0r_period=-period;
	TH0=_tmr0_period;					//set the autoreload period
	TL0=_0;								//reset the timer / counter
	ET0=1;								//enable tmr0 interrupt
	TR0=1;								//turn on the timer
}
#endif

//set up the isr handler
void tmr0_act(void (*isr_ptr)(void)) {	//set up the isr pointer
	_tmr0_isr_ptr=isr_ptr;
}
