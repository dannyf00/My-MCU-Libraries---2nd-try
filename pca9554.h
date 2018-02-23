#ifndef PCA9554_H_INCLUDED
#define PCA9554_H_INCLUDED

//driver for pca9554/9554a devices
//only write / output is implemented

//hardware configuration
//end hardware configuration

#define PCA9554_ADDR	0x40			//i2c address for pca9554 -> 0b0100xxxx
#define PCA9554A_ADDR	0x70			//i2c address for pca9554 -> 0b0111xxxx

#define PCA9554_PIN		0x00	//input byte
#define PCA9554_POUT	0x01	//output byte
#define PCA9554_PINV	0x02	//port inversion
#define PCA9554_DDR		0x03	//port direction register. defaults to input

extern unsigned char _pca9554_i2c_addr/*=PCA9554_ADDR*/;	//default i2c_address

//write to addr
void pca9554_write(unsigned char addr, unsigned char dat);

//read from addr
unsigned char pca9554_read(unsigned char addr);

//for pca9554

//select pca9554
#define pca9554_select(addr)			_pca9554_i2c_addr = PCA9554_ADDR | (addr)

#define pca9554_deselect(addr)			//does nothing

#define pca9554_init()					//do nothing

//set port to output
#define pca9554_ddr(pins)				pca9554_write(PCA9554_DDR, pins)	//default to 1 (input). 0 -> output. 1-> input

//write to port
#define pca9554_port(dat)				pca9554_write(PCA9554_POUT, dat)

//read from addr
#define pca9554_pin(addr)				pca9554_read(addr)

//select pca9554a
#define pca9554a_select(addr)			_pca9554_i2c_addr = PCA9554A_ADDR | (addr)

#define pca9554a_deselect(addr)			//does nothing

//set port to output
#define pca9554a_ddr(pins)				pca9554_ddr(pins)	//default to 1 (input). 0 -> output. 1-> input

//write to port
#define pca9554a_port(dat)				pca9554_port(dat)

//read from addr
#define pca9554a_pin(addr)				pca9554_pin(addr)

#define pca9554a_init()					//do nothing
//general usage:
//	i2c_init();							//reset the i2c
//	pca9554_select(PCA9554_ADDR | PCA9554_0);	//select the device
//	pca9554_out(0x00);					//all pins as output: 0->output, 1->input (default)
//		pca9554_select(PCA9554_ADDR | PCA9554_0);	//select device
//		pca9554_port(i);				//write to output pins

//read from addr
unsigned char pca9554_read(unsigned char addr);

#endif // PCA9554_H_INCLUDED
