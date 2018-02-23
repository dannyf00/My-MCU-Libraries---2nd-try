//hardware configuration
#define mcp4822spi_write		spi1_write
#define MCP4822_PORT			SPI1_PORT
#define MCP4822_DDR				SPI1_DDR
//#define MCP4822_CS0				(1<<1)
//#define MCP4822_LDAC			(1<<3)		//tied low
//end hardware configuration

#define mcp4822_select(cs)		{mcp4822_deselect(cs); IO_CLR(MCP4822_PORT, cs);}
#define mcp4822_deselect(cs)	{IO_SET(MCP4822_PORT, cs); IO_OUT(MCP4822_DDR, cs);}

void mcp4822_init(void);					//reset mcp4822

//bit 15 - select output dac
#define MCP4822_DAC_A			0x0000		//select dac a
#define MCP4822_DAC_B			0x8000		//select dac b

//bit 14
//ignored

//bit 13 - select the gain
#define MCP4822_GAIN1x			0x2000		//bit 13=1: gain =1x
#define MCP4822_GAIN2x			0x0000		//bit 13=0: gain =2x

//bit 12 - shutdown
#define MCP4822_SHUTDOWN		0x0000		//bit 12=0: shutdown the device
#define MCP4822_ACTIVE			0x1000		//bit 12=1: this device is active

//#define MCP4822_WRITE		0x0000		//bit 15=0: write to this device
//#define MCP4822_IGNORE		0x8000		//bit 15=1: ignore this device

//word_t is left aligned
#define mcp4822_write(word_t) 	{mcp4822spi_write((word_t)>>8); mcp4822spi_write((word_t)&0x00ff);}

//turn on dac a
#define mcp4822a_write(word_t) 	{mcp4822spi_write((MCP4822_DAC_A | MCP4822_ACTIVE | (word_t))>>8); mcp4822spi_write((word_t)&0x00ff);}

//turn on dac b
#define mcp4822b_write(word_t) 	{mcp4822spi_write((MCP4822_DAC_B | MCP4822_ACTIVE | (word_t))>>8); mcp4822spi_write((word_t)&0x00ff);}

#define mcp4822_shutdown()		mcp4822spi_write(MCP4822_SHUTDOWN)

