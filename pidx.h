#ifndef PIDX_H_INCLUDED
#define PIDX_H_INCLUDED

//pid configuration
#define pid()		pid2()
//end pid configuration

#define Kp			20
#define Kd			10
#define Ki			5

#define bound(x, upper, lower)	(((x) > (upper))?(upper):(((x) < (lower))?(lower):(x)))

//global variables

//comparison of various pid algorithm

//return the action
signed short pid1(signed short actual, signed short target);

signed short pid2(signed short actual, signed short target);

//return the action
signed short pid3(signed short actual, signed short target);

//return the action
signed short pid4(signed short actual, signed short target);

#endif // PIDX_H_INCLUDED
