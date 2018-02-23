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
static void (* /*_tmr0*/_isrptr)(void)=empty_handler;				//tmr0_ptr pointing to empty_handler by default

//tmr0 isr
ISR(TIMER0_COMPA_vect) {
	/*_tmr0*/_isrptr();					//execute the handler
}

//reset the tmr
//ctc mode wgm02..0=0b010
void tmr0_init(uint8_t ps, uint8_t pr) {
	//initialize the handler
	_isrptr = empty_handler;

	//initialize the timer
	TCCR0B =	TCCR0B & (~TMR0_PSMASK);				//turn off tmr0
	TCCR0A = 	(0<<COM0A1) | (0<<COM0A0) |				//oc0a pins normal operations
				(0<<COM0B1) | (0<<COM0B0) |				//oc0b pins normal operations
				(1<<WGM01) | (0<<WGM00);				//reset to default. wgm01..0=0b10
	TCCR0B =	(TCCR0B & ~(1<<WGM02)) |
				(0<<WGM02);					//wgm02=0b0
	TCNT0 = 0;								//reset the counter
	OCR0A = pr - 1;
	TIFR |= 1<<TOV0;						//clear by writing 1 to it
	TIMSK &= ~(1<<TOIE0)					//tmr overflow interrupt: disabled
				;
	TCCR0B |=	(ps & TMR0_PSMASK)			//prescaler = 1:1, per the header file
				;
	//now timer 0 is running
}

void tmr0_act(void (*isr_ptr)(void)) {

	/*_tmr0*/_isrptr=isr_ptr;					//reassign tmr0 isr ptr
	TIFR |= (1<<OCF0A);							//clear by writing 1 to it
	TIMSK |= (1<<OCIE0A)						//tmr output compare match ch a interrupt: enabled
				;

}
