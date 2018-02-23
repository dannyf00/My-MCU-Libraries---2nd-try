#include <avr/io.h>							//avr gcc
#include <avr/interrupt.h>					//we use interrupt
#include "gpio.h"
#include "tmr1.h"							//tmr1 header file

//empty handler
static void /*_tmr1_*/empty_handler(void) {
	//default tmr handler
}

static void (* /*_tmr1*/_isr_ptr)(void)=empty_handler;	//tmr1_ptr pointing to empty_handler by default

//tmr1 isr
ISR(TIMER1_COMPA_vect) {
	/*_tmr1*/_isr_ptr();						//execute the handler
}

//reset the tmr
void tmr1_init(unsigned char prescaler, unsigned short period) {
	TCCR1B =	TCCR1B & (~0x07);			//turn off tmr1
	/*_tmr1*/_isr_ptr=/*_tmr1_*/empty_handler;			//reset isr ptr
	TCCR1A =	(0<<COM1A1) | (0<<COM1A0) |	//output compare a pins normal operation
				(0<<COM1B1) | (0<<COM1B0) |	//output compare b pins normal operation
#if defined(COM1C1)
				(0<<COM1C1) | (0<<COM1C0) |	//output compare c pins normal operation
#endif
				(0<<WGM11) | (0<<WGM10)		//wgm13..0 = 0b0100 -> ctc, top at ocr1a
				;
	TCCR1B =	(0<<ICNC1) |				//nput capture noise canceller disabled
				(0<<ICES1) |				//input capture edge selection on falling edge
				(0<<WGM13) | (1<<WGM12) |	//wgm13..0 = 0b0100 -> ctc, top at ocr1a
				(prescaler & TMR_PS_MASK)	//prescaler, per the header file
				;
	TCCR1C =	(0<<FOC1A) |				//forced output on ch a disabled
				(0<<FOC1B) |				//forced output on ch b disabled
#if defined(FOC1C)
				(0<<FOC1C) |					//forced output on ch c disabled
#endif
				0x00
				;
	OCR1A = period-1;						//set the period
	TCNT1 = 0;								//reset the timer / counter
	TIMSK1 =	(0<<ICIE1) |				//input capture isr: disabled
#if defined(OCIE1C)
				(0<<OCIE1C) |				//output compare isr for ch a: disabled
#endif
				(0<<OCIE1B) |				//output compare isr for ch b: disabled
				(1<<OCIE1A) |				//output compare isr for ch c: disabled
				(0<<TOIE1)					//tmr overflow interrupt: enabled
				;
}

void tmr1_act(void (*isr_ptr)(void)) {
	/*_tmr1*/_isr_ptr=isr_ptr;					//reassign tmr1 isr ptr
}
