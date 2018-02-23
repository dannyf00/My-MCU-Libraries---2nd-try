#include "rand_adc.h"										//we use prng

//hardware configuration
//end hardware configuration

//global defines

//global variables

//random number generator - 32-bit
uint32_t rand32(void) {
	uint32_t tmp=0;
	uint32_t mask=0x80000000ul;			//msb first
	do {
		if (rand1()) tmp |= mask;
		mask = mask >> 1;
	} while (mask);
	return tmp;
}

//random number generator
uint16_t rand16(void) {
	uint16_t tmp=0;
	uint16_t mask=0x8000;				//msb first
	do {
		if (rand1()) tmp |= mask;
		mask = mask >> 1;
	} while (mask);
	return tmp;
}

//random number generator
uint8_t rand8(void) {
	uint8_t tmp=0;
	uint8_t mask=0x80;					//msb first
	do {
		if (rand1()) tmp |= mask;
		mask = mask >> 1;
	} while (mask);
	return tmp;
}

//random number generator
//1-bit: 0 or 1
