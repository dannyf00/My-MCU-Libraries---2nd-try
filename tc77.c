#include <regx51.h>
#include "gpio.h"
#include "delay.h"
#include "tc77.h"

void tc77_init(void) {							//reset tc77
	IO_CLR(TC77_PORT, TC77_SCK);				//clera sck
	IO_OUT(TC77_DDR, TC77_SCK);					//sck as output

	IO_IN(TC77_DDR, TC77_SIO);					//sio in high z
}

//read from tc77
//assume that device has been selected prior
signed short tc77_read(void) {					//read a word from tc77
	unsigned short mask = 0x8000;					//mask. most significant bit first
	unsigned short tmp=0x0000;						//temp variable

	IO_IN(TC77_DDR, TC77_SIO);						//sio as input / high z
	do {
		IO_CLR(TC77_PORT, TC77_SCK);					//sck cleared
		if (TC77_PORT_IN & TC77_SIO) tmp|=mask;	//read 1
		else tmp|=0x0000;							//for equal timing
		IO_SET(TC77_PORT, TC77_SCK);				//sck goes high
		mask = mask >> 1;							//next bit
	} while (mask);
	IO_CLR(TC77_PORT, TC77_SCK);					//sck cleared
	return tmp>>3;									//last 3 bits not used
}

//write to tc77
//assume that device has been selected prior
signed short tc77_write(signed short word_t) {		//write a word to tc77
	unsigned short mask = 0x8000;					//mask. most significant bit first
	unsigned short tmp=0x0000;						//temp variable

	tmp=tc77_read();								//read the temperature
	
	IO_OUT(TC77_DDR, TC77_SIO);						//sio as output
	do {
		IO_CLR(TC77_PORT, TC77_SCK);					//sck cleared
		if (word_t & mask) IO_SET(TC77_PORT, TC77_SIO);	//write 1
		else IO_CLR(TC77_PORT, TC77_SIO);				//write 0
		IO_SET(TC77_PORT, TC77_SCK);				//sck goes high
		mask = mask >> 1;							//next bit
	} while (mask);
	IO_CLR(TC77_PORT, TC77_SCK);					//sck cleared
	return tmp;									//last 3 bits not used
}
