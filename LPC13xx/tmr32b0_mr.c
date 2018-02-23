//#include <lpc122x.h>				//we use lpc122x
#include "tmr32b0_mr.h"				//we use tmr32b0

//hardware configuration
//end hardware configuration

//global defines
#define CTx				LPC_TMR32B0	//16bix timer0
#define CTx_IRQn		TIMER_32_0_IRQn

//empty handler
static void empty_handler(void) {
	//do nothing here
}

//global variable
//pointer to user handler
static void (* _tmrisr0_ptr)(void)=empty_handler;				//tmr1_ptr pointing to empty_handler
static void (* _tmrisr1_ptr)(void)=empty_handler;				//tmr1_ptr pointing to empty_handler
static void (* _tmrisr2_ptr)(void)=empty_handler;				//tmr1_ptr pointing to empty_handler
static void (* _tmrisr3_ptr)(void)=empty_handler;				//tmr1_ptr pointing to empty_handler

static uint32_t _tmr_pr0=0xffff;								//timer period
static uint32_t _tmr_pr1=0xffff;								//timer period
static uint32_t _tmr_pr2=0xffff;								//timer period
static uint32_t _tmr_pr3=0xffff;								//timer period

//tmr handler
void TIMER32_0_IRQHandler(void) {
	//tmr0 handler here
	//match channel 0
	if (CTx->IR & (1<<0)) {
		CTx->IR |= 1<<0;			//clear the flag by writing 1 to it
		CTx->MR0+= _tmr_pr0;			//update match register
		_tmrisr0_ptr();					//execute user handler
	}

	//match channel 1
	if (CTx->IR & (1<<1)) {
		CTx->IR |= 1<<1;			//clear the flag by writing 1 to it
		CTx->MR1+= _tmr_pr1;			//update match register
		_tmrisr1_ptr();					//execute user handler
	}

	//match channel 2
	if (CTx->IR & (1<<2)) {
		CTx->IR |= 1<<2;			//clear the flag by writing 1 to it
		CTx->MR2+= _tmr_pr2;			//update match register
		_tmrisr2_ptr();					//execute user handler
	}

	//match channel 3
	if (CTx->IR & (1<<3)) {
		CTx->IR |= 1<<3;			//clear the flag by writing 1 to it
		CTx->MR3+= _tmr_pr3;			//update match register
		_tmrisr3_ptr();					//execute user handler
	}
}

//set up tmr
void tmr32b0_init(uint32_t prescaler) {
	//route clock to timer
	LPC_SYSCON->SYSAHBCLKCTRL |= (1<<9);		//7=ct16b0, 8=ct16b1, 9=ct32b0, 10=ct32b1

	//configure as counter
	CTx->CTCR = (CTx->CTCR & ~0b11) | 0b00;		//00->as counter

	//set up the timer
	CTx->TCR&=~(1<<0);				//disable the timer
	//CTx->PC = (prescaler-1) & 0xffff;			//set up the prescaler
	CTx->PR = (prescaler-1) /*& 0xffff*/;				//set up the prescaler register
	CTx->IR|=	(1<<0) |			//clear the interrupt flag on match channel 0..3, by writing 1s to it
				(1<<1) |
				(1<<2) |
				(1<<3);
	CTx->TC = 0;					//reset the counter
	CTx->TCR|= (1<<0);				//start the timer
}

//set up match register - ch0
void tmr32b0_setpr0(uint32_t match/*, uint32_t config*/) {
	//enable timer interrupt on match
	CTx->MCR =	(CTx->MCR & ~(0b111<<(3*0))) |	//clear MCR
				((0x0000 & 0b111) << (3*0));	//0b00x: trigger an interrupt; 0b0x0: reset on match; 0bx00: stop on match
	CTx->MR0 = _tmr_pr0 = (match-1) /*& 0xffff*/;	//set the match register
}

//set up match register - ch1
void tmr32b0_setpr1(uint32_t match/*, uint32_t config*/) {
	//enable timer interrupt on match
	CTx->MCR =	(CTx->MCR & ~(0b111<<(3*1))) |	//clear MCR
				((0x0000 & 0b111) << (3*1));	//0b00x: trigger an interrupt; 0b0x0: reset on match; 0bx00: stop on match
	CTx->MR1 = _tmr_pr1 = (match-1) /*& 0xffff*/;	//set the match register
}

//set up match register - ch2
void tmr32b0_setpr2(uint32_t match/*, uint32_t config*/) {
	//enable timer interrupt on match
	CTx->MCR =	(CTx->MCR & ~(0b111<<(3*2))) |	//clear MCR
				((0x0000 & 0b111) << (3*2));	//0b00x: trigger an interrupt; 0b0x0: reset on match; 0bx00: stop on match
	CTx->MR2 = _tmr_pr2 = (match-1) /*& 0xffff*/;	//set the match register
}

//set up match register - ch3
void tmr32b0_setpr3(uint32_t match/*, uint32_t config*/) {
	//enable timer interrupt on match
	CTx->MCR =	(CTx->MCR & ~(0b111<<(3*3))) |	//clear MCR
				((0x0000 & 0b111) << (3*3));	//0b00x: trigger an interrupt; 0b0x0: reset on match; 0bx00: stop on match
	CTx->MR3 = _tmr_pr3 = (match-1) /*& 0xffff*/;	//set the match register
}

//set up tmr handler, channel 0
void tmr32b0_act0(void (*isr_ptr)(void)){
	//clear the flag
	CTx->IR |= 1<<0;							//clear the flag by writing 1 to it

	//enable timer interrupt on match
	CTx->MCR|=(CTxMR_EINT & 0b111) << (3*0);	//enable timer match interrupt

	_tmrisr0_ptr = isr_ptr;			//install user handler
	NVIC_EnableIRQ(CTx_IRQn);
}

//set up tmr handler, channel 1
void tmr32b0_act1(void (*isr_ptr)(void)){
	//clear the flag
	CTx->IR |= 1<<1;							//clear the flag by writing 1 to it

	//enable timer interrupt on match
	CTx->MCR|=(CTxMR_EINT & 0b111) << (3*1);	//enable timer match interrupt

	_tmrisr1_ptr = isr_ptr;			//install user handler
	NVIC_EnableIRQ(CTx_IRQn);
}

//set up tmr handler, channel 2
void tmr32b0_act2(void (*isr_ptr)(void)){
	//clear the flag
	CTx->IR |= 1<<2;							//clear the flag by writing 1 to it

	//enable timer interrupt on match
	CTx->MCR|=(CTxMR_EINT & 0b111) << (3*2);	//enable timer match interrupt

	_tmrisr2_ptr = isr_ptr;			//install user handler
	NVIC_EnableIRQ(CTx_IRQn);
}

//set up tmr handler, channel 3
void tmr32b0_act3(void (*isr_ptr)(void)){
	//clear the flag
	CTx->IR |= 1<<3;							//clear the flag by writing 1 to it

	//enable timer interrupt on match
	CTx->MCR|=(CTxMR_EINT & 0b111) << (3*3);	//enable timer match interrupt

	_tmrisr3_ptr = isr_ptr;			//install user handler
	NVIC_EnableIRQ(CTx_IRQn);
}

//get match register value - ch0
uint32_t tmr32b0_getpr0(void) {
	return CTx->MR0;
}

//get match register value - ch1
uint32_t tmr32b0_getpr1(void) {
	return CTx->MR1;
}

//get match register value - ch2
uint32_t tmr32b0_getpr2(void) {
	return CTx->MR2;
}

//get match register value - ch3
uint32_t tmr32b0_getpr3(void) {
	return CTx->MR3;
}

