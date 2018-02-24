/*
 * systick.c
 *
 *  Created on: Sep 19, 2013
 *      Author: Ken
 */


//#define TARGET_IS_BLIZZARD_RA1									//indicate parts, for rom functions
//#define PART_TM4C1233H6PM											//indicate parts, for pin / memory definitions

#include "systick.h"

//global defines

//global variables
volatile uint32_t systickovf_counter=0;

//systick handler
void SysTick_Handler(void) {
	systickovf_counter+=1ul<<24;										//increment the overflow counter
}

//set up systick
void systick_init(void) {
	systickovf_counter = 1ul<<24;										//24-bit downcounter
	//MAP_SysTickPeriodSet(period);									//set the period
	//MAP_SysTickDisable();											//disable systick
	//_systick_isr_ptr = isr_ptr;									//install the user handler
	SysTick_Config(systickovf_counter);									//config the systick timer
	//SysTickIntRegister(SysTick_Handler);							//register the user handler
	//MAP_SysTickEnable();											//turn on the systick
	NVIC_EnableIRQ(SysTick_IRQn);									//enable irq
}

//return timer clicks
//execution time = 30 ticks, no optimization
uint32_t systicks(void) {
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
	uint32_t start_time = systicks();

	ms *= cyclesPerMillisecond();				//convert ms to ticks
	while (systicks() - start_time < ms) continue;	//wait for timer to expire
}

//delay using SysTick ticks()
//watch out for overflow - max = 2^32/(F_CPU / 1000000)
void systick_delayus(uint32_t us) {
	uint32_t start_time = systicks();

	us *= cyclesPerMicrosecond();				//convert ms to ticks
	while (systicks() - start_time < us) continue;	//wait for timer to expire
}
