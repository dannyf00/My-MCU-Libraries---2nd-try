#include <regx51.h>
#include "gpio.h"
#include "delay.h"
#include "ad5206.h"							//we use ad5206

//reset the device
void ad5206_init(void) {
}

//send a byte
unsigned char ad5206_write(unsigned char a210, unsigned char dat) {
	unsigned char mask;

	IO_CLR(AD5206_PORT, AD5206_CLK);	//clk idle low
	//IO_SET(AD5206_PORT, AD5206_CS);		//cs idles high
	IO_OUT(AD5206_DDR, AD5206_CLK | AD5206_SDO);	//pins as output

	//IO_CLR(AD5206_PORT, AD5206_CS);		//pull cs low to enable chip
	
	mask = 0x04;				//send lowest 3 bits in a210;
	IO_CLR(AD5206_PORT, AD5206_CLK);	//clk idle low
	do {
		if (a210 & mask) IO_SET(AD5206_PORT, AD5206_SDO);	//send 1
		else IO_CLR(AD5206_PORT, AD5206_SDO);						//send 0
		IO_SET(AD5206_PORT, AD5206_CLK);	//clk's rising edge
		mask = mask >> 1;
		IO_CLR(AD5206_PORT, AD5206_CLK);	//clk's falling edge
	} while (mask);
	
	mask = 0x80;				//send dat;
	IO_CLR(AD5206_PORT, AD5206_CLK);	//clk idle low
	do {
		if (dat & mask) IO_SET(AD5206_PORT, AD5206_SDO);	//send 1
		else IO_CLR(AD5206_PORT, AD5206_SDO);						//send 0
		IO_SET(AD5206_PORT, AD5206_CLK);	//clk's rising edge
		mask = mask >> 1;
		IO_CLR(AD5206_PORT, AD5206_CLK);	//clk's falling edge
	} while (mask);
	
	//IO_SET(AD5206_PORT, AD5206_CS);		//pull cs high


	return 0;
}
