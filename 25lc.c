//spi_sw source file

//#include <iccioavr.H>						//we use icc avr
//#include <regx51.h>							//we use keil c51
#include <avr/io.h>							//we use avr gcc
//#include <stdio.h>
#include "gpio.h"
//#include "spi_sw.h"							//we use spi bit bang routines
#include "spi_hw.h"							//we use hardware spi
#include "_25lc.h"							//own header

unsigned char _25LC_CS=0x00;				//hold the value of the current CS line

void _25lc_select(unsigned char cs) {		//select the char
	_25LC_CS = cs;							//reset _25lc_cs

	//need to bring CS high before taking it low to select the chip
	IO_SET(SPI_PORT, _25LC_CS);				//select the chip
	IO_OUT(SPI_DDR, _25LC_CS);

	IO_CLR(SPI_PORT, _25LC_CS);				//select the chip
}

//deselect the cs
void _25lc_deselect(unsigned char cs) {		//deselect the char
	IO_SET(SPI_PORT, _25LC_CS);				//deselect the chip
	IO_OUT(SPI_DDR, _25LC_CS);
	//_25LC_CS = 0x00;							//reset _25lc_cs
}

void _25lc_init(void) {			//initialize _25LCxx
	//doing nothing

	//need to bring CS high to start the 1st transmission
	//IO_OUT(SPI_DDR, _25LC_CS_ALL);	//put those pins in output
	//IO_SET(SPI_PORT, _25LC_CS_ALL);				//set cs pin to disable chip
}

//void _25lc_cs_clr(unsigned int cs) {			//select cs, logic low
	//IO_OUT(SPI_DDR, cs);					//put cs to output mode
//	IO_CLR(SPI_PORT, cs);					//select cs
//}
//#define _25lc_cs_clr(cs)			IO_CLR(SPI_PORT, cs)	//select cs

//void _25lc_cs_set(unsigned int cs) {			//delect
	//IO_OUT(SPI_DDR, cs);					//select the chip to be deselected
//	IO_SET(SPI_PORT, cs);					//deselect the chip, logic low
//}
//#define _25lc_cs_set(cs)			IO_SET(SPI_PORT, cs)	//deselect the chip

void _25lc_write(unsigned short address, unsigned char data_t) {		//write a byte to _25LC

	//write wpen
	//IO_CLR(SPI_PORT, cs);				//set cs low
	//spi_write(_25LC_CMD_WREN);		//send wpen
	//IO_SET(SPI_PORT, cs);				//set cs high to write the enable latch
	//spi_delay(1);						//add some delay
	_25LC_SEND_WREN();					//send the wren

	//IO_CLR(SPI_PORT, cs);				//set cs low again
	_25lc_select(_25LC_CS);				//select the chip
	spi_write(_25LC_CMD_WRITE);			//send the "write" instruction
#ifdef _25LC_16BIT
	spi_write(_25LC_MSB(address));		//send the msb
#endif
	spi_write(_25LC_LSB(address));		//send the lsb
	spi_write(data_t);					//send the data
	_25lc_deselect(_25LC_CS);			//deselect the chip, to start the write process

	//only exit if the chip is ready
	//_25lc_select(_25LC_CS);				//select the chip
	while (_25LC_WIP()) continue;		//wait for the write to finish
	//IO_SET(SPI_PORT, cs);				//unselect the chip
	//_25lc_deselect(_25LC_CS);			//deselect the chip, to start the write process

}

unsigned char _25lc_read(unsigned short address) {		//write to _25LC
	unsigned char data_t;
	//pull cs low
	//IO_CLR(SPI_PORT, cs);					//pull cs low
	_25lc_select(_25LC_CS);				//select the chip
	spi_write(_25LC_CMD_READ);				//send the read command
#ifdef _25LC_16BIT
	spi_write(_25LC_MSB(address));			//send the msb of address
#endif
	spi_write(_25LC_LSB(address));			//send the lsb of address
	data_t=spi_read();						//read from the slave
	//IO_SET(SPI_PORT, cs);					//pull cs high
	_25lc_deselect(_25LC_CS);				//deselect the chip
	return data_t;
}

unsigned char _25lc_read_status(void) {			//read wpen status register
	unsigned char data_t;
	//pull cs low
	//IO_CLR(SPI_PORT, cs);					//pull cs low
	_25lc_select(_25LC_CS);					//select the chip
	spi_write(_25LC_CMD_RDSR);				//send the status register
	data_t=spi_read();						//read from the slave
	//IO_SET(SPI_PORT, cs);					//pull cs high
	_25lc_deselect(_25LC_CS);				//deselect the chip
	return data_t;
}

void _25lc_write_status(unsigned char status) {			//read wpen status register
	//pull cs low
	//IO_CLR(SPI_PORT, cs);					//pull cs low
	_25lc_select(_25LC_CS);					//select the chip
	spi_write(_25LC_CMD_WRSR);				//send the write-status register command
	spi_write(status);						//read from the slave
	//IO_SET(SPI_PORT, cs);					//pull cs high
	_25lc_deselect(_25LC_CS);				//deselect the chip
}

void _25lc_page_erase(unsigned short address) {		//erase a page
	_25LC_SEND_WREN();				//send the wren

	//IO_CLR(SPI_PORT, cs);					//pull cs low
	_25lc_select(_25LC_CS);					//select the chip
	spi_write(_25LC_CMD_PE);				//send the page erase command
#ifdef _25LC_16BIT
	spi_write(_25LC_MSB(address));				//send the msb of address
#endif
	spi_write(_25LC_LSB(address));				//send the lsb of address
	//IO_SET(SPI_PORT, cs);					//pull cs high to start the erase
	_25lc_deselect(_25LC_CS);				//deselect the chip
}

void _25lc_sector_erase(unsigned short address) {		//erase a page
	_25LC_SEND_WREN();				//send the wren

	//IO_CLR(SPI_PORT, cs);					//pull cs low
	_25lc_select(_25LC_CS);					//select the chip
	spi_write(_25LC_CMD_PE);				//send the page erase command
#ifdef _25LC_16BIT
	spi_write(_25LC_MSB(address));				//send the msb of address
#endif
	spi_write(_25LC_LSB(address));				//send the lsb of address
	//IO_SET(SPI_PORT, cs);					//pull cs high to start the erase
	_25lc_deselect(_25LC_CS);				//deselect the chip
}

void _25lc_chip_erase(void) {		//erase a page
	_25LC_SEND_WREN();				//send the wren

	//IO_CLR(SPI_PORT, cs);					//pull cs low
	_25lc_select(_25LC_CS);					//select the chip
	spi_write(_25LC_CMD_CE);				//send the page erase command
	//spi_write(_25LC_MSB(address));				//send the msb of address
	//spi_write(_25LC_LSB(address));				//send the lsb of address
	//IO_SET(SPI_PORT, cs);					//pull cs high to start the erase
	_25lc_deselect(_25LC_CS);				//deselect the chip
}

void _25lc_power_down(void) {		//erase a page
	_25LC_SEND_WREN();				//send the wren

	//IO_CLR(SPI_PORT, cs);					//pull cs low
	_25lc_select(_25LC_CS);					//select the chip
	spi_write(_25LC_CMD_DPD);				//send the page erase command
	//spi_write(_25LC_MSB(address));				//send the msb of address
	//spi_write(_25LC_LSB(address));				//send the lsb of address
	//IO_SET(SPI_PORT, cs);					//pull cs high to start the erase
	_25lc_deselect(_25LC_CS);				//deselect the chip
}

unsigned char _25lc_read_ID(void) {		//erase a page
	unsigned char id;
	//_25LC_SEND_WREN(cs);				//send the wren

	//IO_CLR(SPI_PORT, cs);					//pull cs low
	_25lc_select(_25LC_CS);					//select the chip
	spi_write(_25LC_CMD_RDID);				//send the page erase command
#ifdef _25LC_16BIT
	spi_write(_25LC_MSB(0x0000));			//send msb of a dummy address (0x0000)
#endif
	spi_write(_25LC_LSB(0x0000));			//send lsb of a dummy address (0x0000)
	id=spi_read();
	//IO_SET(SPI_PORT, cs);					//pull cs high to start the erase
	_25lc_deselect(_25LC_CS);				//deselect the chip
	return id;
}

