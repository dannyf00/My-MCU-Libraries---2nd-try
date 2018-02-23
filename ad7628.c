#include <regx51.h>							//we use keil c51
#include "gpio.h"
#include "ad7628.h"							//we use ad7628

//hardware configuration
//WR1/WR2/XFER tied to ground
//ILE tied to high
//CS to MCU
//AB to MCU
//end hardware configuration

#define ad7628_deselect(cs)		{IO_SET(AD7628_CTRL_PORT, cs); IO_OUT(AD7628_CTRL_DDR, cs);}
#define ad7628_select(cs)		{ad7628_deselect(cs); IO_CLR(AD7628_CTRL_PORT, cs);}

#define ad7628_dewrite(wr)		{IO_SET(AD7628_CTRL_PORT, wr); IO_OUT(AD7628_CTRL_DDR, wr);}
#define ad7628_write(wr)		{ad7628_dewrite(wr); IO_CLR(AD7628_CTRL_PORT, wr);}

#define ad7628_daca(dac_ab)		{IO_CLR(AD7628_CTRL_PORT, dac_ab); IO_OUT(AD7628_CTRL_DDR, dac_ab);}
#define ad7628_dacb(dac_ab)		{IO_SET(AD7628_CTRL_PORT, dac_ab); IO_OUT(AD7628_CTRL_DDR, dac_ab);}

//strobe out the data
#define ad7628_xfer(xfer)		{IO_CLR(AD7628_CTRL_PORT, xfer); IO_OUT(AD7628_CTRL_DDR, xfer);}
#define ad7628_dexfer(xfer)		{IO_SET(AD7628_CTRL_PORT, xfer); IO_OUT(AD7628_CTRL_DDR, xfer);}

//initialize the module
void ad7628_init(void) {
	IO_CLR(AD7628_DATA_PORT, AD7628_DATA);		//clear the output pins
	IO_OUT(AD7628_DATA_DDR, AD7628_DATA);		//data pins as output

	ad7628_deselect(AD7628_CTRL_CS);			//deselect the chip
	ad7628_daca(AD7628_CTRL_AB);				//select daca by default
}

//send a byte to ad7628a
void ad7628a_write(unsigned char dat) {
	ad7628_select(AD7628_CTRL_CS);				//select the chip
	ad7628_daca(AD7628_CTRL_AB);				//select daca
	AD7628_DATA_PORT = dat;						//output the data
#ifdef AD7628_CTRL_WR
	ad7628_write(AD7628_CTRL_WR);				//write to the chip
	ad7628_dewrite(AD7628_CTRL_WR);				//dewrite to the chip
#endif

#ifdef AD7628_CTRL_XFER
	ad7628_xfer(AD7628_CTRL_XFER);				//strobe out the data
	//ad7628_write(AD7628_CTRL_WR);				//write to the chip
	//ad7628_dewrite(AD7628_CTRL_WR);				//dewrite to the chip
	ad7628_dexfer(AD7628_CTRL_XFER);				//strobe out the data
#endif
	ad7628_deselect(AD7628_CTRL_CS);			//deselect the chip

}

//send a byte to ad7628b
void ad7628b_write(unsigned char dat) {
	ad7628_select(AD7628_CTRL_CS);				//select the chip
	ad7628_dacb(AD7628_CTRL_AB);				//select daca
	AD7628_DATA_PORT = dat;						//output the data
#ifdef AD7628_CTRL_WR
	ad7628_write(AD7628_CTRL_WR);				//write to the chip
	ad7628_dewrite(AD7628_CTRL_WR);				//dewrite to the chip
#endif

#ifdef AD7628_CTRL_XFER
	ad7628_xfer(AD7628_CTRL_XFER);				//strobe out the data
	//ad7628_write(AD7628_CTRL_WR);				//write to the chip
	//ad7628_dewrite(AD7628_CTRL_WR);				//dewrite to the chip
	ad7628_dexfer(AD7628_CTRL_XFER);				//strobe out the data
#endif
	ad7628_deselect(AD7628_CTRL_CS);			//deselect the chip

}

