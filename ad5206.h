//header file for ad5206

//hardware cofniguration
#define AD5206_PORT				P2
#define AD5206_DDR				P2
#define AD5206_CLK				(1<<0)
#define AD5206_SDO				(1<<1)
//CS pin define by user code
//end hardware configuration

#define AD5206_RDAC1			0x00		//rdac1
#define AD5206_RDAC2			0x01		//rdac2
#define AD5206_RDAC3			0x02		//rdac3
#define AD5206_RDAC4			0x03		//rdac4
#define AD5206_RDAC5			0x04		//rdac5
#define AD5206_RDAC6			0x05		//rdac6

//select a device
#define ad5206_select(cs)		{IO_SET(AD5206_PORT, cs); IO_OUT(AD5206_DDR, cs); IO_CLR(AD5206_PORT, cs);}

//unselect a device
#define ad5206_deselect(cs)		{IO_SET(AD5206_PORT, cs); IO_OUT(AD5206_DDR, cs); /*IO_CLR(AD5206_PORT, cs);*/}

//reset the device
void ad5206_init(void);

//send a byte
unsigned char ad5206_write(unsigned char a210, unsigned char dat);
