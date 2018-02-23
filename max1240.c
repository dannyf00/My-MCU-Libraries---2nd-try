#include <regx51.h>
#include "gpio.h"
#include "delay.h"
#include "spi_sw.h"							//we use software spi
#include "max1240.h"						//we use max1240

//reset max1240
void max1240_init(void) {
}

//read max1240
unsigned short max1240_read(void) {
	unsigned char msb, lsb;

	while (!max1240_ready()) continue;	//wait for max1240 to be ready (SPI_MISO high)

	//now max1240 is ready
	msb=spi_read() & 0x7f;					//highest bit ineffective
	lsb=spi_read();							//lsb's highest 5 bits effective

	return (msb<<5) | (lsb>>3);				//12-bit resolution
}
