#ifndef PWM4_H_INCLUDED
#define PWM4_H_INCLUDED

//#include <p24fxxxx.h>						//we use pic24f
#include "gpio.h"

//hardware configuration
#define PWM4			5				//pwm2 pin on rp4

//trisb pin presumed to have been set to output
//end hardware configuration

//reset pwm
//tris pin presumed to have been set to output
void pwm4_init(void);

//set pwm parameters
void pwm4_set(unsigned short period, unsigned short duty_cycle);

//set pwm parameters
void pwm4_setperiod(unsigned short period);
#define pwm4_setpr(pr)				pwm4_setperiod(pr)

//set pwm parameters
void pwm4_setdc(unsigned short duty_cycle);

#endif // PWM4_H_INCLUDED
