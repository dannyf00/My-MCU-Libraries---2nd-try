#ifndef SYSTICK_H_
#define SYSTICK_H_

//#include <p32xxxx.h>					//we use c32 compiler
#include "gpio.h"

#define F_SYSTICK			F_PHB		//systick driven by F_PHB

//initialize the timer
void systick_init(void);

//activate the isr handler
uint32_t systicks(void);
#define ticks()						systicks()

//ticks per us - arduino styled function
#define cyclesPerMillisecond()		(F_SYSTICK / 1000ul)
#define cyclesPerMicrosecond()		(F_SYSTICK / 1000000ul)
#define millis()					(systicks() / cyclesPerMillisecond())
#define micros()					(systicks() / cyclesPerMicrosecond())

//precision delays using ticks()
void systick_delay(uint32_t tk);
void systick_delayms(uint32_t ms);
void systick_delayus(uint32_t us);

#endif //tmr1_h_
