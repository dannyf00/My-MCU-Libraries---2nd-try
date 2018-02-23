//header file for mcp6s21/2/4/6/8 chips

//hardware configuration
//#define MCP6S2x_CS0			(1<<2)			//cs0 on p.2
//end hardware configuration

//send an instruction byte followed by a data byte
#define mcp6s2x_write(intr, dat)	{spi_write(intr); spi_write(dat);}

//set gain
#define mcp6s2x_gain_set(gain)		{mcp6s2x_write(MCP6S2x_INSTR_WRITE | MCP6S2x_INSTR_GAIN, gain);}

//set channel
#define mcp6s2x_ch_set(ch)			{mcp6s2x_write(MCP6S2x_INSTR_WRITE | MCP6S2x_INSTR_CH, ch);}


//instruction register
#define MCP6S2x_INSTR_NOP		0x00		//nop
#define MCP6S2x_INSTR_SHUTDOWN	0x20		//chip goes into shut down mode
#define MCP6S2x_INSTR_WRITE		0x40		//write to register
#define MCP6S2x_INSTR_CH		0x01		//address the channel register
#define MCP6S2x_INSTR_GAIN		0x00		//address the gain register

//gain register
#define MCP6S2x_GAIN_1x			0x00		//gain=1x
#define MCP6S2x_GAIN_2x			0x01		//gain=2x
#define MCP6S2x_GAIN_4x			0x02		//gain=4x
#define MCP6S2x_GAIN_5x			0x03		//gain=5x
#define MCP6S2x_GAIN_8x			0x04		//gain=8x
#define MCP6S2x_GAIN_10x		0x05		//gain=10x
#define MCP6S2x_GAIN_16x		0x06		//gain=16x
#define MCP6S2x_GAIN_32x		0x07		//gain=32x

//channel register
#define MCP6S2x_CH0				0x00		//channel 0
#define MCP6S2x_CH1				0x01		//channel 1
#define MCP6S2x_CH2				0x02		//channel 2
#define MCP6S2x_CH3				0x03		//channel 3
#define MCP6S2x_CH4				0x04		//channel 4
#define MCP6S2x_CH5				0x05		//channel 5
#define MCP6S2x_CH6				0x06		//channel 6
#define MCP6S2x_CH7				0x07		//channel 7

//select mcp62s8
#define mcp6s2x_select(cs)		{spi_select(cs);}

//deselect mcp6S2x
#define mcp6s2x_deselect(cs)	{spi_deselect(cs);}

//reset the chip
void mcp6s2x_init(void);
