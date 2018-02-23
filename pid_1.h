//pid header file - single controlle rversion

//pid type definitions
typedef struct {
	float p_factor, i_factor, d_factor;	//pid factors
	float target;						//target for input
	float output;						//pid output
	float output_max, output_min;		//max and minimum for output
	float error_last;					//last error
	float error_sum;					//integer of errors
} PID_T;

//extern PID_T _pid;						//global variable used by pid routines

//set the pid variable
void pid_set(PID_T * pid_ptr);

//initialize the pid's gains
void pid_gain(float p, float i, float d);

//initialize the output limits
void pid_limits(float max, float min);

//initialize the pid's target
void pid_target(float target);

//tuning pid factors with the Ziegler-Nichols (open loop) method
//tuning process:
//1) apply a shock to the system at t0, at output levels of 20%. the original temperature is T0
//2) wait for the temperature to rise more than 10%, at t0+t_deadtime.
//3) record time t1 when temperature is more than 30% higher than the original temperature (T1)
//4) record time t1+t_delta when temperature is more than 70% of the original temperature (T2)
//5) the slope a = 40% * T0 / (t_delta) * (1/20%) = 2 * T0 / t_delta
//
void pid_tuning_zn(float t_deadtime, float a);

float pid_output(float input);
