#include <regx51.h>
#include "gpio.h"
#include "delay.h"
#include "adc080x.h"						//we use adc080x

//initialize the adc
void adc_init(void) {
	IO_SET(ADC_PORT, ADC_CS | ADC_WR);		//set wr/cs - pins idle high
	IO_CLR(ADC_PORT, ADC_RD);				//clear rd - > output enabled
	IO_OUT(ADC_DDR, ADC_RD | ADC_CS | ADC_WR);		//rd/wr/cs as output

	IO_IN(ADC_DDR, ADC_INTR);					//intr as input
}
