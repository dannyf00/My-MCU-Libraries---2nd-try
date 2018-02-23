#ifndef HPWM_H
#define HPWM_H
//using hardware PWM generator, vs. timer ccp

#include "gpio.h"									//we use pwm

//global defines
#define HPWM_PS2x			0
#define HPWM_PS4x			1
#define HPWM_PS8x			2
#define HPWM_PS16x			3
#define HPWM_PS32x			4
#define HPWM_PS64x			7						//default

//pin outs
//PWM0:0a/PD0, 1b/PD1
//PWM1:2a/PB0, 3b/PB1
//PWM2:4a/PE0, 5b/PE1

//use hardware PWM0 module
//ps/3bits: 0..7
//pr/16bits
//PWM0:PWM0a/PD0, PWM0b/PD1
void HPWM0_init(uint32_t ps, uint32_t pr);

//set duty cycle
#define HPWM0A_setdc(dc)		PWMGEN0->CMPA = (dc)
#define HPWM0B_setdc(dc)		PWMGEN0->CMPB = (dc)

//use hardware PWM1 module
//ps/3bits: 0..7
//pr/16bits
//PWM1:PWM1a/PB0, PWM1b/PB1
void HPWM1_init(uint32_t ps, uint32_t pr);

//set duty cycle
#define HPWM1A_setdc(dc)		PWMGEN1->CMPA = (dc)
#define HPWM1B_setdc(dc)		PWMGEN1->CMPB = (dc)

//use hardware PWM2 module
//ps/3bits: 0..7
//pr/16bits
//PWM2:PWM2a/PE0, PWM2b/PE1
void HPWM2_init(uint32_t ps, uint32_t pr);

//set duty cycle
#define HPWM2A_setdc(dc)		PWMGEN2->CMPA = (dc)
#define HPWM2B_setdc(dc)		PWMGEN2->CMPB = (dc)


#endif
