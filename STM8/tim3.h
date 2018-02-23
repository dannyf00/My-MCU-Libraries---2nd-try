#ifndef _TIM3_H
#define _TIM3_H

#include "gpio.h"							//we use gpio

//hardware configuration
//end hardware configuration

//global defines
//TIM3 prescaler
#define TIM3_PS1x			0x00
#define TIM3_PS2x			0x01
#define TIM3_PS4x			0x02
#define TIM3_PS8x			0x03
#define TIM3_PS16x			0x04
#define TIM3_PS32x			0x05
#define TIM3_PS64x			0x06
#define TIM3_PS128x			0x07
#define TIM3_PS256x			0x08
#define TIM3_PS1024x		0x09
#define TIM3_PS2048x		0x0a
#define TIM3_PS4096x		0x0b
#define TIM3_PS8192x		0x0c
#define TIM3_PS16384x		0x0d
#define TIM3_PS32768x		0x0e

//global variables


//initialize the timer
//ps = prescaler: 0x0000 - 0xffff
//pr = 16-bit period, 0x0000 - 0xffff
void tim3_init(uint16_t ps, uint16_t pr);

//activate user handler
void tim3_act(void (*isr_ptr)(void));

#endif
