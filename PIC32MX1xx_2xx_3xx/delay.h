#ifndef __DELAY_H
#define __DELAY_H

#include "gpio.h"				//we use _nop_()

void delay(uint16_t dly);

void delay_us(uint32_t us);

void delay_ms(uint32_t ms);

#endif //delay_h_
