#ifndef __DELAY_H
#define __DELAY_H

#include "gpio.h"				//we use _nop_(), F_CPU

void delay(volatile unsigned char dly);

void delay_us(volatile unsigned short us);

void delay_ms(volatile unsigned short ms);

#endif //delay_h
