#ifndef _GPIO_H
#define _GPIO_H

//using just device header file, no tiva lib support

//#include "tm4c1233h6pm.h"		//for tivaware = lm4f120h5
#include "tm4c123.h"			//the same as lm4c1233


//port macros
#define IO_SET(port, pins)		port->DATA |= (pins)					//MAP_GPIOPinWrite(port, (pins), (pins))
#define IO_CLR(port, pins)		port->DATA &=~(pins)					//MAP_GPIOPinWrite(port, (pins), (0))
#define IO_FLP(port, pins)		port->DATA ^= (pins)					//MAP_GPIOPinWrite(port, (pins), ~IO_GET(port, pins))
#define IO_GET(port, pins)		((port->DATA)&(pins))					//MAP_GPIOPinRead(port, pins)

//set pins as floating input
#define IO_IN(port, pins)		IO_INFL(port, pins)
#define IO_INFL(port, pins)		do {port->AFSEL &=~(pins); port->DEN |= (pins); port->PUR &=~(pins); port->PDR &=~(pins); port->DIR &=~(pins);} while (0)	//IO_IN(port, pins)						//MAP_GPIOPinTypeGPIOInput(port, pins)
#define IO_INPU(port, pins)		do {port->AFSEL &=~(pins); port->DEN |= (pins); port->PUR |= (pins); port->PDR &=~(pins); port->DIR &=~(pins);} while (0)	//IO_IN(port, pins)						//do {IO_IN(port, pins); HWREG((port) + (GPIO_O_PUR)) |= (pins);} while (0)
#define IO_INPD(port, pins)		do {port->AFSEL &=~(pins); port->DEN |= (pins); port->PUR &=~(pins); port->PDR |= (pins); port->DIR &=~(pins);} while (0)	//IO_IN(port, pins)						//do {IO_IN(port, pins); HWREG((port) + (GPIO_O_PDR)) |= (pins);} while (0)
//set pins to output - clock assumed to be already pumped to the periopherals
#define IO_OUT(port, pins)		IO_OUTPP(port, pins)
#define IO_OUTPP(port, pins)		do {port->AFSEL &=~(pins); port->DEN |= (pins); port->PUR &=~(pins); port->PDR &=~(pins); port->ODR |= (pins); port->DIR |= (pins);} while (0)		//IO_OUT(port, pins)						//do {IO_OUT(port, pins); HWREG((port) + (GPIO_O_ODR)) |= (pins);} while (0)
//set pins as output OD
#define IO_OUTOD(port, pins)		IO_OU
#define IO_OUTPU(port, pins)	do {port->AFSEL &=~(pins); port->DEN |= (pins); port->PUR |= (pins); port->PDR &=~(pins); port->ODR |= (pins); port->DIR |= (pins);} while (0)		//IO_OUT(port, pins)						//do {IO_OUT(port, pins); HWREG((port) + (GPIO_O_PUR)) |= (pins);} while (0)
#define IO_OUTPD(port, pins)	do {port->AFSEL &=~(pins); port->DEN |= (pins); port->PUR &=~(pins); port->PDR |= (pins); port->ODR |= (pins); port->DIR |= (pins);} while (0)		//IO_OUT(port, pins)						//do {IO_OUT(port, pins); HWREG((port) + (GPIO_O_PDR)) |= (pins);} while (0)

//using the bit-banding area - first 1k address
#define FIO_SET(port, pins)		port->RESERVED0[pins] = (pins)
#define FIO_CLR(port, pins)		port->RESERVED0[pins] =&(pins)
#define FIO_FLP(port, pins)		IO_FLP(port, pins)
#define FIO_GET(port, pins)		(port->RESERVED0[pins] & (pins))

//GPIO pins

//specific to STM32VLDiscovery
//led definitions
#define LED_PORT			GPIOF
#define LED_DDR				GPIOF
#define LEDG				GPIO_PIN_3			//green led on pf3
#define LEDB				GPIO_PIN_2			//blue led on pf2
#define LEDR				GPIO_PIN_1			//blue led on pf1
#define LEDs				(LEDR | LEDB | LEDG)	//all three leds

//close sources
#ifndef HSI_VALUE
#define HSI_VALUE			16000000ul			//16Mhz HSI/PIOSC
#endif
#ifndef HSE_VALUE
#define HSE_VALUE			16000000ul			//HSE/MainOSC frequency, in hz
#endif
#ifndef LSI_VALUE
#define LSI_VALUE			30000ul				//30Khz low frequency internal oscillator, in hz
#endif
#define PLL_VALUE			400000000ul			//400Mhz PLL output frequency

#define RCC_SYSDIV1			0x00
#define RCC_SYSDIV2			0x01
#define RCC_SYSDIV3			0x02
#define RCC_SYSDIV4			0x03
#define RCC_SYSDIV5			0x04
#define RCC_SYSDIV6			0x05
#define RCC_SYSDIV7			0x06
#define RCC_SYSDIV8			0x07
#define RCC_SYSDIV9			0x08
#define RCC_SYSDIV10		0x09
#define RCC_SYSDIV11		0x0a
#define RCC_SYSDIV12		0x0b
#define RCC_SYSDIV13		0x0c
#define RCC_SYSDIV14		0x0d
#define RCC_SYSDIV15		0x0e
#define RCC_SYSDIV16		0x0f

//HSI/PIOSC
void SystemCoreClock2HSI(uint32_t sysdiv);
void SystemCoreClock2HSIPLL(uint32_t mul, uint32_t div);
#define SystemCoreClock2HSI_1Mhz()		SystemCoreClock2HSI(RCC_SYSDIV16)										////use PIOSC/HSI/16 = 1Mhz
#define SystemCoreClock2HSI_1M07hz()	SystemCoreClock2HSI(RCC_SYSDIV15)										////use PIOSC/HSI/15 = 1Mhz
#define SystemCoreClock2HSI_1M14hz()	SystemCoreClock2HSI(RCC_SYSDIV14)										////use PIOSC/HSI/14 = 1Mhz
#define SystemCoreClock2HSI_1M23hz()	SystemCoreClock2HSI(RCC_SYSDIV13)										////use PIOSC/HSI/13 = 1Mhz
#define SystemCoreClock2HSI_1M33hz()	SystemCoreClock2HSI(RCC_SYSDIV12)										////use PIOSC/HSI/12 = 1Mhz
#define SystemCoreClock2HSI_1M45hz()	SystemCoreClock2HSI(RCC_SYSDIV11)										////use PIOSC/HSI/11 = 1Mhz
#define SystemCoreClock2HSI_1M60hz()	SystemCoreClock2HSI(RCC_SYSDIV10)										////use PIOSC/HSI/10 = 1Mhz
#define SystemCoreClock2HSI_1M78hz()	SystemCoreClock2HSI(RCC_SYSDIV9 )										////use PIOSC/HSI/9 = 1Mhz
#define SystemCoreClock2HSI_2Mhz()		SystemCoreClock2HSI(RCC_SYSDIV8 )										////use PIOSC/HSI/8 = 1Mhz
#define SystemCoreClock2HSI_2M29hz()	SystemCoreClock2HSI(RCC_SYSDIV7 )										////use PIOSC/HSI/7 = 1Mhz
#define SystemCoreClock2HSI_2M67hz()	SystemCoreClock2HSI(RCC_SYSDIV6 )										////use PIOSC/HSI/6 = 1Mhz
#define SystemCoreClock2HSI_3M20hz()	SystemCoreClock2HSI(RCC_SYSDIV5 )										////use PIOSC/HSI/5 = 1Mhz
#define SystemCoreClock2HSI_4Mhz()		SystemCoreClock2HSI(RCC_SYSDIV4 )										////use PIOSC/HSI/4 = 1Mhz
#define SystemCoreClock2HSI_5M33hz()	SystemCoreClock2HSI(RCC_SYSDIV3 )										////use PIOSC/HSI/3 = 1Mhz
#define SystemCoreClock2HSI_8Mhz()		SystemCoreClock2HSI(RCC_SYSDIV2 )										////use PIOSC/HSI/2 = 1Mhz
#define SystemCoreClock2HSI_16Mhz()		SystemCoreClock2HSI(RCC_SYSDIV1 )										////use PIOSC/HSI/1 = 16Mhz

//HSI/4
void SystemCoreClock2HSI4(uint32_t sysdiv);
#define SystemCoreClock2HSI_0M25hz()	SystemCoreClock2HSI4(RCC_SYSDIV16)										////use PIOSC/HSI/16 = 1Mhz
#define SystemCoreClock2HSI_0M27hz()	SystemCoreClock2HSI4(RCC_SYSDIV15)										////use PIOSC/HSI/15 = 1Mhz
#define SystemCoreClock2HSI_0M29hz()	SystemCoreClock2HSI4(RCC_SYSDIV14)										////use PIOSC/HSI/14 = 1Mhz
#define SystemCoreClock2HSI_0M31hz()	SystemCoreClock2HSI4(RCC_SYSDIV13)										////use PIOSC/HSI/13 = 1Mhz
#define SystemCoreClock2HSI_0M33hz()	SystemCoreClock2HSI4(RCC_SYSDIV12)										////use PIOSC/HSI/12 = 1Mhz
#define SystemCoreClock2HSI_0M36hz()	SystemCoreClock2HSI4(RCC_SYSDIV11)										////use PIOSC/HSI/11 = 1Mhz
#define SystemCoreClock2HSI_0M40hz()	SystemCoreClock2HSI4(RCC_SYSDIV10)										////use PIOSC/HSI/10 = 1Mhz
#define SystemCoreClock2HSI_0M44hz()	SystemCoreClock2HSI4(RCC_SYSDIV9 )										////use PIOSC/HSI/9 = 1Mhz
#define SystemCoreClock2HSI_0M50hz()	SystemCoreClock2HSI4(RCC_SYSDIV8 )										////use PIOSC/HSI/8 = 1Mhz
#define SystemCoreClock2HSI_0M57hz()	SystemCoreClock2HSI4(RCC_SYSDIV7 )										////use PIOSC/HSI/7 = 1Mhz
#define SystemCoreClock2HSI_0M67hz()	SystemCoreClock2HSI4(RCC_SYSDIV6 )										////use PIOSC/HSI/6 = 1Mhz
#define SystemCoreClock2HSI_0M80hz()	SystemCoreClock2HSI4(RCC_SYSDIV5 )										////use PIOSC/HSI/5 = 1Mhz
//#define SystemCoreClock2HSI_1Mhz()		SystemCoreClock2HSI4(RCC_SYSDIV4 )										////use PIOSC/HSI/4 = 1Mhz
//#define SystemCoreClock2HSI_1M33hz()	SystemCoreClock2HSI4(RCC_SYSDIV3 )										////use PIOSC/HSI/3 = 1Mhz
//#define SystemCoreClock2HSI_2Mhz()		SystemCoreClock2HSI4(RCC_SYSDIV2 )										////use PIOSC/HSI/2 = 1Mhz
//#define SystemCoreClock2HSI_1Mhz()		SystemCoreClock2HSI4(RCC_SYSDIV1 )										////use PIOSC/HSI/1 = 16Mhz

//HSE/external crystal - for 16Mhz only
void SystemCoreClock2HSE(uint32_t sysdiv);
void SystemCoreClock2HSEPLL(uint32_t mul, uint32_t div);

//reset the mcu
void mcu_init(void);

//nop
#define NOP()				__nop()						//asm(" nop")				//__asm("NOP")
#define NOP2()				{NOP(); NOP();}
#define NOP4()				{NOP2(); NOP2();}
#define NOP8()				{NOP4(); NOP4();}
#define NOP16()				{NOP8(); NOP8();}
#define NOP24()				{NOP16(); NOP8();}
#define NOP32()				{NOP16(); NOP16();}
#define NOP40()				{NOP32(); NOP8();}
#define NOP64()				{NOP32(); NOP32();}

//f_cpu speed
//#define SystemCoreClock		40000000ul					//cpu runs at 2Mhz -> Fxtal = 2Mhz
#define F_CPU				SystemCoreClock				//(SysCtlClockGet()/*40000000ul*/)					//cpu runs at 2Mhz -> Fxtal = 2Mhz
//#define SystemCoreClockUpdate()	SysCtlClockGet()				//for compatibility

//void (*mcu_reset)(void) = 0x0000; 							//jump to 0x0000 -> software reset

#ifndef ei
#define ei()				__enable_irq()
#endif

#ifndef di
#define di()				__disable_irq()
#endif

//DID0/DID1
#define DID0				SYSCTL_DID0_R			//DID0
#define DID1				SYSCTL_DID1_R			//DID1

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
