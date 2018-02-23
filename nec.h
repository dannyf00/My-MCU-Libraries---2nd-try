#ifndef NEC_H_INCLUDED
#define NEC_H_INCLUDED

//hardware configuration
#define NEC_PORT			PORTB
#define NEC_DDR				TRISB
#define NEC_TX				(1<<15)
//#define NEC_RX				(1<<1)	//uncomment is the receiver is implemented

//delay 13us
//may need to change for your mcu/frequency
//#define NEC_COUNT			(562.5/26.3+1)	//count for the count-down loop
//#define NEC_13us()			do {NOP32(); NOP8(); NOP4(); NOP2();} while (0)	//delay for 13.15us - at 4Mhz mips, 13.15 / (0.25) = 52, - 2us = 50 instructions, with overhead.

//#define TX_ON()				IO_SET(NEC_PORT, NEC_TX)	//turn on the led
//#define TX_OFF()			IO_CLR(NEC_PORT, NEC_TX)	//turn off the led
//#define TX_NOP()			NOP()						//do nothing - equal length as TX_ON/_OFF
//end hardware configuration

//global defines

//global variables

//reset the nec module
void nec_init(void);

//send a 32-bit word
void nec_tx(unsigned char addr, unsigned char dat);

#endif // NEC_H_INCLUDED
