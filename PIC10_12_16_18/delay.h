#ifndef __DELAY_H
#define __DELAY_H

#include "gpio.h"				//we use f_cpu

//for compatability
#define delayms(n)				delay_ms(n)
#define delayus(n)				delay_us(n)

void delay(volatile int dly);

void delay_us(volatile unsigned short us);

void delay_ms(volatile unsigned short ms);

#endif
