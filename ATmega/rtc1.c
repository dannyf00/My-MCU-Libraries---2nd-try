#include <avr/io.h>							//avr gcc
#include <avr/interrupt.h>					//we use interrupt
#include "gpio.h"
#include "rtc1.h"							//tmr1 header file

//uses roman black's zero cumulative error approach
void (* _tmr1_isr_ptr)(void);				//tmr1_ptr pointing to empty_handler by default
unsigned long _rtc1_period=RTC_1ms;			//default rtc period is 1ms
volatile RTC_TIME _rtc0;				//rtc0

//empty handler
void _tmr1_empty_handler(void) {
	//default tmr handler
}

//tmr1 isr
ISR(TIMER1_COMPA_vect) {
	static unsigned long _rtc_count=0;		//isr count
	_rtc_count+=RTC_1ms+1;					//increment isr_count: ctc overflows at when the counter passes OCRnA
	if (_rtc_count >= _rtc1_period) {			//overflown?
		_rtc_count -= _rtc1_period;			//reset _rtc_count
		rtc1_update();					//update time
		_tmr1_isr_ptr();						//execute the handler
	}
}

//reset the tmr
void rtc1_init(unsigned long period) {
	TCCR1B =	TCCR1B & (~0x07);			//turn off tmr1
	_tmr1_isr_ptr=_tmr1_empty_handler;			//reset isr ptr
	_rtc1_period = period;					//reset rtc_period
	TCCR1A =	(0<<COM1A1) | (0<<COM1A0) |	//output compare a pins normal operation
				(0<<COM1B1) | (0<<COM1B0) |	//output compare b pins normal operation
				(0<<COM1C1) | (0<<COM1C0) |	//output compare c pins normal operation
				(0<<WGM11) | (0<<WGM10)		//wgm13..0 = 0b0100 -> ctc, top at ocr1a
				;
	TCCR1B =	(0<<ICNC1) |				//nput capture noise canceller disabled
				(0<<ICES1) |				//input capture edge selection on falling edge
				(0<<WGM13) | (1<<WGM12) |	//wgm13..0 = 0b0100 -> ctc, top at ocr1a
				(TMR_PS_1x & TMR_PS_MASK)		//prescaler, per the header file
				;
	TCCR1C =	(0<<FOC1A) |				//forced output on ch a disabled
				(0<<FOC1B) |				//forced output on ch b disabled
				(0<<FOC1C)					//forced output on ch c disabled
				;
	OCR1A = RTC_1ms;						//minimum time interval is 1ms
	TCNT1 = 0;								//reset the timer / counter
	TIMSK1 =	(0<<ICIE1) |				//input capture isr: disabled
				(0<<OCIE1C) |				//output compare isr for ch a: disabled
				(0<<OCIE1B) |				//output compare isr for ch b: disabled
				(1<<OCIE1A) |				//output compare isr for ch c: disabled
				(0<<TOIE1)					//tmr overflow interrupt: enabled
				;
}

void rtc1_act(void (*isr_ptr)(void)) {
	_tmr1_isr_ptr=isr_ptr;					//reassign tmr1 isr ptr
}

void rtc0_update(void) {
	_rtc0.half_sec+=1;					//increment half_sec
	if (_rtc0.half_sec==2) {				//overflown
		_rtc0.half_sec=0;				//reset half_sec
		_rtc0.sec+=1;					//increment sec
		if (_rtc0.sec==60) {				//sec overflown?
			_rtc0.sec=0;				//reset sec
			_rtc0.min+=1;				//increment min
			if (_rtc0.min==60) {			//min overflown?
				_rtc0.min=0;			//reset min
				_rtc0.hour+=1;			//increment hour
				if (_rtc0.hour==24) {		//hour overflown?
					_rtc0.hour=0;		//reset hour
					_rtc0.day+=1;		//increment day
				}
			}
		}
	}
}
