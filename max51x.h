//header file for max517/8/9

#define MAX517_I2C_ID		0x58			//uses a1,a0
#define MAX518_I2C_ID		0x58
#define MAX519_I2C_ID		0x40			//uses a3, a2, a1, a0

#define MAX517_CMD_DAC0		0x00

#define MAX518_CMD_DAC0		0x00
#define MAX518_CMD_DAC1		0x01

#define MAX519_CMD_DAC0		0x00
#define MAX519_CMD_DAC1		0x01

//write to max51x
void max51x_write(unsigned char cmd, unsigned char val);

//reste max51x
void max51x_init(void);

//for max517
#define max517_init()			{max51x_init();}
void max517_select(unsigned char a3210);
#define max517_deselect(a3210) 				//deselect the chip
#define max517_write(cmd, val)	{max51x_write(cmd, val);}

//for max518
#define max518_init()			{max51x_init();}
void max518_select(unsigned char a3210);
#define max518_deselect(a3210) 				//deselect the chip
#define max518_write(cmd, val)	{max51x_write(cmd, val);}

//for max519
#define max519_init()			{max51x_init();}
void max519_select(unsigned char a3210);
#define max519_deselect(a3210) 				//deselect the chip
#define max519_write(cmd, val)	{max51x_write(cmd, val);}
