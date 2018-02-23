#include "mcp41xxx.h"						//we use mcp41xxx

//hardware configuration

//end hardware configuration

//global defines

//eeprom resigers from 0x06 -> 0x0f			//data registers from 0x06 to 0x0f

//global variables

//reset the module
void mcp41xx_init(void) {
	spi_init();					//reset the spi
}

//write to the device wiper0
void mcp41xxx_write0(uint8_t dat) {
	spi_write(MCP41XXX_P0 | MCP41XXX_CMD_WRITE);	//send the command byte
	spi_write(dat);									//send the data byte
}

//write to the device wiper1
void mcp41xxx_write1(uint8_t dat) {
	spi_write(MCP41XXX_P1 | MCP41XXX_CMD_WRITE);	//send the command byte
	spi_write(dat);									//send the data byte
}

