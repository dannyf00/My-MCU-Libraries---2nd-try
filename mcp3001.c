#include <regx51.h>
#include "gpio.h"
#include "spi_sw.h"				//we use software spi
#include "mcp3001.h"			//we use mcp3001

void mcp3001_init(void) {
}

unsigned short mcp3001_read(void) {
	unsigned char msb, lsb;
	msb=spi_read();				//read msb
	lsb=spi_read();				//read lsb
	return (msb << 5) | (lsb>>3);	//last 3 bits are lsb
}

