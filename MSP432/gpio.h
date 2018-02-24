#ifndef _GPIO_H
#define _GPIO_H

//#include "inc/tm4c1233h6pm.h"		//for tivaware = lm4f120h5

#include <stdint.h>
#include <stdbool.h>
#include "msp.h"					//msp432
#include "system_msp432p401r.h"		//for SystemCoreClockUpdate()

//port macros
#define IO_SET(port, pins)		port |= (pins)
#define IO_CLR(port, pins)		port &=~(pins)
#define IO_FLP(port, pins)		port ^= (pins)
#define IO_GET(port, pins)		((port) & (pins))
#define IO_IN(port, pins)		port &=~(pins)
#define IO_OUT(port, pins)		port |= (pins)

//fast gpio routines: approximately 3x faster than IO_XXX() macros above -> doesn't exist on this chip
#define FIO_SET(port, pins)		IO_SET(port, pins)			//HWREG(port + (GPIO_O_DATA + ((pins) << 2))) = (pins)		//port->BSRR = (pins)
#define FIO_CLR(port, pins)		IO_CLR(port, pins)			//HWREG(port + (GPIO_O_DATA + ((pins) << 2))) = 0				//port->BRR = (pins)
#define FIO_FLP(port, pins)		IO_FLP(port, pins)			//HWREG(port + (GPIO_O_DATA + ((pins) << 2))) ^= (pins)		//IO_FLP(port, pins)		//no fast io routine for pin flipping
#define FIO_GET(port, pins) 	IO_GET(port, pins)			//(HWREG(port + (GPIO_O_DATA + ((pins) << 2))) & (pins))		//IO_GET(port, pins)		// no fast io routines
#define FIO_OUT(port, pins)		IO_OUT(port, pins)
#define FIO_IN(port, pins)		IO_IN(port, pins)

//gpio macros
#define GIO_SET(port, pins)		port->OUT |= (pins)
#define GIO_CLR(port, pins)		port->OUT &=~(pins)
#define GIO_FLP(port, pins)		port->OUT ^= (pins)
#define GIO_GET(port, pins)		((port->IN) & (pins))
#define GIO_IN(port, pins)		port->DDR &=~(pins)
#define GIO_OUT(port, pins)		port->DDR |= (pins)

//get pins
//uint16_t IO_GET(GPIO_TypeDef* port, uint16_t pins);
typedef struct {
	uint16_t IN;				//input register
	uint16_t OUT;			//otput register
	uint16_t DDR;			//direction register
	uint16_t REN;			//resistor enable
	uint16_t DS;				//drive strength
	uint16_t SEL0;			//select 0
	uint16_t SEL1;			//select 1
	uint16_t SELC;			//complement selection
	uint16_t IES;			//interrupt edge select
	uint16_t IE;			//interrupt enable
	uint16_t IFG;			//interrupt flag
} GPIO_TypeDef;

#define GPIO0				((volatile GPIO_TypeDef *)&P0IN)
#define GPIO1				((volatile GPIO_TypeDef *)&P1IN)
#define GPIO2				((volatile GPIO_TypeDef *)&P2IN)
#define GPIO3				((volatile GPIO_TypeDef *)&P3IN)
#define GPIO4				((volatile GPIO_TypeDef *)&P4IN)
#define GPIO5				((volatile GPIO_TypeDef *)&P5IN)
#define GPIO6				((volatile GPIO_TypeDef *)&P6IN)
#define GPIO7				((volatile GPIO_TypeDef *)&P7IN)
#define GPIO8				((volatile GPIO_TypeDef *)&P8IN)
#define GPIO9				((volatile GPIO_TypeDef *)&P9IN)
#define GPIOA				((volatile GPIO_TypeDef *)&PAIN)
#define GPIOB				((volatile GPIO_TypeDef *)&PBIN)
#define GPIOC				((volatile GPIO_TypeDef *)&PCIN)
#define GPIOD				((volatile GPIO_TypeDef *)&PDIN)
#define GPIOE				((volatile GPIO_TypeDef *)&PEIN)
#define GPIOJ				((volatile GPIO_TypeDef *)&PJIN)

//specific to STM32VLDiscovery
//led definitions
#define LED_GPIO			GPIO1
#define LED_PORT			P1OUT
#define LED_DDR				P1DIR
#define LED					(1<<0)	//all three leds
#define LEDRGB_GPIO			GPIO2
#define LEDRGB_PORT			P2OUT
#define LEDRGB_DDR			P2DIR
#define LEDR				(1<<0)	//all three leds
#define LEDG				(1<<1)	//all three leds
#define LEDB				(1<<2)	//all three leds

//close sources

#define F_DCO1dot5Mhz		CS_CTL0_DCORSEL_0
#define F_DCO_3Mhz			CS_CTL0_DCORSEL_1
#define F_DCO_6Mhz			CS_CTL0_DCORSEL_2
#define F_DCO_12Mhz			CS_CTL0_DCORSEL_3
#define F_DCO_24Mhz			CS_CTL0_DCORSEL_4
#define F_DCO_48Mhz			CS_CTL0_DCORSEL_5

#define SystemCoreClockHSI_1dot5Mhz()	SystemCoreClockHSI(F_DCO1dot5Mhz)
#define SystemCoreClockHSI_3Mhz()		SystemCoreClockHSI(F_DCO_3Mhz)
#define SystemCoreClockHSI_6Mhz()		SystemCoreClockHSI(F_DCO_6Mhz)
#define SystemCoreClockHSI_12Mhz()		SystemCoreClockHSI(F_DCO_12Mhz)
#define SystemCoreClockHSI_24Mhz()		SystemCoreClockHSI(F_DCO_24Mhz)
#define SystemCoreClockHSI_48Mhz()		SystemCoreClockHSI(F_DCO_48Mhz)

//reset the mcu
void mcu_init(void);

//nop
#define NOP()				__asm("NOP")
#define NOP2()				{NOP(); NOP();}
#define NOP4()				{NOP2(); NOP2();}
#define NOP8()				{NOP4(); NOP4();}
#define NOP16()				{NOP8(); NOP8();}
#define NOP24()				{NOP16(); NOP8();}
#define NOP32()				{NOP16(); NOP16();}
#define NOP40()				{NOP32(); NOP8();}
#define NOP64()				{NOP32(); NOP32();}

//f_cpu speed
#define F_CPU				(3000000ul)						//cpu runs at 2Mhz -> Fxtal = 2Mhz

//void (*mcu_reset)(void) = 0x0000; 							//jump to 0x0000 -> software reset

#ifndef ei
#define ei()				//MAP_IntMasterEnable()
#endif

#ifndef di
#define di()				//MAP_IntMasterDisable()
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

//byte-bit definitions
typedef struct {
	volatile unsigned char B0:1;	//bit 0
	volatile unsigned char B1:1;	//bit 1
	volatile unsigned char B2:1;	//bit 2
	volatile unsigned char B3:1;	//bit 3
	volatile unsigned char B4:1;	//bit 4
	volatile unsigned char B5:1;	//bit 5
	volatile unsigned char B6:1;	//bit 6
	volatile unsigned char B7:1;	//bit 7
} B8_TypeDef;

//word definitions
typedef struct {
	volatile unsigned char B0:1;	//bit 0
	volatile unsigned char B1:1;	//bit 1
	volatile unsigned char B2:1;	//bit 2
	volatile unsigned char B3:1;	//bit 3
	volatile unsigned char B4:1;	//bit 4
	volatile unsigned char B5:1;	//bit 5
	volatile unsigned char B6:1;	//bit 6
	volatile unsigned char B7:1;	//bit 7
	volatile unsigned char B8:1;	//bit 8
	volatile unsigned char B9:1;	//bit 9
	volatile unsigned char B10:1;	//bit 10
	volatile unsigned char B11:1;	//bit 11
	volatile unsigned char B12:1;	//bit 12
	volatile unsigned char B13:1;	//bit 13
	volatile unsigned char B14:1;	//bit 14
	volatile unsigned char B15:1;	//bit 15
} B16_TypeDef;

//Dword definitions
typedef struct {
	volatile unsigned char B0:1;	//bit 0
	volatile unsigned char B1:1;	//bit 1
	volatile unsigned char B2:1;	//bit 2
	volatile unsigned char B3:1;	//bit 3
	volatile unsigned char B4:1;	//bit 4
	volatile unsigned char B5:1;	//bit 5
	volatile unsigned char B6:1;	//bit 6
	volatile unsigned char B7:1;	//bit 7
	volatile unsigned char B8:1;	//bit 8
	volatile unsigned char B9:1;	//bit 9
	volatile unsigned char B10:1;	//bit 10
	volatile unsigned char B11:1;	//bit 11
	volatile unsigned char B12:1;	//bit 12
	volatile unsigned char B13:1;	//bit 13
	volatile unsigned char B14:1;	//bit 14
	volatile unsigned char B15:1;	//bit 15
	volatile unsigned char B16:1;	//bit 16
	volatile unsigned char B17:1;	//bit 17
	volatile unsigned char B18:1;	//bit 18
	volatile unsigned char B19:1;	//bit 19
	volatile unsigned char B20:1;	//bit 20
	volatile unsigned char B21:1;	//bit 21
	volatile unsigned char B22:1;	//bit 22
	volatile unsigned char B23:1;	//bit 23
	volatile unsigned char B24:1;	//bit 24
	volatile unsigned char B25:1;	//bit 25
	volatile unsigned char B26:1;	//bit 26
	volatile unsigned char B27:1;	//bit 28
	volatile unsigned char B28:1;	//bit 28
	volatile unsigned char B29:1;	//bit 29
	volatile unsigned char B30:1;	//bit 30
	volatile unsigned char B31:1;	//bit 31
} B32_TypeDef;


#endif
