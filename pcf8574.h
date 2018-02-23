#define PCF8575_I2C_ADDR		0x40		//pcf8574 address. 0x70 for pcf8574A

//#define pcf8574_select(a210x)				{_pcf8574_a210x=(a210x) & 0x0e;}
//#define pcf8574_deselect(a210x)				//dummy. for compatibility only

void pcf8574_init(void);

//select pcf8574
void pcf8574_select(unsigned char a210x);

//deselect pcf8574
void pcf8574_deselect(unsigned char a210x);

//read pcf8574
unsigned char pcf8574_read(void);

//write a word to pcf8574
void pcf8574_write(unsigned char byte_t);

//output a value on pcf8574
#define pcf8574_out(val)					{pcf8574_write(val);}

//read from pcf8574
#define pcf8574_get()						(pcf8574_read())

//set mask on pcf8574
#define pcf8574_set(val)					{pcf8574_out(pcf8574_get() | (val));}

//clear mask on pcf8574
#define pcf8574_clr(val)					{pcf8574_out(pcf8574_get() & (~(val)));}

//flip mask on pcf8574
#define pcf8574_flp(val)					{pcf8574_out(pcf8574_get() ^ (val));}

