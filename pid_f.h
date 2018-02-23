#ifndef PID_F_H_INCLUDED
#define PID_F_H_INCLUDED

//floating point pid
typedef struct {
	double Ki, Kp, Kd;		//gain for integration, proportion and differential
	double error, error_last;		//error terms, now and previous
	double error_sum;				//error sum
	double target;					//target
	double output;					//output
	double max, min;				//output max / min
} PID_T;							//pid types

//set gain
void pid_setgain(PID_T *pid, double Ki, double Kp, double Kd);

//set min/max
void pid_setminmax(PID_T *pid, double min, double max);

//set target
void pid_settarget(PID_T *pid, double target);

//initialize pid controller
void pid_init(PID_T *pid, double Ki, double Kp, double Kd, double target, double min, double max);

//limit output to its min/max
double pid_outputlimit(PID_T *pid);

//calculate the control variable
double pid_output(PID_T * pid, double input);

//calculate the control variable
//a new way of caulculating pid
double pid_output1(PID_T * pid_ptr, double input);

//return the error of the pid controller
double pid_error(PID_T * pid_ptr);

#endif // PID_F_H_INCLUDED
