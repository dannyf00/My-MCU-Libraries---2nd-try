/*
 */

#include <avr/io.h>						//we use gcc avr
#include <avr/interrupt.h>				//we use interrupt
//#include "gpio.h"
#include "int.h"						//we use int


//----------------------for int0------------------
//empty isr
void int0_isr_empty(void) {
}

void (* _int0_isr_ptr)(void) = int0_isr_empty;		//int0_ptr pointing to empty_handler by default

//int0 isr
ISR(INT0_vect) {
	_int0_isr_ptr();					//run the isr
}

//int0 initialized
void int0_init(unsigned char int_trigger) {
	//user needs to make sure that the int pin is configured to be digital input
	//IO_IN(INT_0DDR, INT_0);			//int0 as input

	EIFR |= (1<<INT0);				//write 1 to clear the flag
	EICRA = (EICRA & ~(0x03 << 0)) | ((int_trigger & 0x03) << 0);	//configure the edge
	EIMSK |= (1<<INT0);				//enable the isr
}

//install usr isr
void int0_act(void (*isr_ptr)(void)) {
	_int0_isr_ptr = isr_ptr;		//install user ptr
}
//-----------------end int0------------------------

//----------------------for int1------------------
//empty isr
void int1_isr_empty(void) {
}

void (* _int1_isr_ptr)(void) = int1_isr_empty;		//int0_ptr pointing to empty_handler by default

//int1 isr
ISR(INT1_vect) {
	_int1_isr_ptr();					//run the isr
}

//int1 initialized
void int1_init(unsigned char int_trigger) {
	EIFR |= (1<<INT1);				//write 1 to clear the flag
	EICRA = (EICRA & ~(0x03 << 2)) | ((int_trigger & 0x03) << 2);	//configure the edge
	EIMSK |= (1<<INT1);				//enable the isr
}

//install usr isr
void int1_act(void (*isr_ptr)(void)) {
	_int1_isr_ptr = isr_ptr;		//install user ptr
}
//-----------------end int1------------------------

//----------------------for int2------------------
//empty isr
void int2_isr_empty(void) {
}

void (* _int2_isr_ptr)(void) = int2_isr_empty;		//int0_ptr pointing to empty_handler by default

//int1 isr
ISR(INT2_vect) {
	_int2_isr_ptr();					//run the isr
}

//int1 initialized
void int2_init(unsigned char int_trigger) {
	EIFR |= (1<<INT2);				//write 1 to clear the flag
	EICRA = (EICRA & ~(0x03 << 4)) | ((int_trigger & 0x03) << 4);	//configure the edge
	EIMSK |= (1<<INT2);				//enable the isr
}

//install usr isr
void int2_act(void (*isr_ptr)(void)) {
	_int2_isr_ptr = isr_ptr;		//install user ptr
}
//-----------------end int2------------------------

//----------------------for int3------------------
//empty isr
void int3_isr_empty(void) {
}

void (* _int3_isr_ptr)(void) = int3_isr_empty;		//int0_ptr pointing to empty_handler by default

//int3 isr
ISR(INT3_vect) {
	_int3_isr_ptr();					//run the isr
}

//int3 initialized
void int3_init(unsigned char int_trigger) {
	EIFR |= (1<<INT3);				//write 1 to clear the flag
	EICRA = (EICRA & ~(0x03 << 6)) | ((int_trigger & 0x03) << 6);	//configure the edge
	EIMSK |= (1<<INT3);				//enable the isr
}

//install usr isr
void int3_act(void (*isr_ptr)(void)) {
	_int3_isr_ptr = isr_ptr;		//install user ptr
}
//-----------------end int3------------------------

//----------------------for int4------------------
//empty isr
void int4_isr_empty(void) {
}

void (* _int4_isr_ptr)(void) = int4_isr_empty;		//int0_ptr pointing to empty_handler by default

//int0 isr
ISR(INT4_vect) {
	_int4_isr_ptr();					//run the isr
}

//int0 initialized
void int4_init(unsigned char int_trigger) {
	EIFR |= (1<<INT4);				//write 1 to clear the flag
	EICRB = (EICRB & ~(0x03 << 0)) | ((int_trigger & 0x03) << 0);	//configure the edge
	EIMSK |= (1<<INT4);				//enable the isr
}

//install usr isr
void int4_act(void (*isr_ptr)(void)) {
	_int4_isr_ptr = isr_ptr;		//install user ptr
}
//-----------------end int4------------------------

//----------------------for int5------------------
//empty isr
void int5_isr_empty(void) {
}

void (* _int5_isr_ptr)(void) = int5_isr_empty;		//int0_ptr pointing to empty_handler by default

//int1 isr
ISR(INT5_vect) {
	_int5_isr_ptr();					//run the isr
}

//int1 initialized
void int5_init(unsigned char int_trigger) {
	EIFR |= (1<<INT5);				//write 1 to clear the flag
	EICRB = (EICRB & ~(0x03 << 2)) | ((int_trigger & 0x03) << 2);	//configure the edge
	EIMSK |= (1<<INT5);				//enable the isr
}

//install usr isr
void int5_act(void (*isr_ptr)(void)) {
	_int5_isr_ptr = isr_ptr;		//install user ptr
}
//-----------------end int5------------------------

//----------------------for int6------------------
//empty isr
void int6_isr_empty(void) {
}

void (* _int6_isr_ptr)(void) = int6_isr_empty;		//int0_ptr pointing to empty_handler by default

//int1 isr
ISR(INT6_vect) {
	_int6_isr_ptr();					//run the isr
}

//int1 initialized
void int6_init(unsigned char int_trigger) {
	EIFR |= (1<<INT6);				//write 1 to clear the flag
	EICRB = (EICRB & ~(0x03 << 4)) | ((int_trigger & 0x03) << 4);	//configure the edge
	EIMSK |= (1<<INT6);				//enable the isr
}

//install usr isr
void int6_act(void (*isr_ptr)(void)) {
	_int6_isr_ptr = isr_ptr;		//install user ptr
}
//-----------------end int6------------------------

//----------------------for int7------------------
//empty isr
void int7_isr_empty(void) {
}

void (* _int7_isr_ptr)(void) = int7_isr_empty;		//int0_ptr pointing to empty_handler by default

//int3 isr
ISR(INT7_vect) {
	_int7_isr_ptr();					//run the isr
}

//int3 initialized
void int7_init(unsigned char int_trigger) {
	EIFR |= (1<<INT7);				//write 1 to clear the flag
	EICRB = (EICRB & ~(0x03 << 6)) | ((int_trigger & 0x03) << 6);	//configure the edge
	EIMSK |= (1<<INT7);				//enable the isr
}

//install usr isr
void int7_act(void (*isr_ptr)(void)) {
	_int7_isr_ptr = isr_ptr;		//install user ptr
}
//-----------------end int7------------------------
