#include <p24fxxxx.h>							//we use pic24f
//#include <htc.h>
#include "gpio.h"
#include "rtcc_hw.h"							//we use the hardware rtc


//allows write to rtc registers
#define _RTCC_WREN()			{NVMKEY=0x55; NVMKEY=0xaa; RCFGCALbits.RTCWREN = 1;}
//do not allow any write to rtc registers - assumes the nvmkey sequence has been sent
#define _RTCC_WRDIS()			{RCFGCALbits.RTCWREN = 0;}

//global variables
//struct tm _rtcc;								//rtcc time

//initialize the rtcc
void rtcc_init(void) {
	_RTCC_WREN();								//allows write to rtc registers
	RCFGCALbits.RTCEN=1;						//start the rtc
	_RTCC_WRDIS();
}

//get time
void rtcc_gtime(struct tm * tm_time) {
	unsigned short tmp;							//tmp variable
	_RTCC_WREN();								//enable rtcc write
	_RTCPTR = 0x03;								//start from year
	
	tmp = RTCVAL;								//read year
	tm_time->tm_year = BCD2DEC(tmp & 0x00ff);		//year in dec
	
	tmp = RTCVAL;								//mon_day
	tm_time->tm_mon = BCD2DEC(tmp >> 8);			//month
	tm_time->tm_mday = BCD2DEC(tmp & 0x00ff);		//day
	
	tmp = RTCVAL;								//wday_hour
	tm_time->tm_wday = BCD2DEC(tmp >> 8);			//weekday
	tm_time->tm_hour = BCD2DEC(tmp & 0x00ff);		//hour
	
	tmp = RTCVAL;								//min_sec
	tm_time->tm_min = BCD2DEC(tmp >> 8);		//minute
	tm_time->tm_sec = BCD2DEC(tmp & 0x00ff);	//second

	_RTCC_WRDIS();								//disable rtcc write
}
	
//set time
void rtcc_stime(struct tm * tm_time) {
	unsigned short tmp;							//tmp variable
	_RTCC_WREN();								//enable rtcc write
	_RTCPTR = 0x03;								//start from year
	
	tmp = DEC2BCD(tm_time->tm_year);			//set year
	RTCVAL = tmp;
	
	tmp = (DEC2BCD(tm_time->tm_mon) << 8) | DEC2BCD(tm_time->tm_mday);
	RTCVAL = tmp;								//mon_day
	
	tmp = (DEC2BCD(tm_time->tm_wday) << 8) | DEC2BCD(tm_time->tm_hour);
	RTCVAL = tmp;								//wday_hour
	
	tmp = (DEC2BCD(tm_time->tm_min) << 8) | DEC2BCD(tm_time->tm_sec);
	RTCVAL = tmp;								//min_sec

	_RTCC_WRDIS();								//disable rtcc write
}
	
/*
//read from rtcc
unsigned short rtcc_read(unsigned short mask) {
	unsigned short tmp;
	_RTCC_WREN();								//allows write to rtc registers
	RCFGCAL &= _RTCC_MASK;						//mask off all bits not related to pointers
	RCFGCAL |= mask;							//point to min/sec
	tmp = RTCVAL;								//return the lower byte
	_RTCC_WRDIS();
	return tmp;
}
	
//write to rtcc
void rtcc_write(unsigned short mask, unsigned short byte_t) {
	_RTCC_WREN();								//allows write to rtc registers
	RCFGCAL &= _RTCC_MASK;						//mask off all bits not related to pointers
	RCFGCAL |= mask;							//point to min/sec
	RTCVAL = byte_t;							//return the lower byte
	_RTCC_WRDIS();
}

//write the calibration
void rtcc_cal_write(signed char offset) {
	_RTCC_WREN();								//allows write to rtc registers
	RCFGCAL &= 0xff00;							//clear the cal registers
	RCFGCAL |= offset;							//load the offset
	_RTCC_WRDIS();								//disable any write to rfc
}

//read the calibration
signed char rtcc_cal_read(void) {
	signed char tmp;
	_RTCC_WREN();								//allows write to rtc registers
	tmp = RCFGCAL & 0x00ff;							//clear the cal registers
	_RTCC_WRDIS();								//disable any write to rfc
	return tmp;
}
*/
