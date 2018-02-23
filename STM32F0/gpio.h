//gpio function, direct register access

#ifndef _GPIO_H
#define _GPIO_H

#include "stm32f0xx.h"										//we use stm32f10x

//global defines
//MODE:
//Output modes: GPIOMODE_OUTPP, GPIOMODE_OUTOD
//Input mode: GPIOMODE_INPUT, GPIOMODE_INPUTPD, GPIOMODE_INPUTPU
//Alternate function: GPIOMODE_AFPP, GPIOMODE_AFOD
//for moder
#define GPIOMODE_INPUT		(0<<0)		//(0<<0)
#define GPIOMODE_OUTPUT		(1<<0)		//(1<<0)
#define GPIOMODE_AF			(2<<0)
#define GPIOMODE_AN			(3<<0)
//for otyper
#define GPIOMODE_PP			(1<<3)
#define GPIOMODE_OD			(0<<3)
//for pupdr
#define GPIOMODE_FL			(0<<4)
#define GPIOMODE_PU			(1<<4)
#define GPIOMODE_PD			(2<<4)

//AF defs
#define GPIOMODE_AF0		0
#define GPIOMODE_AF1		1
#define GPIOMODE_AF2		2
#define GPIOMODE_AF3		3
#define GPIOMODE_AF4		4
#define GPIOMODE_AF5		5
#define GPIOMODE_AF6		6
#define GPIOMODE_AF7		7

#define GPIOMODE_OUTPP		(GPIOMODE_OUTPUT | GPIOMODE_PP)		//gpio, output, push-pull
#define GPIOMODE_OUTOD		(GPIOMODE_OUTPUT | GPIOMODE_OD)		//gpio, output, od
#define GPIOMODE_INFL		(GPIOMODE_INPUT)
#define GPIOMODE_INPU		(GPIOMODE_INPUT | GPIOMODE_PU)
#define GPIOMODE_INPD		(GPIOMODE_INPUT | GPIOMODE_PD)
#define GPIOMODE_AFPP		(GPIOMODE_AF | GPIOMODE_PP)
#define GPIOMODE_AFOD		(GPIOMODE_AF | GPIOMODE_OD)
#define GPIOMODE_INAN		(GPIOMODE_AN)

//global variables

//port/gpio oriented macros
#define IO_SET(port, pins)					port->ODR |= (pins)				//set bits on port
#define IO_CLR(port, pins)					port->ODR &=~(pins)				//clear bits on port
#define IO_FLP(port, pins)					port->ODR ^= (pins)				//flip bits on port
#define IO_GET(port, pins)					((port->IDR) & (pins))			//return bits on port
//set a pin to output/input
#define IO_OUTPP(port, pins)				GPIO_DDR(port, pins, GPIOMODE_OUTPP)	//push-pull mode (CR1 set, CR2 cleared)	//IO_OUTPP(GPIOx, GPIO_Pins).
#define IO_OUTOD(port, pins)				GPIO_DDR(port, pins, GPIOMODE_OUTOD)	//open drain mode (cr1 + cr2 cleared)	//_GPIO_Init(GPIOx, GPIO_Pins, GPIO_MODE_OUT_OD_LOW_FAST)
#define IO_OUT(port, pins)					IO_OUTPP(port, pins)					//_GPIO_Init(GPIOx, GPIO_Pins, GPIO_MODE_OUT_PP_LOW_FAST)
#define IO_INFL(port, pins)					GPIO_DDR(port, pins, GPIOMODE_INFL)		//floating input, no interrupt			//IO_INFL(GPIOx, GPIO_Pins)
#define IO_INPU(port, pins)					GPIO_DDR(port, pins, GPIOMODE_INPU)		//pull-up, no interrupt					//_GPIO_Init(GPIOx, GPIO_Pins, GPIO_MODE_IN_PU_NO_IT)
#define IO_INPD(port, pins)					GPIO_DDR(port, pins, GPIOMODE_INPD)		//pull-up, no interrupt					//_GPIO_Init(GPIOx, GPIO_Pins, GPIO_MODE_IN_PU_NO_IT)
#define IO_IN(port, pins)					IO_INFL(port, pins)					//IO_IN(port, pins)				//_GPIO_Init(GPIOx, GPIO_Pins, GPIO_MODE_IN_FL_NO_IT)
#define IO_AFPP(port, pins)					GPIO_DDR(port, pins, GPIOMODE_AFPP)		//configure pin for alternative function output, push-pull, 10Mhz
#define IO_AFOD(port, pins)					GPIO_DDR(port, pins, GPIOMODE_AFOD)		//configure pin for alternative function output, open-drain, 10Mhz
#define IO_AN(port, pins)					GPIO_DDR(port, pins, GPIOMODE_INAN)

//fast routines through BRR/BSRR registers
#define FIO_SET(port, pins)					port->BSRR = (pins)
#define FIO_CLR(port, pins)					port->BRR = (pins)
#define FIO_FLP(port, pins)					IO_FLP(port, pins)
#define FIO_GET(port, pins)					IO_GET(port, pins)

//configure gpio mode (cnf1..0 + mod1..0 bits)
void GPIO_DDR(GPIO_TypeDef * gpio, uint32_t mask, uint32_t mode);

//set systemcoreclock to 8Mhz / 2 * RCC_PLLMul_x (x=[2..16])
//Need to check wait state RCC_PLLMul_2
#define RCC_PLLMul2			RCC_CFGR_PLLMULL2
#define RCC_PLLMul3			RCC_CFGR_PLLMULL3
#define RCC_PLLMul4			RCC_CFGR_PLLMULL4
#define RCC_PLLMul5			RCC_CFGR_PLLMULL5
#define RCC_PLLMul6			RCC_CFGR_PLLMULL6
#define RCC_PLLMul7			RCC_CFGR_PLLMULL7
#define RCC_PLLMul8			RCC_CFGR_PLLMULL8
#define RCC_PLLMul9			RCC_CFGR_PLLMULL9
#define RCC_PLLMul10		RCC_CFGR_PLLMULL10
#define RCC_PLLMul11		RCC_CFGR_PLLMULL11
#define RCC_PLLMul12		RCC_CFGR_PLLMULL12
#define RCC_PLLMul13		RCC_CFGR_PLLMULL13
#define RCC_PLLMul14		RCC_CFGR_PLLMULL14
#define RCC_PLLMul15		RCC_CFGR_PLLMULL15
#define RCC_PLLMul16		RCC_CFGR_PLLMULL16
//#define RCC_PLLMul_16		RCC_CFGR_PLLMULL2

#define RCC_PREDIV1			RCC_CFGR2_PREDIV1_DIV1
#define RCC_PREDIV2			RCC_CFGR2_PREDIV1_DIV2
#define RCC_PREDIV3			RCC_CFGR2_PREDIV1_DIV3
#define RCC_PREDIV4			RCC_CFGR2_PREDIV1_DIV4
#define RCC_PREDIV5			RCC_CFGR2_PREDIV1_DIV5
#define RCC_PREDIV6			RCC_CFGR2_PREDIV1_DIV6
#define RCC_PREDIV7			RCC_CFGR2_PREDIV1_DIV7
#define RCC_PREDIV8			RCC_CFGR2_PREDIV1_DIV8
#define RCC_PREDIV9			RCC_CFGR2_PREDIV1_DIV9
#define RCC_PREDIV10		RCC_CFGR2_PREDIV1_DIV10
#define RCC_PREDIV11		RCC_CFGR2_PREDIV1_DIV11
#define RCC_PREDIV12		RCC_CFGR2_PREDIV1_DIV12
#define RCC_PREDIV13		RCC_CFGR2_PREDIV1_DIV13
#define RCC_PREDIV14		RCC_CFGR2_PREDIV1_DIV14
#define RCC_PREDIV15		RCC_CFGR2_PREDIV1_DIV15
#define RCC_PREDIV16		RCC_CFGR2_PREDIV1_DIV16
//set SystemCoreClock to HSI
void SystemCoreClockHSI(void);
//set SystemCoreClock to HSI+PLL
void SystemCoreClockHSIPLL(uint32_t pll);
#define SystemCoreClockHSIPLL_8Mhz()	SystemCoreClockHSIPLL(RCC_PLLMul2)
#define SystemCoreClockHSIPLL_12Mhz()	SystemCoreClockHSIPLL(RCC_PLLMul3)
#define SystemCoreClockHSIPLL_16Mhz()	SystemCoreClockHSIPLL(RCC_PLLMul4)
#define SystemCoreClockHSIPLL_20Mhz()	SystemCoreClockHSIPLL(RCC_PLLMul5)
#define SystemCoreClockHSIPLL_24Mhz()	SystemCoreClockHSIPLL(RCC_PLLMul6)
#define SystemCoreClockHSIPLL_28Mhz()	SystemCoreClockHSIPLL(RCC_PLLMul7)
#define SystemCoreClockHSIPLL_32Mhz()	SystemCoreClockHSIPLL(RCC_PLLMul8)
//32Mhz max for STM32F030
#define SystemCoreClockHSIPLL_36Mhz()	SystemCoreClockHSIPLL(RCC_PLLMul9)
#define SystemCoreClockHSIPLL_40Mhz()	SystemCoreClockHSIPLL(RCC_PLLMul10)
#define SystemCoreClockHSIPLL_44Mhz()	SystemCoreClockHSIPLL(RCC_PLLMul11)
#define SystemCoreClockHSIPLL_48Mhz()	SystemCoreClockHSIPLL(RCC_PLLMul12)
#define SystemCoreClockHSIPLL_52Mhz()	SystemCoreClockHSIPLL(RCC_PLLMul13)
#define SystemCoreClockHSIPLL_56Mhz()	SystemCoreClockHSIPLL(RCC_PLLMul14)
#define SystemCoreClockHSIPLL_60Mhz()	SystemCoreClockHSIPLL(RCC_PLLMul15)
#define SystemCoreClockHSIPLL_64Mhz()	SystemCoreClockHSIPLL(RCC_PLLMul16)

//set systemcoreclock to hse
void SystemCoreClockHSE(void);
//set to hsepll
void SystemCoreClockHSEPLL(uint32_t pll, uint32_t div);


#define NOP()         			__NOP()						//__no_operation()			//asm("nop")            		//nop
#define NOP2()					{NOP(); NOP();}
#define NOP4()					{NOP2(); NOP2();}
#define NOP8()					{NOP4(); NOP4();}
#define NOP16()					{NOP8(); NOP8();}
#define NOP16()					{NOP8(); NOP8();}
#define NOP24()					{NOP16(); NOP8();}
#define NOP32()					{NOP16(); NOP16();}
#define NOP40()					{NOP32(); NOP8();}
#define NOP64()					{NOP32(); NOP32();}

//interrupts always enabled and never disabled
#ifndef ei
	#define ei()							//asm("rim")					//enable all interrupts
#endif

#ifndef di
	#define di()							//asm("sim")					//disable all interrupts
#endif

#define F_CPU					(SystemCoreClock)							//default fcpu, SystemCoreClock -> more code space (+200 bytes)

//simple multiples
#define x1(val)				(val)								//multiply val by 1
#define x2(val)				(((val) << 1))						//multiply val by 2
#define x3(val)				(x2(val) + (val))					//multiply val by 3
#define x4(val)				(((val) << 2))						//multiply val by 4
#define x5(val)				(x4(val) + (val))					//multiply val by 5
#define x6(val)				(x4(val) + x2(val))					//multiply val by 6
#define x7(val)				(x6(val) + (val))					//multiply val by 7
#define x8(val)				((val) << 3)						//multiply val by 8
#define x9(val)				(x8(val) + (val))					//multiply val by 9

//multiples of 10s
#define x10(val)			(x8(val) + x2(val))					//multiply val by 10
#define x100(val)			(x10(x10(val)))						//multiply val by 100
#define x1000(val)			(x100(x10(val)))					//multiply val by 1000
#define x1k(val)			x1000(val)							//multiply val by 1000
#define x10k(val)			(x100(x100(val)))					//multiply val by 10000

#define x20(val)			(x2(x10(val)))
#define x30(val)			(x3(x10(val)))
#define x40(val)			(x4(x10(val)))
#define x50(val)			(x5(x10(val)))
#define x60(val)			(x6(x10(val)))
#define x70(val)			(x7(x10(val)))
#define x80(val)			(x8(x10(val)))
#define x90(val)			(x9(x10(val)))

//multiples of 100s
#define x200(val)			(x2(x100(val)))
#define x300(val)			(x3(x100(val)))
#define x400(val)			(x4(x100(val)))
#define x500(val)			(x5(x100(val)))
#define x600(val)			(x6(x100(val)))
#define x700(val)			(x7(x100(val)))
#define x800(val)			(x8(x100(val)))
#define x900(val)			(x9(x100(val)))

//custom definitions
#define x34(val)			(x30(val) + x4(val))				//multiply val by 34
#define x97(val)			(x90(val) + x7(val))				//multiply val by 97x

//reset the chip
void mcu_init(void);
#endif
