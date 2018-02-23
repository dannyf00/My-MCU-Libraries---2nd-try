#ifndef SYSTICK_H_
#define SYSTICK_H_

//simulating SysTick via TIMER1 interrupt.
//Timer1 runs at 0x10000ul period (PR = 0xffff), 1:1 prescaler.
//Prescaler can be set to be 1x, 8x, 64x, 256x
//#include <p24fxxxx.h>					//we use htc compiler
#include "gpio.h"

//global defines
#define F_SYSTICK			F_CPU		//systick driven by F_CPU

//systick config
//tmr1 error term
//use a positive number if tmr0 is too fast
//use a negative number if tmr0 is too slow
//#define RTC1_ERROR			0


//initialize the timer
void systick_init(void);

//activate the isr handler
uint32_t ticks(void);

//ticks per us - arduino styled function
#define cyclesPerMillisecond()		(F_SYSTICK / 1000ul)
#define cyclesPerMicrosecond()		(F_SYSTICK / 1000000ul)
#define millis()					(ticks() / (F_CPU / 1000))
#define micros()					(ticks() / (F_CPU / 1000000ul))

//precision delays using ticks()
void systick_delayms(uint32_t ms);
void systick_delayus(uint32_t us);

#endif //tmr1_h_
