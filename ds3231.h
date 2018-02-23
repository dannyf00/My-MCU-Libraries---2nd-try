#include <time.h>							//we use struct tm
#include "gpio.h"							//we use gpio
#include "i2c_sw.h"							//we use software i2c

#define DS3231_I2C_ID			0xd0		//id for DS3231 = 0b11010000
#define DS3231_SEC				0x00		//ch # for seconds
#define DS3231_MIN				0x01		//ch # for minutes
#define DS3231_HOUR				0x02		//ch # for hours
#define DS3231_WDAY				0x03		//ch # for day
#define DS3231_MDAT				0x04		//ch # for date
#define DS3231_MON				0x05		//ch # for month
#define DS3231_YEAR				0x06		//ch # for year
//alarm functions not implemented
//0x07 - 0x0d

//control register bits
#define DS3231_CONTROL			0x0e		//ch # for control
#define DS3231_CTRL_EOSC		0x80		//clear to enable oscillator
#define DS3231_CTRL_BBSQW		0x40		//battery-backed SQWE bit in control register. 1 enables square wave out (default)
#define DS3231_CTRL_CONV		0x20		//force a temperature conversion
#define DS3231_CTRL_1HZ			0x00		//rs21=0b00
#define DS3231_CTRL_1024HZ		0x08		//rs21=0b01
#define DS3231_CTRL_4096HZ		0x10		//rs21=0b10
#define DS3231_CTRL_8192HZ		0x18		//rs21=0b11
#define DS3231_CTRL_INTCN		0x04		//0->output square wave on int/sqw pin; 1->output alarm matches
#define DS3231_CTRL_A2IE		0x02		//set to enable alarm 2 interrupt on int/sqw pin
#define DS3231_CTRL_A1IE		0x01		//set to enable alarm 1 interrupt on int/sqw pin
#define DS3231_CTRL_DEFAULT		0x1c		//default value for the control register. 0b0001 1100

//control/status register bits
#define DS3231_CS				0x0f		//ch # for control / status register
#define DS3231_CS_OSF			0x08		//oscillator stop flag: 1-> oscillator has stopped or is stopped
#define DS3231_CS_BB32KHZ		0x04		//battery backed 32Khz: 1-> enable. 0->make it low
#define DS3231_CS_CRATE64		0x00		//sample rate of tcxo at 64seconds
#define DS3231_CS_CRATE128		0x10		//sample rate of tcxo at 128seconds
#define DS3231_CS_CRATE256		0x20		//sample rate of tcxo at 256seconds
#define DS3231_CS_CRATE512		0x30		//sample rate of tcxo at 512seconds
#define DS3231_CS_EN32KHZ		0x08		//set to enable 32Khz
#define DS3231_CS_BSY			0x04		//1->a temp conversion in process
#define DS3231_CS_A2F			0x02		//1->alarm 2 time match has occured
#define DS3231_CS_A1F			0x01		//1->alarm 1 time match has occured
#define DS3231_CS_DEFAULT		0xc8		//default value fo rthe control / stataus register. 0b1100 1000
//aging offset register
#define DS3231_AGING			0x10		//aging offset. signed char type (msb is sign)
#define DS3231_TEMP_MSB			0x11		//msb of temp. signed char type (msb is sign)
#define DS3231_TEMP_LSB			0x12		//lsb of temp. left most 2 bits effective

//0x13 reserved

//RAM = 0x14..ff:
#define DS3231_RAM14			0x14		//ram
#define DS3231_RAM15			0x15		//ram @0x15
#define DS3231_RAM16			0x16		//ram @0x16
#define DS3231_RAM17			0x17		//ram @0x17
#define DS3231_RAM18			0x18		//ram @0x18
#define DS3231_RAM19			0x19		//ram @0x19
#define DS3231_RAM1A			0x1a		//ram @0x1a
#define DS3231_RAM1B			0x1b		//ram @0x1b
#define DS3231_RAM1C			0x1c		//ram @0x1c
#define DS3231_RAM1D			0x1d		//ram @0x1d
#define DS3231_RAM1E			0x1e		//ram @0x1e
#define DS3231_RAM1F			0x1f		//ram @0x1f
#define DS3231_RAM20			0x20		//ram @0x20
#define DS3231_RAM21			0x21		//ram @0x21
#define DS3231_RAM22			0x22		//ram @0x22
#define DS3231_RAM23			0x23		//ram @0x23
#define DS3231_RAM24			0x24		//ram @0x24
#define DS3231_RAM25			0x25		//ram @0x25
#define DS3231_RAM26			0x26		//ram @0x26
#define DS3231_RAM27			0x27		//ram @0x27
#define DS3231_RAM28			0x28		//ram @0x28
#define DS3231_RAM29			0x29		//ram @0x29
#define DS3231_RAM2A			0x2a		//ram @0x2a
#define DS3231_RAM2B			0x2b		//ram @0x2b
#define DS3231_RAM2C			0x2c		//ram @0x2c
#define DS3231_RAM2D			0x2d		//ram @0x2d
#define DS3231_RAM2E			0x2e		//ram @0x2e
#define DS3231_RAM2F			0x2f		//ram @0x2f
#define DS3231_RAM30			0x30		//ram @0x30
#define DS3231_RAM31			0x31		//ram @0x31
#define DS3231_RAM32			0x32		//ram @0x32
#define DS3231_RAM33			0x33		//ram @0x33
#define DS3231_RAM34			0x34		//ram @0x34
#define DS3231_RAM35			0x35		//ram @0x35
#define DS3231_RAM36			0x36		//ram @0x36
#define DS3231_RAM37			0x37		//ram @0x37
#define DS3231_RAM38			0x38		//ram @0x38
#define DS3231_RAM39			0x39		//ram @0x39
#define DS3231_RAM3A			0x3a		//ram @0x3a
#define DS3231_RAM3B			0x3b		//ram @0x3b
#define DS3231_RAM3C			0x3c		//ram @0x3c
#define DS3231_RAM3D			0x3d		//ram @0x3d
#define DS3231_RAM3E			0x3e		//ram @0x3e
#define DS3231_RAM3F			0x3f		//ram @0x3f
//...
#define DS3231_RAMFF			0xff			//ram
#define DS3231_RAM_MIN			DS3231_RAM14	//minimum address for ram
#define DS3231_RAM_MAX			DS3231_RAMFF	//max address for ram

#define BCD2DEC(bcd)			((((bcd) & 0xf0)>>4)*10+((bcd) & 0x0f))	//convert bcd to int
#define DEC2BCD(dec)			((((dec) / 10)<<4) +((dec) % 10))	//convert int to bcd

void ds3231_write(unsigned char ch, unsigned char byte_t);
unsigned char ds3231_read(unsigned char ch);

#define ds3231_init()			ds3231_write(DS3231_CONTROL, DS3231_CTRL_DEFAULT);					//start the clock - clear EOSC bit in the control register

//set time
void ds3231_stime(struct tm * tm_time);
//get time
void ds3231_gtime(struct tm * tm_time);


//write / read second
#define ds3231_sec_write(n)		ds3231_write(DS3231_SEC, (n))		//write seconds
#define ds3231_sec_read()		ds3231_read(DS3231_SEC)				//read seconds, in bcd format

//write / read minute
#define ds3231_min_write(n)		ds3231_write(DS3231_MIN, (n))		//write minute
#define ds3231_min_read()		ds3231_read(DS3231_MIN)				//read minute, in bcd format

//write / read hour
#define ds3231_hour_write(n)	ds3231_write(DS3231_HOUR, (n))		//write hour
#define ds3231_hour_read()		ds3231_read(DS3231_HOUR)			//read hour, in bcd format

//write / read day of the week
#define ds3231_wday_write(n)	ds3231_write(DS3231_WDAY, (n))		//write day of week
#define ds3231_wday_read()		ds3231_read(DS3231_WDAY)			//read day of the week, in bcd format

//write / read date of the month
#define ds3231_mdat_write(n)	ds3231_write(DS3231_MDAT, (n))		//write day of the month
#define ds3231_mdat_read()		ds3231_read(DS3231_MDAT)			//read date of the month, in bcd format

//write / read month
#define ds3231_mon_write(n)		ds3231_write(DS3231_MON, (n))		//write month
#define ds3231_mon_read()		ds3231_read(DS3231_MON)				//read month, in bcd format

//write / read year
#define ds3231_year_write(n)	ds3231_write(DS3231_YEAR, (n))		//write year
#define ds3231_year_read()		ds3231_read(DS3231_YEAR)			//read year, in bcd format

//write / read control register
#define ds3231_ctrl_write(n)	ds3231_write(DS3231_CONTROL, (n))	//write control register
#define ds3231_ctrl_read()		ds3231_read(DS3231_CONTROL)			//read control register, in bcd format

//write / read ram, 0x08 - 0x3f
#define ds3231_ram_write(ram, n)	ds3231_write(ram, (n))			//write control register
#define sd3231_ram_read(ram)		ds3231_read(ram)				//read control register, in bcd format

//turn off the oscillator
#define ds3231_shutdown()		ds3231_write(DS3231_CONTROL, DS3231_CTRL_DEFAULT | DS3231_CTRL_EOSC)

//start temp conversion
unsigned char ds3231_temp_conv(void);

//read temp conversion
signed short ds3231_temp_read(void);								//in 0.25C increments
