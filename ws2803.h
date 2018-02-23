#ifndef _WS2803_H
#define _WS2803_H

#include "gpio.h"                           //we use gpio functions
#include "delay.h"                          //we use software delays

//hardware configuration
#define WS2803_PORT		GPIO
#define WS2803_DDR		TRISIO
#define WS2803_CKI		(1<<0)				//idles low
#define WS2803_SDI		(1<<1)

#define WS2803_DLY()	delay(50)			//at least 600us delay to reset ws2803

//end hardware configuration

//global defines

//global variables
//uint8_t wRAM[144/8];						//ws1803 ram

//initialize ws2803 module
void ws2803_init(void);

//send 144-bit / 18 bytes of data
void ws2803_send(uint8_t *buf);

#endif
