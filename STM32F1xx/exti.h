#ifndef _EXTI_H
#define _EXTI_H

#include "gpio.h"					//we use F_CPU + gpio functions

//hardware configuration
//end hardware configuration

//global variables

//global defines
#define EXTI_FALLING	0				//trigger on falling edge
#define EXTI_RISING		1				//trigger on rising edge
#define EXTI_BOTH		2				//trigger on falling and rising edges

//for ease of uses:
#define exti0_init(gpio, edge)			exti_init(gpio, 1<<0, edge)
#define exti1_init(gpio, edge)			exti_init(gpio, 1<<1, edge)
#define exti2_init(gpio, edge)			exti_init(gpio, 1<<2, edge)
#define exti3_init(gpio, edge)			exti_init(gpio, 1<<3, edge)
#define exti4_init(gpio, edge)			exti_init(gpio, 1<<4, edge)
#define exti5_init(gpio, edge)			exti_init(gpio, 1<<5, edge)
#define exti6_init(gpio, edge)			exti_init(gpio, 1<<6, edge)
#define exti7_init(gpio, edge)			exti_init(gpio, 1<<7, edge)
#define exti8_init(gpio, edge)			exti_init(gpio, 1<<8, edge)
#define exti9_init(gpio, edge)			exti_init(gpio, 1<<9, edge)
#define exti10_init(gpio, edge)			exti_init(gpio, 1<<10, edge)
#define exti11_init(gpio, edge)			exti_init(gpio, 1<<11, edge)
#define exti12_init(gpio, edge)			exti_init(gpio, 1<<12, edge)
#define exti13_init(gpio, edge)			exti_init(gpio, 1<<13, edge)
#define exti14_init(gpio, edge)			exti_init(gpio, 1<<14, edge)
#define exti15_init(gpio, edge)			exti_init(gpio, 1<<15, edge)

#define exti0_act(isrptr)				exti_act(1<<0, isrptr)
#define exti1_act(isrptr)				exti_act(1<<1, isrptr)
#define exti2_act(isrptr)				exti_act(1<<2, isrptr)
#define exti3_act(isrptr)				exti_act(1<<3, isrptr)
#define exti4_act(isrptr)				exti_act(1<<4, isrptr)
#define exti5_act(isrptr)				exti_act(1<<5, isrptr)
#define exti6_act(isrptr)				exti_act(1<<6, isrptr)
#define exti7_act(isrptr)				exti_act(1<<7, isrptr)
#define exti8_act(isrptr)				exti_act(1<<8, isrptr)
#define exti9_act(isrptr)				exti_act(1<<9, isrptr)
#define exti10_act(isrptr)				exti_act(1<<10, isrptr)
#define exti11_act(isrptr)				exti_act(1<<11, isrptr)
#define exti12_act(isrptr)				exti_act(1<<12, isrptr)
#define exti13_act(isrptr)				exti_act(1<<13, isrptr)
#define exti14_act(isrptr)				exti_act(1<<14, isrptr)
#define exti15_act(isrptr)				exti_act(1<<15, isrptr)

//global variables

//initialize the exti
//pin: one pin only
//gpio: GPIOA..GPIOG
void exti_init(GPIO_TypeDef * gpio, uint16_t pin, uint8_t edge);

//install user handler
void exti_act(uint16_t pin, void (*isr_ptr)(void));

#endif
