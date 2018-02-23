#include <Arduino.h>
#include "ltc1451.h"				//we use ltc1451

//hardware configuration
//end hardware configuration

//macros for pin operations
#define PIN_SET(pin)	digitalWrite(pin, HIGH)
#define PIN_CLR(pin)	digitalWrite(pin, LOW)
#define PIN_FLP(pin)	digitalWrite(pin, ~digitalRead(pin))
#define PIN_GET(pin)	digitalRead(pin)
#define PIN_OUT(pin)	pinMode(pin, OUTPUT)
#define PIN_IN(pin)		pinMode(pin, INPUT)

//reset ltc1451
void ltc1451_init(void) {
	PIN_SET(LTC1451_CS);					//cs idles high
	PIN_OUT(LTC1451_CS);

	PIN_CLR(LTC1451_CLK);					//clk idles low
	PIN_OUT(LTC1451_CLK);

	PIN_OUT(LTC1451_DIN);					//din as output
}

//write to ltc1451 - least significant 12 bits
void ltc1451_write(unsigned short dat) {
	unsigned short mask = (1<<11);			//send least significant 12-bit data

	do {
		PIN_CLR(LTC1451_CLK);				//clk low
		if (dat & mask) PIN_SET(LTC1451_DIN);
		else PIN_CLR(LTC1451_DIN);
		PIN_SET(LTC1451_CLK);
		mask = mask >> 1;
	} while (mask);
	PIN_CLR(LTC1451_CLK);
}
