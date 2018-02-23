#ifndef LTC1450_H_INCLUDED
#define LTC1450_H_INCLUDED

/* 	code to drive ltc1450 parallel dac
	pins connected
	data pins
	cs pins (csmsb and cslsb tied together), specified in user programs
	ldac pin tied together

	pins not connected
	rw pin tied to ground
	clr pin pulled to vcc

 */

//hardware configuration
#define LTC1450MSB_PORT			PORTC
#define LTC1450MSB_DDR			DDRC
#define LTC1450MSB				0x0f	//4-bit output only

#define LTC1450LSB_PORT			PORTB
#define LTC1450LSB_DDR			DDRB
#define LTC1450LSB				0xff	//8-bit output only

#define LTC1450CTRL_PORT		PORTC
#define LTC1450CTRL_DDR			DDRC
//#define LTC1450CTRL_CS			(1<<4)	//for msb/lsb. csmsb and cslsb tied together. defined in user files
//#define LTC1450CTRL_CSMSB		(1<<0)	//for msb
//#define LTC1450CTRL_CSLSB		(1<<1)	//for lsb
//#define LTC1450CTRL_WR			(1<<2)	//tied low active low to write data to input register. data latches into the input register on rising edge
#define LTC1450CTRL_LDAC		(1<<5)	//active low. load for transparency. rising edge load data from input register to output register
//#define LTC1450CTRL_CLR			(1<<4)	//active high. low to reset all input register

//end hardware configuration

//macros to select a chip
#define ltc1450_select(cs)		{ltc1450_deselect(cs); IO_CLR(LTC1450CTRL_PORT, cs);}
#define ltc1450_deselect(cs)	{IO_SET(LTC1450CTRL_PORT, cs); IO_OUT(LTC1450CTRL_DDR, cs);}
//output the value on msb_lsb
#define LTC1450_OUT(msb_lsb)	{LTC1450MSB_PORT = ((LTC1450MSB_PORT) & ~(LTC1450MSB)) | (((msb_lsb) >> 8) & LTC1450MSB); LTC1450LSB_PORT = (msb_lsb);}

//latch data to output
#define ltc1450_latch()			{IO_CLR(LTC1450CTRL_PORT, LTC1450CTRL_LDAC); IO_OUT(LTC1450CTRL_DDR, LTC1450CTRL_LDAC); IO_SET(LTC1450CTRL_PORT, LTC1450CTRL_LDAC);}

//initialize the pins
void ltc1450_init(void);

//write to ltc1450
#define ltc1450_write(val)		LTC1450_OUT(val)

#endif // LTC1450_H_INCLUDED
