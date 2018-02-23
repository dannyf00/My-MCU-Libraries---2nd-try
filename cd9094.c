#include <regx51.h>							//we use keil c51
#include "gpio.h"
//#include "delay.h"
#include "cd9094.h"							//we use cd9094

//hardware configuration
//end hardware configuration

//initialize the pins
void cd9094_init(void) {
	IO_CLR(CD9094_PORT, CD9094_SCK | CD9094_MOSI);	//clera clock + data pins
	IO_OUT(CD9094_DDR, CD9094_SCK | CD9094_MOSI);	//clock + data pins as output

	IO_CLR(CD9094_PORT, CD9094_LATCH);		//clear latch pin
	IO_OUT(CD9094_DDR, CD9094_LATCH);		//latch pin as output

#if defined(CD9094_OE)
	IO_CLR(CD9094_PORT, CD9094_OE);			//set the pin, disable output
	IO_OUT(CD9094_DDR, CD9094_OE);			//en pin as output
#endif

}

//send a byte to cd9094
void cd9094_write(unsigned char dat) {
	unsigned char mask = 0x80;				//bit mask, msb first
	do {
		IO_CLR(CD9094_PORT, CD9094_SCK);	//clear sck
		if (dat & mask) IO_SET(CD9094_PORT, CD9094_MOSI);	//send 1
		else IO_CLR(CD9094_PORT, CD9094_MOSI);				//send 0
		IO_SET(CD9094_PORT, CD9094_SCK);	//take sck high
		mask = mask >> 1;					//next bit
	} while (mask);
}
