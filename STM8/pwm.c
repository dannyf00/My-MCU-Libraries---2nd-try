#include "pwm.h"				//we use pwm

//reset the pwm
//configure TIM1/CCP1..4
void pwm1_init(uint16_t TxCCP_PS, uint16_t TxCCP_PR) {
	//configure the time base: as counter, top at CxCCP_PR-1
	//enable the clock to peripheral
	CLK->PCKENR1 |= CLK_PCKENR1_TIM1;			//'1'=clock enabled, '0'=clock disabled

	//stop the timer
	TIM1->CR1 &=~(1<<0);					//stop the timer
	
	//set up the timer
	TIM1->CR1 = (1<<7) |					//'1'->enable auto reload buffer
	  			(0<<5) |					//'0'->edge aligned. 1..3->center aligned
				(0<<4) |					//'0'->up counter, '1' downcounter
				(0<<3) |					//'0'->continuous mode, '1'->one pulse mode
				(0<<2) |					//'0'-> update enable source
				(0<<1) |					//'0'-> update enabled
				(0<<0);						//'0'->counter disabled
	TIM1->CR2 = 0;							//default value
	TIM1->SMCR = 0;							//default value
	TIM1->ETR = 0;							//'0'->external trigger not inverted
	TIM1->RCR = 0;							//repeatition counter = 0
	
	TIM1->PSCRH = (TxCCP_PS-1) >> 8; TIM1->PSCRL = (TxCCP_PS-1);	//set up the prescaler - msb first
	TIM1->ARRH  = (TxCCP_PR-1) >> 8; TIM1->ARRL  = (TxCCP_PR-1);	//load up the auto reload register - msb first
	TIM1->CNTRH = 0; TIM1->CNTRL = 0;			//reset the counter
	
	TIM1->SR1&=~(0xff);						//clear UIF
	TIM1->IER&=~(0xff);						//'1'->enable overflow interrupt, '0'->disable interrupt

	//configure output compare
	TIM1->CCMR1 = 	(0<<7) |				//1->clear enabled; 0->clear not enabled
					(7<<4) |				//6->pwm mode 1, 7->pwm mode 2
					(1<<3) |				//0->output preload disabled, 1->output preload enabled
					(0<<2) |				//0->normal operation, 1->enabled output compare fast
					(0<<0) |				//0->output compare as output pin, 1->CC1 as input, 2->CC! as input, 3->CC1 as input
					0x00;
	TIM1->CCER1 = 	(TIM1->CCER1 &~0x0f) |
					(0<<3) |				//1->CC1N active high, 0->CC1N active low
					(0<<2) |				//1->CC1N enabled, 0->CC1N disabled
					(1<<1) |				//0->CC1 normal polarity, 1->CC1 reverse polarity
					(1<<0) |				//1->enable CC1, 0->disable CC1
					0x00;
	TIM1->CCR1H = TIM1->CCR1L = 0;			//0%duty cycle
	
	TIM1->CCMR2 = 	(0<<7) |				//1->clear enabled; 0->clear not enabled
					(7<<4) |				//6->pwm mode 1, 7->pwm mode 2
					(1<<3) |				//0->output preload disabled, 1->output preload enabled
					(0<<2) |				//0->normal operation, 1->enabled output compare fast
					(0<<0) |				//0->output compare as output pin, 1->CC1 as input, 2->CC! as input, 3->CC1 as input
					0x00;
	TIM1->CCER1 = 	(TIM1->CCER1 &~0xf0) |
					(0<<7) |				//1->CC1N active high, 0->CC1N active low
					(0<<6) |				//1->CC1N enabled, 0->CC1N disabled
					(1<<5) |				//0->CC1 normal polarity, 1->CC1 reverse polarity
					(1<<4) |				//1->enable CC1, 0->disable CC1
					0x00;
	TIM1->CCR2H = TIM1->CCR2L = 0;			//0%duty cycle
	
	TIM1->CCMR3 = 	(0<<7) |				//1->clear enabled; 0->clear not enabled
					(7<<4) |				//6->pwm mode 1, 7->pwm mode 2
					(1<<3) |				//0->output preload disabled, 1->output preload enabled
					(0<<2) |				//0->normal operation, 1->enabled output compare fast
					(0<<0) |				//0->output compare as output pin, 1->CC1 as input, 2->CC! as input, 3->CC1 as input
					0x00;
	TIM1->CCER2 = 	(TIM1->CCER2 &~0x0f) |
					(0<<3) |				//1->CC1N active high, 0->CC1N active low
					(0<<2) |				//1->CC1N enabled, 0->CC1N disabled
					(1<<1) |				//0->CC1 normal polarity, 1->CC1 reverse polarity
					(1<<0) |				//1->enable CC1, 0->disable CC1
					0x00;
	TIM1->CCR3H = TIM1->CCR3L = 0;			//0%duty cycle
	
	TIM1->CCMR4 = 	(0<<7) |				//1->clear enabled; 0->clear not enabled
					(7<<4) |				//6->pwm mode 1, 7->pwm mode 2
					(1<<3) |				//0->output preload disabled, 1->output preload enabled
					(0<<2) |				//0->normal operation, 1->enabled output compare fast
					(0<<0) |				//0->output compare as output pin, 1->CC1 as input, 2->CC! as input, 3->CC1 as input
					0x00;
	TIM1->CCER2 = 	(TIM1->CCER2 &~0xf0) |
					(0<<7) |				//1->CC1N active high, 0->CC1N active low
					(0<<6) |				//1->CC1N enabled, 0->CC1N disabled
					(1<<5) |				//0->CC1 normal polarity, 1->CC1 reverse polarity
					(1<<4) |				//1->enable CC1, 0->disable CC1
					0x00;
	TIM1->CCR4H = TIM1->CCR4L = 0;			//0%duty cycle
	
	TIM1->EGR = 0xff;						//force an event generation so new prescaler can take effect
	TIM1->BKR |= (1<<7);					//1->set main-output-enable bit, 0->reset MOE (main-output-enable) bit
	//re-enable the counter
	TIM1->CR1 |= (1<<0);	

}
	
//configure TIM2/CCP1..4
void pwm2_init(uint16_t TxCCP_PS, uint16_t TxCCP_PR) {
	//configure the time base: as counter, top at CxCCP_PR-1
	//enable the clock to peripheral
	CLK->PCKENR1 |= CLK_PCKENR1_TIM2;			//'1'=clock enabled, '0'=clock disabled

	//stop the timer
	TIM2->CR1 &=~(1<<0);					//stop the timer
	
	//set up the timer
	TIM2->CR1 = (1<<7) |					//'1'->enable auto reload buffer
	  			(0<<5) |					//'0'->edge aligned. 1..3->center aligned
				(0<<4) |					//'0'->up counter, '1' downcounter
				(0<<3) |					//'0'->continuous mode, '1'->one pulse mode
				(0<<2) |					//'0'-> update enable source
				(0<<1) |					//'0'-> update enabled
				(0<<0);						//'0'->counter disabled
	//TIM2->CR2 = 0;							//default value
	//TIM2->SMCR = 0;							//default value
	//TIM2->ETR = 0;							//'0'->external trigger not inverted
	//TIM2->RCR = 0;							//repeatition counter = 0
	
	/*TIM2->PSCRH = (TxCCP_PS-1) >> 8; */TIM2->PSCR/*L*/ = (TxCCP_PS-1);	//set up the prescaler - msb first - lowest 4-bit only
	TIM2->ARRH  = (TxCCP_PR-1) >> 8; TIM2->ARRL  = (TxCCP_PR-1);	//load up the auto reload register - msb first
	TIM2->CNTRH = 0; TIM2->CNTRL = 0;			//reset the counter
	
	TIM2->SR1&=~(0xff);						//clear UIF
	TIM2->IER&=~(0xff);						//'1'->enable overflow interrupt, '0'->disable interrupt

	//configure output compare
#if defined(TIM2_CCMR1_RESET_VALUE)
	TIM2->CCMR1 = 	(0<<7) |				//1->clear enabled; 0->clear not enabled
					(6<<4) |				//6->pwm mode 1, 7->pwm mode 2
					(1<<3) |				//0->output preload disabled, 1->output preload enabled
					(0<<2) |				//0->normal operation, 1->enabled output compare fast
					(0<<0) |				//0->output compare as output pin, 1->CC1 as input, 2->CC! as input, 3->CC1 as input
					0x00;
	TIM2->CCER1 = 	(TIM2->CCER1 &~0x0f) |
					(0<<3) |				//1->CC1N active high, 0->CC1N active low
					(0<<2) |				//1->CC1N enabled, 0->CC1N disabled
					(1<<1) |				//0->CC1 normal polarity, 1->CC1 reverse polarity
					(1<<0) |				//1->enable CC1, 0->disable CC1
					0x00;
	TIM2->CCR1H = TIM2->CCR1L = 0;			//0%duty cycle
#endif
	
#if defined(TIM2_CCMR2_RESET_VALUE)
	TIM2->CCMR2 = 	(0<<7) |				//1->clear enabled; 0->clear not enabled
					(6<<4) |				//6->pwm mode 1, 7->pwm mode 2
					(1<<3) |				//0->output preload disabled, 1->output preload enabled
					(0<<2) |				//0->normal operation, 1->enabled output compare fast
					(0<<0) |				//0->output compare as output pin, 1->CC1 as input, 2->CC! as input, 3->CC1 as input
					0x00;
	TIM2->CCER1 = 	(TIM2->CCER1 &~0xf0) |
					(0<<7) |				//1->CC1N active high, 0->CC1N active low
					(0<<6) |				//1->CC1N enabled, 0->CC1N disabled
					(1<<5) |				//0->CC1 normal polarity, 1->CC1 reverse polarity
					(1<<4) |				//1->enable CC1, 0->disable CC1
					0x00;
	TIM2->CCR2H = TIM2->CCR2L = 0;			//0%duty cycle
#endif
	
#if defined(TIM2_CCMR3_RESET_VALUE)
	TIM2->CCMR3 = 	(0<<7) |				//1->clear enabled; 0->clear not enabled
					(6<<4) |				//6->pwm mode 1, 7->pwm mode 2
					(1<<3) |				//0->output preload disabled, 1->output preload enabled
					(0<<2) |				//0->normal operation, 1->enabled output compare fast
					(0<<0) |				//0->output compare as output pin, 1->CC1 as input, 2->CC! as input, 3->CC1 as input
					0x00;
	TIM2->CCER2 = 	(TIM2->CCER2 &~0x0f) |
					(0<<3) |				//1->CC1N active high, 0->CC1N active low
					(0<<2) |				//1->CC1N enabled, 0->CC1N disabled
					(1<<1) |				//0->CC1 normal polarity, 1->CC1 reverse polarity
					(1<<0) |				//1->enable CC1, 0->disable CC1
					0x00;
	TIM2->CCR3H = TIM2->CCR3L = 0;			//0%duty cycle
#endif
	
#if defined(TIM2_CCMR4_RESET_VALUE)
	TIM2->CCMR4 = 	(0<<7) |				//1->clear enabled; 0->clear not enabled
					(6<<4) |				//6->pwm mode 1, 7->pwm mode 2
					(1<<3) |				//0->output preload disabled, 1->output preload enabled
					(0<<2) |				//0->normal operation, 1->enabled output compare fast
					(0<<0) |				//0->output compare as output pin, 1->CC1 as input, 2->CC! as input, 3->CC1 as input
					0x00;
	TIM2->CCER2 = 	(TIM2->CCER2 &~0xf0) |
					(0<<7) |				//1->CC1N active high, 0->CC1N active low
					(0<<6) |				//1->CC1N enabled, 0->CC1N disabled
					(1<<5) |				//0->CC1 normal polarity, 1->CC1 reverse polarity
					(1<<4) |				//1->enable CC1, 0->disable CC1
					0x00;
	TIM2->CCR4H = TIM2->CCR4L = 0;			//0%duty cycle
#endif
	
	TIM2->EGR = 0xff;						//force an event generation so new prescaler can take effect
	//TIM2->BKR |= (1<<7);					//1->set main-output-enable bit, 0->reset MOE (main-output-enable) bit
	//re-enable the counter
	TIM2->CR1 |= (1<<0);	

}
	
//configure TIM3/CCP1..4
void pwm3_init(uint16_t TxCCP_PS, uint16_t TxCCP_PR){
	//configure the time base: as counter, top at CxCCP_PR-1
	//enable the clock to peripheral
	CLK->PCKENR1 |= CLK_PCKENR1_TIM3;			//'1'=clock enabled, '0'=clock disabled

	//stop the timer
	TIM3->CR1 &=~(1<<0);					//stop the timer
	
	//set up the timer
	TIM3->CR1 = (1<<7) |					//'1'->enable auto reload buffer
	  			(0<<5) |					//'0'->edge aligned. 1..3->center aligned
				(0<<4) |					//'0'->up counter, '1' downcounter
				(0<<3) |					//'0'->continuous mode, '1'->one pulse mode
				(0<<2) |					//'0'-> update enable source
				(0<<1) |					//'0'-> update enabled
				(0<<0);						//'0'->counter disabled
	//TIM3->CR2 = 0;							//default value
	//TIM3->SMCR = 0;							//default value
	//TIM3->ETR = 0;							//'0'->external trigger not inverted
	//TIM3->RCR = 0;							//repeatition counter = 0
	
	/*TIM3->PSCRH = (TxCCP_PS-1) >> 8; */TIM3->PSCR/*L*/ = (TxCCP_PS-1);	//set up the prescaler - msb first - lowest 4-bit only
	TIM3->ARRH  = (TxCCP_PR-1) >> 8; TIM3->ARRL  = (TxCCP_PR-1);	//load up the auto reload register - msb first
	TIM3->CNTRH = 0; TIM3->CNTRL = 0;			//reset the counter
	
	TIM3->SR1&=~(0xff);						//clear UIF
	TIM3->IER&=~(0xff);						//'1'->enable overflow interrupt, '0'->disable interrupt

	//configure output compare
#if defined(TIM3_CCMR1_RESET_VALUE)
	TIM3->CCMR1 = 	(0<<7) |				//1->clear enabled; 0->clear not enabled
					(6<<4) |				//6->pwm mode 1, 7->pwm mode 2
					(1<<3) |				//0->output preload disabled, 1->output preload enabled
					(0<<2) |				//0->normal operation, 1->enabled output compare fast
					(0<<0) |				//0->output compare as output pin, 1->CC1 as input, 2->CC! as input, 3->CC1 as input
					0x00;
	TIM3->CCER1 = 	(TIM3->CCER1 &~0x0f) |
					(0<<3) |				//1->CC1N active high, 0->CC1N active low
					(0<<2) |				//1->CC1N enabled, 0->CC1N disabled
					(1<<1) |				//0->CC1 normal polarity, 1->CC1 reverse polarity
					(1<<0) |				//1->enable CC1, 0->disable CC1
					0x00;
	TIM3->CCR1H = TIM3->CCR1L = 0;			//0%duty cycle
#endif
	
#if defined(TIM3_CCMR2_RESET_VALUE)
	TIM3->CCMR2 = 	(0<<7) |				//1->clear enabled; 0->clear not enabled
					(6<<4) |				//6->pwm mode 1, 7->pwm mode 2
					(1<<3) |				//0->output preload disabled, 1->output preload enabled
					(0<<2) |				//0->normal operation, 1->enabled output compare fast
					(0<<0) |				//0->output compare as output pin, 1->CC1 as input, 2->CC! as input, 3->CC1 as input
					0x00;
	TIM3->CCER1 = 	(TIM3->CCER1 &~0xf0) |
					(0<<7) |				//1->CC1N active high, 0->CC1N active low
					(0<<6) |				//1->CC1N enabled, 0->CC1N disabled
					(1<<5) |				//0->CC1 normal polarity, 1->CC1 reverse polarity
					(1<<4) |				//1->enable CC1, 0->disable CC1
					0x00;
	TIM3->CCR2H = TIM3->CCR2L = 0;			//0%duty cycle
#endif
	
#if defined(TIM3_CCMR3_RESET_VALUE)
	TIM3->CCMR3 = 	(0<<7) |				//1->clear enabled; 0->clear not enabled
					(6<<4) |				//6->pwm mode 1, 7->pwm mode 2
					(1<<3) |				//0->output preload disabled, 1->output preload enabled
					(0<<2) |				//0->normal operation, 1->enabled output compare fast
					(0<<0) |				//0->output compare as output pin, 1->CC1 as input, 2->CC! as input, 3->CC1 as input
					0x00;
	TIM3->CCER2 = 	(TIM3->CCER2 &~0x0f) |
					(0<<3) |				//1->CC1N active high, 0->CC1N active low
					(0<<2) |				//1->CC1N enabled, 0->CC1N disabled
					(1<<1) |				//0->CC1 normal polarity, 1->CC1 reverse polarity
					(1<<0) |				//1->enable CC1, 0->disable CC1
					0x00;
	TIM3->CCR3H = TIM3->CCR3L = 0;			//0%duty cycle
#endif
	
#if defined(TIM3_CCMR4_RESET_VALUE)
	TIM3->CCMR4 = 	(0<<7) |				//1->clear enabled; 0->clear not enabled
					(6<<4) |				//6->pwm mode 1, 7->pwm mode 2
					(1<<3) |				//0->output preload disabled, 1->output preload enabled
					(0<<2) |				//0->normal operation, 1->enabled output compare fast
					(0<<0) |				//0->output compare as output pin, 1->CC1 as input, 2->CC! as input, 3->CC1 as input
					0x00;
	TIM3->CCER2 = 	(TIM3->CCER2 &~0xf0) |
					(0<<7) |				//1->CC1N active high, 0->CC1N active low
					(0<<6) |				//1->CC1N enabled, 0->CC1N disabled
					(1<<5) |				//0->CC1 normal polarity, 1->CC1 reverse polarity
					(1<<4) |				//1->enable CC1, 0->disable CC1
					0x00;
	TIM3->CCR4H = TIM3->CCR4L = 0;			//0%duty cycle
#endif
	
	TIM3->EGR = 0xff;						//force an event generation so new prescaler can take effect
	//TIM3->BKR |= (1<<7);					//1->set main-output-enable bit, 0->reset MOE (main-output-enable) bit
	//re-enable the counter
	TIM3->CR1 |= (1<<0);	

}

#if defined(TIM5)
//configure TIM5/CCP1..4 - if available
void pwm5_init(uint16_t TxCCP_PS, uint16_t TxCCP_PR){
	//configure the time base: as counter, top at CxCCP_PR-1
	//enable the clock to peripheral
	CLK->PCKENR1 |= CLK_PCKENR1_TIM5;			//'1'=clock enabled, '0'=clock disabled

	//stop the timer
	TIM5->CR1 &=~(1<<0);					//stop the timer
	
	//set up the timer
	TIM5->CR1 = (1<<7) |					//'1'->enable auto reload buffer
	  			(0<<5) |					//'0'->edge aligned. 1..3->center aligned
				(0<<4) |					//'0'->up counter, '1' downcounter
				(0<<3) |					//'0'->continuous mode, '1'->one pulse mode
				(0<<2) |					//'0'-> update enable source
				(0<<1) |					//'0'-> update enabled
				(0<<0);						//'0'->counter disabled
	//TIM5->CR2 = 0;							//default value
	//TIM5->SMCR = 0;							//default value
	//TIM5->ETR = 0;							//'0'->external trigger not inverted
	//TIM5->RCR = 0;							//repeatition counter = 0
	
	/*TIM5->PSCRH = (TxCCP_PS-1) >> 8; */TIM5->PSCR/*L*/ = (TxCCP_PS-1);	//set up the prescaler - msb first - lowest 4-bit only
	TIM5->ARRH  = (TxCCP_PR-1) >> 8; TIM5->ARRL  = (TxCCP_PR-1);	//load up the auto reload register - msb first
	TIM5->CNTRH = 0; TIM5->CNTRL = 0;			//reset the counter
	
	TIM5->SR1&=~(0xff);						//clear UIF
	TIM5->IER&=~(0xff);						//'1'->enable overflow interrupt, '0'->disable interrupt

	//configure output compare
#if defined(TIM5_CCMR1_RESET_VALUE)
	TIM5->CCMR1 = 	(0<<7) |				//1->clear enabled; 0->clear not enabled
					(6<<4) |				//6->pwm mode 1, 7->pwm mode 2
					(1<<3) |				//0->output preload disabled, 1->output preload enabled
					(0<<2) |				//0->normal operation, 1->enabled output compare fast
					(0<<0) |				//0->output compare as output pin, 1->CC1 as input, 2->CC! as input, 3->CC1 as input
					0x00;
	TIM5->CCER1 = 	(TIM5->CCER1 &~0x0f) |
					(0<<3) |				//1->CC1N active high, 0->CC1N active low
					(0<<2) |				//1->CC1N enabled, 0->CC1N disabled
					(1<<1) |				//0->CC1 normal polarity, 1->CC1 reverse polarity
					(1<<0) |				//1->enable CC1, 0->disable CC1
					0x00;
	TIM5->CCR1H = TIM5->CCR1L = 0;			//0%duty cycle
#endif
	
#if defined(TIM5_CCMR2_RESET_VALUE)
	TIM5->CCMR2 = 	(0<<7) |				//1->clear enabled; 0->clear not enabled
					(6<<4) |				//6->pwm mode 1, 7->pwm mode 2
					(1<<3) |				//0->output preload disabled, 1->output preload enabled
					(0<<2) |				//0->normal operation, 1->enabled output compare fast
					(0<<0) |				//0->output compare as output pin, 1->CC1 as input, 2->CC! as input, 3->CC1 as input
					0x00;
	TIM5->CCER1 = 	(TIM5->CCER1 &~0xf0) |
					(0<<7) |				//1->CC1N active high, 0->CC1N active low
					(0<<6) |				//1->CC1N enabled, 0->CC1N disabled
					(1<<5) |				//0->CC1 normal polarity, 1->CC1 reverse polarity
					(1<<4) |				//1->enable CC1, 0->disable CC1
					0x00;
	TIM5->CCR2H = TIM5->CCR2L = 0;			//0%duty cycle
#endif
	
#if defined(TIM5_CCMR3_RESET_VALUE)
	TIM5->CCMR3 = 	(0<<7) |				//1->clear enabled; 0->clear not enabled
					(6<<4) |				//6->pwm mode 1, 7->pwm mode 2
					(1<<3) |				//0->output preload disabled, 1->output preload enabled
					(0<<2) |				//0->normal operation, 1->enabled output compare fast
					(0<<0) |				//0->output compare as output pin, 1->CC1 as input, 2->CC! as input, 3->CC1 as input
					0x00;
	TIM5->CCER2 = 	(TIM5->CCER2 &~0x0f) |
					(0<<3) |				//1->CC1N active high, 0->CC1N active low
					(0<<2) |				//1->CC1N enabled, 0->CC1N disabled
					(1<<1) |				//0->CC1 normal polarity, 1->CC1 reverse polarity
					(1<<0) |				//1->enable CC1, 0->disable CC1
					0x00;
	TIM5->CCR3H = TIM5->CCR3L = 0;			//0%duty cycle
#endif
	
#if defined(TIM5_CCMR4_RESET_VALUE)
	TIM5->CCMR4 = 	(0<<7) |				//1->clear enabled; 0->clear not enabled
					(6<<4) |				//6->pwm mode 1, 7->pwm mode 2
					(1<<3) |				//0->output preload disabled, 1->output preload enabled
					(0<<2) |				//0->normal operation, 1->enabled output compare fast
					(0<<0) |				//0->output compare as output pin, 1->CC1 as input, 2->CC! as input, 3->CC1 as input
					0x00;
	TIM5->CCER2 = 	(TIM5->CCER2 &~0xf0) |
					(0<<7) |				//1->CC1N active high, 0->CC1N active low
					(0<<6) |				//1->CC1N enabled, 0->CC1N disabled
					(1<<5) |				//0->CC1 normal polarity, 1->CC1 reverse polarity
					(1<<4) |				//1->enable CC1, 0->disable CC1
					0x00;
	TIM5->CCR4H = TIM5->CCR4L = 0;			//0%duty cycle
#endif
	
	TIM5->EGR = 0xff;						//force an event generation so new prescaler can take effect
	//TIM5->BKR |= (1<<7);					//1->set main-output-enable bit, 0->reset MOE (main-output-enable) bit
	//re-enable the counter
	TIM5->CR1 |= (1<<0);	

}
#endif

