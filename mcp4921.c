#include <regx51.h>
#include "gpio.h"
#include "spi_sw.h"							//we use software i2c
#include "mcp4921.h"						//own header file

void mcp4921_init(void) {					//reset mcp4822
	//IO_SET(MCP4822_PORT, MCP4822_LDAC);		//set ldac
	//IO_OUT(MCP4822_DDR, MCP4822_LDAC);		//ldac as output
}

//#define mcp4921_write(word_t) 	{spi_write((word_t)>>8); spi_write((word_t)&0x00ff);}
