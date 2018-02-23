//hearder file for ds1804

//hardware configuration
#define DS1804_PORT		P2
#define DS1804_DDR		P2
//#define DS1804_CS		(1<<1)
#define DS1804_UD		(1<<2)
#define DS1804_INC		(1<<0)
//end hardware configuration

//select ds1804
#define ds1804_select(cs)	{ds1804_deselect(cs); IO_CLR(DS1804_PORT, cs);}

//deselect ds1804
#define ds1804_deselect(cs)	{IO_SET(DS1804_PORT, cs); IO_OUT(DS1804_DDR, cs);}

void ds1804_init(void);

void ds1804_inc(unsigned char steps);

void ds1804_dec(unsigned char steps);
