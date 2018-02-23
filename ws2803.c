#include "ws2803.h"							//ws2803 prototypes

//hardware configuration
//end hardware configuration

//global defines

//global variables
//uint8_t wRAM[144/8];						//ws1803 ram

//initialize ws2803 module
void ws2803_init(void) {
	IO_SET(WS2803_PORT, WS2803_CKI | WS2803_SDI);	//cki idles high to avoid resetting data
	IO_OUT(WS2803_DDR, WS2803_CKI | WS2803_SDI);

	//send the reset
	//IO_CLR(WS2803_PORT, WS2803_CKI | WS2803_SDI);
	//IO_SET(WS2803_PORT, WS2803_CKI); NOP4(); 
	IO_CLR(WS2803_PORT, WS2803_CKI);		//bring cki low for more than 600us to reset the module
	WS2803_DLY();							//delay at least 600us
	
}


//send 144-bit / 18 bytes of data
void ws2803_send(uint8_t *buf) {
	uint8_t cnt, mask;
	//now, send the data
	for (cnt=0; cnt<18; cnt++) {
		mask = 0x01;						//lsb first, left shift
		do {
			IO_CLR(WS2803_PORT, WS2803_CKI);	//cki idles low
			if (mask & buf[cnt]) IO_SET(WS2803_PORT, WS2803_SDI);	//send a bit
			else IO_CLR(WS2803_PORT, WS2803_SDI);
			IO_SET(WS2803_PORT, WS2803_CKI);	//send a bit -> cki idles high
			mask = mask << 1;
		} while (mask);
	}
}
