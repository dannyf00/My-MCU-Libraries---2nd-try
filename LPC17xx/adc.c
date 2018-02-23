#include "adc.h"						//we use adc

#define ADCx				LPC_ADC		//adc module in use
#define ADC_PS				10			//8-bit adc clock divider. to yield a clock < 13Mhz

//reset the adc
void adc_init(void) {
	//enable the clock to adc
	LPC_SC->PCONP |= (1<<12);			//'1'@12->enable adc
	LPC_SC->PCLKSEL0 = (LPC_SC->PCLKSEL0 &~(0b11<<24)) | (0b00<<24);	//0b00->4x, 0b01->1x, 0b10->2x, 0b11->8x

	//configure adc
	ADCx->ADCR = 	(0<<0) |				//select ch (bit0..7) for adc0..7
					((ADC_PS & 0xff) << 8) |			//select 8-bit adc clock divider
					(0<<16) |				//'1'->enable burst mode
					(1<<21) |				//'1'->enable adc
					(0<<24) |				//'0b001'->start conversion
					0x00;
	ADCx->ADINTEN = 0;					//'0'->disable interrupts
	//now adc is running
}


//read the adc - lowest 10 digits effective
uint32_t adc_read(uint32_t ch) {
	//configure the pins
	switch (ch) {
	case ADC_CH0:
		//p0.23 as adc0.0 @ '0b01'
		LPC_PINCON->PINSEL1 = (LPC_PINCON->PINSEL1 &~(0b11 << 14)) | (0b01 << 14);	//'0b01'->P0.23 to adc0.0
		break;
	case ADC_CH1:
		//p0.24 as adc0.1 @ '0b01'
		LPC_PINCON->PINSEL1 = (LPC_PINCON->PINSEL1 &~(0b11 << 16)) | (0b01 << 16);	//'0b01'->P0.24 to adc0.1
		break;
	case ADC_CH2:
		//p0.25 as adc0.2 @ '0b01'
		LPC_PINCON->PINSEL1 = (LPC_PINCON->PINSEL1 &~(0b11 << 18)) | (0b01 << 18);	//'0b01'->P0.25 to adc0.2
		break;
	case ADC_CH3:
		//p0.26 as adc0.3 @ '0b01'
		LPC_PINCON->PINSEL1 = (LPC_PINCON->PINSEL1 &~(0b11 << 20)) | (0b01 << 20);	//'0b01'->P0.26 to adc0.3
		break;
	case ADC_CH4:
		//p1.30 as adc0.4 @ '0b11'
		LPC_PINCON->PINSEL3 = (LPC_PINCON->PINSEL3 &~(0b11 << 28)) | (0b11 << 28);	//'0b11'->P1.30 to adc0.4
		break;
	case ADC_CH5:
		//p1.31 as adc0.5 @ '0b11'
		LPC_PINCON->PINSEL3 = (LPC_PINCON->PINSEL3 &~(0b11 << 30)) | (0b11 << 30);	//'0b11'->P1.31 to adc0.5
		break;
	case ADC_CH6:
		//p0.2 as adc0.6 @ '0b10'
		LPC_PINCON->PINSEL0 = (LPC_PINCON->PINSEL0 &~(0b11 <<  6)) | (0b10 <<  6);	//'0b10'->P0.2 to adc0.6
		break;
	case ADC_CH7:
		//p0.3 as adc0.7 @ '0b10'
		LPC_PINCON->PINSEL0 = (LPC_PINCON->PINSEL0 &~(0b11 <<  4)) | (0b10 <<  4);	//'0b10'->P0.3 to adc0.7
		break;
	}
	ADCx->ADCR = 	(ADCx->ADCR &~0xff) | (ch & 0xff) |		//set the channel
					0b001<<24;								//start the conversion
	while ((ADCx->ADGDR & (1<<31)) == 0)	//wait for conversion to complete = bit 31 set
	return (ADCx->ADGDR >> 4) & 0x0fff;				//return the results - 12bit

}
