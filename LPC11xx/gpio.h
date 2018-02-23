#ifndef _GPIO_H
#define _GPIO_H

#include "lpc11xx.h"								//we use lpc1343
//#include "lpc11xx_syscon.h"							//we use rcc
//#include "lpc11xx_gpio.h"							//we use gpio

//port macros
#define IO_SET(port, pins) 	port->DATA |= (pins)	//port->ODR |= (pins)		//port->BSRR = (pins)
#define IO_CLR(port, pins)	port->DATA &=~(pins)		//port->BRR = (pins)
#define IO_FLP(port, pins)	port->DATA ^= (pins)
#define IO_GET(port, pins)	(port->DATA & (pins))	//return gpio pins

//fast gpio routines
//#define FIO_SET(port, pins)	port->MASKED_ACCESS[(pins) & 0b11111111111] = ((pins) & 0b11111111111)		//port->BSRR = (pins)
//#define FIO_CLR(port, pins)	port->MASKED_ACCESS[(pins) & 0b11111111111] = 0		//port->BRR = (pins)
//#define FIO_FLP(port, pins)	IO_FLP(port, pins)		//no fast io routine for pin flipping
//#define FIO_GET(port, pins) (port->MASKED_ACCESS[(pins) & 0b11111111111])			//IO_GET(port, pins)		// no fast io routines
#define FIO_SET(port, pins)	port->MASKED_ACCESS[pins] = (pins)	//IO_SET(port, pins)		//port->BSRR = (pins)
#define FIO_CLR(port, pins)	port->MASKED_ACCESS[pins] = 0		//IO_CLR(port, pins)		//port->BRR = (pins)
#define FIO_FLP(port, pins)	IO_FLP(port, pins)		//no fast io routine for pin flipping
#define FIO_GET(port, pins) (port->MASKED_ACCESS[pins] & (pins))	//IO_GET(port, pins)		// no fast io routines

//set pins to output
//void IO_OUT(GPIO_TypeDef* port, uint16_t pins);
#define IO_OUT(port, pins)	port->DIR |= (pins)		//GPIO_SetDir(port, pins, 1)

//set pins as floating input
//void IO_IN(GPIO_TypeDef* port, uint16_t pins);
#define IO_IN(port, pins)	port->DIR &=~(pins)		//GPIO_SetDir(port, pins, 0)

//get pins
//uint16_t IO_GET(GPIO_TypeDef* port, uint16_t pins);

//specific to STM32VLDiscovery
//led definitions
#define LED_PORT		GPIO0
#define LED_DDR			GPIO0
#define LED				(1<<7)						//GPIO_Pin_9			//green led on pc9

#define GPIO0			LPC_GPIO0
#define GPIO1			LPC_GPIO1
#define GPIO2			LPC_GPIO2

//reset the mcu
void mcu_init(void);


//nop
#define NOP()	__NOP()
#define NOP2()	{NOP(); NOP();}
#define NOP4()	{NOP2(); NOP2();}
#define NOP8()	{NOP4(); NOP4();}
#define NOP16()	{NOP8(); NOP8();}
#define NOP24()	{NOP16(); NOP8();}
#define NOP32()	{NOP16(); NOP16();}
#define NOP40()	{NOP32(); NOP8();}

//f_cpu speed
//#define SystemCoreClock		(SystemFrequency)					//SystemFrequency used in the library files
#define F_CPU				(SystemCoreClock/*24000000ul*/)					//cpu runs at 2Mhz -> Fxtal = 2Mhz

//void (*mcu_reset)(void) = 0x0000; 				//jump to 0x0000 -> software reset

#ifndef ei
#define ei()
#endif

#ifndef di
#define di()
#endif

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


#endif
