//hearder file for mcp3221 i2c adc

//hardware configuration
//end hardware configuration

#define MCP3221_I2C_ID			0x90		//mcp3221's i2c id

//a210 lines, per the datasheet
#define MCP3221_A210_A0			0x00		//A0 configuration for a210
#define MCP3221_A210_A1			0x02		//A0 configuration for a210
#define MCP3221_A210_A2			0x04		//A0 configuration for a210
#define MCP3221_A210_A3			0x06		//A0 configuration for a210
#define MCP3221_A210_A4			0x08		//A0 configuration for a210
#define MCP3221_A210_A5			0x0a		//A0 configuration for a210
#define MCP3221_A210_A6			0x0c		//A0 configuration for a210
#define MCP3221_A210_A7			0x0e		//A0 configuration for a210
#define MCP3221_A210_DEFAULT	MCP3221_A210_A5	//a5 is the default a210, per mcp

void mcp3221_init(void);

//select the i2c device
void mcp3221_select(unsigned char a210x);

//read the mcp3221's adc results
unsigned short mcp3221_read(void);
