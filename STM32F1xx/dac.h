#ifndef _DAC_H
#define _DAC_H

#include "gpio.h"

//initialize dac
void dac_init(void);

//extended function
//output a 12-bit value on DACn ch 1
//DAC1 = PA4 = Pin 4
void DAC1Write(uint16_t val);

//output a 12-bit value on DACn ch 2
//DAC2 = PA5 = Pin 5
void DAC2Write(uint16_t val);

#endif
