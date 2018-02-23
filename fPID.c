#include "fPID.h"				//we use floating point pid routines

//initialize PID
void PID_init(PID_t *pid, float Kp, float Ki, float Kd) {
	pid->Kp = Kp;
	pid->Ki = Ki;
	pid->Kd = Kd;
	pid->error = 0;
	//pid->error_prev=0;
	pid->error_sum=0;
}

void PID_set(PID_t *pid, float target) {
	pid->target = target;
}

//update control variable
float PID(PID_t *pid, float actual) {
	pid->actual = actual;		//update actual
	pid->error_prev = pid->error;	//save previous error
	pid->error = pid->target - pid->actual;	//update current error
	pid->error_sum+= pid->error;	//update the error integral
	pid->error_delta = pid->error - pid->error_prev;	//calculate the change in error
	pid->control = pid->Kp * pid->error + pid->Ki * pid->error_sum + pid->Kd * pid->error_delta;
	return pid->control;
}

//update control, with bounds
float PID_limit(PID_t *pid, float min, float max) {
	//PID(pid, actual);
	if (pid->control > max) pid->control = max;	//bound the output
	if (pid->control < min) pid->control = min;	//bound the output
	return pid->control;
}
