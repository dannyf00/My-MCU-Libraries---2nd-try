#include "pwm1.h"						//we use oc1

//hardware configuration
//end hardware configuration

#define PWMx						PWM1		//assign output pins
#define PPS_OCx_TO_RP(pin)			PPS_OC1_TO_RP(pin)
#define OCxCON1						OC1CON1
#define OCxCON2						OC1CON2
#define _OCTSELx 					OC1CON1bits.OCTSEL
#define _OCMx 						OC1CON1bits.OCM
#define OCxR						OC1R		//compare register
#define OCxRS						OC1RS		//period register
#define _OCxMD						_OC1MD		//power management register

//reset pwm
void pwm1_init(void) {
	//assign the output pins
	PPS_OCx_TO_RP(PWMx);

	//tris pin presumed to have been set to output

	//power up the pwm module
	_OCxMD = 0;

	//reset the registers
	OCxCON1 = 0x0000;
	OCxCON2 = 0x0000;

	//OCxCON1 register settings
	_OCTSELx = 0x07;				//0b111 -> system clock as clock source
	_OCMx = 0x06;					//0b110 -> edge aligned pwm, 0b111 -> center aligned pwm

	//OCxCON2 register settings
	OCxCON2 = 0x001f;				//this module as sync source
}

//set pwm parameters
void pwm1_set(unsigned short period, unsigned short duty_cycle) {
	OCxRS = period;
	OCxR = duty_cycle;
}

//set pwm period
void pwm1_setperiod(unsigned short period) {
	OCxRS = period;
	//OCxR = duty_cycle;
}

//set pwm duty cycle parameters
void pwm1_setdc(unsigned short duty_cycle) {
	//OCxRS = period;
	OCxR = duty_cycle;
}

