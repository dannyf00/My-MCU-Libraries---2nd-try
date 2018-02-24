/*
 * systick.h
 *
 *  Created on: Sep 19, 2013
 *      Author: Ken
 */

#ifndef _SYSTICK_H
#define _SYSTICK_H

#include "gpio.h"								//we use gpio
#define F_SYSTICK			F_CPU		//systick driven by F_CPU

//initialize the timer
void systick_init(void);

//activate the isr handler
uint32_t systicks(void);
#define ticks()				systicks()

//ticks per us - arduino styled function
#define cyclesPerMillisecond()		(F_CPU / 1000ul)
#define cyclesPerMicrosecond()		(F_CPU / 1000000ul)
#define millis()					(ticks() / cyclesPerMicrosecond())
#define micros()					(ticks() / cyclesPerMicrosecond())

//precision delays using ticks()
void systick_delayms(uint32_t ms);
void systick_delayus(uint32_t us);


#endif /* SYSTICK_H_ */
