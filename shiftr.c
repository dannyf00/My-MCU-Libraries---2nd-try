/*
 */

#include <avr/io.h>						//we use gcc avr
#include "gpio.h"
#include "shiftr.h"						//we use shift registers

//reset the shift register pins
void sr_init(void) {
	IO_CLR(SR_PORT, SR_SCK | SR_MOSI);	//sck / mosi cleared
	IO_OUT(SR_DDR, SR_SCK | SR_MOSI);	//sck / mosi as output

#if defined(SR_LAT)
	IO_CLR(SR_PORT, SR_LAT);			//clear lat
	IO_OUT(SR_DDR, SR_LAT);				//lat as output
#endif
}

//send a byte
void sr_write(unsigned char dat) {
	unsigned char mask = 0x80;			//msb first

	do {
		IO_CLR(SR_PORT, SR_SCK);		//sck idles low
		if (dat & mask) IO_SET(SR_PORT, SR_MOSI);	//send 1
		else IO_CLR(SR_PORT, SR_MOSI);				//send 0
		IO_SET(SR_PORT, SR_SCK);		//strobe out data
		mask = mask >> 1;				//next bit
	} while (mask);

#if defined(SR_LAT)
	IO_CLR(SR_PORT, SR_LAT); IO_SET(SR_PORT, SR_LAT);
#endif
}
