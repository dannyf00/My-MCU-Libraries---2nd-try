#ifndef _STIMER_H
#define _STIMER_H

//software timers
//usage:
//stimer_tick() to be called periodically
//stimer_init() initialize the timer - done once
//stimer_ovf() tests if a software timer has overflown. if so, update the timer and return a flag

#include "gpio.h"                           //we use gpio functions

//hardware configuration
//end hardware configuration

//global defines

//global variables

typedef uint32_t tick_t;       				//soft timer ticks
typedef struct {
    tick_t period;              			//period
    tick_t tick;                			//next tick to invoke call back function
    //void (*ptr)(void);      				//call back function here
} stimer_t;               					//timer types


//global variables

//initialize the timer
void stimer_init(stimer_t *stimer, tick_t pr);

//check and update tick
uint8_t stimer_ovf(stimer_t *stimer);

//advance systick
void stimer_tick(void);

#endif
