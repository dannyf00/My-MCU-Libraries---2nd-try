#include "wtimer4.h"									//use timer4

//hardware configuration
//end hardware configuration

//global defines
#define TMRx				WTIMER4					//current timer

//global variables

//empty handler
static void empty_handler(void) {
	//do nothing
}

//global variables
//user isr ptr
//those two ISRs (TIMER0A_ISR and TIMER0B_ISR) will need to be inserted in the start-up file
static void (* _isrptr_tmra)(void)=empty_handler;				//tmr_ptr pointing to empty_handler by default
static void (* _isrptr_tmrb)(void)=empty_handler;				//tmr_ptr pointing to empty_handler by default

//timera isr handler
void WTIMER4A_Handler(void) {
	TMRx->ICR |= (1<<0);							//1->clear the flag, 0->no effect
	_isrptr_tmra();									//execute user handler
}

//timerb isr handler
void WTIMER4B_Handler(void) {
	TMRx->ICR |= (1<<8);							//1->clear the flag, 0->no effect
	_isrptr_tmrb();									//execute user handler

}

//reset timer0a - split timer
//16/32-bit timer: 8-bit prescaler, 16-bit period register
void wtmr4a_init(uint32_t ps, uint32_t pr) {
	_isrptr_tmra = empty_handler;

	//route the clock
	SYSCTL->RCGCWTIMER |= (1<<4);						//1->route clock. TIMER0/1/2/3/4/5

	//stop the timer
	TMRx->CTL &=~(1<<0);							//0->disable timer, 1->enable timer
	//configure the timer, split, upcounter
	TMRx->CFG  = 0x04;								//0x00->32/64bit, 0x01->rtc, 0x02-0x03->reserved, 0x04->16/32bit split timers
	TMRx->TAMR = 	(0<<11) |							//0->legacy ops
					(0<<10) |						//0->update match register on the next cycle, 1->update match register now
					(0<< 9) |						//0->pwm interrupt disabled, 1->pwm interrupt enabled
					(0<< 8) |						//0->update load register ont he next cycle; 1->update load register now
					(0<< 7) |						//0->disable snap shot, 1->enable snap shot
					(0<< 6) |						//0->timer counts right away; 1->timer waits on trigger before counting
					(0<< 5) |						//0->match interrupt disabled, 1->match interrupt enabled
					(1<< 4) |						//0->counts down, 1->counts up
					(0<< 3) |						//0->capture / compare enabled 1->pwm enabled
					(0<< 2) |						//0->edge count for capture; 1->edge time for capture
					(0x02) |						//0x00->reserved, 0x01->one shot, 0x02->periodic, 0x03->capture
					0x00;

	//set the prescaler
	TMRx->TAPR = (ps - 1) & 0xffff;							//set the prescaler
	TMRx->TAILR= (pr - 1);							//set the top
	//reset counter
	TMRx->TAV = 0;

	//clear ISR flags, disable isr
	//disable all interrupt
	TMRx->IMR &=~(0x1f << 0);						//0->disable time-out interrupt, 1->enable time-out interrupt
	TMRx->ICR |= (0x1f << 0);						//1->clear interrupt flag, 0->no effect

	//start the timer
	TMRx->CTL |= (1<<0);							//0->disable timer, 1->enable timer
}

//activate the timera isr
void wtmr4a_act(void (*isrptr)(void)) {
	_isrptr_tmra = isrptr;
	TMRx->ICR |= (1<<0);							//1-.clera the flag, 0->no effect
	TMRx->IMR |= (1<<0);							//1->enable time-out interrupt, 0->disable it.
	NVIC_EnableIRQ(WTIMER4A_IRQn);					//use default priorities
}

//reset timer0b - split timer
//16/32-bit timer: 8-bit prescaler, 16-bit period register
void wtmr4b_init(uint32_t ps, uint32_t pr) {
	_isrptr_tmrb = empty_handler;

	//route the clock
	SYSCTL->RCGCWTIMER |= (1<<4);					//1->route clock. TIMER0/1/2/3/4/5

	//stop the timer
	TMRx->CTL &=~(1<<8);							//0->disable timer, 1->enable timer
	//configure the timer, split, upcounter
	TMRx->CFG  = 0x04;								//0x00->32/64bit, 0x01->rtc, 0x02-0x03->reserved, 0x04->16/32bit split timers
	TMRx->TBMR = 	(0<<11) |						//0->legacy ops
					(0<<10) |						//0->update match register on the next cycle, 1->update match register now
					(0<< 9) |						//0->pwm interrupt disabled, 1->pwm interrupt enabled
					(0<< 8) |						//0->update load register ont he next cycle; 1->update load register now
					(0<< 7) |						//0->disable snap shot, 1->enable snap shot
					(0<< 6) |						//0->timer counts right away; 1->timer waits on trigger before counting
					(0<< 5) |						//0->match interrupt disabled, 1->match interrupt enabled
					(1<< 4) |						//0->counts down, 1->counts up
					(0<< 3) |						//0->capture / compare enabled 1->pwm enabled
					(0<< 2) |						//0->edge count for capture; 1->edge time for capture
					(0x02) |						//0x00->reserved, 0x01->one shot, 0x02->periodic, 0x03->capture
					0x00;

	//set the prescaler
	TMRx->TBPR = (ps - 1) & 0xffff;							//set the prescaler
	TMRx->TBILR= (pr - 1);							//set the top
	//reset counter
	TMRx->TBV = 0;

	//clear ISR flags, disable isr
	//disable all interrupt
	TMRx->IMR &=~(0x1f << 8);						//0->disable time-out interrupt, 1->enable time-out interrupt
	TMRx->ICR |= (0x1f << 8);						//1->clear interrupt flag, 0->no effect

	//start the timer
	TMRx->CTL |= (1<<8);							//0->disable timer, 1->enable timer
}

//activate the timerb isr
void wtmr4b_act(void (*isrptr)(void)) {
	_isrptr_tmrb = isrptr;
	TMRx->ICR |= (1<<8);							//1-.clera the flag, 0->no effect
	TMRx->IMR |= (1<<8);							//1->enable time-out interrupt, 0->disable it.
	NVIC_EnableIRQ(WTIMER4B_IRQn);					//use default priorities
}
