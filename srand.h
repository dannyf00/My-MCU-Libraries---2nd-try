#ifndef SRAND_H_
#define SRAND_H_

//use adc to produce a random number

//hardware configuration
#define ADC_SRAND		ADC_AN0			//srand's adc channel
//end hardware configuration

//global defines

//global variables

//generate 8-bit random number
unsigned char srand8(void);

//generate 16-bit random number
unsigned short srand16(void);

//generate 32-bit random number
unsigned long srand32(void);

#endif /*SRAND_H_*/
