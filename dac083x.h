//header file for dac08
//connection
//d0->p0, ..., d7->p7
//wr1/wr2/xfer -> gnd
//ile -> vcc

//hardware configuration
#define DAC_DATA_PORT		P2
#define DAC_DATA_DDR		P2
#define DAC_DATA_PINs		0xff			//all pins as output
#define DAC_CTRL_PORT		P3
#define DAC_CTRL_DDR		P3
//#define DAC_CTRL_CS			(1<<0)
//end hardware configuration

void dac_init(void);

#define dac_select(cs)		{dac_deselect(cs); IO_CLR(DAC_CTRL_PORT, cs);}
#define dac_deselect(cs)	{IO_SET(DAC_CTRL_PORT, cs); IO_OUT(DAC_CTRL_DDR, cs);}
#define dac_write(val)		{DAC_DATA_PORT = (val);}
