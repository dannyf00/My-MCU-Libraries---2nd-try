#ifndef __HC595_H
#define __HC595_H

//hardware configuration
#define HC595_PORT		PORTD
#define HC595_DDR		DDRD
#define HC595_SCK		(1<<1)		//serial clock
#define HC595_MOSI		(1<<2)		//master out, slave in
#define HC595_RCK		(1<<4)		//rck to transfer data to output registers
//end hardware configuration

//latch the data into hc595
#define hc595_latch()	{IO_CLR(HC595_PORT, HC595_RCK); IO_SET(HC595_PORT, HC595_RCK); IO_CLR(HC595_PORT, HC595_RCK);}

//initialize hc595
void hc595_init(void);

//write to hc595
unsigned char hc595_write(unsigned char data_byte);

#endif //hc595_h
