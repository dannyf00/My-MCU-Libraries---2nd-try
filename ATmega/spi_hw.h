/*
 */
//#include <ioavr.h>
//#include <avr/io.h>
//#include <macros.h>
//#include "gpio.h"

#define SPI_PORT				PORTB
#define SPI_DDR					DDRB
//#define SPI_CS					(1<<0)
#define SPI_SCK					(1<<1)
#define SPI_MOSI				(1<<2)
#define SPI_MISO				(1<<3)
#define SPI_SELECT(cs)			{IO_CLR(SPI_PORT, cs); IO_OUT(SPI_DDR, cs);}	//select the chip
#define SPI_DESELECT(cs)		{IO_SET(SPI_PORT, cs); IO_OUT(SPI_DDR, cs);}	//deselect the chip
#define spi_select(cs)			SPI_SELECT(cs)
#define spi_deselect(cs)		SPI_DESELECT(cs)

void spi_init(/*unsigned char cs*/);				//initialize the spi

void spi_write(unsigned char data_t);//send data_t over spi

unsigned char spi_read(void);		//read from spi

unsigned char spi_write_read(unsigned char data_t);//send / read data_t over spi
