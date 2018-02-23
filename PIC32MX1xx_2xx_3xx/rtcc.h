#ifndef __RTCC_H
#define __RTCC_H

//rtc routines
#include <time.h>										//we use struct tm
#include "gpio.h"										//we use gpio

//alarm functions not implemented
//turn on rtc
#define _RTCC_MIN_SEC		0x0000										//read min/sec
#define _RTCC_WDAY_HOUR		0x0100										//read weekday / hour
#define _RTCC_MON_MDAT		0x0200										//month and day of month
#define _RTCC_YEAR			0x0300										//read "reserve" + month
#define _RTCC_MASK			(~_RTCC_YEAR)								//rtc mask
#define _RTCPTR				RCFGCALbits.RTCPTR							//rtcptr
//#define _NVM_WRITE_EN()		{NVMKEY=0x55; NVMKEY=0xaa;}		//have to write 0x55/0xaa to initialize a write to non-volatile memory

//global variable

//extern struct tm _rtcc;

//reset the rtc
void rtcc_init(void);

uint32_t rtcc_timeget (void);		//get rtc time
uint32_t rtcc_timeset(uint32_t val);	//set rtc time
uint32_t rtcc_dateget (void);		//get rtc date
uint32_t rtcc_dateset(uint32_t val);	//set rtc date


//write  the calibration registers
uint32_t rtcc_calset(uint32_t offset);

//read the calibration registers
uint32_t rtcc_calget(void);


#endif
