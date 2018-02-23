#include "tmr1.h"							//tmr1 header file


//global defines

//global variables

//empty handler
static void /*_tmr1_*/empty_handler(void) {
	//default tmr handler
}

static void (* /*_tmr1*/_isrptr)(void)=empty_handler;	//tmr1_ptr pointing to empty_handler by default

//tmr1 compc isr
ISR(TIMER1_OVF_vect) {
	//clear the flag - done automatically
	/*_tmr1*/_isrptr();						//execute the handler
}

//reset the tmr
//mode CTC, top at OCR1C
void tmr1_init(uint8_t prescaler, uint16_t pr) {
	/*_tmr1*/_isrptr=/*_tmr1_*/empty_handler;			//reset isr ptr

	//set up the timer
	TCCR1 =		TCCR1 & (~TMR1_PSMASK);			//turn off tmr1
	TCCR1 =		(TCCR1 & ~((1<<COM1A1) | (1<<COM1A0))) |	//clear wgm13..2
				(0<<COM1A1) | (0<<COM1A0);	//0b00->normal port operation
	TCCR1 |=	(1<<CTC1);					//1->CTC mode
	OCR1C = pr - 1;
	TCNT1 = 0;								//reset the timer / counter

	TIFR |= (1<<OCF1A) | (1<<OCF1B) | (1<<TOV1);						//clear the flag by writing '1' to it
	TIMSK =	//(0<<TICIE1) |					//input capture isr: disabled
				//(0<<OCIE1C) |				//output compare isr for ch a: disabled
				(0<<OCIE1B) |				//output compare isr for ch b: disabled
				(0<<OCIE1A) |				//output compare isr for ch c: disabled
				(0<<TOIE1)					//tmr overflow interrupt: disabled
				;
	TCCR1 |=	(prescaler & TMR1_PSMASK)	//prescaler, per the header file
				;
	//now timer1 is running
}

//enable overflow interrupt
void tmr1_act(void (*isr_ptr)(void)) {
	/*_tmr1*/_isrptr=isr_ptr;					//reassign tmr1 isr ptr
	TIFR |= 	(1<<TOV1);						//clear the flag by writing '1' to it
	TIMSK |=	(1<<TOIE1)					//tmr overflow interrupt: enabled
				;
}
