#ifndef USISPI_H_INCLUDED
#define USISPI_H_INCLUDED

//#include <avr/io.h>							//we use gcc-avr
#include "gpio.h"

//hardware configuration
#define USI_PORT		PORTB
#define USI_DDR			DDRB
#define USI_USCK		(1<<2)				//USCK on PB2
#define USI_DO			(1<<1)				//DO on PB1
#define USI_DI			(1<<0)				//DI on PB0
//end hardware configuration

//global defines
#define SPI_SELECT(cs)		do {IO_CLR(CS_PORT, cs); IO_OUT(CS_DDR, cs);} while (0)
#define SPI_DESELECT(cs)	do {IO_SET(CS_PORT, cs); IO_OUT(CS_DDR, cs);} while (0)
#define spi_select(cs)		SPI_SELECT(cs)
#define spi_deselect(cs)	SPI_DESELECT(cs)

//used to control speed
#define usispi_dly(n)		do {NOP();} while (0)

//global variables

//initialize spi
//software clock (strobe USICLK bit on USICR
void spi_init(void);

//write to spi
uint8_t spi_write(uint8_t dat);

//read from spi
uint8_t spi_read(void);

#endif // USISPI_H_INCLUDED
