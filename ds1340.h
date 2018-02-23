#define DS1340_I2C_ID			0xd0		//id for DS1340
//#define I2C_CMD_READ			0x01		//i2c command for read
//#define I2C_CMD_WRITE			0x00		//i2c command for write
#define DS1340_SEC				0x00		//ch # for seconds
#define DS1340_SEC_EOSC			0x80		//eosc bit for sec register: 0->enable the oscillator;
#define DS1340_MIN				0x01		//ch # for minutes
#define DS1340_HOUR				0x02		//ch # for hours
#define DS1340_HOUR_CEB			0x80		//century enable bit for hour register: 1-> enable century
#define DS1340_HOUR_CB			0x40		//century bit: CB toggles when year rolls from 99 to 00
#define DS1340_WDAY				0x03		//ch # for day
#define DS1340_MDAT				0x04		//ch # for date
#define DS1340_MON				0x05		//ch # for month
#define DS1340_YEAR				0x06		//ch # for year
#define DS1340_CONTROL			0x07		//ch # for control
//control register bits
#define DS1340_CTRL_OUT			0x80		//output control bit: 0-> FT/OUT controlled by OUT bit.
#define DS1340_CTRL_FT			0x40		//frequency test: 1-> FT/OUT toggles at 512Hz. 1-> FT/OUT follows OUT
#define DS1340_CTRL_S			0x20		//calibration sign: 1-> positive calibration; 0-> negative calibration
#define DS1340_CTRL_CAL4		0x10		//CAL4..0-> calibration bits
#define DS1340_CTRL_CAL3		0x08		//
#define DS1340_CTRL_CAL2		0x04		//
#define DS1340_CTRL_CAL1		0x02		//
#define DS1340_CTRL_CAL0		0x01		//
#define DS1340_CTRL_DEFAULT		0x00		//default value for the control register

//trickle charger
#define DS1340_TC				0x08		//trickle charger
#define DS1340_TC_0D250			0xa5		//trickle charger: no diode, 250ohm resistor
#define DS1340_TC_1D250			0xa9		//trickle charger: 1 diode, 250ohm resistor
#define DS1340_TC_0D2000		0xa6		//trickle charger: no diode, 2kohm resistor
#define DS1340_TC_1D2000		0xaa		//trickle charger: 1 diode, 2kohm resistor
#define DS1340_TC_0D4000		0xa7		//trickle charger: no diode, 4kohm resistor
#define DS1340_TC_1D4000		0xab		//trickle charger: 1 diode, 4kohm resistor
#define DS1340_TC_REST			0x00		//trickle charger: power on reset value
#define DS1340_TC_DEFAULT		DS1340_TC_REST	//default value for the trickle charger

//RAM = 0x08..3f:
#define DS1340_RAM08			0x08		//ram, minimum address
#define DS1340_RAM3F			0x3f		//ram, minimum address

#define DS1340_RAM_MIN			DS1340_RAM08	//ram, minimum address
#define DS1340_RAM_MAX			DS1340_RAM3F	//ram, minimum address

#define DS1340_FLAG				0x09		//flag register
#define DS1340_FLAG_OSF			0x80		//oscillator stop'd flag: 1-> oscillator is stopped or has been stopped

void ds1340_write(unsigned char ch, unsigned char byte_t);
unsigned char ds1340_read(unsigned char ch);

#define ds1340_init()			ds1340_write(DS1340_SEC, 0x00);					//start the clock

//set time
void ds1340_stime(struct tm * tm_time);
//get time
void ds1340_gtime(struct tm * tm_time);


//write / read second
#define ds1340_sec_write(n)		ds1340_write(DS1340_SEC, (n))	//write seconds
#define ds1340_sec_read()		ds1340_read(DS1340_SEC)					//read seconds, in bcd format

//write / read minute
#define ds1340_min_write(n)		ds1340_write(DS1340_MIN, (n))	//write minute
#define ds1340_min_read()		ds1340_read(DS1340_MIN)					//read minute, in bcd format

//write / read hour
#define ds1340_hour_write(n)	ds1340_write(DS1340_HOUR, (n))	//write hour
#define ds1340_hour_read()		ds1340_read(DS1340_HOUR)				//read hour, in bcd format

//write / read day of the week
#define ds1340_wday_write(n)	ds1340_write(DS1340_WDAY, (n))	//write day of week
#define ds1340_wday_read()		ds1340_read(DS1340_WDAY)				//read day of the week, in bcd format

//write / read date of the month
#define ds1340_mdat_write(n)	ds1340_write(DS1340_MDAT, (n))	//write day of the month
#define ds1340_mdat_read()		ds1340_read(DS1340_MDAT)				//read date of the month, in bcd format

//write / read month
#define ds1340_mon_write(n)		ds1340_write(DS1340_MON, (n))	//write month
#define ds1340_mon_read()		ds1340_read(DS1340_MON)					//read month, in bcd format

//write / read year
#define ds1340_year_write(n)	ds1340_write(DS1340_YEAR, (n))	//write year
#define ds1340_year_read()		ds1340_read(DS1340_YEAR)				//read year, in bcd format

//write / read control register
#define ds1340_ctrl_write(n)	ds1340_write(DS1340_CONTROL, (n))	//write control register
#define ds1340_ctrl_read()		ds1340_read(DS1340_CONTROL)					//read control register, in bcd format

//write / read trickle charger register
#define ds1340_tc_write(n)		ds1340_write(DS1340_TC, (n))	//write control register
#define ds1340_tc_read()		ds1340_read(DS1340_TC)					//read control register, in bcd format

//write / read ram, 0x08 - 0x3f
#define ds1340_flag_write(n)	ds1340_write(DS1340_FLAG, (n))	//write control register
#define ds1340_flag_read()		ds1340_read(DS1340_FLAG)					//read control register, in bcd format

