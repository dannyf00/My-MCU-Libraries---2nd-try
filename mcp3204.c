//#include <avr/io.h>
//#include "gpio.h"
//#include "delay.h"
//#include "spi_sw.h"
#include "mcp3204.h"

//code is written for mcp3204/8

#define mcp3208_read(config)		mcp3204_read(config)

#if 1
//sending the 7+8*2 bits with spi routines
unsigned short mcp3204_read(unsigned char config_byte) {
	unsigned short mcp3204_adc;

	config_byte |= MCP3204_START_BIT;					//add the start_bit
	spi_write_read(config_byte >> 2);		//send the first three bits of config
	mcp3204_adc=(0x0f & spi_write_read(config_byte << 6))<<8;	//send d1/d0, and the highest 4 bits
	mcp3204_adc|=spi_write_read(0x00);			//get out the last byte


	return mcp3204_adc;
}

#else
//sending individual bits
unsigned short mcp3204_read(unsigned char config_byte) {
	unsigned short mcp3204_adc;
	unsigned short mask;

	config_byte |= MCP3204_START_BIT;					//add the start_bit
	config_byte = config_byte << 2;			//send in the null bit
	//send config byte (7 bits)
	mask = MCP3204_START_BIT << 2;
	do {
        IO_CLR(SPI_PORT, SPI_SCK);         //sck idles low
        if (config_byte & mask) IO_SET(SPI_PORT, SPI_MOSI);
        else IO_CLR(SPI_PORT, SPI_MOSI);
        IO_SET(SPI_PORT, SPI_SCK);
        mask = mask >> 1;
	} while (mask);

	//receive 12-bits
	mcp3204_adc = 0x0000;
	mask = 0x0800;
	do {
		IO_CLR(SPI_PORT, SPI_SCK);
		if (SPI_PORT_IN & SPI_MISO) mcp3204_adc |= mask;
		else mcp3204_adc |= 0;
		IO_SET(SPI_PORT, SPI_SCK);
		mask = mask >> 1;
	} while (mask);
	return mcp3204_adc;
}
#endif
