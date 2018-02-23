#define MCP23017_I2C_ID			0x40			//mcp23017's i2c default i2c address

//mcp23017 register map
//icon.bank=0 -> 8bit mode, 0x16 registers
#define MCP23017_IODIRA			0x00
#define MCP23017_IODIRB			0x01
#define MCP23017_IPOLA			0x02
#define MCP23017_IPOLB			0x03
#define MCP23017_GPINTENA		0x04
#define MCP23017_GPINTENB		0x05
#define MCP23017_DEFVALA		0x06
#define MCP23017_DEFVALB		0x07
#define MCP23017_INTCONA		0x08
#define MCP23017_INTCONB		0x09
#define MCP23017_IOCONA			0x0A
#define MCP23017_IOCONB			0x0B
#define MCP23017_GPPUA			0x0C
#define MCP23017_GPPUB			0x0D
#define MCP23017_INTFA			0x0E
#define MCP23017_INTFB			0x0F
#define MCP23017_INTCAPA		0x10
#define MCP23017_INTCAPB		0x11
#define MCP23017_GPIOA			0x12
#define MCP23017_GPIOB			0x13
#define MCP23017_OLATA			0x14
#define MCP23017_OLATAB			0x15

//select mcp23017
void mcp23017_select(unsigned char a210);

//mcp23017 initialization
//currently not used
//potentially can reset the icon registers
#define mcp23017_init()							//for compability reasons

//write a byte to mcp23017
void mcp23017_write(unsigned char ch, unsigned char byte_t);

//read a byte from mcp23017
unsigned char mcp23017_read(unsigned char ch);

#define _VAR_SET(var, mask)		mcp23017_write((var), mcp23017_read(var) | (mask))	//set mask on var
#define _VAR_CLR(var, mask)		mcp23017_write((var), mcp23017_read(var) &(~mask))	//clear mask on var
#define _VAR_FLP(var, mask)		mcp23017_write((var), mcp23017_read(var) ^ (mask))	//flip mask on var

//set / clear pins
#define I2C_SET(port, mask)		_VAR_SET((port), (mask))	//set mask on port
#define I2C_CLR(port, mask)		_VAR_CLR((port), (mask))	//clear mask on port
#define I2C_FLP(port, mask)		_VAR_FLP((port), (mask))	//flip mask on port

//pins as input / output
//set ddr to make an input
//clear ddr to make an output
#define I2C_OUT(ddr, mask)		_VAR_CLR((ddr), (mask))	//mark as output
#define I2C_IN(ddr, mask)		_VAR_SET((ddr), (mask))	//mask as input

