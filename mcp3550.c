//#include <pic24.h>						//we use pic24f
#include "mcp3550.h"						//we use mcp3550

//hardware configuration
#define mcp3550spi_read			spi_read	//select the spi read routine
//end hardware configuration

//global defines

//global variables

//initialize mcp3550
void mcp3550_init(void) {
	//initialize mcp3550
	//spi module separately initialized
}

//read mcp3550
//single step conversion
uint32_t mcp3550_read(uint8_t cs) {
	uint32_t tmp;
	//IO_SET(SPI2_PORT, SPI2_SCK);		//set sck -> mode 11
	mcp3550_select(cs);		//cs brought low
	tmp = 200000ul;						//over time
	while (tmp-- && (IO_GET(MCP3550_PORT_IN, MCP3550_MISO))) continue;	//wait for SDO/READY to go low
	//while ((IO_GET(MCP3550_PORT_IN, MCP3550_MISO))) continue;	//wait for SDO/READY to go low
	//now data is ready
	tmp = tmp << 8; tmp |= mcp3550spi_read(); //read msb
	tmp = tmp << 8; tmp |= mcp3550spi_read(); //read 2nd msb
	tmp = tmp << 8; tmp |= mcp3550spi_read(); //read lsb
	tmp = tmp << 8; tmp |= mcp3550spi_read(); //read lsb
	//mcp3550spi_read();
	//IO_SET(SPI2_PORT, SPI2_SCK);		//set sck -> mode 11
	//IO_CLR(SPI2_PORT, SPI2_SCK);		//set sck -> mode 11
	//IO_SET(SPI2_PORT, SPI2_SCK);		//set sck -> mode 11
	mcp3550_deselect(cs);
	return tmp;
}

//start a conversion
uint8_t mcp3550_start(uint8_t cs) {
	mcp3550_select(cs);					//pull CS down
	//minimal delay of 50ns, per datasheet
	mcp3550_deselect(cs);				//deselect
	return IO_GET(MCP3550_PORT_IN, MCP3550_MISO);	//0=conversion done; 1=conversion in process
}

