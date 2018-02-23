#define MCP980x_I2C_ID					0x90		//id for MCP980X -> 0b1001xxxx
//#define I2C_CMD_READ			0x01		//i2c command for read
//#define I2C_CMD_WRITE			0x00		//i2c command for write

//register pointers
#define MCP980x_TA					0x00		//temperature pointer
#define MCP980x_CONFIG				0x01		//configuration register
#define MCP980x_THYST	 			0x02		//temperature hysterisis register
#define MCP980x_TSET				0x03		//temperature limit set register

#define MCP980x_CONFIG_1SHOT		0x80		//configure 1shot

//resolution
#define MCP980x_CONFIG_9BIT			0x00		//9 bit resulotion
#define MCP980x_CONFIG_10BIT		0x20		//10 bit resolution
#define MCP980x_CONFIG_11BIT		0x40		//11 bit ersolution
#define MCP980x_CONFIG_12BIT		0x60		//12 bit resolution

//fault queue
#define MCP980x_CONFIG_FQ1			0x00		//fault queue 1
#define MCP980x_CONFIG_FQ2			0x08		//fault queue 2
#define MCP980x_CONFIG_FQ4			0x10		//fault queue 4
#define MCP980x_CONFIG_FQ6			0x18		//fault queue 6

//alert polarity
#define MCP980x_CONFIG_APHI			0x04		//alert active high
#define MCP980x_CONFIG_APLOW		0x00		//alert active low

//comparator / interrupt
#define MCP980x_CONFIG_INT			0x02		//interrupt mode
#define MCP980x_CONFIG_COMP			0x00		//comparator mode

//shutdown
#define MCP980x_CONFIG_SHUTDOWN		0x01		//shutdown

//#define BCD2INT(bcd)			((((bcd) & 0xf0)>>4)*10+((bcd) & 0x0f))	//convert bcd to int
//#define INT2BCD(int_num)		((((int_num) / 10)<<4) + ((int_num) % 10))	//convert int to bcd

#define mcp980x_init()										//do nothing. for compatability reasons
void mcp980x_select(unsigned char a210);	//select the mcp980x
void mcp980x_write(unsigned char ch, unsigned char byte);	//write a byte to mcp980x
void mcp980x_write_word(unsigned char ch, unsigned short byte);	//write a byte to mcp980x
unsigned char mcp980x_read(unsigned char ch);				//read a byte from mcp980x
unsigned short mcp980x_read_word(unsigned char ch);
unsigned short mcp980x_read_temp(void);						//read the temperature

//control register
#define mcp980x_config_write(n)			mcp980x_write(MCP980x_CONFIG, (n))	//write to control register
#define mcp980x_config_read()			mcp980x_read(MCP980x_CONFIG)		//read from control register

#define mcp980x_temp_read()				mcp980x_read_word(MCP980x_TA)			//read the temp

#define mcp980x_tempf_read()			(mcp980x_temp_read()+0.75-(((double)mcp980x_counter_read()) / mcp980x_slope_read()))							//read the temp, in floating point format

//thyst read / write
#define mcp980x_thyst_read()			mcp980x_read_word(MCP980x_THYST)		//read thyst
#define mcp980x_thyst_write(n)			mcp980x_write_word(MCP980x_THYST, (n))	//write thyst

//limit read / write
#define mcp980x_tset_read()				mcp980x_read_word(MCP980x_TSET)		//read tset
#define mcp980x_tset_write(n)			mcp980x_write_word(MCP980x_TSET, (n))	//write tset
