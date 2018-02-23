#include "tim1oc.h"								//we use tim1 output compare

//hardware configuration
#define TIMx			TIM1					//tim1
//end hardware configuration

//global defines

//empty handler
static void empty_handler(void) {
	//do nothing
}

//global variables
static void (*/*_tim1*/_isrptr_tov) (void)=empty_handler;					//tim isr handler ptr
static void (*/*_tim1*/_isrptr_oc1) (void)=empty_handler;					//tim isr handler ptr
static void (*/*_tim1*/_isrptr_oc2) (void)=empty_handler;					//tim isr handler ptr
static void (*/*_tim1*/_isrptr_oc3) (void)=empty_handler;					//tim isr handler ptr
static void (*/*_tim1*/_isrptr_oc4) (void)=empty_handler;					//tim isr handler ptr
static uint16_t _inc_oc1;
static uint16_t _inc_oc2;
static uint16_t _inc_oc3;
static uint16_t _inc_oc4;

//tim1_ovr_handler to be set by users
//tim1 isr handler
#pragma vector = TIM1_OVR_UIF_vector		//tim3 overflow interrupt
__interrupt void tim1_ovr_isr(void) {
	//process tov
	TIMx->SR1 &=~(1<<0);				//TIM1_SR_UIF=0;							//clear the flag
	/*_tim1*/_isrptr_tov();				//execute the isr handler
}

//tim1 isr handler
#pragma vector = TIM1_CAPCOM_CC1IF_vector		//tim1 output compare interrupt
__interrupt void tim1_oc14_isr(void) {
	uint16_t tmp;

	//process ccif - 1
	if (TIMx->SR1 & (1<<1)) {				//CCIF set
		TIMx->SR1 &=~(1<<1);				////clear the flag
		//update CCRx
		tmp = TIMx->CCR1H << 8;	tmp|= TIMx->CCR1L;
		tmp+= _inc_oc1;
		TIMx->CCR1H = tmp >> 8; TIMx->CCR1L = tmp;
		/*_tim1*/_isrptr_oc1();				//execute the isr handler
	}

	//process ccif - 2
	if (TIMx->SR1 & (1<<2)) {				//CCIF set
		TIMx->SR1 &=~(1<<2);				////clear the flag
		//update CCRx
		tmp = TIMx->CCR2H << 8;	tmp|= TIMx->CCR2L;
		tmp+= _inc_oc2;
		TIMx->CCR2H = tmp >> 8; TIMx->CCR2L = tmp;
		/*_tim1*/_isrptr_oc2();				//execute the isr handler
	}

	//process ccif - 3
	if (TIMx->SR1 & (1<<3)) {				//CCIF set
		TIMx->SR1 &=~(1<<3);				////clear the flag
		//update CCRx
		tmp = TIMx->CCR3H << 8;	tmp|= TIMx->CCR3L;
		tmp+= _inc_oc3;
		TIMx->CCR3H = tmp >> 8; TIMx->CCR3L = tmp;
		/*_tim1*/_isrptr_oc3();				//execute the isr handler
	}

	//process ccif - 4
	if (TIMx->SR1 & (1<<4)) {				//CCIF set
		TIMx->SR1 &=~(1<<4);				////clear the flag
		//update CCRx
		tmp = TIMx->CCR4H << 8; tmp|= TIMx->CCR4L;
		tmp+= _inc_oc4;
		TIMx->CCR4H = tmp >> 8; TIMx->CCR4L = tmp;
		/*_tim1*/_isrptr_oc4();				//execute the isr handler
	}

}

//initialize the timer
//ps = prescaler: TIM1_PS1x, TIM4_PS2x, TIM4_PS4x, TIM4_PS8x, TIM4_PS16x, TIM4_PS32x, TIM4_PS64x, TIM4_PS128x
//pr = 8-bit period, 0x00 - 0xff
void tim1_init(uint16_t ps) {
	uint16_t pr;
	
	//enable the clock to peripheral
	CLK->PCKENR1 |= CLK_PCKENR1_TIM1;		//'1'=clock enabled, '0'=clock disabled
	
	_isrptr_tov = _isrptr_oc1 = _isrptr_oc2 = _isrptr_oc3 = _isrptr_oc4 = empty_handler;				//reset the handler
	_inc_oc1 = _inc_oc2 = _inc_oc3 = _inc_oc4 = 0xffff;
	
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
	pr = 0xffff; TIMx->ARRH = (pr >> 8); TIMx->ARRL = pr;	//load up the auto reload register - msb first
	
	//set up compare channels - maximum circle
	TIMx->CCR1H = _inc_oc1 >> 8; TIMx->CCR1L = _inc_oc1;
	TIMx->CCR2H = _inc_oc2 >> 8; TIMx->CCR2L = _inc_oc2;
	TIMx->CCR3H = _inc_oc3 >> 8; TIMx->CCR3L = _inc_oc3;
	TIMx->CCR4H = _inc_oc4 >> 8; TIMx->CCR4L = _inc_oc4;
	
	TIMx->SR1&=~(1<<0);						//clear UIF
	TIMx->IER&=~(1<<0);						//'1'->enable overflow interrupt, '0'->disable interrupt
	TIMx->SR1&=~(1<<1); TIMx->IER&=~(1<<1);	//clear CCif/CCIE
	TIMx->SR1&=~(1<<2); TIMx->IER&=~(1<<2);	//clear CCif/CCIE
	TIMx->SR1&=~(1<<3); TIMx->IER&=~(1<<3);	//clear CCif/CCIE
	TIMx->SR1&=~(1<<4); TIMx->IER&=~(1<<4);	//clear CCif/CCIE

	//re-enable the counter
	TIMx->CR1 |= (1<<0);	
}

//activate user handler
void tim1_act(void (*isr_ptr)(void)) {
	_isrptr_tov = isr_ptr;						//install user handler
	
	TIMx->SR1&=~(1<<0);						//clear UIF
	TIMx->IER|= (1<<0);						//'1'->enable overflow interrupt, '0'->disable interrupt
}

//set output compare 1 period
void tim1oc1_setpr(uint16_t pr) {
	uint16_t tmp;
	
	_inc_oc1 = pr - 1;						//save the period
	tmp = TIMx->CCR1H << 8; tmp|= TIMx->CCR1L;
	tmp+=_inc_oc1;
	TIMx->CCR1H = _inc_oc1 >> 8; TIMx->CCR1L = _inc_oc1;
	
}

//activate user handler
void tim1oc1_act(void (*isr_ptr)(void)) {
	_isrptr_oc1 = isr_ptr;						//install user handler
	
	TIMx->SR1&=~(1<<1);						//clear CCIF
	TIMx->IER|= (1<<1);						//'1'->enable overflow interrupt, '0'->disable interrupt
}

//set output compare 2 period
void tim1oc2_setpr(uint16_t pr) {
	uint16_t tmp;
	
	_inc_oc2 = pr - 1;						//save the period
	tmp = TIMx->CCR2H << 8; tmp|= TIMx->CCR2L;
	tmp+=_inc_oc2;
	TIMx->CCR2H = tmp >> 8; TIMx->CCR2L = tmp;
	
}

//activate user handler
void tim1oc2_act(void (*isr_ptr)(void)) {
	_isrptr_oc2 = isr_ptr;						//install user handler
	
	TIMx->SR1&=~(1<<2);						//clear CCIF
	TIMx->IER|= (1<<2);						//'1'->enable overflow interrupt, '0'->disable interrupt
}

//set output compare 3 period
void tim1oc3_setpr(uint16_t pr) {
	uint16_t tmp;
	
	_inc_oc3 = pr - 1;						//save the period
	tmp = TIMx->CCR3H << 8; tmp|= TIMx->CCR3L;
	tmp+=_inc_oc3;
	TIMx->CCR3H = tmp >> 8; TIMx->CCR3L = tmp;
	
}

//activate user handler
void tim1oc3_act(void (*isr_ptr)(void)) {
	_isrptr_oc3 = isr_ptr;						//install user handler
	
	TIMx->SR1&=~(1<<3);						//clear CCIF
	TIMx->IER|= (1<<3);						//'1'->enable overflow interrupt, '0'->disable interrupt
}

//set output compare 4 period
void tim1oc4_setpr(uint16_t pr) {
	uint16_t tmp;
	
	_inc_oc4 = pr - 1;						//save the period
	tmp = TIMx->CCR4H << 8; tmp|= TIMx->CCR4L;
	tmp+=_inc_oc4;
	TIMx->CCR4H = tmp >> 8; TIMx->CCR4L = tmp;
	
}

//activate user handler
void tim1oc4_act(void (*isr_ptr)(void)) {
	_isrptr_oc4 = isr_ptr;						//install user handler
	
	TIMx->SR1&=~(1<<4);						//clear CCIF
	TIMx->IER|= (1<<4);						//'1'->enable overflow interrupt, '0'->disable interrupt
}
	