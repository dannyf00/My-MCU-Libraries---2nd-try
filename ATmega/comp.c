/*
 */

#include <avr/io.h>						//we use gcc avr
#include <avr/interrupt.h>			//we ues interrupt
#include "gpio.h"

//hardware configuration
#define C
//end hardware configuration

//global variables
void (* _comp_isr_ptr)(void);				//comp_ptr pointing to empty_handler by default

//empty handler
void _comp_empty_handler(void) {
	//default tmr handler
}

//some chips use ana_comp_vect and others analog_comp_vect
#if defined(ANA_COMP_vect)
ISR(ANA_COMP_vect) {
#else
ISR(ANALOG_COMP_vect) {
#endif
	//clear the flag
	_comp_isr_ptr();				//run user isr handler
}

//reset the comparator
void comp_init(void) {
	//ain0/ain1 assumed to be input

	//configure output pin
	//IO_CLR(COMP_PORT, COMP_OUT);	//clear the output pin
	//IO_OUT(COMP_DDR , COMP_OUT);	//output the pin

	//configure the analog comparator
#if defined(DIDR)
	DIDR = 	(1<<AIN1D) |			//disable ain1's digital input
			(1<<AIN0D)				//disable ain0's digital input
			;
#endif

#if defined(DIDR1)
	DIDR1 = (1<<AIN1D) |			//disable ain1's digital input
			(1<<AIN0D)				//disable ain0's digital input
			;
#endif

	//configure ACSRB if available
#if defined(ACSRB)
	ACSRB &=~(0<<ACME);				//disable analog comparator multiplexer
#endif

	//configure ACSR
	ACSR &=~(1<<ACIE);				//disable interrupt
	ACSR = 	(0<<ACD) |				//analog comparator power on
#if defined(ACBG)
			(0<<ACBG) |				//bandgap reference not selected. Use AIN1 for non-inverting input
#endif
			(1<<ACI) |				//clear acif by writing '1' to it
			(0<<ACIE) |				//interrupt not yet enabled
			(0<<ACIC) |				//analog comparator input capture disabled
			(0<<ACIS1) | (0<<ACIS0)	//interrupt on output toggle
			//(0<<ACIS1) | (1<<ACIS0)	//reserved
			//(1<<ACIS1) | (0<<ACIS0)	//interrupt on falling output edge
			//(1<<ACIS1) | (1<<ACIS0)	//interrupt on rising output edge
			;

	ACSR |= (1<<ACIE);				//enable the interrupt

	//rest comp_ptr
	_comp_isr_ptr = _comp_empty_handler;
}

//install my isr handler
void comp_act(void (*isr_ptr)(void)) {
	_comp_isr_ptr = isr_ptr;
}

