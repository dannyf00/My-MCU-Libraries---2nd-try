#ifndef CD4021_H_INCLUDED
#define CD4021_H_INCLUDED

/*
 */

//hardware configuration
#define CD4021_PORT			PORTB
#define CD4021_PORT_IN		PINB
#define CD4021_DDR			DDRB
#define CD4021_SCK			(1<<0)
#define CD4021_LATCH		(1<<1)		//active high -> 1 to load parallel data and 0 to load serial data
#define CD4021_SDI			(1<<2)
//end hardware configuration

#define cd4021_load(latch)	{IO_SET(CD4021_PORT, latch); IO_CLR(CD4021_PORT, latch);}

void cd4021_init(void);

unsigned char cd4021_read(void);

#endif // CD4021_H_INCLUDED
