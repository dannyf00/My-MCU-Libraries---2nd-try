//#include <p24fxxxx.h>							//we use pic24f
//#include <htc.h>
//#include "gpio.h"
#include "rtcc.h"							//we use the hardware rtc

//for enhanced portability
#define _RTCCMD					PMD6bits.RTCCMD

//allows write to rtc registers
#define _RTCC_WREN()			do {di(); SYSKEY=0xaa996655ul; SYSKEY=0x556699aaul; RTCCONbits.RTCWREN = 1; ei();} while (RTCCONbits.RTCWREN == 0)
//do not allow any write to rtc registers - assumes the nvmkey sequence has been sent
#define _RTCC_WRDIS()			do {RTCCONbits.RTCWREN = 0;} while (RTCCONbits.RTCWREN == 1)

//bcd to dec conversion
#define BCD2DEC(bcd)			((((bcd) & 0xf0)>>4)*10+((bcd) & 0x0f))	//convert bcd to int
#define DEC2BCD(dec)			((((dec) / 10)<<4) +((dec) % 10))		//convert int to bcd

//global variables
//struct tm _rtcc;								//rtcc time

//initialize the rtcc
void rtcc_init(void) {
	_RTCCMD = 0;						//enable power to rtcc
	_RTCC_WREN();								//allows write to rtc registers
	RTCCON |= 1<<15;						//start the rtc
	_RTCC_WRDIS();
}

//get time
uint32_t rtcc_timeget(void) {
	return RTCTIME;
}

//set time
uint32_t rtcc_timeset(uint32_t val) {
	_RTCC_WREN();								//enable rtcc write
	di();
	while ((RTCCON & (1<<2)) != 0) continue;	//wait for RTCSYNC=0
	RTCTIME = val;
	ei();
	_RTCC_WRDIS();								//disable rtcc write
	return val;
}

//get date
uint32_t rtcc_dateget(void) {
	return RTCDATE;
}

//set time
uint32_t rtcc_dateset(uint32_t val) {
	_RTCC_WREN();								//enable rtcc write
	di();
	while ((RTCCON & (1<<2)) != 0) continue;	//wait for RTCSYNC=0
	RTCDATE = val;
	ei();
	_RTCC_WRDIS();								//disable rtcc write
	return val;
}



//write the calibration
uint32_t rtcc_calset(uint32_t offset) {
	_RTCC_WREN();								//allows write to rtc registers
	RTCCON &= 0x03ff0000ul;						//clear the cal registers
	RTCCON |= (offset & 0x3ff) << 16;			//load the offset
	_RTCC_WRDIS();								//disable any write to rfc
	return offset;
}

//read the calibration
uint32_t rtcc_calget(void) {
	signed char tmp;
	_RTCC_WREN();								//allows write to rtc registers
	tmp = RTCCON & 0x03ff0000ul;				//clear the cal registers
	_RTCC_WRDIS();								//disable any write to rfc
	return tmp >> 16;
}
