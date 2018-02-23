#include "l3gd20spi.h"								//we use spi interface for l3gd20

//hardware configuration
//end hardware configuration


//global defines

//global variable

//initialize l3gd20
void l3gd20_init(void) {
	//IO_SET(SPI_PORT, SPI_SCK | SPI_MOSI);			//sck idles high
	//IO_OUT(SPI_DDR, SPI_SCK | SPI_MOSI);			//sck / mosi as oupput
	
	//IO_IN(SPI_DDR, SPI_MISO);						//miso as input
	
	l3gd20_select(L3GD20CS);

	//set control registers
	spi_write(L3GD20_WRITE | L3GD20_INC | L3GD20_CTRL_REG1);
	//set register 1
	spi_write(
		0x00 |										//set data rate
		0x00 |										//set bandwidth
		0x08 |										//0x08: normal mode / sleep mode; 0x00: power down mode
		0x04 |										//0x04: enable Z axis
		0x02 |										//0x02: enable Y axis
		0x01 |										//0x01: enable X axis
		0x00);
	//set ctrl2
	spi_write(
		0x00 |										//high pass filter = normal
		0x00 |										//high pass filter cut-off frequency
		0x00);
	//set ctrl3
	spi_write(
		(0<<7) |									//0x00=disable int1, 0x80=enable int1
		(0<<6) |									//0x00=disable boot status, 0x40=enable boot status
		(0<<5) |									//0x00=interrupt active high, 0x20=active low
		(0<<4) |									//0x00=push-pull. 0x10=open drain
		(0<<3) |									//0=data ready on drdy/int2 disable
		(0<<2) |									//0=fifo watermark interrupt disable
		(0<<1) |									//0=fifo overrun interrupt disable
		(0<<0) |									//0=fifo empty interrupt disable
		0x00);
	//set ctrl4
	spi_write(
		(0<<7) |									//0=continous update
		(0<<6) |									//0=data lsb at lower address
		(01<<4) |									//00=250dps, 01=500dps, 10=1000dps, 11=2000dps
		(0<<0) |									//0=4wire spi; 1=3-wire spi
		0x00);
	//set ctrl5
	spi_write(
		(0<<7) |									//0=normal mode for memory reboot
		(0<<6) |									//0=disable fifo
		(1<<4) |									//0=disable high pass filter, 1=enable hpf
		(0<<2) |									//00=int1 selection bits
		(0<<0) |									//00=out selection bits
		0x00);
	
	l3gd20_deselect(L3GD20CS);
}

//read from l3gd20 accelerometer
L3GD20_T *l3gd20a_read(L3GD20_T *l3gd) {
	uint16_t tmp;
	
	l3gd20_select(L3GD20CS);

	spi_write(L3GD20_READ | L3GD20_INC | L3GD20_OUT_X_L);
	//read X
	tmp = spi_read();								//default to lsb on lower address
	tmp|= spi_read() << 8;
	l3gd->GYRO_X = tmp;
	
	//read Y
	tmp = spi_read();
	tmp|= spi_read() << 8;
	l3gd->GYRO_Y = tmp;
	
	//read Z
	tmp = spi_read();
	tmp|= spi_read() << 8;
	l3gd->GYRO_Z = tmp;
	
	l3gd20_deselect(L3GD20CS);
	return l3gd;
}

//read from l3gd20 temperature
L3GD20_T *l3gd20t_read(L3GD20_T *l3gd) {
	l3gd20_select(L3GD20CS);

	spi_write(L3GD20_READ | L3GD20_STAY | L3GD20_OUT_TEMP);
	l3gd->TEMP = spi_read();
	
	l3gd20_deselect(L3GD20CS);
	return l3gd;
}

//read l3gd20 accelerometer + status + temperature
L3GD20_T *l3gd20_read(L3GD20_T *l3gd) {
	uint16_t tmp;
	
	l3gd20_select(L3GD20CS);

	spi_write(L3GD20_READ | L3GD20_INC | L3GD20_OUT_TEMP);
	//read temp
	l3gd->TEMP = spi_read();
	
	//read status
	l3gd->STATUS = spi_read();
	
	//read X
	tmp = spi_read();
	tmp|= spi_read() << 8;
	l3gd->GYRO_X = tmp;
	
	//read Y
	tmp = spi_read();
	tmp|= spi_read() << 8;
	l3gd->GYRO_Y = tmp;
	
	//read Z
	tmp = spi_read();
	tmp|= spi_read() << 8;
	l3gd->GYRO_Z = tmp;
	
	l3gd20_deselect(L3GD20CS);
	return l3gd;
}
