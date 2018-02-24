/*
 * tmr32.c
 *
 *  Created on: Aug 14, 2016
 *      Author: Ken
 */

//*****************************************************************************
//
// MSP432 main.c template - Empty main
//
//****************************************************************************

//#include "msp.h"
#include "tmr32.h"					//we use timer32

//hardware configuration
//end hardware configuration

//global defines
#define TMR1				TIMER32_1		//we use timer32_1
#define TMR2				TIMER32_2		//we use timer32_1

//global variables

//empty handler
static void empty_handler(void) {
	//do nothing here
}

//user isr ptr
//those two ISRs (T32_INT1_ISR and T32_INT2_ISR) will need to be inserted in the start-up file
static void (* _tmr321_isrptr)(void)=empty_handler;				//tmr_ptr pointing to empty_handler by default
static void (* _tmr322_isrptr)(void)=empty_handler;				//tmr_ptr pointing to empty_handler by default

//tmr32 isr
//#pragma vector=USCI_B0_VECTOR	-- does not yet work on CCS
void T32_INT1_IRQHandler(void) {
	//clear the flag
	TMR1->INTCLR = 1;						//clear the flag by writing to intclr register

	//run user isr handler
	_tmr321_isrptr();
}

//initialize tmrx
void tmr321_init(uint32_t prescaler, uint32_t period) {
	_tmr321_isrptr=empty_handler;			//reset user handler

	//stop the timer
	TMR1->CONTROL &=~(1<<7);				//disable the timer

	//configure the timer
	TMR1->CONTROL = (1<<6) |				//1=periodic mode, 0=free-running mode
					(0<<5) |				//1=interrupt enabled, 0=interrupt disabled
					(prescaler & TMR32PS_MASK) |	//set prescaler
					(1<<1) |				//0=16bit timer, 1=32-bit timer
					(0<<0);					//0=timer wraps around, 1=one-shot
	TMR1->LOAD = period - 1;				//set the load register
	//TMRx->BGLOAD = period - 1;				//alternatively, write to BGLOAD
	//TMRx->INTCLR = 1;						//write to clear interrupt

	//enable the timer
	TMR1->CONTROL|= (1<<7);					//start the timer
}

//install user handler for tmrx
void tmr321_act(void (*isrptr)(void)) {
	TMR1->INTCLR = 1;						//write to clear interrupt
	_tmr321_isrptr = isrptr;				//install user handler
	TMR1->CONTROL|=1<<5;					//enable interrupt
	NVIC_EnableIRQ(T32_INT1_IRQn);			//enable tmr321 isr
}

//tmr32 isr
//#pragma vector=USCI_B0_VECTOR	-- does not yet work on CCS
void T32_INT2_IRQHandler(void) {
	//clear the flag
	TMR2->INTCLR = 1;						//clear the flag by writing to intclr register

	//run user isr handler
	_tmr322_isrptr();
}

//initialize tmrx
void tmr322_init(uint32_t prescaler, uint32_t period) {
	_tmr322_isrptr=empty_handler;			//reset user handler

	//stop the timer
	TMR2->CONTROL &=~(1<<7);				//disable the timer

	//configure the timer
	TMR2->CONTROL = (1<<6) |				//1=periodic mode, 0=free-running mode
					(0<<5) |				//1=interrupt enabled, 0=interrupt disabled
					(prescaler & TMR32PS_MASK) |	//set prescaler
					(1<<1) |				//0=16bit timer, 1=32-bit timer
					(0<<0);					//0=timer wraps around, 1=one-shot
	TMR2->LOAD = period - 1;				//set the load register
	//TMRx->BGLOAD = period - 1;				//alternatively, write to BGLOAD
	//TMRx->INTCLR = 1;						//write to clear interrupt

	//enable the timer
	TMR2->CONTROL|= (1<<7);					//start the timer
}

//install user handler for tmrx
void tmr322_act(void (*isrptr)(void)) {
	TMR2->INTCLR = 1;						//write to clear interrupt
	_tmr322_isrptr = isrptr;					//install user handler
	TMR2->CONTROL|=1<<5;					//enable interrupt
	NVIC_EnableIRQ(T32_INT2_IRQn);			//enable tmr321 isr
}
