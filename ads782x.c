#include "ads782x.h"					//we use ads7824/7825

//hardware configuration
//end hardware configuration

//global defines

//global variables

//reset ads782x
void ads782x_init(void) {
	//set up input/output pins
	IO_IN(ADS782X_DDR, ADS782X_BUSY);
	IO_CLR(ADS782X_PORT, ADS782X_A1 | ADS782X_A0);
	IO_SET(ADS782X_PORT, ADS782X_RC);
	IO_OUT(ADS782X_DDR, ADS782X_A1 | ADS782X_A0 | ADS782X_RC);
}

//select a channel, and start the conversion
void ads782x_startch(uint8_t ch) {
	//set R/C high
	IO_SET(ADS782X_PORT, ADS782X_RC);		//brings rc high
	//select the channels
	if (ch & (1<<0)) IO_SET(ADS782X_PORT, ADS782X_A0);
	else IO_CLR(ADS782X_PORT, ADS782X_A0);
	if (ch & (1<<1)) IO_SET(ADS782X_PORT, ADS782X_A1);
	else IO_CLR(ADS782X_PORT, ADS782X_A1);
	IO_CLR(ADS782X_PORT, ADS782X_RC);		//clear RC -> produce a falling edge, and starts a conversion
	//IO_SET(ADS782X_PORT, ADS782X_RC);
}

//read current adc channel
uint16_t ads782x_read(void) {
	uint16_t tmp;
	IO_CLR(ADS782X_PORT, ADS782X_RC);		//clear RC -> produce a falling edge, and starts a conversion
	IO_SET(ADS782X_PORT, ADS782X_RC);
	//now transmission starts
	tmp = spi1_read() << 8;					//read msb
	tmp|= spi1_read();						//read lsb
	return tmp;
}

//returns 1 if ads782x is still busy
#define ads782x_busy()					(IO_GET(ADS782X_PORT_IN, ADS782X_BUSY))?0:1)
