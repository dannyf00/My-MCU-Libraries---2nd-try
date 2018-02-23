#include "tmr0.h"							//we use tmr0

//hardware configuration
//end hardware configuration

//global defines

//global variables

//empty handler
static void /*_tmr0_*/empty_handler(void) {
	//default tmr handler
}

//uses roman black's zero cumulative error approach
static void (* /*_tmr0*/_isrptr_tov)(void)=empty_handler;				//tmr0_ptr pointing to empty_handler by default
static void (* /*_tmr0*/_isrptr_oca)(void)=empty_handler;				//tmr0_ptr pointing to empty_handler by default
static void (* /*_tmr0*/_isrptr_ocb)(void)=empty_handler;				//tmr0_ptr pointing to empty_handler by default
static uint8_t _oca_inc=0xff;
static uint8_t _ocb_inc=0xff;

//tmr0 isr
ISR(TIMER0_OVF_vect) {
		/*_tmr0*/_isrptr_tov();					//execute the handler
}

//tmr0 compare match a
ISR(TIMER0_COMPA_vect) {
	OCR0A += _oca_inc;							//advance tot he next match point
	/*_tmr0*/_isrptr_oca();					//execute the handler
}

//tmr0 compare match b
ISR(TIMER0_COMPB_vect) {
	OCR0B += _ocb_inc;							//advance to the next match point
	/*_tmr0*/_isrptr_ocb();					//execute the handler
}

//reset the tmr
void tmr0_init(unsigned char ps) {
	//initialize the handler
	_isrptr_tov = _isrptr_oca = _isrptr_ocb = empty_handler;
	_oca_inc=_ocb_inc=0xff;

	//initialize the timer
	TCCR0B =	TCCR0B & (~TMR0_PSMASK);				//turn off tmr0
	TCNT0 = 0;								//reset the counter
	TIFR |= (1<<TOV0) | (1<<OCF0A) | (1<<OCF0B);						//clear by writing 1 to it
	TIMSK = (TIMSK & ~((1<<TOIE0) | (1<<OCIE0A) | (1<<OCIE0B))) |		//tmr overflow interrupt: disabled
			(0<<TOIE0) | (0<<OCIE0A) | (0<<OCIE0B);
				;
	TCCR0B |=	(ps & TMR0_PSMASK)			//prescaler = 1:1, per the header file
				;
	//now timer 0 is running
}

//for the overflow isr
void tmr0_act(void (*isr_ptr)(void)) {

	_isrptr_tov=isr_ptr;					//reassign tmr0 isr ptr
	TIFR |= (1<<TOV0) | (0<<OCF0A) | (0<<OCF0B);						//clear by writing 1 to it
	TIMSK |= (1<<TOIE0) | (0<<OCIE0A) | (0<<OCIE0B);						//tmr overflow interrupt: enabled
}

//set up the period for cha
void tmr0a_setpr(uint8_t pr) {
	_oca_inc = pr;							//save the period value
	OCR0A = TCNT0 + _oca_inc;				//load the next compare point
}

//load user isr for cha
void tmr0a_act(void (*isr_ptr)(void)) {
	_isrptr_oca=isr_ptr;					//reassign tmr0 isr ptr
	TIFR |= (0<<TOV0) | (1<<OCF0A) | (0<<OCF0B);						//clear by writing 1 to it
	TIMSK |= (0<<TOIE0) | (1<<OCIE0A) | (0<<OCIE0B);						//tmr overflow interrupt: enabled
}
//set up the period for chb
void tmr0b_setpr(uint8_t pr) {
	_ocb_inc = pr;							//save the period value
	OCR0B = TCNT0 + _ocb_inc;				//load the next compare point
}

//load user isr for cha
void tmr0b_act(void (*isr_ptr)(void)) {
	_isrptr_ocb=isr_ptr;					//reassign tmr0 isr ptr
	TIFR |= (0<<TOV0) | (0<<OCF0A) | (1<<OCF0B);						//clear by writing 1 to it
	TIMSK |= (0<<TOIE0) | (0<<OCIE0A) | (1<<OCIE0B);						//tmr overflow interrupt: enabled
}
