//rtc routines

#include <time.h>										//we use struct tm

//alarm functions not implemented
//turn on rtc
#define _RTCC_MIN_SEC		0x0000										//read min/sec
#define _RTCC_WDAY_HOUR		0x0100										//read weekday / hour
#define _RTCC_MON_MDAT		0x0200										//month and day of month
#define _RTCC_YEAR			0x0300										//read "reserve" + month
#define _RTCC_MASK			(~_RTCC_YEAR)								//rtc mask
#define _RTCPTR				RCFGCALbits.RTCPTR							//rtcptr
//#define _NVM_WRITE_EN()		{NVMKEY=0x55; NVMKEY=0xaa;}		//have to write 0x55/0xaa to initialize a write to non-volatile memory

//bcd to dec conversion
#define BCD2DEC(bcd)			((((bcd) & 0xf0)>>4)*10+((bcd) & 0x0f))	//convert bcd to int
#define DEC2BCD(dec)			((((dec) / 10)<<4) +((dec) % 10))		//convert int to bcd

//global variable

//extern struct tm _rtcc;

//reset the rtc
void rtcc_init(void);

//get time
void rtcc_gtime (struct tm * time_tm);

//set time
void rtcc_stime(struct tm * time_tm);


//read the rtc
unsigned short rtcc_read(unsigned short mask);
	
//write to the rtc
void rtcc_write(unsigned short mask, unsigned short byte_t);

//write /read second
#define rtcc_sec_write(n)	rtcc_write(_RTCC_MIN_SEC, (rtcc_read(_RTCC_MIN_SEC) & 0xff00) | ((n) & 0x00ff))
#define rtcc_sec_read()		(rtcc_read(_RTCC_MIN_SEC) & 0x00ff)

//write / read minute
#define rtcc_min_write(n)	rtcc_write(_RTCC_MIN_SEC, (rtcc_read(_RTCC_MIN_SEC) & 0x00ff) | (((n) & 0x00ff)<<8))
#define rtcc_min_read()		(rtcc_read(_RTCC_MIN_SEC) >> 8)

//write /read hour
#define rtcc_hour_write(n)	rtcc_write(_RTCC_WDAY_HOUR, (rtcc_read(_RTCC_WDAY_HOUR) & 0xff00) | ((n) & 0x00ff))
#define rtcc_hour_read()	(rtcc_read(_RTCC_WDAY_HOUR) & 0x00ff)

//write / read wday
#define rtcc_wday_write(n)	rtcc_write(_RTCC_WDAY_HOUR, (rtcc_read(_RTCC_WDAY_HOUR) & 0x00ff) | (((n) & 0x00ff)<<8))
#define rtcc_wday_read()	(rtcc_read(_RTCC_WDAY_HOUR) >> 8)

//write /read mdat
#define rtcc_mdat_write(n)	rtcc_write(_RTCC_MON_MDAT, (rtcc_read(_RTCC_MON_MDAT) & 0xff00) | ((n) & 0x00ff))
#define rtcc_mdat_read()	(rtcc_read(_RTCC_MON_MDAT) & 0x00ff)

//write / read wday
#define rtcc_mon_write(n)	rtcc_write(_RTCC_MON_MDAT, (rtcc_read(_RTCC_MON_MDAT) & 0x00ff) | (((n) & 0x00ff)<<8))
#define rtcc_mon_read()		(rtcc_read(_RTCC_MON_MDAT) >> 8)

//write /read year
#define rtcc_year_write(n)	rtcc_write(_RTCC_YEAR, (rtcc_read(_RTCC_YEAR) & 0xff00) | ((n) & 0x00ff))
#define rtcc_year_read()	(rtcc_read(_RTCC_YEAR) & 0x00ff)

//write  the calibration registers
void rtcc_cal_write(signed char offset);

//read the calibration registers
signed char rtcc_cal_read(void);


