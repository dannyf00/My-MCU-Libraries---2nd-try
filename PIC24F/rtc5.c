//#include <p24fxxxx.h>					//we use htc compiler
#include "rtc5.h"						//we use tmr

#define RTC_PERIOD			RTC_1ms		//rtc resolutoin

//global variables
static void (* _tmr5_isr_ptr)(void);			//tmr_ptr pointing to empty_handler by default
unsigned long _rtc5_count=0;			//tmr isr counter
unsigned long _rtc5_period=RTC_10ms;	//tmr's period
volatile RTC_TIME _rtc5;			//rtc5's time keep

//empty handler
static void _rtc5_empty_handler(void) {
	//default tmr handler
}

void _ISR _T5Interrupt(void) {
	_T5IF=0;							//clear tmr3 interrupt flag
	_rtc5_count+=RTC_PERIOD;			//advance counter
	if (_rtc5_count>=_rtc5_period) {	//overflown?
		_rtc5_count-=_rtc5_period;		//reset the counter
		rtc5_update();				//update rtc5
		_tmr5_isr_ptr();				//execute user tmr3 isr
	}
}

//initialize the timer1 (16bit)
void rtc5_init(unsigned long period) {
	_T5MD = 0;					//enable power to tmr
	_T5ON = 0;							//turn off rtc5
	_tmr5_isr_ptr=_rtc5_empty_handler;	//point to default handler
	_rtc5_count=0;						//reset tmr isr counter
	_rtc5_period=period;				//reset _rtc_trigger
	PR5=RTC_PERIOD;						//minimum rtc resolution is 1ms
	_T5CS = 0;							//use internal clock = Fosc / 4
	//_T32 = 0;							//clock as two 16-bit timer/counter
	//T1CON = (T1CON & 0xcf) | ((TMR1_PS_1x & 0x03) << 4);	//set the prescaler
	_T5CKPS=TMR_PS_1x;					//set prescaler to 1:1
	_T5GE = 0;							//rtc5 gate disabled
	_T5IF = 0;							//reset the flag
	_T5IE=1;							//rtc5 interrupt on
	//PEIE=1;							//peripheral interrupt on. no PEIE for PIC24 mcus
	TMR5 = 0;							//reset the timer/counter
	//TMR1L = 0;
	_T5ON = 1;							//turn on rtc
}

//activate the isr handler
void rtc5_act(void (*isr_ptr)(void)) {
	_tmr5_isr_ptr=isr_ptr;			//activate the isr handler
}

//update rtc5
void rtc5_update(void) {
	_rtc5.half_sec+=1;					//increment half_sec indicator
	if (_rtc5.half_sec==2) {				//overflown?
		_rtc5.half_sec=0;				//reset rtc0.half_sec
		_rtc5.sec+=1;					//increment sec
		if (_rtc5.sec==60) {				//overflown?
			_rtc5.sec=0;					//reset rtc0.sec
			_rtc5.min+=1;				//increment min
			if (_rtc5.min==60) {			//overflown?
				_rtc5.min=0;				//reset min
				_rtc5.hour+=1;			//increment hour
				if (_rtc5.hour==24) {	//overlown?
					_rtc5.hour=0;		//reset hour
					_rtc5.day+=1;		//increment day
				}
			}
		}
	}
}

