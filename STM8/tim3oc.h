#ifndef _TIM3OC_H
#define _TIM3OC_H

#include "gpio.h"							//we use gpio

//hardware configuration
//end hardware configuration

//global defines
//TIM2 prescaler
#define TIM2_PS1x			0x00
#define TIM2_PS2x			0x01
#define TIM2_PS4x			0x02
#define TIM2_PS8x			0x03
#define TIM2_PS16x			0x04
#define TIM2_PS32x			0x05
#define TIM2_PS64x			0x06
#define TIM2_PS128x			0x07
#define TIM2_PS256x			0x08
#define TIM2_PS1024x		0x09
#define TIM2_PS2048x		0x0a
#define TIM2_PS4096x		0x0b
#define TIM2_PS8192x		0x0c
#define TIM2_PS16384x		0x0d
#define TIM2_PS32768x		0x0e

//global variables


//initialize the timer
//ps = prescaler: 0x0000 - 0xffff
//pr = 16-bit period, fixed at 0xffff
void tim3_init(uint16_t ps);
//activate user handler
void tim3_act(void (*isr_ptr)(void));

//output compare channels
void tim3oc1_setpr(uint16_t pr);			//set output compare 1 period
void tim3oc1_act(void (*isr_ptr)(void));	//activate user handler
void tim3oc2_setpr(uint16_t pr);			//set output compare 1 period
void tim3oc2_act(void (*isr_ptr)(void));	//activate user handler

#endif
