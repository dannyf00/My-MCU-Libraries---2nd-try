//#include <p24fxxxx.h>					//we use htc compiler
//#include "gpio.h"
#include "rtc4.h"						//we use tmr1

#define RTC_PERIOD			RTC_1ms		//rtc resolutoin

//global variables
static void (* _tmr4_isr_ptr)(void);				//tmr1_ptr pointing to empty_handler by default
unsigned long _rtc4_count=0;			//tmr1 isr counter
unsigned long _rtc4_period=RTC_10ms;	//tmr1's period
volatile RTC_TIME _rtc4;			//rtc4's timekeep

//empty handler
static void _rtc4_empty_handler(void) {
	//default tmr handler
}

void _ISR _T4Interrupt(void) {
	_T4IF=0;							//clear tmr1 interrupt flag
	_rtc4_count+=RTC_PERIOD;			//advance counter
	if (_rtc4_count>=_rtc4_period) {	//overflown?
		_rtc4_count-=_rtc4_period;		//reset the counter
		rtc4_update();				//update rtc4
		_tmr4_isr_ptr();				//execute user tmr1 isr
	}
}

//initialize the timer1 (16bit)
void rtc4_init(unsigned long period) {
	_T4MD = 0;					//enable power to tmr
	_T4ON = 0;							//turn off rtc4
	_tmr4_isr_ptr=_rtc4_empty_handler;	//point to default handler
	_rtc4_count=0;						//reset tmr1 isr counter
	_rtc4_period=period;				//reset _rtc4_trigger
	PR4=RTC_PERIOD;						//minimum rtc resolution is 1ms
	_T4CS = 0;							//use internal clock = Fosc / 4
	_T4_32 = 0;							//clock as two 16-bit timer/counter
	//T1CON = (T1CON & 0xcf) | ((TMR1_PS_1x & 0x03) << 4);	//set the prescaler
	_T4CKPS=TMR_PS_1x;			//set prescaler to 1:1
	_T4GE = 0;							//rtc4 gate disabled
	_T4IF = 0;							//reset the flag
	_T4IE=1;							//rtc4 interrupt on
	//PEIE=1;								//peripheral interrupt on. no PEIE for PIC24 mcus
	TMR4 = 0;							//reset the timer/counter
	//TMR1L = 0;
	_T4ON = 1;							//turn on rtc4
}

//activate the isr handler
void rtc4_act(void (*isr_ptr)(void)) {
	_tmr4_isr_ptr=isr_ptr;			//activate the isr handler
}

//update rtc4
void rtc4_update(void) {
	_rtc4.half_sec+=1;					//increment half_sec indicator
	if (_rtc4.half_sec==2) {				//overflown?
		_rtc4.half_sec=0;				//reset rtc0.half_sec
		_rtc4.sec+=1;					//increment sec
		if (_rtc4.sec==60) {				//overflown?
			_rtc4.sec=0;					//reset rtc0.sec
			_rtc4.min+=1;				//increment min
			if (_rtc4.min==60) {			//overflown?
				_rtc4.min=0;				//reset min
				_rtc4.hour+=1;			//increment hour
				if (_rtc4.hour==24) {	//overlown?
					_rtc4.hour=0;		//reset hour
					_rtc4.day+=1;		//increment day
				}
			}
		}
	}
}

