#include <avr/io.h>							//avr gcc
#include <avr/interrupt.h>					//we use interrupt
#include "gpio.h"
#include "rtc0.h"							//tmr0 header file

//uses roman black's zero cumulative error approach
void (* _tmr0_isr_ptr)(void);				//tmr0_ptr pointing to empty_handler by default
unsigned long _rtc0_period=RTC_1ms;			//default rtc period is 1ms
volatile RTC_TIME _rtc0;				//rtc0

//empty handler
void _tmr0_empty_handler(void) {
	//default tmr handler
}

//tmr0 isr
ISR(TIMER0_OVF_vect) {
	static unsigned long _rtc_count=0;		//isr count
	_rtc_count+=0x100;						//increment isr_count - tmr0 is an 8-bit timer
	if (_rtc_count >= _rtc0_period) {		//overflown?
		_rtc_count -= _rtc0_period;			//reset _rtc_count
		rtc0_update();					//update time in rtc0
		_tmr0_isr_ptr();					//execute the handler
	}
}

//reset the tmr
void rtc0_init(unsigned long period) {
	TCCR0B =	TCCR0B & (~0x07);			//turn off tmr0
	_tmr0_isr_ptr=_tmr0_empty_handler;		//reset isr ptr
	_rtc0_period = period;					//reset rtc_period
	TCCR0A =	(0<<COM0A1) | (0<<COM0A0) |	//output compare a pins normal operation
				(0<<COM0B1) | (0<<COM0B0) |	//output compare b pins normal operation
				//(0<<COM1C1) | (0<<COM1C0) |	//output compare c pins normal operation
				(0<<WGM01) | (0<<WGM00)		//wgm02..0 = 0b000 -> normal, overflow at 0xff->0x00
				;
	/*TCCR0B =	(0<<ICNC1) |				//nput capture noise canceller disabled
				(0<<ICES1) |				//input capture edge selection on falling edge
				(0<<WGM13) | (1<<WGM12) |	//wgm13..0 = 0b0100 -> ctc, top at ocr1a
				(TMR_PS_1x & TMR_PS_MASK)		//prescaler, per the header file
				;*/
	TCCR0B =	(0<<FOC0A) |				//forced output on ch a disabled
				(0<<FOC0B) |				//forced output on ch b disabled
				//(0<<FOC1C)					//forced output on ch c disabled
				(0<<WGM02) |				//wgm02..0 = 0b000 -> normal, overflow at 0xff->0x00
				(TMR_CS210_CLK & 0x07)		//prescaler = 1:1, per the header file
				;
	//OCR1A = RTC_1ms;						//minimum time interval is 1ms
	TCNT0 = 0;								//reset the timer / counter
	TIMSK0 =	//(0<<ICIE1) |				//input capture isr: disabled
				//(0<<OCIE1C) |				//output compare isr for ch a: disabled
				(0<<OCIE0B) |				//output compare isr for ch b: disabled
				(0<<OCIE0A) |				//output compare isr for ch c: disabled
				(1<<TOIE0)					//tmr overflow interrupt: enabled
				;
}

void rtc0_act(void (*isr_ptr)(void)) {
	_tmr0_isr_ptr=isr_ptr;					//reassign tmr0 isr ptr
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
