#include "usii2c.h"							//we use usispi

//hardware configuration
//end hardware configuration

//global defines

//global variables

//reset the usi_i2c module
void i2c_init(void) {
	IO_SET(USII2C_PORT, USII2C_SCL); IO_OUT(USII2C_DDR, USII2C_SCL);	//scl idles high, as input
	IO_SET(USII2C_PORT, USII2C_SDA); IO_OUT(USII2C_DDR, USII2C_SDA);		//sda idles high, as input

	//clear status register
	//USISR = 0x00;

	//set up control registers for two wire operation / i2c
	USICR = (0<<USISIE) | 							//0=start condition interrupt disable
			(0<<USIOIE) | 							//0=no usi counter overflow interrupt,
			(1<<USIWM1) | (0<<USIWM0) |				//10=two wire mode / i2c
	        (1<<USICS1) | (0<<USICS0) | (1<<USICLK) |//000=no clock, 101=positive edge, 111=negative edge
	        (0<<USITC);								//don't send yet
	//USISR = (1<<USISIF)|(1<<USIOIF)|(1<<USIPF)|(1<<USIDC)|      // Clear flags,
    //        (0x0<<USICNT0);                                     // and reset counter.

}

//send data via i2c
uint8_t i2c_write(uint8_t dat) {
	uint8_t i;
	//prepare for transmission
	IO_CLR(USII2C_PORT, USII2C_SCL);			//pull scl low
	//IO_OUT(USII2C_DDR, USII2C_SDA);

	//start transmission
	IO_OUT(USII2C_DDR, USII2C_SDA);				//sda as output
	USIDR = dat;
	USICR |= 1<<USITC; usii2c_dly(0); USICR |= 1<<USITC; usii2c_dly(0);	//shift out 1 bit
	USICR |= 1<<USITC; usii2c_dly(0); USICR |= 1<<USITC; usii2c_dly(0);	//shift out 1 bit
	USICR |= 1<<USITC; usii2c_dly(0); USICR |= 1<<USITC; usii2c_dly(0);	//shift out 1 bit
	USICR |= 1<<USITC; usii2c_dly(0); USICR |= 1<<USITC; usii2c_dly(0);	//shift out 1 bit
	USICR |= 1<<USITC; usii2c_dly(0); USICR |= 1<<USITC; usii2c_dly(0);	//shift out 1 bit
	USICR |= 1<<USITC; usii2c_dly(0); USICR |= 1<<USITC; usii2c_dly(0);	//shift out 1 bit
	USICR |= 1<<USITC; usii2c_dly(0); USICR |= 1<<USITC; usii2c_dly(0);	//shift out 1 bit
	USICR |= 1<<USITC; usii2c_dly(0); USICR |= 1<<USITC; usii2c_dly(0);	//shift out 1 bit
	dat = USIDR;								//save usidr
	USIDR = 0xff;								//release sda
	//IO_OUT(USII2C_DDR, USII2C_SDA); usii2c_dly(0);				//realease sda

	//read ack/noack
	IO_IN(USII2C_DDR, USII2C_SDA); usii2c_dly(0);				//i2c as input
	USICR |= 1<<USITC; usii2c_dly(0); USICR |= 1<<USITC; usii2c_dly(0);	//shift out 1 bit
	i=0;
	while ((IO_GET(USII2C_PORT_IN, USII2C_SDA)&&(i<I2C_ACK_ERROR)))
		i++;								//wait for ack from the slave (ack = sda pulled to low by the slave
	IO_OUT(USII2C_DDR, USII2C_SDA);			//return sda to output
	if (i<I2C_ACK_ERROR) return I2C_ACK;	//no trouble
	else return I2C_NOACK;					//trouble! ack timed out
}

//read data via i2c
//not yet tested
uint8_t i2c_read(uint8_t ack) {
	uint8_t dat;

	//prepair the pins
	IO_IN(USII2C_DDR, USII2C_SDA);				//sda as input

	//start transmission
	USIDR = 0xff;
	USICR |= 1<<USITC; usii2c_dly(0); USICR |= 1<<USITC; usii2c_dly(0);	//shift out 1 bit
	USICR |= 1<<USITC; usii2c_dly(0); USICR |= 1<<USITC; usii2c_dly(0);	//shift out 1 bit
	USICR |= 1<<USITC; usii2c_dly(0); USICR |= 1<<USITC; usii2c_dly(0);	//shift out 1 bit
	USICR |= 1<<USITC; usii2c_dly(0); USICR |= 1<<USITC; usii2c_dly(0);	//shift out 1 bit
	USICR |= 1<<USITC; usii2c_dly(0); USICR |= 1<<USITC; usii2c_dly(0);	//shift out 1 bit
	USICR |= 1<<USITC; usii2c_dly(0); USICR |= 1<<USITC; usii2c_dly(0);	//shift out 1 bit
	USICR |= 1<<USITC; usii2c_dly(0); USICR |= 1<<USITC; usii2c_dly(0);	//shift out 1 bit
	USICR |= 1<<USITC; usii2c_dly(0); USICR |= 1<<USITC; usii2c_dly(0);	//shift out 1 bit
	dat = USIDR;								//save the data

	//send ack/noack
	if (ack==I2C_ACK) USIDR = 0x00;				//send ack
	else USIDR = 0xff;							//send no ack
	USICR |= 1<<USITC; usii2c_dly(0); USICR |= 1<<USITC; usii2c_dly(0);	//shift out just 1bit
	IO_OUT(USII2C_DDR, USII2C_SDA);				//return sda to output
	return dat;
}

//send a start condition
void i2c_start(void) {
	IO_SET(USII2C_PORT, USII2C_SCL | USII2C_SDA); usii2c_dly();	//set i2c high
	IO_CLR(USII2C_PORT, USII2C_SDA); usii2c_dly();	//clear sda
	IO_CLR(USII2C_PORT, USII2C_SCL); usii2c_dly();	//clear scl
	IO_SET(USII2C_PORT, USII2C_SDA); usii2c_dly();	//set sda

}

//send a stop condition
void i2c_stop(void) {
	IO_CLR(USII2C_PORT, USII2C_SDA); usii2c_dly();	//clear sda
	IO_SET(USII2C_PORT, USII2C_SCL); usii2c_dly();	//set i2c high
	IO_SET(USII2C_PORT, USII2C_SDA | USII2C_SCL); usii2c_dly();	//set sda
}

//send a restart = stop+start
void i2c_restart(void) {
	i2c_stop();
	i2c_start();
}
