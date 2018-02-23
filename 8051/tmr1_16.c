#include <regx51.h>						//we use keil c51
#include "gpio.h"
#include "tmr1_16.h"					//we use tmr1, 16-bit

#define T1_error		35				//error term due to timing

void (*_tmr1_isr_ptr)(void);			//function ptr
unsigned short _tmr1_offset=0x0000;		//tmr1's offset

void _tmr1_isr(void) interrupt TF1_VECTOR {
	unsigned short T1=(TH1<<8)|TL1;
	//clear the flag					//automatically done by hardware
	T1+=_tmr1_offset+T1_error;			//advance the offset
	TH1=T1>>8;
	TL1=T1&0x00ff;
	_tmr1_isr_ptr();					//call the handler
}

void tmr1_empty_ptr(void) {				//empty ptr
}

//initialize the timer
//prescaler not used - for compatability reasons only
//16-bit period
void tmr1_init(unsigned char prescaler, unsigned short period) {
	TR1=0;								//turn off the timer
	_tmr1_isr_ptr=tmr1_empty_ptr;		//point isr to the empty handler
	TMOD = (TMOD & 0x0f) | 0x10;		//tmr1 in mode 1: 16 bit tmr, no auto reloading
	_tmr1_offset=-period;				//update _tmr1_offset
	TH1 = _tmr1_offset >> 8;			//set the offset
	TL1 = _tmr1_offset & 0x00ff;
	ET1=1;								//enable tmr1 interrupt
	TR1=1;								//turn on the timer
}

//set up the isr handler
void tmr1_act(void (*isr_ptr)(void)) {	//set up the isr pointer
	_tmr1_isr_ptr=isr_ptr;
}
