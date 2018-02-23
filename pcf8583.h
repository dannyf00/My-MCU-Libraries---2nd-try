//hearder file for pcf8583/8593 (comment out the ram related functions for 8593)

#define PCF8583_I2C_ID			0xa0		//id for PCF8583 - A0=0. use 0xa1 if A0=1
//#define I2C_CMD_READ			0x01		//i2c command for read
//#define I2C_CMD_WRITE			0x00		//i2c command for write
#define PCF8583_CONTROL			0x00		//ch # for control
//control register bits
#define PCF8583_CTRL_STOP		0x80		//set the count
//#define PCF8583_CTRL_STARTCOUNT	0x00		//start count
#define PCF8583_CTRL_HOLDCOUNT	0x40		//1->stop and hold the last count in latch
#define PCF8583_CTRL_32768HZ	0x00		//clock mode, 32768hz. osc enabled
#define PCF8583_CTRL_50HZ		0x10		//clock mode, 50hz. osc disabled and user needs to feed a 50hz signal
#define PCF8583_CTRL_COUNTER	0x20		//counter mode
#define PCF8583_CTRL_TEST		0x30		//test mode
#define PCF8583_CTRL_MASK		0x08		//read date / month directly
#define PCF8583_CTRL_AE			0x04		//alarm enabled
#define PCF8583_CTRL_AF			0x02		//alarm flag
#define PCF8583_CTRL_TF			0x01		//timer flag
#define PCF8583_CTRL_DEFAULT	0x00		//default value for the control register. in 32768hz mode

#define PCF8583_SEC100TH		0x01		//ch # for seconds/100
#define PCF8583_SEC				0x02		//ch # for seconds
#define PCF8583_MIN				0x03		//ch # for minutes
#define PCF8583_HOUR			0x04		//ch # for hours. hour is the last 6 bits. the highest 2 bits for 24hr/12hr flag
#define PCF8583_YEAR_MDAT		0x05		//ch # for year/date. date is the last 6 bits. the highest 2 bits for year
#define PCF8583_WDAY_MON		0x06		//ch # for day / month. month is the last 5 bits. the highest 3 bits for wday
#define PCF8583_TMR_WDAY		0x07		//ch # for timer day of month
//alarm control not implemented

//RAM = 0x10..ff:
#define PCF8583_RAM10			0x10		//ram @0x10
#define PCF8583_RAM11			0x11		//ram @0x11
#define PCF8583_RAM12			0x12		//ram @0x12
#define PCF8583_RAM13			0x13		//ram @0x13
#define PCF8583_RAM14			0x14		//ram @0x14
#define PCF8583_RAM15			0x15		//ram @0x15
#define PCF8583_RAM16			0x16		//ram @0x16
#define PCF8583_RAM17			0x17		//ram @0x17
#define PCF8583_RAM18			0x18		//ram @0x18
#define PCF8583_RAM19			0x19		//ram @0x19
#define PCF8583_RAM1A			0x1a		//ram @0x1a
#define PCF8583_RAM1B			0x1b		//ram @0x1b
#define PCF8583_RAM1C			0x1c		//ram @0x1c
#define PCF8583_RAM1D			0x1d		//ram @0x1d
#define PCF8583_RAM1E			0x1e		//ram @0x1e
#define PCF8583_RAM1F			0x1f		//ram @0x1f
#define PCF8583_RAM20			0x20		//ram @0x20
#define PCF8583_RAM21			0x21		//ram @0x21
#define PCF8583_RAM22			0x22		//ram @0x22
#define PCF8583_RAM23			0x23		//ram @0x23
#define PCF8583_RAM24			0x24		//ram @0x24
#define PCF8583_RAM25			0x25		//ram @0x25
#define PCF8583_RAM26			0x26		//ram @0x26
#define PCF8583_RAM27			0x27		//ram @0x27
#define PCF8583_RAM28			0x28		//ram @0x28
#define PCF8583_RAM29			0x29		//ram @0x29
#define PCF8583_RAM2A			0x2a		//ram @0x2a
#define PCF8583_RAM2B			0x2b		//ram @0x2b
#define PCF8583_RAM2C			0x2c		//ram @0x2c
#define PCF8583_RAM2D			0x2d		//ram @0x2d
#define PCF8583_RAM2E			0x2e		//ram @0x2e
#define PCF8583_RAM2F			0x2f		//ram @0x2f
#define PCF8583_RAM30			0x30		//ram @0x30
#define PCF8583_RAM31			0x31		//ram @0x31
#define PCF8583_RAM32			0x32		//ram @0x32
#define PCF8583_RAM33			0x33		//ram @0x33
#define PCF8583_RAM34			0x34		//ram @0x34
#define PCF8583_RAM35			0x35		//ram @0x35
#define PCF8583_RAM36			0x36		//ram @0x36
#define PCF8583_RAM37			0x37		//ram @0x37
#define PCF8583_RAM38			0x38		//ram @0x38
#define PCF8583_RAM39			0x39		//ram @0x39
#define PCF8583_RAM3A			0x3a		//ram @0x3a
#define PCF8583_RAM3B			0x3b		//ram @0x3b
#define PCF8583_RAM3C			0x3c		//ram @0x3c
#define PCF8583_RAM3D			0x3d		//ram @0x3d
#define PCF8583_RAM3E			0x3e		//ram @0x3e
#define PCF8583_RAM3F			0x3f		//ram @0x3f
//...
#define PCF8583_RAMFF			0xff		//ram
#define PCF8583_RAM_MIN			PCF8583_RAM10	//ram, minimum address
#define PCF8583_RAM_MAX			PCF8583_RAMFF	//ram, minimum address

#define BCD2DEC(bcd)			((((bcd) & 0xf0)>>4)*10+((bcd) & 0x0f))	//convert bcd to int
#define DEC2BCD(dec)			((((dec) / 10)<<4) +((dec) % 10))	//convert int to bcd

void pcf8583_write(unsigned char ch, unsigned char byte_t);
unsigned char pcf8583_read(unsigned char ch);

#define pcf8583_init()			pcf8583_write(PCF8583_CONTROL, PCF8583_CTRL_DEFAULT);					//start the clock

//stop pcf8385 - needed prior to changing the time
#define pcf8583_stop()			pcf8583_write(PCF8583_CONTROL, PCF8583_CTRL_STOP | pcf8583_read(PCF8583_CONTROL))

//start pcf8385
#define pcf8583_start()			pcf8583_write(PCF8583_CONTROL, (~PCF8583_CTRL_STOP) & pcf8583_read(PCF8583_CONTROL))

//write / read second
#define pcf8583_sec_write(n)	pcf8583_write(PCF8583_SEC, DEC2BCD(n))			//write seconds
#define pcf8583_sec_read()		pcf8583_read(PCF8583_SEC)						//read seconds, in bcd format

//write / read minute
#define pcf8583_min_write(n)	pcf8583_write(PCF8583_MIN, DEC2BCD(n))			//write minute
#define pcf8583_min_read()		pcf8583_read(PCF8583_MIN)						//read minute, in bcd format

//write / read hour
#define pcf8583_hour_write(n)	pcf8583_write(PCF8583_HOUR, DEC2BCD(n))			//write hour
#define pcf8583_hour_read()		(pcf8583_read(PCF8583_HOUR) & 0x3f)				//read hour, in bcd format. hour is the last 6 bits

//write / read day of the week
#define pcf8583_wday_write(n)	pcf8583_write(PCF8583_WDAY_MON, (DEC2BCD(n)<<5) | pcf8583_mon_read())		//write day of week
#define pcf8583_wday_read()		((pcf8583_read(PCF8583_WDAY_MON) & (~0x1f))>>5)	//read day of the week, in bcd format. wday is the highest 3 bits

//write / read month
#define pcf8583_mon_write(n)	pcf8583_write(PCF8583_WDAY_MON, (pcf8583_wday_read()<<5) | (DEC2BCD(n) & 0x1f))	//write month
#define pcf8583_mon_read()		(pcf8583_read(PCF8583_WDAY_MON) & 0x1f)			//read month, in bcd format. month being the least significant 5 digits

//write / read date of the month
#define pcf8583_mdat_write(n)	pcf8583_write(PCF8583_YEAR_MDAT, (pcf8583_year_read() << 6) | (DEC2BCD(n) & 0x3f))	//write day of the month
#define pcf8583_mdat_read()		(pcf8583_read(PCF8583_YEAR_MDAT) & 0x3f)		//read date of the month, in bcd format

//write / read year
#define pcf8583_year_write(n)	pcf8583_write(PCF8583_YEAR_MDAT, (DEC2BCD(n)<<6) | pcf8583_mdat_read())	//write year
#define pcf8583_year_read()		((pcf8583_read(PCF8583_YEAR_MDAT) & (~0x3f)) >> 6)				//read year, in bcd format

//write / read control register
#define pcf8583_ctrl_write(n)	pcf8583_write(PCF8583_CONTROL, (n))				//write control register
#define pcf8583_ctrl_read()		pcf8583_read(PCF8583_CONTROL)					//read control register, in bcd format

//write / read ram, 0x08 - 0x3f
#define pcf8583_ram_write(ram, n)	pcf8583_write(ram, (n))						//write control register
#define pcf8583_ram_read(ram)		pcf8583_read(ram)							//read control register, in bcd format

