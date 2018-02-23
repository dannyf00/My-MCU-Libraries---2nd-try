#define DS1621_I2C_ID				0x90		//id for DS1621 -> 0b1001xxxx
//#define I2C_CMD_READ				0x01		//i2c command for read
//#define I2C_CMD_WRITE				0x00		//i2c command for write
#define DS1621_CMD_READ_TEMP		0xaa		//read temperature
#define DS1621_CMD_ACCESS_TH		0xA1		//ACCESS TH REGISTER
#define DS1621_CMD_ACCESS_TL		0xA2		//ACCESS TL REGISTER
#define DS1621_CMD_CONFIG			0xAC		//ACCESS THE CONFIG REGISTER
#define DS1621_CMD_READ_COUNTER		0xA8		//READ THE COUNTER
#define DS1621_CMD_READ_SLOPE		0xA9		//READ THE SLOPE
#define DS1621_CMD_START_CONV		0xEE		//start a temp conversion
#define DS1621_CMD_STOP_CONV		0x22		//stop a temp conversion

#define DS1621_CONFIG_DONE			0x80		//1 if conversion complete. 0 if in progress
#define DS1621_CONFIG_THF			0x40		//temperature high flag. set to 1 if temp > th
#define DS1621_CONFIG_TLF			0x30		//temperature low flag. set to 1 if temp < tl
#define DS1621_CONFIG_NVB			0x10		//nonvolatile memory busy flag bit for configuration byte
#define DS1621_CONFIG_POL			0x02		//output polarity bit for configuration byte. 1=active high
#define DS1621_CONFIG_1SHOT			0x01		//1shot bit for configuration byte. 1=one shot. 0=continues conversion
#define DS1621_CONFIG_DEFAULT		0x00		//default value of the configure register
 
//RAM = 0x08..3f not implemented
//#define DS1621_1HZ			0x90		//0b10010000	//1hz rate select register, & style
//#define DS1621_4096HZ		0x91		//0b10010001	//4096hz rate select register, & style
//#define DS1621_8192HZ		0x92		//0b10010010	//8192hz rate select register, & style
//#define DS1621_32768HZ		0x93		//0b10010011	//32768hz rate select register, & style
//#define DS1621_NO_SQWE		0x83		//0b10000011	//no sqwe. default is to have sqwe
//#define DS1621_OUT_CLR		0x03		//0b00000011	//clear out pin. only makes sense if sqwe=0
//#define DS1621_OUT_SET		0x83		//0b10000011	//set out pin. only makes sense if sqwe=0

//#define BCD2INT(bcd)			((((bcd) & 0xf0)>>4)*10+((bcd) & 0x0f))	//convert bcd to int
//#define INT2BCD(int_num)		((((int_num) / 10)<<4) + ((int_num) % 10))	//convert int to bcd

#define ds1621_init()										//do nothing. for compatability reasons
void ds1621_select(unsigned char a210);	//select the ds1621
void ds1621_write(unsigned char ch, unsigned char byte);	//write a byte to ds1621
unsigned char ds1621_read(unsigned char ch);				//read a byte from ds1621
unsigned short ds1621_read_word(unsigned char ch);
unsigned short ds1621_read_temp(void);						//read the temperature

//control register
#define ds1621_config_write(n)		ds1621_write(DS1621_CMD_CONFIG, (n))	//write to control register
#define ds1621_config_read()		ds1621_read(DS1621_CMD_CONFIG)		//read from control register

#define ds1621_conv_start()			ds1621_write(DS1621_CMD_START_CONV, 0x00)		//start the conversion
#define ds1621_conv_stop()			ds1621_write(DS1621_CMD_STOP_CONV, 0x00)		//stop the conversion

#define ds1621_temp_read()			ds1621_read_word(DS1621_CMD_READ_TEMP)			//read the temp

#define ds1621_tempf_read()			(ds1621_temp_read()+0.75-(((double)ds1621_counter_read()) / ds1621_slope_read()))							//read the temp, in floating point format

#define ds1621_counter_read()		ds1621_read(DS1621_CMD_READ_COUNTER)			//read the counter

#define ds1621_slope_read()			ds1621_read(DS1621_CMD_READ_SLOPE)			//read the slope
