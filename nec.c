#include <pic24.h>						//we use pic24f
#include "gpio.h"
#include "nec.h"						//nec transmitter/receiver - only transmitter is implemented

//hardware configuration
//#define NEC_PORT			PORTB
//#define NEC_DDR				TRISB
//#define NEC_TX				(1<<15)
//#define NEC_RX				(1<<1)

//delay 13us
//may need to change for your mcu/frequency
#define NEC_COUNT			(562.5/26.3+1)	//count for the count-down loop
#define NEC_13us()			do {NOP32(); NOP8(); NOP4(); NOP2();} while (0)	//delay for 13.15us - at 4Mhz mips, 13.15 / (0.25) = 52, - 2us = 50 instructions, with overhead.

#define TX_ON()				IO_SET(NEC_PORT, NEC_TX)	//turn on the led
#define TX_OFF()			IO_CLR(NEC_PORT, NEC_TX)	//turn off the led
#define TX_NOP()			NOP()						//do nothing - equal length as TX_ON/_OFF
//end hardware configuration

//global defines

//global variables

//reset the nec module
void nec_init(void) {
	IO_CLR(NEC_PORT, NEC_TX);			//clera tc
	IO_OUT(NEC_DDR, NEC_TX);			//tx as output

#if defined(NEC_RX)
	IO_IN(NEC_DDR, NEC_RX);				//RX as input
#endif
}

//send a burst of pulses, 562.5us
void nec_burst(void) {
	unsigned char count;

	//pulse for 562.5us
	count=NEC_COUNT;
	while (count--) {
		TX_ON();		//set tx
		NEC_13us();						//wait 13us
		TX_OFF();		//clera tx
		NEC_13us();
	};
}

//send a space of 562.5us
void nec_space(void) {
	unsigned char count;

	//pulse for 562.5us
	count=NEC_COUNT;
	while (count--) {
		TX_NOP();							//IO_SET(NEC_PORT, NEC_TX);		//set tx
		NEC_13us();						//wait 13us
		TX_NOP();							//IO_CLR(NEC_PORT, NEC_TX);		//clera tx
		NEC_13us();
	};
}

//send '0'
#define nec_0()			do {nec_burst(); nec_space();} while (0)		//send '1'
#define nec_1()			do {nec_burst(); nec_space(); nec_space(); nec_space();} while (0)	//send '0'

//send a char
void nec_8(unsigned char dat) {
	unsigned char mask = 0x01;			//lsb first

	do {
		if (dat & mask) nec_1();		//send '1'
		else nec_0();					//send '0'
		mask = mask << 1;				//shift to the next bit
	} while (mask);
}

//send a 32-bit word
void nec_tx(unsigned char addr, unsigned char dat) {
	unsigned char count;

	unsigned char _addr=~addr;			//logic inverse of addr
	unsigned char _dat =~dat;			//logic inverse of dat

	//send the header
	count = 9000/562.5;
	while (count--) nec_burst();		//send out 9ms of bursts
	count = 4500/562.5;
	while (count--) nec_space();		//send out 4.5ms of space

	//send address
	nec_8(addr);						//send the address
	nec_8(_addr);						//send the logic inverse of address
	//send data
	nec_8(dat);							//send the dat
	nec_8(_dat);						//send the logic inverse of the dat
	//should have taken 67.5ms to execute to this point

	//send the last burst - stop bit
	nec_burst();
}

