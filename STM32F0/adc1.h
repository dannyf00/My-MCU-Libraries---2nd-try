#ifndef _ADC1_H
#define _ADC1_H

#include "gpio.h"						//we use gpio

//global defines
//adc channel definitions
#define ADC_CH0			(1ul<<0)
#define ADC_CH1			(1ul<<1)
#define ADC_CH2			(1ul<<2)
#define ADC_CH3			(1ul<<3)
#define ADC_CH4			(1ul<<4)
#define ADC_CH5			(1ul<<5)
#define ADC_CH6			(1ul<<6)
#define ADC_CH7			(1ul<<7)
#define ADC_CH8			(1ul<<8)
#define ADC_CH9			(1ul<<9)
#define ADC_CH10		(1ul<<10)
#define ADC_CH11		(1ul<<11)
#define ADC_CH12		(1ul<<12)
#define ADC_CH13		(1ul<<13)
#define ADC_CH14		(1ul<<14)
#define ADC_CH15		(1ul<<15)
#define ADC_CH16		(1ul<<16)
#define ADC_CH17		(1ul<<17)
#define ADC_TS			ADC_CH16				//tempeature sensor on CH16
#define ADC_VREFINT		ADC_CH17				//internal reference on CH17 @ 1.20v

//convert temperature sensor adc reading into temperaturex10
//follow the datasheet. 3.3v Vref (3.0v for my board), 12bit adc
#define Tx10(adc)		(3529 - ((uint32_t) (3300*10*10/43 * (adc)) >> 12))

//global variables

void adc1_init(void);
uint16_t adc1_read(uint32_t ain);

#endif
