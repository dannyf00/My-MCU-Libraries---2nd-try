#include "tim1.h"								//we use tim1

//hardware configuration
#define TIMx			TIM1					//tim1
//end hardware configuration

//global defines

//empty handler
static void empty_handler(void) {
	//do nothing
}

//global variables
static void (*/*_tim4*/_isrptr) (void)=empty_handler;					//tim isr handler ptr

//tim3_ovr_handler to be set by users
//tim3 isr handler
#pragma vector = TIM1_OVR_UIF_vector		//tim3 overflow interrupt
__interrupt void tim1_ovr_isr(void) {
	TIMx->SR1 &=~(1<<0);						//TIM1_SR_UIF=0;							//clear the flag
	/*_tim4*/_isrptr();							//execute the isr handler
}

//initialize the timer
//ps = prescaler: TIM1_PS1x, TIM4_PS2x, TIM4_PS4x, TIM4_PS8x, TIM4_PS16x, TIM4_PS32x, TIM4_PS64x, TIM4_PS128x
//pr = 8-bit period, 0x00 - 0xff
void tim1_init(uint16_t ps, uint16_t pr) {
	_isrptr = empty_handler;				//reset the handler
	
	//enable the clock to peripheral
	CLK->PCKENR1 |= CLK_PCKENR1_TIM1;			//'1'=clock enabled, '0'=clock disabled

	//stop the timer
	TIMx->CR1 &=~(1<<0);					//stop the timer
	
	//set up the timer
	TIMx->CR1 = (1<<7) |					//'1'->enable auto reload buffer
	  			(0<<5) |					//'0'->edge aligned. 1..3->center aligned
				(0<<4) |					//'0'->up counter, '1' downcounter
				(0<<3) |					//'0'->continuous mode, '1'->one pulse mode
				(0<<2) |					//'0'-> update enable source
				(0<<1) |					//'0'-> update enabled
				(0<<0);						//counter disabled
	TIMx->CR2 = 0;							//default value
	TIMx->SMCR = 0;							//default value
	TIMx->ETR = 0;							//'0'->external trigger not inverted
	
	ps = ps - 1; TIMx->PSCRH = ps >> 8; TIMx->PSCRL = ps;	//set up the prescaler - msb first
	TIMx->CNTRH = 0; TIMx->CNTRL = 0;			//reset the counter
	pr = pr - 1; TIMx->ARRH = (pr >> 8); TIMx->ARRL = pr;	//load up the auto reload register - msb first
	
	TIMx->SR1&=~(1<<0);						//clear UIF
	TIMx->IER&=~(1<<0);						//'1'->enable overflow interrupt, '0'->disable interrupt

	//re-enable the counter
	TIMx->CR1 |= (1<<0);	
}

//activate user handler
void tim1_act(void (*isr_ptr)(void)) {
	_isrptr = isr_ptr;						//install user handler
	
	TIMx->SR1&=~(1<<0);						//clear UIF
	TIMx->IER|= (1<<0);						//'1'->enable overflow interrupt, '0'->disable interrupt
}
