#define AD524X_ADDR					0x58			//AD524X's address = 0b01011xxxx

#define AD524X_ADDR_READ			0x01			//read bit
#define AD524X_ADDR_WRITE			0x00			//write bit
#define AD524X_CMD_DAC1				0x00			//select dac1
#define AD524X_CMD_DAC0				0x80			//select dac2
#define AD524X_CMD_RS				0x40			//mid scale reset, active high
#define AD524X_CMD_NO_RS			0x00			//no mid scale reset
#define AD524X_CMD_SHUTDOWN			0x20			//shutdown
#define AD524X_CMD_O1				0x10			//output high on output latch O1
#define AD524X_CMD_O2				0x08			//ouptut high on output latch O2

void ad524x_select(unsigned char addr);		//select AD524X

void ad524x_write(unsigned char cmd, unsigned char data_t);

unsigned char ad524x_read(unsigned char cmd);

void AD524X_shutdown(void);
