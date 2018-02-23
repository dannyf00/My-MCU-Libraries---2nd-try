#define AD525X_ADDR					0x58			//AD525X's address = 0b01011xxxx

//commands not implemented
#define AD525X_ADDR_READ			0x01			//read bit
#define AD525X_ADDR_WRITE			0x00			//write bit
#define AD525X_RDAC0				0x00			//set dac0
#define AD525X_RDAC1				0x01			//set dac1
#define AD525X_RDAC2				0x02			//set dac2
#define AD525X_RDAC3				0x03			//set dac3
#define AD525X_EE_MEM0				0x20			//read/write rdac0 to eemem0
#define AD525X_EE_MEM1				0x21			//read/write rdac0 to eemem1
#define AD525X_EE_MEM2				0x22			//read/write rdac0 to eemem2
#define AD525X_EE_MEM3				0x23			//read/write rdac0 to eemem3
#define AD525X_EE_MEM4				0x24			//read/write data to eemem4
#define AD525X_EE_MEM5				0x25			//read/write data to eemem5
#define AD525X_EE_MEM6				0x26			//read/write data to eemem6
#define AD525X_EE_MEM7				0x27			//read/write data to eemem7
#define AD525X_EE_MEM8				0x28			//read/write data to eemem8
#define AD525X_EE_MEM9				0x29			//read/write data to eemem9
#define AD525X_EE_MEM10				0x2a			//read/write data to eemema
#define AD525X_EE_MEM11				0x2b			//read/write data to eememb
#define AD525X_EE_MEM12				0x2c			//read/write data to eememc
#define AD525X_EE_MEM13				0x2d			//read/write data to eememd
#define AD525X_EE_MEM14				0x2e			//read/write data to eememe
#define AD525X_EE_MEM15				0x2f			//read/write data to eememf

void ad525x_select(unsigned char addr);		//select AD525X

void ad525x_write(unsigned char cmd, unsigned char data_t);

unsigned char ad525x_read(unsigned char cmd);
