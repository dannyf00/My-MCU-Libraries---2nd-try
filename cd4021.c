/*
 */

/*
 */

#include <avr/io.h>						//we use gcc avr
#include "gpio.h"
#include "cd4021.h"						//we use cd4021

//hardware configuration
//end hardware configuration

void cd4021_init(void) {
	IO_CLR(CD4021_PORT, CD4021_SCK | CD4021_LATCH);
	IO_OUT(CD4021_DDR , CD4021_SCK | CD4021_LATCH);

	IO_IN(CD4021_DDR , CD4021_SDI);
}

unsigned char cd4021_read(void) {
	unsigned char mask = 0x80;
	unsigned char tmp = 0;

	do {
		IO_CLR(CD4021_PORT, CD4021_SCK);
		if (CD4021_PORT_IN & CD4021_SDI) tmp |= mask;
		else tmp |= 0x00;
		IO_SET(CD4021_PORT, CD4021_SCK);
		mask = mask >> 1;
	} while (mask);

	return tmp;
}
