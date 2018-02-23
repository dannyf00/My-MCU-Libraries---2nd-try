#define PCF8575_I2C_ADDR		0x40		//pcf8575 address

//#define pcf8575_select(a210x)				{_pcf8575_a210x=(a210x) & 0x0e;}
//#define pcf8575_deselect(a210x)				//dummy. for compatibility only

void pcf8575_init(void);

//select pcf8575
void pcf8575_select(unsigned char a210x);

//deselect pcf8575
void pcf8575_deselect(unsigned char a210x);

//read pcf8575
//p0=lsb, p1=msb
unsigned short pcf8575_read(void);

//write a word to pcf8575
void pcf8575_write(unsigned short word_t);

//output a value on pcf8575
#define pcf8575_out(val)					{pcf8575_write(val);}

//read from pcf8575
#define pcf8575_get()						(pcf8575_read())

//set mask on pcf8575
#define pcf8575_set(val)					{pcf8575_out(pcf8575_get() | (val));}

//clear mask on pcf8575
#define pcf8575_clr(val)					{pcf8575_out(pcf8575_get() & (~(val)));}

//flip mask on pcf8575
#define pcf8575_flp(val)					{pcf8575_out(pcf8575_get() ^ (val));}

//routines for manipulating just P0
//output a value on pcf8575's p0 (lsb)
#define pcf8575p0_out(val)					{pcf8575_write((pcf8575_read() & 0xff00) | ((val) & 0x00ff));}

//read from pcf8575's p0
#define pcf8575p0_get()						(pcf8575_read() & 0x00ff)

//set mask on pcf8575
#define pcf8575p0_set(val)					{pcf8575_out(pcf8575_get() | ((val) & 0x00ff));}

//clear mask on pcf8575
#define pcf8575p0_clr(val)					{pcf8575_out(pcf8575_get() & (~((val) & 0x00ff)));}

//flip mask on pcf8575
#define pcf8575p0_flp(val)					{pcf8575_out(pcf8575_get() ^ ((val) & 0x00ff));}

//routines for manipulating just P1
//output a value on pcf8575's p1 (msb)
#define pcf8575p1_out(val)					{pcf8575_write((pcf8575_read() & 0x00ff) | ((val) << 8));}

//read from pcf8575's p0
#define pcf8575p1_get()						(pcf8575_read() >> 8)

//set mask on pcf8575
#define pcf8575p1_set(val)					{pcf8575_out(pcf8575_get() | ((val) << 8));}

//clear mask on pcf8575
#define pcf8575p1_clr(val)					{pcf8575_out(pcf8575_get() & (~((val) << 8)));}

//flip mask on pcf8575
#define pcf8575p1_flp(val)					{pcf8575_out(pcf8575_get() ^ ((val) << 8));}

