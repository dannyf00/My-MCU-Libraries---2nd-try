//#include <avr/io.h>
#include "gpio.h"
#include "spi_hw.h"
#include "hc595_spi.h"

void hc595_init(void) {
	IO_CLR(HC595_PORT, HC595_RCK);				//clear rck
	IO_OUT(HC595_DDR, HC595_RCK);				//rck as output
}

unsigned char hc595_write(unsigned char ch) {
	spi_write(ch);
	IO_SET(HC595_PORT, HC595_RCK);				//set rck to strobe out the data
	IO_CLR(HC595_PORT, HC595_RCK);				//clear rck
	return 0;
}
