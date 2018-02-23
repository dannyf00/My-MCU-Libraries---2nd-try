//header file for ad56x1/5320
//power_down mode not implemented but provided

//hardware configuration
#define AD56x1_PORT		SPI_PORT
#define AD56x1_DDR		SPI_DDR
//end hardware configuration

#define ad56x1_select(sync)			{ad56x1_deselect(sync); IO_CLR(AD56x1_PORT, sync);}
#define ad56x1_deselect(sync)		{IO_SET(AD56x1_PORT, sync); IO_OUT(AD56x1_DDR, sync);}

//mode - bit 15/14
#define AD56x1_NORMAL				(0x00<<2)	//normal mode
#define AD56x1_PD1K					(0x10<<2)	//pull-down, 1k
#define AD56x1_PD100K				(0x20<<2)	//pull-down, 100k
#define AD56x1_PDFLOAT				(0x30<<2)	//pull-down, float/tristate

void ad56x1_init(void);

//for ad5621
//output a word to ad5621. bit 13 - 2 (12bit), left aligned
#define ad5621_select(sync)			{ad56x1_select(sync);}
#define ad5621_deselect(sync)		{ad56x1_deselect(sync);}
#define ad5621_init()				{ad56x1_init();}
#define ad5621_write(val)			{spi_write(((val) & 0x0fff) >> 6); spi_write(val<<2);}

//for ad5611
//output a word to ad5611. bit 13 - 4 (10bit), left aligned
#define ad5611_select(sync)			{ad56x1_select(sync);}
#define ad5611_deselect(sync)		{ad56x1_deselect(sync);}
#define ad5611_init()				{ad56x1_init();}
#define ad5611_write(val)			{spi_write(((val) & 0x03ff) >> 4); spi_write(val<<4);}

//for ad5601
//output a word to ad5601. bit 13 - 6 (8bit), left aligned
#define ad5601_select(sync)			{ad56x1_select(sync);}
#define ad5601_deselect(sync)		{ad56x1_deselect(sync);}
#define ad5601_init()				{ad56x1_init();}
#define ad5601_write(val)			{spi_write(((val) & 0x00ff) >> 2); spi_write(val<<6);}


