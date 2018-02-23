//#include <regx51.h>							//we use keil c51
#include <avr/io.h>							//we use gcc-avr
#include "gpio.h"
//#include "delay.h"
#include "led7_sr.h"							//we use led7x8

//hardware configuration
//end hardware configuration

//global variables
//display font for common cathode display - active high
unsigned char const led7_font[]= {
	0x3f,									//0
	0x06,									//1
	0x5b,									//2
	0x4f,									//3
	0x66,									//4
	0x6d,									//5
	0x7d,									//6
	0x07,									//7
	0x7f,									//8
	0x6f,									//9
	0x77,									//A
	0x7c,									//b
	0x39,									//C
	0x5e,									//d
	0x79,									//E
	0x71,									//F
	0x80,									//'.' - dot
	0x00,									//' ' - blank
	0x40									//???????
};

//initialize the led7 display
void led7_init(void) {
	//set up the serial pins
	IO_CLR(SR_PORT, SR_SCK | SR_SDA);	//clear sck/sda
	IO_OUT(SR_DDR, SR_SCK | SR_SDA);	//sck / sda as output

	//if strobe pin is defined
#if defined(SR_STROBE)
	IO_CLR(SR_PORT, SR_STROBE);
	IO_OUT(SR_DDR, SR_STROBE);
#endif
}

//display a char
//write a byte to serial port
void led7_write(unsigned char data_byte) {
	unsigned char mask = 0x80;				//msb first
#ifdef LED7_CA
	data_byte = ~data_byte;					//reverse polarity if common cathode
#endif

	do {
		IO_CLR(SR_PORT, SR_SCK);			//clear the clock
		if (mask & data_byte) IO_SET(SR_PORT, SR_SDA);
		else IO_CLR(SR_PORT, SR_SDA);
		IO_SET(SR_PORT, SR_SCK);		//strobe out the bit
		mask = mask >> 1;				//shift to the next bit
	} while (mask);
}


