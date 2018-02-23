#ifndef AD9832_H_INCLUDED
#define AD9832_H_INCLUDED

//hardware configuration
#define AD9832_PORT		LATB
#define AD9832_DDR		TRISB
#define AD9832_SCLK		(1<<0)			//ad9832 serial clock, idle high
#define AD9832_SDATA	(1<<1)			//ad9832 serial data input, on sclk's falling edge
#define AD9832_FSYNC	(1<<2)			//Fsync pin. active low

//other connections
//FSELECT, PSEL0 and PSEL1 are tied to DGND - they are software selected
//#define AD9832_FSELECT	(1<<6)			//ad9832 frequency select. unused and tied to DGND

//other connection
//D0/D1 -> GND
//D2 -> Vcc
//RST ->  GND

//end hardware configuration

//global defines
#define F_AD9832		25000000ul		//reference clock frequency
#define W_AD9832		32			//32-bit dds

#define AD9832_1Khz		1000ul			//1khz
#define AD9832_10Khz	(AD9832_1Khz * 10)
#define AD9832_100Khz	(AD9832_1Khz * 100)
#define AD9832_1Mhz		(AD9832_1Khz * 1000)

#define AD9832_DELAY()	NOP()			//waste some time

//stroke pins. pins idle low
//#define AD9832_STROKE(pins)				do {IO_SET(AD9832_PORT, pins); AD9832_DELAY(); IO_CLR(AD9832_PORT, pins);} while (0)

//ad9832 commands
#define AD9832_RESET	0xD000			//0b11010000 00000000. device resets to mid-scale
#define AD9832_SLEEP	0xe000			//0b11100000 00000000. device goes into sleep
#define AD9832_CLEAR	0xc800			//set SYNC / SELSRC to zero
#define AD9832_POWERON	0xC000			//bring the device out of reset (=power it on)
//commands
#define AD9832_FREQB	0x3000			//write to 8-bit frequency defer register - first write
#define AD9832_FREQW	0x2000			//write 16-bit frequency (present + defer) - 2nd write
#define AD9832_PHASEB	0x1000			//write to phase defer register - first write
#define AD9832_PHASEW	0x0000			//write 16-bit phase (present 8 bit + defer) - 2nd write

//sync and selsrc bits
#define AD9832_SYNC		0xa000			//set sync -> transfers are synchronized
#define AD9832_SELSRC	0x9000			//set selsrc -> use FSELECT bit to switch freqx/phasex

//select freq0/freq1
#define AD9832_FREQ0	0x5000			//select FREQ0 when SELSRC = 1;
#define AD9832_FREQ1	0x5800			//select FREQ1 when selsrc = 1;

//A3..0 - addressing registers
#define AD9832_F0LLSB	0x0000			//Frequency register 0, lowest 8 bits of LSB
#define AD9832_F0HLSB	0x0100			//frequency register 0, highest 8 bits of LSB
#define AD9832_F0LMSB	0x0200			//Frequency register 0, lowest 8 bits of MSB
#define AD9832_F0HMSB	0x0300			//frequency register 0, highest 8 bits of MSB
#define AD9832_F1LLSB	0x0400			//Frequency register 1, lowest 8 bits of LSB
#define AD9832_F1HLSB	0x0500			//frequency register 1, highest 8 bits of LSB
#define AD9832_F1LMSB	0x0600			//Frequency register 1, lowest 8 bits of MSB
#define AD9832_F1HMSB	0x0700			//frequency register 1, highest 8 bits of MSB

//global variables

//initialize the pins
void ad9832_init(void);

//send ad9832 a word (=two bytes), msb first
void ad9832_sendword(unsigned short dat);

//convert frequency / phase defaults to 0/1 alternately
void ad9832_freq(unsigned long freq);

//convert frequency to words
//calculate Freq * 2^BitCount / Divisor
//unsigned long ad9832_f2w(unsigned long freq);

#endif // AD9832_H_INCLUDED
