//source file for pwm1 for PIC32

#include "pwm4.h"                    //header file for f0_pwm1

//hardware configuration
//#define TMR2_USED                   //timebase used for pwm module. Uncomment to use TMR3
#define OCxCON						OC4CON
#if defined(OC4CON2)
#define OCxCON2						OC4CON2
#endif
#define _OCTSELx 					OC4CONbits.OCTSEL
#define _OCMx 						OC4CONbits.OCM
#define _OCxON						OC4CONbits.ON
#define OCxR						OC4R		//compare register
#define OCxRS						OC4RS		//period register
#define _OCxMD						PMD3bits.OC4MD		//power management register
//end hardware configuration

//global defines

//global variables

//reset pwm
void pwm4_init(uint32_t ps, uint32_t pr) {
	//power up the pwm module
	_OCxMD = 0;						//0->turn on the peripheral, 1->turn off the peripheral

	//assign the output pins
	PWM4_TO_RP();

    //tris pin presumed to have been set to output

	//OCxCON1 register settings
	//reset the registers
	OCxCON = 0x0000;
	//OCxCON2 = 0x0000;
    OCxR = OCxRS = 0;				//reset the duty cycle registers
    _OCMx = 0x06;					//0b110 -> pwm on OCx, fault pin disabled, 0b111->pwm on OCx, fault pin enabled
    _OCxON= 1;						//1->turn on oc, 0->turn off oc
	//OCxCON2 register settings
	//OCxCON2 = 0x001f;				//this module as sync source

    //set up time base
#if defined(TMR2_USED)
	PMD4bits.T2MD = 0;				//0->enable the peripheral, 1->disable the peripheral
    T2CON = 0x0000;                 //stop timer
	_OCTSELx = 0;				    //0 -> use timer2
    TMR2 = 0;
    PR2 = pr - 1;
    T2CONbits.TCKPS = ps;			//set the prescaler
    T2CONbits.TCS = 0;              //use internal instruction clock
    T2CONbits.TGATE = 0;            //no gating
    T2CONbits.TON = 1;              //turn on the timer
#else
	PMD4bits.T3MD = 0;				//0->enable the peripheral, 1->disable the peripheral
    T3CON = 0x0000;                 //stop timer
    _OCTSELx = 1;                   //1 -> use timer3
    TMR3 = 0;
    PR3 = pr - 1;
    T3CONbits.TCKPS = ps;			//set the prescaler
    T3CONbits.TCS = 0;              //use internal instruction clock
    T3CONbits.TGATE = 0;            //no gating
    T3CONbits.TON = 1;              //turn on the timer
#endif

}

//set pwm duty cycle parameters
//void pwm2_setdc(unsigned short duty_cycle) {
//	//OCxRS = period;
//	OCxR = 0;
//	OCxRS= duty_cycle;
//}
