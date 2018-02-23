#include "spi1_sw.h"						//we use software spi1

//initialize the spi module
void spi1_init(void) {
#if defined(SPI1_MISO)
	IO_IN(SPI1_DDR, SPI1_MISO);				//input pins
#endif

#if defined(SPI1_MOSI)
	IO_CLR(SPI1_PORT, SPI1_MOSI);			//clear output pins
	IO_OUT(SPI1_DDR, SPI1_MOSI);			//set pins as output
#endif

	IO_CLR(SPI1_PORT, SPI1_SCK);			//clear sck
	IO_OUT(SPI1_DDR, SPI1_SCK);				//sck as output
}

//transmission on sck's rising edge
void spi1_write(unsigned char data_t) {
	unsigned char mask = 0x80;				//start with the most signifcant bit

#if defined(SPI1_MOSI)
	IO_OUT(SPI1_DDR, SPI1_MOSI);			//mosi as output
#endif
	//IO_CLR(SPI1_PORT, SPI1_SCK);		//default state of sck: low
	while (mask) {
		IO_CLR(SPI1_PORT, SPI1_SCK);		//clear spi_sck

#if defined(SPI1_MOSI)
		if (data_t & mask) IO_SET(SPI1_PORT, SPI1_MOSI);	//send the data
		else IO_CLR(SPI1_PORT, SPI1_MOSI);
#endif
		IO_SET(SPI1_PORT, SPI1_SCK);		//send on the rising edge
		SPI1_DELAY(SPI1_DLY);				//insert some delays to generate 50% dc
		mask = mask >> 1;					//next bit
	}
	//IO_CLR(SPI1_PORT, SPI1_MOSI);		//clear mosi
	IO_CLR(SPI1_PORT, SPI1_SCK);			//clear sck
}

//reading spi on the falling edge
unsigned char spi1_read(void) {
	unsigned char mask = 0x80;				//start with the most signifcant bit
	unsigned char data_t=0;					//tmp

#if defined(SPI1_MISO)
	IO_IN(SPI1_DDR, SPI1_MISO);				//miso as input
#endif
	//IO_CLR(SPI1_PORT, SPI1_SCK);		//drive spi low
	while (mask) {
		//data_t = data_t << 1;				//msb first
		IO_SET(SPI1_PORT, SPI1_SCK);		//send on the rising edge

		//if (SPI1_PORT_IN & SPI1_MISO) data_t |= 0x01;
#if defined(SPI1_MISO)
		if (IO_GET(SPI1_PORT_IN, SPI1_MISO)) data_t |= mask;	//if miso is high, set the bit
		else data_t &=~mask;				//if miso is low, clear the bit
#endif
		IO_CLR(SPI1_PORT, SPI1_SCK);		//clear spi_sck
		SPI1_DELAY(SPI1_DLY);				//insert some delays to generate 50% dc

		mask = mask >> 1;					//next bit
	}
	//IO_CLR(SPI1_PORT, SPI1_MOSI);		//clear mosi
	return data_t;							//return the buffer
}

//writing data on sck's rising edge
//reading data on sck's falling edge
unsigned char spi1_write_read(unsigned char data_t) {
	unsigned char mask = 0x80;				//start with the most signifcant bit

	//IO_CLR(SPI1_PORT, SPI1_SCK);		//default state of sck: low
	while (mask) {
		//send the bit
		IO_CLR(SPI1_PORT, SPI1_SCK);		//clear spi_sck

#if defined(SPI1_MOSI)
		if (data_t & mask) IO_SET(SPI1_PORT, SPI1_MOSI);	//send the data
		else IO_CLR(SPI1_PORT, SPI1_MOSI);
#endif

		IO_SET(SPI1_PORT, SPI1_SCK);		//send on the rising edge

		//read the bit
		//SPI1_DELAY(SPI1_DLY);				//insert some delays to generate 50% dc
		//IO_CLR(SPI1_PORT, SPI1_SCK);	//clear spi_sck
#if defined(SPI1_MISO)
		if (IO_GET(SPI1_PORT_IN, SPI1_MISO)) data_t |= mask;	//if miso is high, set the bit
		else data_t &=~mask;				//if miso is low, clear the bit
#endif
		IO_CLR(SPI1_PORT, SPI1_SCK);		//clear spi_sck

		mask = mask >> 1;					//next bit
	}
	//IO_CLR(SPI1_PORT, SPI1_MOSI);		//clear mosi
	IO_CLR(SPI1_PORT, SPI1_SCK);			//clear sck

	return data_t;
}

