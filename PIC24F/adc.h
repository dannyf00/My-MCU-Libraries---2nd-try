#ifndef ADC_H_
#define ADC_H_

//#include <p24fxxxx.h>						//we use pic24f
#include "gpio.h"
//#include "delay.h"						//delay some time

//pic24f adc header file
//hardware configuration
#define Vref					3300ul	//Vref, in mv
//end hardware configuration

//convert 10bit adc to mv
#define ADC2MV(adc)			((adc*Vref) >> 10)	//convert adc to mv

//ad1con1
#define ADC_ADON				0x8000	//turn on the adc
#define ADC_ADOFF				0x0000	//turn off the adc

//asidl bit
#define ADC_ADSIDL_DISCONT		(1<13)	//discontinue adc in idle
#define ADC_ADSIDL_CONT			(0<<13)	//continue adc in idle

//adc results
//form1..0 bits
#define ADC_FORM_SFRAC			0x0300	//signed factional (sddd dddd dd00 0000)
#define ADC_FORM_FRAC			0x0200	//factional (dddd dddd dd00 0000)
#define ADC_FORM_SINT			0x0100	//signed integer (ssss sssd dddd dddd)
#define ADC_FORM_INT			0x0000	//(unsigned) integer (0000 00dd dddd dddd)

//sample / conversion sequence - AD1CON1
#define ADC_SSRC_AUTO			0x00e0	//auto conversion
#define ADC_SSRC_TMR3			0x0040	//triggered by tmr3
#define ADC_SSRC_INTO			0x0020	//active transistion on int0
#define ADC_SSRC_SAMP			0x0000	//by setting SAMP bit

//adc saamp
#define ADC_ASAM_AUTO			0x0004	//sampling begin after the last conversion - samp auto set
#define ADC_ASAM_SAMP			0x0000	//sampling begin after samp is set

//ad1con2
//voltage reference
#define ADC_VCFG_AVDD_AVSS		0x0000	//AVdd-AVss
#define ADC_VCFG_VREF_AVSS		0x2000	//Vref+-AVss
#define ADC_VCFG_AVDD_VREF		0x4000	//AVdd-Vref-
#define ADC_VCFG_VREF_VREF		0x6000	//Vref+-Vref-
#define ADC_VCFG_AVDD_AVSS2		0x8000	//AVdd-AVss

//cscna - scan input
#define ADC_CSCNA_NOSCAN		0x0000	//do not scan input
#define ADC_CSCNA_SCAN			0x0400	//scan input

//buffer configuration
#define ADC_BUFM_8x2			0x0002	//buffer configured as two bytes
#define ADC_BUFM_16x1			0x0000	//buffer configured as 1 word

//ad1con3
//adc clock source
#define ADC_ADRC_INTERNAL		0x8000	//internal adc rc clock
#define ADC_ADRC_SYSTEM			0x0000	//use system clock

//adc auto sample time bits
#define ADC_SAMC_1TAD			0x0000	//sample time = 1 tcy - not recommended
#define ADC_SAMC_2TAD			0x0100	//sample time = 2 tcy
#define ADC_SAMC_3TAD			0x0200	//sample time = 3 tcy
#define ADC_SAMC_4TAD			0x0300	//sample time = 4 tcy
#define ADC_SAMC_5TAD			0x0400	//sample time = 5 tcy
#define ADC_SAMC_6TAD			0x0500	//sample time = 6 tcy
#define ADC_SAMC_7TAD			0x0600	//sample time = 7 tcy
#define ADC_SAMC_8TAD			0x0700	//sample time = 8 tcy
#define ADC_SAMC_9TAD			0x0800	//sample time = 9 tcy
#define ADC_SAMC_10TAD			0x0900	//sample time = 10 tcy
#define ADC_SAMC_11TAD			0x0a00	//sample time = 11tcy
#define ADC_SAMC_12TAD			0x0b00	//sample time = 12tcy
#define ADC_SAMC_13TAD			0x0c00	//sample time = 13tcy
#define ADC_SAMC_14TAD			0x0d00	//sample time = 14tcy
#define ADC_SAMC_15TAD			0x0e00	//sample time = 15tcy
#define ADC_SAMC_16TAD			0x0f00	//sample time = 16 tcy
#define ADC_SAMC_17TAD			0x1000	//sample time = 17 tcy
#define ADC_SAMC_18TAD			0x1100	//sample time = 18tcy
#define ADC_SAMC_19TAD			0x1200	//sample time = 19tcy
#define ADC_SAMC_20TAD			0x1300	//sample time = 20tcy
#define ADC_SAMC_21TAD			0x1400	//sample time = 21tcy
#define ADC_SAMC_22TAD			0x1500	//sample time = 22tcy
#define ADC_SAMC_23TAD			0x1600	//sample time = 23tcy
#define ADC_SAMC_24TAD			0x1700	//sample time = 24tcy
#define ADC_SAMC_25TAD			0x1800	//sample time = 25tcy
#define ADC_SAMC_26TAD			0x1900	//sample time = 26 tcy
#define ADC_SAMC_27TAD			0x1a00	//sample time = 27tcy
#define ADC_SAMC_28TAD			0x1b00	//sample time = 28tcy
#define ADC_SAMC_29TAD			0x1c00	//sample time = 29tcy
#define ADC_SAMC_30TAD			0x1d00	//sample time = 30tcy
#define ADC_SAMC_31TAD			0x1e00	//sample time = 31 tcy
#define ADC_SAMC_32TAD			0x1f00	//sample time = 32 tcy

//adc clock selecton bits
#define ADC_ADCS_1TCY			0x0000	//adc clock selection - 1tcy
#define ADC_ADCS_2TCY			0x0001	//adc clock selection - 2tcy
#define ADC_ADCS_3TCY			0x0002	//adc clock selection - 1tcy
#define ADC_ADCS_4TCY			0x0003	//adc clock selection - 1tcy
#define ADC_ADCS_5TCY			0x0004	//adc clock selection - 1tcy
#define ADC_ADCS_6TCY			0x0005	//adc clock selection - 1tcy
#define ADC_ADCS_7TCY			0x0006	//adc clock selection - 1tcy
#define ADC_ADCS_8TCY			0x0007	//adc clock selection - 1tcy
#define ADC_ADCS_9TCY			0x0008	//adc clock selection - 1tcy
#define ADC_ADCS_10TCY			0x0009	//adc clock selection - 1tcy
#define ADC_ADCS_11TCY			0x000a	//adc clock selection - 1tcy
#define ADC_ADCS_12TCY			0x000b	//adc clock selection - 1tcy
#define ADC_ADCS_13TCY			0x000c	//adc clock selection - 1tcy
#define ADC_ADCS_14TCY			0x000d	//adc clock selection - 1tcy
#define ADC_ADCS_15TCY			0x000e	//adc clock selection - 1tcy
#define ADC_ADCS_16TCY			0x000f	//adc clock selection - 1tcy
#define ADC_ADCS_17TCY			0x0010	//adc clock selection - 1tcy
#define ADC_ADCS_18TCY			0x0011	//adc clock selection - 2tcy
#define ADC_ADCS_19TCY			0x0012	//adc clock selection - 1tcy
#define ADC_ADCS_20TCY			0x0013	//adc clock selection - 1tcy
#define ADC_ADCS_21TCY			0x0014	//adc clock selection - 1tcy
#define ADC_ADCS_22TCY			0x0015	//adc clock selection - 1tcy
#define ADC_ADCS_23TCY			0x0016	//adc clock selection - 1tcy
#define ADC_ADCS_24TCY			0x0017	//adc clock selection - 1tcy
#define ADC_ADCS_25TCY			0x0018	//adc clock selection - 1tcy
#define ADC_ADCS_26TCY			0x0019	//adc clock selection - 1tcy
#define ADC_ADCS_27TCY			0x001a	//adc clock selection - 1tcy
#define ADC_ADCS_28TCY			0x001b	//adc clock selection - 1tcy
#define ADC_ADCS_29TCY			0x001c	//adc clock selection - 1tcy
#define ADC_ADCS_30TCY			0x001d	//adc clock selection - 1tcy
#define ADC_ADCS_31TCY			0x001e	//adc clock selection - 1tcy
#define ADC_ADCS_32TCY			0x001f	//adc clock selection - 1tcy
#define ADC_ADCS_33TCY			0x0020	//adc clock selection - 1tcy
#define ADC_ADCS_34TCY			0x0021	//adc clock selection - 2tcy
#define ADC_ADCS_35TCY			0x0022	//adc clock selection - 1tcy
#define ADC_ADCS_36TCY			0x0023	//adc clock selection - 1tcy
#define ADC_ADCS_37TCY			0x0024	//adc clock selection - 1tcy
#define ADC_ADCS_38TCY			0x0025	//adc clock selection - 1tcy
#define ADC_ADCS_39TCY			0x0026	//adc clock selection - 1tcy
#define ADC_ADCS_40TCY			0x0027	//adc clock selection - 1tcy
#define ADC_ADCS_41TCY			0x0028	//adc clock selection - 1tcy
#define ADC_ADCS_42TCY			0x0029	//adc clock selection - 1tcy
#define ADC_ADCS_43TCY			0x002a	//adc clock selection - 1tcy
#define ADC_ADCS_44TCY			0x002b	//adc clock selection - 1tcy
#define ADC_ADCS_45TCY			0x002c	//adc clock selection - 1tcy
#define ADC_ADCS_46TCY			0x002d	//adc clock selection - 1tcy
#define ADC_ADCS_47TCY			0x002e	//adc clock selection - 1tcy
#define ADC_ADCS_48TCY			0x002f	//adc clock selection - 1tcy
#define ADC_ADCS_49TCY			0x0030	//adc clock selection - 1tcy
#define ADC_ADCS_50TCY			0x0031	//adc clock selection - 2tcy
#define ADC_ADCS_51TCY			0x0032	//adc clock selection - 1tcy
#define ADC_ADCS_52TCY			0x0033	//adc clock selection - 1tcy
#define ADC_ADCS_53TCY			0x0034	//adc clock selection - 1tcy
#define ADC_ADCS_54TCY			0x0035	//adc clock selection - 1tcy
#define ADC_ADCS_55TCY			0x0036	//adc clock selection - 1tcy
#define ADC_ADCS_56TCY			0x0037	//adc clock selection - 1tcy
#define ADC_ADCS_57TCY			0x0038	//adc clock selection - 1tcy
#define ADC_ADCS_58TCY			0x0039	//adc clock selection - 1tcy
#define ADC_ADCS_59TCY			0x003a	//adc clock selection - 1tcy
#define ADC_ADCS_60TCY			0x003b	//adc clock selection - 1tcy
#define ADC_ADCS_61TCY			0x003c	//adc clock selection - 1tcy
#define ADC_ADCS_62TCY			0x003d	//adc clock selection - 1tcy
#define ADC_ADCS_63TCY			0x003e	//adc clock selection - 1tcy
#define ADC_ADCS_64TCY			0x003f	//adc clock selection - 1tcy
//0x0040 .. 0xffff						//reserved

//ad1pcfg - ad channel configure
//1 = digital
//0 = analog
#define ADC_AN0					(0)		//adc an0
#define ADC_AN1					(1)		//adc an1
#define ADC_AN2					(2)		//adc an2
#define ADC_AN3					(3)		//adc an3
#define ADC_AN4					(4)		//adc an4
#define ADC_AN5					(5)		//adc an5
#define ADC_AN6					(6)		//adc an6		-unimplemented on 28pin devices
#define ADC_AN7					(7)		//adc an7		-unimplemented on 28pin devices
#define ADC_AN8					(8)		//adc an8		-unimplemented on 28pin devices
#define ADC_AN9					(9)		//adc an9
#define ADC_AN10				(10)	//adc an10
#define ADC_AN11				(11)	//adc an11
#define ADC_AN12				(12)	//adc an12
#define ADC_VCORE				(13)	//adc vcore
#define ADC_VBG_2				(14)	//adc bandgap/2
#define ADC_VBG					(15)	//adc bandgap
#define ADC_CTMU				(0xffff)	//for ctmu

void adc_init(void);

unsigned short adc_read(unsigned short adc_ch);

#endif //adc_h_
