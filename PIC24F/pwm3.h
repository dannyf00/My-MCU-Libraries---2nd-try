#ifndef PWM3_H_INCLUDED
#define PWM3_H_INCLUDED

//#include <p24fxxxx.h>						//we use pic24f
#include "gpio.h"

//hardware configuration
#define PWM3			5				//pwm3 pin on rp4

//trisb pin presumed to have been set to output
//end hardware configuration

//reset pwm
//tris pin presumed to have been set to output
void pwm3_init(void);

//set pwm parameters
void pwm3_set(unsigned short period, unsigned short duty_cycle);

//set pwm parameters
void pwm3_setperiod(unsigned short period);
#define pwm3_setpr(pr)				pwm3_setperiod(pr)

//set pwm parameters
void pwm3_setdc(unsigned short duty_cycle);


#endif // PWM3_H_INCLUDED
