//#include <p24fxxxx.h>					//we use pic24f
#include <htc.h>						//we use pic
#include "rtcc.h"						//we use the rtc hardware

volatile RTCC_TIME_t _rtcc_time={
	0, 0, 0, 0, 0
}	;									//global variable to keep time

//set rtcc's time

void rtcc_time_set(RTCC_TIME_t rtcc_time) {
	_rtcc_time.halfsec=rtcc_time.halfsec;
	_rtcc_time.sec=rtcc_time.sec;
	_rtcc_time.min=rtcc_time.min;
	_rtcc_time.hour=rtcc_time.hour;
	_rtcc_time.day=rtcc_time.day;
}

//obtain rtcc's time
void rtcc_time_get(RTCC_TIME_t *rtcc_time) {
	rtcc_time->halfsec=_rtcc_time.halfsec;
	rtcc_time->sec=_rtcc_time.sec;
	rtcc_time->min=_rtcc_time.min;
	rtcc_time->hour=_rtcc_time.hour;
	rtcc_time->day=_rtcc_time.day;
}
		

//initialize the rtcc on tmr1
//32768khz crystal on tmr1 input / output pins
void rtcc_init(void) {
	T1CONbits.TMR1ON = 0;						//turn tmr1 off
	T1CONbits.T1RD16 = 0;						//read/write tmr1 as two bytes (8-bit access)
	T1CONbits.T1RUN = 0;						//system clock doesn't run from tmr1 oscillator
	T1CONbits.T1CKPS=0x00;						//tmr1 scaler = 1:1
	T1CONbits.T1OSCEN = 1;						//enable tmr1
	T1CONbits.T1SYNC = 1;						//asynchronous operation
	T1CONbits.TMR1CS = 1;						//use external clock
	TMR1H = 0x80+0x40;								//reset tmr1 so to trip every second
	//PIE1bits.T1IE=1;
	PIE1bits.TMR1IE=1;							//enable tmr1 interrupt
	T1CONbits.TMR1ON = 1;						//turn tmr1 on
	PEIE = 1;									//turn on periperhal interrupt
	ei();
}

void rtcc_update(void) {
	if (TMR1IF && TMR1IE) {						//tmr1 overflown
		TMR1IF = 0;								//reset tmr1 flag
		//rtcc_update();							//update the rtcc
		TMR1H = 0x80+0x40;							//interrupt every second
		_rtcc_time.halfsec+=1;						//advance half sec
		if (_rtcc_time.halfsec==2) {					//have we reached a full second?
			_rtcc_time.halfsec=0;					//reset halfsec
			_rtcc_time.sec+=1;						//increment the second
			if (_rtcc_time.sec >= 60) {				//second overflown
				_rtcc_time.sec-=60;					//reset the sec
				_rtcc_time.min+=1;					//increment the min
				if (_rtcc_time.min>=60) {			//min overflown
					_rtcc_time.min-=60;				//reset the min
					_rtcc_time.hour+=1;				//increment the hour
					if (_rtcc_time.hour>=24) {		//hour overflown
						_rtcc_time.hour-=24;			//reset the hour
						_rtcc_time.day+=1;			//increment the day
					}
				}
			}
		}
	}
}
	
