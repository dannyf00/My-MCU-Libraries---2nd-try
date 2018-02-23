#include "pwm_sw.h"						//we use software pwm

//hardware configuration
//end hardware configuration

//global defines

//global variables
volatile uint16_t _pwm_cnt;
uint16_t _pwm_period=0xffff;			//pwm period
PWM_T pwm[PWM_CNT];						//stores pwm parameters

//pwm isr
void pwm_isr(void) {
	unsigned char ch;
	_pwm_cnt+=1;						//increment counter
	if (_pwm_cnt==_pwm_period) {
		_pwm_cnt=0;						//reset pwm counter
		for (ch=0; ch<PWM_CNT; ch++) IO_SET(PWM_PORT, pwm[ch].pin);
	} else {
		for (ch=0; ch<PWM_CNT; ch++) if (_pwm_cnt==pwm[ch].dc) IO_CLR(PWM_PORT, pwm[ch].pin);
	}
}

//initialize pwm
void pwm_init(uint16_t ps, uint16_t period) {
	_pwm_period=period;
	tmr_init(ps, PWM_PERIOD);			//load up timer
	tmr_act(pwm_isr);					//install user handler
}

//active pwm channels
void pwm_setdc(uint8_t ch, uint16_t pin, uint16_t dc) {
	pwm[ch].pin=pin;					//update pwm struct
	pwm[ch].dc=dc;
	IO_OUT(PWM_DDR, pwm[ch].pin);		//set pin as output
}
