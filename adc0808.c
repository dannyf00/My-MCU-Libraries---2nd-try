#include <regx51.h>
#include "gpio.h"
#include "adc0808.h"			//we use adc0808

//reset the adc
void adc_init(void) {
	IO_CLR(ADC_PORT, ADC_ADD_A | ADC_ADD_B | ADC_ADD_C | ADC_ADD_LE | ADC_START | ADC_OE);	//clear output pins
	IO_OUT(ADC_DDR, ADC_ADD_A | ADC_ADD_B | ADC_ADD_C | ADC_ADD_LE | ADC_START | ADC_OE);	//clear output pins

	IO_IN(ADC_DDR, ADC_EOC);
}

void adc_ch(unsigned char ch) {
	//set the add a/b/c pins
	switch (ch) {
		case ADC_CH_IN0: IO_CLR(ADC_PORT, ADC_ADD_C); IO_CLR(ADC_PORT, ADC_ADD_B); IO_CLR(ADC_PORT, ADC_ADD_A); break;
		case ADC_CH_IN1: IO_CLR(ADC_PORT, ADC_ADD_C); IO_CLR(ADC_PORT, ADC_ADD_B); IO_SET(ADC_PORT, ADC_ADD_A); break;
		case ADC_CH_IN2: IO_CLR(ADC_PORT, ADC_ADD_C); IO_SET(ADC_PORT, ADC_ADD_B); IO_CLR(ADC_PORT, ADC_ADD_A); break;
		case ADC_CH_IN3: IO_CLR(ADC_PORT, ADC_ADD_C); IO_SET(ADC_PORT, ADC_ADD_B); IO_SET(ADC_PORT, ADC_ADD_A); break;
		case ADC_CH_IN4: IO_SET(ADC_PORT, ADC_ADD_C); IO_CLR(ADC_PORT, ADC_ADD_B); IO_CLR(ADC_PORT, ADC_ADD_A); break;
		case ADC_CH_IN5: IO_CLR(ADC_PORT, ADC_ADD_C); IO_CLR(ADC_PORT, ADC_ADD_B); IO_SET(ADC_PORT, ADC_ADD_A); break;
		case ADC_CH_IN6: IO_CLR(ADC_PORT, ADC_ADD_C); IO_SET(ADC_PORT, ADC_ADD_B); IO_CLR(ADC_PORT, ADC_ADD_A); break;
		case ADC_CH_IN7: IO_CLR(ADC_PORT, ADC_ADD_C); IO_CLR(ADC_PORT, ADC_ADD_B); IO_SET(ADC_PORT, ADC_ADD_A); break;
	}

	//latch the addr pins: active on the rising edge
	IO_CLR(ADC_PORT, ADC_ADD_LE);
	IO_SET(ADC_PORT, ADC_ADD_LE);
	IO_CLR(ADC_PORT, ADC_ADD_LE);

}

//star the adc
void adc_start(void) {
	//create a rising edge on adc_start
	IO_CLR(ADC_PORT, ADC_START);
	IO_SET(ADC_PORT, ADC_START);
	IO_CLR(ADC_PORT, ADC_START);
}

//enable the output
void adc_oe(unsigned char action) {
	if (action == ADC_OE_ENABLE) IO_SET(ADC_PORT, ADC_OE);	//enable the output
	else IO_CLR(ADC_PORT, ADC_OE);							//otherwise disable the output
}

//read the eoc
//#define adc_eoc()		(IO_GET(ADC_PORT, ADC_EOC))			//return eoc. high = conversion done
