#ifndef IPID_H_INCLUDED
#define IPID_H_INCLUDED

#include <stdint.h>				//if exist

//PID struct
typedef struct {
	int32_t control;			//control output
	int32_t target;				//target value
	int32_t actual;				//actual
	int32_t error;				//error
	int32_t error_prev;			//previous error
	int32_t error_sum;			//sum of errors
	int32_t error_delta;		//change in error
	int32_t Kp;					//gain for proportion
	int32_t Ki;					//gain for integration
	int32_t Kd;					//gain for differential
} PID_t;						//pid type

//initialize PID
void PID_init(PID_t *pid, int32_t Kp, int32_t Ki, int32_t Kd);

void PID_set(PID_t *pid, int32_t target);

//update control variable
int32_t PID(PID_t *pid, int32_t actual);

//update control, with bounds
int32_t PID_limit(PID_t *pid, int32_t min, int32_t max);

#endif // IPID_H_INCLUDED
