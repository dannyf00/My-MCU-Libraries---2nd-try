//#include <regx51.h>						//we use keil c51
//#include <htc.h>							//we use picc
#include "gpio.h"
#include "spi1_sw.h"						//we use software i2c
#include "mcp4822.h"						//own header file

void mcp4822_init(void) {					//reset mcp4822
#if defined(MCP4822_LDAC)
	IO_SET(MCP4822_PORT, MCP4822_LDAC);		//set ldac
	IO_OUT(MCP4822_DDR, MCP4822_LDAC);		//ldac as output
#endif
}


//#define mcp4822_write(word_t) 	{spi_write((word_t)>>8); spi_write((word_t)&0x00ff);}
