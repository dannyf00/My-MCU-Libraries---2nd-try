#ifndef GADC_H_INCLUDED
#define GADC_H_INCLUDED

#include "gpio.h"

//hardware configuration
//#define GADC_PIN		(1<<0)				//read / discharge pin
//end hardware configuration

//global defines


//global variables

//reset the gadc module
void adc_init(void);

//read gadc
uint16_t adc_read(uint8_t pins);

#endif // GADC_H_INCLUDED
