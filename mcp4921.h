//hardware configuration
#define MCP4921_PORT			SPI_PORT
#define MCP4921_DDR				SPI_DDR
//#define MCP4921_CS0				(1<<1)
//#define MCP4921_LDAC			(1<<3)		//tied low
//end hardware configuration

#define mcp4921_select(cs)		{IO_CLR(MCP4921_PORT, cs); IO_OUT(MCP4921_DDR, cs);}
#define mcp4921_deselect(cs)	{IO_SET(MCP4921_PORT, cs); IO_OUT(MCP4921_DDR, cs);}

void mcp4921_init(void);					//reset mcp4921

//bit15
//ignored

//bit14
//Buf
#define MCP4921_BUF			0x4000		//output is buffered
#define MCP4921_NOBUF		0x0000		//output is not buffered

//bit13
#define MCP4921_GAIN1x		0x2000		//bit 13=1: gain =1x
#define MCP4921_GAIN2x		0x0000		//bit 13=0: gain =2x

//bit 12 shutdown mode
#define MCP4921_SHUTDOWN	0x0000		//bit 12=0: shutdown the device
#define MCP4921_ACTIVE		0x1000		//bit 12=1: this device is active

//write to mcp4921
#define mcp4921_write(word_t) 	{spi_write((word_t)>>8); spi_write((word_t)&0x00ff);}
#define mcp4921_shutdown()		spi_write(MCP4921_SHUTDOWN)

//write to adc
#define mcp4921_dac_write(val)	{spi_write((MCP4921_ACTIVE | MCP4921_BUF | MCP4921_GAIN1x | (val)) >> 8); spi_write((val) & 0x00ff);}
