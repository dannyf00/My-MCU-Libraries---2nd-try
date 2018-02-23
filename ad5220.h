//header file for ad5220

//hardware cofniguration
#define AD5220_PORT				P2
#define AD5220_DDR				P2
#define AD5220_CLK				(1<<0)		//clock
#define AD5220_UD				(1<<2)		//up/down
//end hardware configuration

//select a chip
#define ad5220_select(cs)		{IO_SET(AD5220_PORT, cs); IO_OUT(AD5220_DDR, cs); IO_CLR(AD5220_PORT, cs);}

//deselect a chip
#define ad5220_deselect(cs)		{IO_SET(AD5220_PORT, cs); IO_OUT(AD5220_DDR, cs); /*IO_CLR(AD5220PPORT, cs);*/}

//clk falling edge
#define ad5220_strobe()			{IO_SET(AD5220_PORT, AD5220_CLK); /*NOP(); NOP();*/ IO_CLR(AD5220_PORT, AD5220_CLK);}

#define ad5220_up()				{IO_SET(AD5220_PORT, AD5220_UD); ad5220_strobe();}

#define ad5220_down()			{IO_CLR(AD5220_PORT, AD5220_UD); ad5220_strobe();}

void ad5220_init(void);
