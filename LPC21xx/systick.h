#ifndef _SYSTICK_H
#define _SYSTICK_H

//emulate systick using tmr0's MR0 channel

#include "tmr0_mr.h"				//we use tmr0

//global defines
#define F_SYSTICK			F_CPU		//systick driven by F_CPU

//initialize systick
void systick_init(void);

//activate the isr handler
uint32_t ticks(void);

//ticks per us - arduino styled function
#define cyclesPerMillisecond()		(F_SYSTICK / 1000ul)
#define cyclesPerMicrosecond()		(F_SYSTICK / 1000000ul)
#define millis()					(ticks() / cyclesPerMicrosecond())
#define micros()					(ticks() / cyclesPerMicrosecond())

//precision delays using ticks()
void systick_delayms(uint32_t ms);
void systick_delayus(uint32_t us);

#endif
