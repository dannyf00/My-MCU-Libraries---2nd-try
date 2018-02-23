#include "adc.h"						//we use adc

#define ADCx				LPC_ADC		//adc module in use
#define ADC_PS				10			//8-bit adc clock divider. to yield a clock < 9Mhz

//reset the adc
void adc_init(void) {
	//enable power to adc - default powered down
	LPC_SYSCON->PDRUNCFG &=~(1<<4);		//'1'->power down adc; '0'->power up adc
	//enable the clock to adc
	LPC_SYSCON->SYSAHBCLKCTRL |= (1<<14);	//12->uart0, 13=uart1, 14=adc
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
		//p0.30 as adc0.0 @ '0b011'
		LPC_IOCON->R_PIO0_30 = (LPC_IOCON->R_PIO0_30 &~(0b111 <<  0)) | (0b011 <<  0);	//'0b011'->P0.32 to adc0.0
		LPC_IOCON->R_PIO0_30&=~((1<<7) | (1<<4));										//'0'->analog mode enabled + disable inputer pullup
		break;
	case ADC_CH1:
		//p0.31 as adc0.1 @ '0b011'
		LPC_IOCON->R_PIO0_31 = (LPC_IOCON->R_PIO0_31 &~(0b111 <<  0)) | (0b011 <<  0);	//'0b011'->P0.31 to adc0.1
		LPC_IOCON->R_PIO0_31&=~((1<<7) | (1<<4));										//'0'->analog mode enabled + disable inputer pullup
		break;
	case ADC_CH2:
		//p1.0 as adc0.2 @ '0b010'
		LPC_IOCON->R_PIO1_0 = (LPC_IOCON->R_PIO1_0 &~(0b111 <<  0)) | (0b010 <<  0);	//'0b010'->P1.0 to adc0.2
		LPC_IOCON->R_PIO1_0&=~((1<<7) | (1<<4));										//'0'->analog mode enabled + disable inputer pullup
		break;
	case ADC_CH3:
		//p1.1 as adc0.3 @ '0b010'
		LPC_IOCON->R_PIO1_1 = (LPC_IOCON->R_PIO1_1 &~(0b111 <<  0)) | (0b010 <<  0);	//'0b010'->P1.1 to adc0.3
		LPC_IOCON->R_PIO1_1&=~((1<<7) | (1<<4));										//'0'->analog mode enabled + disable inputer pullup
		break;
	case ADC_CH4:
		//p1.2 as adc0.4 @ '0b010'
		LPC_IOCON->PIO1_2 = (LPC_IOCON->PIO1_2 &~(0b111 <<  0)) | (0b010 <<  0);	//'0b010'->P1.2 to adc0.4
		LPC_IOCON->PIO1_2&=~((1<<7) | (1<<4));										//'0'->analog mode enabled + disable inputer pullup
		break;
	case ADC_CH5:
		//p1.3 as adc0.5 @ '0b001'
		LPC_IOCON->PIO1_3 = (LPC_IOCON->PIO1_3 &~(0b111 <<  0)) | (0b001 <<  0);	//'0b001'->P1.3 to adc0.5
		LPC_IOCON->PIO1_3&=~((1<<7) | (1<<4));										//'0'->analog mode enabled + disable inputer pullup
		break;
	case ADC_CH6:
		//p1.4 as adc0.6 @ '0b001'
		LPC_IOCON->PIO1_4 = (LPC_IOCON->PIO1_4 &~(0b111 <<  0)) | (0b001 <<  0);	//'0b001'->P1.4 to adc0.6
		LPC_IOCON->PIO1_4&=~((1<<7) | (1<<4));										//'0'->analog mode enabled + disable inputer pullup
		break;
	case ADC_CH7:
		//p1.5 as adc0.7 @ '0b001'
		LPC_IOCON->PIO1_5 = (LPC_IOCON->PIO1_5 &~(0b111 <<  0)) | (0b001 <<  0);	//'0b001'->P1.4 to adc0.7
		LPC_IOCON->PIO1_5&=~((1<<7) | (1<<4));										//'0'->analog mode enabled + disable inputer pullup
		break;
	}
	ADCx->CR = 	(ADCx->CR &~0xff) | (ch & 0xff) |		//set the channel
					0b001<<24;								//start the conversion
	while ((ADCx->GDR & (1<<31)) == 0)	//wait for conversion to complete = bit 31 set
	return (ADCx->GDR >> 6) & 0x03ff;				//return the results - 10bit

}
