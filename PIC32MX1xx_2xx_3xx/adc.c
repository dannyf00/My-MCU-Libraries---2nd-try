#include "adc.h"			//we use adc

//hardware configuration
//end hardware configuration

//global defines

//global variables

//adc
//reste the adc
//automatic sampling (ASAM=1), manual conversion
void adc_init(void) {
	//turn off the adc
	AD1CON1bits.ON = 0;				//0->adc off, 1->adc on

	//configure the adc
	AD1CON1 = 	(0<<15) |			//0->adc off, 1->adc on
				//(0<<14) |			//0->continue adc operation in debug, 1->freeze operation when cpu enters debug
				(0<<13) |			//0->continue operation in idle, 1->stop operation in idle
				(1<< 8) |			//0->16-bit int, 1->16-bit signed, 2->fractional 16-bit, 3->signed fractional 16-bit, 4->32-bit int, 5->signed 32-bit int, 6->fractional 32-bit int, 7->signed fractional 32-bit int
				(0<< 5) |			//0->SAMP triggers sampling, 1->int0 transition triggers adc, 2->timer3 period match triggers sampling, 7->internal counter triggers sampling
				(0<< 4) |			//0->normal operation, 1->stop conversions when the first adc interrupt is generated
				(1<< 2) |			//0->sampling begins when samp is set, 1->sampling begins immediately after last conversion (=continuous mode)
				(0<< 1) |			//0->adc sample/hold amplifier is holding, 1->adc sha is sampling. when asam = 0, writing 1 to this bit starts sampling
				(0<< 0) |			//0->adc conversion is not done, 1->adc conversion is done
				0x00;
	AD1CON2 = 	(0<<13) |			//0->AVDD-AVss, 1->Vref+ - AVss, 2->AVdd - Vref-, 3->Vref+ - Vref-, 4..7->AVdd - AVss
				(0<<12) |			//0->disable offset calibration mode, 1->enable offset calibration mode (VinH and VinL are connected to VR-)
				(0<<10) |			//0->do not scan inputs, 1->scan inputs
				(0<< 7) |			//0->ADC is current filling buffer 0-7, user should access data in 8-15; 1->ADC is currently filling buffer 8-15,  user should access data in 0-7
				(0<< 2) |			//0->interrupt at end of each conversion, 1->interrupt at end of every 2nd conversion, 2->interrupt every 3rd conversion, ...
				(0<< 1) |			//0->buffer configured as one 16-word buffer (ADC1BUF15..0), 1->buffer configured as two 8-word buffer (ADC1BUF7..0, ADC1BUF15..8)
				(0<< 0) |			//0->always use mux a input settings, 1->uses muxA for first sample, then alternate between muxA and muxB
				0x00;
	AD1CON3 = 	//(0<<15) |			//0->clock derived from peripheral bus clock, 1->adc internal rc clock
				(9<< 8) |			//0->not allowed, 1->1TAD, 2->2TAD, ..., 31->31Tad
				(9<< 0) |			//0->Tad=2*TPB, 1->Tad=4Tpb, ..., Tad=512*TPB
				0x00;

	//use muxA always
	//negative input is VR-
	AD1CHSbits.CH0NA = 0;			//0->ch0 negative is VR-, 1->ch0 negative is AN1

	//turn on the adc
	AD1CON1bits.ON = 1;				//0->adc off, 1->adc on
}

//read the adc
int16_t adc_read(uint32_t ch) {

	ch = ch & 0x0f;					//0..15 is valid input
#if defined(AD1PCFG)
	AD1PCFGCLR = (1 << ch);			//1->pin in digital mode, 0->pin in analog mode
#endif
	AD1CHSbits.CH0SA = ch;			//set Ch0 positive input
	//clear the DONE bit -> it is persistent in manual mode
	AD1CON1bits.DONE = 0;
	//start the conversion
	AD1CON1bits.SAMP = 1;			// |= (1<<1);			//set SAMP to start conversion
	//wait for the previous conversion to end
	while (AD1CON1bits.DONE == 0) continue;	//0->conversion on going, 1->conversion done
	return ADC1BUF0;
}
