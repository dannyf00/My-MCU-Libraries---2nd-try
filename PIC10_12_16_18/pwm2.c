//#include "gpio.h"
#include "pwm2.h"								//we use pwm1/ccp1

//hardware configuration
//pwm registers
#define PWMx_DDR			TRISC
#define PWMx				(1<<1)
#define PWMx_TMR			PWM_USE_TMR2		//tmr2/4/6 only
//end hardware configuration

//global defines

//for poring
#define CCPxCON				CCP2CON
#define CCPRxL				CCPR2L
#define DCxB1				DC2B1
#define DCxB0				DC2B0

//#define CCPxTMR1(ps)		do {TMR1ON = 0; TMR1IF = 0; T1CON = (((ps) & 0x03) << 4); TMR1 = 0; PR1 = 0xff; TMR1ON = 1; C5TSEL1=0, C5TSEL0=0;} while (0)
#define CCPxTMR2(ps)		do {TMR2ON = 0; TMR2IF = 0; T2CON = (((ps) & 0xf0) >> 1) | ((ps) & 0x03); TMR2 = 0; PR2 = 0xff; TMR2ON = 1; C3TSEL1=0, C3TSEL0=0;} while (0)
//#define CCPxTMR3(ps)		do {TMR3ON = 0; TMR3IF = 0; T3CON = (((ps) & 0x03) << 4); TMR3 = 0; PR3 = 0xff; TMR3ON = 1; C5TSEL1=0, C5TSEL0=1;} while (0)
#define CCPxTMR4(ps)		do {TMR4ON = 0; TMR4IF = 0; T4CON = (((ps) & 0xf0) >> 1) | ((ps) & 0x03); TMR4 = 0; PR4 = 0xff; TMR4ON = 1; C3TSEL1=0, C3TSEL0=1;} while (0)
//#define CCPxTMR5(ps)		do {TMR5ON = 0; TMR5IF = 0; T5CON = (((ps) & 0x03) << 4); TMR5 = 0; PR5 = 0xff; TMR5ON = 1; C5TSEL1=1, C5TSEL0=0;} while (0)
#define CCPxTMR6(ps)		do {TMR6ON = 0; TMR6IF = 0; T6CON = (((ps) & 0xf0) >> 1) | ((ps) & 0x03); TMR6 = 0; PR6 = 0xff; TMR6ON = 1; C3TSEL1=1, C3TSEL0=0;} while (0)


//global variables
unsigned char _tmr_used=PWMx_TMR;

/*
The following steps should be taken when configuring
the CCP module for PWM operation:
1. Disable the PWM pin (CCPx) output driver(s) by
setting the associated TRIS bit(s).
2. Load the PRx register with the PWM period value.
3. Configure the CCP module for the PWM mode
by loading the CCPxCON register with the
appropriate values.
4. Load the CCPRxL register and the DCxBx bits of
the CCPxCON register, with the PWM duty cycle
value.
5. Configure and start Timerx:
? Clear the TMRxIF interrupt flag bit of the PIRx
register. See Note below.
? Configure the TxCKPS bits of the TxCON
register with the Timerx prescale value.
? Enable Timerx by setting the TMRxON bit of
the T2CON register.
6. Enable PWM output pin:
? Wait until Timerx overflows, TMRxIF bit of the
PIR1 register is set. See Note below.
? Enable the PWM pin (CCPx) output driver(s) by
clearing the associated TRIS bit(s).
*/

//initialize the pwm
void pwm2_init(void) {
	IO_IN(PWMx_DDR, PWMx);			//pwmx as input temperarily
	CCPxCON = 	0b00000000 |		//PxM1..0
				0b00000000 |		//DCxB1..0, lowest 2 bits of the duty cycle
				0b00001100;			//PWM mode
	//PRx = 0xff;						//max period
	CCPRxL = 0x00;					//duty cycle is minimum
	IO_OUT(PWMx_DDR, PWMx);			//turn on the pin drive
}

//set pwm period
void pwm2_setpr(unsigned char prescaler, unsigned short period) {
	//set the period
	switch (_tmr_used) {
		//case PWM_USE_TMR1: CCPxTMR1(prescaler); PR1 = period >> 2; break;
		case PWM_USE_TMR2: CCPxTMR2(prescaler); PR2 = period >> 2; break;
		//case PWM_USE_TMR3: CCPxTMR3(prescaler); PR3 = period >> 2; break;
		case PWM_USE_TMR4: CCPxTMR4(prescaler); PR4 = period >> 2; break;
		//case PWM_USE_TMR5: CCPxTMR5(prescaler); PR5 = period >> 2; break;
		case PWM_USE_TMR6: CCPxTMR6(prescaler); PR6 = period >> 2; break;
		default: 		   CCPxTMR2(prescaler); PR2 = period >> 2; break;
	}
}

//set pwm duty cycle parameters
void pwm2_setdc(unsigned short duty_cycle) {
	CCPRxL = duty_cycle >> 2;
	DCxB1 = (duty_cycle & 0x02)?1:0;
	DCxB0 = (duty_cycle & 0x01)?1:0;
}

