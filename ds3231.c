//#include <lpc210x.h>
//#include "delay.h"
//#include <regx51.h>							//we use keil c51
#include "ds3231.h"								//we use ds3231

//*************************************************************
// This code is written to interface a pic16f690 with a
// ds3232 Real Time Clock Chip through an I2C communication
// implemented through software.

// More specifically the code is to write the value 0b00000000
// at address 0x00 in order to start the ds3232 internal occilator,
// and to also write the value 0b10010000 at address 0x07 in
// order to output a 1hz signal on the ds3232 output pin.
//*************************************************************


//send byte to ch on ds3232
void ds3231_write(unsigned char ch, unsigned char byte_t) {
	i2c_start(); 
	i2c_write(DS3231_I2C_ID | I2C_CMD_WRITE); 
	i2c_write(ch); 
	i2c_write(byte_t); 
	i2c_stop();
}

//read from ds3232
unsigned char ds3231_read(unsigned char ch) {
	unsigned char dat;
	i2c_start(); 							//start condition
	i2c_write(DS3231_I2C_ID | I2C_CMD_WRITE); 				//second the id
	i2c_write(ch); 							//send the channel
	i2c_restart();							//restart
	i2c_write(DS3231_I2C_ID | I2C_CMD_READ);		//send the read command
	dat=i2c_read(I2C_NOACK);				//read from ds3232, no acknowledgement
	i2c_stop();
	return dat;
}

//start temp conversion
unsigned char ds3231_temp_conv(void) {
	unsigned char tmp;

	tmp=ds3231_read(DS3231_CS);				//read the control / status register
	if (tmp & DS3231_CS_BSY) return 0;		//a conversion already in process

	//no conversion in process
	tmp=ds3231_read(DS3231_CONTROL);		//read the control register
	tmp|= DS3231_CTRL_CONV;					//set the control bit
	ds3231_write(DS3231_CONTROL, tmp);		//write the revised value back to the control register
	return 0;
}

//read temp conversion
signed short ds3231_temp_read(void) {
	signed short temp;

	while (ds3231_read(DS3231_CS) & DS3231_CS_BSY)
		continue;							//wait time ds3232 has finished a conversion

	temp = ds3231_read(DS3231_TEMP_MSB)<<8;	//read the temp msb
	temp|= ds3231_read(DS3231_TEMP_LSB);	//read the temp lsb
	
	//temp = temp>>6;							//eliminate the right most 6 '0's
	return temp >> 6;	
}

//get time
void ds3231_gtime(struct tm * tm_time) {
	unsigned char tmp;							//tmp variable
	
	tmp = ds3231_year_read();								//read year
	tm_time->tm_year = BCD2DEC(tmp);		//year in dec
	
	tmp = ds3231_mon_read();								//mon_day
	tm_time->tm_mon = BCD2DEC(tmp);			//month
	
	tmp = ds3231_mdat_read();
	tm_time->tm_mday = BCD2DEC(tmp);		//day
	
	tmp = ds3231_wday_read();
	tm_time->tm_wday = BCD2DEC(tmp);			//weekday
	
	tmp = ds3231_hour_read(); 
	tm_time->tm_hour = BCD2DEC(tmp);		//hour
	
	tmp = ds3231_min_read();
	tm_time->tm_min = BCD2DEC(tmp);		//minute
	
	tmp = ds3231_sec_read();
	tm_time->tm_sec = BCD2DEC(tmp);	//second

}
	
//set time
void ds3231_stime(struct tm * tm_time) {
		
	ds3231_year_write(DEC2BCD(tm_time->tm_year));		//set year
	ds3231_mon_write(DEC2BCD(tm_time->tm_mon));			//write month
	ds3231_mdat_write(DEC2BCD(tm_time->tm_mday));		//write day of month	
	ds3231_wday_write(DEC2BCD(tm_time->tm_wday));		//write tm_wday
	ds3231_hour_write(DEC2BCD(tm_time->tm_hour));		//write hour
	ds3231_min_write(DEC2BCD(tm_time->tm_min));			//write minutes
	ds3231_sec_write(DEC2BCD(tm_time->tm_sec));			//write seconds
	
}
	
