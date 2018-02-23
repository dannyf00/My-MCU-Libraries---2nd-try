/*
 */
//#include <regx51.h>							//we use keil c51
//#include <pic24.h>							//we use pic24
//#include <htc.h>							//we use picc
//#include <pic24.h>							//we use pic24f
//#include <ioavr.h>
//#include <avr/io.h>
//#include <macros.h>
//#include "gpio.h"
//#include "delay.h"
#include "spi_sw.h"

//initialize the spi module
void spi_init(void) {
#if defined(SPI_MISO)
	IO_IN(SPI_DDR, SPI_MISO);				//input pins
#endif

#if defined(SPI_MOSI)
	SPI_CLR(SPI_PORT, SPI_MOSI);	//clear output pins
	IO_OUT(SPI_DDR, SPI_MOSI);	//set pins as output
#endif

	SPI_CLR(SPI_PORT, SPI_SCK);				//clear sck
	IO_OUT(SPI_DDR, SPI_SCK);				//sck as output
}

//transmission on sck's rising edge
void spi_write(unsigned char data_t) {
	unsigned char mask = 0x80;				//start with the most signifcant bit

	IO_OUT(SPI_DDR, SPI_MOSI);				//mosi as output
	//SPI_CLR(SPI_PORT, SPI_SCK);			//default state of sck: low
	while (mask) {
		SPI_CLR(SPI_PORT, SPI_SCK);			//clear spi_sck

#if defined(SPI_MOSI)
		if (data_t & mask) SPI_SET(SPI_PORT, SPI_MOSI);	//send the data
		else SPI_CLR(SPI_PORT, SPI_MOSI);
#endif
		SPI_SET(SPI_PORT, SPI_SCK);			//send on the rising edge
		SPI_DELAY(SPI_DLY);				//insert some delays to generate 50% dc
		mask = mask >> 1;					//next bit
	}
	//SPI_CLR(SPI_PORT, SPI_MOSI);			//clear mosi
	SPI_CLR(SPI_PORT, SPI_SCK);				//clear sck
}

//reading spi on the falling edge
unsigned char spi_read(void) {
	unsigned char mask = 0x80;				//start with the most signifcant bit
	unsigned char data_t=0;					//tmp

	IO_IN(SPI_DDR, SPI_MISO);				//miso as input
	//SPI_CLR(SPI_PORT, SPI_SCK);			//drive spi low
	while (mask) {
		//data_t = data_t << 1;				//msb first
		SPI_SET(SPI_PORT, SPI_SCK);			//send on the rising edge

		//if (SPI_PORT_IN & SPI_MISO) data_t |= 0x01;
#if defined(SPI_MISO)
		if (IO_GET(SPI_PORT_IN, SPI_MISO)) data_t |= mask;	//if miso is high, set the bit
		else data_t &=~mask;				//if miso is low, clear the bit
#endif
		SPI_CLR(SPI_PORT, SPI_SCK);			//clear spi_sck
		SPI_DELAY(SPI_DLY);				//insert some delays to generate 50% dc

		mask = mask >> 1;					//next bit
	}
	//SPI_CLR(SPI_PORT, SPI_MOSI);				//clear mosi
	return data_t;							//return the buffer
}

//writing data on sck's rising edge
//reading data on sck's falling edge
unsigned char spi_write_read(unsigned char data_t) {
	unsigned char mask = 0x80;				//start with the most signifcant bit

	//SPI_CLR(SPI_PORT, SPI_SCK);			//default state of sck: low
	while (mask) {
		//send the bit
		SPI_CLR(SPI_PORT, SPI_SCK);			//clear spi_sck

#if defined(SPI_MOSI)
		if (data_t & mask) SPI_SET(SPI_PORT, SPI_MOSI);	//send the data
		else SPI_CLR(SPI_PORT, SPI_MOSI);
#endif

		SPI_SET(SPI_PORT, SPI_SCK);			//send on the rising edge

		//read the bit
		//SPI_DELAY(SPI_DLY);				//insert some delays to generate 50% dc
		//SPI_CLR(SPI_PORT, SPI_SCK);			//clear spi_sck
#if defined(SPI_MISO)
		if (IO_GET(SPI_PORT_IN, SPI_MISO)) data_t |= mask;	//if miso is high, set the bit
		else data_t &=~mask;				//if miso is low, clear the bit
#endif
		SPI_CLR(SPI_PORT, SPI_SCK);			//clear spi_sck

		mask = mask >> 1;					//next bit
	}
	//SPI_CLR(SPI_PORT, SPI_MOSI);			//clear mosi
	SPI_CLR(SPI_PORT, SPI_SCK);				//clear sck

	return data_t;
}

