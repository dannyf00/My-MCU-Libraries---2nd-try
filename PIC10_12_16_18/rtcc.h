#ifndef __RTCC_H
#define __RTCC_H

//header file to establish rtcc on a pic16/18 part
//utilizes timer1. 24h format. no calendar function yet.

typedef struct {
	unsigned char halfsec;						//0=1st half of a second, 1=2nd half of a second
	unsigned char sec;
	unsigned char min;
	unsigned char hour;
	unsigned short day;
} RTCC_TIME_t;

//initialize the rtcc on tmr1
//32768khz crystal on tmr1 input / output pins
void rtcc_init(void);

//set rtcc's time
void rtcc_time_set(RTCC_TIME_t rtcc_time);

//obtain rtcc's time
void rtcc_time_get(RTCC_TIME_t *rtcc_time);

//update rtcc
//in your isr
void rtcc_update(void);

#endif
