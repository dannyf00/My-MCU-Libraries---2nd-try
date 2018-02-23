#ifndef __GPIO_H
#define __GPIO_H

//#include <stdint.h>									//standard types
#if defined(__XC16__)
#include <xc.h>
#else
#include <p24fxxxx.h>									//we use pic24f
//#include <p33fxxxx.h>									//we use dspic33f
//#include <p30fxxxx.h>									//we use dspic30f
#endif


typedef unsigned char uint8_t;
typedef signed char int8_t;
typedef unsigned short uint16_t;
typedef signed short int16_t;
typedef unsigned long uint32_t;
typedef signed long int32_t;

//port manipulation macros for PIC.

#define IO_SET(port, bits)	port |= (bits)			//set bits on port
#define IO_CLR(port, bits)	port &=~(bits)			//clear bits on port
#define IO_FLP(port, bits)	port ^= (bits)			//flip bits on port
#define IO_GET(port, bits)	((port) & (bits))		//return bits on port
#define IO_OUT(ddr, bits)	ddr &=~(bits)			//set bits as output
#define IO_IN(ddr, bits)	ddr |= (bits)			//set bits as input

//gpio definitions
#define GIO_SET(port, bits)	IO_SET(port->LAT, bits)		//port->LAT |= (bits)			//set bits on port
#define GIO_CLR(port, bits)	IO_CLR(port->LAT, bits)		//port->LAT &=~(bits)			//clear bits on port
#define GIO_FLP(port, bits)	IO_FLP(port->LAT, bits)		//port->LAT ^= (bits)			//flip bits on port
#define GIO_GET(port, bits)	IO_GET(port->PORT, bits)	//((port->PORT) & (bits))		//return bits on port
#define GIO_OUT(port, bits)	IO_OUT(port->TRIS, bits)	//ddr->TRIS &=~(bits)			//set bits as output
#define GIO_IN(port, bits)	IO_IN(port->TRIS, bits)		//ddr->TRIS |= (bits)			//set bits as input


#define NOP()				Nop()					//asm("nop")					//nop()
#define NOP2()				{NOP(); NOP();}
#define NOP4()				{NOP2(); NOP2();}
#define NOP8()				{NOP4(); NOP4();}
#define NOP16()				{NOP8(); NOP8();}
#define NOP16()				{NOP8(); NOP8();}
#define NOP24()				{NOP16(); NOP8();}
#define NOP32()				{NOP16(); NOP16();}
#define NOP40()				{NOP32(); NOP8();}
#define NOP64()				{NOP32(); NOP32();}

#define sleep()				asm("sleep")				//put the mcu into sleep

//define clock speed
#ifndef F_XTAL
#define F_XTAL				8000000ul				//default to 8Mhz
#endif
#define F_FRC				8000000ul				//8Mhz
#define F_SOSC				32768ul					//32768Hz
#define F_LPRC				31000ul					//31Khz
//#define F_CPU				(8000000ul/2)					//cpu runs at 2Mhz -> Fxtal = 2Mhz
extern uint32_t SystemCoreClock;	//systemcoreclock = Peripheral clock
extern uint32_t F_CPU;			//CPU clock
extern uint32_t F_REFO;		//refclock output
uint32_t SystemCoreClockUpdate(void);

//void (*mcu_reset)(void) = 0x0000; 				//jump to 0x0000 -> software reset

#ifndef ei
#define ei()
#endif

#ifndef di
#define di()
#endif

//device/family id
//#define DEVID				(*(const unsigned int *) 0xff0000)
//#define DEVREV			(*(const unsigned int *) 0xff0002)

unsigned int DEVID(void);							//read device id at 0xff0000
unsigned int DEVREV(void);							//read device rev at 0xff0002
unsigned long DEVIDREV(void);							//read device rev at 0xff0002
void mcu_init();									//reset the mcu

//unlock IOLOCK OSCCONL -  __builtin_write_OSCCONL(unsigned char value);
#define IO_UNLOCKL()	{asm volatile ( "MOV #OSCCON, w1 \n" \
					"MOV #0x46, w2 \n" \
					"MOV #0x57, w3 \n" \
					"MOV.b w2, [w1] \n" \
					"MOV.b w3, [w1] \n" \
					"BCLR OSCCON,#6"); \
					}

//unlock IOLOCK OSCCONH -  __builtin_write_OSCCONH(unsigned char value);
#define IO_UNLOCKH()	{asm volatile ( "MOV #OSCCON, w1 \n" \
					"MOV #0x78, w2 \n" \
					"MOV #0x9a, w3 \n" \
					"MOV.b w2, [w1] \n" \
					"MOV.b w3, [w1] \n" \
					"BCLR OSCCON,#6"); \
					}

//lock IOLOCK
#define IO_LOCK()	{asm volatile ( "MOV #OSCCON, w1 \n" \
					"MOV #0x46, w2 \n" \
					"MOV #0x57, w3 \n" \
					"MOV.b w2, [w1] \n" \
					"MOV.b w3, [w1] \n" \
					"BSET OSCCON, #6" ); \
					}


//more on macro
//macros for remappable pins
//for peripheral pin select (PPS)
#if defined(_INT1R)
/// Maps INT1 to a remappable pin;
/// see PPS_xxx_TO_RP(pin) for more informatino.
#define PPS_INT1_TO_RP(pin) _INT1R = pin
#else
#define PPS_INT1_TO_RP(pin)
#endif


#if defined(_INT2R)
#define PPS_INT2_TO_RP(pin) _INT2R = pin
#else
#define PPS_INT2_TO_RP(pin)
#endif

#if defined(_T2CKR)
#define PPS_T2CK_TO_RP(pin) _T2CKR = pin
#else
#define PPS_T2CK_TO_RP(pin)
#endif

#if defined(_T3CKR)
#define PPS_T3CK_TO_RP(pin) _T3CKR = pin
#else
#define PPS_T3CK_TO_RP(pin)
#endif

#if defined(_T4CKR)
#define PPS_T4CK_TO_RP(pin) _T4CKR = pin
#else
#define PPS_T4CK_TO_RP(pin)
#endif

#if defined(_T5CKR)
#define PPS_T5CK_TO_RP(pin) _T5CKR = pin
#else
#define PPS_T5CK_TO_RP(pin)
#endif

#if defined(_IC1R)
#define PPS_IC1_TO_RP(pin) _IC1R = pin
#else
#define PPS_IC1_TO_RP(pin)
#endif

#if defined(_IC2R)
#define PPS_IC2_TO_RP(pin) _IC2R = pin
#else
#define PPS_IC2_TO_RP(pin)
#endif

#if defined(_IC3R)
#define PPS_IC3_TO_RP(pin) _IC3R = pin
#else
#define PPS_IC3_TO_RP(pin)
#endif

#if defined(_IC4R)
#define PPS_IC4_TO_RP(pin) _IC4R = pin
#else
#define PPS_IC4_TO_RP(pin)
#endif

#if defined(_IC5R)
#define PPS_IC5_TO_RP(pin) _IC5R = pin
#else
#define PPS_IC5_TO_RP(pin)
#endif

#if defined(_IC6R)
#define PPS_IC6_TO_RP(pin) _IC6R = pin
#else
#define PPS_IC6_TO_RP(pin)
#endif

#if defined(_IC7R)
#define PPS_IC7_TO_RP(pin) _IC7R = pin
#else
#define PPS_IC7_TO_RP(pin)
#endif

#if defined(_IC8R)
#define PPS_IC8_TO_RP(pin) _IC8R = pin
#else
#define PPS_IC8_TO_RP(pin)
#endif

#if defined(_OCFAR)
#define PPS_OCFA_TO_RP(pin) _OCFAR = pin
#else
#define PPS_OCFA_TO_RP(pin)
#endif

#if defined(_OCFBR)
#define PPS_OCFB_TO_RP(pin) _OCFBR = pin
#else
#define PPS_OCFB_TO_RP(pin)
#endif

#if defined(_U1RXR)
#define PPS_U1RX_TO_RP(pin) _U1RXR = pin
#else
#define PPS_U1RX_TO_RP(pin)
#endif

#if defined(_U1CTSR)
#define PPS_U1CTS_TO_RP(pin) _U1CTSR = pin
#else
#define PPS_U1CTS_TO_RP(pin)
#endif

#if defined(_U2RXR)
#define PPS_U2RX_TO_RP(pin) _U2RXR = pin
#else
#define PPS_U2RX_TO_RP(pin)
#endif

#if defined(_U2CTSR)
#define PPS_U2CTS_TO_RP(pin) _U2CTSR = pin
#else
#define PPS_U2CTS_TO_RP(pin)
#endif

#if defined(_SDI1R)
#define PPS_SDI1_TO_RP(pin) _SDI1R = pin
#else
#define PPS_SDI1_TO_RP(pin)
#endif

#if defined(_SCK1R)
#define PPS_SCK1IN_TO_RP(pin) _SCK1R = pin
#else
#define PPS_SCK1IN_TO_RP(pin)
#endif

#if defined(_SS1R)
#define PPS_SS1IN_TO_RP(pin) _SS1R = pin
#else
#define PPS_SS1IN_TO_RP(pin)
#endif

#if defined(_SDI2R)
#define PPS_SDI2_TO_RP(pin) _SDI2R = pin
#else
#define PPS_SDI2_TO_RP(pin)
#endif

#if defined(_SCK2R)
#define PPS_SCK2IN_TO_RP(pin) _SCK2R = pin
#else
#define PPS_SCK2IN_TO_RP(pin)
#endif

#if defined(_SS2R)
#define PPS_SS2IN_TO_RP(pin) _SS2R = pin
#else
#define PPS_SS2IN_TO_RP(pin)
#endif

#if defined(_C1RXR)
#define PPS_C1RXR_TO_RP(pin) _C1RXR = pin
#else
#define PPS_C1RXR_TO_RP(pin)
#endif

#if defined(_C2RXR)
#define PPS_C2RXR_TO_RP(pin) _C2RXR = pin
#else
#define PPS_C2RXR_TO_RP(pin)
#endif
//@}


//end RP input mapping
//Your device may not have all of these peripherals!

//start RP output mapping


#if defined(_RP0R)
/// Maps C1OUT to a remappable pin;
/// see PPS_yyy_TO_RP(pin) for more informatino.
#define PPS_C1OUT_TO_RP(pin) _RP##pin##R = 1
#else
#define PPS_C1OUT_TO_RP(pin)
#endif

#if defined(_RP0R)
#define PPS_C2OUT_TO_RP(pin) _RP##pin##R = 2
#else
#define PPS_C2OUT_TO_RP(pin)
#endif

#if defined(_RP0R)
#define PPS_U1TX_TO_RP(pin) _RP##pin##R = 3
#else
#define PPS_U1TX_TO_RP(pin)
#endif

#if defined(_RP0R)
#define PPS_U1RTS_TO_RP(pin) _RP##pin##R = 4
#else
#define PPS_U1RTS_TO_RP(pin)
#endif

#if defined(_RP0R)
#define PPS_U2TX_TO_RP(pin) _RP##pin##R = 5
#else
#define PPS_U2TX_TO_RP(pin)
#endif

#if defined(_RP0R)
#define PPS_U2RTS_TO_RP(pin) _RP##pin##R = 6
#else
#define PPS_U2RTS_TO_RP(pin)
#endif

#if defined(_RP0R)
#define PPS_SDO1_TO_RP(pin) _RP##pin##R = 7
#else
#define PPS_SDO1_TO_RP(pin)
#endif

#if defined(_RP0R)
#define PPS_SCK1OUT_TO_RP(pin) _RP##pin##R = 8
#else
#define PPS_SCK1OUT_TO_RP(pin)
#endif

#if defined(_RP0R)
#define PPS_SS1OUT_TO_RP(pin) _RP##pin##R = 9
#else
#define PPS_SS1OUT_TO_RP(pin)
#endif

#if defined(_RP0R)
#define PPS_SDO2_TO_RP(pin) _RP##pin##R = 10
#else
#define PPS_SDO2_TO_RP(pin)
#endif

#if defined(_RP0R)
#define PPS_SCK2OUT_TO_RP(pin) _RP##pin##R = 11
#else
#define PPS_SCK2OUT_TO_RP(pin)
#endif

#if defined(_RP0R)
#define PPS_SS2OUT_TO_RP(pin) _RP##pin##R = 12
#else
#define PPS_SS2OUT_TO_RP(pin)
#endif

#if defined(_RP0R)
#define PPS_C1TX_TO_RP(pin) _RP##pin##R = 16
#else
#define PPS_C1TX_TO_RP(pin)
#endif

#if defined(_RP0R)
#define PPS_OC1_TO_RP(pin) _RP##pin##R = 18
#else
#define PPS_OC1_TO_RP(pin)
#endif

#if defined(_RP0R)
#define PPS_OC2_TO_RP(pin) _RP##pin##R = 19
#else
#define PPS_OC2_TO_RP(pin)
#endif

#if defined(_RP0R)
#define PPS_OC3_TO_RP(pin) _RP##pin##R = 20
#else
#define PPS_OC3_TO_RP(pin)
#endif

#if defined(_RP0R)
#define PPS_OC4_TO_RP(pin) _RP##pin##R = 21
#else
#define PPS_OC4_TO_RP(pin)
#endif

#if defined(_RP0R)
#define PPS_OC5_TO_RP(pin) _RP##pin##R = 22
#else
#define PPS_OC5_TO_RP(pin)
#endif

#if defined(_RP0R)
#define PPS_CTPLS_TO_RP(pin) _RP##pin##R = 29
#else
#define PPS_CTPLS_TO_RP(pin)
#endif

#if defined(_RP0R)
#define PPS_C3OUT_TO_RP(pin) _RP##pin##R = 30
#else
#define PPS_C3OUT_TO_RP(pin)
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
	volatile unsigned char B1:1;	//bit 0
	volatile unsigned char B2:1;	//bit 0
	volatile unsigned char B3:1;	//bit 0
	volatile unsigned char B4:1;	//bit 0
	volatile unsigned char B5:1;	//bit 0
	volatile unsigned char B6:1;	//bit 0
	volatile unsigned char B7:1;	//bit 7
} B8_TypeDef;

//word definitions
typedef struct {
	volatile unsigned char B0:1;	//bit 0
	volatile unsigned char B1:1;	//bit 0
	volatile unsigned char B2:1;	//bit 0
	volatile unsigned char B3:1;	//bit 0
	volatile unsigned char B4:1;	//bit 0
	volatile unsigned char B5:1;	//bit 0
	volatile unsigned char B6:1;	//bit 0
	volatile unsigned char B7:1;	//bit 7
	volatile unsigned char B8:1;	//bit 7
	volatile unsigned char B9:1;	//bit 7
	volatile unsigned char B10:1;	//bit 7
	volatile unsigned char B11:1;	//bit 7
	volatile unsigned char B12:1;	//bit 7
	volatile unsigned char B13:1;	//bit 7
	volatile unsigned char B14:1;	//bit 7
	volatile unsigned char B15:1;	//bit 7
} B16_TypeDef;

//gpio definitions
typedef struct {
	volatile unsigned short TRIS;	//direction register - offset 0x0000
	volatile unsigned short PORT;	//input data register
	volatile unsigned short LAT;		//output data register
	volatile unsigned short ODC;		//open drain register
} GPIO_TypeDef;				//gpio type definitions

#define GPIOA				((GPIO_TypeDef *) &TRISA)
#define GPIOB				((GPIO_TypeDef *) &TRISB)
#define GPIOC            		((GPIO_TypeDef *) &TRISC)
#define GPIOD				((GPIO_TypeDef *) &TRISD)
#define GPIOE				((GPIO_TypeDef *) &TRISE)
#define GPIOF				((GPIO_TypeDef *) &TRISF)
#define GPIOG				((GPIO_TypeDef *) &TRISG)

#endif //gpio_h_
