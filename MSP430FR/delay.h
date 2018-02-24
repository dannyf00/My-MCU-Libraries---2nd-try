#ifndef _DELAY_H
#define _DELAY_H

#include "gpio.h"

//#define DLY_US	853				//852.46 is the right number for default stm32vl discovery board

void delay(uint16_t dly);

//delay a few us
void delay_us(uint16_t dly_us);

//delay a few ms
void delay_ms(uint16_t dly_ms);

#endif
