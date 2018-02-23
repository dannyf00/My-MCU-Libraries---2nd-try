#include "gpio.h"
#include "hc595.h"

void hc595_init(void) {
	IO_CLR(HC595_PORT, HC595_SCK | HC595_MOSI | HC595_RCK);		//clear hc595 pins
	IO_OUT(HC595_DDR, HC595_SCK | HC595_MOSI | HC595_RCK);		//hc595 pins as output
}

unsigned char hc595_write(unsigned char data_byte) {
	unsigned char mask = 0x80;			//send highest bit first

	//IO_CLR(HC595_PORT, HC595_RCK);		//clear rck / sck
	do {
		IO_CLR(HC595_PORT, HC595_SCK);	//clear the clock
		if (mask & data_byte) IO_SET(HC595_PORT, HC595_MOSI);
		else IO_CLR(HC595_PORT, HC595_MOSI);
		IO_SET(HC595_PORT, HC595_SCK);	//strobe out the data
		mask = mask >> 1;				//shift to the next bit
	} while (mask);
	IO_CLR(HC595_PORT, HC595_SCK);		//sck cleared
	//IO_SET(HC595_PORT, HC595_RCK);		//stroke out data

	return 1;
}
