#ifndef MCP41XXX_H_INCLUDED
#define MCP41XXX_H_INCLUDED


//hardware configuration
//end hardware configuration

#include "gpio.h"							//we use gpio
#include "stdint.h"							//we use uintn_t types
#include "spi_sw.h"							//we use spi software

//global defines
//memory addresses
#define MCP41XXX_P0				0x01		//wiper0, volatile
#define MCP41XXX_P1				0x02		//wiper1, volatile

//command bits
#define MCP41XXX_CMD_NOP		0x00		//command bits -> write
#define MCP41XXX_CMD_WRITE		0x10		//command bits -> increment
#define MCP41XXX_CMD_SHUTDOWN	0x20		//command bits -> decrement
#define MCP41XXX_CMD_NONE		0x30		//command bits -> read

//eeprom resigers from 0x06 -> 0x0f			//data registers from 0x06 to 0x0f

//global variables

//reset the module
void mcp41xx_init(void);

//write to the device wiper0
void mcp41xxx_write0(uint8_t dat);

//write to the device wiper1
void mcp41xxx_write1(uint8_t dat);

#endif // MCP41XXX_H_INCLUDED
