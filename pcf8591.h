//header file for pcf8591

//hardware configuration
//#define PCF8591_0					0		//a210 of pcf8591_0
//end hardware configuration

#define PCF8591_I2C_ID				0x90	//i2c address for pcf8591
//bit 6 of the control byte
#define PCF8591_CTRL_ANOE			0x40	//1=analog output enable
//bit 5/4 of the control byte
#define PCF8591_CTRL_SE				0x00	//all channels are single ended
#define PCF8591_CTRL_3DI			0x10	//AIN0/1/2 differential to AIN3
#define PCF8591_CTRL_2SE2DI			0x20	//AIN0/1 single ended, and AIN2/3 differential
#define PCF8591_CTRL_2DI			0x30	//AIN0/1 differential, AIN2/3 differential
//bit 2 of the control byte
#define PCF8591_CTRL_INCR			0x04	//1=auto incrementing
//bit 1/0 of the control byte
#define PCF8591_CTRL_CH0			0x00	//select ch0
#define PCF8591_CTRL_CH1			0x01	//select ch1
#define PCF8591_CTRL_CH2			0x02	//select ch2
#define PCF8591_CTRL_CH3			0x03	//select ch3

//adc ch configuration
#define PCF8591_CH_AIN0				(PCF8591_CTRL_SE | PCF8591_CTRL_CH0)
#define PCF8591_CH_AIN1				(PCF8591_CTRL_SE | PCF8591_CTRL_CH1)
#define PCF8591_CH_AIN2				(PCF8591_CTRL_SE | PCF8591_CTRL_CH2)
#define PCF8591_CH_AIN3				(PCF8591_CTRL_SE | PCF8591_CTRL_CH3)
#define PCF8591_CH_AIN0_3			(PCF8591_CTRL_3DI | PCF8591_CTRL_CH0)	//ain0-ain3
#define PCF8591_CH_AIN1_3			(PCF8591_CTRL_3DI | PCF8591_CTRL_CH1)	//ain0-ain3
#define PCF8591_CH_AIN2_3			(PCF8591_CTRL_3DI | PCF8591_CTRL_CH2)	//ain0-ain3

extern unsigned char _pcf8591_addr;

#define PCF8591_CTRL_AIN_MASK		PCF8591_CTRL_AIN3

#define pcf8591_select(a210)		{_pcf8591_addr=PCF8591_I2C_ID | ((a210) & 0x0e);}
#define pcf8591_deselect(a210)		//nothing

//write to pcf8591
void pcf8591_write(unsigned char ch, unsigned char data_t);

//read from pcf8591
unsigned char pcf8591_read(unsigned char ch);

//do a/d conversion on a single channel
#define pcf8591_adc(ch)				pcf8591_read(ch)

//do a d/a conversion on a single channel
#define pcf8591_dac(byte_t)			{pcf8591_write(PCF8591_CTRL_ANOE, byte_t);}

//reset pcf8591
void pcf8591_init();

