#ifndef __SPI_SW_H
#define __SPI_SW_H

#include "gpio.h"									//we use gpio

/*
 */
//hardware configuration
#define SPI_PORT			GPIOB
#define SPI_PORT_IN			GPIOB
#define SPI_DDR				GPIOB
//#define SPI_CS				(1<<0)
#define SPI_SCK				(1<<7)					//serial clock
#define SPI_MOSI			(1<<6)					//mask out slave in
#define SPI_MISO			(1<<4)					//master in slave out
//end hardware configuration

//Global defines
//#define SPI_DLY				0
#define SPI_DELAY(n)		{/*NOP(); delay(n);*/}				//some delay
#define SPI_SELECT(cs)		{spi_deselect(cs); IO_CLR(SPI_PORT, cs);}	//select the chip
#define SPI_DESELECT(cs)	{IO_SET(SPI_PORT, cs); IO_OUT(SPI_DDR, cs);}	//deselect the chip
#define spi_select(cs)		SPI_SELECT(cs)			//select the spi attached to cs pin
#define spi_deselect(cs)	SPI_DESELECT(cs)		//deselect the spi attached to cs pin
#define SPI_SET(port, pins)	FIO_SET(port, pins)		//use FIO_SET() or IO_SET()
#define SPI_CLR(port, pins)	FIO_CLR(port, pins)		//use FIO_CLR() or IO_CLR()

void spi_init(void);			//initialize the spi

void spi_write(unsigned char data_t);		//send data_t over spi

unsigned char spi_read(void);				//read data from spi

unsigned char spi_write_read(unsigned char data_t);				//write / read data from spi

#endif
