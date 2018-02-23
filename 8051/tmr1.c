#include <regx51.h>						//we use keil c51
#include "gpio.h"
#include "tmr1.h"						//we use tmr1

void (*_tmr1_isr_ptr)(void);			//function ptr
unsigned short _tmr1_period;

void _tmr1_isr(void) interrupt TF1_VECTOR {
	//clear the flag					//automatically done by hardware
#ifdef TMR1_16BIT
	TH1+=(_tmr1_period) >> 8;			//set the autoreload period
	TL1+=_tmr1_period;					//reset the timer / counter
#endif
	_tmr1_isr_ptr();					//call the handler
}

void tmr1_empty_ptr(void) {				//empty ptr
}

#ifdef TMR1_16BIT
//initialize the timer
//prescaler not used - for compatability reasons only
//16-bit period
void tmr1_init(unsigned char prescaler, unsigned short period) {
	TR1=0;								//turn off the timer
	_tmr1_isr_ptr=tmr1_empty_ptr;		//point isr to the empty handler
	TMOD = (TMOD & 0x0f) | 0x10;		//tmr1 in mode 1: 16 bit tmr
	_tmr1_period=-period;
	TH1=(_tmr1_period) >> 8;			//set the autoreload period
	TL1=_tmr1_period;					//reset the timer / counter
	ET1=1;								//enable tmr0 interrupt
	TR1=1;								//turn on the timer
}
#else
//initialize the timer
//prescaler not used - for compatability reasons only
//8-bit period
void tmr1_init(unsigned char prescaler, unsigned char period) {
	TR1=0;								//turn off the timer
	_tmr1_isr_ptr=tmr1_empty_ptr;		//point isr to the empty handler
	TMOD = (TMOD & 0x0f) | 0x20;		//tmr0 in mode 2: 16 bit tmr, auto reload TH0
	_tmr1_period=-period;
	TH1=_tmr1_period;					//set the autoreload period
	TL1=_0;								//reset the timer / counter
	ET1=1;								//enable tmr0 interrupt
	TR1=1;								//turn on the timer
}
#endif

//set up the isr handler
void tmr1_act(void (*isr_ptr)(void)) {	//set up the isr pointer
	_tmr1_isr_ptr=isr_ptr;
}
