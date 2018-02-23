#ifndef _DELAY_H
#define _DELAY_H

#include "gpio.h"

//for compatability
#define delayms(n)			delay_ms(n)
#define delayus(n)			delay_us(n)

//delay routines
void delay(unsigned int dly);				//waste some cycle

//delay_us(1000) = 10ms
//delay_us(1) = 10us
void delay_us(unsigned int us);           	//delay a us

void delay_ms(unsigned int ms);				//delay ms
#endif
