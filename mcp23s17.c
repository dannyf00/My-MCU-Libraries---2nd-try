#include <htc.h>						//we use picc
#include "gpio.h"
#include "delay.h"						//we use software delay
#include "spi_sw.h"						//we use software spi
#include "mcp23s17.h"					//we use mcp23s17

//hardware configuration
//end hardware configuration

unsigned char _mcp23s17_a210=0x00;				//a210, defaults to 0x00

//reset the mcp23s17
void mcp23s17_init(unsigned char a210) {
	_mcp23s17_a210 = a210 & 0x0e;	
}

//write bits
void mcp23s17_write(unsigned char port, unsigned char val) {
	spi_select(MCP23S17_CS);					//select the chip
	spi_write(MCP23S17_ID | _mcp23s17_a210 | MCP23S17_WRITE);	//send the opcode
	spi_write(port);							//send the port
	spi_write(val);								//send the byte
	spi_deselect(MCP23S17_CS);					//deselect the chip
}

//read bits
unsigned char mcp23s17_read(unsigned char port) {
	unsigned char tmp;
	spi_select(MCP23S17_CS);					//select the chip
	spi_write(MCP23S17_ID | MCP23S17_A210 | MCP23S17_READ);	//send the opcode byte
	spi_write(port);							//send the port to be read
	tmp=spi_read();								//read the data
	spi_deselect(MCP23S17_CS);					//deselect the chip
	return tmp;
}

//clear pins
void mcp23s17_clr(unsigned char port, unsigned char pins) {
	unsigned char tmp;
	tmp=mcp23s17_read(port);					//read port
	mcp23s17_write(port, tmp & (~pins));		//clear pins
}

//set pins
void mcp23s17_set(unsigned char port, unsigned char pins) {
	unsigned char tmp;
	tmp=mcp23s17_read(port);					//read port
	mcp23s17_write(port, tmp | ( pins));		//set pins
}
		
//clear gpiodir to put pins to output mode
#define mcp23s17_out(port, pins)				mcp23s17_clr(port, pins)
//set gpiodir to put pins to input mode
#define mcp23s17_in(port, pins)					mcp23s17_set(port, pins)
