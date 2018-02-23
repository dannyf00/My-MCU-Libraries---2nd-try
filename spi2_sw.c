#include "spi2_sw.h"						//we use software spi1

//initialize the spi module
void spi2_init(void) {
#if defined(SPI2_MISO)
	IO_IN(SPI2_DDR, SPI2_MISO);				//input pins
#endif

#if defined(SPI2_MOSI)
	IO_CLR(SPI2_PORT, SPI2_MOSI);			//clear output pins
	IO_OUT(SPI2_DDR, SPI2_MOSI);			//set pins as output
#endif

	IO_CLR(SPI2_PORT, SPI2_SCK);			//clear sck
	IO_OUT(SPI2_DDR, SPI2_SCK);				//sck as output
}

//transmission on sck's rising edge
void spi2_write(unsigned char data_t) {
	unsigned char mask = 0x80;				//start with the most signifcant bit

#if defined(SPI2_MOSI)
	IO_OUT(SPI2_DDR, SPI2_MOSI);			//mosi as output
#endif
	//IO_CLR(SPI2_PORT, SPI2_SCK);		//default state of sck: low
	while (mask) {
		IO_CLR(SPI2_PORT, SPI2_SCK);		//clear spi_sck

#if defined(SPI2_MOSI)
		if (data_t & mask) IO_SET(SPI2_PORT, SPI2_MOSI);	//send the data
		else IO_CLR(SPI2_PORT, SPI2_MOSI);
#endif
		IO_SET(SPI2_PORT, SPI2_SCK);		//send on the rising edge
		SPI2_DELAY(SPI2_DLY);				//insert some delays to generate 50% dc
		mask = mask >> 1;					//next bit
	}
	//IO_CLR(SPI2_PORT, SPI2_MOSI);		//clear mosi
	IO_CLR(SPI2_PORT, SPI2_SCK);			//clear sck
}

//reading spi on the falling edge
unsigned char spi2_read(void) {
	unsigned char mask = 0x80;				//start with the most signifcant bit
	unsigned char data_t=0;					//tmp

#if defined(SPI2_MISO)
	IO_IN(SPI2_DDR, SPI2_MISO);				//miso as input
#endif
	//IO_CLR(SPI2_PORT, SPI2_SCK);		//drive spi low
	while (mask) {
		//data_t = data_t << 1;				//msb first
		IO_SET(SPI2_PORT, SPI2_SCK);		//send on the rising edge

		//if (SPI2_PORT_IN & SPI2_MISO) data_t |= 0x01;
#if defined(SPI2_MISO)
		if (IO_GET(SPI2_PORT_IN, SPI2_MISO)) data_t |= mask;	//if miso is high, set the bit
		else data_t &=~mask;				//if miso is low, clear the bit
#endif
		IO_CLR(SPI2_PORT, SPI2_SCK);		//clear spi_sck
		SPI2_DELAY(SPI2_DLY);				//insert some delays to generate 50% dc

		mask = mask >> 1;					//next bit
	}
	//IO_CLR(SPI2_PORT, SPI2_MOSI);		//clear mosi
	//IO_SET(SPI2_PORT, SPI2_SCK);			//sck idles high
	return data_t;							//return the buffer
}

//writing data on sck's rising edge
//reading data on sck's falling edge
unsigned char spi2_write_read(unsigned char data_t) {
	unsigned char mask = 0x80;				//start with the most signifcant bit

	//IO_CLR(SPI2_PORT, SPI2_SCK);		//default state of sck: low
	while (mask) {
		//send the bit
		IO_CLR(SPI2_PORT, SPI2_SCK);		//clear spi_sck

#if defined(SPI2_MOSI)
		if (data_t & mask) IO_SET(SPI2_PORT, SPI2_MOSI);	//send the data
		else IO_CLR(SPI2_PORT, SPI2_MOSI);
#endif

		IO_SET(SPI2_PORT, SPI2_SCK);		//send on the rising edge

		//read the bit
		//SPI2_DELAY(SPI2_DLY);				//insert some delays to generate 50% dc
		//IO_CLR(SPI2_PORT, SPI2_SCK);	//clear spi_sck
#if defined(SPI2_MISO)
		if (IO_GET(SPI2_PORT_IN, SPI2_MISO)) data_t |= mask;	//if miso is high, set the bit
		else data_t &=~mask;				//if miso is low, clear the bit
#endif
		IO_CLR(SPI2_PORT, SPI2_SCK);		//clear spi_sck

		mask = mask >> 1;					//next bit
	}
	//IO_CLR(SPI2_PORT, SPI2_MOSI);		//clear mosi
	IO_CLR(SPI2_PORT, SPI2_SCK);			//clear sck

	return data_t;
}

