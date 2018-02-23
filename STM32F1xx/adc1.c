#include "adc1.h"

//hardware configuration
#define ADC_SMPR		7				//ADC sample time, 0b000(1.5us)..0b111(239.5us), applied to all channels
//end hardware configuration

//initialize adc
void adc1_init(void) {
	RCC->APB2ENR |= RCC_APB2ENR_ADC1EN;		//enable clock to ADC1
	ADC1->CR1 = (0<<23) |					//0->disable analog watchdog on regular channels
				(0<<22) |					//0->disable analog watchdog on injected channels
				(0<<13) |					//0->1 ch for discontinous conversion
				(0<<12) |					//0->discontinous mode for injected channels disabled
				(0<<11) |					//0->discontinous mode for regular channel disabled
				(0<<10) |					//0->automatic injected conversion disabled
				(0<< 9) |					//0->analog watchdog enabled on all channels
				(0<< 8) |					//0->scan mode disabled
				(0<< 7) |					//0->EOC interrupt on injected conversion disabled
				(0<< 6) |					//0->interrupt on analog watchdog disabled
				(0<< 5) |					//0->EOC interrupt on regular channels disabled
				(0<< 0) |					//ADC watchdog channels, 0..17 (16=Temperature sensor, 17 = Vrefint)
				0x00;
	ADC1->CR2 = (1<<23) |					//0->temperature/internal vref sensor disabled
				(0<<22) |					//1->start conversion on regular channel. 0->reset state. cleared by software
				(0<<21) |					//1->start conversion on injected channels. 0->reset state. cleared by s oftware
				(1<<20) |					//0->regular conversion on external event disabled
				(7<<17) |					//7->regular conversion triggered by software
				(0<<15) |					//0->injected conversion on external event disabled
				(7<<12) |					//7->injected conversion triggered by software
				(0<<11) |					//0->right aligned, 1->left aligned
				(0<< 3) |					//0->caliberatin stablized, 1->caliberatin initialized
				(0<< 2) |					//0->calibration complete, 1->initialize calibration
				(0<< 1) |					//0->single conversion mode, 1->continous conversion mode
				(1<< 0);					//1->adc1 on, 0->adc1 off
	//set adc sample time
	//0b111->239.5 cycles for all channels
	ADC1->SMPR1 = 	(ADC_SMPR << (3 * 7)) |
					(ADC_SMPR << (3 * 6)) |
					(ADC_SMPR << (3 * 5)) |
					(ADC_SMPR << (3 * 4)) |
					(ADC_SMPR << (3 * 3)) |
					(ADC_SMPR << (3 * 2)) |
					(ADC_SMPR << (3 * 1)) |
					(ADC_SMPR << (3 * 0)) |
					0x00;
	ADC1->SMPR2 = 	(ADC_SMPR << (3 * 9)) |
					(ADC_SMPR << (3 * 8)) |
					(ADC_SMPR << (3 * 7)) |
					(ADC_SMPR << (3 * 6)) |
					(ADC_SMPR << (3 * 5)) |
					(ADC_SMPR << (3 * 4)) |
					(ADC_SMPR << (3 * 3)) |
					(ADC_SMPR << (3 * 2)) |
					(ADC_SMPR << (3 * 1)) |
					(ADC_SMPR << (3 * 0)) |
					0x00;
	//set adc channel sequence
	ADC1->SQR3 = ADC1->SQR2 = ADC1->SQR1 = 0;							//0->1 conversion

	//optional: adc self-calibration
	//start caliberation
	ADC1->CR2 |= (1<<3);					//1->initialize calibration registers
	while ((ADC1->CR2) & (1<<3)) continue;	//wait for calibration to initialize
	ADC1->CR2 |= (1<<2);					//1->initialize calibration
	while ((ADC1->CR2) & (1<<2)) continue;	//wait for calibration to finish
	//now adc is calibrated
}

//analog to digital converter on ADC1
//ain/analog input channel: ain valid values: 0..15, 16=temperature sensor, 17=Vrefint
//***user needs to be configured as floating input***
uint16_t adc1_read(uint32_t ain) {
	ADC1->SR &= ~(1<<1);					//clear the eoc flag
	//ADC1->CR1 = (ADC1->CR1 &~0x1f) | (ain & 0x1f);	//pick the adc channel
	//ADC1->CR2|= (1<<0);					//start the conversion
	ADC1->SQR3 = ain & 0x1f;				//define the first (and only) adc ch
	ADC1->CR2 |= (1<<22);					//start conversion
	while ((ADC1->SR & (1<<1)) == 0) continue;	//wait for conversion to end (EOC set at end of conversion)
	return ADC1->DR;						//return adc results
}

