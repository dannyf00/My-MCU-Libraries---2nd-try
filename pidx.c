#include "pidx.h"						//we use our own pid controller

//global variables

//comparison of various pid algorithm

//return the action
signed short pid1(signed short actual, signed short target) {
	signed short pid, e0;
	static signed short e1=0, e_sum=0;	//historical errors

	e0=target - actual;					//revise the error
	e_sum += e0;						//update e_sum

	pid  = Kp * e0;
	pid += Ki * e_sum;
	pid += Kd * (e0 - e1);
	e1 = e0;

	return pid;
}


signed short pid2(signed short actual, signed short target) {
	signed short pid;
	static signed short e0=0, e1=0, e2=0, e3=0;	//historical errors

	e3=e2;
	e2=e1;
	e1=e0;
	e0=target - actual;					//revise the error

	pid  = Kp * e0;
	pid += Ki * (e0 + e1 + e2 + e3);
	pid += Kd * (e0 - e1);

	return pid;
}


//return the action
signed short pid3(signed short actual, signed short target) {
	signed short pid;
	static signed short e0=0, e1=0, e_sum=0;	//historical errors

	e1=e0;
	e0=target - actual;					//revise the error
	e_sum = (e_sum / 2) + (e0 / 2);

	pid  = Kp * e0;
	pid += Ki * e_sum;					//(e0 + e1 + e2 + e3);
	pid += Kd * (e0 - e1);

	return pid;
}

//return the action
signed short pid4(signed short actual, signed short target) {
	signed short pid;
	static signed short e0=0, e1=0, e2=0, e_sum=0;	//historical errors

	e2=e1;
	e1=e0;
	e0=target - actual;					//revise the error
	e_sum = (e_sum / 2) + (e0 / 2);

	pid  = Kp * e0;
	pid += Ki * (e0+e1+e2);				//e_sum;					//(e0 + e1 + e2 + e3);
	pid += Kd * ((e0 - e1) - (e1 - e2));

	return pid;
}
