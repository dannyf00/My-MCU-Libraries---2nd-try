#ifndef _RAND_ADC_H
#define _RAND_ADC_H

//caution: adc modules to be presummed initiated prior to the rngxx routines

#include "adc1.h"										//we use hardware adc

//hardware configuration
#define randadc_read()		adc1_read(ADC_TEMP)			//adc modules to be used
//end hardware configuration

//global defines
#define rand1()			(randadc_read() & 0x01)		//return a random 1-bit
//global variables

//random number generator - 32-bit
uint32_t rand32(void);

//random number generator - 16-bit
uint16_t rand16(void);

//random number generator - 8-bit
uint8_t rand8(void);

//random number generator - 1-bit
//uint8_t rand1(void);

#endif
