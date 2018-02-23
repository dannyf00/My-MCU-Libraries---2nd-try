//#include <regx51.h>						//we use keil c51
#include <p24fxxxx.h>						//we use pic24f
#include "gpio.h"
#include "ds1302.h"							//we use ds1302

#define BCD2DEC(bcd)			((((bcd) & 0xf0)>>4)*10+((bcd) & 0x0f))	//convert bcd to int
#define DEC2BCD(dec)			((((dec) / 10)<<4) +((dec) % 10))	//convert int to bcd


void ds1302_init(void) {					//reset ds1302
	IO_CLR(DS1302_PORT, DS1302_SCK);		//clear sck
	IO_OUT(DS1302_DDR, DS1302_SCK);			//sck as output

	IO_IN(DS1302_DDR, DS1302_SIO);			//sio as input/high-z
}

//write a byte
//assuming that the device has been selected
void ds1302_send(unsigned char byte_t) {	//write a byte
	unsigned char mask = 0x01;				//mask

	IO_OUT(DS1302_DDR, DS1302_SIO);			//sio as output
	do {
		IO_CLR(DS1302_PORT, DS1302_SCK);		//clear sck
		if (byte_t & mask) IO_SET(DS1302_PORT, DS1302_SIO);	//send 1
		else IO_CLR(DS1302_PORT, DS1302_SIO);				//otherwise, send 0
		IO_SET(DS1302_PORT, DS1302_SCK);	//set sck -> strobe out the bit on sck's rising edge
		mask = mask << 1;					//shift to the next bit
	} while (mask);
	IO_CLR(DS1302_PORT, DS1302_SCK);		//clear sck
}

//read a byte
//assuming that the device has been selected
unsigned char ds1302_get(void) {			//read a byte
	unsigned char mask = 0x01;				//mask
	unsigned char tmp = 0x00;				//temp variable

	IO_IN(DS1302_DDR, DS1302_SIO);			//sio as input
	//IO_SET(DS1302_PORT, DS1302_SCK);		//set sck
	do {
		IO_CLR(DS1302_PORT, DS1302_SCK);	//clear sck -> strobe in the bit on sck's falling edge
		NOP(); NOP(); //NOP(); NOP(); NOP();	//waste some time to allow ds1302 to output the bit on sio - tcdd in the datasheet (800ns)
		if (DS1302_PORT_IN & DS1302_SIO) tmp |= mask;	//read 1
		else tmp |= 0x00;					//otherwise, read 0
		IO_SET(DS1302_PORT, DS1302_SCK);	//set sck
		mask = mask << 1;					//shift to the next bit
	} while (mask);
	IO_CLR(DS1302_PORT, DS1302_SCK);		//clear sck
	return tmp;
}

//#define ds1302_init()					//do nothing - for compatability reasons only

//write a byte to a channel
//assuming that the device has been selected
void ds1302_write(unsigned char ch, unsigned char byte_t) {
	ds1302_select(DS1302_CS);				//enable to write to the chip
	ds1302_send(ch | DS1302_CMD_WRITE);		//send the channel
	ds1302_send(byte_t);
	ds1302_deselect(DS1302_CS);				//disable to write to the chip
}

//read a byte from a channel
//assuming that the device has been selected
unsigned char ds1302_read(unsigned char ch) {
	unsigned char tmp;
	ds1302_select(DS1302_CS);				//enable to write to the chip
	ds1302_send(ch | DS1302_CMD_READ);		//send the channel
	tmp = ds1302_get();
	ds1302_deselect(DS1302_CS);				//disable to write to the chip
	return tmp;				//return the result of a read operation
}

//get time
void ds1302_gtime(struct tm * tm_time) {
	unsigned char tmp;				//tmp variable
	
	tmp = ds1302_year_read();								//read year
	tm_time->tm_year = BCD2DEC(tmp);		//year in dec
	
	tmp = ds1302_mon_read();								//mon_day
	tm_time->tm_mon = BCD2DEC(tmp);			//month
	
	tmp = ds1302_mdat_read();
	tm_time->tm_mday = BCD2DEC(tmp);		//day
	
	tmp = ds1302_wday_read();
	tm_time->tm_wday = BCD2DEC(tmp);		//weekday
	
	tmp = ds1302_hour_read(); 
	tm_time->tm_hour = BCD2DEC(tmp);		//hour
	
	tmp = ds1302_min_read();
	tm_time->tm_min = BCD2DEC(tmp);			//minute
	
	tmp = ds1302_sec_read();
	tm_time->tm_sec = BCD2DEC(tmp);			//second

}
	
//set time
void ds1302_stime(struct tm * tm_time) {
		
	ds1302_year_write(DEC2BCD(tm_time->tm_year));	//set year
	ds1302_mon_write(DEC2BCD(tm_time->tm_mon));		//write month
	ds1302_mdat_write(DEC2BCD(tm_time->tm_mday));	//write day of month	
	ds1302_wday_write(DEC2BCD(tm_time->tm_wday));	//write tm_wday
	ds1302_hour_write(DEC2BCD(tm_time->tm_hour));	//write hour
	ds1302_min_write(DEC2BCD(tm_time->tm_min));		//write minutes
	ds1302_sec_write(DEC2BCD(tm_time->tm_sec));		//write seconds
	
}
	
