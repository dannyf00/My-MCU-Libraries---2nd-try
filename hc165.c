//#include <avr/io.h>						//we use gcc avr
#include "gpio.h"
#include "hc165.h"						//we use hc165

//hardware configuration
//end hardware configuration

void hc165_init(void) {
	IO_IN(HC165_DDR, HC165_MISO);		//miso as input

	IO_CLR(HC165_PORT, HC165_SCK);		//clear sck
	IO_SET(HC165_PORT, HC165_PL);		//pl stays high
	IO_OUT(HC165_DDR, HC165_SCK | HC165_PL);		//sck as output
}

unsigned char hc165_read(void) {
	unsigned char mask = 0x80;			//lsb first
	unsigned char tmp;

	IO_IN(HC165_DDR, HC165_MISO);		//miso as input

	//read the shift register
	do {
		IO_CLR(HC165_PORT, HC165_SCK);	//clear sck
		if (HC165_PORT_IN & HC165_MISO) tmp |= mask;	//read 1
		else tmp |= 0x00;								//read 0
		IO_SET(HC165_PORT, HC165_SCK);	//pulse out
		mask = mask >> 1;
	} while (mask);

	//reset the sck
	IO_CLR(HC165_PORT, HC165_SCK);		//sck idles low

	return tmp;							//return the value of the shift register
}
