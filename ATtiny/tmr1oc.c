#include "tmr1oc.h"					//we use timer1 output compare

//empty handler
static void /*_tmr1_*/empty_handler(void) {
	//default tmr handler
}

static void (* _isrptr_tov)(void)=empty_handler;	//tmr1_ptr pointing to empty_handler by default
static void (* _isrptr_oca)(void)=empty_handler;	//tmr1_ptr pointing to empty_handler by default
static void (* _isrptr_ocb)(void)=empty_handler;	//tmr1_ptr pointing to empty_handler by default
uint16_t _oca_inc;						//compare point for oc1a increment / period
uint16_t _ocb_inc;						//compare point for oc1b increment / period

//timer overflow
ISR(TIMER1_OVF_vect) {
	//clear the flag - done automatically
	//OCR1A += _oca_inc;					//advance to the next compare point
	_isrptr_tov();					//run the user handler
}

//output compare a isr
ISR(TIMER1_COMPA_vect) {
	//clear the flag - done automatically
	OCR1A += _oca_inc;					//advance to the next compare point
	_isrptr_oca();					//run the user handler
}

//output compare b isr
ISR(TIMER1_COMPB_vect) {
	//clear the flag - done automatically
	OCR1B += _ocb_inc;					//advance to the next compare point
	_isrptr_ocb();					//run the user handler
}
//reset the tmr
//default: normal mode (16-bit top at 0xffff)
void tmr1_init(uint8_t prescaler) {
	//reset user isr handlers and default output compare increments
	_isrptr_tov = _isrptr_oca = _isrptr_ocb = empty_handler;
	_oca_inc = _ocb_inc = 0xffff;						//default values

	//TCCR1  =	TCCR1 & (~TMR1_PSMASK);			//turn off tmr1
	///*_tmr1*/_isr_ptr=/*_tmr1_*/empty_handler;			//reset isr ptr
	TCCR1  =	(0<<COM1A1) | (0<<COM1A0) |	//output compare a pins normal operation
				//(0<<COM1B1) | (0<<COM1B0) |	//output compare b pins normal operation
				//(0<<COM1C1) | (0<<COM1C0) |	//output compare c pins normal operation
				//(0<<WGM11) | (0<<WGM10)		//wgm13..0 = 0b0000 -> default
				0x00;
	//TCCR1  =	(TCCR1 & ~((1<<WGM13) | (1<<WGM12))) |	//clear wgm13..2
	//			(0<<WGM13) | (0<<WGM12);	//wgm13.0=0b0000 - default
	//TCCR1C =	(0<<FOC1A) |				//forced output on ch a disabled
	//			(0<<FOC1B) |				//forced output on ch b disabled
	//			(0<<FOC1C)					//forced output on ch c disabled
	//			;
	//OCR1A = period-1;
	TCNT1 = 0;								//reset the timer / counter
	TIFR |= (1<<OCF1A) | (1<<OCF1B) | (1<<TOV1);		//clear the flag by writing '1' to it
	TIMSK =		//(0<<TICIE1) |				//input capture isr: disabled
				//(0<<OCIE1C) |				//output compare isr for ch a: disabled
				(0<<OCIE1B) |				//output compare isr for ch b: disabled
				(0<<OCIE1A) |				//output compare isr for ch c: disabled
				(0<<TOIE1)					//tmr overflow interrupt: disabled
				;
	TCCR1 |=	(prescaler & TMR1_PSMASK)	//prescaler, per the header file
				;
	//now timer1 is running
}

//set dc for channel a
//0b10->clear on compare match
//need to pay attention to the mode bits (wgm13..0) and dc value
void tmr1a_setpr(uint16_t pr) {
	///*_tmr1*/_isr_ptr=isr_ptr;					//reassign tmr1 isr ptr
	//TIFR |= (1<<OCF1A);						//clear the flag by writing '1' to it
	//TIMSK |=	(1<<OCIE1A)					//tmr overflow interrupt: enabled
	//			;

	//IO_OUT(PWM1A_DDR, PWM1A);				//oc1a as output
	_oca_inc = pr;
	OCR1A = TCNT1 + _oca_inc;							//set dc
}

//set dc for channel b
//0b10->clear on compare match
//need to pay attention to the mode bits (wgm13..0) and dc value
void tmr1b_setpr(uint16_t pr) {
	///*_tmr1*/_isr_ptr=isr_ptr;					//reassign tmr1 isr ptr
	//TIFR |= (1<<OCF1A);						//clear the flag by writing '1' to it
	//TIMSK |=	(1<<OCIE1A)					//tmr overflow interrupt: enabled
	//			;

	//IO_OUT(PWM1B_DDR, PWM1B);				//oc1b as output

	_ocb_inc = pr;
	OCR1B = TCNT1 + _ocb_inc;							//set dc
}

//install user handler for timer1 overflow
void tmr1_act(void (*isr_ptr)(void)) {
	_isrptr_tov=isr_ptr;					//reassign tmr1 isr ptr
	TIFR |= (0<<OCF1A) | (0<<OCF1B) | (1<<TOV1);		//clear the flag by writing '1' to it
	TIMSK |=	//(0<<TICIE1) |				//input capture isr: disabled
				//(0<<OCIE1C) |				//output compare isr for ch a: disabled
				(0<<OCIE1B) |				//output compare isr for ch b: disabled
				(0<<OCIE1A) |				//output compare isr for ch c: disabled
				(1<<TOIE1)					//tmr overflow interrupt: disabled
				;

}

//install user handler
void tmr1a_act(void (*isr_ptr)(void)) {
	_isrptr_oca=isr_ptr;					//reassign tmr1 isr ptr
	TIFR |= (1<<OCF1A) | (0<<OCF1B) | (0<<TOV1);		//clear the flag by writing '1' to it
	TIMSK |=	//(0<<TICIE1) |				//input capture isr: disabled
				//(0<<OCIE1C) |				//output compare isr for ch a: disabled
				(0<<OCIE1B) |				//output compare isr for ch b: disabled
				(1<<OCIE1A) |				//output compare isr for ch c: disabled
				(0<<TOIE1)					//tmr overflow interrupt: disabled
				;

}

//install user handler
void tmr1b_act(void (*isr_ptr)(void)) {
	_isrptr_ocb=isr_ptr;					//reassign tmr1 isr ptr
	TIFR |= (0<<OCF1A) | (1<<OCF1B) | (0<<TOV1);		//clear the flag by writing '1' to it
	TIMSK |=	//(0<<TICIE1) |				//input capture isr: disabled
				//(0<<OCIE1C) |				//output compare isr for ch a: disabled
				(1<<OCIE1B) |				//output compare isr for ch b: disabled
				(0<<OCIE1A) |				//output compare isr for ch c: disabled
				(0<<TOIE1)					//tmr overflow interrupt: disabled
				;

}
