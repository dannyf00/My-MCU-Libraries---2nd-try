//#include <p24fxxxx.h>					//we use htc compiler
//#include "gpio.h"
#include "rtc2.h"						//we use tmr1

#define RTC_PERIOD			RTC_1ms		//rtc resolutoin

static void (* _tmr2_isr_ptr)(void);				//tmr1_ptr pointing to empty_handler by default
unsigned long _rtc2_count=0;			//tmr isr counter
unsigned long _rtc2_period=RTC_10ms;	//tmr1's period
volatile RTC_TIME _rtc2;			//rtc2's timekeep

//empty handler
static void _rtc2_empty_handler(void) {
	//default tmr handler
}

void _ISR _T2Interrupt(void) {
	_T2IF=0;							//clear tmr1 interrupt flag
	_rtc2_count+=RTC_PERIOD;			//advance counter
	if (_rtc2_count>=_rtc2_period) {	//overflown?
		_rtc2_count-=_rtc2_period;		//reset the counter
		rtc2_update();				//update rtc2
		_tmr2_isr_ptr();				//execute user tmr2 isr
	}
}

//initialize the timer1 (16bit)
void rtc2_init(unsigned long period) {
	_T2MD = 0;					//enable power to tmr
	_T2ON = 0;							//turn off rtc2
	_tmr2_isr_ptr=_rtc2_empty_handler;	//point to default handler
	_rtc2_count=0;						//reset tmr1 isr counter
	_rtc2_period=period;				//reset _rtc2_trigger
	PR2=RTC_PERIOD;						//minimum rtc resolution is 1ms
	_T2CS = 0;							//use internal clock = Fosc / 4
	_T2_32 = 0;							//clock as two 16-bit timer/counter
	//T1CON = (T1CON & 0xcf) | ((TMR1_PS_1x & 0x03) << 4);	//set the prescaler
	_T2CKPS=TMR_PS_1x;			//set prescaler to 1:1
	_T2GE = 0;							//rtc2 gate disabled
	_T2IF = 0;							//reset the flag
	_T2IE=1;							//rtc2 interrupt on
	//PEIE=1;								//peripheral interrupt on. no PEIE for PIC24 mcus
	TMR2 = 0;							//reset the timer/counter
	//TMR1L = 0;
	_T2ON = 1;							//turn on rtc2
}

//activate the isr handler
void rtc2_act(void (*isr_ptr)(void)) {
	_tmr2_isr_ptr=isr_ptr;			//activate the isr handler
}

//update rtc2
void rtc2_update(void) {
	_rtc2.half_sec+=1;					//increment half_sec indicator
	if (_rtc2.half_sec==2) {				//overflown?
		_rtc2.half_sec=0;				//reset rtc0.half_sec
		_rtc2.sec+=1;					//increment sec
		if (_rtc2.sec==60) {				//overflown?
			_rtc2.sec=0;					//reset rtc0.sec
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

