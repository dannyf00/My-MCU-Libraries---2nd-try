//header file for mcp23s17

//hardware configuration
#define MCP23S17_PORT			GPIO
#define MCP23S17_DDR			TRISIO
#define MCP23S17_CS				(1<<2)
//end hardware configuration

#define MCP23S17_ID				0x40			//device id
#define MCP23S17_A210			0x00			//a210 all grounded
#define MCP23S17_READ			0x01			//read command
#define MCP23S17_WRITE			0x00			//write command

//IOCONBANK=0
//register addresses
#define MCP23S17_IODIRA			0x00			//io direction register. 1=input, 0=output
#define MCP23S17_IODIRB			0x01
#define MCP23S17_IPOLA			0x02			//io polarity register. 1=opposite logic. 0= same logic
#define MCP23S17_IPOLB			0x03
#define MCP23S17_GPINTENA		0x04			//ioc control register. 1=enable ioc. 0=disable ioc
#define MCP23S17_GPINTENB		0x05
#define MCP23S17_DEFVALA		0x06			//default compare register for ioc. 
#define MCP23S17_DEFVALB		0x07
#define MCP23S17_INTCONA		0x08			//interrupt control register. 1=compare vs. DEFVAL. 0=compare vs. previous value
#define MCP23S17_INTCONB		0x09
#define MCP23S17_IOCONA			0x0a			//configuration register
#define MCP23S17_IOCONB			0x0b
#define MCP23S17_GPPUA			0x0c			//pull-up control register. 1=pull-up enabled. 0=pull-up disabled.
#define MCP23S17_GPPUB			0x0d
#define MCP23S17_INTFA			0x0e			//interrupt flag register. 1=pin caused interrupt. 0=interrupt not pending
#define MCP23S17_INTFB			0x0f
#define MCP23S17_INTCAPA		0x10			//interrupt capture register -> captures the gpio port value at time of the interrupt. 1=logic high. 0=logic low
#define MCP23S17_INTCAPB		0x11
#define MCP23S17_GPIOA			0x12			//port register.reading from this register reads the port. writing to this register modifies the OLAT register
#define MCP23S17_GPIOB			0x13
#define MCP23S17_OLATA			0x14			//output latch register. writing to this port modifie the output latches that modifies the pins. reading from this port reads the latch, not the port itself
#define MCP23S17_OLATB			0x15

#define IOCON					IOCONA

//iocon bits
#define IOCON_BANK				0x80
#define IOCON_MIRROR			0x40			//1=int pins are internally connected. 0=int pins are not connected
#define IOCON_SEQOP				0x20			//1=sequential operation disabled. 0=sequential operation enabled
#define IOCON_DISSLW			0x10			//1=slew rate disabled. 0=slew rate enabled
#define IOCON_HAEN				0x08			//1=enable mcp23s17 address pins (a210). 0=disable address pins
#define IOCON_ODR				0x04			//1=open drain output (overrides the intpol bit). 0=active driver output
#define IOCON_INTPOL			0x02			//1=active high. 0=active low
#define IOCON_RESERVED			0x01			//reserved/unimplemented.

//reset the mcp23s17
void mcp23s17_init(unsigned char a210);

//write bits
void mcp23s17_write(unsigned char port, unsigned char val);

//read bits
unsigned char mcp23s17_read(unsigned char port);

//clear pins
void mcp23s17_clr(unsigned char port, unsigned char pins);

//set pins
void mcp23s17_set(unsigned char port, unsigned char pins);
		
//clear gpiodir to put pins to output mode
#define mcp23s17_out(port, pins)				mcp23s17_clr(port, pins)
//set gpiodir to put pins to input mode
#define mcp23s17_in(port, pins)					mcp23s17_set(port, pins)
