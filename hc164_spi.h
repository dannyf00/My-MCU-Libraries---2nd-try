#ifndef __HC164_SPI_H
#define __HC164_SPI_H

//hardware configuration
#define HC164_PORT			SPI_PORT
#define HC164_DDR			SPI_DDR
#define HC164_SCK			(SPI_SCK)
#define HC164_SDO			(SPI_MOSI)
//end hardware configuration

void hc164_init(void);

void hc164_write(unsigned char byte_t);

#endif //hc164_spi