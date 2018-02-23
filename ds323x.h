#include <time.h>				//we use struct tm

//demo files for DS3232 and DS3231
//alarm functions not implemented

//for the clock
#define DS323x_WRITE		0x00		//write command
#define DS323x_READ			0x01		//read command
#define DS323x_ID			0xd0		//id for DS323x=0b11010000
#define DS323x_SEC			0x00		//ch # for seconds
#define DS323x_MIN			0x01		//ch # for minutes
#define DS323x_HOUR			0x02		//ch # for hours
#define DS323x_WDAY			0x03		//ch # for day
#define DS323x_MDAT			0x04		//ch # for date
#define DS323x_MON			0x05		//ch # for month
#define DS323x_YEAR			0x06		//ch # for year

//for alarm 1
#define DS323x_A1_SEC		0x07		//alarm 1 second
#define DS323x_A1_MIN		0x08		//alarm 1 minute
#define DS323x_A1_HOUR		0x09		//alarm 1 hour
#define DS323x_A1_DY_DT		0x0a		//alarm 1 day / date

//for alarm 2
//#define DS323x_A2_SEC		0x07		//alarm 1 second
#define DS323x_A2_MIN		0x0b		//alarm 2 minute
#define DS323x_A2_HOUR		0x0c		//alarm 2 hour
#define DS323x_A2_DY_DT		0x0d		//alarm 2 day / date

//control register
#define DS323x_CTRL		0x0e		//ch # for control
#define DS323x_CTRL_EOSC	0x80		//eosc (enable oscillator)bit for control: 0->enable oscillator, default 0
#define DS323x_CTRL_BBSQW	0x40		//bbsqw (battery-backed square wave enable) bit for control: 1 -> enable square wave output under battery. default 0
#define DS323x_CTRL_CONV	0x20		//conv (convert temperature) bit for control: 1
#define DS323x_CTRL_RS2		0x10		//rate select 2 bit for control (RS2..1: 00->1Hz, 01->1.024khz, 10->4.096khz, 11->8.192khz)
#define DS323x_CTRL_RS1		0x08		//rate select 1 bit for control
#define DS323x_CTRL_INTCN	0x04		//interrupt control bit for control: 0-> square wave on INT/SQW pin; 1-> set if alarm time is reached
#define DS323x_CTRL_A2IE	0x02		//Alarm 2 interrupt enable bit for control: 1: enable alarm 2 interrupt to enable INT/SQW pin
#define DS323x_CTRL_A1IE	0x01		//Alarm 1 interrupt enable bit for control: 1: enable alarm 1 interrupt to enable int/sqw pin

//control_status register
#define DS323x_CS			0x0f		//ch # for control_status
#define DS323x_CS_OSF		0x80		//oscillator stop flag: 1 if the interrupt is stop'd, or has been stop'd for sometime in the past
#define DS323x_CS_BB32Khz	0x40		//battery-backed 32Khz output enabled: 1 to enable 32khz; 0 to force it low
#define DS323x_CS_CRATE1	0x20		//conversion rate 1: how often the temp sensor takes a conversion: 00->64 sec; 01->128 sec; 10->256 sec; 11->512 sec;
#define DS323x_CS_CRATE0	0x10		//conversion rate 0
#define DS323x_CS_EN32Khz	0x08		//32Khz output enable: 1-> enable 32khz output; 0-> goes low
#define DS323x_CS_BSY		0x04		//busy flag: 1-> device busy; 0-> device not busy
#define DS323x_CS_A2F		0x02		//alarm 2 flag: 1-> time matches alarm 2's time. write 0 to clear it
#define DS323x_CS_A1F		0x01		//alarm 1 flag: 1-> time matches alarm 1's time. write 0 to clear it

//aging offset
#define DS323x_OFFSET		0x10		//aging offset, singed char type

//temperature, msb, left aligned
#define DS323x_TEMP_MSB		0x11		//msb of temperature, left aligned, singed char type
//temperature, lsb, left aligned, high two bits effective
#define DS323x_TEMP_LSB		0x12		//lsb of temperature, left aligned, left two bits effective

//not used
typedef struct {
	unsigned char sec;						//seconds
	unsigned char min;						//minutes
	unsigned char hour;						//hour
	unsigned char wday;						//day of the week
	unsigned char mdat;						//date of the month
	unsigned char mon;						//month
	unsigned char year;						//year
} RTC_T;									//rtc data type

void ds323x_init(void);

//set time
void ds323x_stime(struct tm * tm_time);
//get time
void ds323x_gtime(struct tm * tm_time);

void ds323x_write(unsigned char ch, unsigned char byte_t);
unsigned char ds323x_read(unsigned char ch);

//write / read control register
#define ds323x_control_write(n)	ds323x_write(DS323x_CTRL, n)
#define ds323x_control_read()	(ds323x_read(DS323x_CTRL))

//write / read control / status register
#define ds323x_cs_write(val)	ds323x_write(DS323x_CS, val)
#define ds323x_cs_read()		(ds323x_read(DS323x_CS))

//write / read seconds
#define ds323x_sec_write(val)	ds323x_write(DS323x_SEC, (val))
#define ds323x_sec_read()		(ds323x_read(DS323x_SEC))

//write / read minutes
#define ds323x_min_write(val)	ds323x_write(DS323x_MIN, (val))
#define ds323x_min_read()		(ds323x_read(DS323x_MIN))

//write / read hour
#define ds323x_hour_write(val)	ds323x_write(DS323x_HOUR, (val))
#define ds323x_hour_read()		(ds323x_read(DS323x_HOUR))

//write / read day of week
#define ds323x_wday_write(val)	ds323x_write(DS323x_WDAY, (val))
#define ds323x_wday_read()		(ds323x_read(DS323x_WDAY))

//write / read date of month
#define ds323x_mdat_write(val)	ds323x_write(DS323x_MDAT, (val))
#define ds323x_mdat_read()		(ds323x_read(DS323x_MDAT))

//write / read month
#define ds323x_mon_write(val)	ds323x_write(DS323x_MON, (val))
#define ds323x_mon_read()		(ds323x_read(DS323x_MON))

//write / read year
#define ds323x_year_write(val)	ds323x_write(DS323x_YEAR, (val))
#define ds323x_year_read()		(ds323x_read(DS323x_YEAR))

//write  temp, return a signed short type
#define ds323x_temp_read()		((ds323x_read(DS323x_TEMP_MSB) << 2) | (ds323x_read(DS323x_TEMP_LSB)>>6))
