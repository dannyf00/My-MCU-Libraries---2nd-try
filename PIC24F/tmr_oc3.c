//#include <p24fxxxx.h>						//we use pic24f
#include "tmroc3.h"						//using oc3 as timer

//hardware configuration
//end hardware configuration

//global defines
//#define PWMx						PWM2			//assign output pins
//#define PPS_OCx_TO_RP(pin)			PPS_OC2_TO_RP(pin)
#define OCxCON1						OC3CON1
#define OCxCON2						OC3CON2
#define _OCTSELx 					OC3CON1bits.OCTSEL
#define _OCMx 						OC3CON1bits.OCM
#define OCxR						OC3R		//compare register
#define OCxRS						OC3RS		//period register
#define _OCxMD						_OC3MD		//power management register
#define OCxTMR						OC3TMR		//oc2 timer
#define _OCxIF						_OC3IF		//interrupt flag
#define _OCxIE						_OC3IE		//interrupt enable

//global variables

//empty handler
static void /*_tmr2_*/empty_handler(void) {
	//default tmr handler
}

static void (* /*_tmr2*/_isr_ptr)(void)=empty_handler;				//tmr1_ptr pointing to empty_handler by default
static unsigned short _isr_counter=0;	//isr counter
static unsigned short _tmrocx_prescaler=TMROC_PS_1x;	//default prescaler = 1x

void _ISR _OC3Interrupt(void) {
	_OCxIF=0;							//clear tmr1 interrupt flag
	//_isr_counter+=1;
	//if (++_isr_counter==_tmrocx_prescaler) {
	//	_isr_counter=0;					//reset the prescaler
		/*_tmr2*/_isr_ptr();			//execute user tmr1 isr
	//}
	//IO_FLP(LED_PORT, LED);
}

//initialize oc1 as timer
void tmroc3_init(unsigned short ps, unsigned short period) {
	//assign the output pins
	//PPS_OCx_TO_RP(PWMx);

	//tris pin presumed to have been set to output
	_isr_ptr = empty_handler;			//reset the handler
	_tmrocx_prescaler=ps;				//set the prescaler
	_isr_counter=0;						//reset the counter

	//power up the pwm module
	_OCxMD = 0;

	//reset the registers
	OCxCON1 = 0x0000;
	OCxCON2 = 0x0000;

	OCxTMR = 0;						//reset the counter value

	//OCxCON2 register settings
	OCxCON2 = 0x001f;				//this module as sync source

	OCxRS = period - 1;				//set period
	OCxR = period / 2;				//50% duty cycle

	_OCxIF = 0;						//clear the flag
	_OCxIE = 0;						//not enable the interrupt

	//OCxCON1 register settings
	_OCTSELx = 0x07;				//0b111 -> system clock as clock source
	_OCMx = 0x06;					//0b110 -> edge aligned pwm

}

//activate user isr
void tmroc3_act(void (*isr_ptr)(void)) {
	/*_tmr2*/_isr_ptr=isr_ptr;			//activate the isr handler
	_OCxIF = 0;							//reset the flag
	_OCxIE = 1;							//rtc1 interrupt on
}
