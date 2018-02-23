//#include <pic24.h>						//we use pic24f
#include "ws281x.h"							//we use ws281x

//hardware configuration
//end hardware configuration

//global defines
//delay 1/3 of a cycle
#define WS281X_DLY()		do {NOP(); NOP(); NOP(); NOP();} while (0) 	//delay 0.4u
#define WS281X_10u()		do {NOP64(); NOP64(); NOP64();} while (0)						//delay 10u at least, typical 50us
#define WS281X_1()			do {IO_SET(WS281X_PORT, WS281X_DIN); WS281X_DLY(); WS281X_DLY(); IO_CLR(WS281X_PORT, WS281X_DIN); WS281X_DLY();} while (0)
#define WS281X_0()			do {IO_SET(WS281X_PORT, WS281X_DIN); WS281X_DLY(); IO_CLR(WS281X_PORT, WS281X_DIN); WS281X_DLY(); WS281X_DLY();} while (0)
//global variables

//initialize ws281x interface
void ws281x_init(void) {
	IO_CLR(WS281X_PORT, WS281X_DIN);	//din idles low
	IO_OUT(WS281X_DDR, WS281X_DIN);	//din as output
}

//send 8 bits
void ws281x_send8(uint8_t color) {
	uint8_t mask = 0x80;				//msb first
	//send bit 7
	if (color & mask) WS281X_1();	//send 1
	else WS281X_0();				//send 0
	mask = mask >> 1;

	//send bit 6
	if (color & mask) WS281X_1();	//send 1
	else WS281X_0();				//send 0
	mask = mask >> 1;

	//send bit 5
	if (color & mask) WS281X_1();	//send 1
	else WS281X_0();				//send 0
	mask = mask >> 1;

	//send bit 4
	if (color & mask) WS281X_1();	//send 1
	else WS281X_0();				//send 0
	mask = mask >> 1;

	//send bit 3
	if (color & mask) WS281X_1();	//send 1
	else WS281X_0();				//send 0
	mask = mask >> 1;

	//send bit 2
	if (color & mask) WS281X_1();	//send 1
	else WS281X_0();				//send 0
	mask = mask >> 1;

	//send bit 1
	if (color & mask) WS281X_1();	//send 1
	else WS281X_0();				//send 0
	mask = mask >> 1;

	//send bit 0
	if (color & mask) WS281X_1();	//send 1
	else WS281X_0();				//send 0
	mask = mask >> 1;

}
//send ws281x rgb
#define ws281x_send(r, g, b) 	do {ws281x_send8(g); ws281x_send8(r); ws281x_send8(b);} while (0)

//reset ws281x - at least 10us
#define ws281x_reset()			do {IO_SET(WS281X_PORT, WS281X_DIN); IO_CLR(WS281X_PORT, WS281X_DIN); WS281X_10u(); IO_SET(WS281X_PORT, WS281X_DIN);} while (0)
