#ifndef SPI3_H
#define SPI3_H

#include "gpio.h"									//use gpio

//hardware configuration
//comment out if not used
#define SPI3_SCLK()			do {SYSCTL->RCGCGPIO |= (1<<0); GPIOA->DEN |= (1<<2); GPIOA->AFSEL |= (1<<2); GPIOA->PCTL = (GPIOA->PCTL &~(0x0f << (2*4))) | (0x02 << (2*4));} while (0)
#define SPI3_MISO()			do {SYSCTL->RCGCGPIO |= (1<<0); GPIOA->DEN |= (1<<4); GPIOA->AFSEL |= (1<<4); GPIOA->PCTL = (GPIOA->PCTL &~(0x0f << (4*4))) | (0x02 << (4*4));} while (0)
#define SPI3_MOSI()			do {SYSCTL->RCGCGPIO |= (1<<0); GPIOA->DEN |= (1<<5); GPIOA->AFSEL |= (1<<5); GPIOA->PCTL = (GPIOA->PCTL &~(0x0f << (5*4))) | (0x02 << (5*4));} while (0)
//end hardware configuration

//global defines
//pin configuration
//SPI0_SCLK=PA2(2)
//SPI0_MISO=PA4(2)
//SPI0_MOSI=PA5(2)

//SPI1_SCLK=PF2(2)/PD0(2)
//SPI1_MISO=PF0(2)/PD2(2)
//SPI1_MOSI=PF1(2)/PD3(2)

//SPI2_SCLK=PB4(2)
//SPI2_MISO=PB6(2)
//SPI2_MOSI=PB7(2)

//SPI3_SCLK=PD0(1)
//SPI3_MISO=PD2(1)
//SPI3_MOSI=PD3(1)

//read the spi
#define spi3_read()			(SSI3->DR)				//read the data back
#define spi3_busy()			(~SSI3->SR & (1<<1))		//(SSI0->SR & (1<<4))
#define spi3_available()	(SSI3->SR & (1<<2))


//reset the spi
void spi3_init(void);

//send the spi
//need to check for device busy status / fifo
uint16_t spi3_write(uint16_t dat);

#endif
