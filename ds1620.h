//hardware configuration
#define DS1620_PORT			P2
#define DS1620_DDR			P2
#define DS1620_PORT_IN		P2
#define DS1620_SCK			(1<<1)
#define DS1620_DQ			(1<<0)
//end hardware configuration

//read / write command
#define DS1620_CMD_WRITE			0x00		//write command
#define DS1620_CMD_READ				0xa0		//read command

//command / protocol
#define DS1620_CMD_COUNTER			0x00		//READ THE COUNTER
#define DS1620_CMD_TH				0x01		//write TH REGISTER
#define DS1620_CMD_TL				0x02		//write TL REGISTER
#define DS1620_CMD_NVB				0x09		//READ THE SLOPE
#define DS1620_CMD_TEMP				0x0a		//read temperature
#define DS1620_CMD_CONFIG			0x0C		//write THE CONFIG REGISTER
#define DS1620_CMD_STOP_CONV		0x22		//stop a temp conversion
#define DS1620_CMD_START_CONV		0xEE		//start a temp conversion

#define DS1620_CONFIG_DONE			0x80		//1 if conversion complete. 0 if in progress
#define DS1620_CONFIG_THF			0x40		//temperature high flag. set to 1 if temp > th
#define DS1620_CONFIG_TLF			0x30		//temperature low flag. set to 1 if temp < tl
#define DS1620_CONFIG_NVB			0x10		//nonvolatile memory busy flag bit for configuration byte. 1=busy
//bit 3=1, bit 2=0
#define DS1620_CONFIG_CPU			0x02		//1=control'd via its 3-wire port
#define DS1620_CONFIG_1SHOT			0x01		//1shot bit for configuration byte. 1=one shot. 0=continues conversion
#define DS1620_CONFIG_DEFAULT		0x08		//default value of the configure register
 
#define ds1620_select(cs)	{IO_OUT(DS1620_DDR, (cs)); IO_SET(DS1620_PORT, (cs));}
#define ds1620_deselect(cs)	{IO_OUT(DS1620_DDR, (cs)); IO_CLR(DS1620_PORT, (cs));}

void ds1620_init(void);										//reset the chip
//void ds1620_send(unsigned char ch);
//unsigned char ds1620_get(void);
void ds1620_write(unsigned char ch, unsigned char byte_t);	//write a byte
void ds1620_write16(unsigned char ch, unsigned short word_t);	//write a word
unsigned char ds1620_read(unsigned char ch);				//read a byte from ds1620
unsigned short ds1620_read16(unsigned char ch);				//read a word from ds1620

//control register
#define ds1620_config_write(n)		ds1620_write(DS1620_CMD_CONFIG, (n))	//write to control register
#define ds1620_config_read()		ds1620_read(DS1620_CMD_CONFIG)		//read from control register

#define ds1620_start_conv()			ds1620_write(DS1620_CMD_START_CONV, 0x00)		//start the conversion
#define ds1620_stop_conv()			ds1620_write(DS1620_CMD_STOP_CONV, 0x00)		//start the conversion

#define ds1620_temp_read()			ds1620_read16(DS1620_CMD_TEMP | DS1620_CMD_READ)			//read the temp

#define ds1620_th_set(n)			ds1620_write16(DS1620_CMD_TH | DS1620_CMD_WRITE, n)	//set th
#define ds1620_th_get(n)			ds1620_read16(DS1620_CMD_TH | DS1620_CMD_READ)		//get th

#define ds1620_tl_set(n)			ds1620_write16(DS1620_CMD_TL | DS1620_CMD_WRITE, n)	//set th
#define ds1620_tl_get(n)			ds1620_read16(DS1620_CMD_TL | DS1620_CMD_READ)		//get th
