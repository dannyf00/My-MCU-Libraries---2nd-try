//hearder file for ad0831
//using non-standard spi protocol

//hardware configuration
#define ADC0831_PORT			P2
#define ADC0831_PORT_IN			P2
#define ADC0831_DDR				P2
//#define SPI_CS				(1<<0)
#define ADC0831_SCK				(1<<1)					//serial clock
#define ADC0831_MOSI			(1<<3)					//mask out slave in
#define ADC0831_MISO			(1<<2)					//master in slave out
//end hardware configuration

#define SPI_DLY				0
#define SPI_DELAY(n)		{/*NOP(); delay(n);*/}	//some delay
#define _SPI_SELECT(cs)		{IO_CLR(ADC0831_PORT, cs); IO_OUT(ADC0831_DDR, cs);}	//select the chip
#define _SPI_DESELECT(cs)	{IO_SET(ADC0831_PORT, cs); IO_OUT(ADC0831_DDR, cs);}	//deselect the chip
#define _spi_select(cs)		_SPI_SELECT(cs)			//select the spi attached to cs pin
#define _spi_deselect(cs)	_SPI_DESELECT(cs)		//deselect the spi attached to cs pin

//select adc0831
#define adc0831_select(cs)		{_spi_select(cs);}

//deselect adc0831
#define adc0831_deselect(cs)	{_spi_deselect(cs);}

void adc0831_init(void);

//transmission on sck's rising edge
void _spi_write(unsigned char data_t);

//reading spi on the falling edge
unsigned char _spi_read(void);

unsigned char adc0831_read(void);
