//header file for adc0808/0809
//please note that the output is lsb highest and msb lowest

//hardware configuration
#define ADC_PORT		P2
#define ADC_DDR			P2
#define ADC_ADD_A		(1<<0)	//address line a
#define ADC_ADD_B		(1<<1)	//address line b
#define ADC_ADD_C		(1<<2)	//address line c
#define ADC_ADD_LE		(1<<3)	//address latch enable: active on the rising edge
#define ADC_START		(1<<5)	//adc start: active on the rising edge
#define ADC_OE			(1<<4)	//adc output enable: 
#define ADC_EOC			(1<<6)	//adc end of conversion indicator (active high)
//end hardware configuration

#define ADC_CH_IN0		0x00	//adc ch0
#define ADC_CH_IN1		0x01	//adc ch1
#define ADC_CH_IN2		0x02	//adc ch2
#define ADC_CH_IN3		0x03	//adc ch3
#define ADC_CH_IN4		0x04	//adc ch4
#define ADC_CH_IN5		0x05	//adc ch5
#define ADC_CH_IN6		0x06	//adc ch6
#define ADC_CH_IN7		0x07	//adc ch7

#define ADC_OE_ENABLE	0x01	//output enable
#define ADC_OE_DISABLE	0x00	//output disable

//reset the adc
void adc_init(void);

void adc_ch(unsigned char ch);

//star the adc
void adc_start(void);

//enable the output
void adc_oe(unsigned char action);

//read the eoc
#define adc_eoc()		(!IO_GET(ADC_PORT, ADC_EOC))			//return eoc. high = conversion done
