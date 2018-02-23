//using gpio pins for adc
//GADC_PIN tied to power via a resistor (to form a ccs) and to ground via a capacitor.
//100K / 0.1uf generally
//returns the time it takes for the capacitor to be charged via the resistor to logic high

#include "gadc.h"

//hardware configuration
#define GADC_PORT		PORTB
#define GADC_DDR		DDRB
#define GADC_PORTIN		PINB
//#define GADC_PIN		(1<<0)				//read / discharge pin
//end hardware configuration

//global defines


//global variables

//reset the gadc module
void adc_init(void) {
	//IO_IN(GADC_DDR, pins);					//pins as input
	//IO_CLR(GADC_PORT, pins);				//pins idles low
}

//read gadc
uint16_t adc_read(uint8_t pins) {
	uint16_t tmp=0;							//temp variable
	IO_CLR(GADC_PORT, pins); IO_OUT(GADC_DDR, pins);	//start discharging
	while (IO_GET(GADC_PORTIN, pins)) continue;	//wait for the port to be disicharged
	IO_IN(GADC_DDR, pins);					//start charging up
	while (IO_GET(GADC_PORTIN, pins) == 0) tmp+=1;		//increment tmp as long as pins is low
	return tmp;
}
