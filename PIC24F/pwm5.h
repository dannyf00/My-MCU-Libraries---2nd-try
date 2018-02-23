#ifndef PWM5_H_INCLUDED
#define PWM5_H_INCLUDED

//#include <p24fxxxx.h>						//we use pic24f
#include "gpio.h"

//hardware configuration
#define PWM5			5				//pwm5 pin on rp4

//trisb pin presumed to have been set to output
//end hardware configuration

//reset pwm
//tris pin presumed to have been set to output
void pwm5_init(void);

//set pwm parameters
void pwm5_set(unsigned short period, unsigned short duty_cycle);

//set pwm parameters
void pwm5_setperiod(unsigned short period);

//set pwm parameters
void pwm5_setdc(unsigned short duty_cycle);
#define pwm5_setpr(pr)				pwm5_setperiod(pr)

#endif // PWM5_H_INCLUDED
