#include "tmr1.h"					//we use timer0

//hardware configuration
#define TMRx			LPC_TIM1
#define TMRx_IRQn		TIMER1_IRQn

//end hardware configuration

//empty handler
static void empty_handler(void) {
	//do nothing
}

//handler
static void (*_isr_ptr0)(void) = empty_handler;
static void (*_isr_ptr1)(void) = empty_handler;
static void (*_isr_ptr2)(void) = empty_handler;
static void (*_isr_ptr3)(void) = empty_handler;

//period register
static uint32_t _tmr_pr0=0xfffffffful;
static uint32_t _tmr_pr1=0xfffffffful;
static uint32_t _tmr_pr2=0xfffffffful;
static uint32_t _tmr_pr3=0xfffffffful;

//global defines

//global variables

//isr
void TIMER1_IRQHandler(void) {
	//isr for mr0
	if (TMRx->IR & (1<<0)) {
		TMRx->IR |= (1<<0);			//clear the flag by writing 1 to it
		TMRx->MR0 += _tmr_pr0;		//advance to the next match point
		_isr_ptr0();				//run user handler
	}

	//isr for mr1
	if (TMRx->IR & (1<<1)) {
		TMRx->IR |= (1<<1);			//clear the flag by writing 1 to it
		TMRx->MR1 += _tmr_pr1;		//advance to the next match point
		_isr_ptr1();				//run user handler
	}

	//isr for mr2
	if (TMRx->IR & (1<<2)) {
		TMRx->IR |= (1<<2);			//clear the flag by writing 1 to it
		TMRx->MR2 += _tmr_pr2;		//advance to the next match point
		_isr_ptr2();				//run user handler
	}

	//isr for mr3
	if (TMRx->IR & (1<<3)) {
		TMRx->IR |= (1<<3);			//clear the flag by writing 1 to it
		TMRx->MR3 += _tmr_pr3;		//advance to the next match point
		_isr_ptr3();				//run user handler
	}
}

//reset timer0 with prescaler
void tmr1_init(uint32_t prescaler) {
	//_tmr_pr0 = 0xfffffffful;		//reset the period

	//enable power
	LPC_SC->PCONP |= (1<<2);		//enable power. 1=tim0, 2=tim1, 22=tim3, 23=tim4
	//enable clock
	//PCLKSEL0: bit 2..3 for timer0, bit 4..5 for timer1
	//PCLKSEL1: bit 12..13 for timer2, bit 14..15 for timer3
	LPC_SC->PCLKSEL0 = (LPC_SC->PCLKSEL0 & ~(0b11<<(2*2))) |		//clear bits
						(0b01 << (2*2));							//0b00->cclk/4, 0b01->cclk, 0b10->cclk/2, 0b11->cclk/8

	//stop the timer
	TMRx->TCR &=~(1<<0);			//stop the timer
	//TMRx->TCR |= (1<<1);			//reset timer
	//TMRx->TCR &=~(1<<1);			//restart timer
	TMRx->IR = 0x3f;				//clear all flags
	TMRx->CTCR = (TMRx->CTCR & ~0b11) |		//clear the bits
					(0b00);			//0b00->timer mode. 0b01/10/11->capture mode
	TMRx->TC = 0;					//reset the timer
	TMRx->PC = 0;					//reset the prescaler counter
	TMRx->PR = prescaler - 1;		//set prescaler

	//start the timer
	TMRx->TCR |= (1<<0);
}

//set match + mode - ch 0
void tmr1_setpr0(uint32_t match) {
	TMRx->MR0 = _tmr_pr0 = match - 1;
	TMRx->MR0+= TMRx->TC;			//match - 1;			//set match
	TMRx->MCR = (TMRx->MCR & ~(0b111 << (3*0))) |	//clear bits
				((TMRMR_EINT & 0b111) << (3*0));	//set mode bits
}

//install user handler for ch 0
void tmr1_act0(void (*isr_ptr)(void)) {
	_isr_ptr0=isr_ptr;				//install user handler
	NVIC_EnableIRQ(TMRx_IRQn);		//enable timer0 irq
}

//set match + mode - ch 1
void tmr1_setpr1(uint32_t match) {
	TMRx->MR1 = _tmr_pr1 = match - 1;			//set match
	TMRx->MR1+= TMRx->TC;
	TMRx->MCR = (TMRx->MCR & ~(0b111 << (3*1))) |	//clear bits
				((TMRMR_EINT & 0b111) << (3*1));	//set mode bits
}

//install user handler for ch 1
void tmr1_act1(void (*isr_ptr)(void)) {
	_isr_ptr1=isr_ptr;				//install user handler
	NVIC_EnableIRQ(TMRx_IRQn);		//enable timer0 irq
}

//set match + mode - ch 2
void tmr1_setpr2(uint32_t match) {
	TMRx->MR2 = _tmr_pr2 = match - 1;			//set match
	TMRx->MR2+= TMRx->TC;
	TMRx->MCR = (TMRx->MCR & ~(0b111 << (3*2))) |	//clear bits
				((TMRMR_EINT & 0b111) << (3*2));	//set mode bits
}

//install user handler for ch 2
void tmr1_act2(void (*isr_ptr)(void)) {
	_isr_ptr2=isr_ptr;				//install user handler
	NVIC_EnableIRQ(TMRx_IRQn);		//enable timer0 irq
}

//set match + mode - ch 3
void tmr1_setpr3(uint32_t match) {
	TMRx->MR3 = _tmr_pr3 = match - 1;			//set match
	TMRx->MR3+= TMRx->TC;
	TMRx->MCR = (TMRx->MCR & ~(0b111 << (3*3))) |	//clear bits
				((TMRMR_EINT & 0b111) << (3*3));	//set mode bits
}

//install user handler for ch 3
void tmr1_act3(void (*isr_ptr)(void)) {
	_isr_ptr3=isr_ptr;				//install user handler
	NVIC_EnableIRQ(TMRx_IRQn);		//enable timer0 irq
}

