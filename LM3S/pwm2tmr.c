#include "pwm2tmr.h"					//we use pwm as timers

//use pwm cmpa/b interrupts as timer

//global defines

//global variables

//empty handler
void empty_handler(void) {
	//do nothing here
}

//isr function pointers for overflow / zero
void (*_isrptr_pwm0)(void) = empty_handler;
void (*_isrptr_pwm1)(void) = empty_handler;
void (*_isrptr_pwm2)(void) = empty_handler;

volatile uint32_t _pr_pwm0=0xffff;	//period for pwm0
volatile uint32_t _pr_pwm1=0xffff;	//period for pwm0
volatile uint32_t _pr_pwm2=0xffff;	//period for pwm0

//pwm0 interrupt
void PWMGen0_IRQHandler(void) {
	//clear the flag
	//PWM->ISC |= (1<<0);				//1->clear the flag, 0->no effect

	//zero update isr / overflow
	if (PWMGEN0->ISC & (1<<0)) {
		PWMGEN0->ISC |= (1<<0);		//1->clear cmpa flag, 0->no effect
		//PWMGEN0->CMPA+= _pr_pwm0a;	//point to the next matchpoint - downcounter
		_isrptr_pwm0();
	}

}

//pwm0 interrupt
void PWMGen1_IRQHandler(void) {
	//clear the flag
	//PWM->ISC |= (1<<0);				//1->clear the flag, 0->no effect

	//zero update isr / overflow
	if (PWMGEN1->ISC & (1<<0)) {
		PWMGEN1->ISC |= (1<<0);		//1->clear cmpa flag, 0->no effect
		//PWMGEN1->CMPA+= _pr_pwm0a;	//point to the next matchpoint - downcounter
		_isrptr_pwm1();
	}

}

//pwm0 interrupt
void PWMGen2_IRQHandler(void) {
	//clear the flag
	//PWM->ISC |= (1<<0);				//1->clear the flag, 0->no effect

	//zero update isr / overflow
	if (PWMGEN2->ISC & (1<<0)) {
		PWMGEN2->ISC |= (1<<0);		//1->clear cmpa flag, 0->no effect
		//PWMGEN2->CMPA+= _pr_pwm0a;	//point to the next matchpoint - downcounter
		_isrptr_pwm2();
	}

}

//reset the module
//pwm output disabled
//down counter
//CompareDown interrupt is enabled - all others are disabled
//16-bit periods, 3-bit prescaler
void pwm0tmr_init(uint32_t ps, uint32_t pr) {
	//initialize the variables
	_isrptr_pwm0 = empty_handler;
	//_pr_pwm0a=0xffff;

	//route the clock
	SYSCTL->RCGC0 |= (1<<20);			//1->enable pwm clock, 0-.disable pwm clock

	//disable output
	PWM->ENABLE &=~(1<<0);				//1->enable pwm output, 0->disable pwm output
	//configure pwm timebase
	PWMGEN0->CTL =	(0<<5) |			//1->update cmpb immediately, 0->update on roll-over
					(0<<4) |			//1->update cmpa immediately, 0->update on roll-over
					(0<<3) |			//1->update load immediately, 0->update on roll-over
					(0<<2) |			//1->timer stops on debug, 0->timer continues to count
					(0<<1) |			//1->up/down counter, 0->down counter
					(0<<0) |			//1->enable pwm, 0->disable pwm
					0x00;
	//set prescaler
	SYSCTL->RCC = (SYSCTL->RCC &~(0x07<<17)) | ((ps & 0x07) << 17);
	//for PS=1, disable USEPWMDIV in RCC
	//1->enable prescaler, 0->disable prescaler (=prescaler 1:1)
	if (ps == PWM_PS1x) SYSCTL->RCC &=~(1<<20);
	else SYSCTL->RCC|= (1<<20);

	//load at 0xffff
	PWMGEN0->LOAD = pr - 1;				//top at 0xffff
	//PWMGEN0->COUNT= 0;					//count at 0
	//PWMGEN0->CMPA = _pr_pwm0a = (pr - 1);;
	//PWMGEN0->CMPB = 0;

	//set up the interrupts / remain disabled
	PWM->ISC |= (1<<0);					//1->clera the interrupt, 0->no effect
	PWM->INTEN &=~((1<<1) | (1<<0));				//1->pwm interrupt enabled, 0->pwm0 interrupt disabled
	//enable interrupt on the down match only
	//PWMGEN0->INTEN =(0<<8) |			//0->no adc trigger, 1..3f: some forms of adc trigger
	//				(0<<5) |			//1->cmpb down interrupt enabled, 0->cmpb down interrupt disabled
	//				(0<<4) |			//1->cmpb up interrupt enabled, 0->cmpb up interrupt disabled
	//				(0<<3) |			//1->cmpa down interrupt enabled, 0->cmpa down interrupt disabled
	//				(0<<2) |			//1->cmpa up interrupt enabled, 0->cmpa up interrupt disabled
	//				(0<<1) |			//1->load interrupt enabled, 0->load interrupt disabled
	//				(0<<0) |			//1->zero interrupt enabled, 0->zero interrupt disabled
	//				0x00;
	//PWMGEN0->INTEN &=~(1<<3);			//0->disable cmpa down interrupt
	//disable all but cmpb down interrupts
	PWMGEN0->INTEN &= (1<<0);			//->disable all but zero update interrupt

	//enable the timebase
	PWMGEN0->CTL|= (1<<0);				//1->enable pwm, 0->disable pwm
}

//set up isr user handler
void pwm0tmr_act(void (*isrptr)(void)) {
	_isrptr_pwm0 = isrptr;

	//set up the interrupts / remain disabled
	PWM->ISC |= (1<<0);					//1->clear the interrupt, 0->no effect
	//enable interrupt on the down match only
	PWMGEN0->INTEN|=//(0<<8) |			//0->no adc trigger, 1..3f: some forms of adc trigger
					//(0<<5) |			//1->cmpb down interrupt enabled, 0->cmpb down interrupt disabled
					//(0<<4) |			//1->cmpb up interrupt enabled, 0->cmpb up interrupt disabled
					//(1<<3) |			//1->cmpa down interrupt enabled, 0->cmpa down interrupt disabled
					//(0<<2) |			//1->cmpa up interrupt enabled, 0->cmpa up interrupt disabled
					//(0<<1) |			//1->load interrupt enabled, 0->load interrupt disabled
					(1<<0) |			//1->zero interrupt enabled, 0->zero interrupt disabled
					0x00;
	PWM->INTEN |= (1<<0);				//1->pwm interrupt enabled, 0->pwm0 interrupt disabled
	//register pwm interrupt
	NVIC_EnableIRQ(PWMGen0_IRQn);		//enable interrupt
}

//reset the module
//pwm output disabled
//down counter
//CompareDown interrupt is enabled - all others are disabled
//16-bit periods, 3-bit prescaler
void pwm1tmr_init(uint32_t ps, uint32_t pr) {
	//initialize the variables
	_isrptr_pwm1 = empty_handler;
	//_pr_pwm0a=0xffff;

	//route the clock
	SYSCTL->RCGC0 |= (1<<20);			//1->enable pwm clock, 0-.disable pwm clock

	//disable output
	PWM->ENABLE &=~((1<<3) | (1<<2));				//1->enable pwm output, 0->disable pwm output
	//configure pwm timebase
	PWMGEN1->CTL =	(0<<5) |			//1->update cmpb immediately, 0->update on roll-over
					(0<<4) |			//1->update cmpa immediately, 0->update on roll-over
					(0<<3) |			//1->update load immediately, 0->update on roll-over
					(0<<2) |			//1->timer stops on debug, 0->timer continues to count
					(0<<1) |			//1->up/down counter, 0->down counter
					(0<<0) |			//1->enable pwm, 0->disable pwm
					0x00;
	//set prescaler
	SYSCTL->RCC = (SYSCTL->RCC &~(0x07<<17)) | ((ps & 0x07) << 17);
	//for PS=1, disable USEPWMDIV in RCC
	//1->enable prescaler, 0->disable prescaler (=prescaler 1:1)
	if (ps == PWM_PS1x) SYSCTL->RCC &=~(1<<20);
	else SYSCTL->RCC|= (1<<20);

	//load at 0xffff
	PWMGEN1->LOAD = pr - 1;				//top at 0xffff
	//PWMGEN0->COUNT= 0;					//count at 0
	//PWMGEN0->CMPA = _pr_pwm0a = (pr - 1);;
	//PWMGEN0->CMPB = 0;

	//set up the interrupts / remain disabled
	PWM->ISC |= (1<<1);					//1->clear the interrupt, 0->no effect
	PWM->INTEN &=~(1<<1);				//1->pwm interrupt enabled, 0->pwm0 interrupt disabled
	//enable interrupt on the down match only
	//PWMGEN0->INTEN =(0<<8) |			//0->no adc trigger, 1..3f: some forms of adc trigger
	//				(0<<5) |			//1->cmpb down interrupt enabled, 0->cmpb down interrupt disabled
	//				(0<<4) |			//1->cmpb up interrupt enabled, 0->cmpb up interrupt disabled
	//				(0<<3) |			//1->cmpa down interrupt enabled, 0->cmpa down interrupt disabled
	//				(0<<2) |			//1->cmpa up interrupt enabled, 0->cmpa up interrupt disabled
	//				(0<<1) |			//1->load interrupt enabled, 0->load interrupt disabled
	//				(0<<0) |			//1->zero interrupt enabled, 0->zero interrupt disabled
	//				0x00;
	//PWMGEN0->INTEN &=~(1<<3);			//0->disable cmpa down interrupt
	//disable all but cmpb down interrupts
	PWMGEN1->INTEN &= (1<<0);			//->disable all but zero update interrupt

	//enable the timebase
	PWMGEN1->CTL|= (1<<0);				//1->enable pwm, 0->disable pwm
}

//set up isr user handler
void pwm1tmr_act(void (*isrptr)(void)) {
	_isrptr_pwm1 = isrptr;

	//set up the interrupts / remain disabled
	PWM->ISC |= (1<<1);					//1->clear the interrupt, 0->no effect
	//enable interrupt on the down match only
	PWMGEN1->INTEN|=//(0<<8) |			//0->no adc trigger, 1..3f: some forms of adc trigger
					//(0<<5) |			//1->cmpb down interrupt enabled, 0->cmpb down interrupt disabled
					//(0<<4) |			//1->cmpb up interrupt enabled, 0->cmpb up interrupt disabled
					//(1<<3) |			//1->cmpa down interrupt enabled, 0->cmpa down interrupt disabled
					//(0<<2) |			//1->cmpa up interrupt enabled, 0->cmpa up interrupt disabled
					//(0<<1) |			//1->load interrupt enabled, 0->load interrupt disabled
					(1<<0) |			//1->zero interrupt enabled, 0->zero interrupt disabled
					0x00;
	PWM->INTEN |= (1<<1);				//1->pwm interrupt enabled, 0->pwm0 interrupt disabled
	//register pwm interrupt
	NVIC_EnableIRQ(PWMGen1_IRQn);		//enable interrupt
}

//reset the module
//pwm output disabled
//down counter
//CompareDown interrupt is enabled - all others are disabled
//16-bit periods, 3-bit prescaler
void pwm2tmr_init(uint32_t ps, uint32_t pr) {
	//initialize the variables
	_isrptr_pwm2 = empty_handler;
	//_pr_pwm0a=0xffff;

	//route the clock
	SYSCTL->RCGC0 |= (1<<20);			//1->enable pwm clock, 0-.disable pwm clock

	//disable output
	PWM->ENABLE &=~((1<<5) | (1<<4));				//1->enable pwm output, 0->disable pwm output
	//configure pwm timebase
	PWMGEN2->CTL =	(0<<5) |			//1->update cmpb immediately, 0->update on roll-over
					(0<<4) |			//1->update cmpa immediately, 0->update on roll-over
					(0<<3) |			//1->update load immediately, 0->update on roll-over
					(0<<2) |			//1->timer stops on debug, 0->timer continues to count
					(0<<1) |			//1->up/down counter, 0->down counter
					(0<<0) |			//1->enable pwm, 0->disable pwm
					0x00;
	//set prescaler
	SYSCTL->RCC = (SYSCTL->RCC &~(0x07<<17)) | ((ps & 0x07) << 17);
	//for PS=1, disable USEPWMDIV in RCC
	//1->enable prescaler, 0->disable prescaler (=prescaler 1:1)
	if (ps == PWM_PS1x) SYSCTL->RCC &=~(1<<20);
	else SYSCTL->RCC|= (1<<20);

	//load at 0xffff
	PWMGEN2->LOAD = pr - 1;				//top at 0xffff
	//PWMGEN0->COUNT= 0;					//count at 0
	//PWMGEN0->CMPA = _pr_pwm0a = (pr - 1);;
	//PWMGEN0->CMPB = 0;

	//set up the interrupts / remain disabled
	PWM->ISC |= (1<<2);					//1->clera the interrupt, 0->no effect
	PWM->INTEN &=~(1<<2);				//1->pwm interrupt enabled, 0->pwm0 interrupt disabled
	//enable interrupt on the down match only
	//PWMGEN0->INTEN =(0<<8) |			//0->no adc trigger, 1..3f: some forms of adc trigger
	//				(0<<5) |			//1->cmpb down interrupt enabled, 0->cmpb down interrupt disabled
	//				(0<<4) |			//1->cmpb up interrupt enabled, 0->cmpb up interrupt disabled
	//				(0<<3) |			//1->cmpa down interrupt enabled, 0->cmpa down interrupt disabled
	//				(0<<2) |			//1->cmpa up interrupt enabled, 0->cmpa up interrupt disabled
	//				(0<<1) |			//1->load interrupt enabled, 0->load interrupt disabled
	//				(0<<0) |			//1->zero interrupt enabled, 0->zero interrupt disabled
	//				0x00;
	//PWMGEN0->INTEN &=~(1<<3);			//0->disable cmpa down interrupt
	//disable all but cmpb down interrupts
	PWMGEN2->INTEN &= (1<<0);			//->disable all but zero update interrupt

	//enable the timebase
	PWMGEN2->CTL|= (1<<0);				//1->enable pwm, 0->disable pwm
}

//set up isr user handler
void pwm2tmr_act(void (*isrptr)(void)) {
	_isrptr_pwm2 = isrptr;

	//set up the interrupts / remain disabled
	PWM->ISC |= (1<<2);					//1->clear the interrupt, 0->no effect
	//enable interrupt on the down match only
	PWMGEN2->INTEN|=//(0<<8) |			//0->no adc trigger, 1..3f: some forms of adc trigger
					//(0<<5) |			//1->cmpb down interrupt enabled, 0->cmpb down interrupt disabled
					//(0<<4) |			//1->cmpb up interrupt enabled, 0->cmpb up interrupt disabled
					//(1<<3) |			//1->cmpa down interrupt enabled, 0->cmpa down interrupt disabled
					//(0<<2) |			//1->cmpa up interrupt enabled, 0->cmpa up interrupt disabled
					//(0<<1) |			//1->load interrupt enabled, 0->load interrupt disabled
					(1<<0) |			//1->zero interrupt enabled, 0->zero interrupt disabled
					0x00;
	PWM->INTEN |= (1<<2);				//1->pwm interrupt enabled, 0->pwm0 interrupt disabled
	//register pwm interrupt
	NVIC_EnableIRQ(PWMGen2_IRQn);		//enable interrupt
}

