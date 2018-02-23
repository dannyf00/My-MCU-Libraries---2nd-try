//demo code for using ad5241/2
//#include <regx51.h>

//hardware configuration
#define I2C_AD524X_A10_0			0x00					//ad524x
//end hardware configuration

#define I2C_AD524X_A10_MASK			0x06					//a1..0 mask
#define I2C_AD524X_ID				0x58					//0b0101 1xxx
#define I2C_AD524X_CMD_READ			0x01					//ad524x read command
#define I2C_AD524X_CMD_WRITE		0x00					//ad524x write command
#define I2C_AD524X_INSTR_MASK		0xf8					//instr mask = 0b1111 1000
#define I2C_AD524X_INSTR_RDAC1		0x00					//select rdac1
#define I2C_AD524X_INSTR_RDAC2		0x80					//select rdac2
#define I2C_AD524X_INSTR_RS			0x40					//midscale reset, active high
#define I2C_AD524X_INSTR_SD			0x20					//shutdown, active high
#define I2C_AD524X_INSTR_O1			0x10					//output logic pin latch for O1
#define I2C_AD524X_INSTR_O2			0x08					//output logic pin latch for O2

void ad524x_cs_set(unsigned char a10);

unsigned char ad524x_cs_get(void);

void ad524x_write(unsigned char instr, unsigned char val);

void ad524x_shutdown(void);									//shutdown the pot

void ad524x_reset(void);									//reset the chip
