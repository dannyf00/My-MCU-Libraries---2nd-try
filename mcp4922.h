//hardware configuration
#define MCP4922_PORT			SPI_PORT
#define MCP4922_DDR				SPI_DDR
//#define MCP4922_CS0				(1<<1)
//#define MCP4922_LDAC			(1<<3)		//tied low
//end hardware configuration

#define mcp4922_select(cs)		{spi_select(cs);}
#define mcp4922_deselect(cs)	{spi_deselect(cs);}

void mcp4922_init(void);					//reset mcp4922

//bit 15 - select output dac
#define MCP4922_DAC_A			0x0000		//select dac a
#define MCP4922_DAC_B			0x8000		//select dac b

//bit 14
#define MCP4922_BUFF			0x4000		//output is buffered
#define MCP4922_NOBUFF			0x0000		//output is not buffered


//bit 13 - select the gain
#define MCP4922_GAIN1x			0x2000		//bit 13=1: gain =1x
#define MCP4922_GAIN2x			0x0000		//bit 13=0: gain =2x

//bit 12 - shutdown
#define MCP4922_SHUTDOWN		0x0000		//bit 12=0: shutdown the device
#define MCP4922_ACTIVE			0x1000		//bit 12=1: this device is active

//#define MCP4922_CMD_WRITE		0x0000		//bit 15=0: write to this device
//#define MCP4922_CMD_IGNORE		0x8000		//bit 15=1: ignore this device

//word_t is left aligned
#define mcp4922_write(word_t) 	{spi_write((word_t)>>8); spi_write((word_t)&0x00ff);}

//turn on dac a
#define mcp4922a_write(word_t) 	{spi_write((MCP4922_DAC_A | MCP4922_ACTIVE | (word_t))>>8); spi_write((word_t)&0x00ff);}

//turn on dac b
#define mcp4922b_write(word_t) 	{spi_write((MCP4922_DAC_B | MCP4922_ACTIVE | (word_t))>>8); spi_write((word_t)&0x00ff);}

#define mcp4922_shutdown()		spi_write(MCP4922_CMD_SHUTDOWN)

