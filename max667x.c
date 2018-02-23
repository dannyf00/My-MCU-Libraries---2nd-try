#include <regx51.h>							//we use keil c51
#include "gpio.h"
#include "spi_sw.h"							//we use software spi
#include "max667x.h"						//we use max6675/6674

//hardware configuration
//end hardware configuration

//initialize max6675
void max667x_init(void) {
}

//read from max6675
//bit 15 is always 0.
//bit 14.. 3 contain msb..lsb
//bit 2 is normally low but goes high if the coupler is open
//bit 1 is always 0
//bit 0 is tri-state
unsigned short max667x_read(void) {
	unsigned char msb, lsb;

	msb = spi_read();						//read the msb
	lsb = spi_read();						//read the lsb

	return (msb << 8) | lsb;
}
