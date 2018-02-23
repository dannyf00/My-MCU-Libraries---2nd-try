#include <htc.h>					//we use htc compiler
#include "gpio.h"
#include "rtc2.h"					//we use tmr2

void (*_tmr2_isr_ptr)(void);			//tmr2 isr handler pointer
//unsigned char tmr2_offset=0xff;
unsigned long _rtc2_count;				//tmr2 isr counter
unsigned long _rtc2_trigger;			//tmr2's period
volatile RTC_TIME _rtc2;			//rtc2's timekeep

void _rtc2_empty_handler(void) {	//empty handler
}

//initialize the timer1 (8bit)
void rtc2_init(unsigned long period) {
	unsigned char scaler=TMR2_PS_16x | TMR2_MLT_16x;
	TMR2ON = 0;							//turn off tmr2
	_tmr2_isr_ptr=_rtc2_empty_handler;	//point to default handler
	_rtc2_count=0;						//reset isr count
	_rtc2_trigger=period;
	//TMR2CS = 0;						//use internal clock = Fosc / 4
	TMR2 = 0;							//reset tmr2
	PR2=0xff;							//update tmr2_period: PR2 is auto reloaded
	//TMR2ON = 1;							//turn on tmr2
	//T2CON = (T2CON & ~0x02) | (prescaler & 0x02);	//set the prescaler
	//T2CON = (T2CON & ~0xf8) | ((postscaler & 0xf0)>>1);	//set the postscaler
	T2CON = (scaler & 0x03) | 			//set the prescaler - not working?
			((scaler & 0xf0) >> 1) | 	//set the postscaler
			(1<<2);						//turn on the timer
	TMR2IE=1;							//tmr2 interrupt on
	PEIE=1;								//peripheral interrupt on
}

//activate the isr handler
void rtc2_act(void (*isr_ptr)(void)) {
	_tmr2_isr_ptr=isr_ptr;			//activate the isr handler
}

//update rtc2
//update rtc2
void rtc2_update(void) {
	_rtc2_count+=0x10000ul;					//increment rtc2 (8bit timer+256xpre/post scaler)
	if (_rtc2_count>_rtc2_trigger) {
		_rtc2_count-=_rtc2_trigger;			//date rtc2_count
		_rtc2.half_sec+=1;					//increment half_sec indicator
		if (_rtc2.half_sec==2) {				//overflown?
			_rtc2.half_sec=0;				//reset rtc2.half_sec
			_rtc2.sec+=1;					//increment sec
			if (_rtc2.sec==60) {				//overflown?
				_rtc2.sec=0;					//reset rtc2.sec
				_rtc2.min+=1;				//increment min
				if (_rtc2.min==60) {			//overflown?
					_rtc2.min=0;				//reset min
					_rtc2.hour+=1;			//increment hour
					if (_rtc2.hour==24) {	//overlown?
						_rtc2.hour=0;		//reset hour
						_rtc2.day+=1;		//increment day
					}
				}
			}
		}
	}
}

