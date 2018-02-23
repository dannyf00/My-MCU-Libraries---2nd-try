//header file for tl548/549

//hardware configuration
#define TLC548_CS			(1<<1)
//end hardware configuration

#define tlc548_select(cs)	{tlc548_deselect(cs); IO_CLR(SPI_PORT, cs);}
#define tlc548_deselect(cs)	{IO_SET(SPI_PORT, cs); IO_OUT(SPI_DDR, cs);}
#define tlc548_delay5()		{NOP(); NOP(); NOP(); NOP(); NOP();}
#define tlc548_delay()		{tlc548_delay5(); tlc548_delay5(); tlc548_delay5(); NOP(); NOP(); }	//generate at least 17us of delay
#define tlc548_read()		(spi_read())

void tlc548_init(void);
