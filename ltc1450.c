#include <avr/io.h>						//we use gcc avr
#include "gpio.h"
#include "ltc1450.h"					//we use ltc1450

//hardware configuration
//end hardware configuration

//macros to select a chip

void ltc1450_init(void) {
	//initialize the pins
	IO_CLR(LTC1450MSB_PORT, LTC1450MSB);	//clear msb
	IO_OUT(LTC1450MSB_DDR, LTC1450MSB);		//msb as output

	//initialize the lsb pins
	IO_CLR(LTC1450LSB_PORT, LTC1450LSB);	//clear lsb
	IO_OUT(LTC1450LSB_DDR, LTC1450LSB);		//lsb as output

	//initialize the ldac pins
	//IO_CLR(LTC1450CTRL_PORT, LTC1450CTRL_LDAC);	//clear lsb
	//IO_OUT(LTC1450CTRL_DDR, LTC1450CTRL_LDAC);		//lsb as output
}
