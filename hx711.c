#include "hx711.h"			//we use hx711

//hardware configuration
//end hardware configuration

//global defines

//global variables

//initialize hx711
void hx711_init(void) {
	//dout idles as input
	IO_IN(HX711DIN_DDR, HX711DIN);

	//sck as output and idles low
	IO_CLR(HX711SCK_PORT, HX711SCK);
	IO_OUT(HX711SCK_DDR, HX711SCK);
}

//read hx711, 25 pulses
int32_t hx711_read(void) {
	uint8_t mask = 24;						//mask, msb first
	int32_t tmp=0;

	//hx711_init();							//rest the pins, optional
	IO_CLR(HX711SCK_PORT, HX711SCK);		//sck idles low
	do {
		tmp = tmp << 1;
		IO_SET(HX711SCK_PORT, HX711SCK);	//rising edge of sck
		if (IO_GET(HX711DIN_PORT, HX711DIN)) tmp+=1;
		mask-= 1;							//decrement mask
		IO_CLR(HX711SCK_PORT, HX711SCK);	//falling edge of sck
	} while (mask);
	IO_SET(HX711SCK_PORT, HX711SCK); IO_CLR(HX711SCK_PORT, HX711SCK);	//25th pulse
	//if (tmp &  0x800000ul) {tmp = (tmp ^ 0xfffffful) + 1; tmp = -tmp;}
	tmp = (tmp & 0x800000ul)?(tmp | 0xff000000ul):tmp;
	return tmp;
}

//read hx711, x32 gain
int32_t hx711_readx32(void) {
	int32_t tmp;
	tmp=hx711_read();						//read hx711, 25 pulses
	IO_SET(HX711SCK_PORT, HX711SCK); IO_CLR(HX711SCK_PORT, HX711SCK);	//26th pulse
	return tmp;
}
//read hx711, x64 gain
int32_t hx711_readx64(void) {
	int32_t tmp;
	tmp=hx711_read();						//read hx711, 25 pulses
	IO_SET(HX711SCK_PORT, HX711SCK); IO_CLR(HX711SCK_PORT, HX711SCK);	//26th pulse
	IO_SET(HX711SCK_PORT, HX711SCK); IO_CLR(HX711SCK_PORT, HX711SCK);	//27th pulse
	return tmp;
}
