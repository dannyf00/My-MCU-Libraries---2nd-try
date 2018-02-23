#include <stdio.h>
#include <stdlib.h>

#include "pid_f.h"					//we use floating point pid controllers

//set gain
void pid_setgain(PID_T *pid, double Ki, double Kp, double Kd) {
	pid->Ki = Ki;
	pid->Kp = Kp;
	pid->Kd = Kd;
}

//set min/max
void pid_setminmax(PID_T *pid, double min, double max) {
	pid->max = max;
	pid->min = min;
}

//set target
void pid_settarget(PID_T *pid, double target) {
	pid->target = target;
	pid->error_last = pid->error = target;
	pid->error_sum = 0;
}

//initialize pid controller
void pid_init(PID_T *pid, double Ki, double Kp, double Kd, double target, double min, double max) {
	pid->Ki = Ki;
	pid->Kp = Kp;
	pid->Kd = Kd;
	pid->max = max;
	pid->min = min;
	pid->target = target;
	pid->error = target;
	pid->error_last = pid->error;
	pid->error_sum = 0;
}

//limit output to its min/max
double pid_outputlimit(PID_T *pid) {
	if (pid->output>pid->max) pid->output=pid->max;
	else if (pid->output<pid->min) pid->output=pid->min;
	return pid->output;
}

//calculate the control variable
double pid_output(PID_T * pid, double input) {
	double error=pid->target - input;				//calculate the current error

	//update error integrated
	pid->error_sum += error;						//update the error sum - consider potential weighing

	//calculate the control variable
	pid->output = pid->Kp * error;					//the p_factor
	pid->output+= pid->Ki * pid->error_sum;		//the i factor
	pid->output+= pid->Kd * (error - pid->error_last);	//the d factor

	//perform boundary check on the control variable
	if (pid->output > pid->max) pid->output = pid->max;
	if (pid->output < pid->min) pid->output = pid->min;

	//save the error
	pid->error_last = pid->error;
	pid->error = error;			//save the current error value for the next iteration


	return pid->output;
}

//calculate the control variable
//a new way of caulculating pid
double pid_output1(PID_T * pid_ptr, double input) {
	double error=pid_ptr->target - input;	//calculate the current error
	static double error1=0, error2=0;		//previous errors
	double delta;
	//static float pid_out=0;					//pid output

	//update error integrated
	//pid_ptr->error_sum += error;			//update the error sum - consider potential weighing

	//calculate the control variable
	delta = pid_ptr->Kp * (error - error1);	//p_factor
	delta+= pid_ptr->Ki * error;				//i_factor
	delta+= pid_ptr->Kd * (error -2*error1 + error2);	//d_factor
	pid_ptr->output+=delta;							//pid output

	//pid_ptr->output = pid_ptr->p_factor * error;	//the p_factor
	//pid_ptr->output+= pid_ptr->i_factor * pid_ptr->error_sum;	//the i factor
	//pid_ptr->output+= pid_ptr->d_factor * (error - pid_ptr->error_last);	//the d factor



	//perform boundary check on the control variable
	if (pid_ptr->output > pid_ptr->max) pid_ptr->output = pid_ptr->max;
	if (pid_ptr->output < pid_ptr->min) pid_ptr->output = pid_ptr->min;

	//save the error
	//pid_ptr->error_last = error;			//save the current error value for the next iteration
	error2=error1;
	error1=error;

	return pid_ptr->output;
}

//return the error of the pid controller
double pid_error(PID_T * pid_ptr) {
	return pid_ptr->error_last;
}

