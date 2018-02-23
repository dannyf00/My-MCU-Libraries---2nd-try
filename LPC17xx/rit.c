/*
 * rit.c
 *
 *  Created on: May 18, 2016
 *      Author: Ken
 */


#include "rit.h"					//we use rit

//hardware configuration
//end hardware configuration

//global defines
#define RITx			LPC_RIT
#define RITx_IRQn		RIT_IRQn

//empty handler
static void empty_handler(void) {
	//do nothing
}

//global variables
static void (* _isr_ptr)(void)=empty_handler;

//rit isr
void RIT_IRQHandler(void) {
	//clear the flag by writing 1 to it
	RITx->RICTRL |= (1<<0);
	_isr_ptr();						//run the isr

}

//reset rit
void rit_init(uint32_t ps, uint32_t pr) {
	//enable power
	LPC_SC->PCONP |= (1<<16);		//bit16=rit
	//enable clock
	LPC_SC->PCLKSEL1 = (LPC_SC->PCLKSEL1 &~(0b11<<14)) |	//clear rit bits (26..27)
						((ps & 0b11) << 14);						//0b00=cclk/4, 0b01=cclk, 0b10=cclk/2, 0b11=cclk/8

	//turn off rit
	RITx->RICTRL &=~(1<<3);			//disable rit
	RITx->RICTRL |= (1<<1);			//rit reset on compare
	RITx->RIMASK = 0x0000;			//fffffffful;	//all bits to be compared
	RITx->RICOMPVAL = pr - 1;		//compval-1;	//set the comp value
	RITx->RICOUNTER = 0;			//reset the counter
	RITx->RICTRL |= (1<<0);			//clear the flag

	//turn on rit
	RITx->RICTRL |= (1<<3);			//enable rit
}

//install user handler
void rit_act(void (*isr_ptr)(void)) {
	_isr_ptr=isr_ptr;				//install user handler
	RITx->RICTRL |= 1<<0;			//clera the flag by writing '1' to it
	NVIC_EnableIRQ(RITx_IRQn);		//enable interrupt
}
