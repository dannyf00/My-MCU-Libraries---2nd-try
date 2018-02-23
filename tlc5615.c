/*
 */
#include <avr/io.h>
//#include <macros.h>
#include "gpio.h"
#include "spi_sw.h"
#include "tlc5615.h"

void tlc5615_write(unsigned short val_dac) {	//write val_dac to tlc5616
	val_dac = val_dac << 2;			//prepare the two sub-lsb bits
	spi_write(val_dac>>8);			//send the high byte
	spi_write(val_dac & 0x00ff);		//send the low byte
}
