#include <htc.h>					//we use htc compiler
#include "gpio.h"
#include "rtc0.h"					//we use rtc0

//use roman black approach to generate accurate long-term timing

//global variables
void (*_tmr0_isr_ptr)(void);			//rtc0 isr handler pointer
unsigned long _rtc0_count=0;			//reset isr count
unsigned long _rtc0_trigger=RTC_1000ms;	//rtc defaults to 1 cal per 1000ms
volatile RTC_TIME _rtc0;			//rtc0's time keep

void _tmr0_empty_handler(void) {	//empty handler
}

//initialize the timer
void rtc0_init(unsigned long period) {
	_tmr0_isr_ptr=_tmr0_empty_handler;	//point to default handler
	_rtc0_count=0;						//reset isr count
	_rtc0_trigger=period;				//establish period
	T0CS = 0;							//use internal clock = Fosc / 4
	PSA = 1;							//prescaler assigned to wdt
	//OPTION = (OPTION & ~0x07) | (RTC0_PS & 0x07);	//set prescaler - option's last three bits
	//PS2=0, PS1=0, PS0=0;				//no prescaler
	TMR0 = 0;							//reset counter
	T0IE = 1;							//turn on rtc0 interrupt
}

//activate the isr handler
void rtc0_act(void (*isr_ptr)(void)) {
	_tmr0_isr_ptr=isr_ptr;				//activate the isr handler
}


//update rtc0 - called in the isr
void rtc0_update(void) {
	_rtc0_count+=0x100ul;					//increment rtc0 (8bit tmr)
	if (_rtc0_count>=_rtc0_trigger) {	//overflown?
		_rtc0_count-=_rtc0_trigger;
		_rtc0.half_sec+=1;					//increment half_sec indicator
		if (_rtc0.half_sec==2) {			//overflown?
			_rtc0.half_sec=0;				//reset rtc0.half_sec
			_rtc0.sec+=1;					//increment sec
			if (_rtc0.sec==60) {			//overflown?
				_rtc0.sec=0;				//reset rtc0.sec
				_rtc0.min+=1;				//increment min
				if (_rtc0.min==60) {		//overflown?
					_rtc0.min=0;			//reset min
					_rtc0.hour+=1;			//increment hour
					if (_rtc0.hour==24) {	//overlown?
						_rtc0.hour=0;		//reset hour
						_rtc0.day+=1;		//increment day
					}
				}
			}
		}
	}
}

