#include <regx51.h>
#include "gpio.h"
#include "delay.h"
#include "nrc17.h"			//we use nrc17

#ifdef IR_38KMCU
  #define IR_ONE(port, pin)	IO_FLP(port, pin)
#else
  #define IR_ONE(port, pin)	IO_SET(port, pin)
#endif

//reset the ir pin
void ir_init(void) {
	IO_CLR(IR_PORT, IR);			//clear ir
	IO_OUT(IR_DDR, IR);				//ir as output
}

//send 38khz out for 500us
void ir_on(void) {
	unsigned char tmp=IR_DLY;
	while (tmp--) {
		IR_ONE(IR_PORT, IR);		//allow the signal
		//padding to achieve the desired frequency - 39Khz
		IR_PADDING();
		//NOP(); NOP(); NOP(); NOP(); //NOP();
	}
	//additional padding if needed
}

//output cleared for 500us
void ir_off(void) {
	unsigned char tmp=IR_DLY;
	while (tmp--) {
		IO_CLR(IR_PORT, IR);		//disable the signal
		//padding to achieve the desired frequency - 39Khz
		IR_PADDING();
		//NOP(); NOP(); NOP(); NOP(); NOP();
	}
	//additional padding if needed
}

void ir_one(void) {
	ir_on();
	ir_off();
}

void ir_zero(void) {
	ir_off();
	ir_on();
}

//send an ir pre-pulse
//a pre-pulse consists of 1, followed by two empty slots.
void ir_pre(void) {
	ir_on(); ir_off();
	ir_off(); ir_off();
	ir_off(); ir_off();
}

//send a byte
//lsb first
void ir_byte(unsigned char dat) {
	unsigned char mask = 0x01;
	do {
		if (dat & mask) ir_one();	//send th current bit
		else ir_zero();
		mask = mask << 1;			//shift for the next bit
	} while (mask);					//until the whole byte is sent
}

//send a frame
//a frame consists of a pre-pulse, a start bit (1), a command byte and an address byte
void ir_frame(unsigned char cmd, unsigned char addr) {
	ir_pre();						//send the pre-byte
	ir_one();						//send the start bit (1)
	ir_byte(cmd);					//send the command byte
	ir_byte(addr);					//send the addr byte
}
