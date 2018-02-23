//#include <p24fxxxx.h>					//we use pic24f
//#include "gpio.h"
#include "spi1_hw.h"						//we use hardware spi1

//hardware configuration
//end hardware configuration

#define _SPIxMD				_SPI1MD
#define _SPIxIF				_SPI1IF
#define _SPIxIE				_SPI1IE
#define SPIxBUF				SPI1BUF
#define SPIxCON1			SPI1CON1
#define SPIxCON2			SPI1CON2
#define SPIxSTAT			SPI1STAT
#define _SPIxTBF			SPI1STATbits.SPITBF
#define _SPIxRBF			SPI1STATbits.SPIRBF

//spistat
//#define SPISTAT_SPIEN		0x8000		//enable spi

//spicon1
//#define SPICON1_SCK_DISABLE	0x0100		//sck clock disabled, pin act like io
//#define SPICON1_SCK_ENABLE	0x0000		//sck clock enabled, pin act like sck

//#define SPICON1_SDO_DISABLE	0x0800		//sdo clock disabled. pin act like io
//#define SPICON1_SDO_ENABLE	0x0000		//sdo clock enabled. pin act like sck

//#define SPICON1_MODE8		0x0000		//8 bit mode
//#define SPICON1_MODE16		0x0400		//16 bit mode

//#define SPICON1_SMP_END		0x0200		//input data sampled at the end of the data output time
//#define SPICON1_SMP_MIDDLE	0x0000		//input data sampled in the middle

//#define SPICON1_CKE_A2I		0x0100		//data stroke out from active clock to idle clock
//#define SPICON1_CKE_I2A		0x0000		//data out from idle to active

//#define SPICON1_SSENABLE	0x0080		//ss pin used for slave select
//#define SPICON1_SSDISABLE	0x0000		//ss pin not used for slave select

//#define SPICON1_CKP_HIGH	0x0040		//clock idle high, active low
//#define SPICON1_CKP_LOW		0x0000		//clock idle low, active high

//#define SPICON1_MSTR_EN		0x0020		//master enabled
//#define SPICON1_MSTR_DIS	0x0000		//master disabled

//#define SPICON1_SPRE1		0x001c		//2ndary prescaler 1:1
//#define SPICON1_SPRE2		0x0018		//2ndary prescaler 2:1
//#define SPICON1_SPRE3		0x0014		//2ndary prescaler 3:1
//#define SPICON1_SPRE4		0x0010		//2ndary prescaler 4:1
//#define SPICON1_SPRE5		0x000c		//2ndary prescaler 5:1
//#define SPICON1_SPRE6		0x0008		//2ndary prescaler 6:1
//#define SPICON1_SPRE7		0x0004		//2ndary prescaler 7:1
//#define SPICON1_SPRE8		0x0000		//2ndary prescaler 8:1

//#define SPICON1_PPRE1		0x0003		//primary prescaler 1:1
//#define SPICON1_PPRE4		0x0002		//primary prescaler 4:1
//#define SPICON1_PPRE16		0x0001		//primary prescaler 16:1
//#define SPICON1_PPRE64		0x0000		//primary prescaler 64:1

//set prescalers
//F_SPI = (F_CPU / 2) / (SPICON1_PPRE * SPICON1_SPRE)
//#define SPICON1_PPRE		SPICON1_PPRE4
//#define SPICON1_SPRE		(((F_CPU / 2 / SPICON1_PPRE / F_SPI1) & 0x07) << 2)
//#define SPICON1_SPRE		SPICON1_SPRE8

//spicon2
//#define SPICON2_DEFAULT		0x0000		//default spicon2
//#define SPICON2_SPIBEN		0x0001		//1=enable enhanced mode. 0=disables enhanced mode

//spistat definitions
#define SPISTAT_SPITBF		0x0002		//spi transmission buffer flag. 1=buffer full. 0=buffer available
#define SPISTAT_SPIRBF		0x0001		//spi receive buffer flag. 1=data available to read
#define SPISTAT_SRMPT		0x0080		//srmpt bit mask

//initalize the spi module
void spi1_init(void) {
	_SPIxMD = 0;						//enable power to spi1
#ifdef SPI1_SCK
	SPI1_SCK();
#endif

#ifdef SPI1_MOSI
	SPI1_MOSI();
#endif

#ifdef SPI1_MISO
	SPI1_MISO();
#endif
	_SPIxIF = 0;
	_SPIxIE = 0;

	SPIxCON1 = 0x0000;					//set to default
	SPIxCON1 = 	(0<<12) |				//1=disable sck pin; 1=enable sck pin. SPICON1_SCK_ENABLE |	//enable sck p in
				(0<<11) |				//1=disable sdo/mosi pin; 1=enable sdo/mosi; SPICON1_SDO_ENABLE |	//enable sdo pin
				(0<<10) |				//1=16-bit mode; 0=8-bit mode; SPICON1_MODE8 |			//8 bit   mode
				(1<<9) |				//1=input sampled at end; 0=input sampled at middle; SPICON1_SMP_END |		//input sampling at the end
				(0<<8) |				//1=serial data change from active to idle; 0=serial data change from idle to active; SPICON1_CKE_I2A |		//data stroke out from idle to active
				(0<<7) |				//1=slave select managed by spi module; 0=slave select managed by port pins; SPICON1_SSDISABLE |		//slave select pin disabled
				(0<<6) |				//1=clock idles high; 0=clock idles low; SPICON1_CKP_LOW |		//sck idles low
				(1<<5) |				//1=enable master mode; 0=enable slave mode; SPICON1_MSTR_EN |		//master enabled
				(1<<4) | (1<<3) | (1<<2) | 	//111=2nd prescaler 1:1; ...; 000=2nd prescaler 8:1; SPICON1_SPRE |			//set secndary prescaler bits
				//be cautious using prescaler less than 4:1 (0b10) - read the errata
				(1<<1) | (0<<0)			//11=primary prescaler 1:1; ...; 00=64:1; SPICON1_PPRE			//set primary prescaler bits
				;
	//use enhanced mode
	SPIxCON2 = 0x0001;					//SPICON2_DEFAULT;// | SPICON2_SPIBEN;	//enable enhanced buffer mode
	SPIxSTAT |= 1<<15;					//SPISTAT_SPIEN;			//enable the spi
}

//write a byte over spi
/*
void spi_write(unsigned char dat) {
	_SPIBUF = dat;						//load up the spi buffer
	while (!_SPIIF) continue;			//watif or the transmission to end
	_SPIIF = 0;							//reset the flag
	//return _SPIBUF;
}
*/
//alternative
//#define spi_write(n)		spi_write_read(n)


unsigned char spi1_write_read(unsigned char dat) {
	while (_SPIxTBF) continue;			//wait for the buffer to free up - use RBF - see errata
	SPIxBUF = dat;						//load up the spi buffer with 0x00
	//while (!_SPIxIF) continue;			//watif or the transmission to end
	//_SPIxIF = 0;							//reset the flag
	return SPIxBUF;
}

unsigned char spi1_read(void) {
	//while (_SPIxRBF) continue;			//wait for data to arrive
	return SPIxBUF;						//read the buffer
}

