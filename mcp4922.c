#include <regx51.h>
#include "gpio.h"
#include "spi_sw.h"							//we use software i2c
#include "mcp4922.h"						//own header file

void mcp4922_init(void) {					//reset mcp4922
	//IO_SET(MCP4922_PORT, MCP4922_LDAC);		//set ldac
	//IO_OUT(MCP4922_DDR, MCP4922_LDAC);		//ldac as output
}

//#define mcp4922_write(word_t) 	{spi_write((word_t)>>8); spi_write((word_t)&0x00ff);}
