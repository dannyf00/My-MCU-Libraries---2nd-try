#include <htc.h>						//we use picc
#include "adc.h"						//we use adc
#include "srand.h"						//we use srand

//hardware configuration
//#define ADC_SRAND		ADC_AN0			//srand's adc channel
//end hardware configuration

//global defines

//global variables

//generate 8-bit random number
unsigned char srand8(void) {
	unsigned char tmp=0;
	unsigned char mask=0x80;
	
	do {
		tmp |=(adc_read(ADC_SRAND) & 0x01)?mask:0;	//set tmp based on adc's lsb
		mask = mask >> 1;
	} while (mask);
	return tmp;
}

//generate 16-bit random number
unsigned short srand16(void) {
	unsigned short tmp=0;
	unsigned short mask=0x8000;
	
	do {
		tmp |=(adc_read(ADC_SRAND) & 0x01)?mask:0;	//set tmp based on adc's lsb
		mask = mask >> 1;
	} while (mask);
	return tmp;
}

//generate 32-bit random number
unsigned long srand32(void) {
	unsigned long tmp=0;
	unsigned long mask=0x80000000ul;
	
	do {
		tmp |=(adc_read(ADC_SRAND) & 0x01)?mask:0;	//set tmp based on adc's lsb
		mask = mask >> 1;
	} while (mask);
	return tmp;
}
