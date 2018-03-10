#include "spi0.h"									//we use spi0

//hardware configuration
#define F_SPI				10000					//spi bit rate
#define SPIx				SSI0					//SSI0..3
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

//reset the spi
void spi0_init(void) {
	int tmp;
	//enable clock to ssi
	SYSCTL->RCGCSSI |= (1<<0);						//0->SSI0, 1->SSI1, 2->SSI2, 3->SSI3
	while ((SYSCTL->PRSSI & (1<<0)) == 0) continue;	//1->ready, 0->not ready
	
	//gpio configuration
#if defined(SPI0_SCLK)
	SPI0_SCLK();
#endif
	
#if defined(SPI0_MOSI)
	SPI0_MOSI();
#endif
	
#if defined(SPI0_MISO)
	SPI0_MISO();
#endif

	//disable the module
	SPIx->CR1 &=~(1<<1);							//1->enable spi/ssi, 0->disable spi/ssi
	SPIx->CPSR = F_CPU / F_SPI / 256;				//=CPSDVR
	if (SPIx->CPSR == 0) SPIx->CPSR = 1;			//in case
	SPIx->CR0  =	(((1 + F_CPU / F_SPI / SPIx->CPSR) & 0xff) << 8) |		//set the baud rate
					(0<<7) |						//0->data captured on the first transition, 1->data captured on the 2nd transistion
					(0<<6) |						//0->steady state of low on SCLK, 1->steady state of high on SCLK
					(0<<4) |						//0->spi frame, 1->TI synchronous serial, 2->microwire, 3->reserved
					(7<<0) |						//0..2->reserved, 3->4bit, 4->5bit, 5->6bit, 7->8bit, ..., 15->16bit
					0x00;
	SPIx->CR1  = 	(0<<4) |						//0->TXRIS indicates fifo is half full or less, 1->TXRIS set at end of transmission
					(0<<3) |						//0->SSI can drive the SSITx output in slave mode, 1->SSI must not drive the SSITx output in slave mode
					(0<<2) |						//0->SSI as master, 1->SSI as slave
					(0<<1) |						//0->SSI disabled, 1->SSI enabled
					(1<<0) |						//0->loop back disabled, 1->loop back enabled
					0x00;
	
	SPIx->IM = 0;									//0->disable all interrupt
	SPIx->ICR= 0xff;								//0xff->clear all interrupts
	SPIx->CC = 0x00;								//0->spi driven by system clock, 5->spi driven by PIOSC
	
	//enable the module
	SPIx->CR1 |= (1<<1);							//1->enable spi/ssi, 0->disable spi/ssi
}

//send the spi
//need to check for device busy status / fifo
uint16_t spi0_write(uint16_t dat) {
	while (spi0_busy()) continue;					//wait for spi0 fifo to free up
	SPIx->DR = dat;									//load the data to be sent
	return SPIx->DR;
}

