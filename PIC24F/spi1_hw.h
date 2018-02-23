#ifndef __SPI1_HW_H
#define __SPI1_HW_H

//**************caution**********************
//due to spi bugs in the module
//1. no more than 8 bytes can be written to the buffer - or no transmission will be done
//2. use SPIxRBF flag as much as possible
//3. SPI clock not be too fast - 1:4 or less
//*******************************************

#include "gpio.h"			//we use spi modules

//header file for pic24 hardware spi

//hardware configuration
#define SPI1_GPIO			GPIOB
#define SPI1_SCK()			PPS_SCK1OUT_TO_RP(6)		//remap sck9.
#define SPI1_MOSI()			PPS_SDO1_TO_RP(7)			//remap sdo. comment if not used
#define SPI1_MISO()			PPS_SDI1_TO_RP(8)			//remap sdi. comment if not used
#define spi1_busy()			(SPI1STATbits.SRMPT==0)		//0=SPIx_SR not empty
//end hardware configuration

#define F_SPI1				100000ul					//(spi frequency, in hz)

#define spi1_select(cs)		{spi1_deselect(cs); GIO_CLR(SPI1_GPIO, cs);}
#define spi1_deselect(cs)	{GIO_SET(SPI1_GPIO, cs); GIO_OUT(SPI1_GPIO, cs);}

//#define SPI1_PORT			SPI1_GPIO->LAT
//#define SPI1_PORT_IN		SPI1_GPIO->PORT
//#define SPI1_DDR			SPI1_GPIO->TRIS

void spi1_init(void);

//void spi_write(unsigned char dat);
#define spi1_write(n)		spi1_write_read(n)

//#define spi1_read()			spi_write_read(0x00)
unsigned char spi1_read(void);

unsigned char spi1_write_read(unsigned char dat);

//spi busy signal
//1=spi transmission in progress
//0=spi transmission has ended
//unsigned char spi1_busy(void);

#endif //spi_hw_h_

