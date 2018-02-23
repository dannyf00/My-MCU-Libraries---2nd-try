#include <regx51.h>
#include "gpio.h"
//#include "spi_sw.h"							//we use software spi
#include "adc0831.h"						//we use adc0831

void adc0831_init(void) {
}

//transmission on sck's rising edge
void _spi_write(unsigned char data_t) {
	unsigned char mask = 0x80;				//start with the most signifcant bit

	//IO_CLR(SPI_PORT, SPI_SCK);			//default state of sck: low
	while (mask) {
		IO_CLR(ADC0831_PORT, ADC0831_SCK);			//clear spi_sck
		if (data_t & mask) IO_SET(ADC0831_PORT, ADC0831_MOSI);	//send the data
		else IO_CLR(ADC0831_PORT, ADC0831_MOSI);
		IO_SET(ADC0831_PORT, ADC0831_SCK);			//send on the rising edge
		SPI_DELAY(SPI_DLY);				//insert some delays to generate 50% dc
		mask = mask >> 1;					//next bit
	}
	//IO_CLR(SPI_PORT, SPI_MOSI);			//clear mosi
	IO_CLR(ADC0831_PORT, ADC0831_SCK);				//clear sck
}

//reading spi on the falling edge
unsigned char _spi_read(void) {
	unsigned char mask = 0x80;				//start with the most signifcant bit
	unsigned char data_t=0;					//tmp

	//IO_CLR(SPI_PORT, SPI_SCK);			//drive spi low
	while (mask) {
		//data_t = data_t << 1;				//msb first
		IO_SET(ADC0831_PORT, ADC0831_SCK);			//send on the rising edge

		//if (SPI_PORT_IN & SPI_MISO) data_t |= 0x01;
		if (ADC0831_PORT_IN & ADC0831_MISO) data_t |= mask;	//if miso is high, set the bit
		else data_t &=~mask;				//if miso is low, clear the bit

		IO_CLR(ADC0831_PORT, ADC0831_SCK);			//clear spi_sck
		SPI_DELAY(SPI_DLY);				//insert some delays to generate 50% dc

		mask = mask >> 1;					//next bit
	}
	IO_CLR(ADC0831_PORT, ADC0831_MOSI);				//clear mosi
	return data_t;							//return the buffer
}

unsigned char adc0831_read(void) {
	
	//send two pulses for tset-up
	
	//send the first sck pulse
	IO_SET(ADC0831_PORT, ADC0831_SCK);
	NOP(); NOP(); NOP(); NOP(); NOP();
	IO_CLR(ADC0831_PORT, ADC0831_SCK);

	NOP(); NOP(); NOP(); NOP(); NOP();
	
	//send the 2nd sck pulse
	IO_SET(ADC0831_PORT, ADC0831_SCK);
	NOP(); NOP(); NOP(); NOP(); NOP();
	IO_CLR(ADC0831_PORT, ADC0831_SCK);
	
	return _spi_read();						//perform the adc and return the results
}

