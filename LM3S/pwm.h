#ifndef PWM_H
#define PWM_H

#include "gpio.h"

//using timers' pwm functions
//CCPx pin out
//T0CCP0/PD4
//T0CCP1/PC5
//T0CCP2/PD5
//T1CCP3/PC6
//T1CCP4/PC7
//T2CCP5/PB5

//16-bit pwm routines
//prescaler not used in ccp/pwm mode - provided for compatability reasons
void pwm0_init(uint8_t Txpwm_PS, uint16_t Txpwm_PR);
void pwm1_init(uint8_t Txpwm_PS, uint16_t Txpwm_PR);
void pwm2_init(uint8_t Txpwm_PS, uint16_t Txpwm_PR);
void pwm3_init(uint8_t Txpwm_PS, uint16_t Txpwm_PR);
void pwm4_init(uint8_t Txpwm_PS, uint16_t Txpwm_PR);
void pwm5_init(uint8_t Txpwm_PS, uint16_t Txpwm_PR);

#define pwm0_setdc(dc)		TIMER0->TAMATCHR = (dc)
#define pwm1_setdc(dc)		TIMER0->TBMATCHR = (dc)
#define pwm2_setdc(dc)		TIMER0->TAMATCHR = (dc)
#define pwm3_setdc(dc)		TIMER0->TBMATCHR = (dc)
#define pwm4_setdc(dc)		TIMER0->TAMATCHR = (dc)
#define pwm5_setdc(dc)		TIMER0->TBMATCHR = (dc)

#endif
