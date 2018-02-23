#ifndef _ADC1_H
#define _ADC1_H

#include "gpio.h"							//we use gpio

//hardware configuration
//end hardware configuration

//global defines
#define ADC_DLY			64					//waste 7us for tSTAB

#define ADC_AIN0		0x00
#define ADC_AIN1		0x01
#define ADC_AIN2		0x02
#define ADC_AIN3		0x03
#define ADC_AIN4		0x04
#define ADC_AIN5		0x05
#define ADC_AIN6		0x06
#define ADC_AIN7		0x07
#define ADC_AIN8		0x08
#define ADC_AIN9		0x09
#define ADC_AIN10		0x0a
#define ADC_AIN11		0x0b
#define ADC_AIN12		0x0c
#define ADC_AIN13		0x0d
#define ADC_AIN14		0x0e
#define ADC_AIN15		0x0f

//global variables

//initialize the adc
void adc_init(void);

//read the adc - single conversion, non-interrupt
uint16_t adc_read(uint8_t ch);
#endif
