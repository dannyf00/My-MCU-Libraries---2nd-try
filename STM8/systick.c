#include "systick.h"							//we use tim4 as systick
//use TIM4 as systick

//hardware configuration
#define TIMx			TIM4					//TIM4/6
#define TIMx_PS			7						//prescaler = 2^TIMx_PS. [0..7]->[1x..128x]
//end hardware configuration

//global defines

//global variables
volatile uint32_t systickovf_counter=0;			//systick overflow counter

//tim4_ovr_handler to be set by users
//tim4 isr handler
#pragma vector = TIM4_OVR_UIF_vector			//tim4 overflow interrupt
__interrupt void tim4_ovr_isr(void) {
//INTERRUPT_HANDLER(time4_isr, TIM4_OVR_UIF_vector) {
	TIMx->SR1 &=~(1<<0);						//TIM4_SR_UIF=0;							//clear the flag
	systickovf_counter+=0x100;					//increment systick overflow counter - 8bit timer counter
}

//initialize the timer
//ps = prescaler: TIM1_PS1x, TIM4_PS2x, TIM4_PS4x, TIM4_PS8x, TIM4_PS16x, TIM4_PS32x, TIM4_PS64x, TIM4_PS128x
//pr = 8-bit period, 0x00 - 0xff
void systick_init(void) {
	//enable the clock to peripheral
	//needs to be changed if TIM6 is used
	CLK->PCKENR1 |= CLK_PCKENR1_TIM4;			//'1'=clock enabled, '0'=clock disabled
	
	//stop the timer
	TIMx->CR1 &=~(1<<0);						//stop the timer
	
	//set up the timer
	TIMx->CR1 = (1<<7) |						//'1'->enable auto reload buffer
	  			(0<<5) |						//'0'->edge aligned. 1..3->center aligned
				(0<<4) |						//'0'->up counter, '1' downcounter
				(0<<3) |						//'0'->continuous mode, '1'->one pulse mode
				(0<<2) |						//'0'-> update enable source
				(0<<1) |						//'0'-> update enabled
				(0<<0);							//counter disabled
	//TIMx->CR2 = 0;							//default value
	//TIMx->SMCR = 0;							//default value
	//TIMx->ETR = 0;							//'0'->external trigger not inverted
	
	TIMx->PSCR = TIMx_PS & 0x07;			//set up the prescaler to 0x07->128:1
	TIMx->CNTR = 0; 						//TIMx->CNTRL = 0;			//reset the counter
	TIMx->ARR = 0xff;						//load up the auto reload register - 0xff -> each cycle is 0x100
	
	TIMx->SR1&=~(1<<0);						//clear UIF
	TIMx->IER|= (1<<0);						//'1'->enable overflow interrupt, '0'->disable interrupt

	//re-enable the counter
	TIMx->CR1 |= (1<<0);	
}

//return timer clicks
//execution time = 30 ticks, no optimization
uint32_t ticks(void) {
	uint32_t m;
	uint8_t f;

	//do a double read
	do {
		m = systickovf_counter;				//read the overflow counter
		f = TIMx->CNTR;						//read the least significant 16-bits
	} while (m != systickovf_counter);		//gaurd against overflow

	return (m | f) << TIMx_PS;
}

//return micros()

//return millis

//delay ms using SysTick ticks()
void systick_delayms(uint32_t ms) {
	uint32_t start_time = ticks();

	ms *= cyclesPerMillisecond();				//convert ms to ticks
	while (ticks() - start_time < ms) continue;	//wait for timer to expire
}

//delay using SysTick ticks()
void systick_delayus(uint32_t us) {
	uint32_t start_time = ticks();

	us *= cyclesPerMicrosecond();				//convert ms to ticks
	while (ticks() - start_time < us) continue;	//wait for timer to expire
}
