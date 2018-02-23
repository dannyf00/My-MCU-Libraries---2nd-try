#include <pic24.h>						//we use pic24f
//#include "config.h"						//configuration words
#include "gpio.h"
#include "encout.h"						//we use encoder emulator

//hardware configuration
//end hardware configuration

//#define ENC_CW			0
//#define ENC_CCW			1

//reset encoder emulator
void encout_init(void) {
	IO_CLR(OUT_PORT, OUT_A | OUT_B);	//clear a/b pins
	IO_OUT(OUT_DDR, OUT_A | OUT_B);		//ab as output
}

//write encoder output
//step can be positive or negative 1
//bit arrangement: 0bAB
const unsigned char enc_cw[]={
	0b01,				//0b00 -> 0b01
	0b11,				//0b01 -> 0b11
	0b00,				//0b10 -> 0b00
	0b10				//0b11 -> 0b10
};

//counterclockwise - not used
const unsigned char enc_ccw[]={
	0b10,				//0b00 -> 0b10
	0b00,				//0b01 -> 0b00
	0b11,				//0b10 -> 0b11
	0b01				//0b11 -> 0b01
};

unsigned char encout_val(signed char step) {
	//use enc_cw table for clockwise
	if (step==ENC_CW) return enc_cw[((OUT_PORT & OUT_A)?0b10:0b00) | ((OUT_PORT & OUT_B)?0b01:0b00)];
	//use inverse of it for counter-clockwise
	else return ~enc_cw[((OUT_PORT & OUT_A)?0b10:0b00) | ((OUT_PORT & OUT_B)?0b01:0b00)];
}

void encout_write(unsigned char enc_val) {
	if (enc_val & 0b01) IO_SET(OUT_PORT, OUT_B);
	else IO_CLR(OUT_PORT, OUT_B);
	if (enc_val & 0b10) IO_SET(OUT_PORT, OUT_A);
	else IO_CLR(OUT_PORT, OUT_A);
}

