//header file for hc573

#ifndef HC573_H_INCLUDED
#define HC573_H_INCLUDED

//hardware configuration
#define HC573_PORT		LATB
#define HC573_DDR		TRISB
#define HC573s			0xff
//#define HC573_LATCH		(1<<9)
//end hardware configuration

//select / deselect hc573_deselect
#define hc573_select(latch) 	{IO_SET(HC573_PORT, latch); IO_OUT(HC573_DDR, latch);}
#define hc573_deselect(latch)	{IO_CLR(HC573_PORT, latch); IO_OUT(HC573_DDR, latch);}

//write a byte to hc573
#define hc573_write(dat)		HC573_PORT = (HC573_PORT & ~(HC573s)) | (dat)

//initialize hc573
void hc573_init(void);


#endif // HC573_H_INCLUDED
