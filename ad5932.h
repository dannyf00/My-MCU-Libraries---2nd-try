#ifndef AD5932_H_INCLUDED
#define AD5932_H_INCLUDED

//hardware configuration
#define AD5932_PORT		LATB
#define AD5932_DDR		TRISB
#define AD5932_SCLK		(1<<0)			//ad5932 serial clock, idle high
#define AD5932_SDATA	(1<<1)			//ad5932 serial data input, on sclk's falling edge
#define AD5932_FSYNC	(1<<2)			//Fsync pin. active low
#define AD5932_CTRL		(1<<3)			//CTRL line. active low-to-high

#define AD5932_TINT		AD5932_TINT_OUT	//AD5932_TINT_OUT -> fixed number of output periods. AD5932_TINT_CLK -> fixed number of master clocks
#define AD5932_TINTMULT	AD5932_TINTx500	//output multiplier
#define AD5932_TINTCNT	0x02ff			//desired output cycles at each frequency

//default control words -> two write operations, dac enabled, automatic increment and syncout enabled
#define AD5932_DEFAULT	(AD5932_B24 | AD5932_DACEN | AD5932_INTINCR | AD5932_SYNCSEL | AD5932_SYNCOUTEN | AD5932_MASK)

#define F_AD5932		25000000ul		//reference clock frequency
#define W_AD5932		24				//bit-width. = 24 bits for ad5932

//other connections
//SYNCOUT is connected to CTRL via a resistor (1k-10k). Syncout is enabled to go up / down at the end of the sweep cycle. CTRL pin goes to input. This will keep the sweep going forever.

//other connection
//D0/D1 -> GND
//D2 -> Vcc
//RST ->  GND

//end hardware configuration

//global defines

#define AD5932_1Khz		1000ul			//1khz
#define AD5932_10Khz	(AD5932_1Khz * 10)
#define AD5932_100Khz	(AD5932_1Khz * 100)
#define AD5932_1Mhz		(AD5932_1Khz * 1000)

#define AD5932_DELAY()	NOP()			//waste some time

//stroke pins. pins idle low
//#define AD5932_STROKE(pins)				do {IO_SET(AD5932_PORT, pins); AD5932_DELAY(); IO_CLR(AD5932_PORT, pins);} while (0)

//ad5932 commands
#define AD5932_B24			0x0800		//set B24 -> Two write operations are required to load a complete word into the FSTART register and the ¦¤f register.
#define AD5932_DACEN		0x0400		//enable dac
#define AD5932_SINE			0x0200		//generate sine wave
#define AD5932_TRI			0x0000		//generate triangle wave
#define AD5932_MSBOUTEN		0x0100		//enable msb output
#define AD5932_INTINCR		0x0020		//automatic increment triggered by ctrl pin
#define AD5932_EXTINCR		0x0000		//manual increment trigger by ctrl pin
#define AD5932_SYNCSEL		0x0008		//syncout is high at end of the scan and then low at the subsequent scan
#define AD5932_SYNCOUTEN	0x0004		//enable syncout
#define AD5932_MASK			0x00d3		//D7, D6, D4, D1, D0 must be set, per datasheet

#define AD5932_FSTARTLSB	0xc000		//fstart's lsb
#define AD5932_FSTARTMSB	0xd000		//fstart's msb

#define AD5932_FDELTALSB	0x2000		//fdelta's lsb
#define AD5932_FDELTAMSB	0x3000		//fdelta's msb

#define AD5932_NINCR		0x1000		//Nincr

#define AD5932_TINT_OUT		0x4000		//fixed number of output periods
#define AD5932_TINT_CLK		0x6000		//fixed number of clock cycles
#define AD5932_TINTx1		0x0000		//multiply by 1
#define AD5932_TINTx5		0x0800		//multiply by 5
#define AD5932_TINTx100		0x1000		//multiply by 100
#define AD5932_TINTx500		0x1800		//multiply by 500

//start sweep -> ctrl goes through a 0->1 transistion by flipping its output direction register (CTRL bit set to input + high)
#define ad5932_sweep()		do {IO_SET(AD5932_PORT, AD5932_CTRL); IO_OUT(AD5932_DDR, AD5932_CTRL); AD5932_DELAY(); IO_IN(AD5932_DDR, AD5932_CTRL); } while (0)

//start a single frequency sweep -> single output
#define ad5932_single()		do {IO_SET(AD5932_PORT, AD5932_CTRL); IO_OUT(AD5932_DDR, AD5932_CTRL); AD5932_DELAY(); IO_CLR(AD5932_PORT, AD5932_CTRL); } while (0)

//global variables

//initialize the pins
void ad5932_init(void);

//send ad5932 a word (=two bytes), msb first
void ad5932_sendword(unsigned short dat);

//convert frequency / phase defaults to 0
//for sine freq sweep from fstart to fend, in fsteps
void ad5932_sinesweep(unsigned long fstart, unsigned long fend, unsigned long fsteps);

//convert frequency / phase defaults to 0
//for triangle freq sweep from fstart to fend, in fsteps,
void ad5932_trisweep(unsigned long fstart, unsigned long fend, unsigned long fsteps);

#endif // AD5932_H_INCLUDED
