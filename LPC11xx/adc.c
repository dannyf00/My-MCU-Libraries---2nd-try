#include "adc.h"						//we use adc

#define ADCx				LPC_ADC		//adc module in use
#define ADC_PS				10			//8-bit adc clock divider. to yield a clock < 13Mhz

//reset the adc
void adc_init(void) {
	//enable power to adc - default powered down
	LPC_SYSCON->PDRUNCFG &=~(1<<4);		//'1'->power down adc; '0'->power up adc

	//enable the clock to adc
	LPC_SYSCON->SYSAHBCLKCTRL |= (1<<13);	//12->uart, 13=adc
	//LPC_SC->PCLKSEL0 = (LPC_SC->PCLKSEL0 &~(0b11<<24)) | (0b00<<24);	//0b00->4x, 0b01->1x, 0b10->2x, 0b11->8x

	//configure adc
	ADCx->CR = 		(0<<0) |				//select ch (bit0..7) for adc0..7
					((ADC_PS & 0xff) << 8) |			//select 8-bit adc clock divider
					(0<<16) |				//'1'->enable burst mode
					(1<<21) |				//'1'->enable adc
					(0<<24) |				//'0b001'->start conversion
					0x00;
	ADCx->INTEN = 0;					//'0'->disable interrupts
	//now adc is running
}


//read the adc - lowest 10 digits effective
uint32_t adc_read(uint32_t ch) {
	//configure the pins
	switch (ch) {
	case ADC_CH0:
		//p0.11 as adc0.0 @ '0b010'
		LPC_IOCON->R_PIO0_11 = (LPC_IOCON->R_PIO0_11 &~(0b111 <<  0)) | (0b010 <<  0);	//'0b010'->P0.11 to adc0.0
		LPC_IOCON->R_PIO0_11&=~((1<<7) | (1<<4));										//'0'->analog mode enabled + disable pull-up
		break;
	case ADC_CH1:
		//p0.10 as adc0.1 @ '0b010'
		LPC_IOCON->SWCLK_PIO0_10 = (LPC_IOCON->SWCLK_PIO0_10 &~(0b111 <<  0)) | (0b010 <<  0);	//'0b010'->P0.10 to adc0.1
		LPC_IOCON->SWCLK_PIO0_10&=~((1<<7) | (1<<4));										//'0'->analog mode enabled + disable pull-up
		break;
	case ADC_CH2:
		//p1.1 as adc0.2 @ '0b010'
		LPC_IOCON->R_PIO1_1 = (LPC_IOCON->R_PIO1_1 &~(0b111 <<  0)) | (0b010 <<  0);	//'0b010'->P1.1 to adc0.2
		LPC_IOCON->R_PIO1_1&=~((1<<7) | (1<<4));										//'0'->analog mode enabled + disable pull-up
		break;
	case ADC_CH3:
		//p1.2 as adc0.3 @ '0b010'
		LPC_IOCON->R_PIO1_2 = (LPC_IOCON->R_PIO1_2 &~(0b111 <<  0)) | (0b010 <<  0);	//'0b010'->P1.2 to adc0.3
		LPC_IOCON->R_PIO1_2&=~((1<<7) | (1<<4));										//'0'->analog mode enabled + disable pull-up
		break;
	case ADC_CH4:
		//p1.3 as adc0.4 @ '0b010'
		LPC_IOCON->SWDIO_PIO1_3 = (LPC_IOCON->SWDIO_PIO1_3 &~(0b111 <<  0)) | (0b010 <<  0);	//'0b010'->P1.3 to adc0.4
		LPC_IOCON->SWDIO_PIO1_3&=~((1<<7) | (1<<4));										//'0'->analog mode enabled + disable pull-up
		break;
	case ADC_CH5:
		//p1.4 as adc0.5 @ '0b010'
		LPC_IOCON->PIO1_4 = (LPC_IOCON->PIO1_4 &~(0b111 <<  0)) | (0b010 <<  0);	//'0b010'->P1.4 to adc0.5
		LPC_IOCON->PIO1_4&=~((1<<7) | (1<<4));										//'0'->analog mode enabled + disable pull-up
		break;
	case ADC_CH6:
		//p1.10 as adc0.6 @ '0b010'
		LPC_IOCON->PIO1_10 = (LPC_IOCON->PIO1_10 &~(0b111 <<  0)) | (0b010 <<  0);	//'0b010'->P1.10 to adc0.6
		LPC_IOCON->PIO1_10&=~((1<<7) | (1<<4));										//'0'->analog mode enabled + disable pull-up
		break;
	case ADC_CH7:
		//p1.11 as adc0.7 @ '0b010'
		LPC_IOCON->PIO1_11 = (LPC_IOCON->PIO1_11 &~(0b111 <<  0)) | (0b010 <<  0);	//'0b010'->P1.11 to adc0.7
		LPC_IOCON->PIO1_11&=~((1<<7) | (1<<4));										//'0'->analog mode enabled + disable pull-up
		break;
	}
	ADCx->CR = 	(ADCx->CR &~0xff) | (ch & 0xff) |		//set the channel
					0b001<<24;								//start the conversion
	while ((ADCx->GDR & (1<<31)) == 0)	//wait for conversion to complete = bit 31 set
	return (ADCx->GDR >> 4) & 0x0fff;				//return the results - 12bit

}
