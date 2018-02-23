#include "fs714x.h"						//we use fs7140/7145

//hardware configuration
//end hardware configuration

//global defines
//modify if A1..0 is set

//global variables
static unsigned char fs714x_addr = FS714x_ADDR;	//writing to registers only

//select the device i2c address (to write to registers or eeprom)
void fs714x_select(unsigned char i2c_addr) {
	fs714x_addr = i2c_addr & 0xfe;		//addr's last bit must be 0
}

//read fs714x a register
unsigned char fs714x_read(unsigned char fs714x_reg){
	unsigned char tmp;

	//see figure 4 on page 10 of the datasheet
	i2c_start();						//send the start condition
	i2c_write(fs714x_addr | I2C_CMD_WRITE);	//send the device address
	i2c_write(fs714x_reg);					//starting address
	i2c_stop();							//send the stop condition - optional

	i2c_start();						//restart
	i2c_write(fs714x_addr | I2C_CMD_READ);	//read from the address
	tmp = i2c_read(I2C_NOACK);	//read the last bit, no ack
	i2c_stop();							//send the stop condition
	return tmp;
}

//write fs714x register
unsigned char fs714x_write(unsigned char fs714x_reg, unsigned char dat) {
	unsigned char tmp;					//tmp variable for ack

	i2c_start();						//send the start condition
	i2c_write(fs714x_addr | I2C_CMD_WRITE);	//send the device address
	i2c_write(fs714x_reg);					//starting address
	tmp = i2c_write(dat);				//write the data
	i2c_stop();							//send the stop condition - optional

	return tmp;							//return 0 if successful
}

//initialize fs714x
void fs714x_init(void) {
	i2c_start();						//send the start condition
	i2c_write(fs714x_addr | I2C_CMD_WRITE);	//send the device address
	i2c_write(0x00);					//start with register 0x00
	//register 0
	i2c_write(10);						//default reference divider = 10
	//register 1
	i2c_write(1<<5);					//set shut1 -> chip turned off
	//register 2
	i2c_write(0x00);					//post divider 2/3=0x00
	//register 3
	i2c_write(1);						//feedback divider = 1
	//register 4
	i2c_write((1<<7) |					//1=cmos, 0=pecl
			(0<<6) |						//0=VCO output, 1=post divider output
			0x00);							//feedback divider = 1
	//register 5
	i2c_write((1<<6) |					//loop cap. 0=185pf, 1=500pf
			(1<<5) | (1<<4) |			//loop resistor select. 00=400k, 01=133k, 10=30k, 11=12k
			(1<<1) | (1<<0) |			//charge pump current. 00=2.0ua, 01=4.5ua, 10=11ua, 11=22.5ua
			0x00);
	//register 6
	i2c_write((1<<5));					//set shut2 -> chip turned off
	//register 7
	i2c_write(0x00);					//write register 7
	i2c_stop();
}

//Fout = Fref * Nf / Fr / (Np1 * Np2 * Np3)

//set Nf - feedback divider (FBKDIV), 14 bits
void fs714x_setNf(unsigned short Nf) {
	unsigned char tmp;
	Nf = Nf & 0x3fff;				//Nf is 14bits
	tmp = fs714x_read(0x04);		//read register 0x04
	fs714x_write(0x03, Nf);		//send Nf's lowest 8 bits
	tmp = (tmp &~0x3f) | (Nf >> 8);	//send value to register 0x04
	fs714x_write(0x04, tmp);
}
//get Nf
unsigned short fs714x_getNf(unsigned short *Nf) {
	*Nf = fs714x_read(0x03);		//read register 0x03
	*Nf|= (fs714x_read(0x04) & 0x3f) << 8;	//read register 0x04, 14 bits
	return *Nf;
}

//set Nr - reference divider (REFDIV), 13 bits
void fs714x_setNr(unsigned short Nr) {
	unsigned char tmp;
	Nr = Nr & 0x1fff;				//Nr is 13 bits long
	tmp = fs714x_read(0x01);		//read register 0x01 -> highest 8 bits
	fs714x_write(0x00, Nr);			//send the lsb
	tmp = (tmp &~0x1f) | (Nr >> 8);	//form the msb
	fs714x_write(0x01, tmp);		//send the msb
}

//get Nr
unsigned short fs714x_getNr(unsigned short *Nr) {
	*Nr = fs714x_read(0x00);		//read the lsb
	*Nr|= (fs714x_read(0x01) & 0x1f) << 8;	//read the msb, 13 bits
	return *Nr;						//return the value
}

//set Np1..2
void fs714x_setNp(unsigned char Np1, unsigned char Np2, unsigned char Np3) {
	unsigned char tmp;
	Np1 = (Np1 > 11)?11:Np1;		//Np1/2 limited to 0b1011 = 11
	Np2 = (Np2 > 11)?11:Np2;
	fs714x_write(0x02, (Np2 << 4) | Np1);	//send register 2 = Np2..Np1;
	tmp = fs714x_read(0x01);		//read register 0x01
	tmp = (tmp & 0x3f) | ((Np3 & 0x03) << 6);	//form register 0x01
	fs714x_write(0x01, tmp);
}

//get Np1..2
void fs714x_getNp(unsigned char *Np1, unsigned char *Np2, unsigned char *Np3) {
	unsigned char tmp;

	tmp = fs714x_read(0x00);		//read register 0x00
	*Np1 = tmp & 0x0f;				//Np1 is the llowest 4 bits
	*Np2 = tmp >> 4;				//Np2 is the highest 4 bits
	tmp = fs714x_read(0x01);		//read register 0x01
	*Np3 = tmp >> 6;				//Np3 is the highest two bits
}

//turn off fs714x(set SHUT1 | SETUT2)
void fs714x_off(void) {
	unsigned char tmp;
	tmp = fs714x_read(0x01);			//read registoer 0x01 / SHUT1
	fs714x_write(0x01, tmp &~(1<<5));	//SHUT1 is bit 5 of register 1
	tmp = fs714x_read(0x06);			//read registoer 0x06 / SHUT2
	fs714x_write(0x06, tmp &~(1<<5));	//SHUT2 is bit 5 of register 6
}

//turn on fs714x(clear SHUT1 | SETUT2)
void fs714x_on(void) {
	unsigned char tmp;
	tmp = fs714x_read(0x01);			//read registoer 0x01 / SHUT1
	fs714x_write(0x01, tmp | (1<<5));	//SHUT1 is bit 5 of register 1
	tmp = fs714x_read(0x06);			//read registoer 0x06 / SHUT2
	fs714x_write(0x06, tmp | (1<<5));	//SHUT2 is bit 5 of register 6
}
