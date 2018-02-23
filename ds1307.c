//#include <lpc210x.h>
//#include "delay.h"
//#include <regx51.h>							//we use keil c51
#include <p24fxxxx.h>						//we use pic24f
#include "i2c_hw.h"							//we use software i2c
#include "ds1307.h"							//we use ds1307

//*************************************************************
// This code is written to interface a pic16f690 with a
// ds1307 Real Time Clock Chip through an I2C communication
// implemented through software.

// More specifically the code is to write the value 0b00000000
// at address 0x00 in order to start the ds1307 internal occilator,
// and to also write the value 0b10010000 at address 0x07 in
// order to output a 1hz signal on the ds1307 output pin.
//*************************************************************

#define BCD2DEC(bcd)			((((bcd) & 0xf0)>>4)*10+((bcd) & 0x0f))	//convert bcd to int
#define DEC2BCD(dec)			((((dec) / 10)<<4) +((dec) % 10))	//convert int to bcd

//global variable
//struct tm _ds1307_time;					//global variable

//send byte to ch on ds1307
void ds1307_write(unsigned char ch, unsigned char byte_t) {
	i2c_start();							//send the start condition
	i2c_write(DS1307_I2C_ID | I2C_CMD_WRITE); 	//send the device id
	i2c_write(ch); 							//send the channel
	i2c_write(byte_t); 						//send the data
	i2c_stop();
}

//read from ds1307
unsigned char ds1307_read(unsigned char ch) {
	unsigned char dat;
	i2c_start(); 							//start condition
	i2c_write(DS1307_I2C_ID | I2C_CMD_WRITE); 				//second the id
	i2c_write(ch); 							//send the channel
	i2c_restart();							//restart
	i2c_write(DS1307_I2C_ID | I2C_CMD_READ);		//send the read command
	dat=i2c_read(I2C_NOACK);				//read from ds1307, no acknowledgement
	i2c_stop();
	return dat;
}

//get time
void ds1307_gtime(struct tm * tm_time) {
	unsigned char tmp;						//tmp variable
	
/*	
	tmp = ds1307_year_read();								//read year
	tm_time->tm_year = BCD2DEC(tmp);		//year in dec
	
	tmp = ds1307_mon_read();				//mon_day
	tm_time->tm_mon = BCD2DEC(tmp);			//month
	
	tmp = ds1307_mdat_read();
	tm_time->tm_mday = BCD2DEC(tmp);		//day
	
	tmp = ds1307_wday_read();
	tm_time->tm_wday = BCD2DEC(tmp);		//weekday
	
	tmp = ds1307_hour_read(); 
	tm_time->tm_hour = BCD2DEC(tmp);		//hour
	
	tmp = ds1307_min_read();
	tm_time->tm_min = BCD2DEC(tmp);			//minute
	
	tmp = ds1307_sec_read();
	tm_time->tm_sec = BCD2DEC(tmp);			//second
*/
	i2c_start(); 							//start condition
	i2c_write(DS1307_I2C_ID | I2C_CMD_WRITE); 				//second the id
	i2c_write(DS1307_SEC); 						//send the channel
	i2c_restart();							//restart
	i2c_write(DS1307_I2C_ID | I2C_CMD_READ);		//send the read command
	tmp=i2c_read(I2C_ACK); tm_time->tm_sec = BCD2DEC(tmp);			//second
	tmp=i2c_read(I2C_ACK); tm_time->tm_min = BCD2DEC(tmp);			//second
	tmp=i2c_read(I2C_ACK); tm_time->tm_hour = BCD2DEC(tmp);			//second
	tmp=i2c_read(I2C_ACK); tm_time->tm_wday = BCD2DEC(tmp);			//second
	tmp=i2c_read(I2C_ACK); tm_time->tm_mday = BCD2DEC(tmp);			//second
	tmp=i2c_read(I2C_ACK); tm_time->tm_mon = BCD2DEC(tmp);			//second
	tmp=i2c_read(I2C_NOACK); tm_time->tm_year= BCD2DEC(tmp);			//second
	i2c_stop();	
}
	
//set time
void ds1307_stime(struct tm * tm_time) {
		
	ds1307_year_write(DEC2BCD(tm_time->tm_year));		//set year
	ds1307_mon_write(DEC2BCD(tm_time->tm_mon));			//write month
	ds1307_mdat_write(DEC2BCD(tm_time->tm_mday));		//write day of month	
	ds1307_wday_write(DEC2BCD(tm_time->tm_wday));		//write tm_wday
	ds1307_hour_write(DEC2BCD(tm_time->tm_hour));		//write hour
	ds1307_min_write(DEC2BCD(tm_time->tm_min));			//write minutes
	ds1307_sec_write(DEC2BCD(tm_time->tm_sec));			//write seconds
	
}
	
