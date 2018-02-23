#ifndef FPID_H_INCLUDED
#define FPID_H_INCLUDED

#include <stdint.h>				//if exist

//PID struct
typedef struct {
	float control;			//control output
	float target;				//target value
	float actual;				//actual
	float error;				//error
	float error_prev;			//previous error
	float error_sum;			//sum of errors
	float error_delta;		//change in error
	float Kp;					//gain for proportion
	float Ki;					//gain for integration
	float Kd;					//gain for differential
} PID_t;						//pid type

//initialize PID
void PID_init(PID_t *pid, float Kp, float Ki, float Kd);

void PID_set(PID_t *pid, float target);

//update control variable
float PID(PID_t *pid, float actual);

//update control, with bounds
float PID_limit(PID_t *pid, float min, float max);

#endif // IPID_H_INCLUDED
