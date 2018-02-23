#include "systick.h"					//we use systick for time base

//global definitions

//global variables
//for time base off SysTick (24-bit counter)
volatile uint32_t systickovf_counter = 1ul<<24;						//time base on Systick -> SysTick->VAL being the lowest 24-bits (SysTick is a downcounter)

//systick handler - to provide time base for millis()/micros()
void SysTick_Handler(void) {
	//clear the flag
	systickovf_counter += 1ul<<24;						//increment systick counter - 24bit, 1:1 prescaler
}

//reset systick
void systick_init(void) {
	//configure Systick as the time base for millis()/micros()

	systickovf_counter = 1ul<<24;											//SysTick is a 24-bit downcounter
	//for chips where SysTick_Config() is not defined in cmsis
	SysTick->LOAD  = 	(systickovf_counter-1)/*ticks*/ & SysTick_LOAD_RELOAD_Msk;      /* set reload register */
	NVIC_SetPriority 	(SysTick_IRQn, (1<<__NVIC_PRIO_BITS) - 1);  /* set Priority for Systick Interrupt */
	SysTick->VAL   = 	0;                                          /* Load the SysTick Counter Value */
	SysTick->CTRL  = 	SysTick_CTRL_CLKSOURCE_Msk |
						SysTick_CTRL_TICKINT_Msk   |
						SysTick_CTRL_ENABLE_Msk;                    /* Enable SysTick IRQ and SysTick Timer */

	//alternative - for CMSIS-equip'd chips
	//SysTick_Config(SysTick_LOAD_RELOAD_Msk);			//reload all 24 bits
}

//return timer clicks
//execution time = 30 ticks, no optimization
uint32_t ticks(void) {
	uint32_t m;
	uint32_t f;

	//do a double read
	do {
		m = systickovf_counter;			//read the overflow counter
		f = SysTick->VAL;				//read the least significant 16-bits
	} while (m != systickovf_counter);	//guard against overflow

	return (m - f) << 0;				//systick is a 24-bit downcounter
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
