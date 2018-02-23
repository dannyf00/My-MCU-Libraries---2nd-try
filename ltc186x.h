//hardware configuration
#define SPI_CONV			(1<<6)					//spi cs/conv pin
//end hardware configuration

#define LTC186x_VREF		5000ul					//LTC186x Vref, in mv
#define LTC186x_TCONV()		{NOP(); NOP(); NOP(); NOP();}	//


unsigned short ltc186x_read(void);					//read ltc186x

unsigned short ltc186x_read_mv(void);				//return the adc reading, in mv
