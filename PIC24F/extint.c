//#include <pic24.h>						//we use pic24f
//#include "gpio.h"
#include "extint.h"						//we use external interrupt

//hardware configuration
//#define INT0_PIN		7				//map int7 to rp7
//#define INT1_PIN		8				//map int1 to rp8
//#define INT2_PIN		9				//map int1 to rp9
//end hardware configuration

static void empty_handler(void) {
}

void (* _int0_isr_ptr) (void)=empty_handler;
// = int0_isr_empty();

void _ISR _INT0Interrupt(void) {
	_INT0IF = 0;						//clera the flag
	_int0_isr_ptr();					//run the isr
}

void int0_init(void) {
	//PPS_INT0_TO_RP(INT0_PIN);				//map int0_pin - int0 cannot be remapped
	_int0_isr_ptr = empty_handler;				//initialize int isr ptr
	_INT0IF = 0;						//clear int0 flag
	_INT0EP = 1;						//1=triggered on the falling edge. 0 = rising edge
	_INT0IE = 1;						//enable int0 interrupt
}

void int0_act(void (*isr_ptr) (void)) {
	_int0_isr_ptr = isr_ptr;
}

void (* _int1_isr_ptr) (void)=empty_handler;

void _ISR _INT1Interrupt(void) {
	_INT1IF = 0;						//clera the flag
	_int1_isr_ptr();					//run the isr
}

void int1_init(void) {
	PPS_INT1_TO_RP(INT1_PIN);				//map int1_pin
	_int1_isr_ptr = empty_handler;				//initialize the ptr
	_INT1IF = 0;						//clear int0 flag
	_INT1EP = 1;						//1=triggered on the falling edge. 0 = rising edge
	_INT1IE = 1;						//enable int0 interrupt
}

void int1_act(void (*isr_ptr) (void)) {
	_int1_isr_ptr = isr_ptr;
}


void (* _int2_isr_ptr) (void)=empty_handler;

void _ISR _INT2Interrupt(void) {
	_INT2IF = 0;						//clera the flag
	_int2_isr_ptr();					//run the isr
}

void int2_init(void) {
	PPS_INT2_TO_RP(INT2_PIN);				//map int1_pin
	_int2_isr_ptr = empty_handler;				//initialize the ptr
	_INT2IF = 0;						//clear int0 flag
	_INT2EP = 1;						//1=triggered on the falling edge. 0 = rising edge
	_INT2IE = 1;						//enable int0 interrupt
}

void int2_act(void (*isr_ptr) (void)) {
	_int2_isr_ptr = isr_ptr;
}


