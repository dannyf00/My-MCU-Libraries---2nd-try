#ifndef MCP3421_H_INCLUDED
#define MCP3421_H_INCLUDED

//hardware configuration
//end hardware configuration

//global defines
#define MCP3421_I2C_ADDR			0xd0		//0b1101,xxxW/R, where xxx = a210

//start conversion
#define MCP3421_RDY		0x80			//start conversion

//adc mode
#define MCP3421_OC		0x00			//one-shot mode
#define MCP3421_CON		0x10			//continuous mode

//adc resolution
#define MCP3421_18BITS	0x0c			//18 bits -> 0b11
#define MCP3421_16BITS	0x08			//16 bits -> 0b10
#define MCP3421_14BITS	0x04			//14 bits -> 0b01
#define MCP3421_12BITS	0x00			//12 bits -> 0b00

//gain factors
#define MCP3421_1x		0x00			//1x
#define MCP3421_2x		0x01			//2x
#define MCP3421_4x		0x02			//4x
#define MCP3421_8x		0x03			//8x

//global variables
//unsigned char _mcp3421_addr;	//default to a210=0b000

#define mcp3421_init()					//initialize mcp3421 - does nothing
//void mcp3421_init(void) {
//}

//perform adc conversion
unsigned char mcp3421_read(unsigned char a210, signed long * adc);

//write configuration word to mcp3421
void mcp3421_write(unsigned char a210, unsigned char config);

#endif // MCP3421_H_INCLUDED
