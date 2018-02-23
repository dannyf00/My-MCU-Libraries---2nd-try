#include <htc.h>					//we use htc compiler
#include "gpio.h"
#include "rtc1.h"					//we use tmr1

//global variables
void (*_tmr1_isr_ptr)(void);			//tmr1 isr handler pointer
unsigned long _rtc1_count=0;			//tmr1 isr counter
unsigned long _rtc1_trigger=RTC_1000ms;	//tmr1's period
volatile RTC_TIME _rtc1;			//rtc1's time keep

void _rtc1_empty_handler(void) {	//empty handler
}

//initialize the timer1 (16bit)
void rtc1_init(unsigned long period) {
	TMR1ON = 0;							//turn off rtc1
	_tmr1_isr_ptr=_rtc1_empty_handler;	//point to default handler
	_rtc1_count=0;						//reset tmr1 isr counter
	_rtc1_trigger=period;				//reset _rtc1_trigger
	TMR1CS = 0;							//use internal clock = Fosc / 4
	T1CON = (T1CON & 0xcf) | ((TMR1_PS_1x & 0x03) << 4);	//set the prescaler
	TMR1GE = 0;							//rtc1 gate disabled
	TMR1IE=1;							//rtc1 interrupt on
	PEIE=1;								//peripheral interrupt on
	TMR1H = 0;							//reset the timer/counter
	TMR1L = 0;
	TMR1ON = 1;							//turn on rtc1
}

//activate the isr handler
void rtc1_act(void (*isr_ptr)(void)) {
	_tmr1_isr_ptr=isr_ptr;			//activate the isr handler
}

//update rtc1
void rtc1_update(void) {
	_rtc1_count+=0x10000ul;					//increment rtc1_count
	if (_rtc1_count>=_rtc1_trigger) {
		_rtc1_count-=_rtc1_trigger;
		_rtc1.half_sec+=1;					//increment half_sec indicator
		if (_rtc1.half_sec==2) {				//overflown?
			_rtc1.half_sec=0;				//reset rtc1.half_sec
			_rtc1.sec+=1;					//increment sec
			if (_rtc1.sec==60) {				//overflown?
				_rtc1.sec=0;					//reset rtc1.sec
				_rtc1.min+=1;				//increment min
				if (_rtc1.min==60) {			//overflown?
					_rtc1.min=0;				//reset min
					_rtc1.hour+=1;			//increment hour
					if (_rtc1.hour==24) {	//overlown?
						_rtc1.hour=0;		//reset hour
						_rtc1.day+=1;		//increment day
					}
				}
			}
		}
	}
}

