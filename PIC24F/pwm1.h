#ifndef PWM1_H_INCLUDED
#define PWM1_H_INCLUDED

//#include <p24fxxxx.h>						//we use pic24f
#include "gpio.h"

//hardware configuration
#define PWM1			5				//pwm1 pin on rp14

//trisb pin presumed to have been set to output
//end hardware configuration

//reset pwm
//tris pin presumed to have been set to output
void pwm1_init(void);

//set pwm parameters
void pwm1_set(unsigned short period, unsigned short duty_cycle);

//set pwm parameters
void pwm1_setperiod(unsigned short period);
#define pwm1_setpr(pr)				pwm1_setperiod(pr)

//set pwm parameters
void pwm1_setdc(unsigned short duty_cycle);


#endif // PWM1_H_INCLUDED
