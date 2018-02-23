#ifndef __ADC_H
#define __ADC_H

#include "gpio.h"                       //we use pic/f_cpu

//header file for utilizing adc on 12f675
//only implemented the first four channels on porta

//hardware configuration
//#define ADC_PORT			PORTA
//#define ADC_DDR				TRISA
//end hardware configuration

#define GODONE				GO_DONE

#if defined(_12F675)
#define ADC_v1                                          //adc for 12F675
//channel definitions for adcon0
#define ADC_0				0x00
#define ADC_1				0x04
#define ADC_2				0x08
#define ADC_3				0x0c
#define ADC_MASK			ADC_3		//adc channel mask

#elif defined(_16F684)
#define ADC_v2                                          //adc for 16F684
//channel definitions for 16F684
#define ADC_0				0x00
#define ADC_1				0x04
#define ADC_2				0x08
#define ADC_3				0x0c
#define ADC_4				0x10
#define ADC_5				0x14
#define ADC_6				0x18
#define ADC_7				0x1c
#define ADC_MASK			ADC_7		//adc channel mask

#elif defined(_16F886)
#define ADC_v3                                          //adc for 16F886
//channel definitions for 16F684
#define ADC_0				0x00
#define ADC_1				0x04
#define ADC_2				0x08
#define ADC_3				0x0c
#define ADC_4				0x10
#define ADC_5				0x14
#define ADC_6				0x18
#define ADC_7				0x1c
#define ADC_8				0x20
#define ADC_9				0x24
#define ADC_10			0x28
#define ADC_11			0x2c
#define ADC_12			0x30
#define ADC_13			0x34
#define ADC_VREF			0x38			//Vref
#define ADC_FREF			0x3c			//Fixed reference (600mv)
#define ADC_MASK			ADC_FREF		//adc channel mask

#elif   defined(_16F1933) || defined(_16F1934) || defined(_16F1935) || defined(_16F1936) || defined(_16F1937) || defined(_16F1938) || defined(_16F1939) || \
        defined(_16LF1933) || defined(_16LF1934) || defined(_16LF1935) || defined(_16LF1936) || defined(_16LF1937) || defined(_16LF1938) || defined(_16LF1939)
#define ADC_v4                                          //adc for 16F193x
//channel definitions for 16F684
#define ADC_0				0x00            //PORTA0
#define ADC_1				0x04            //PORTA1
#define ADC_2				0x08            //PORTA2
#define ADC_3				0x0c            //PORTA3
#define ADC_4				0x10            //PORTA5
#define ADC_5				0x14                    //PORTE0
#define ADC_6				0x18                    //PORTE1
#define ADC_7				0x1c                    //PORTE2
#define ADC_8				0x20                    //PORTB2
#define ADC_9				0x24                    //PORTB3
#define ADC_10			0x28                    //PORTB1
#define ADC_11			0x2c                    //PORTB4
#define ADC_12			0x30                    //PORTB0
#define ADC_13			0x34                    //PORTB5
#define ADC_TEMP			0x74			//temperature sensing
#define ADC_DAC 			0x78			//DAC / CVREF+
#define ADC_FVR                         0x7c			//Fixed reference (1.024/2.048/4.096v) or CVREF+
#define ADC_MASK			ADC_FVR                 //adc channel mask
#define GODONE                          GO_nDONE                //to provide backward compatability

#else
//missing channel definition information
  #warning adc.h - no channel definitions
#endif
//adc delay before channel switching
//need to adjust for your application
#define adc_delay()			{NOP64(); /*NOP(); NOP();NOP(); NOP(); NOP(); NOP();*/}

//initialize the adc
void adc_init(void);

//perform an adc
unsigned short adc_read(unsigned char ch);

#endif	//ADC_H
