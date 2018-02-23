#include <regx51.h>						//we use keil c51
#include "gpio.h"
#include "rtc1.h"						//we use tmr1 for rtc

//use black roman's zero cumulative error approach
//this approach will generate an output pulse whose long-term accuracy depends only on the crystal/clock source
//however, it does generate jitter between clocks: the longer the periods, the bigger the jitter
//as such, it is desirable in those applications that require long-term accuracy

void (*_rtc1_isr_ptr)(void);			//function ptr
unsigned long _rtc1_trigger=RTC_1000ms;	//rtc trigger
unsigned long _rtc1_count=0;			//rtc count: count up to rtc1_trigger
volatile RTC_TIME _rtc1 ={				//global time keeper for tc1
	0, 58, 59, 23, 0};

//rtc1 error term
//use a positive number if rtc runs too slow;
//use a negative number if rtc runs too fast

void _rtc1_isr(void) interrupt TF1_VECTOR {
	//clear the flag					//automatically done by hardware
	_rtc1_count+= 0x10000ul+RTC1_ERROR;	//tmr0 in 16 bit mode
	if (_rtc1_count < _rtc1_trigger) return;	//life goes on
	else {
		_rtc1_count-=_rtc1_trigger;		//reset _rtc1_count;
		rtc1_update();					//update rtc1
		_rtc1_isr_ptr();				//call the handler
	}
}

void rtc1_empty_ptr(void) {				//empty ptr
}

//initialize the timer
//prescaler not used - for compatability reasons only
//8-bit period
void rtc1_init(unsigned long trigger) {
	TR1=0;								//turn off the timer
	_rtc1_isr_ptr=rtc1_empty_ptr;		//point isr to the empty handler
	_rtc1_count=0;						//reset rtc_count
	_rtc1_trigger = trigger;			//assign the trigger
	TMOD = (TMOD & 0x0f) | 0x10;		//rtc1 in mode 1: 16 bit tmr
	TH1=0;								//set the autoreload period
	TL1=0;								//reset the timer / counter
	ET1=1;								//enable rtc1 interrupt
	TR1=1;								//turn on the timer
}

//set up the isr handler
void rtc1_act(void (*isr_ptr)(void)) {	//set up the isr pointer
	_rtc1_isr_ptr=isr_ptr;
}

void rtc1_update(void) {
	rtc1.half_sec+=1;					//increment half_sec indicator
	if (rtc1.half_sec==2) {				//overflown?
		rtc1.half_sec=0;				//reset rtc1.half_sec
		rtc1.sec+=1;					//increment sec
		if (rtc1.sec==60) {				//overflown?
			rtc1.sec=0;					//reset rtc1.sec
			rtc1.min+=1;				//increment min
			if (rtc1.min==60) {			//overflown?
				rtc1.min=0;				//reset min
				rtc1.hour+=1;			//increment hour
				if (rtc1.hour==24) {	//overlown?
					rtc1.hour=0;		//reset hour
					rtc1.day+=1;		//increment day
				}
			}
		}
	}
}

