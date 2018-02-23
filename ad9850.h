#ifndef AD9850_H_INCLUDED
#define AD9850_H_INCLUDED

//hardware configuration
#define AD9850_PORT		LATB
#define AD9850_DDR		TRISB
#define AD9850_SDATA	(1<<5)			//ad9850 serial data input, pin D7
#define AD9850_WCLK		(1<<7)			//ad9850 w clock, rising edge, idle low
#define AD9850_FQUD		(1<<6)			//ad9850 frequency update, rising edge, idle low

//other connection
//D0/D1 -> VCC
//D2 -> GND
//RST ->  GND

//end hardware configuration

//global defines
#define F_AD9850		125000000ul		//reference clock frequency
#define W_AD9850		32		//32-bit dds

#define AD9850_1Khz		1000ul			//1khz
#define AD9850_10Khz		(AD9850_1Khz * 10)
#define AD9850_100Khz		(AD9850_1Khz * 100)
#define AD9850_1Mhz		(AD9850_1Khz * 1000)

#define AD9850_DELAY()		NOP()			//waste some time

//commands
#define AD9850_POWERON		0x00		//turn on ad9850
#define AD9850_SHUTDOWN		0x04		//power off ad9850
//#define AD9850_PLL6xEN		0x001		//enable refclk multiplier (6x)

//stroke pins. pins idle low
#define AD9850_STROKE(pins)		do {IO_SET(AD9850_PORT, pins); AD9850_DELAY(); IO_CLR(AD9850_PORT, pins);} while (0)

typedef struct {
	unsigned char W0;					//ad9850 control word, Freqb7..0, lsb first
	unsigned char W1;					//ad9850 control word, Freqb15..8, lsb first
	unsigned char W2;					//ad9850 control word, Freqb23..16, lsb first
	unsigned char W3;					//ad9850 control word, Freqb31..24, lsb first
	unsigned char W4;					//ad9850 control word, Control0, Control1, PowerDown, PhaseB0..PhaseB4
} AD9850_T;

//global variables
//AD9850_T ad9850;

//initialize the pins
void ad9850_init(void);

//send ad9850 byte - not directly called, lsb first
void ad9850_sendbyte(unsigned char dat);

//send ad9850 words - lsb first
void ad9850_sendwords(unsigned long words);

//shut down the chip
void ad9850_poweroff(void);

//power up the chip
void ad9850_poweron(unsigned long words);

//convert frequency / phase defaults to 0
void ad9850_freq(unsigned long freq);

//convert frequency to words
//calculate Freq * 2^BitCount / Divisor
//unsigned long ad9850_f2w(unsigned long freq);

#endif // AD9850_H_INCLUDED
