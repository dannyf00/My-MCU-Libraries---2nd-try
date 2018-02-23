#ifndef _TIM1OC_H
#define _TIM1OC_H

#include "gpio.h"							//we use gpio

//hardware configuration
//end hardware configuration

//global defines

//global variables


//initialize the timer
//ps = prescaler: 0x0000 - 0xffff
//pr = 0xffff, fixed
void tim1_init(uint16_t ps);
//activate user handler
void tim1_act(void (*isr_ptr)(void));

//output compare channels
void tim1oc1_setpr(uint16_t pr);			//set output compare 1 period
void tim1oc1_act(void (*isr_ptr)(void));	//activate user handler
void tim1oc2_setpr(uint16_t pr);			//set output compare 1 period
void tim1oc2_act(void (*isr_ptr)(void));	//activate user handler
void tim1oc3_setpr(uint16_t pr);			//set output compare 1 period
void tim1oc3_act(void (*isr_ptr)(void));	//activate user handler
void tim1oc4_setpr(uint16_t pr);			//set output compare 1 period
void tim1oc4_act(void (*isr_ptr)(void));	//activate user handler

#endif
