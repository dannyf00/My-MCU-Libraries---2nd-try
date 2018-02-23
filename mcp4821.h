//hardware configuration
#define MCP4821_PORT			SPI_PORT
#define MCP4821_DDR				SPI_DDR
//#define MCP4821_CS0				(1<<1)
//#define MCP4821_LDAC			(1<<3)		//tied low
//end hardware configuration

#define mcp4821_select(cs)		{IO_CLR(MCP4821_PORT, cs); IO_OUT(MCP4821_DDR, cs);}
#define mcp4821_deselect(cs)	{IO_SET(MCP4821_PORT, cs); IO_OUT(MCP4821_DDR, cs);}

void mcp4821_init(void);					//reset mcp4821

#define MCP4821_WRITE		0x0000		//bit 15=0: write to this device
#define MCP4821_IGNORE		0x8000		//bit 15=1: ignore this device
//bit 14 ignored
#define MCP4821_GAIN1x		0x2000		//bit 13=1: gain =1x
#define MCP4821_GAIN2x		0x0000		//bit 13=0: gain =2x
#define MCP4821_SHUTDOWN	0x0000		//bit 12=0: shutdown the device
#define MCP4821_ACTIVE		0x1000		//bit 12=1: this device is active

#define mcp4821_write(word_t) 	{spi_write((word_t)>>8); spi_write((word_t)&0x00ff);}
#define mcp4821_shutdown()		spi_write(MCP4821_SHUTDOWN)

