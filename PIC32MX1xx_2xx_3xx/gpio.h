#ifndef __GPIO_H
#define __GPIO_H

#include <stdint.h>                                             //we use standard types
#if defined(__XC32)
#include <xc.h>
#else
#include <p32xxxx.h>											//we use pic32f
#endif
//#include <plib.h>												//to use isr macro
#include <sys/attribs.h>										//attributes for interrupts

//port manipulation macros for PIC.
#define IO_SET(port, bits)              port |= (bits)			//set bits on port
#define IO_CLR(port, bits)              port &=~(bits)			//clear bits on port
#define IO_FLP(port, bits)              port ^= (bits)			//flip bits on port
#define IO_GET(port, bits)              ((port) & (bits))		//return bits on port
#define IO_OUT(ddr, bits)               ddr &=~(bits)			//set bits as output
#define IO_IN(ddr, bits)                ddr |= (bits)			//set bits as input

//if gpio_typedef is used
#define GIO_SET(port, bits)              port->LAT |= (bits)			//set bits on port
#define GIO_CLR(port, bits)              port->LAT &=~(bits)			//clear bits on port
#define GIO_FLP(port, bits)              port->LAT ^= (bits)			//flip bits on port
#define GIO_GET(port, bits)              ((port->PORT) & (bits))		//return bits on port
#define GIO_OUT(port, bits)              port->TRIS &=~(bits)			//set bits as output
#define GIO_IN(port, bits)               port->TRIS |= (bits)			//set bits as input

//fast port operations
#define FIO_SET(port, bits)              port->LATSET = (bits)			//set bits on port
#define FIO_CLR(port, bits)              port->LATCLR = (bits)			//clear bits on port
#define FIO_FLP(port, bits)              port->LATINV = (bits)			//flip bits on port
#define FIO_GET(port, bits)              ((port->PORT) & (bits))		//return bits on port
#define FIO_OUT(port, bits)              port->TRISCLR = (bits)			//set bits as output
#define FIO_IN(port, bits)               port->TRISSET = (bits)			//set bits as input

#define NOP()				Nop()                           //asm("nop")					//nop()
#define NOP2()				{NOP(); NOP();}
#define NOP4()				{NOP2(); NOP2();}
#define NOP8()				{NOP4(); NOP4();}
#define NOP16()				{NOP8(); NOP8();}
#define NOP16()				{NOP8(); NOP8();}
#define NOP24()				{NOP16(); NOP8();}
#define NOP32()				{NOP16(); NOP16();}
#define NOP40()				{NOP32(); NOP8();}
#define NOP64()				{NOP32(); NOP32();}

#define sleep()				asm("sleep")					//put the mcu into sleep

//default frequencies
//user specification
#ifndef F_XTAL
#define F_XTAL				25088000ul		//crystal frequency, user-specified
#endif
#ifndef F_SOSC
#define F_SOSC				32768			//SOSC = 32768Hz, user-specified
#endif
//end user specification
#define F_FRC				8000000			//FRC frequency = 8Mhz, fixed
#define F_LPRC				31250			//LPRC frequency = 31.25K, fixed

//to safe time on F_CPU
extern volatile uint32_t 	SystemCoreClock;			//updated by sysclk_get()
#define F_CPU				(SystemCoreClock)			//cpu runs at 8Mhz/2 by default -> Fxtal = 8Mhz - can be updated by _F_CPU
//#define F_CPU				(_F_CPU)		//updated by _F_CPU
#define F_PHB				(F_CPU / 8)		//peripheral block runs at F_PB - default = F_CPU / 8
#define SystemCoreClockUpdate()	sysclk_get()

//reset the mcu
void mcu_init(void);                    					//reset the mcu

//void (*mcu_reset)(void) = 0x0000; 						//jump to 0x0000 -> software reset

#ifndef ei
#define ei()				asm volatile ("ei")				//__builtin_enable_interrupts()	//do {INTEnableInterrupts();	INTEnableSystemMultiVectoredInt();} while (0)	//__builtin_enable_interrupts()
#endif

#ifndef di
#define di()				asm volatile ("di")				//__builtin_enable_interrupts()	//INTDisableInterrupts()			//__builtin_disable_interrupts()	//
#endif

//unlock IOLOCK
#define IO_UNLOCK()	{asm volatile ( "MOV #OSCCON, w1 \n" \
					"MOV #0x46, w2 \n" \
					"MOV #0x57, w3 \n" \
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
//PPS input pins

//group 1
#define PPS_INT4_TO_RPA0()		INT4R = 0
#define PPS_INT4_TO_RPB3()		INT4R = 1
#define PPS_INT4_TO_RPB4()		INT4R = 2
#define PPS_INT4_TO_RPB15()		INT4R = 3
#define PPS_INT4_TO_RPB7()		INT4R = 4
#define PPS_INT4_TO_RPC7()		INT4R = 5
#define PPS_INT4_TO_RPC0()		INT4R = 6
#define PPS_INT4_TO_RPC5()		INT4R = 7

#define PPS_T2CK_TO_RPA0()		T2CKR = 0
#define PPS_T2CK_TO_RPB3()		T2CKR = 1
#define PPS_T2CK_TO_RPB4()		T2CKR = 2
#define PPS_T2CK_TO_RPB15()		T2CKR = 3
#define PPS_T2CK_TO_RPB7()		T2CKR = 4
#define PPS_T2CK_TO_RPC7()		T2CKR = 5
#define PPS_T2CK_TO_RPC0()		T2CKR = 6
#define PPS_T2CK_TO_RPC5()		T2CKR = 7

#define PPS_IC4_TO_RPA0()		IC4R = 0
#define PPS_IC4_TO_RPB3()		IC4R = 1
#define PPS_IC4_TO_RPB4()		IC4R = 2
#define PPS_IC4_TO_RPB15()		IC4R = 3
#define PPS_IC4_TO_RPB7()		IC4R = 4
#define PPS_IC4_TO_RPC7()		IC4R = 5
#define PPS_IC4_TO_RPC0()		IC4R = 6
#define PPS_IC4_TO_RPC5()		IC4R = 7

#define PPS_SS1_TO_RPA0()		SS1R = 0
#define PPS_SS1_TO_RPB3()		SS1R = 1
#define PPS_SS1_TO_RPB4()		SS1R = 2
#define PPS_SS1_TO_RPB15()		SS1R = 3
#define PPS_SS1_TO_RPB7()		SS1R = 4
#define PPS_SS1_TO_RPC7()		SS1R = 5
#define PPS_SS1_TO_RPC0()		SS1R = 6
#define PPS_SS1_TO_RPC5()		SS1R = 7

#define PPS_REFCLKI_TO_RPA0()		REFCLKIR = 0
#define PPS_REFCLKI_TO_RPB3()		REFCLKIR = 1
#define PPS_REFCLKI_TO_RPB4()		REFCLKIR = 2
#define PPS_REFCLKI_TO_RPB15()		REFCLKIR = 3
#define PPS_REFCLKI_TO_RPB7()		REFCLKIR = 4
#define PPS_REFCLKI_TO_RPC7()		REFCLKIR = 5
#define PPS_REFCLKI_TO_RPC0()		REFCLKIR = 6
#define PPS_REFCLKI_TO_RPC5()		REFCLKIR = 7


//group 2
#define PPS_INT3_TO_RPA1()		INT3R = 0
#define PPS_INT3_TO_RPB5()		INT3R = 1
#define PPS_INT3_TO_RPB1()		INT3R = 2
#define PPS_INT3_TO_RPB11()		INT3R = 3
#define PPS_INT3_TO_RPB8()		INT3R = 4
#define PPS_INT3_TO_RPA8()		INT3R = 5
#define PPS_INT3_TO_RPC8()		INT3R = 6
#define PPS_INT3_TO_RPA9()		INT3R = 7


#define PPS_T3CK_TO_RPA1()		T3CKR = 0
#define PPS_T3CK_TO_RPB5()		T3CKR = 1
#define PPS_T3CK_TO_RPB1()		T3CKR = 2
#define PPS_T3CK_TO_RPB11()		T3CKR = 3
#define PPS_T3CK_TO_RPB8()		T3CKR = 4
#define PPS_T3CK_TO_RPA8()		T3CKR = 5
#define PPS_T3CK_TO_RPC8()		T3CKR = 6
#define PPS_T3CK_TO_RPA9()		T3CKR = 7

#define PPS_IC3_TO_RPA1()		IC3R = 0
#define PPS_IC3_TO_RPB5()		IC3R = 1
#define PPS_IC3_TO_RPB1()		IC3R = 2
#define PPS_IC3_TO_RPB11()		IC3R = 3
#define PPS_IC3_TO_RPB8()		IC3R = 4
#define PPS_IC3_TO_RPA8()		IC3R = 5
#define PPS_IC3_TO_RPC8()		IC3R = 6
#define PPS_IC3_TO_RPA9()		IC3R = 7

#define PPS_U1CTS_TO_RPA1()		U1CTSR = 0
#define PPS_U1CTS_TO_RPB5()		U1CTSR = 1
#define PPS_U1CTS_TO_RPB1()		U1CTSR = 2
#define PPS_U1CTS_TO_RPB11()		U1CTSR = 3
#define PPS_U1CTS_TO_RPB8()		U1CTSR = 4
#define PPS_U1CTS_TO_RPA8()		U1CTSR = 5
#define PPS_U1CTS_TO_RPC8()		U1CTSR = 6
#define PPS_U1CTS_TO_RPA9()		U1CTSR = 7

#define PPS_U2RX_TO_RPA1()		U2RXR = 0
#define PPS_U2RX_TO_RPB5()		U2RXR = 1
#define PPS_U2RX_TO_RPB1()		U2RXR = 2
#define PPS_U2RX_TO_RPB11()		U2RXR = 3
#define PPS_U2RX_TO_RPB8()		U2RXR = 4
#define PPS_U2RX_TO_RPA8()		U2RXR = 5
#define PPS_U2RX_TO_RPC8()		U2RXR = 6
#define PPS_U2RX_TO_RPA9()		U2RXR = 7

#define PPS_SDI1_TO_RPA1()		SDI1R = 0
#define PPS_SDI1_TO_RPB5()		SDI1R = 1
#define PPS_SDI1_TO_RPB1()		SDI1R = 2
#define PPS_SDI1_TO_RPB11()		SDI1R = 3
#define PPS_SDI1_TO_RPB8()		SDI1R = 4
#define PPS_SDI1_TO_RPA8()		SDI1R = 5
#define PPS_SDI1_TO_RPC8()		SDI1R = 6
#define PPS_SDI1_TO_RPA9()		SDI1R = 7


//group 3
#define PPS_INT2_TO_RPA2()		INT2R = 0
#define PPS_INT2_TO_RPB6()		INT2R = 1
#define PPS_INT2_TO_RPA4()		INT2R = 2
#define PPS_INT2_TO_RPB13()		INT2R = 3
#define PPS_INT2_TO_RPB2()		INT2R = 4
#define PPS_INT2_TO_RPC6()		INT2R = 5
#define PPS_INT2_TO_RPC1()		INT2R = 6
#define PPS_INT2_TO_RPA3()		INT2R = 7


#define PPS_T4CK_TO_RPA2()		T4CKR = 0
#define PPS_T4CK_TO_RPB6()		T4CKR = 1
#define PPS_T4CK_TO_RPA4()		T4CKR = 2
#define PPS_T4CK_TO_RPB13()		T4CKR = 3
#define PPS_T4CK_TO_RPB2()		T4CKR = 4
#define PPS_T4CK_TO_RPC6()		T4CKR = 5
#define PPS_T4CK_TO_RPC1()		T4CKR = 6
#define PPS_T4CK_TO_RPA3()		T4CKR = 7

#define PPS_IC1_TO_RPA2()		IC1R = 0
#define PPS_IC1_TO_RPB6()		IC1R = 1
#define PPS_IC1_TO_RPA4()		IC1R = 2
#define PPS_IC1_TO_RPB13()		IC1R = 3
#define PPS_IC1_TO_RPB2()		IC1R = 4
#define PPS_IC1_TO_RPC6()		IC1R = 5
#define PPS_IC1_TO_RPC1()		IC1R = 6
#define PPS_IC1_TO_RPA3()		IC1R = 7

#define PPS_IC5_TO_RPA2()		IC5R = 0
#define PPS_IC5_TO_RPB6()		IC5R = 1
#define PPS_IC5_TO_RPA4()		IC5R = 2
#define PPS_IC5_TO_RPB13()		IC5R = 3
#define PPS_IC5_TO_RPB2()		IC5R = 4
#define PPS_IC5_TO_RPC6()		IC5R = 5
#define PPS_IC5_TO_RPC1()		IC5R = 6
#define PPS_IC5_TO_RPA3()		IC5R = 7

#define PPS_U1RX_TO_RPA2()		U1RXR = 0
#define PPS_U1RX_TO_RPB6()		U1RXR = 1
#define PPS_U1RX_TO_RPA4()		U1RXR = 2
#define PPS_U1RX_TO_RPB13()		U1RXR = 3
#define PPS_U1RX_TO_RPB2()		U1RXR = 4
#define PPS_U1RX_TO_RPC6()		U1RXR = 5
#define PPS_U1RX_TO_RPC1()		U1RXR = 6
#define PPS_U1RX_TO_RPA3()		U1RXR = 7

#define PPS_U2CTS_TO_RPA2()		U2CTSR = 0
#define PPS_U2CTS_TO_RPB6()		U2CTSR = 1
#define PPS_U2CTS_TO_RPA4()		U2CTSR = 2
#define PPS_U2CTS_TO_RPB13()		U2CTSR = 3
#define PPS_U2CTS_TO_RPB2()		U2CTSR = 4
#define PPS_U2CTS_TO_RPC6()		U2CTSR = 5
#define PPS_U2CTS_TO_RPC1()		U2CTSR = 6
#define PPS_U2CTS_TO_RPA3()		U2CTSR = 7

#define PPS_SDI2_TO_RPA2()		SDI2R = 0
#define PPS_SDI2_TO_RPB6()		SDI2R = 1
#define PPS_SDI2_TO_RPA4()		SDI2R = 2
#define PPS_SDI2_TO_RPB13()		SDI2R = 3
#define PPS_SDI2_TO_RPB2()		SDI2R = 4
#define PPS_SDI2_TO_RPC6()		SDI2R = 5
#define PPS_SDI2_TO_RPC1()		SDI2R = 6
#define PPS_SDI2_TO_RPA3()		SDI2R = 7

#define PPS_OCFB_TO_RPA2()		OCFBR = 0
#define PPS_OCFB_TO_RPB6()		OCFBR = 1
#define PPS_OCFB_TO_RPA4()		OCFBR = 2
#define PPS_OCFB_TO_RPB13()		OCFBR = 3
#define PPS_OCFB_TO_RPB2()		OCFBR = 4
#define PPS_OCFB_TO_RPC6()		OCFBR = 5
#define PPS_OCFB_TO_RPC1()		OCFBR = 6
#define PPS_OCFB_TO_RPA3()		OCFBR = 7

//group 4
#define PPS_INT1_TO_RPA3()		INT1R = 0
#define PPS_INT1_TO_RPB14()		INT1R = 1
#define PPS_INT1_TO_RPB0()		INT1R = 2
#define PPS_INT1_TO_RPB10()		INT1R = 3
#define PPS_INT1_TO_RPB9()		INT1R = 4
#define PPS_INT1_TO_RPC9()		INT1R = 5
#define PPS_INT1_TO_RPC2()		INT1R = 6
#define PPS_INT1_TO_RPC4()		INT1R = 7

#define PPS_T5CK_TO_RPA3()		T5CKR = 0
#define PPS_T5CK_TO_RPB14()		T5CKR = 1
#define PPS_T5CK_TO_RPB0()		T5CKR = 2
#define PPS_T5CK_TO_RPB10()		T5CKR = 3
#define PPS_T5CK_TO_RPB9()		T5CKR = 4
#define PPS_T5CK_TO_RPC9()		T5CKR = 5
#define PPS_T5CK_TO_RPC2()		T5CKR = 6
#define PPS_T5CK_TO_RPC4()		T5CKR = 7

#define PPS_IC2_TO_RPA3()		IC2R = 0
#define PPS_IC2_TO_RPB14()		IC2R = 1
#define PPS_IC2_TO_RPB0()		IC2R = 2
#define PPS_IC2_TO_RPB10()		IC2R = 3
#define PPS_IC2_TO_RPB9()		IC2R = 4
#define PPS_IC2_TO_RPC9()		IC2R = 5
#define PPS_IC2_TO_RPC2()		IC2R = 6
#define PPS_IC2_TO_RPC4()		IC2R = 7

#define PPS_SS2_TO_RPA3()		SS2R = 0
#define PPS_SS2_TO_RPB14()		SS2R = 1
#define PPS_SS2_TO_RPB0()		SS2R = 2
#define PPS_SS2_TO_RPB10()		SS2R = 3
#define PPS_SS2_TO_RPB9()		SS2R = 4
#define PPS_SS2_TO_RPC9()		SS2R = 5
#define PPS_SS2_TO_RPC2()		SS2R = 6
#define PPS_SS2_TO_RPC4()		SS2R = 7

#define PPS_OCFA_TO_RPA3()		OCFAR = 0
#define PPS_OCFA_TO_RPB14()		OCFAR = 1
#define PPS_OCFA_TO_RPB0()		OCFAR = 2
#define PPS_OCFA_TO_RPB10()		OCFAR = 3
#define PPS_OCFA_TO_RPB9()		OCFAR = 4
#define PPS_OCFA_TO_RPC9()		OCFAR = 5
#define PPS_OCFA_TO_RPC2()		OCFAR = 6
#define PPS_OCFA_TO_RPC4()		OCFAR = 7

//PPS output pins
//group 1
#define PPS_RPA0_TO_NC()		RPA0R = 0
#define PPS_RPA0_TO_U1TX()		RPA0R = 1
#define PPS_RPA0_TO_U2RTS()		RPA0R = 2
#define PPS_RPA0_TO_SS1()		RPA0R = 3
#define PPS_RPA0_TO_OC1()		RPA0R = 0b0101
#define PPS_RPA0_TO_C2OUT()		RPA0R = 0b0111

#define PPS_RPB3_TO_NC()		RPB3R = 0
#define PPS_RPB3_TO_U1TX()		RPB3R = 1
#define PPS_RPB3_TO_U2RTS()		RPB3R = 2
#define PPS_RPB3_TO_SS1()		RPB3R = 3
#define PPS_RPB3_TO_OC1()		RPB3R = 0b0101
#define PPS_RPB3_TO_C2OUT()		RPB3R = 0b0111

#define PPS_RPB4_TO_NC()		RPB4R = 0
#define PPS_RPB4_TO_U1TX()		RPB4R = 1
#define PPS_RPB4_TO_U2RTS()		RPB4R = 2
#define PPS_RPB4_TO_SS1()		RPB4R = 3
#define PPS_RPB4_TO_OC1()		RPB4R = 0b0101
#define PPS_RPB4_TO_C2OUT()		RPB4R = 0b0111

#define PPS_RPB15_TO_NC()		RPB15R = 0
#define PPS_RPB15_TO_U1TX()		RPB15R = 1
#define PPS_RPB15_TO_U2RTS()		RPB15R = 2
#define PPS_RPB15_TO_SS1()		RPB15R = 3
#define PPS_RPB15_TO_OC1()		RPB15R = 0b0101
#define PPS_RPB15_TO_C2OUT()		RPB15R = 0b0111

#define PPS_RPB7_TO_NC()		RPB7R = 0
#define PPS_RPB7_TO_U1TX()		RPB7R = 1
#define PPS_RPB7_TO_U2RTS()		RPB7R = 2
#define PPS_RPB7_TO_SS1()		RPB7R = 3
#define PPS_RPB7_TO_OC1()		RPB7R = 0b0101
#define PPS_RPB7_TO_C2OUT()		RPB7R = 0b0111

#define PPS_RPC7_TO_NC()		RPC7R = 0
#define PPS_RPC7_TO_U1TX()		RPC7R = 1
#define PPS_RPC7_TO_U2RTS()		RPC7R = 2
#define PPS_RPC7_TO_SS1()		RPC7R = 3
#define PPS_RPC7_TO_OC1()		RPC7R = 0b0101
#define PPS_RPC7_TO_C2OUT()		RPC7R = 0b0111

#define PPS_RPC0_TO_NC()		RPC0R = 0
#define PPS_RPC0_TO_U1TX()		RPC0R = 1
#define PPS_RPC0_TO_U2RTS()		RPC0R = 2
#define PPS_RPC0_TO_SS1()		RPC0R = 3
#define PPS_RPC0_TO_OC1()		RPC0R = 0b0101
#define PPS_RPC0_TO_C2OUT()		RPC0R = 0b0111

#define PPS_RPC5_TO_NC()		RPC5R = 0
#define PPS_RPC5_TO_U1TX()		RPC5R = 1
#define PPS_RPC5_TO_U2RTS()		RPC5R = 2
#define PPS_RPC5_TO_SS1()		RPC5R = 3
#define PPS_RPC5_TO_OC1()		RPC5R = 0b0101
#define PPS_RPC5_TO_C2OUT()		RPC5R = 0b0111


//group 2
#define PPS_RPA1_TO_NC()		RPA1R = 0
#define PPS_RPA1_TO_SDO1()		RPA1R = 0b0011
#define PPS_RPA1_TO_SDO2()		RPA1R = 0b0100
#define PPS_RPA1_TO_OC2()		RPA1R = 0b0101
#define PPS_RPA1_TO_C3OUT()		RPA1R = 0b0111

#define PPS_RPB5_TO_NC()		RPB5R = 0
#define PPS_RPB5_TO_SDO1()		RPB5R = 0b0011
#define PPS_RPB5_TO_SDO2()		RPB5R = 0b0100
#define PPS_RPB5_TO_OC2()		RPB5R = 0b0101
#define PPS_RPB5_TO_C3OUT()		RPB5R = 0b0111

#define PPS_RPB1_TO_NC()		RPB1R = 0
#define PPS_RPB1_TO_SDO1()		RPB1R = 0b0011
#define PPS_RPB1_TO_SDO2()		RPB1R = 0b0100
#define PPS_RPB1_TO_OC2()		RPB1R = 0b0101
#define PPS_RPB1_TO_C3OUT()		RPB1R = 0b0111

#define PPS_RPB11_TO_NC()		RPB11R = 0
#define PPS_RPB11_TO_SDO1()		RPB11R = 0b0011
#define PPS_RPB11_TO_SDO2()		RPB11R = 0b0100
#define PPS_RPB11_TO_OC2()		RPB11R = 0b0101
#define PPS_RPB11_TO_C3OUT()		RPB11R = 0b0111

#define PPS_RPB8_TO_NC()		RPB8R = 0
#define PPS_RPB8_TO_SDO1()		RPB8R = 0b0011
#define PPS_RPB8_TO_SDO2()		RPB8R = 0b0100
#define PPS_RPB8_TO_OC2()		RPB8R = 0b0101
#define PPS_RPB8_TO_C3OUT()		RPB8R = 0b0111

#define PPS_RPA8_TO_NC()		RPA8R = 0
#define PPS_RPA8_TO_SDO1()		RPA8R = 0b0011
#define PPS_RPA8_TO_SDO2()		RPA8R = 0b0100
#define PPS_RPA8_TO_OC2()		RPA8R = 0b0101
#define PPS_RPA8_TO_C3OUT()		RPA8R = 0b0111

#define PPS_RPC8_TO_NC()		RPC8R = 0
#define PPS_RPC8_TO_SDO1()		RPC8R = 0b0011
#define PPS_RPC8_TO_SDO2()		RPC8R = 0b0100
#define PPS_RPC8_TO_OC2()		RPC8R = 0b0101
#define PPS_RPC8_TO_C3OUT()		RPA1R = 0b0111

#define PPS_RPA9_TO_NC()		RPA9R = 0
#define PPS_RPA9_TO_SDO1()		RPA9R = 0b0011
#define PPS_RPA9_TO_SDO2()		RPA9R = 0b0100
#define PPS_RPA9_TO_OC2()		RPA9R = 0b0101
#define PPS_RPA9_TO_C3OUT()		RPA9R = 0b0111


//group 3
#define PPS_RPA2_TO_NC()		RPA2R = 0
#define PPS_RPA2_TO_SDO1()		RPA2R = 0b0011
#define PPS_RPA2_TO_SDO2()		RPA2R = 0b0100
#define PPS_RPA2_TO_OC4()		RPA2R = 0b0101
#define PPS_RPA2_TO_OC5()		RPA2R = 0b0110
#define PPS_RPA2_TO_REFCLKO()		RPA2R = 0b0111

#define PPS_RPB6_TO_NC()		RPB6R = 0
#define PPS_RPB6_TO_SDO1()		RPB6R = 0b0011
#define PPS_RPB6_TO_SDO2()		RPB6R = 0b0100
#define PPS_RPB6_TO_OC4()		RPB6R = 0b0101
#define PPS_RPB6_TO_OC5()		RPB6R = 0b0110
#define PPS_RPB6_TO_REFCLKO()	RPB6R = 0b0111

#define PPS_RPA4_TO_NC()		RPA4R = 0
#define PPS_RPA4_TO_SDO1()		RPA4R = 0b0011
#define PPS_RPA4_TO_SDO2()		RPA4R = 0b0100
#define PPS_RPA4_TO_OC4()		RPA4R = 0b0101
#define PPS_RPA4_TO_OC5()		RPA4R = 0b0110
#define PPS_RPA4_TO_REFCLKO()		RPA4R = 0b0111

#define PPS_RPB13_TO_NC()		RPB13R = 0
#define PPS_RPB13_TO_SDO1()		RPB13R = 0b0011
#define PPS_RPB13_TO_SDO2()		RPB13R = 0b0100
#define PPS_RPB13_TO_OC4()		RPB13R = 0b0101
#define PPS_RPB13_TO_OC5()		RPB13R = 0b0110
#define PPS_RPB13_TO_REFCLKO()		RPB13R = 0b0111

#define PPS_RPB2_TO_NC()		RPB2R = 0
#define PPS_RPB2_TO_SDO1()		RPB2R = 0b0011
#define PPS_RPB2_TO_SDO2()		RPB2R = 0b0100
#define PPS_RPB2_TO_OC4()		RPB2R = 0b0101
#define PPS_RPB2_TO_OC5()		RPB2R = 0b0110
#define PPS_RPB2_TO_REFCLKO()		RPB2R = 0b0111

#define PPS_RPC6_TO_NC()		RPC6R = 0
#define PPS_RPC6_TO_SDO1()		RPC6R = 0b0011
#define PPS_RPC6_TO_SDO2()		RPC6R = 0b0100
#define PPS_RPC6_TO_OC4()		RPC6R = 0b0101
#define PPS_RPC6_TO_OC5()		RPC6R = 0b0110
#define PPS_RPC6_TO_REFCLKO()		RPC6R = 0b0111

#define PPS_RPC1_TO_NC()		RPC1R = 0
#define PPS_RPC1_TO_SDO1()		RPC1R = 0b0011
#define PPS_RPC1_TO_SDO2()		RPC1R = 0b0100
#define PPS_RPC1_TO_OC4()		RPC1R = 0b0101
#define PPS_RPC1_TO_OC5()		RPC1R = 0b0110
#define PPS_RPC1_TO_REFCLKO()		RPC1R = 0b0111

#define PPS_RPC3_TO_NC()		RPC3R = 0
#define PPS_RPC3_TO_SDO1()		RPC3R = 0b0011
#define PPS_RPC3_TO_SDO2()		RPC3R = 0b0100
#define PPS_RPC3_TO_OC4()		RPC3R = 0b0101
#define PPS_RPC3_TO_OC5()		RPC3R = 0b0110
#define PPS_RPC3_TO_REFCLKO()		RPC3R = 0b0111

//group 4
#define PPS_RPA3_TO_NC()		RPA3R = 0
#define PPS_RPA3_TO_U1RTS()		RPA3R = 0b0001
#define PPS_RPA3_TO_U2TX()		RPA3R = 0b0010
#define PPS_RPA3_TO_SS2()		RPA3R = 0b0100
#define PPS_RPA3_TO_OC3()		RPA3R = 0b0101
#define PPS_RPA3_TO_C1OUT()		RPA3R = 0b0111

#define PPS_RPB14_TO_NC()		RPB14R = 0
#define PPS_RPB14_TO_U1RTS()		RPB14R = 0b0001
#define PPS_RPB14_TO_U2TX()		RPB14R = 0b0010
#define PPS_RPB14_TO_SS2()		RPB14R = 0b0100
#define PPS_RPB14_TO_OC3()		RPB14R = 0b0101
#define PPS_RPB14_TO_C1OUT()		RPB14R = 0b0111

#define PPS_RPB0_TO_NC()		RPB0R = 0
#define PPS_RPB0_TO_U1RTS()		RPB0R = 0b0001
#define PPS_RPB0_TO_U2TX()		RPB0R = 0b0010
#define PPS_RPB0_TO_SS2()		RPB0R = 0b0100
#define PPS_RPB0_TO_OC3()		RPB0R = 0b0101
#define PPS_RPB0_TO_C1OUT()		RPB0R = 0b0111

#define PPS_RPB10_TO_NC()		RPB10R = 0
#define PPS_RPB10_TO_U1RTS()		RPB10R = 0b0001
#define PPS_RPB10_TO_U2TX()		RPB10R = 0b0010
#define PPS_RPB10_TO_SS2()		RPB10R = 0b0100
#define PPS_RPB10_TO_OC3()		RPB10R = 0b0101
#define PPS_RPB10_TO_C1OUT()		RPB10R = 0b0111

#define PPS_RPB9_TO_NC()		RPB9R = 0
#define PPS_RPB9_TO_U1RTS()		RPB9R = 0b0001
#define PPS_RPB9_TO_U2TX()		RPB9R = 0b0010
#define PPS_RPB9_TO_SS2()		RPB9R = 0b0100
#define PPS_RPB9_TO_OC3()		RPB9R = 0b0101
#define PPS_RPB9_TO_C1OUT()		RPB9R = 0b0111

#define PPS_RPC9_TO_NC()		RPC9R = 0
#define PPS_RPC9_TO_U1RTS()		RPC9R = 0b0001
#define PPS_RPC9_TO_U2TX()		RPC9R = 0b0010
#define PPS_RPC9_TO_SS2()		RPC9R = 0b0100
#define PPS_RPC9_TO_OC3()		RPC9R = 0b0101
#define PPS_RPC9_TO_C1OUT()		RPC9R = 0b0111

#define PPS_RPC2_TO_NC()		RPC2R = 0
#define PPS_RPC2_TO_U1RTS()		RPC2R = 0b0001
#define PPS_RPC2_TO_U2TX()		RPC2R = 0b0010
#define PPS_RPC2_TO_SS2()		RPC2R = 0b0100
#define PPS_RPC2_TO_OC3()		RPC2R = 0b0101
#define PPS_RPC2_TO_C1OUT()		RPC2R = 0b0111

#define PPS_RPC4_TO_NC()		RPC4R = 0
#define PPS_RPC4_TO_U1RTS()		RPC4R = 0b0001
#define PPS_RPC4_TO_U2TX()		RPC4R = 0b0010
#define PPS_RPC4_TO_SS2()		RPC4R = 0b0100
#define PPS_RPC4_TO_OC3()		RPC4R = 0b0101
#define PPS_RPC4_TO_C1OUT()		RPC4R = 0b0111

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

typedef struct {
    volatile uint32_t TRIS;             //data direction register -> 0ffset 0x0000, little endian
    //volatile uint32_t RESERVED0[3];     //fill the space
    volatile uint32_t TRISCLR;          //set to clear
    volatile uint32_t TRISSET;          //set to set
    volatile uint32_t TRISINV;          //set to flip
    volatile uint32_t PORT;             //input data register
    volatile uint32_t RESERVED1[3];     //fill the space
    volatile uint32_t LAT;              //output data register
    //volatile uint32_t RESERVED2[3];     //fill the space
    volatile uint32_t LATCLR;          //set to clear
    volatile uint32_t LATSET;          //set to set
    volatile uint32_t LATINV;          //set to flip
    volatile uint32_t ODC;              //open drain configuration register. set to activate open drain
    //volatile uint32_t RESERVED3[3];     //fill the space

} GPIO_TypeDef;                          //port definition registers

#define GPIOA                           ((GPIO_TypeDef *) &TRISA)
#define GPIOB                           ((GPIO_TypeDef *) &TRISB)
#define GPIOC                           ((GPIO_TypeDef *) &TRISC)
#define GPIOD                           ((GPIO_TypeDef *) &TRISD)
#define GPIOE                           ((GPIO_TypeDef *) &TRISE)
#define GPIOF                           ((GPIO_TypeDef *) &TRISF)
#define GPIOG                           ((GPIO_TypeDef *) &TRISG)

//pre-requisite: FCKSM = CSECMD.
//NOSC bits 10..8
#define CLKNOSC_FRCDIV		(0b111 << 8)	//clock source = frc/
#define CLKNOSC_FRC16		(0b110 << 8)	//clock source = frc/16
#define CLKNOSC_LPRC		(0b101 << 8)	//clock source = lprc
#define CLKNOSC_SOSC		(0b100 << 8)	//clock source = sosc
#define CLKNOSC_POSCPLL		(0b011 << 8)	//clock source = hs, xt, ec + PLL
#define CLKNOSC_POSC		(0b010 << 8)	//clock source = hs, xt, ec
#define CLKNOSC_FRCPLL		(0b001 << 8)	//clock source = frc + PLL
#define CLKNOSC_FRC			(0b000 << 8)	//clock source = frc

//COSC bits 14..12
#define CLKCOSC_FRCDIV		(0b111 << 12)	//clock source = frc/
#define CLKCOSC_FRC16		(0b110 << 12)	//clock source = frc/16
#define CLKCOSC_LPRC		(0b101 << 12)	//clock source = lprc
#define CLKCOSC_SOSC		(0b100 << 12)	//clock source = sosc
#define CLKCOSC_POSCPLL		(0b011 << 12)	//clock source = hs, xt, ec + PLL
#define CLKCOSC_POSC		(0b010 << 12)	//clock source = hs, xt, ec
#define CLKCOSC_FRCPLL		(0b001 << 12)	//clock source = frc + PLL
#define CLKCOSC_FRC			(0b000 << 12)	//clock source = frc

//CLK FRCDIV bit 26..24
#define CLKFRCDIV_256		(0b111 << 24)	//frc divider = 256
#define CLKFRCDIV_64		(0b110 << 24)	//frc divider = 64
#define CLKFRCDIV_32		(0b101 << 24)	//frc divider = 32
#define CLKFRCDIV_16		(0b100 << 24)	//frc divider = 16
#define CLKFRCDIV_8			(0b011 << 24)	//frc divider = 8
#define CLKFRCDIV_4			(0b010 << 24)	//frc divider = 4
#define CLKFRCDIV_2			(0b001 << 24)	//frc divider = 2
#define CLKFRCDIV_1			(0b000 << 24)	//frc divider = 1

//CLK PLLDIV bit 29..27
#define CLKPLLDIV_256		(0b111 << 27)	//frc divider = 256
#define CLKPLLDIV_64		(0b110 << 27)	//frc divider = 64
#define CLKPLLDIV_32		(0b101 << 27)	//frc divider = 32
#define CLKPLLDIV_16		(0b100 << 27)	//frc divider = 16
#define CLKPLLDIV_8			(0b011 << 27)	//frc divider = 8
#define CLKPLLDIV_4			(0b010 << 27)	//frc divider = 4
#define CLKPLLDIV_2			(0b001 << 27)	//frc divider = 2
#define CLKPLLDIV_1			(0b000 << 27)	//frc divider = 1

//CLK PLLMULT bit 18..16
#define CLKPLLMULT_24		(0b111 << 16)	//frc divider = 256
#define CLKPLLMULT_21		(0b110 << 16)	//frc divider = 64
#define CLKPLLMULT_20		(0b101 << 16)	//frc divider = 32
#define CLKPLLMULT_19		(0b100 << 16)	//frc divider = 16
#define CLKPLLMULT_18		(0b011 << 16)	//frc divider = 8
#define CLKPLLMULT_17		(0b010 << 16)	//frc divider = 4
#define CLKPLLMULT_16		(0b001 << 16)	//frc divider = 2
#define CLKPLLMULT_15		(0b000 << 16)	//frc divider = 1

//switch clock
void sysclk_set(uint32_t tgt_clk);

//read sysclock back
uint32_t sysclk_get(void);
//switch reference clock
//tgt_clk: use REFOSC_ and REFODIV() macros
//pllotrim: use REFOTRIM() macros
void refclk_set(uint32_t tgt_clk,uint32_t pllotrim);

#define REFOSC_REFCLKI		(0b1001 << 0)	//REFCLKI
#define REFOSC_SYSPLLO		(0b1000 << 0)	//SYStem PLL
#define REFOSC_USBPLLO		(0b0111 << 0)	//USB PLL
#define REFOSC_SOSC			(0b0101 << 0)	//Secondary OSC
#define REFOSC_LPRC			(0b0100 << 0)	//LPRC
#define REFOSC_FRC			(0b0011 << 0)	//FRC
#define REFOSC_POSC			(0b0010 << 0)	//Primary osc
#define REFOSC_PBCLK		(0b0001 << 0)	//pbclk
#define REFOSC_SYSCLK		(0b0000 << 0)	//sysclk
#define REFOSC_ON			(1<<15)			//1=turn on REFOSCC
#define REFOSC_OE			(1<<12)			//1=output enable

#define REFODIV(div)		(((div) & 0x7fff) << 16)
#define REFOTRIM(trim)		(((trim) & 0x01ff) << 23)
#endif //gpio_h_
