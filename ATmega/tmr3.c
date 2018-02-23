#include <avr/io.h>							//avr gcc
#include <avr/interrupt.h>					//we use interrupt
#include "gpio.h"
#include "tmr3.h"							//tmr3 header file

//empty handler
static void /*_tmr3_*/empty_handler(void) {
	//default tmr handler
}

static void (* /*_tmr3*/_isr_ptr)(void)=empty_handler;	//tmr3_ptr pointing to empty_handler by default

//tmr3 isr
ISR(TIMER3_COMPA_vect) {
	/*_tmr3*/_isr_ptr();						//execute the handler
}

//reset the tmr
void tmr3_init(unsigned char prescaler, unsigned short period) {
	TCCR3B =	TCCR3B & (~0x07);			//turn off tmr3
	/*_tmr3*/_isr_ptr=/*_tmr3_*/empty_handler;			//reset isr ptr
	TCCR3A =	(0<<COM3A1) | (0<<COM3A0) |	//output compare a pins normal operation
				(0<<COM3B1) | (0<<COM3B0) |		//output compare b pins normal operation
				(0<<COM3C1) | (0<<COM3C0) |	//output compare c pins normal operation
				(0<<WGM31) | (0<<WGM30)		//wgm33..0 = 0b0100 -> ctc, top at ocr3a
				;
	TCCR3B =	(0<<ICNC3) |				//nput capture noise canceller disabled
				(0<<ICES3) |			//input capture edge selection on falling edge
				(0<<WGM33) | (1<<WGM32) |	//wgm13..0 = 0b0100 -> ctc, top at ocr1a
				(prescaler & TMR_PS_MASK)	//prescaler, per the header file
				;
	TCCR3C =	(0<<FOC3A) |				//forced output on ch a disabled
				(0<<FOC3B) |				//forced output on ch b disabled
				(0<<FOC3C)					//forced output on ch c disabled
				;
	OCR3A = period;
	TCNT3 = 0;								//reset the timer / counter
	TIMSK3 =	(0<<ICIE3) |				//input capture isr: disabled
				(0<<OCIE3C) |				//output compare isr for ch a: disabled
				(0<<OCIE3B) |				//output compare isr for ch b: disabled
				(1<<OCIE3A) |				//output compare isr for ch c: disabled
				(0<<TOIE3)					//tmr overflow interrupt: enabled
				;
}

void tmr3_act(void (*isr_ptr)(void)) {
	/*_tmr3*/_isr_ptr=isr_ptr;					//reassign tmr3 isr ptr
}

