#ifndef _TIM1_H
#define _TIM1_H

#include "gpio.h"							//we use gpio

//hardware configuration
//end hardware configuration

//global defines

//global variables


//initialize the timer
//ps = prescaler: 0x0000 - 0xffff
//pr = 16-bit period, 0x0000 - 0xffff
void tim1_init(uint16_t ps, uint16_t pr);

//activate user handler
void tim1_act(void (*isr_ptr)(void));

#endif
