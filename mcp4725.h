//hearder file for mcp4725 i2c adc
//write to dac register only
//no support for configuration / eeprom

//hardware configuration
//end hardware configuration

#define MCP4725_I2C_ID			0xc0		//mcp4725's i2c id

//a210 lines, per the datasheet
#define MCP4725_A0			0x00		//A0 configuration for a210
#define MCP4725_A1			0x04		//A1 configuration for a210
#define MCP4725_A2			0x08		//A2 configuration for a210
#define MCP4725_A3			0x0a		//A3 configuration for a210
#define MCP4725_DEFAULT			MCP4725_A0	//a5 is the default a210, per mcp

#define MCP4725_MODE_NORMAL		0x00		//normal mode
#define MCP4725_MODE_PD1K		0x01		//power down, 1k pull down resistor
#define MCP4725_MODE_PD100K		0x02		//power down, 100k pull down resistor
#define MCP4725_MODE_PD500K		0x03		//power down, 500k pull down resistor

void mcp4725_init(void);

//select the i2c device
void mcp4725_select(unsigned char a210x);

//write to the mcp4725's dac
void mcp4725_dac_write(unsigned short val);
