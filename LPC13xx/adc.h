#ifndef ADC_H_
#define ADC_H_

//adc0 driver for lpc17xx
#include "gpio.h"							//we use gpio

//hardware configuration
#define ADC_CH0				(1<<0)
#define ADC_CH1				(1<<1)
#define ADC_CH2				(1<<2)
#define ADC_CH3				(1<<3)
#define ADC_CH4				(1<<4)
#define ADC_CH5				(1<<5)
#define ADC_CH6				(1<<6)
#define ADC_CH7				(1<<7)
//end hardware configuration

//reset the adc
void adc_init(void);

//read the adc - lowest 10 digits effective
uint32_t adc_read(uint32_t ch);

#endif /* ADC0_H_ */
