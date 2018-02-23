#ifndef PWM2TMR_H
#define PWM2TMR_H

#include "gpio.h"

//use pwm cmpa/b interrupts as timer

//global defines
#define PWM_PS1x			8			//disable pwm divider
#define PWM_PS2x			0
#define PWM_PS4x			1
#define PWM_PS8x			2
#define PWM_PS16x			3
#define PWM_PS32x			4
#define PWM_PS64x			7			//default

//global variables


//reset the module
//pwm output disabled
//down counter
//CompareDown interrupt is enabled - all others are disabled
void pwm0tmr_init(uint32_t ps, uint32_t pr);
//set up isr user handler
void pwm0tmr_act(void (*isrptr)(void));

//reset the module
//pwm output disabled
//down counter
//CompareDown interrupt is enabled - all others are disabled
void pwm1tmr_init(uint32_t ps, uint32_t pr);
//set up isr user handler
void pwm1tmr_act(void (*isrptr)(void));

//reset the module
//pwm output disabled
//down counter
//CompareDown interrupt is enabled - all others are disabled
void pwm2tmr_init(uint32_t ps, uint32_t pr);
//set up isr user handler
void pwm2tmr_act(void (*isrptr)(void));


#endif
