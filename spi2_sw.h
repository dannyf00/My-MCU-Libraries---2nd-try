#ifndef __SPI2_SW_H
#define __SPI2_SW_H

#include "gpio.h"									//we use gpio

//hardware configuration
#define SPI2_PORT				LATB
#define SPI2_PORT_IN			PORTB
#define SPI2_DDR				TRISB
//#define SPI2_CS				(1<<0)
#define SPI2_SCK				(1<<14)					//serial clock
//#define SPI2_MOSI				(1<<2)					//mask out slave in
#define SPI2_MISO				(1<<13)					//master in slave out
//end hardware configuration

//Global defines
//#define SPI2_DLY				0
#define SPI2_DELAY(n)			{/*NOP(); delay(n);*/}	//some delay
#define SPI2_SELECT(cs)			{spi2_deselect(cs); IO_CLR(SPI2_PORT, cs);}	//select the chip
#define SPI2_DESELECT(cs)		{IO_SET(SPI2_PORT, cs); IO_OUT(SPI2_DDR, cs);}	//deselect the chip
#define spi2_select(cs)			SPI2_SELECT(cs)			//select the spi attached to cs pin
#define spi2_deselect(cs)		SPI2_DESELECT(cs)		//deselect the spi attached to cs pin
//#define SPI2_SET(port, pins)	IO_SET(port, pins)		//use FIO_SET() or IO_SET()
//#define SPI2_CLR(port, pins)	IO_CLR(port, pins)		//use FIO_CLR() or IO_CLR()

void spi2_init(void);									//initialize the spi

void spi2_write(unsigned char data_t);					//send data_t over spi

unsigned char spi2_read(void);							//read data from spi

unsigned char spi2_write_read(unsigned char data_t);		//write / read data from spi

#endif
