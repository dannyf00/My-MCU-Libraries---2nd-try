#include <pic24.h>						//we use pic24f
#include "gpio.h"
#include "ad5932.h"						//we use ad5932

//hardware configuration
//end hardware configuration

//global defines
//#define F_AD9850		125000000ul		//reference clock frequency
//#define W_AD5932		24				//bit-width. = 24 bits for ad5932

//#define AD5932_DELAY()	NOP()			//waste some time

//stroke pins. pins idle low
//#define AD5932_STROKE(pins)		do {IO_SET(AD5932_PORT, pins); AD5932_DELAY(); IO_CLR(AD5932_PORT, pins);} while (0)


//global variables
//AD5932_T ad5932;

//initialize the pins
void ad5932_init(void) {
	//ctrl sets as output, and idles low
	IO_SET(AD5932_PORT, AD5932_CTRL);	IO_IN(AD5932_DDR, AD5932_CTRL); //ctrl idles low (pulled low by syncout) -> active low-to-high transistion

	//set up the control pins
	IO_SET(AD5932_PORT, AD5932_SCLK | AD5932_FSYNC | AD5932_SDATA); //set the pins -> idle high
	IO_OUT(AD5932_DDR, AD5932_SDATA | AD5932_FSYNC | AD5932_SCLK);	//set pins as output

	//reset the device
	//ad5932_sendword(AD5932_RESET | AD5932_SINE);		//reset the device, default to sine wave
}

//send ad5932 a word (=two bytes), msb first
void ad5932_sendword(unsigned short dat) {
	unsigned short i=0x8000;						//mask. msb first

	//IO_SET(AD5932_PORT, AD5932_FSYNC);			//clear ad5932_fsync
	//AD5932_DELAY();									//waste some time
	IO_CLR(AD5932_PORT, AD5932_FSYNC);			//start to write serial data

	//IO_SET(AD5932_PORT, AD5932_FSYNC);				//pins idle high
	do {
		IO_SET(AD5932_PORT, AD5932_SCLK);			//idle sclk high
		if (dat & i) IO_SET(AD5932_PORT, AD5932_SDATA);	//send '1'
		else IO_CLR(AD5932_PORT, AD5932_SDATA);			//send '0'
		IO_CLR(AD5932_PORT, AD5932_SCLK);			//send the bit on sclk's falling edge
		i = i>>1;									//shift to the next bit
	} while (i);
	IO_SET(AD5932_PORT, AD5932_SCLK);				//reset the wclock line to high

	//bring FSELECT high
	IO_SET(AD5932_PORT, AD5932_FSYNC);			//clear ad5932_fsync
}

//convert frequency to words
//calculate Freq * 2^BitCount / Divisor
unsigned long ad5932_f2w(unsigned long freq) {

   unsigned long Dividend = freq;
   unsigned long Quotient = 0;
   unsigned long Divisor = F_AD5932/*125000000ul*/;	 //F_AD9850, in hz

   unsigned char BitCount;

   for( BitCount=W_AD5932; BitCount!=0; BitCount-- ) {	//*2^32
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
//for sine freq sweep from fstart to fend, in fsteps
void ad5932_sinesweep(unsigned long fstart, unsigned long fend, unsigned long fsteps) {
	//set up wave output form
	//reset the device
	ad5932_sendword(AD5932_DEFAULT | AD5932_SINE);		//reset the device, default to sine wave

	//send fdelta
	if (fend >= fstart) {					//positive steps
		fend = + ad5932_f2w((fend - fstart) / fsteps);						//convert 32-bit freq to 32-bit tuning words
	} else {
		fend = - ad5932_f2w((fstart - fend) / fsteps);	//calculate the steps
	}
	ad5932_sendword(AD5932_FDELTALSB | (fend & 0x0fff));	//send the 12-bit lsb
	fend = fend >> 12; ad5932_sendword(AD5932_FSTARTMSB | (fend & 0x0fff));	//send the 12-bit msb

	//send fstart
	fstart = ad5932_f2w(fstart);						//convert 32-bit freq to 32-bit tuning words
	ad5932_sendword(AD5932_FSTARTLSB | (fstart & 0x0fff));	//send the 12-bit lsb
	fstart = fstart >> 12; ad5932_sendword(AD5932_FSTARTMSB | (fstart & 0x0fff));	//send the 12-bit msb

	//send fsteps
	ad5932_sendword(AD5932_NINCR | (fsteps & 0x0ffff));	//send fsteps

	//send Tincr
	ad5932_sendword(AD5932_TINT | AD5932_TINTMULT | (AD5932_TINTCNT & 0x07ff)); 	//output cycles is 11 bits

}

//convert frequency / phase defaults to 0
//for triangle freq sweep from fstart to fend, in fsteps,
void ad5932_trisweep(unsigned long fstart, unsigned long fend, unsigned long fsteps) {
	//set up wave output form
	//reset the device
	ad5932_sendword(AD5932_DEFAULT | AD5932_TRI);		//reset the device, default to sine wave

	//send fdelta
	if (fend >= fstart) {					//positive steps
		fend = ad5932_f2w((fend - fstart) / fsteps);						//convert 32-bit freq to 32-bit tuning words
	} else {
		fend = - ad5932_f2w((fstart - fend) / fsteps);	//calculate the steps
	}
	ad5932_sendword(AD5932_FDELTALSB | (fend & 0x0fff));	//send the 12-bit lsb
	fend = fend >> 12; ad5932_sendword(AD5932_FSTARTMSB | (fend & 0x0fff));	//send the 12-bit msb

	//send fstart
	fstart = ad5932_f2w(fstart);						//convert 32-bit freq to 32-bit tuning words
	ad5932_sendword(AD5932_FSTARTLSB | (fstart & 0x0fff));	//send the 12-bit lsb
	fstart = fstart >> 12; ad5932_sendword(AD5932_FSTARTMSB | (fstart & 0x0fff));	//send the 12-bit msb

	//send fsteps
	ad5932_sendword(AD5932_NINCR | (fsteps & 0x0ffff));	//send fsteps

	//send Tincr
	ad5932_sendword(AD5932_TINT | AD5932_TINTMULT | (AD5932_TINTCNT & 0x07ff)); 	//output cycles is 11 bits

}

