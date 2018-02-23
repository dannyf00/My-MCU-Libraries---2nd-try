//#include <p24fxxxx.h>						//we use pic24f
//#include "gpio.h"
#include "adc.h"							//we use hardware adc
//#include "delay.h"						//delay some time

void adc_init(void) {
	_ADC1MD = 0;						//enable power to adc
	AD1CON1 = 	ADC_ADON |					//adc module on
				ADC_ADSIDL_DISCONT |		//stop module in idle
				ADC_FORM_INT |				//adc results = (0000 00dd dddd dddd)
				ADC_SSRC_AUTO |				//adc conversion sequence - conversion ends automatically
				ADC_ASAM_SAMP 				//adc begin after samp is set
				;

	AD1CON2 =	ADC_VCFG_AVDD_AVSS |		//vdd-vss as ref voltage
				ADC_CSCNA_NOSCAN |			//don't scan input
				ADC_BUFM_16x1 |				//buffer full mode: 16x1
				(1<<0)						//always use mux a for input sampling
				;

	AD1CON3 = 	ADC_ADRC_SYSTEM |			//adc on system clock
				ADC_SAMC_32TAD |			//auto sample time = 16tad
				ADC_ADCS_2TCY				//adc clock selection 2tcy
				;
	AD1CSSL = 0;							//scanning disabled
}

unsigned short adc_read(unsigned short adc_ch) {
	unsigned short tmp;
	//set up adc port configuration bits
	//for the positive channel (mux a only)
	_DONE=0;
	//adc_ch = adc_ch & 0x0f;					//adc_ch limited to 16 channels
	//tmp=AD1PCFG;							//save current port configuration setting
	//AD1PCFG = ~(1<<adc_ch);					//configure the port to be analog
	//AD1CHS = adc_ch;						//select the channel
	switch (adc_ch) {
		case ADC_AN0:		AD1PCFG = ~(1<<0); AD1CHS =0x0000; break;
		case ADC_AN1:		AD1PCFG = ~(1<<1); AD1CHS =0x0001; break;
		case ADC_AN2:		AD1PCFG = ~(1<<2); AD1CHS =0x0002; break;
		case ADC_AN3:		AD1PCFG = ~(1<<3); AD1CHS =0x0003; break;
		case ADC_AN4:		AD1PCFG = ~(1<<4); AD1CHS =0x0004; break;
		case ADC_AN5:		AD1PCFG = ~(1<<5); AD1CHS =0x0005; break;
		//case ADC_AN6:			AD1PCFG = ~(1<<6); AD1CHS =0x0006; break;					//not implemented on 28pin devices. do not use
		//case ADC_AN7:			AD1PCFG = ~(1<<7); AD1CHS =0x0007; break;					//not implemented on 28pin devices. do not use
		//case ADC_AN8:			AD1PCFG = ~(1<<8); AD1CHS =0x0008; break;					//not implemented on 28pin devices. do not use
		case ADC_AN9:		AD1PCFG = ~(1<<9); AD1CHS =0x0008; break;
		case ADC_AN10:		AD1PCFG = ~(1<<10); AD1CHS =0x000a; break;
		case ADC_AN11:		AD1PCFG = ~(1<<11); AD1CHS =0x000b; break;
		//case ADC_AN12:		AD1PCFG = ~(1<<12); AD1CHS =0x000c; break;					//not impelemned on 28pin devices. do not use
		case ADC_VCORE:		AD1PCFG = ~(1<<13); AD1CHS =0x000d; break;
		case ADC_VBG_2:		AD1PCFG = ~(1<<14); AD1CHS =0x000e; break;
		case ADC_VBG:		AD1PCFG = ~(1<<15); AD1CHS =0x000f; break;//AD1PCFG = ~adc_ch;					//mux b: not used; mux a: negative is Vref-,
		case ADC_CTMU:		AD1PCFG = ~(0<<0); AD1CHS = 0x001f; break;						//reserved for ctmu
		default: 			break;			//do nothing
	}
	_SAMP = 1;								//start the adc
	while (!_DONE) continue;				//wait for adc to finish
	//AD1PCFG = tmp;							//restore ad1pcfg setting
	return ADC1BUF0;						//return the adc results
}

