//header files for max5413/4/5 chips

//hardware configuration
#define MAX541X_PORT		P2
#define MAX541X_DDR			P2
#define MAX541X_CLK			(1<<0)
#define MAX541X_DIN			(1<<1)
#define MAX541X_CS			(1<<2)
//end hardware configuration

//reset the chip - does nothing
void max541x_init(void);
	//IO_SET(MAX541X_PORT, MAX541X_CS);		//cs idles high
	//IO_CLR(MAX541X_PORT, MAX541X_CLK | MAX541X_DIN);	//clk / din idles low
	//IO_OUT(MAX541X_DDR, MAX541X_CS | MAX541X_CLK | MAX541X_DIN);	//output pins

//send a byte to pot a
unsigned char max541xa_write(unsigned char position);

//send a byte to pot b
unsigned char max541xb_write(unsigned char position);
