#include "adc1.h"

//hardware configuration
#define ADC_SMPR		7				//ADC sample time, 0b000(1.5us)..0b111(239.5us), applied to all channels
//end hardware configuration

//for compatability
#define ADCx			ADC1

//global variables
static uint32_t _adc_calfactor;				//adc calibration factor
//initialize adc
void adc1_init(void) {
	RCC->APB2ENR |= RCC_APB2ENR_ADC1EN;		//enable clock to ADCx

	//configure adc
	ADCx->CFGR1 = 	(0x00<<26) |			//0->awd on channel 0
					(0<<23) |				//0->AWD disabled
					(0<<22) |				//0->AWD on all channels (but disabled by bit 22
					(1<<16) |				//1->enable discontinuous conversion
					(0<<15) |				//0->auto off disabled
					(0<<14) |				//0->wait conversion disabled
					(0<<13) |				//0->single conversion mode, 1->continuous mode
					(0<<12) |				//0->adc data register preserved in overrun
					(0x00<<10) |			//00->hardware external trigger disabled
					(0x00<<6) |				//0000->external on TRG0 - but disabled
					(0<<5) |				//0->right aligned, 1->left aligned
					(0x00<<3) |				//00->data resolution = 12bit, 01->10bit, 10->8bit, 11->6bit
					(0<<2) |				//0->upward scan
					(0<<1) |				//0->DMA one shot mode selected
					(0<<0) |				//0->DMA disabled
					0x00;
	ADCx->CFGR2 = 	(0x02 << 30);			//00->adc clock, 01->PCLK/2, 10->PCLK/4 -> no jitter
	//set adc sample time
	//0b111->239.5 cycles for all channels
	ADCx->SMPR = 	(ADC_SMPR << (3 * 0)) |
					0x00;
	//set adc channel sequence
	//ADCx->SQR3 = ADCx->SQR2 = ADCx->SQR1 = 0;							//0->1 conversion

	//start self-calibration
	ADCx->CR =	0;							//reset CR
	ADCx->CR = (1<<15);						//start the calibration
	while (ADCx->CR & (1<<15)) continue;	//wait for ADC calibration to finish
	_adc_calfactor = ADCx->DR;				//save adc calibration factor

	//optional: enable temperature sensors
	ADC->CCR |= 	(1ul<<23) |				//1->enable temperature sensor
					(1ul<<22) |				//1->enable Vrefint. 1.20v nominal
					0x00;

	ADCx->CR = 	(1<<0);						//enable aden
	while ((ADCx->ISR & (1<<0)) == 0) continue;	//wait for the adc to be ready
}

//analog to digital converter on ADCx
//ain/analog input channel: ain valid values: 0..15, 16=temperature sensor, 17=Vrefint
//***user needs to be configured as floating input***
uint16_t adc1_read(uint32_t ain) {
	//ADCx->ISR &= ~(1<<2);					//clear the eoc flag
	//ADCx->CR1 = (ADCx->CR1 &~0x1f) | (ain & 0x1f);	//pick the adc channel
	//ADCx->CR2|= (1<<0);					//start the conversion
	ADCx->CHSELR = ain & 0x03fffful;				//define the first (and only) adc ch
	ADCx->CR |= (1<<2);						//start conversion
	while ((ADCx->ISR & (1<<2)) == 0) continue;	//wait for conversion to end (EOC set at end of conversion)
	return ADCx->DR;						//return adc result and clears the EOC bit
}

