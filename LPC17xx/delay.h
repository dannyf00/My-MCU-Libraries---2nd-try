#ifndef _DELAY_H
#define _DELAY_H

//#include <lpc_types.h>				//we use lpc
//#include <lpc13xx.h>				//we use lpc11xx
#include "gpio.h"					//we use f_cpu

//for compatability
#define delayms(ms)	delay_ms(ms)
#define delayus(us)	delay_us(us)

//#define DLY_US	853				//852.46 is the right number for default stm32vl discovery board

void delay(uint32_t dly);

//delay a few us
void delay_us(uint32_t dly_us);

//delay a few ms
void delay_ms(uint32_t dly_ms);

#endif
