#ifndef SWRTC_H
#define SWRTC_H

//software implementation of a RTC
//typical flow:
//1. time_set() to initialize the timer
//2. time_update() to update and obtain current time / second count (32-bit)
//ticks can come from millis()/micros(), SysTick(), or any constantly running timer
//TICKS_PER_SEC is user specified - similar to CLOCKS_PER_SEC, and
//may need to be adjusted based on prescaler setting

#include "gpio.h"
#include <time.h>							//we use time.h routines

//global defines
#define TICKS_PER_SEC			(F_CPU / 8)		//timer input = F_CPU

//global variables

//update time - need to be fed with a constantly increasing ticks value
//update time_now
time_t time_update(uint32_t ticks);

//get time
time_t time_get(void);

//set time
time_t time_set(time_t time);

#endif
