//code shamelessly stolen from Maxim-ic's application 126
//ds1822 picc code. 
//v0.1	only one slave attached to the master

// hardware configuration
#define OW_PORT				P2						//OW Port
#define OW_DIR				P2						//port direction control
// end hardware configuration

//#define OW_SET(bits)		IO_SET(OW_PORT, bits)		//set OW bits
#define OW_CLR(bits)		IO_CLR(OW_PORT, bits)		//set OW bits
//#define OW_FLP(bits)		IO_FLP(OW_PORT, bits)		//set OW bits
#define OW_HIZ(bits)		OW_IN(bits)
#define OW_LOW(bits)		{OW_CLR(bits); OW_OUT(bits);}	//pull bits low
#define OW_HIGH(bits)		{OW_HIZ(bits);}			//allow bits to float high

#define OW_OUT(bits)		IO_OUT(OW_DIR, bits)		//set bits output
#define OW_IN(bits)			IO_IN(OW_DIR, bits)		//set bits input/hiz, allowing it to flat high
//#define OW_STROBE(pin)		OW_SET(pin); OW_CLR(pin)	//strobe ow

//#define OW_RESOLUTION_12BIT	0.0625f					//12bit temperature conversion factor
//#define OW_Tconv			800					//12-bit conversion time, in ms. May need to be more than 750 for pro compilers
//#define delay_2				NOP();NOP()				//delay 2us, at 4Mhz fosc
//#define delay_4				delay_2;delay_2
//#define delay_8				delay_4;delay_4
//#define delay_16			delay_8;delay_8
//#define delay_32			delay_16;delay_16
//#define delay_64			delay_32;delay_32
//#define delay_128			delay_64;delay_64
//#define delay_256			delay_128;delay_128

//delay routines, at 4Mhz. will need tweeking
//#define delay_0u()			NOP()
//#define delay_6u()			delay_4; delay_2			//delay 6us
//#define delay_9u()			delay_8;NOP()				//delay 9us
//#define delay_10u()			delay_8;delay_2				//delay 10us

//user defined 1us and 15us delay routines
//for 16F684
//delay_us(x) ~= 9+9*x, in us and running at 4Mhz
/*
#define delay_1u()			{NOP();}					//delay 1u
#define delay_15u()			{delay_us(0); NOP(); NOP(); NOP(); NOP(); NOP();}		//delay 15u
*/

//for 12F675
//delay_us(x) ~= 11+11*x, in us and running at 4Mhz
//#define delay_1u()			{NOP();}					//delay 1u
//#define delay_15u()			{delay_us(0); NOP(); NOP(); NOP(); NOP();}		//delay 15u

//for lpc2106
//#define delay_1u()			delay_us(0)
//#define delay_15u()			delay_us(15)

//for 89c51@1Mhz
#define delay_1u()				{NOP();}						//delay 1u
#define delay_15u()				{delay(0); NOP(); NOP(); NOP();}	//delay 15u

//delay routiens built on 1us / 15us delays
#define delay_30u()				{delay_15u(); delay_15u();}		//delay 30u
#define delay_60u()				{delay_30u(); delay_30u();}		//delay 60u
#define delay_120u()			{delay_60u(); delay_60u();}		//delay 120u
#define delay_240u()			{delay_120u(); delay_120u();}		//delay 240u
#define delay_420u()			{delay_240u(); delay_120u(); delay_60u();}		//delay 420u
#define delay_480u()			{delay_240u(); delay_240u();}		//delay 480u

//one-wire functions
unsigned char ow_init(unsigned int ow_pin);						//reset 1-wire
//void ow_writebit(unsigned int ow_pin, unsigned char tbit);				//write a right most bit from 1-wire
//unsigned char ow_readbit(unsigned int ow_pin);						//read a bit from 1-wire
void ow_write(unsigned int ow_pin, unsigned char data_t);				//write a byte to 1-wire
unsigned char ow_read(unsigned int ow_pin);						//read a byte from 1-wire
unsigned char ow_touchbyte(unsigned int ow_pin, unsigned char data_t);
void ow_writeblock(unsigned int ow_pin, unsigned char *data_t, unsigned short data_len);

