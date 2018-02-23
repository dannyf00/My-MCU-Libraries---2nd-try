#include <regx51.h>								//we use keil c51
#include "gpio.h"
#include "tlc1543.h"							//we use tlc1543

void tlc1543_init(void) {
	IO_CLR(TLC1543_PORT, TLC1543_CLK);	//clear clk
	IO_OUT(TLC1543_DDR, TLC1543_CLK);	//clk as output

	
	IO_IN(TLC1543_DDR, TLC1543_EOC);
}

unsigned short tlc1543_write(unsigned short word_t) {
	unsigned short mask = 1<<9;			//mask
	unsigned short tmp=0;				//temp variable

	IO_CLR(TLC1543_PORT, TLC1543_CLK);	//clear clk
	IO_OUT(TLC1543_DDR, TLC1543_CLK | TLC1543_ADDR);	//clk as output

	IO_IN(TLC1543_DDR, TLC1543_MISO);	//miso as input

	do {
		tmp = tmp << 1;						//shift to the next bit

		//read miso
		if (TLC1543_PORT_IN & TLC1543_MISO) tmp |= 0x01;
		else tmp |= 0x00;
		
		//write addr
		if (word_t & mask) IO_SET(TLC1543_PORT, TLC1543_ADDR);
		else IO_CLR(TLC1543_PORT, TLC1543_ADDR);

		IO_SET(TLC1543_PORT, TLC1543_CLK);	//strobe out the data
		mask = mask >> 1;					//shift for the next bit
		IO_CLR(TLC1543_PORT, TLC1543_CLK);	//reset the clk
	} while (mask);
	
	return tmp;
}

unsigned short tlc1543_read(unsigned char cs, unsigned short ch) {
	unsigned short tmp;

	tlc1543_select(cs);				//select the chip
	tlc1543_write(ch);				//write the adc channel to the chip
	tlc1543_deselect(cs);			//start adc

	while (!tlc1543_eoc()) continue;		//wait for adc to finish

	tlc1543_select(cs);				//select the chip
	tmp=tlc1543_write(ch);				//read the adc results
	tlc1543_deselect(cs);			//deselect the chip

	return tmp;

}
