//header file for ltc1660/1665

//dac channel selection
#define LTC166x_DAC_NOC		0x00	//no change
#define LTC166x_DACA		0x10	//dac a
#define LTC166x_DACB		0x20	//dac b
#define LTC166x_DACC		0x30	//dac c
#define LTC166x_DACD		0x40	//dac d
#define LTC166x_DACE		0x50	//dac e
#define LTC166x_DACF		0x60	//dac f
#define LTC166x_DACG		0x70	//dac g
#define LTC166x_DACH		0x80	//dac h
#define LTC166x_SLEEP		0xe0	//sleep
#define LTC166x_DACALL		0xf0	//dac a-h

#define ltc166x_select(cs)			{spi_select(cs);}
#define ltc166x_deselect(cs)		{spi_deselect(cs);}

//ltc1660
#define ltc1660_init()				{ltc166x_init();}
#define ltc1660_select(cs)			{ltc166x_select(cs);}
#define ltc1660_deselect(cs)		{ltc166x_deselect(cs);}
#define ltc1660_write(ch, val)		{spi_write(((ch) & LTC166x_DACALL) | (((val) & 0x00f0) >> 4)); spi_write((val) << 4);}

//ltc1665
#define ltc1665_init()				{ltc166x_init();}
#define ltc1665_select(cs)			{ltc166x_select(cs);}
#define ltc1665_deselect(cs)		{ltc166x_deselect(cs);}
#define ltc1665_write(ch, val)		{spi_write(((ch) & LTC166x_DACALL) | (((val) & 0x03f0) >> 6)); spi_write((val) << 2);}

void ltc166x_init(void);
