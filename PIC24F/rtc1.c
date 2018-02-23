//#include <p24fxxxx.h>					//we use htc compiler
//#include "gpio.h"
#include "rtc1.h"						//we use tmr1

#define RTC_PERIOD			RTC_1ms		//rtc resolutoin

//global variables
static void (* _tmr1_isr_ptr)(void);				//tmr1_ptr pointing to empty_handler by default
unsigned long _rtc1_count=0;			//tmr1 isr counter
unsigned long _rtc1_period=RTC_10ms;	//tmr1's period
volatile RTC_TIME _rtc1;				//tmr1's timekeep

//empty handler
static void _rtc1_empty_handler(void) {
	//default tmr handler
}

void _ISR _T1Interrupt(void) {
	_T1IF=0;							//clear tmr1 interrupt flag
	_rtc1_count+=RTC_PERIOD;			//advance counter
	if (_rtc1_count>=_rtc1_period) {	//overflown?
		_rtc1_count-=_rtc1_period;		//reset the counter
		rtc1_update();					//update rtc1
		_tmr1_isr_ptr();				//execute user tmr1 isr
	}
}

//initialize the timer1 (16bit)
void rtc1_init(unsigned long period) {
	_T1MD = 0;					//enable power to tmr
	_T1ON = 0;							//turn off rtc1
	_tmr1_isr_ptr=_rtc1_empty_handler;	//point to default handler
	_rtc1_count=0;						//reset tmr1 isr counter
	_rtc1_period=period;				//reset _rtc1_trigger
	PR1=RTC_1ms;						//minimum rtc resolution is 1ms
	_T1CS = 0;							//use internal clock = Fosc / 4
	//T1CON = (T1CON & 0xcf) | ((TMR1_PS_1x & 0x03) << 4);	//set the prescaler
	_T1CKPS=TMR_PS_1x;			//set prescaler to 1:1
	_T1GE = 0;							//rtc1 gate disabled
	_T1IF = 0;							//reset the flag
	_T1IE=1;							//rtc1 interrupt on
	//PEIE=1;								//peripheral interrupt on. no PEIE for PIC24 mcus
	TMR1 = 0;							//reset the timer/counter
	//TMR1L = 0;
	_T1ON = 1;							//turn on rtc1
}

//activate the isr handler
void rtc1_act(void (*isr_ptr)(void)) {
	_tmr1_isr_ptr=isr_ptr;			//activate the isr handler
}

//update rtc1
void rtc1_update(void) {
	_rtc1.half_sec+=1;					//increment half_sec indicator
	if (_rtc1.half_sec==2) {				//overflown?
		_rtc1.half_sec=0;				//reset rtc0.half_sec
		_rtc1.sec+=1;					//increment sec
		if (_rtc1.sec==60) {				//overflown?
			_rtc1.sec=0;					//reset rtc0.sec
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

