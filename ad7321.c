#include <regx51.h>
#include "gpio.h"
#include "spi_sw.h"								//we use software spi
#include "ad7321.h"								//we use ad7321

//reset ad7321
void ad7321_init(void) {
}

//send a word to ad7321
unsigned char ad7321_write(unsigned short word_t) {
	spi_write(word_t >> 8);						//send the msb
	spi_write(word_t & 0x00ff);					//send the lsb
	return 0;
}

//read a word from ad7321
unsigned short ad7321_read(void) {
	unsigned char msb, lsb;
	
	msb=spi_read();						//send the msb
	lsb=spi_read();					//send the lsb
	return ((msb << 8) | lsb) & (~0x2000);	//nulling ad0 bit in the output
}
