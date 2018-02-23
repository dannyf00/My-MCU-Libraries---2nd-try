//max124041 header file
//max1240 has an internal ref of 2.5v (Vdd to 3.6v)
//max1241 requires an external vref (Vdd to 5.5v)

//hardware configuration
#define MAX1240_PORT			SPI_PORT
#define MAX1240_DDR				SPI_DDR
//end hardware configuration

//select the chip
#define max1240_select(cs)		{spi_select(cs);}

//deselect the chip
#define max1240_deselect(cs)	{spi_deselect(cs);}

//max1240 is ready / conversion ends if DOUT (MISO) is high
#define max1240_ready()			(MAX1240_PORT & SPI_MISO)

//reset max1240
void max1240_init(void);

//read max1240
unsigned short max1240_read(void);
