//header file for tlc1543

//hardware configuration
#define TLC1543_PORT		P2
#define TLC1543_PORT_IN		P2
#define TLC1543_DDR			P2
#define TLC1543_CLK			(1<<0)
#define TLC1543_CS			(1<<1)
#define TLC1543_ADDR		(1<<2)
#define TLC1543_MISO		(1<<3)
#define TLC1543_EOC			(1<<4)
//end hardware configuration

//channel definitions - addr
#define TLC1543_CH0			(0x00<<6)
#define TLC1543_CH1			(0x01<<6)
#define TLC1543_CH2			(0x02<<6)
#define TLC1543_CH3			(0x03<<6)
#define TLC1543_CH4			(0x04<<6)
#define TLC1543_CH5			(0x05<<6)
#define TLC1543_CH6			(0x06<<6)
#define TLC1543_CH7			(0x07<<6)
#define TLC1543_CH8			(0x08<<6)
#define TLC1543_CH9			(0x09<<6)
#define TLC1543_CHa			(0x0a<<6)

#define tlc1543_select(cs)		{tlc1543_deselect(cs); IO_CLR(TLC1543_PORT, cs);}
#define tlc1543_deselect(cs)	{IO_SET(TLC1543_PORT, cs); IO_OUT(TLC1543_DDR, cs);}
#define tlc1543_eoc()			(IO_GET(TLC1543_PORT, TLC1543_EOC))		//returns 1 if tlc1543 has finished its conversion

void tlc1543_init(void);

unsigned short tlc1543_write(unsigned short word_t);

unsigned short tlc1543_read(unsigned char cs, unsigned short ch);
