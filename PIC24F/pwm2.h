#ifndef PWM2_H_INCLUDED
#define PWM2_H_INCLUDED

//#include <p24fxxxx.h>						//we use pic24f
#include "gpio.h"

//hardware configuration
#define PWM2			5					//pwm2 pin on rp4

//trisb pin presumed to have been set to output
//end hardware configuration

//reset pwm
//tris pin presumed to have been set to output
void pwm2_init(void);

//set pwm parameters
void pwm2_set(unsigned short period, unsigned short duty_cycle);

//set pwm parameters
void pwm2_setperiod(unsigned short period);
#define pwm2_setpr(pr)				pwm2_setperiod(pr)

//set pwm parameters
void pwm2_setdc(unsigned short duty_cycle);


#endif // PWM2_H_INCLUDED
