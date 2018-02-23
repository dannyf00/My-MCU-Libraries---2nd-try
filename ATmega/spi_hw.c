/*
 */
//#include <ioavr.h>
#include <avr/io.h>
//#include <macros.h>
#include "gpio.h"
#include "spi_hw.h"

void spi_init(/*unsigned char cs*/) {
	SPCR = 	(1<<SPE) |				//spi enabled
			(0<<DORD) |				//msb first
			(1<<MSTR) |				//set as spi master
			(0<<CPOL) |				//sck idles low
			(0<<CPHA) |				//sample on leading edge
			(0<<SPR1) |				//spr1..0=01 -> spi at 1/16 fcpu
			(1<<SPR0);
	SPSR =	(0<<SPI2X);				//spi2x=0.

	IO_CLR(SPI_PORT, SPI_SCK | SPI_MOSI);	//clear output pins
	//IO_SET(SPI_PORT, cs);		//unselect the chip
	IO_OUT(SPI_DDR, /*cs | */SPI_SCK | SPI_MOSI);	//set pins as output

	IO_IN(SPI_DDR, SPI_MISO);		//input pins
}

void spi_write(unsigned char data_t) {
	SPDR = data_t;					//fill the spi buffer
	while (!(SPSR & (1<<SPIF))) continue;	//wait for the transmission to end
}

unsigned char spi_read(void) {
	SPDR = 0x00;					//dummy send
	while (!(SPSR & (1<<SPIF))) continue;	//wait for the transmission to end
	return SPDR;					//return the buffer
}

unsigned char spi_write_send(unsigned char data_t) {
	SPDR = data_t;					//fill the spi buffer
	while (!(SPSR & (1<<SPIF))) continue;	//wait for the transmission to end
	return SPDR;
}
