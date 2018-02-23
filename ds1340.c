//#include <lpc210x.h>
//#include "delay.h"
#include <regx51.h>							//we use keil c51
#include "i2c_sw.h"							//we use software i2c
#include "ds1340.h"

//*************************************************************
// This code is written to interface a pic16f690 with a
// ds1340 Real Time Clock Chip through an I2C communication
// implemented through software.

// More specifically the code is to write the value 0b00000000
// at address 0x00 in order to start the ds1340 internal occilator,
// and to also write the value 0b10010000 at address 0x07 in
// order to output a 1hz signal on the ds1340 output pin.
//*************************************************************

#define BCD2DEC(bcd)			((((bcd) & 0xf0)>>4)*10+((bcd) & 0x0f))	//convert bcd to int
#define DEC2BCD(dec)			((((dec) / 10)<<4) +((dec) % 10))	//convert int to bcd


//send byte to ch on ds1340
void ds1340_write(unsigned char ch, unsigned char byte_t) {
	i2c_start(); 
	i2c_write(DS1340_I2C_ID | I2C_CMD_WRITE); 
	i2c_write(ch); 
	i2c_write(byte_t); 
	i2c_stop();
}

//read from ds1340
unsigned char ds1340_read(unsigned char ch) {
	unsigned char dat;
	i2c_start(); 							//start condition
	i2c_write(DS1340_I2C_ID | I2C_CMD_WRITE); 				//second the id
	i2c_write(ch); 							//send the channel
	i2c_restart();							//restart
	i2c_write(DS1340_I2C_ID | I2C_CMD_READ);		//send the read command
	dat=i2c_read(I2C_NOACK);						//read from ds1340, no acknowledgement
	i2c_stop();
	return dat;
}

//get time
void ds1340_gtime(struct tm * tm_time) {
	unsigned char tmp;							//tmp variable
	
	tmp = ds1340_year_read();								//read year
	tm_time->tm_year = BCD2DEC(tmp);		//year in dec
	
	tmp = ds1340_mon_read();								//mon_day
	tm_time->tm_mon = BCD2DEC(tmp);			//month
	
	tmp = ds1340_mdat_read();
	tm_time->tm_mday = BCD2DEC(tmp);		//day
	
	tmp = ds1340_wday_read();
	tm_time->tm_wday = BCD2DEC(tmp);			//weekday
	
	tmp = ds1340_hour_read(); 
	tm_time->tm_hour = BCD2DEC(tmp);		//hour
	
	tmp = ds1340_min_read();
	tm_time->tm_min = BCD2DEC(tmp);		//minute
	
	tmp = ds1340_sec_read();
	tm_time->tm_sec = BCD2DEC(tmp);	//second

}
	
//set time
void ds1340_stime(struct tm * tm_time) {
		
	ds1340_year_write(DEC2BCD(tm_time->tm_year));		//set year
	ds1340_mon_write(DEC2BCD(tm_time->tm_mon));			//write month
	ds1340_mdat_write(DEC2BCD(tm_time->tm_mday));		//write day of month	
	ds1340_wday_write(DEC2BCD(tm_time->tm_wday));		//write tm_wday
	ds1340_hour_write(DEC2BCD(tm_time->tm_hour));		//write hour
	ds1340_min_write(DEC2BCD(tm_time->tm_min));			//write minutes
	ds1340_sec_write(DEC2BCD(tm_time->tm_sec));			//write seconds
	
}
	
