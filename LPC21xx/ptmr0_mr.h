#ifndef _PTMR0_MR_H
#define _PTMR0_MR_H

#include "gpio.h"					//we use gpio

//hardware configuration
//end hardware configuration

//global defines

//global variables

//reset the pwm with a prescaler
void ptmr0_init(uint32_t ps);

//set the period
void ptmr0_setpr0(uint32_t pr);
//insert the user handler
void ptmr0_act0(void (*isr_ptr)(void));

//set the period
void ptmr0_setpr1(uint32_t pr);
//insert the user handler
void ptmr0_act1(void (*isr_ptr)(void));

//set the period
void ptmr0_setpr2(uint32_t pr);
//insert the user handler
void ptmr0_act2(void (*isr_ptr)(void));

//set the period
void ptmr0_setpr3(uint32_t pr);
//insert the user handler
void ptmr0_act3(void (*isr_ptr)(void));

//set the period
void ptmr0_setpr4(uint32_t pr);
//insert the user handler
void ptmr0_act4(void (*isr_ptr)(void));

//set the period
void ptmr0_setpr5(uint32_t pr);
//insert the user handler
void ptmr0_act5(void (*isr_ptr)(void));

//set the period
void ptmr0_setpr6(uint32_t pr);
//insert the user handler
void ptmr0_act6(void (*isr_ptr)(void));

#endif
