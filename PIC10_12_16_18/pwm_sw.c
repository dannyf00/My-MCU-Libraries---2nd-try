#include "pwm_sw.h"					//we use software pwm
//hardware configuration
//end hardware configuration

//global defines

//global variables
volatile unsigned char _pwm_cnt=0;	//pwm counter
PWM_T pwm[PWM_CNT];
unsigned char _pwm_period=0xff;

//void pwm_isr(void);				//isr for tmr0

//example isr
//void interrupt isr(void) {
//	//tmr0
//	if (TMR0IF) pwm_isr();
//}

void pwm_isr(void) {
	unsigned char ch;
	TMR0IF = 0;						//clear the flag
	_pwm_cnt++;						//increment pwm counter
	if (_pwm_cnt == _pwm_period) _pwm_cnt=0;	//reset pwm_cnt
	//test for pwm output
	if (_pwm_cnt==0) 				//reset pins
		for (ch=0; ch<PWM_CNT; ch++) IO_SET(PWM_PORT, pwm[ch].pin);
	else
		for (ch=0; ch<PWM_CNT; ch++) if (_pwm_cnt==pwm[ch].dc) IO_CLR(PWM_PORT, pwm[ch].pin);
}
	
//reset pwm
void pwm_init(unsigned char prescaler, unsigned char period) {
	unsigned char ch;
	
	//set up pins - done in pwm_set

	//set up timer
	T0CS = 0;							//use internal clock = Fosc / 4
	if (prescaler == TMR0_PS_1x) {
		PSA = 1;						//prescaler assigned to wdt
	} else {
		PSA = 0;						//prescaler assigned to tmr0
#if   	defined (_18F23K22) || defined (_18F24K22) || defined (_18F25K22) || defined (_18F26K22) || \
        defined (_18F43K22) || defined (_18F44K22) || defined (_18F45K22) || defined (_18F46K22) || \
        defined (_18LF23K22) || defined (_18LF24K22) || defined (_18LF25K22) || defined (_18LF26K22) || \
        defined (_18LF43K22) || defined (_18LF44K22) || defined (_18LF45K22) || defined (_18LF46K22)

		T0PS2 = (prescaler & 0x04)?1:0;
		T0PS1 = (prescaler & 0x02)?1:0;
		T0PS0 = (prescaler & 0x01)?1:0;

#elif 	defined(_16F1933) || defined(_16LF1933) || \
 		defined(_16F1934) || defined(_16LF1934) || \
 		defined(_16F1936) || defined(_16LF1936) || \
 		defined(_16F1937) || defined(_16LF1937) || \
 		defined(_16F1938) || defined(_16LF1938) || \
 		defined(_16F1939) || defined(_16LF1939)
		OPTION_REG = (OPTION_REG & ~0x07) | (prescaler & 0x07);	//set prescaler - option's last three bits

#else
		OPTION	 = (OPTION	 & ~0x07) | (prescaler & 0x07);	//set prescaler - option's last three bits
#endif
	}
	//set up offset/period
	_pwm_period=period;
			
	T0IF = 0;							//clear the flag
	T0IE = 1;							//turn on tmr0 interrupt
}

//set pwm duty cycle
void pwm_setdc(unsigned char ch, unsigned char dc, unsigned char pin) {
	pwm[ch].dc=dc;
	pwm[ch].pin=pin;
	
	//set initiaial state of pwin
	IO_SET(PWM_PORT, pwm[ch].pin);
	IO_OUT(PWM_DDR, pwm[ch].pin);
}
