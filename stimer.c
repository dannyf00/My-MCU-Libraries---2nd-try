#include "stimer.h"							//we use software timer

//hardware configuration
//end hardware configuration

//global defines

//global variables


//global variables
volatile tick_t _stimer_tick;

//initialize the timer
void stimer_init(stimer_t *stimer, tick_t pr) {
    _stimer_tick = 0;
    stimer->period = pr;                //set the period
    stimer->tick = stimer->period;       //get the current tick
    //stimer->ptr = func_ptr;           //set up call back functions
}

//check and update tick
uint8_t stimer_ovf(stimer_t *stimer) {
    if (stimer->tick > _stimer_tick) return 0;
    stimer->tick += stimer->period;
    return 1;
}

//software timer heart beat
void stimer_tick(void) {
	_stimer_tick+=1;					//advance heart beat
}
	