#ifndef _ADC_H
#define _ADC_H

#include "gpio.h"
//#include <avr/io.h>     //we use gcc-avr

//hardware configuration
#define ADC_DDR					DDRB		//adc on portb
//end hardware configuration

//input channels - attiny25/45/85: gcc-avr and iar-avr
#define ADC_ADC0			0x00			//singled ended, adc0/pb5
#define ADC_ADC1			0x01			//singled ended, adc1/pb2
#define ADC_ADC2			0x02			//singled ended, adc2/pb4
#define ADC_ADC3			0x03			//singled ended, adc3/pb3
#define ADC_ADC2_2_1x		0x04			//diff. adc, 1x gain, +=adc2, -=adc2 - offset measurement for adc2 x 1
#define ADC_ADC2_2_20x		0x05			//diff. adc, 20x gain, +=adc2, -=adc3 - offset measurement for adc2 x 20
#define ADC_ADC2_3_1x		0x06			//diff. adc, 1x gain, +=adc2, -=adc3 - actual measurement at x1 gain
#define ADC_ADC2_3_20x		0x07			//diff. adc, 20x gain: +=adc2, -=adc3 - actual measurement at x20 gain
#define ADC_ADC0_0_1x		0x08			//diff. adc, 1x gain, +=adc0, -=adc0 - offset measurement for adc0 x 1
#define ADC_ADC0_0_20x		0x09			//diff. adc, 20x gain, +=adc0, -=adc0 - offset measurement at x20 gain
#define ADC_ADC0_1_1x		0x0a			//diff. adc, 20x gain, +=adc0, -=adc1 - actual measurement for adc0 x1
#define ADC_ADC0_1_20x		0x0b			//diff. adc, 20x gain: +=adc0, -=adc1 - actual measurement at x20 gain
#define ADC_BANDGAP			0x0c			//MEASURE THE INTERNAL BANDGAP
#define ADC_GND				0x0d			//ground
#define ADC_RESERVED		0x0e			//reserved
#define ADC_ADC4			0x0f			//measure internal temperature sensor/adc4
#define ADC_TEMP			ADC_ADC4		//measure internal temperature sensor/adc4

//define ADC_VBG to be ADC_BANDGAP
#if defined(ADC_BANDGAP)
#define ADC_VBG				ADC_BANDGAP		//define Vbg
#endif

void adc_init(void);							//reset the adc

unsigned short adc_read(unsigned char ch);					//read the adc

#endif
