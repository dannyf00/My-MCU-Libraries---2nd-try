//software spi source code

#include <htc.H>
#include "gpio.h"
#include "spi_hw.h"

//#define SPI_WAIT()			do {while (!SSPIF) continue; SSPIF=0} while (0)
#define SPI_WAIT()			do {} while (!BF)

//spi sck idles low
//spi sdi/sdo transmitting on rising edge of sck
void spi_init(void) {						//initialize the spi interface
	SMP=1;									//input data sampled at the end of the output data. SMP=0 works as well
	CKP=0;									//sck idles low
	CKE=1;									//data sampled on the rising edge of sck, when ckp=0;
	SSPEN=1;								//enable spi
	SSPM3=0, SSPM2=0, SSPM1=1, SSPM0=0;		//sspm3..0=0b0010, Fosc/64
	IO_OUT(SPI_DDR, SPI_SCK | SPI_SDO);	//sck + sdo as output
	IO_IN(SPI_DDR, SPI_SDI);				//sdi as input - not needed as sdi is automatically controlled by the ssp
}

/* unused
void spi_write_bit(unsigned char bit_var) {		//write a bit to spi
	IO_CLR(SPI_PORT, SPI_SCK);				//clock low
	IO_OUT(SPI_DDR, SPI_SDO);				//sdo to output mode
	//IO_CLR(SPI_PORT, SPI_SDO);			//clear sdo
	if (bit_var)								//data bit is high
		IO_SET(SPI_PORT, SPI_SDO);			//set sdo
	else
		IO_CLR(SPI_PORT, SPI_SDO);			//clear sdo
	IO_SET(SPI_PORT, SPI_SCK);				//clock out the bit, on the falling edge
	spi_delay(1);							//delay a little, to produce 50% dc
	IO_CLR(SPI_PORT, SPI_SCK);				//set sck
}

unsigned char spi_read_bit(void) {			//read from spi
	unsigned char data = 0x00;				//output data

	//IO_SET(SPI_PORT, SPI_SCK);				//clock low
	IO_CLR(SPI_PORT, SPI_SCK);				//clock in the serial data
	IO_IN(SPI_DDR, SPI_SDI);				//sdi as input
	spi_delay(1);							//delay a little
	if (SPI_PORT & SPI_SDI)					//high bit on sdi
		data = 1;
	IO_SET(SPI_PORT, SPI_SCK);				//lower sck
	spi_delay(1);							//delay some
	return data;
}
*/

unsigned char spi_write(unsigned char tbyte) {		//write a byte to spi
	unsigned char data;
	SSPBUF=tbyte;							//load sspbuf and start sending the byte
	SPI_WAIT();								//wait for the send to complete
	//data=SSPBUF;							//dummy read, to clear sspbuf flag
	return SSPBUF;
}

unsigned char spi_read(void) {				//read from spi
	unsigned char data;
	//SPI_WAIT();
	SSPBUF=0x00;							//so to clock out the dummy
	SPI_WAIT();								//wait for the send to complete
	//while (!BF) continue;					//wait for the receive the continue
	//data=SSPBUF;							//read back the buffer
	return SSPBUF;	//data;							//return the buffer
	//alternatively, you can use the spi_write() routine, if you allow spi_write() to return the dummy read
}
