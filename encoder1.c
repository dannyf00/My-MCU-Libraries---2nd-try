//#include <ioavr.H>						//we use iar avr
//#include <regx51.h>							//we use keil c51
#include <pic24.h>							//we use pic24f
#include "gpio.h"
#include "encoder1.h"						//we use rotary encoder

//reset the encoder
void encoder1_init(void) {
	IO_IN(ENC1_DDR, ENC1_A | ENC1_B);			//keya/b as input
}

//determine increment / decrement of the encoder
unsigned char encoder1_read(void) {
	static const signed char encoder_states[]={0, -1, 1, 0, 1, 0, 0, -1, -1, 0, 0, 1, 0, 1, -1, 0};
	//static unsigned char encoder_output=0x00;
	static unsigned char ABs=0x00;			//AB key read out, Previous in the high 2 bits and current in the low two bits;
	//unsigned char tmp;

	ABs = (ABs << 2) & 0x0f;			//left 2 bits now contain the previous AB key read-out;
	//tmp=IO_GET(port, pin_a | pin_b);		//read ab pins
	if (ENC1_PORT & ENC1_A) ABs |= 0x02;			//set the 1st bit if A is high now;
	if (ENC1_PORT & ENC1_B) ABs |= 0x01;			//set the 0th bit if B is high;
	//ABs &= 0x0f;					//only retain ABs' last 4 bits (A_previous, B_previous, A_current, B_current)
	//encoder_output += ABs_states[ABs];		//return encoder_output;			//return the absolute value
	return encoder_states[ABs];				//return the relative value (+1 = clockwise, 0, -1 = counterclockwise)
}
