#include <time.h>			//we use struct tm

//hardware configuration
#define DS1302_PORT			LATB
#define DS1302_PORT_IN		PORTB
#define DS1302_DDR			TRISB
#define DS1302_CS			(1<<3)
#define DS1302_SCK			(1<<4)
#define DS1302_SIO			(1<<5)
//end hardware configuration

//cmd
#define DS1302_CMD_WRITE	0x00			//write command
#define DS1302_CMD_READ		0x01			//read command

//register map
#define DS1302_SEC			0x80			//second
#define DS1302_MIN			0x82			//minute
#define DS1302_HOUR			0x84			//hour
#define DS1302_MDAT			0x86			//date of the month
#define DS1302_MON			0x88			//month
#define DS1302_WDAY			0x8a			//day of week
#define DS1302_YEAR			0x8c			//year
#define DS1302_CONFIG		0x8e			//configuration register
#define DS1302_CONFIG_WP	0x80			//write-protection bit for configuration register
#define DS1302_TC			0x90			//trickle charge
#define DS1302_TC_1D2K		0xa5			//0b10100101
#define DS1302_TC_1D4K		0xa6			//0b10100110
#define DS1302_TC_1D8K		0xa7			//0b10100111
#define DS1302_TC_2D2K		0xa9			//0b10101001
#define DS1302_TC_2D4K		0xaa			//0b10101010
#define DS1302_TC_2D8K		0xab			//0b10101011
#define DS1302_TC_NO		0x00			//0bxxxxxx00	//disabled

//clock burst
#define DS1302_CLKBURST		0xbe			//clock burst

//ram
#define DS1302_RAM00		0xc0			//ram
#define DS1302_RAM01		0xc2			//ram
#define DS1302_RAM02		0xc4			//ram
#define DS1302_RAM03		0xc6			//ram
#define DS1302_RAM04		0xc8			//ram
#define DS1302_RAM05		0xca			//ram
#define DS1302_RAM06		0xcc			//ram
#define DS1302_RAM07		0xce			//ram
#define DS1302_RAM08		0xd0			//ram
#define DS1302_RAM09		0xd2			//ram
#define DS1302_RAM0A		0xd4			//ram
#define DS1302_RAM0B		0xd6			//ram
#define DS1302_RAM0C		0xd8			//ram
#define DS1302_RAM0D		0xda			//ram
#define DS1302_RAM0E		0xdc			//ram
#define DS1302_RAM0F		0xde			//ram
#define DS1302_RAM10		0xe0			//ram
#define DS1302_RAM11		0xe2			//ram
#define DS1302_RAM12		0xe4			//ram
#define DS1302_RAM13		0xe6			//ram
#define DS1302_RAM14		0xe8			//ram
#define DS1302_RAM15		0xea			//ram
#define DS1302_RAM16		0xec			//ram
#define DS1302_RAM17		0xee			//ram
#define DS1302_RAM18		0xf0			//ram
#define DS1302_RAM19		0xf2			//ram
#define DS1302_RAM1A		0xf4			//ram
#define DS1302_RAM1B		0xf6			//ram
#define DS1302_RAM1C		0xf8			//ram
#define DS1302_RAM1D		0xfa			//ram
#define DS1302_RAM1E		0xfc			//ram
#define DS1302_RAM_MIN		DS1302_RAM00		//ram, minimum address
#define DS1302_RAM_MAX		DS1302_RAM1E		//ram, minimum address

//ram burst
#define DS1302_RAM_BURST	0xfe			//ram burst


#define ds1302_select(cs)	{IO_OUT(DS1302_DDR, (cs)); IO_SET(DS1302_PORT, (cs));}
#define ds1302_deselect(cs)	{IO_OUT(DS1302_DDR, (cs)); IO_CLR(DS1302_PORT, (cs));}

void ds1302_init(void);					//reset ds1302

//set time
void ds1302_stime(struct tm * tm_time);
//get time
void ds1302_gtime(struct tm * tm_time);

//write a byte
//assuming that the device has been selected
//void ds1302_send(unsigned char byte_t);	//write a byte

//read a byte
//assuming that the device has been selected
//unsigned char ds1302_get(void);			//read a byte

//write a byte to a channel
//assuming that the device has been selected
void ds1302_write(unsigned char ch, unsigned char byte_t);

//read a byte from a channel
//assuming that the device has been selected
unsigned char ds1302_read(unsigned char ch);

#define ds1302_sec_write(n)					ds1302_write(DS1302_SEC, (n))	//write to the sec register
#define ds1302_sec_read()					ds1302_read(DS1302_SEC)			//read from the sec register
		
#define ds1302_min_write(n)					ds1302_write(DS1302_MIN, (n))	//write to the min register
#define ds1302_min_read()					ds1302_read(DS1302_MIN)			//read from the min register
		
#define ds1302_hour_write(n)				ds1302_write(DS1302_HOUR, (n))	//write to the hour register
#define ds1302_hour_read()					ds1302_read(DS1302_HOUR)		//read from the hour register
		
#define ds1302_mdat_write(n)				ds1302_write(DS1302_MDAT, (n))	//write to the date register
#define ds1302_mdat_read()					ds1302_read(DS1302_MDAT)		//read from the date register
		
#define ds1302_mon_write(n)					ds1302_write(DS1302_MON, (n))	//write to the mon register
#define ds1302_mon_read()					ds1302_read(DS1302_MON)			//read from the mon register
		
#define ds1302_wday_write(n)				ds1302_write(DS1302_WDAY, (n))	//write to the mday register
#define ds1302_wday_read()					ds1302_read(DS1302_WDAY)		//read from the mday register
		
#define ds1302_year_write(n)				ds1302_write(DS1302_YEAR, (n))	//write to the year register
#define ds1302_year_read()					ds1302_read(DS1302_YEAR)		//read from the year register
		
#define ds1302_CONFIG_write(n)				ds1302_write(DS1302_CONFIG, (n))	//write to the config register
#define ds1302_CONFIG_read()				ds1302_read(DS1302_CONFIG)			//read from the config register
		
#define ds1302_TC_write(n)					ds1302_write(DS1302_TC, (n))	//write to the trickle charge register
#define ds1302_TC_read()					ds1302_read(DS1302_TC)			//read from the trickle charge register
