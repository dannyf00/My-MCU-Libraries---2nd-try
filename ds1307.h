//header for ds1307

#include <time.h>							//we use struct tm

#define DS1307_I2C_ID			0xd0		//id for DS1307
//#define I2C_CMD_READ			0x01		//i2c command for read
//#define I2C_CMD_WRITE			0x00		//i2c command for write
#define DS1307_SEC				0x00		//ch # for seconds
#define DS1307_MIN				0x01		//ch # for minutes
#define DS1307_HOUR				0x02		//ch # for hours
#define DS1307_WDAY				0x03		//ch # for day
#define DS1307_MDAT				0x04		//ch # for date
#define DS1307_MON				0x05		//ch # for month
#define DS1307_YEAR				0x06		//ch # for year
#define DS1307_CONTROL			0x07		//ch # for control
//control register bits
#define DS1307_CTRL_OUT			0x80		//out bit in control register
#define DS1307_CTRL_SQWE		0x10		//SQWE bit in control register. 1 enables square wave out (default)
#define DS1307_CTRL_1HZ			0x10		//sqwe=1, rs10=0b00
#define DS1307_CTRL_4096HZ		0x11		//sqwe=1, rs10=0b01
#define DS1307_CTRL_8192HZ		0x12		//sqwe=1, rs10=0b10
#define DS1307_CTRL_32768HZ		0x13		//sqwe=1, rs10=0b11
#define DS1307_CTRL_CLR			0x00		//0b000000xx	//clear out pin. only makes sense if sqwe=0
#define DS1307_CTRL_SET			0x80		//0b100000xx	//set out pin. only makes sense if sqwe=0
#define DS1307_CTRL_DEFAULT		0x03		//default value for the control register



//RAM = 0x08..3f:
#define DS1307_RAM08			0x08		//ram @0x08
#define DS1307_RAM09			0x09		//ram @0x09
#define DS1307_RAM0a			0x0a		//ram @0x0a
#define DS1307_RAM0b			0x0b		//ram @0x0b
#define DS1307_RAM0c			0x0c		//ram @0x0c
#define DS1307_RAM0d			0x0d		//ram @0x0d
#define DS1307_RAM0e			0x0e		//ram @0x0e
#define DS1307_RAM0f			0x0f		//ram @0x0f
#define DS1307_RAM10			0x10		//ram @0x10
#define DS1307_RAM11			0x11		//ram @0x11
#define DS1307_RAM12			0x12		//ram @0x12
#define DS1307_RAM13			0x13		//ram @0x13
#define DS1307_RAM14			0x14		//ram @0x14
#define DS1307_RAM15			0x15		//ram @0x15
#define DS1307_RAM16			0x16		//ram @0x16
#define DS1307_RAM17			0x17		//ram @0x17
#define DS1307_RAM18			0x18		//ram @0x18
#define DS1307_RAM19			0x19		//ram @0x19
#define DS1307_RAM1A			0x1a		//ram @0x1a
#define DS1307_RAM1B			0x1b		//ram @0x1b
#define DS1307_RAM1C			0x1c		//ram @0x1c
#define DS1307_RAM1D			0x1d		//ram @0x1d
#define DS1307_RAM1E			0x1e		//ram @0x1e
#define DS1307_RAM1F			0x1f		//ram @0x1f
#define DS1307_RAM20			0x20		//ram @0x20
#define DS1307_RAM21			0x21		//ram @0x21
#define DS1307_RAM22			0x22		//ram @0x22
#define DS1307_RAM23			0x23		//ram @0x23
#define DS1307_RAM24			0x24		//ram @0x24
#define DS1307_RAM25			0x25		//ram @0x25
#define DS1307_RAM26			0x26		//ram @0x26
#define DS1307_RAM27			0x27		//ram @0x27
#define DS1307_RAM28			0x28		//ram @0x28
#define DS1307_RAM29			0x29		//ram @0x29
#define DS1307_RAM2A			0x2a		//ram @0x2a
#define DS1307_RAM2B			0x2b		//ram @0x2b
#define DS1307_RAM2C			0x2c		//ram @0x2c
#define DS1307_RAM2D			0x2d		//ram @0x2d
#define DS1307_RAM2E			0x2e		//ram @0x2e
#define DS1307_RAM2F			0x2f		//ram @0x2f
#define DS1307_RAM30			0x30		//ram @0x30
#define DS1307_RAM31			0x31		//ram @0x31
#define DS1307_RAM32			0x32		//ram @0x32
#define DS1307_RAM33			0x33		//ram @0x33
#define DS1307_RAM34			0x34		//ram @0x34
#define DS1307_RAM35			0x35		//ram @0x35
#define DS1307_RAM36			0x36		//ram @0x36
#define DS1307_RAM37			0x37		//ram @0x37
#define DS1307_RAM38			0x38		//ram @0x38
#define DS1307_RAM39			0x39		//ram @0x39
#define DS1307_RAM3A			0x3a		//ram @0x3a
#define DS1307_RAM3B			0x3b		//ram @0x3b
#define DS1307_RAM3C			0x3c		//ram @0x3c
#define DS1307_RAM3D			0x3d		//ram @0x3d
#define DS1307_RAM3E			0x3e		//ram @0x3e
#define DS1307_RAM3F			0x3f		//ram @0x3f
#define DS1307_RAM_MIN			DS1307_RAM08	//ram, minimum address
#define DS1307_RAM_MAX			DS1307_RAM3F	//ram, minimum address


void ds1307_write(unsigned char ch, unsigned char byte_t);
unsigned char ds1307_read(unsigned char ch);

#define ds1307_init()			ds1307_write(DS1307_CONTROL, DS1307_CTRL_DEFAULT)					//start the clock

//set time
void ds1307_stime(struct tm * tm_time);
//get time
void ds1307_gtime(struct tm * tm_time);

//write / read second
#define ds1307_sec_write(n)		ds1307_write(DS1307_SEC, (n))			//write seconds
#define ds1307_sec_read()		ds1307_read(DS1307_SEC)					//read seconds, in bcd format

//write / read minute
#define ds1307_min_write(n)		ds1307_write(DS1307_MIN, (n))			//write minute
#define ds1307_min_read()		ds1307_read(DS1307_MIN)					//read minute, in bcd format

//write / read hour
#define ds1307_hour_write(n)	ds1307_write(DS1307_HOUR, (n))			//write hour
#define ds1307_hour_read()		ds1307_read(DS1307_HOUR)				//read hour, in bcd format

//write / read day of the week
#define ds1307_wday_write(n)	ds1307_write(DS1307_WDAY, (n))			//write day of week
#define ds1307_wday_read()		ds1307_read(DS1307_WDAY)				//read day of the week, in bcd format

//write / read date of the month
#define ds1307_mdat_write(n)	ds1307_write(DS1307_MDAT, (n))			//write day of the month
#define ds1307_mdat_read()		ds1307_read(DS1307_MDAT)				//read date of the month, in bcd format

//write / read month
#define ds1307_mon_write(n)		ds1307_write(DS1307_MON, (n))			//write month
#define ds1307_mon_read()		ds1307_read(DS1307_MON)					//read month, in bcd format

//write / read year
#define ds1307_year_write(n)	ds1307_write(DS1307_YEAR, (n))			//write year
#define ds1307_year_read()		ds1307_read(DS1307_YEAR)				//read year, in bcd format

//write / read control register
#define ds1307_ctrl_write(n)	ds1307_write(DS1307_CONTROL, (n))		//write control register
#define ds1307_ctrl_read()		ds1307_read(DS1307_CONTROL)				//read control register, in bcd format

//write / read ram, 0x08 - 0x3f
#define ds1307_ram_write(ram, n)	ds1307_write(ram, (n))				//write control register
#define ds1307_ram_read(ram)		ds1307_read(ram)					//read control register, in bcd format

