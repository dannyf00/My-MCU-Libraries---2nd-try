//#include <lpc210x.h>						//we use lpc210x
//#include <htc.h>							//we use picc
#include <regx51.h>							//we use c51
//#include "delay.h"
#include "i2c_sw.h"
#include "ds323x.h"

//*************************************************************
// This code is written to interface a pic16f690 with a
// ds323x Real Time Clock Chip through an I2C communication
// implemented through software.

// More specifically the code is to write the value 0b00000000
// at address 0x00 in order to start the ds323x internal occilator,
// and to also write the value 0b10010000 at address 0x07 in
// order to output a 1hz signal on the ds323x output pin.
//*************************************************************

#define DEC2BCD(dec)			((((dec) / 10)<<4) | ((dec) %10))	//convert dec to bcd
#define BCD2DEC(bcd)			((((bcd) & 0xf0)>>4)*10+((bcd) & 0x0f))	//convert bcd to dec

//RTC_T rtc_ds323x;									//ds323x data type

void ds323x_init(void) {							//initialize the mcu
	//ds323x_write(DS323x_SEC, 0x00);			//start the clock
}

//send byte to ch on ds323x
void ds323x_write(unsigned char ch, unsigned char byte_t) {
	i2c_start(); 
	i2c_write(DS323x_ID | DS323x_WRITE); 	//send the device id+write command
	i2c_write(ch); 
	i2c_write(byte_t); 
	i2c_stop();
}

//read from ds323x
unsigned char ds323x_read(unsigned char ch) {
	unsigned char dat;
	i2c_start(); 									//start condition
	i2c_write(DS323x_ID | DS323x_WRITE); 				//second the id
	i2c_write(ch); 									//send the channel
	i2c_restart();									//restart
	i2c_write(DS323x_ID | DS323x_READ);		//send the read command
	dat=i2c_read(I2C_NOACK);						//read from ds323x, no acknowledgement
	i2c_stop();
	return dat;
}

//get time
void ds323x_gtime(struct tm * tm_time) {
	unsigned char tmp;							//tmp variable
	
	tmp = ds323x_year_read();								//read year
	tm_time->tm_year = BCD2DEC(tmp);		//year in dec
	
	tmp = ds323x_mon_read();								//mon_day
	tm_time->tm_mon = BCD2DEC(tmp);			//month
	
	tmp = ds323x_mdat_read();
	tm_time->tm_mday = BCD2DEC(tmp);		//day
	
	tmp = ds323x_wday_read();
	tm_time->tm_wday = BCD2DEC(tmp);			//weekday
	
	tmp = ds323x_hour_read(); 
	tm_time->tm_hour = BCD2DEC(tmp);		//hour
	
	tmp = ds323x_min_read();
	tm_time->tm_min = BCD2DEC(tmp);		//minute
	
	tmp = ds323x_sec_read();
	tm_time->tm_sec = BCD2DEC(tmp);	//second

}
	
//set time
void ds323x_stime(struct tm * tm_time) {
		
	ds323x_year_write(DEC2BCD(tm_time->tm_year));		//set year
	ds323x_mon_write(DEC2BCD(tm_time->tm_mon));			//write month
	ds323x_mdat_write(DEC2BCD(tm_time->tm_mday));		//write day of month	
	ds323x_wday_write(DEC2BCD(tm_time->tm_wday));		//write tm_wday
	ds323x_hour_write(DEC2BCD(tm_time->tm_hour));		//write hour
	ds323x_min_write(DEC2BCD(tm_time->tm_min));			//write minutes
	ds323x_sec_write(DEC2BCD(tm_time->tm_sec));			//write seconds
	
}
	
