#ifndef _IWDT_H
#define _IWDT_H

#include "gpio.h"				//not really used

//initialize / enable iwdt
//ps-prescaler: 3-bit, 1:1->256:1
//pr-period: 12-bit
void iwdt_init(uint16_t ps, uint16_t pr);

//feed the dog
#define iwdt_reset()			IWDG -> KR = 0x0000aaaa

#endif
