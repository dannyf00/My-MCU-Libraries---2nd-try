#include <pic24.h>						//we use pic24f
#include "gpio.h"
#include "ad9850.h"						//we use ad9850

//hardware configuration
//end hardware configuration

//global defines
//#define F_AD9850		125000000ul		//reference clock frequency
//#define W_AD9850		32			//bitcount for the dds

//#define AD9850_DELAY()	NOP()			//waste some time

//stroke pins. pins idle low
//#define AD9850_STROKE(pins)		do {IO_SET(AD9850_PORT, pins); AD9850_DELAY(); IO_CLR(AD9850_PORT, pins);} while (0)


//global variables
//AD9850_T ad9850;

//initialize the pins
void ad9850_init(void) {
	IO_CLR(AD9850_PORT, AD9850_SDATA | AD9850_WCLK | AD9850_FQUD);	//clear the pins
	IO_OUT(AD9850_DDR, AD9850_SDATA | AD9850_WCLK | AD9850_FQUD);

	//device boot up to parallel mode
	//d0/d1 = 1, d2 = 0 -> sets the chip to serial mode
	IO_SET(AD9850_PORT, AD9850_WCLK);
	AD9850_DELAY();
	IO_CLR(AD9850_PORT, AD9850_WCLK);				//ad9850_wclk idles low

	//update the registers to enter serial mode
	//enable serial  mode
	IO_SET(AD9850_PORT, AD9850_FQUD);
	AD9850_DELAY();
	IO_CLR(AD9850_PORT, AD9850_FQUD);				//ad9850_fqud idles low

}

//send ad9850 byte - not directly called, lsb first
void ad9850_sendbyte(unsigned char dat) {
	unsigned char i=1<<0;

	IO_CLR(AD9850_PORT, AD9850_WCLK | AD9850_FQUD);	//clear the pins
	do {
		IO_CLR(AD9850_PORT, AD9850_WCLK);			//reset the wclock line
		if (dat & i) IO_SET(AD9850_PORT, AD9850_SDATA);	//send '1'
		else IO_CLR(AD9850_PORT, AD9850_SDATA);			//send '0'
		IO_SET(AD9850_PORT, AD9850_WCLK);			//send the bit
		i = i<<1;									//shift to the next bit
	} while (i);
	IO_CLR(AD9850_PORT, AD9850_WCLK);			//reset the wclock line
}

//send ad9850 words - lsb first
void ad9850_sendwords(unsigned long words) {
	IO_CLR(AD9850_PORT, AD9850_FQUD);				//clear the pin
	ad9850_sendbyte(words);	words = words >> 8;			//send words
	ad9850_sendbyte(words); words = words >> 8; 
	ad9850_sendbyte(words);	words = words >> 8; 
	ad9850_sendbyte(words);	//words = words >> 8; 
#if defined(AD9850_PLL6xEN)
	ad9850_sendbyte(AD9850_POWERON | AD9850_PLL6xEN);		//send the final words -> control1..0 = 0b00
#else
	ad9850_sendbyte(AD9850_POWERON);				//send the final words -> control1..0 = 0b00
#endif
	IO_SET(AD9850_PORT, AD9850_FQUD);
	AD9850_DELAY();									//wait tFH > 7ns
	IO_CLR(AD9850_PORT, AD9850_FQUD);				//reset FQUD
}

//shut down the chip
void ad9850_poweroff(void) {
	//ad9850_sendwords(0x04000000ul);
	IO_CLR(AD9850_PORT, AD9850_FQUD);				//clear the pin
	ad9850_sendbyte(0x00);							//send words, lsb first
	ad9850_sendbyte(0x00);
	ad9850_sendbyte(0x00);
	ad9850_sendbyte(0x00);
	ad9850_sendbyte(AD9850_SHUTDOWN/*0x04*/);				//send the final words -> control1..0 = 0b00, power_down = 1
	IO_SET(AD9850_PORT, AD9850_FQUD);
	AD9850_DELAY();									//wait tFH > 7ns
	IO_CLR(AD9850_PORT, AD9850_FQUD);				//reset FQUD
}

//power up the chip
void ad9850_poweron(unsigned long words) {
	ad9850_sendwords(words);
	//IO_CLR(AD9850_PORT, AD9850_FQUD);				//clear the pin
	//ad9850_sendbyte(words);							//send words, lsb first
	//words = words >> 8; ad9850_sendbyte(words);
	//words = words >> 8; ad9850_sendbyte(words);
	//words = words >> 8; ad9850_sendbyte(words);
	//ad9850_sendbyte(0x00);				//send the final words -> control1..0 = 0b00, power_down = 0
	//IO_SET(AD9850_PORT, AD9850_FQUD);
	//AD9850_DELAY();									//wait tFH > 7ns
	//IO_CLR(AD9850_PORT, AD9850_FQUD);				//reset FQUD
}

//convert frequency to words
//calculate Freq * 2^BitCount / Divisor
unsigned long ad9850_f2w(unsigned long freq) {

   unsigned long Dividend = freq;
   unsigned long Quotient = 0;
   unsigned long Divisor = F_AD9850/*125000000ul*/;	 //F_AD9850, in hz

   unsigned char BitCount;

   for( BitCount=W_AD9850/*32*/; BitCount!=0; BitCount-- ) {	//*2^32
       Dividend <<= 1;
       Quotient <<= 1;

       if( Dividend >= Divisor ) {
           Dividend -= Divisor;

           Quotient |= 1;
       }
   }

   return Quotient /*+ 1*/;
}

//convert frequency / phase defaults to 0
void ad9850_freq(unsigned long freq) {
	freq = ad9850_f2w(freq);						//convert 32-bit freq to 32-bit tuning words
	ad9850_sendwords(freq);						//defualt control word to be 0x00
	//IO_CLR(AD9850_PORT, AD9850_FQUD);				//clear the pin
	//ad9850_sendbyte(freq);							//send words, lsb first
	//freq = freq >> 8; ad9850_sendbyte(freq);
	//freq = freq >> 8; ad9850_sendbyte(freq);
	//freq = freq >> 8; ad9850_sendbyte(freq);
	//ad9850_sendbyte(/*phase*/0 << 3);				//send the final words -> control1..0 = 0b00, power_down = 0
	//IO_SET(AD9850_PORT, AD9850_FQUD);
	//AD9850_DELAY();									//wait tFH > 7ns
	//IO_CLR(AD9850_PORT, AD9850_FQUD);				//reset FQUD
}

