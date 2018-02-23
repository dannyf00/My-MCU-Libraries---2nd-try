#ifndef MCP3550_H_INCLUDED
#define MCP3550_H_INCLUDED


//#include <pic24.h>						//we use pic24f
#include "gpio.h"
#include "delay.h"						//we use software delays
#include "spi_sw.h"					//we use spi2

//hardware configuration
#define MCP3550_PORT		SPI_PORT
#define MCP3550_DDR			SPI_DDR
#define MCP3550_PORT_IN		SPI_PORT_IN
#define MCP3550_MISO		SPI_MISO
#define MCP3550_CS0			(1<<4)

#define MCP3550_DLY			70
//end hardware configuration

//global defines
#define mcp3550_select(cs)		{mcp3550_deselect(cs); IO_CLR(MCP3550_PORT, cs);}
#define mcp3550_deselect(cs)	{IO_SET(MCP3550_PORT, cs); IO_OUT(MCP3550_DDR, cs);}

//global variables
//initialize mcp3550
void mcp3550_init(void);

//read mcp3550
//single step conversion
uint32_t mcp3550_read(uint8_t cs);

//start a conversion
uint8_t mcp3550_start(uint8_t cs);

#endif // MCP3550_H_INCLUDED
