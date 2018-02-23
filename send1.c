//using 1 wire to send serial data
//msb first
//on the rising edge
//based on roman black's shift1 approach

#include <regx51.h>						//we use keil c51
#include "gpio.h"
#include "delay.h"						//we use delay
#include "send1.h"						//we use send1 protocol

//hardware configuration
//end hardware configuration

//initialize send1
void send1_init(void) {
	//IO_SET(SEND1_PORT, SEND1_SCO);		//clear sco
	//IO_OUT(SEND1_DDR, SEND1_SCO);		//sco as output
}

#define send1_delay()		{delay_us(SEND1_DLY);}

//send bit 1
#define send1_1()			{IO_CLR(SEND1_PORT, SEND1_SCO); IO_SET(SEND1_PORT, SEND1_SCO);}

//send bit 0
#define send1_0()			{IO_CLR(SEND1_PORT, SEND1_SCO); send1_delay(); IO_SET(SEND1_PORT, SEND1_SCO);}

//send a byte
void send1_write(unsigned char dat) {
	unsigned char mask = 0x80;			//msb first
	
	do {
		//initialize the bus - bring SCO to high
		IO_SET(SEND1_PORT, SEND1_SCO);		//set sco
		IO_OUT(SEND1_DDR, SEND1_SCO);		//sco as output
		send1_delay();				//charge up the cap
	
		if (dat & mask) send1_1()		//send 1
		else send1_0();					//send 0
		mask = mask >> 1;				//shift to the next bit
	} while (mask);
}
