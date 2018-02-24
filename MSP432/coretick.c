#include "coretick.h"					//we use dwt cycle counter for time base

//global definitions

//global variables

//reset systick
void coretick_init(void) {
	//configure dwt as the time base for millis()/micros()
#if defined(CoreDebug_DEMCR_TRCENA_Msk)
	CoreDebug->DEMCR |= CoreDebug_DEMCR_TRCENA_Msk;		//enable debug tracer
#endif
	//ITM->LAR = 0xC5ACCE55;					//unlock access to dwt, if so equip'd
	DWT->CTRL |= ITM_TCR_ITMENA_Msk;			//enable dwt cycle count
}

//return timer clicks
//execution time = 30 ticks, no optimization

//delay ms using SysTick ticks()
//watch out for overflow - max = 2^32/(F_CPU / 1000)
void coretick_delayms(uint32_t ms) {
	uint32_t start_time = coreticks();

	ms *= cyclesPerMillisecond();				//convert ms to ticks
	while (coreticks() - start_time < ms) continue;	//wait for timer to expire
}

//delay using SysTick ticks()
//watch out for overflow - max = 2^32/(F_CPU / 1000000)
void coretick_delayus(uint32_t us) {
	uint32_t start_time = coreticks();

	us *= cyclesPerMicrosecond();				//convert ms to ticks
	while (coreticks() - start_time < us) continue;	//wait for timer to expire
}
