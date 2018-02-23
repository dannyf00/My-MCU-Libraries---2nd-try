//#include <p24fxxxx.h>					//we use htc compiler
//#include "gpio.h"
#include "rtc3.h"						//we use tmr

#define RTC_PERIOD			RTC_1ms		//rtc resolutoin

//global variables
static void (* _tmr3_isr_ptr)(void);			//tmr_ptr pointing to empty_handler by default
unsigned long _rtc3_count=0;			//tmr isr counter
unsigned long _rtc3_period=RTC_10ms;	//tmr's period
volatile RTC_TIME _rtc3;			//rtc3's timekeep

//empty handler
static void _rtc3_empty_handler(void) {
	//default tmr handler
}

void _ISR _T3Interrupt(void) {
	_T3IF=0;							//clear tmr3 interrupt flag
	_rtc3_count+=RTC_PERIOD;			//advance counter
	if (_rtc3_count>=_rtc3_period) {	//overflown?
		_rtc3_count-=_rtc3_period;		//reset the counter
		rtc3_update();				//rpdate rtc3
		_tmr3_isr_ptr();				//execute user tmr3 isr
	}
}

//initialize the timer1 (16bit)
void rtc3_init(unsigned long period) {
	_T3MD = 0;					//enable power to tmr
	_T3ON = 0;							//turn off rtc3
	_tmr3_isr_ptr=_rtc3_empty_handler;	//point to default handler
	_rtc3_count=0;						//reset tmr isr counter
	_rtc3_period=period;				//reset _rtc_trigger
	PR3=RTC_PERIOD;						//minimum rtc resolution is 1ms
	_T3CS = 0;							//use internal clock = Fosc / 4
	//_T3_32 = 0;							//clock as two 16-bit timer/counter
	//T1CON = (T1CON & 0xcf) | ((TMR1_PS_1x & 0x03) << 4);	//set the prescaler
	_T3CKPS=TMR_PS_1x;					//set prescaler to 1:1
	_T3GE = 0;							//rtc3 gate disabled
	_T3IF = 0;							//reset the flag
	_T3IE=1;							//rtc3 interrupt on
	//PEIE=1;							//peripheral interrupt on. no PEIE for PIC24 mcus
	TMR3 = 0;							//reset the timer/counter
	//TMR1L = 0;
	_T3ON = 1;							//turn on rtc
}

//activate the isr handler
void rtc3_act(void (*isr_ptr)(void)) {
	_tmr3_isr_ptr=isr_ptr;			//activate the isr handler
}

//update rtc3
void rtc3_update(void) {
	_rtc3.half_sec+=1;					//increment half_sec indicator
	if (_rtc3.half_sec==2) {				//overflown?
		_rtc3.half_sec=0;				//reset rtc0.half_sec
		_rtc3.sec+=1;					//increment sec
		if (_rtc3.sec==60) {				//overflown?
			_rtc3.sec=0;					//reset rtc0.sec
			_rtc3.min+=1;				//increment min
			if (_rtc3.min==60) {			//overflown?
				_rtc3.min=0;				//reset min
				_rtc3.hour+=1;			//increment hour
				if (_rtc3.hour==24) {	//overlown?
					_rtc3.hour=0;		//reset hour
					_rtc3.day+=1;		//increment day
				}
			}
		}
	}
}

