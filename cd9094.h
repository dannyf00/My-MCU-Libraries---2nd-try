//header file for cd9094

//hardware configuration
#define CD9094_PORT			P2
#define CD9094_DDR			P2
#define CD9094_SCK			(1<<1)			//the serial clock pin
#define CD9094_MOSI			(1<<0)			//the data pin

#define CD9094_OE			(1<<3)			//the en pin. active high.
#define CD9094_LATCH		(1<<2)			//the latch pin. 1 to receive data. 1->0 to latch data
//end hardware configuration

#define cd9094_select(en)	{cd9094_deselect(en); IO_SET(CD9094_PORT, en);}
#define cd9094_deselect(en)	{IO_CLR(CD9094_PORT, en); IO_OUT(CD9094_PORT, en);}

#define cd9094_oe(oe)		{IO_SET(CD9094_PORT, oe); IO_OUT(CD9094_DDR, oe);}
#define CD9094_od(oe)		{IO_CLR(CD9094_PORT, oe); IO_OUT(CD9094_DDR, oe);}

//initialize the pins
void cd9094_init(void);

//send a byte to cd9094
void cd9094_write(unsigned char dat);
