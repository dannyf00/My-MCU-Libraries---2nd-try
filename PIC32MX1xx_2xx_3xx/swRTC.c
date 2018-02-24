#include "swRTC.h"						//we use software RTC

//global defines

//global variables
volatile time_t time_now=0;				//current time, in second

//update time - time() clock
//needs to be fed with a ticks value - clock() clone
time_t time_update(uint32_t ticks) {
	static uint32_t ticks_last=0;

	if (ticks - ticks_last >= TICKS_PER_SEC) {
		ticks_last += TICKS_PER_SEC;	//update ticks
		time_now+=1;					//increment time
	}
	return time_now;
}

//get time
time_t time_get(void) {
	return time_now;
}

//set time
time_t time_set(time_t time) {
	return time_now = time;
}
