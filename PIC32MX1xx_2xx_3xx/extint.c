//#include <pic24.h>						//we use pic24f
//#include "gpio.h"
#include "extint.h"						//we use external interrupt

//hardware configuration
//#define INT0_PIN		7				//map int7 to rp7
//#define INT1_PIN		8				//map int1 to rp8
//#define INT2_PIN		9				//map int1 to rp9
//end hardware configuration

#define _INT0IE			IEC0bits.INT0IE
#define _INT1IE			IEC0bits.INT1IE
#define _INT2IE			IEC0bits.INT2IE
#define _INT3IE			IEC0bits.INT3IE
#define _INT4IE			IEC0bits.INT4IE

#define _INT0IF			IFS0bits.INT0IF
#define _INT1IF			IFS0bits.INT1IF
#define _INT2IF			IFS0bits.INT2IF
#define _INT3IF			IFS0bits.INT3IF
#define _INT4IF			IFS0bits.INT4IF

#define _INT0EP			INTCONbits.INT0EP
#define _INT1EP			INTCONbits.INT1EP
#define _INT2EP			INTCONbits.INT2EP
#define _INT3EP			INTCONbits.INT3EP
#define _INT4EP			INTCONbits.INT4EP

static void empty_handler(void) {
}

void (* _int0_isr_ptr) (void)=empty_handler;
// = int0_isr_empty();

void __ISR(_EXTERNAL_0_VECTOR) _INT0Interrupt(void) {
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

void __ISR(_EXTERNAL_1_VECTOR) _INT1Interrupt(void) {
	_INT1IF = 0;						//clera the flag
	_int1_isr_ptr();					//run the isr
}

void int1_init(void) {
	PPS_INT1();							//map int1_pin
	_int1_isr_ptr = empty_handler;				//initialize the ptr
	_INT1IF = 0;						//clear int0 flag
	_INT1EP = 1;						//1=triggered on the falling edge. 0 = rising edge
	_INT1IE = 1;						//enable int0 interrupt
}

void int1_act(void (*isr_ptr) (void)) {
	_int1_isr_ptr = isr_ptr;
}


void (* _int2_isr_ptr) (void)=empty_handler;

void __ISR(_EXTERNAL_2_VECTOR) _INT2Interrupt(void) {
	_INT2IF = 0;						//clera the flag
	_int2_isr_ptr();					//run the isr
}

void int2_init(void) {
	PPS_INT2();							//map int1_pin
	_int2_isr_ptr = empty_handler;				//initialize the ptr
	_INT2IF = 0;						//clear int0 flag
	_INT2EP = 1;						//1=triggered on the falling edge. 0 = rising edge
	_INT2IE = 1;						//enable int0 interrupt
}

void int2_act(void (*isr_ptr) (void)) {
	_int2_isr_ptr = isr_ptr;
}


void (* _int3_isr_ptr) (void)=empty_handler;

void __ISR(_EXTERNAL_3_VECTOR) _INT3Interrupt(void) {
	_INT3IF = 0;						//clera the flag
	_int3_isr_ptr();					//run the isr
}

void int3_init(void) {
	//PPS_INT2_TO_RP(INT2_PIN);				//map int1_pin
	_int3_isr_ptr = empty_handler;				//initialize the ptr
	_INT3IF = 0;						//clear int0 flag
	_INT3EP = 1;						//1=triggered on the falling edge. 0 = rising edge
	_INT3IE = 1;						//enable int0 interrupt
}

void int3_act(void (*isr_ptr) (void)) {
	_int3_isr_ptr = isr_ptr;
}


static void (* _int4_isr_ptr) (void) = empty_handler;

void __ISR(_EXTERNAL_4_VECTOR) _INT4Interrupt(void) {
	_INT4IF = 0;						//clera the flag
	_int4_isr_ptr();					//run the isr
}

void int4_init(void) {
	//PPS_INT4_TO_RP(INT4_PIN);				//map int1_pin
	_int4_isr_ptr = empty_handler;				//initialize the ptr
	_INT4IF = 0;						//clear int0 flag
	_INT4EP = 1;						//1=triggered on the falling edge. 0 = rising edge
	_INT4IE = 1;						//enable int0 interrupt
}

void int4_act(void (*isr_ptr) (void)) {
	_int4_isr_ptr = isr_ptr;
}


