#ifndef PWM_SW_H_INCLUDED
#define PWM_SW_H_INCLUDED

#include "gpio.h"
#include "tmr1.h"						//we use timer0 as time base

//hardware configuration
#define PWM_PORT			LATB
#define PWM_DDR				TRISB
#define PWM_CNT				3			//number of pwm channels
#define PWM_PERIOD			200		//timer reload value

//select the following to match timer used
#define tmr_init(ps, pr)	tmr1_init(ps, pr)
#define tmr_act(isr)		tmr1_act(isr)
//end hardware configuration

//global defines
typedef struct {
	uint16_t dc;
	uint16_t pin;
} PWM_T;

//global variables

//initialize pwm
void pwm_init(uint16_t ps, uint16_t period);

//active pwm channels
void pwm_setdc(uint8_t ch, uint16_t pin, uint16_t dc);

#define pwm0_setdc(pin, dc)				pwm_setdc(0, pin, dc)
#define pwm1_setdc(pin, dc)				pwm_setdc(1, pin, dc)
#define pwm2_setdc(pin, dc)				pwm_setdc(2, pin, dc)
#define pwm3_setdc(pin, dc)				pwm_setdc(3, pin, dc)
#define pwm4_setdc(pin, dc)				pwm_setdc(4, pin, dc)
#define pwm5_setdc(pin, dc)				pwm_setdc(5, pin, dc)
#define pwm6_setdc(pin, dc)				pwm_setdc(6, pin, dc)
#define pwm7_setdc(pin, dc)				pwm_setdc(7, pin, dc)

#endif /* PWM_SW_H_INCLUDED */
