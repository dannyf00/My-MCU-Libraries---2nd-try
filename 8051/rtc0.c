#include <regx51.h>						//we use keil c51
//#include "gpio.h"
#include "rtc0.h"						//we use tmr0 for rtc

//use black roman's zero cumulative error approach
//this approach will generate an output pulse whose long-term accuracy depends only on the crystal/clock source
//however, it does generate jitter between clocks: the longer the periods, the bigger the jitter
//as such, it is desirable in those applications that require long-term accuracy

//rtc0 error term
//use a positive number if rtc runs too slow;
//use a negative number if rtc runs too fast

//global variable
void (*_rtc0_isr_ptr)(void);			//function ptr
unsigned long _rtc0_trigger=RTC_1000ms;	//rtc trigger, default to 1s
unsigned long _rtc0_count=0;			//rtc count: count up to rtc0_trigger
volatile RTC_TIME _rtc0 ={				//global time keeper for tc0
	0, 58, 59, 23, 0};

void _rtc0_isr(void) interrupt TF0_VECTOR {
	//clear the flag					//automatically done by hardware
	_rtc0_count+= 0x10000ul+RTC0_ERROR;	//tmr0 in 16 bit mode
	if (_rtc0_count < _rtc0_trigger) return;	//life goes on
	else {
		_rtc0_count-=_rtc0_trigger;		//reset _rtc0_count;
		rtc0_update();					//update rtc0
		_rtc0_isr_ptr();				//call the handler
	}
}

void rtc0_empty_ptr(void) {				//empty ptr
}

//initialize the timer
//prescaler not used - for compatability reasons only
//8-bit period
void rtc0_init(unsigned long trigger) {
	TR0=0;								//turn off the timer
	_rtc0_isr_ptr=rtc0_empty_ptr;		//point isr to the empty handler
	_rtc0_count=0;						//reset rtc_count
	_rtc0_trigger = trigger;			//assign the trigger
	TMOD = (TMOD & 0xf0) | 0x01;		//rtc0 in mode 1: 16 bit tmr
	TH0=0;								//set the autoreload period
	TL0=0;								//reset the timer / counter
	ET0=1;								//enable rtc0 interrupt
	TR0=1;								//turn on the timer
}

//set up the isr handler
void rtc0_act(void (*isr_ptr)(void)) {	//set up the isr pointer
	_rtc0_isr_ptr=isr_ptr;
}

void rtc0_update(void) {
	rtc0.half_sec+=1;					//increment half_sec indicator
	if (rtc0.half_sec==2) {				//overflown?
		rtc0.half_sec=0;				//reset rtc0.half_sec
		rtc0.sec+=1;					//increment sec
		if (rtc0.sec==60) {				//overflown?
			rtc0.sec=0;					//reset rtc0.sec
			rtc0.min+=1;				//increment min
			if (rtc0.min==60) {			//overflown?
				rtc0.min=0;				//reset min
				rtc0.hour+=1;			//increment hour
				if (rtc0.hour==24) {	//overlown?
					rtc0.hour=0;		//reset hour
					rtc0.day+=1;		//increment day
				}
			}
		}
	}
}

