#include "systick.h"				//we use systick

//global defines
#define CTx					CT0		//using timer0

//global variables
volatile uint32_t systickovf_counter=0;		//not really used. here for compatability reasons

//my systick handler
void systick_isr(void) {
	//do nothing - 32-bit roll-over
	//need to maintain systickovf_counter if 24-bit roll-over used
}

//initialize systick
void systick_init(void) {
	tmr0_init(1);					//tmr0 initialize with 1:1 prescaler
	tmr0_setpr0(0);					//systick to have full 32-bit roll-over
	tmr0_act0(systick_isr);				//install my own handler
}

//return timer clicks
//execution time = 30 ticks, no optimization
uint32_t ticks(void) {
	uint32_t m;
	uint32_t f;

	//do a double read
	do {
		m = systickovf_counter;			//read the overflow counter
		f = CTx->TC;					//SysTick->VAL;				//read the least significant 16-bits
	} while (m != systickovf_counter);	//guard against overflow

	return (m + f) << 0;				//systick is a 24-bit downcounter
}

//delay ms using SysTick ticks()
//watch out for overflow - max = 2^32/(F_CPU / 1000)
void systick_delayms(uint32_t ms) {
	uint32_t start_time = ticks();

	ms *= cyclesPerMillisecond();				//convert ms to ticks
	while (ticks() - start_time < ms) continue;	//wait for timer to expire
}

//delay using SysTick ticks()
//watch out for overflow - max = 2^32/(F_CPU / 1000000)
void systick_delayus(uint32_t us) {
	uint32_t start_time = ticks();

	us *= cyclesPerMicrosecond();				//convert ms to ticks
	while (ticks() - start_time < us) continue;	//wait for timer to expire
}
