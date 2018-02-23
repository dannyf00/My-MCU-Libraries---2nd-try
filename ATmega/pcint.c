//#include <avr/io.h>							//we use gcc-avr
#include "pcint.h"								//we use pcint

//hardware configuration
//end hardware configuration

//global defines


//global variables

//empty handlers
static void empty_handler(void) {
	//do nothing here
}

static void (* _pcint0_isr_ptr)(void)=empty_handler;	//pcint0_ptr pointing to empty_handler by default
static void (* _pcint1_isr_ptr)(void)=empty_handler;	//pcint1_ptr pointing to empty_handler by default
static void (* _pcint2_isr_ptr)(void)=empty_handler;	//pcint2_ptr pointing to empty_handler by default

//pcint0 isr
ISR(PCINT0_vect) {
	_pcint0_isr_ptr();						//execute the isr
}

//reset pcint isr
void pcint0_init(void) {
	_pcint0_isr_ptr = empty_handler;		//reset isr ptr

	//initialize the pins
	IO_IN(PCINT0_DDR, PCINT0_PINs);				//pcint0 as input

	PCMSK0 |= PCINT0_PINs;					//enable pcint pins

	PCIFR |= (1<<PCIF0);					//write 0 to clear the flag
	PCICR &=~(1<<PCIE0);					//not enable interrupt yet
}

//activate pcint0
void pcint0_act(void (*isr_ptr)(void)) {
	_pcint0_isr_ptr = isr_ptr;				//install user isr handler

	PCIFR |= (1<<PCIF0);					//write 0 to clear the flag
	PCICR |= (1<<PCIE0);					//enable interrupt
}

//pcint1 isr
ISR(PCINT1_vect) {
	_pcint1_isr_ptr();						//execute the isr
}

//reset pcint isr
void pcint1_init(void) {
	_pcint1_isr_ptr = empty_handler;		//reset isr ptr

	//initialize the pins
	IO_IN(PCINT1_DDR, PCINT1_PINs);				//pcint0 as input

	PCMSK1 |= PCINT1_PINs;					//enable pcint pins

	PCIFR |= (1<<PCIF1);					//write 0 to clear the flag
	PCICR &=~(1<<PCIE1);					//not enable interrupt yet
}

//activate pcint1
void pcint1_act(void (*isr_ptr)(void)) {
	_pcint1_isr_ptr = isr_ptr;				//install user isr handler

	PCIFR |= (1<<PCIF1);					//write 0 to clear the flag
	PCICR |= (1<<PCIE1);					//enable interrupt
}

//pcint2 isr
ISR(PCINT2_vect) {
	_pcint2_isr_ptr();						//execute the isr
}

//reset pcint isr
void pcint2_init(void) {
	_pcint2_isr_ptr = empty_handler;		//reset isr ptr

	//initialize the pins
	IO_IN(PCINT2_DDR, PCINT2_PINs);				//pcint0 as input

	PCMSK2 |= PCINT2_PINs;					//enable pcint pins

	PCIFR |= (1<<PCIF2);					//write 0 to clear the flag
	PCICR &=~(1<<PCIE2);					//not enable interrupt yet
}

//activate pcint0
void pcint2_act(void (*isr_ptr)(void)) {
	_pcint2_isr_ptr = isr_ptr;				//install user isr handler

	PCIFR |= (1<<PCIF2);					//write 0 to clear the flag
	PCICR |= (1<<PCIE2);					//enable interrupt
}
