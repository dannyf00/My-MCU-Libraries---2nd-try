//header file for ad7628

//hardware configuration
#define AD7628_DATA_PORT		P2
#define AD7628_DATA_DDR		P2
#define AD7628_DATA				0xff

#define AD7628_CTRL_PORT		P3
#define AD7628_CTRL_DDR			P3
#define AD7628_CTRL_CS			(1<<0)
#define AD7628_CTRL_AB			(1<<2)
//optional pins
//#define AD7628_CTRL_WR			(1<<1)
//#define AD7628_CTRL_XFER		(1<<3)
//end hardware configuration


//initialize the module
void ad7628_init(void);

//send a byte to ad7628a
void ad7628a_write(unsigned char dat);

//send a byte to ad7628b
void ad7628b_write(unsigned char dat);
