//ARMduino port for ARM family of Cortex-M chips
//software environment: gcc-arm


#ifndef _SYSTICK_H
#define _SYSTICK_H

#include "gpio.h"										//we use stm32f10x

//global defines
#define F_SYSTICK			F_CPU		//systick driven by F_CPU

//global variables
//initialize the timer
void systick_init(void);

//activate the isr handler
uint32_t systicks(void);
#ifndef ticks
#define ticks()				systicks()
#endif

//ticks per us - arduino styled function
#define cyclesPerMillisecond()		(F_CPU / 1000ul)
#define cyclesPerMicrosecond()		(F_CPU / 1000000ul)
#define millis()					(ticks() / cyclesPerMicrosecond())
#define micros()					(ticks() / cyclesPerMicrosecond())

//precision delays using ticks()
void systick_delay(uint32_t dly);
void systick_delayms(uint32_t ms);
void systick_delayus(uint32_t us);

#endif
