#include <regx51.h>						//we use keil c51
#include "gpio.h"
#include "tmr0_16.h"					//we use tmr0, 16-bit mode

#define T0_error		35				//T0's error term

void (*_tmr0_isr_ptr)(void);			//function ptr
unsigned short _tmr0_offset=0x0000;		//tmr0's offset

void _tmr0_isr(void) interrupt TF0_VECTOR {
	unsigned short T0=(TH0<<8)|TL0;
	//clear the flag					//automatically done by hardware
	T0+=_tmr0_offset+T0_error;			//advance T0
	TH0= T0 >> 8;			//update the offset
	TL0= T0 & 0x00ff;
	_tmr0_isr_ptr();					//call the handler
}

void tmr0_empty_ptr(void) {				//empty ptr
}

//initialize the timer
//prescaler not used - for compatability reasons only
//16-bit period
void tmr0_init(unsigned char prescaler, unsigned short period) {
	TR0=0;								//turn off the timer
	_tmr0_isr_ptr=tmr0_empty_ptr;		//point isr to the empty handler
	TMOD = (TMOD & 0xf0) | 0x01;		//tmr0 in mode 1: 16 bit tmr, with no auto reload
	_tmr0_offset = -period;				//update offset
	TH0 = _tmr0_offset >> 8;			//set the autoreload period
	TL0 = _tmr0_offset & 0x00ff;		//reset the timer / counter
	ET0=1;								//enable tmr0 interrupt
	TR0=1;								//turn on the timer
}

//set up the isr handler
void tmr0_act(void (*isr_ptr)(void)) {	//set up the isr pointer
	_tmr0_isr_ptr=isr_ptr;
}
