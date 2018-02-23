#include <pic24.h>						//we use pic24f
#include "gpio.h"
#include "ad9832.h"						//we use ad9832

//hardware configuration
//end hardware configuration

//global defines
//#define F_AD9850		125000000ul		//reference clock frequency
//#define W_AD9832		32				//bit-width. = 32 bits for ad9832

//#define AD9832_DELAY()	NOP()			//waste some time

//stroke pins. pins idle low
//#define AD9832_STROKE(pins)		do {IO_SET(AD9832_PORT, pins); AD9832_DELAY(); IO_CLR(AD9832_PORT, pins);} while (0)


//global variables
//AD9832_T ad9832;

//initialize the pins
void ad9832_init(void) {
	IO_SET(AD9832_PORT, AD9832_SCLK | AD9832_FSYNC | AD9832_SDATA); //set the pins -> idle high
	IO_OUT(AD9832_DDR, AD9832_SDATA | AD9832_FSYNC | AD9832_SCLK);

	//reset the device
	ad9832_sendword(AD9832_RESET);		//reset the device
	ad9832_sendword(AD9832_POWERON);	//powern on the chip
	ad9832_sendword(AD9832_SELSRC | AD9832_SYNC);	//use fselect bit to select registers and allow synchronization
}

//send ad9832 a word (=two bytes), msb first
void ad9832_sendword(unsigned short dat) {
	unsigned short i=0x8000;						//mask. msb first

	//IO_SET(AD9832_PORT, AD9832_FSYNC);			//clear ad9832_fsync
	//AD9832_DELAY();									//waste some time
	IO_CLR(AD9832_PORT, AD9832_FSYNC);			//start to write serial data

	//IO_SET(AD9832_PORT, AD9832_FSYNC);				//pins idle high
	do {
		IO_SET(AD9832_PORT, AD9832_SCLK);			//idle sclk high
		if (dat & i) IO_SET(AD9832_PORT, AD9832_SDATA);	//send '1'
		else IO_CLR(AD9832_PORT, AD9832_SDATA);			//send '0'
		IO_CLR(AD9832_PORT, AD9832_SCLK);			//send the bit on sclk's falling edge
		i = i>>1;									//shift to the next bit
	} while (i);
	IO_SET(AD9832_PORT, AD9832_SCLK);				//reset the wclock line to high

	//bring FSELECT high
	IO_SET(AD9832_PORT, AD9832_FSYNC);			//clear ad9832_fsync
}

//convert frequency to words
//calculate Freq * 2^BitCount / Divisor
unsigned long ad9832_f2w(unsigned long freq) {

   unsigned long Dividend = freq;
   unsigned long Quotient = 0;
   unsigned long Divisor = F_AD9832/*125000000ul*/;	 //F_AD9850, in hz

   unsigned char BitCount;

   for( BitCount=W_AD9832; BitCount!=0; BitCount-- ) {	//*2^32
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
//for freq register 0
void ad9832_freq(unsigned long freq) {
	static unsigned char freqx=0;			//select the frequency registers alternately. 0->freq0, 1->freq1

	freq = ad9832_f2w(freq);						//convert 32-bit freq to 32-bit tuning words
	if (freqx) {							//write to freq1
		ad9832_sendword(AD9832_FREQB | AD9832_F1LLSB | (freq & 0x00ff));			//send the least significant 8 bits of lsb
		freq = freq >> 8; ad9832_sendword(AD9832_FREQW | AD9832_F1HLSB | (freq & 0x00ff));			//send the 16-bit lsb (present + defer register)
		freq = freq >> 8; ad9832_sendword(AD9832_FREQB | AD9832_F1LMSB | (freq & 0x00ff));	//send the least significant 8 bits of msb
		freq = freq >> 8; ad9832_sendword(AD9832_FREQW | AD9832_F1HMSB | (freq & 0x00ff));	//send the 16-bit msb (present + defer register)
		ad9832_sendword(AD9832_FREQ1);		//use register 1
		freqx = 0;							//next time, write to freq0
	} else {								//write to freq0
		ad9832_sendword(AD9832_FREQB | AD9832_F0LLSB | (freq & 0x00ff));			//send the least significant 8 bits of lsb
		freq = freq >> 8; ad9832_sendword(AD9832_FREQW | AD9832_F0HLSB | (freq & 0x00ff));			//send the 16-bit lsb (present + defer register)
		freq = freq >> 8; ad9832_sendword(AD9832_FREQB | AD9832_F0LMSB | (freq & 0x00ff));	//send the least significant 8 bits of msb
		freq = freq >> 8; ad9832_sendword(AD9832_FREQW | AD9832_F0HMSB | (freq & 0x00ff));	//send the 16-bit msb (present + defer register)
		ad9832_sendword(AD9832_FREQ0);		//use register 0
		freqx = 1;							//next time, write to freq1
	}
	//ad9832_sendword(AD9832_POWERON);				//activate the device
}

//convert frequency / phase defaults to 0
//for freq register 1
void ad9832_freq1(unsigned long freq) {
	freq = ad9832_f2w(freq);						//convert 32-bit freq to 32-bit tuning words
	ad9832_sendword(AD9832_RESET);					//reset the chip
	ad9832_sendword(AD9832_FREQB | AD9832_F1HMSB | ((freq & 0xf000) >> 24));	//send the first 8 bits (high 8 bits of 16-msb)
	ad9832_sendword(AD9832_FREQW | AD9832_F1LMSB | ((freq & 0x0f00) >> 16)); 	//send the 2nd 8 bits (low 8 bits of 16-msb);
	ad9832_sendword(AD9832_FREQB | AD9832_F1HLSB | ((freq & 0x00f0) >>  8));	//send the 3rd 8 bits (high 8 bits of 16-lsb)
	ad9832_sendword(AD9832_FREQW | AD9832_F1LLSB | ((freq & 0x000f) >>  0)); 	//send the 4th 8 bits (low 8 bits of 16-lsb);
	ad9832_sendword(AD9832_POWERON);				//activate the device
}

