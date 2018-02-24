//using TMRA3_CCR0 as systick generator
#ifndef _SYSTICK_H
#define _SYSTICK_H

//SYSTICK uses TA3_CCR0.

#include "gpio.h"							//using msp430

//hardware configuration
//end hardware configuration

//global defines
#define F_SYSTICK			F_CPU		//systick driven by F_CPU

//global variables
//prescaler definitions
#define TMRA_PS1x		(0x00<<6)	//prescaler @ 1x
#define TMRA_PS2x		(0x01<<6)	//prescaler @ 2x
#define TMRA_PS4x		(0x02<<6)	//prescaler @ 4x
#define TMRA_PS8x		(0x03<<6)	//prescaler @ 8x
//expanded divider definitions
#define TMRA_EX1x		0x00		//expansion divider
#define TMRA_EX2x		0x01		//expansion divider
#define TMRA_EX3x		0x02		//expansion divider
#define TMRA_EX4x		0x03		//expansion divider
#define TMRA_EX5x		0x04		//expansion divider
#define TMRA_EX6x		0x05		//expansion divider
#define TMRA_EX7x		0x06		//expansion divider
#define TMRA_EX8x		0x07		//expansion divider

//initialize timer_a overflow interrupt, TA3 used
void systick_init(void);

//get systick count
uint32_t systicks(void);
#ifndef ticks
#define ticks()		systicks()		//ticks = systicks
#endif

//ticks per us - arduino styled function
#define cyclesPerMillisecond()		(F_CPU / 1000ul)
#define cyclesPerMicrosecond()		(F_CPU / 1000000ul)
#define millis()					(systicks() / cyclesPerMicrosecond())
#define micros()					(systicks() / cyclesPerMicrosecond())

//precision delays using ticks()
void systick_delay(uint32_t cnt);
void systick_delayms(uint32_t ms);
void systick_delayus(uint32_t us);

//systick compare match - not all channels are available on all timers / chips
void systick_setpr0(uint16_t pr);			//enable compare interrupt
void systick_setpr1(uint16_t pr);			//enable compare interrupt
void systick_setpr2(uint16_t pr);			//enable compare interrupt
void systick_setpr3(uint16_t pr);			//enable compare interrupt
void systick_setpr4(uint16_t pr);			//enable compare interrupt
void systick_setpr5(uint16_t pr);			//enable compare interrupt
void systick_setpr6(uint16_t pr);			//enable compare interrupt
//systick - install compare match handler - not all channels are available on all timers / chips
void systick_act0(void (*isr_ptr)(void));	//install handler
void systick_act1(void (*isr_ptr)(void));	//install handler
void systick_act2(void (*isr_ptr)(void));	//install handler
void systick_act3(void (*isr_ptr)(void));	//install handler
void systick_act4(void (*isr_ptr)(void));	//install handler
void systick_act5(void (*isr_ptr)(void));	//install handler
void systick_act6(void (*isr_ptr)(void));	//install handler
#endif
