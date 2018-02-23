#ifndef SPI_HW_H_
#define SPI_HW_H_

//header file for software spi
//#include "delay.h"

//hardware configuration
//need to be tailored for specific application
#define SPI_PORT		PORTC		//port where spi pins are on
#define SPI_DDR			TRISC		//spi port's output direction register
#define SPI_SCK			(1<<3)		//spi clock pin
#define SPI_SDI			(1<<4)		//spi serial data in pin, from slave to master
#define SPI_SDO			(1<<5)		//spi serial data out pin, from mcu/master to slave
#define BF			SSPSTATbits.BF	//buffer full bit
//end of hardware configuration

#define spi_select(cs)		{IO_SET(SPI_PORT, cs); IO_OUT(SPI_DDR, cs); spi_delay(0); IO_CLR(SPI_PORT, cs);}	//select the chip
#define spi_deselect(cs)	{IO_SET(SPI_PORT, cs); IO_OUT(SPI_DDR, cs);}	//deselect the chip

#define spi_delay(n)	{/*NOP(); NOP(); NOP();*/}	//delay, to help produce 50% duty cycle in sck
//#define spi_delay(dly)				//no delay. 

//spi sdi/sdo transmitting on rising edge of sck
//spi sck idles low
//read / write on the rising edge of the sck (sdi on the falling edge of sck, actually)
void spi_init(void);

//write a bit to spi. not used
void spi_write_bit(unsigned char bit_var);

//write a byte to spi
unsigned char spi_write(unsigned char byte);

//read a bit from spi. not used
unsigned char spi_read_bit(void);

//read a byte from spi.
unsigned char spi_read(void);
		
#endif
