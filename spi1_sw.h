#ifndef __SPI1_SW_H
#define __SPI1_SW_H

#include "gpio.h"									//we use gpio

//hardware configuration
#define SPI1_PORT				PORTB
#define SPI1_PORT_IN			PORTB
#define SPI1_DDR				TRISB
//#define SPI1_CS				(1<<0)
#define SPI1_SCK				(1<<0)					//serial clock
#define SPI1_MOSI				(1<<2)					//mask out slave in
//#define SPI1_MISO				(1<<2)					//master in slave out
//end hardware configuration

//Global defines
//#define SPI1_DLY				0
#define SPI1_DELAY(n)			{/*NOP(); delay(n);*/}	//some delay
#define SPI1_SELECT(cs)			{spi1_deselect(cs); IO_CLR(SPI1_PORT, cs);}	//select the chip
#define SPI1_DESELECT(cs)		{IO_SET(SPI1_PORT, cs); IO_OUT(SPI1_DDR, cs);}	//deselect the chip
#define spi1_select(cs)			SPI1_SELECT(cs)			//select the spi attached to cs pin
#define spi1_deselect(cs)		SPI1_DESELECT(cs)		//deselect the spi attached to cs pin
//#define SPI1_SET(port, pins)	IO_SET(port, pins)		//use FIO_SET() or IO_SET()
//#define SPI1_CLR(port, pins)	IO_CLR(port, pins)		//use FIO_CLR() or IO_CLR()

void spi1_init(void);									//initialize the spi

void spi1_write(unsigned char data_t);					//send data_t over spi

unsigned char spi1_read(void);							//read data from spi

unsigned char spi1_write_read(unsigned char data_t);		//write / read data from spi

#endif
