#include <regx51.h>
#include "gpio.h"
#include "spi_sw.h"							//we use software i2c
#include "mcp4821.h"						//own header file


void mcp4821_init(void) {					//reset mcp4821
	//IO_SET(MCP4821_PORT, MCP4821_LDAC);		//set ldac
	//IO_OUT(MCP4821_DDR, MCP4821_LDAC);		//ldac as output
}

//#define mcp4821_write(word_t) 	{spi_write((word_t)>>8); spi_write((word_t)&0x00ff);}
