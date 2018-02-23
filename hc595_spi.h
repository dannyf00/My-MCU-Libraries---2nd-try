#ifndef __HC595_SPI_H
#define __HC595_SPI_H

//hardware configuration
#define HC595_PORT			PORTB
#define HC595_DDR			DDRB
#define HC595_RCK			(1<<4)		//rck on p.4

void hc595_init(void);
unsigned char hc595_write(unsigned char ch);

#endif //hc595_spi_h