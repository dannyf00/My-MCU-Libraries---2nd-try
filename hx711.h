#ifndef HX711_H_INCLUDED
#define HX711_H_INCLUDED

//#include <pic24.h>						//we use pic24f
#include "gpio.h"

//hardware configuration
#define HX711DIN_PORT			PINB		//an input port
#define HX711DIN_DDR			DDRB
#define HX711DIN				(1<<2)

#define HX711SCK_PORT			PORTB
#define HX711SCK_DDR			DDRB
#define HX711SCK				(1<<3)
//end hardware configuration

//global defines
#define HX711_VREFmv			1250			//HX711 Vref = 1.250mv

//global variables

//initialize hx711
void hx711_init(void);

//read hx711, 25 pulses
int32_t hx711_read(void);

//read hx711, x128 gain
//Channel A
#define hx711_readx128()		hx711_read()

//read hx711, x32 gain
//channel B
int32_t hx711_readx32(void);

//read hx711, x64 gain
//Channel A
int32_t hx711_readx64(void);

//test if hx711 is busy
//hx711 is busy when DIN is high
#define hx711_busy()			(IO_GET(HX711DIN_PORT, HX711DIN))
#define hx711_readA128()		hx711_readx128()
#define hx711_readB32()			hx711_readx32()
#define hx711_readA64()			hx711_readx64()

#endif /* HX711_H_INCLUDED */
