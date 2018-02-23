#include <pic24.h>						//we use pic24f
#include "gpio.h"
#include "encoder.h"					//we use encoders

//hardware configuration
//end of hardware configuration


//reset the encoder
void encoder_init(void) {
	IO_IN(ENC_DDR, ENC_A | ENC_B);			//keya/b as input
}

//determine increment / decrement of the encoder
const signed char encoder_states[]={0, -1, 1, 0, 1, 0, 0, -1, -1, 0, 0, 1, 0, 1, -1, 0};

//change notification isr
signed char encoder_read() {
	//static unsigned char encoder_output=0x00;
	static unsigned char encoder_ABs=0x00;			//AB key read out, Previous in the high 2 bits and current in the low two bits;
	static signed char tmp=0;

	encoder_ABs = (encoder_ABs << 2) & 0x0f;			//left 2 bits now contain the previous AB key read-out;
	//tmp=IO_GET(port, pin_a | pin_b);		//read ab pins
	if (ENC_PORT & ENC_A) encoder_ABs |= 0x01;			//set the 1st bit if A is high now;
	if (ENC_PORT & ENC_B) encoder_ABs |= 0x02;			//set the 0th bit if B is high;

	tmp += encoder_states[encoder_ABs];		//read the encoder states
	if (tmp >= ENC_CLICKS) {
		tmp -= ENC_CLICKS;
		return +1;
	}
	if (tmp <=-ENC_CLICKS) {
		tmp += ENC_CLICKS;
		return -1;
	}
	return 0;
}
