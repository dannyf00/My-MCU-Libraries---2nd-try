#include <avr/io.h>							//avr gcc
#include <avr/interrupt.h>					//we use interrupt
#include "gpio.h"
#include "tmr0.h"							//tmr0 header file

//empty handler
static void /*_tmr0_*/empty_handler(void) {
	//default tmr handler
}

//uses roman black's zero cumulative error approach
static void (* /*_tmr0*/_isr_ptr)(void)=empty_handler;				//tmr0_ptr pointing to empty_handler by default

//tmr0 isr
ISR(TIMER0_OVF_vect) {
		/*_tmr0*/_isr_ptr();					//execute the handler
}

//reset the tmr
void tmr0_init(unsigned char ps, unsigned char period) {
	TCCR0B =	TCCR0B & (~0x07);			//turn off tmr0
	/*_tmr0*/_isr_ptr=/*_tmr0_*/empty_handler;		//reset isr ptr
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
				(ps & TMR_PS_MASK)		//prescaler = 1:1, per the header file
				;
	OCR1A = period;						//minimum time interval is 1ms
	TCNT0 = 0;								//reset the timer / counter
	TIMSK0 =	//(0<<ICIE1) |				//input capture isr: disabled
				//(0<<OCIE1C) |				//output compare isr for ch a: disabled
				(0<<OCIE0B) |				//output compare isr for ch b: disabled
				(0<<OCIE0A) |				//output compare isr for ch c: disabled
				(1<<TOIE0)					//tmr overflow interrupt: enabled
				;
}

void tmr0_act(void (*isr_ptr)(void)) {
	/*_tmr0*/_isr_ptr=isr_ptr;					//reassign tmr0 isr ptr
}
