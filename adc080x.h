//harder file to drive adc080x chips

//hardware configuration
#define ADC_PORT			P2
#define ADC_DDR				P2
#define ADC_CS				(1<<0)			//cs line: 0 to select the device (idle high)
#define ADC_RD				(1<<1)			//read line: active low (0=rd, idle high)
#define ADC_WR				(1<<2)			//write line: active low (0=write, idle high)
#define ADC_INTR			(1<<3)			//intr line: 1 to indicate conversion end
#define adc_dly()			//{NOP8();}				//delay for intr to go high
//end hardware configuration

#define adc_select(cs)			{adc_deselect(cs); IO_CLR(ADC_PORT, cs);}
#define adc_deselect(cs)		{IO_SET(ADC_PORT, cs); IO_OUT(ADC_DDR, cs);}

//initialize the adc
void adc_init(void);

//wait for adc to finish
#define adc_eoc()		(IO_GET(ADC_PORT, ADC_INTR))	//wait till conversion to end (-> sars pulls high

//start adc
#define adc_start()		{IO_SET(ADC_PORT, ADC_WR | ADC_RD); IO_CLR(ADC_PORT, ADC_WR); IO_SET(ADC_PORT, ADC_WR | ADC_RD);adc_dly();}

//enabled the output
#define adc_oe()		{IO_SET(ADC_PORT, ADC_RD); IO_OUT(ADC_DDR, ADC_RD); IO_CLR(ADC_PORT, ADC_RD);}
