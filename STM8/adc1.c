#include "adc1.h"							//we use adc1


//hardware configuration
//end hardware configuration

//global defines

//global variables

//initialize the adc
void adc_init(void) {
	//enable the clock to the adc
	CLK->PCKENR2 |= CLK_PCKENR2_ADC;		
	
	//stop the adc
	//ADC1->CR1 &=~ADC1_CR1_ADON;				//'0'->disable adc
	
	ADC1->CR1 = (0x7 << 4) |				//0b111->fMaster / 18. 0b110-> 12:1, 0b101->10:1, ...
				(0<<1) |					//'0'->single conversion, '1'->continuous conversion
				(0<<0);						//'0'->ADC off, '1'->ADC on
	ADC1->CR2 = (1<<3) |					//'1'->right aligned, '0'->left aligned
				(0<<1);						//'0'->scan disabled
	ADC1->CR3 = (0<<7);						//'0'->buffer disabled
}

//read the adc
uint16_t adc_read(uint8_t ch) {
	uint16_t i;
	//IO_IN(GPIOB, 1<<0);						//ain0 on pb0
	
	ADC1->CSR &=~ADC1_CSR_EOC;				//clear the flag from prior conversion
	//ADC1->CR1 &=~ADC1_CR1_ADON;				//disable the adc for now
	ADC1->CSR = (ADC1->CSR &~ADC1_CSR_CH) | (ch & ADC1_CSR_CH);	//select the channel
	ADC1->CR1 |= ADC1_CR1_ADON;				//turn it on first time
	//wait for tSTAB = 7us typical
	//for (i=0; i<ADC_DLY; i++) ADC1->DRH;	//waste some time
	ADC1->CR1 |= ADC1_CR1_ADON;				//start it the 2nd time
	while ((ADC1->CSR & ADC1_CSR_EOC) == 0)	continue;	//wait for the conversion to end
	ADC1->CR1 &=~ADC1_CR1_ADON;				//turn off the adc
	i = ADC1->DRL;							//must read the lsb first for right aligned adc. read msb first for left aligned adc
	i|= (ADC1->DRH) << 8;					//retrive the data
	return i;
}
