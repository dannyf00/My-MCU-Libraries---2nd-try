#ifndef ADC_H_INCLUDED
#define ADC_H_INCLUDED


#include "gpio.h"

//hardware configuration
//end hardware configuration

//global defines
//adc channels
#define ADC_AN0						0
#define ADC_AN1						1
#define ADC_AN2						2
#define ADC_AN3						3
#define ADC_AN4						4
#define ADC_AN5						5
#define ADC_AN6						6
#define ADC_AN7						7
#define ADC_AN8						8
#define ADC_AN9						9
#define ADC_AN10					10
#define ADC_AN11					11
#define ADC_AN12					12
#define ADC_AN13					13
#define ADC_AN14					14
#define ADC_AN15					15

//global variables

//adc
//reste the adc
//automatic sampling (ASAM=1), manual conversion
void adc_init(void);

//read the adc
int16_t adc_read(uint32_t ch);

#endif /* ADC_H_INCLUDED */
