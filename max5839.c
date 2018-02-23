/*
 */

#include <avr/io.h>						//we use gcc avr
#include "gpio.h"
#include "max5839.h"					//we use max5839

//hardware configuration
//#define MAX5839_CS0				(1<<0)
//end hardware configuration


//initialize the pins
void max5839_init(void) {
	//initialize the data pins
	IO_CLR(MAX5839MSB_PORT, MAX5839MSB);		//clear msb
	IO_OUT(MAX5839MSB_DDR, MAX5839MSB);			//msb as output

	IO_CLR(MAX5839LSB_PORT, MAX5839LSB);		//clear lsb
	IO_OUT(MAX5839LSB_DDR, MAX5839LSB);			//lsb as output

	//initialize the control pins
	IO_CLR(MAX5839CTRL_PORT, MAX5839CTRL_A2 | MAX5839CTRL_A1 | MAX5839CTRL_A0);
	IO_OUT(MAX5839CTRL_DDR, MAX5839CTRL_A2 | MAX5839CTRL_A1 | MAX5839CTRL_A0);

	//initialize the latch
	max5839_latch();
}

