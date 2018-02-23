#include <avr/io.h>							//avr gcc
#include <avr/interrupt.h>					//we use interrupt
#include "gpio.h"
#include "rtc3.h"							//tmr1 header file

//uses roman black's zero cumulative error approach
void (* _tmr3_isr_ptr)(void);				//tmr1_ptr pointing to empty_handler by default
unsigned long _rtc3_period=RTC_1ms;			//default rtc period is 1ms
volatile RTC_TIME _rtc3;				//rtc3's time

//empty handler
void _tmr3_empty_handler(void) {
	//default tmr handler
}

//tmr1 isr
ISR(TIMER3_COMPA_vect) {
	static unsigned long _rtc_count=0;		//isr count
	_rtc_count+=RTC_1ms+1;					//increment isr_count
	if (_rtc_count >= _rtc3_period) {			//overflown?
		_rtc_count -= _rtc3_period;			//reset _rtc_count
		rtc3_update();					//update rtc3
		_tmr3_isr_ptr();						//execute the handler
	}
}

//reset the tmr
void rtc3_init(unsigned long period) {
	TCCR3B =	TCCR3B & (~0x07);			//turn off tmr1
	_tmr3_isr_ptr=_tmr3_empty_handler;			//reset isr ptr
	_rtc3_period = period;					//reset rtc_period
	TCCR3A =	(0<<COM3A1) | (0<<COM3A0) |	//output compare a pins normal operation
				(0<<COM3B1) | (0<<COM3B0) |	//output compare b pins normal operation
				(0<<COM3C1) | (0<<COM3C0) |	//output compare c pins normal operation
				(0<<WGM31) | (0<<WGM30)		//wgm13..0 = 0b0100 -> ctc, top at ocr1a
				;
	TCCR3B =	(0<<ICNC3) |				//nput capture noise canceller disabled
				(0<<ICES3) |				//input capture edge selection on falling edge
				(0<<WGM33) | (1<<WGM32) |	//wgm13..0 = 0b0100 -> ctc, top at ocr1a
				(TMR_PS_1x & TMR_PS_MASK)		//prescaler, per the header file
				;
	TCCR3C =	(0<<FOC3A) |				//forced output on ch a disabled
				(0<<FOC3B) |				//forced output on ch b disabled
				(0<<FOC3C)					//forced output on ch c disabled
				;
	OCR3A = RTC_1ms;						//minimum time interval is 1ms
	TCNT3 = 0;								//reset the timer / counter
	TIMSK3 =	(0<<ICIE3) |				//input capture isr: disabled
				(0<<OCIE3C) |				//output compare isr for ch a: disabled
				(0<<OCIE3B) |				//output compare isr for ch b: disabled
				(1<<OCIE3A) |				//output compare isr for ch c: disabled
				(0<<TOIE3)					//tmr overflow interrupt: enabled
				;
}

void rtc3_act(void (*isr_ptr)(void)) {
	_tmr3_isr_ptr=isr_ptr;					//reassign tmr1 isr ptr
}

void rtc3_update(void) {
	_rtc3.half_sec+=1;					//increment half_sec
	if (_rtc3.half_sec==2) {				//overflown
		_rtc3.half_sec=0;				//reset half_sec
		_rtc3.sec+=1;					//increment sec
		if (_rtc3.sec==60) {				//sec overflown?
			_rtc3.sec=0;				//reset sec
			_rtc3.min+=1;				//increment min
			if (_rtc3.min==60) {			//min overflown?
				_rtc3.min=0;			//reset min
				_rtc3.hour+=1;			//increment hour
				if (_rtc3.hour==24) {		//hour overflown?
					_rtc3.hour=0;		//reset hour
					_rtc3.day+=1;		//increment day
				}
			}
		}
	}
}
