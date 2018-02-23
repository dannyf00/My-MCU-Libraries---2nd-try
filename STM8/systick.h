#ifndef _SYSTICK_H
#define _SYSTICK_H

#include "gpio.h"							//we use systick

//hardware configuration
//end hardware configuration

//global defines
#define F_SYSTICK			F_CPU		//systick driven by F_PHB

//global variables


//initialize the timer
void systick_init(void);

uint32_t ticks(void);

//ticks per us - arduino styled function
#define cyclesPerMillisecond()		(F_CPU / 1000ul)
#define cyclesPerMicrosecond()		(F_CPU / 1000000ul)
#define millis()					(ticks() / (F_CPU / 1000))
#define micros()					(ticks() / (F_CPU / 1000000ul))

//precision delays using ticks()
void systick_delayms(uint32_t ms);
void systick_delayus(uint32_t us);


#endif
