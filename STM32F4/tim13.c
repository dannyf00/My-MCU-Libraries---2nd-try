#include "tim13.h"					//using timer output compare channels as timer

//hardware configuration
//end hardware configuration

//global defines
#define TIMx							TIM13
#define TIMx_IRQn						TIM8_UP_TIM13_IRQn

//empty handler
static void empty_handler(void) {
	//do nothing here
}

//global variables
static void (* _tim_isrptr)(void)=empty_handler;				//tim4_ptr pointing to empty_handler by default

//isr for timer1 capture / compare
void TIM8_UP_TIM13_IRQHandler(void) {
	TIMx->SR &=~TIM_SR_UIF;		//clear the flag
	_tim_isrptr();				//execute user handler
}

//initialize tim4 to use compare channels as timers
//16-bit prescaler. 32-bit used for compatability
void tim13_init(uint32_t ps) {
	//route the clock to timer
	RCC->APB1ENR |= RCC_APB1ENR_TIM13EN;

	//source from internal clock -> disable slave mode
	TIMx->SMCR &=~TIM_SMCR_SMS;			//clear sms->use internal clock

	//stop the timer to configure it
	TIMx->CR1 &=~TIM_CR1_CEN;			//clear cen. 0=disable the timer, 1=enable the timer
	TIMx->CR1 &=~TIM_CR1_CKD;			//clear CKD0..1. 0b00->1x clock; 0b01->2:1 clock, 0b10->4:1 clk; 0b11->reserved
	TIMx->CR1 &=~TIM_CR1_DIR;			//clear DIR bit. 0=upcounter, 1=downcounter
	TIMx->CR1 &=~TIM_CR1_OPM;			//clear opm bit. 0=periodic timer, 1=one-shot timer
	//or to simply zero the register
	//TIMx->CR1 = 0;						//much easier

	//clear the status register bits for capture / compare flags
	TIMx->SR &=~(TIM_SR_CC1IF | TIM_SR_CC2IF | TIM_SR_CC3IF | TIM_SR_CC4IF | TIM_SR_UIF);
	//disable the interrupt by clearing the enable bits
	TIMx->DIER &=~(TIM_DIER_CC1IE | TIM_DIER_CC2IE | TIM_DIER_CC3IE | TIM_DIER_CC4IE | TIM_DIER_UIE);

	//set the prescaler
	TIMx->PSC = ps - 1;					//set the prescaler
	TIMx->RCR = 0;						//repetition counter = 0 (=no repetition)
	TIMx->ARR = -1;						//auto reload register / period = 0; - need to change for downcounters
	TIMx->CNT = 0;						//reset the counter

	//enable the timer.
	TIMx->CR1 |= TIM_CR1_CEN;			//enable the timer
}

//set tim4_oc1 period
//pr is 16-bit. 32-bit used for compatability;
void tim13_setpr(uint32_t pr) {
	//save the period value
	TIMx->ARR = pr - 1;

	//clear the flag
	//TIMx->SR &=~TIM_SR_CC1IF;			//clear the interrupt flag
	//TIMx->DIER &=~TIM_DIER_CC1IE;		//disable the isr
}

//install user handler
void tim13_act(void (*isr_ptr)(void)) {
	NVIC_DisableIRQ(TIMx_IRQn);		//disable irq

	_tim_isrptr = isr_ptr;			//install user handler

	//clear the flag
	TIMx->SR &=~TIM_SR_UIF;			//clear the interrupt flag
	TIMx->DIER |= TIM_DIER_UIE;		//enable the isr

	NVIC_EnableIRQ(TIMx_IRQn);		//enable irq
	//priorities not set -> default values used.
}
