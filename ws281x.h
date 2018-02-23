#ifndef WS281X_H_INCLUDED
#define WS281X_H_INCLUDED

//#include <pic24.h>						//we use pic24f
#include "gpio.h"

//hardware configuration
#define WS281X_PORT			LATB
#define WS281X_DDR			TRISB
#define WS281X_DIN			(1<<9)
//end hardware configuration

//global defines
//delay 1/3 of a cycle
//#define WS281X_DLY()		do {NOP(); NOP(); NOP(); NOP();} while (0) 	//delay 0.4u
//#define WS281X_10u()		do {NOP64(); NOP64(); NOP64();} while (0)						//delay 10u at least, typical 50us
//#define WS281X_1()			do {IO_SET(WS281X_PORT, WS281X_DIN); WS281X_DLY(); WS281X_DLY(); IO_CLR(WS281X_PORT, WS281X_DIN); WS281X_DLY();} while (0)
//#define WS281X_0()			do {IO_SET(WS281X_PORT, WS281X_DIN); WS281X_DLY(); IO_CLR(WS281X_PORT, WS281X_DIN); WS281X_DLY(); WS281X_DLY();} while (0)
//global variables

//initialize ws281x interface
void ws281x_init(void);

//send 8 bits
void ws281x_send8(uint8_t color);

//send ws281x rgb
#define ws281x_send(r, g, b) 	do {ws281x_send8(g); ws281x_send8(r); ws281x_send8(b);} while (0)

//reset ws281x - at least 10us
#define ws281x_reset()			do {IO_SET(WS281X_PORT, WS281X_DIN); IO_CLR(WS281X_PORT, WS281X_DIN); WS281X_10u(); IO_SET(WS281X_PORT, WS281X_DIN);} while (0)

#endif /* WS281X_H_INCLUDED */
