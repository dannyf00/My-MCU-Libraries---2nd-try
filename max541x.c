#include <regx51.h>
#include "gpio.h"
#include "max541x.h"						//we use max5413/4/5 chips

//reset the chip - does nothing
void max541x_init(void) {
	//IO_SET(MAX541X_PORT, MAX541X_CS);		//cs idles high
	//IO_CLR(MAX541X_PORT, MAX541X_CLK | MAX541X_DIN);	//clk / din idles low
	//IO_OUT(MAX541X_DDR, MAX541X_CS | MAX541X_CLK | MAX541X_DIN);	//output pins
}

//send a byte to pot A
unsigned char max541xa_write(unsigned char position) {
	unsigned char mask = 0x80;

	IO_SET(MAX541X_PORT, MAX541X_CS);		//cs idles high
	IO_CLR(MAX541X_PORT, MAX541X_DIN | MAX541X_CLK);		//din / clk low
	IO_OUT(MAX541X_DDR, MAX541X_CS | MAX541X_CLK | MAX541X_DIN);	//output pins

	//select the chip
	IO_CLR(MAX541X_PORT, MAX541X_CS);		//clear cs

	//select a -> din low when clk goes high
	IO_CLR(MAX541X_PORT, MAX541X_DIN);		//din low -> select pot A

	//clk goes high, then low
	IO_SET(MAX541X_PORT, MAX541X_CLK);		//clk goes high
	NOP();
	IO_CLR(MAX541X_PORT, MAX541X_CLK);		//clk goes low

	//now, send the data byte, msb first
	do {
		if (position & mask) IO_SET(MAX541X_PORT, MAX541X_DIN);	//send 1
		else IO_CLR(MAX541X_PORT, MAX541X_DIN);					//send 0
		IO_SET(MAX541X_PORT, MAX541X_CLK);	//rising edge of clk
		mask = mask >> 1;					//shift to the next bit
		IO_CLR(MAX541X_PORT, MAX541X_CLK);	//clear clk
	} while (mask);							//until all 8 bits are sent
	IO_CLR(MAX541X_PORT, MAX541X_DIN);		//din idles low - not necessary
	IO_SET(MAX541X_PORT, MAX541X_CS);		//cs idles high
	return 0;
}


//send a byte to pot B
unsigned char max541xb_write(unsigned char position) {
	unsigned char mask = 0x80;

	IO_SET(MAX541X_PORT, MAX541X_CS);		//cs idles high
	IO_CLR(MAX541X_PORT, MAX541X_DIN | MAX541X_CLK);		//din / clk low
	IO_OUT(MAX541X_DDR, MAX541X_CS | MAX541X_CLK | MAX541X_DIN);	//output pins

	//select the chip
	IO_CLR(MAX541X_PORT, MAX541X_CS);		//clear cs

	//select b -> din high when clk goes high
	IO_SET(MAX541X_PORT, MAX541X_DIN);		//din high -> select pot B

	//clk goes high, then low
	IO_SET(MAX541X_PORT, MAX541X_CLK);		//clk goes high
	NOP();
	IO_CLR(MAX541X_PORT, MAX541X_CLK);		//clk goes low

	//now, send the data byte, msb first
	do {
		if (position & mask) IO_SET(MAX541X_PORT, MAX541X_DIN);	//send 1
		else IO_CLR(MAX541X_PORT, MAX541X_DIN);					//send 0
		IO_SET(MAX541X_PORT, MAX541X_CLK);	//rising edge of clk
		mask = mask >> 1;					//shift to the next bit
		IO_CLR(MAX541X_PORT, MAX541X_CLK);	//clear clk
	} while (mask);							//until all 8 bits are sent
	IO_CLR(MAX541X_PORT, MAX541X_DIN);		//din idles low - not necessary
	IO_SET(MAX541X_PORT, MAX541X_CS);		//cs idles high
	return 0;
}
