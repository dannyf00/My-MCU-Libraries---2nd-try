#include "pid_1.h"					//we use pid - single controller version

PID_T * _pid_ptr;							//pid global variable

//set the pid_ptr
void pid_set(PID_T * pid_ptr) {
	_pid_ptr = pid_ptr;				//point _pid_ptr to the pid variable
}

//initialize the pid's gains
void pid_gain(float p, float i, float d) {
	//_pid_ptr->target = target;
	_pid_ptr->p_factor = p;			//assign p_factor
	_pid_ptr->i_factor = i;			//assign i_factor
	_pid_ptr->d_factor = d;			//assign d_factor
	_pid_ptr->error_last = 0;		//reset error_last
	_pid_ptr->error_sum = 0;			//reset error_sum
}

//initialize the output limits
void pid_limits(float max, float min) {
	_pid_ptr->output_max = max;		//set the upper limit for output
	_pid_ptr->output_min = min;		//set the lower limit for output
}

//initialize the pid's target
void pid_target(float target) {
	_pid_ptr->target = target;		//set the target value for the process variable
}

//tuning pid factors with the Ziegler-Nichols (open loop) method
//tuning process:
//1) apply a shock to the system at t0, at output levels of 20%. the original temperature is T0
//2) wait for the temperature to rise more than 10%, at t0+t_deadtime.
//3) record time t1 when temperature is more than 30% higher than the original temperature (T1)
//4) record time t1+t_delta when temperature is more than 70% of the original temperature (T2)
//5) the slope a = 40% * T0 / (t_delta) * (1/20%) = 2 * T0 / t_delta
//
void pid_tuning_zn(float t_deadtime, float a) {
	_pid_ptr->p_factor = 1.2 / (t_deadtime * a);
	_pid_ptr->i_factor = 2 * t_deadtime;
	_pid_ptr->d_factor = 0.5 * t_deadtime;
}

float pid_output(float input) {
	float error=_pid_ptr->target - input;	//calculate the current error
	_pid_ptr->error_sum += error;			//update the error sum - consider potential weighing
	//alternative
	//_pid_ptr->error_sum = 0.8 * _pid_ptr->error_sum + 0.2 * error;
	_pid_ptr->output = _pid_ptr->p_factor * error;	//the p_factor
	_pid_ptr->output+= _pid_ptr->i_factor * _pid_ptr->error_sum;	//the i factor
	_pid_ptr->output+= _pid_ptr->d_factor * (error - _pid_ptr->error_last);	//the d factor
	if (_pid_ptr->output > _pid_ptr->output_max) _pid_ptr->output = _pid_ptr->output_max;
	if (_pid_ptr->output < _pid_ptr->output_min) _pid_ptr->output = _pid_ptr->output_min;
	_pid_ptr->error_last = error;			//save the current error value for the next iteration

	return _pid_ptr->output;
}

