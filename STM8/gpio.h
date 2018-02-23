#ifndef __GPIO_H
#define __GPIO_H

//#include "stdint.h"
#include "stm8s.h"								//we use stm8s
//#include "iostm8.h"							//for interrupt tables - reproduced below
//#include "stm8s_clk.h"						//set we clocks
//#include "stm8s_conf.h"						//configuration file

//port-related macros for stm8s
//DEFAULT: OPEN DRAIN OUTPUT
//set Px_CR1 and clear Px_CR2 to turn to push_pull output

//port/gpio oriented macros
#define IO_SET(port, pins)					port->ODR |= (pins)				//set bits on port
#define IO_CLR(port, pins)					port->ODR &=~(pins)				//clear bits on port
#define IO_FLP(port, pins)					port->ODR ^= (pins)				//flip bits on port
#define IO_GET(port, pins)					((port->IDR) & (pins))			//return bits on port
//set a pin to output/input
#define IO_OUTPP(port, pins)				do {port->DDR |= (pins); port->CR1 |= (pins); port->CR2 &=~(pins);} while (0)	//push-pull mode (CR1 set, CR2 cleared)	//IO_OUTPP(GPIOx, GPIO_Pins).
#define IO_OUT(port, pins)					IO_OUTPP(port, pins)				//_GPIO_Init(GPIOx, GPIO_Pins, GPIO_MODE_OUT_PP_LOW_FAST)
#define IO_OUTOD(port, pins)				do {port->DDR |= (pins); port->CR1 &=~(pins); port->CR2 &=~(pins);} while (0)	//open drain mode (cr1 + cr2 cleared)	//_GPIO_Init(GPIOx, GPIO_Pins, GPIO_MODE_OUT_OD_LOW_FAST)
#define IO_INFL(port, pins)					do {port->DDR &=~(pins); port->CR1 &=~(pins); port->CR2 &=~(pins);} while (0)	//floating input, no interrupt			//IO_INFL(GPIOx, GPIO_Pins)
#define IO_IN(port, pins)					IO_IN(port, pins)					//IO_IN(port, pins)				//_GPIO_Init(GPIOx, GPIO_Pins, GPIO_MODE_IN_FL_NO_IT)
#define IO_INPU(port, pins)					do {port->DDR &=~(pins); port->CR1 |= (pins); port->CR2 &=~(pins);} while (0)	//pull-up, no interrupt					//_GPIO_Init(GPIOx, GPIO_Pins, GPIO_MODE_IN_PU_NO_IT)


//#define IO_OUT(ddr, bits)		ddr |= (bits)				//set bits as output. stm8s: sets a bit to make it an output
//#define IO_IN(ddr, bits)		ddr &=~(bits)				//set bits as input. stm8s: clears a bit to make it an input

//pin definitions - to be compatible with stm32f
#define GPIO_Pin_0				GPIO_PIN_0
#define GPIO_Pin_1				GPIO_PIN_1
#define GPIO_Pin_2				GPIO_PIN_2
#define GPIO_Pin_3				GPIO_PIN_3
#define GPIO_Pin_4				GPIO_PIN_4
#define GPIO_Pin_5				GPIO_PIN_5
#define GPIO_Pin_6				GPIO_PIN_6
#define GPIO_Pin_7				GPIO_PIN_7

#define NOP()         			nop()						//__no_operation()			//asm("nop")            		//nop
#define NOP2()					{NOP(); NOP();}
#define NOP4()					{NOP2(); NOP2();}
#define NOP8()					{NOP4(); NOP4();}
#define NOP16()					{NOP8(); NOP8();}
#define NOP16()					{NOP8(); NOP8();}
#define NOP24()					{NOP16(); NOP8();}
#define NOP32()					{NOP16(); NOP16();}
#define NOP40()					{NOP32(); NOP8();}
#define NOP64()					{NOP32(); NOP32();}

//initialize the beeper
#define beep_1Khz()				do {beep_init(BEEP_FREQUENCY_1KHZ); BEEP_Cmd(ENABLE);} while (0)	//turn on beeper to produce 1Khz
#define beep_2Khz()				do {beep_init(BEEP_FREQUENCY_2KHZ); BEEP_Cmd(ENABLE);} while (0)	//turn on beeper to produce 1Khz
#define beep_4Khz()				do {beep_init(BEEP_FREQUENCY_4KHZ); BEEP_Cmd(ENABLE);} while (0)	//turn on beeper to produce 1Khz
#define beep_init(freq) 		BEEP_Init(freq)			//initialize beeper
#define beep_on()				BEEP_Cmd(ENABLE)		//turn on beeper
#define beep_off()				BEEP_Cmd(DISABLE)		//turn off beeper

#ifndef ei
	#define ei()				enableInterrupts()			//asm("rim")					//enable all interrupts
#endif

#ifndef di
	#define di()				disableInterrupts()			//asm("sim")					//disable all interrupts
#endif
//#define __enable_interrupt()		ei()
//#define __disable_interrupt()		di()

//fmaster = 16Mhz / 8 -> 2Mhz
//fcpu = fmaster / 1 -> 2Mhz
extern volatile uint32_t 		SystemCoreClock;			//systemcoreclock
#define F_MASTER				(SystemCoreClock)			//fmaster -> default to hsi (16mhz), divided by 8
#define F_CPU					(SystemCoreClock / 1)			//fcpu

//define ld1 on stm8sdiscovery board
#define gLED_PORT				GPIOD						//PD_ODR
#define gLED_DDR					GPIOD						//PD_DDR
#define gLED						(1<<0)						//pd0 - green led on stm8s105c8 discovery board

//#define LED1_ON()  			IO_CLR(LED1_PORT, LED1)     //turn on the leds, assuming output mode
//#define LED1_OFF() 			IO_SET(LED1_PORT, LED1)     //turn off the leds, assuming output mode
//#define LED1_FLP()			IO_FLP(LED1_PORT, LED1)		//flip leds

#define CLK_PRESCALER_CPUDIV1			0x00					//cpu / 1
#define CLK_PRESCALER_CPUDIV2			0x01					//cpu / 2
#define CLK_PRESCALER_CPUDIV4			0x02					//cpu / 4
#define CLK_PRESCALER_CPUDIV8			0x03					//cpu / 8
#define CLK_PRESCALER_CPUDIV16			0x04					//cpu / 16
#define CLK_PRESCALER_CPUDIV32			0x05					//cpu / 32
#define CLK_PRESCALER_CPUDIV64			0x06					//cpu / 64
#define CLK_PRESCALER_CPUDIV128			0x07					//cpu / 128
#define CLK_PRESCALER_HSIDIV1			(0<<3)					//hsi divider 1:1
#define CLK_PRESCALER_HSIDIV2			(1<<3)					//hsi divider 2:1
#define CLK_PRESCALER_HSIDIV4			(2<<3)					//hsi divider 4:1
#define CLK_PRESCALER_HSIDIV8			(3<<3)					//hsi divider 8:1

//use hsi oscillator
void SystemCoreClockHSI(uint8_t CLK_HSIDIV);

//oscillator macros for HSI + dividers
//void SystemCoreClockHSE(/*CLK_Prescaler_TypeDef CLK_CPUDIV*/);		//running on external crystal / oscillator, specified in HSE_VALUE
//void SystemCoreClockHSI(CLK_Prescaler_TypeDef CLK_Prescaler);		//running on external crystal / oscillator, specified in HSE_VALUE
//void SystemCoreClockLSI(/*CLK_Prescaler_TypeDef CLK_CPUDIV*/);		//running on internal low speed oscillator, specified in LSI_VALUE(=128Khz)
#define SystemCoreClockHSI_16MHz()	SystemCoreClockHSI(CLK_PRESCALER_HSIDIV1)
#define SystemCoreClockHSI_8MHz()	SystemCoreClockHSI(CLK_PRESCALER_HSIDIV2)
#define SystemCoreClockHSI_4MHz()	SystemCoreClockHSI(CLK_PRESCALER_HSIDIV4)
#define SystemCoreClockHSI_2MHz()	SystemCoreClockHSI(CLK_PRESCALER_HSIDIV8)

//customized gpio_init() function that does not set / clear GPIOx->ODR registers
//void _GPIO_Init(GPIO_TypeDef* GPIOx, GPIO_Pin_TypeDef GPIO_Pin, GPIO_Mode_TypeDef GPIO_Mode);
void mcu_init(void);
	
//void (*mcu_reset)(void) = 0x0000; 						//jump to 0x0000 -> software reset

//unique IDs, read-only - STM8S003 has no unique IDs
//U_ID[0]: X coordinate
//U_ID[1]: Y coordinate
//U_ID[2]'s LSB: Wafer number
//U_ID[2]'s MSB -> U_ID[5]: Lot number
#if defined(STM8S003) || defined(STM8S103) || defined(STM8S903)
#define U_ID				((const uint16_t *) 0x4865)		//U_ID95..0, referenced via U_ID[0], ..., U_ID[5]
#elif defined(STM8S105) || defined(STM8S207)
#define U_ID				((const uint16_t *) 0x48CD)		//U_ID95..0, referenced via U_ID[0], ..., U_ID[5]
#else
#warning "U_ID not defined for the chip in gpio.h"			//warning message
#endif
#define U_ID0  	       		U_ID[0]							//X coordinate
#define U_ID1				U_ID[1]							//Y coordinate
#define U_ID2         		U_ID[2]							//LSB: wafer number; MSB: Lot number
#define U_ID3         		U_ID[3]							//Lot Number
#define U_ID4         		U_ID[4]							//Lot Number
#define U_ID5         		U_ID[5]							//Lot Number

//simple multiples
#define x1(val)				(val)							//multiply val by 1
#define x2(val)				(((val) << 1))					//multiply val by 2
#define x3(val)				(x2(val) + (val))				//multiply val by 3
#define x4(val)				(((val) << 2))					//multiply val by 4
#define x5(val)				(x4(val) + (val))				//multiply val by 5
#define x6(val)				(x4(val) + x2(val))				//multiply val by 6
#define x7(val)				(x6(val) + (val))				//multiply val by 7
#define x8(val)				((val) << 3)					//multiply val by 8
#define x9(val)				(x8(val) + (val))				//multiply val by 9

//multiples of 10s
#define x10(val)			(x8(val) + x2(val))				//multiply val by 10
#define x100(val)			(x10(x10(val)))					//multiply val by 100
#define x1000(val)			(x100(x10(val)))				//multiply val by 1000
#define x1k(val)			x1000(val)						//multiply val by 1000
#define x10k(val)			(x100(x100(val)))				//multiply val by 10000

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
#define x34(val)			(x30(val) + x4(val))			//multiply val by 34
#define x97(val)			(x90(val) + x7(val))			//multiply val by 97x

//interrupt from iostm8.h

/*-------------------------------------------------------------------------
 *      Interrupt vector numbers
 *-----------------------------------------------------------------------*/
#define AWU_vector                           0x03
#define CLK_CSS_vector                       0x04
#define CLK_SWITCH_vector                    0x04
#define beCAN_FMP_vector                     0x0A
#define beCAN_FULL_vector                    0x0A
#define beCAN_FOVR_vector                    0x0A
#define beCAN_EWGF_vector                    0x0B
#define beCAN_EPVF_vector                    0x0B
#define beCAN_BOFF_vector                    0x0B
#define beCAN_LEC0_vector                    0x0B
#define beCAN_LEC1_vector                    0x0B
#define beCAN_LEC2_vector                    0x0B
#define beCAN_RQCP0_vector                   0x0B
#define beCAN_RQCP1_vector                   0x0B
#define beCAN_RQCP2_vector                   0x0B
#define beCAN_WKUI_vector                    0x0B
#define SPI_TXE_vector                       0x0C
#define SPI_RXNE_vector                      0x0C
#define SPI_WKUP_vector                      0x0C
#define SPI_MODF_vector                      0x0C
#define SPI_OVR_vector                       0x0C
#define SPI_CRCERR_vector                    0x0C
#define TIM1_OVR_UIF_vector                  0x0D
#define TIM1_CAPCOM_BIF_vector               0x0D
#define TIM1_CAPCOM_TIF_vector               0x0D
#define TIM1_CAPCOM_CC1IF_vector             0x0E
#define TIM1_CAPCOM_CC2IF_vector             0x0E
#define TIM1_CAPCOM_CC3IF_vector             0x0E
#define TIM1_CAPCOM_CC4IF_vector             0x0E
#define TIM1_CAPCOM_COMIF_vector             0x0E
#define TIM2_OVR_UIF_vector                  0x0F
#define TIM2_CAPCOM_TIF_vector               0x10
#define TIM2_CAPCOM_CC1IF_vector             0x10
#define TIM2_CAPCOM_CC2IF_vector             0x10
#define TIM2_CAPCOM_CC3IF_vector             0x10
#define TIM3_OVR_UIF_vector                  0x11
#define TIM3_CAPCOM_TIF_vector               0x12
#define TIM3_CAPCOM_CC1IF_vector             0x12
#define TIM3_CAPCOM_CC2IF_vector             0x12
#define TIM3_CAPCOM_CC3IF_vector             0x12
#define UART1_T_TXE_vector                   0x13
#define UART1_T_TC_vector                    0x13
#define UART1_R_RXNE_vector                  0x14
#define UART1_R_OR_vector                    0x14
#define UART1_R_IDLE_vector                  0x14
#define UART1_R_PE_vector                    0x14
#define UART1_R_LBDF_vector                  0x14
#define I2C_SB_vector                        0x15
#define I2C_ADDR_vector                      0x15
#define I2C_ADD10_vector                     0x15
#define I2C_STOPF_vector                     0x15
#define I2C_BTF_vector                       0x15
#define I2C_WUFH_vector                      0x15
#define I2C_RXNE_vector                      0x15
#define I2C_TXE_vector                       0x15
#define I2C_BERR_vector                      0x15
#define I2C_ARLO_vector                      0x15
#define I2C_AF_vector                        0x15
#define I2C_OVR_vector                       0x15
#define UART3_T_TXE_vector                   0x16
#define UART3_T_TC_vector                    0x16
#define UART3_R_RXNE_vector                  0x17
#define UART3_R_OR_vector                    0x17
#define UART3_R_IDLE_vector                  0x17
#define UART3_R_PE_vector                    0x17
#define UART3_R_LBDF_vector                  0x17
#define UART3_R_LHDF_vector                  0x17
#define ADC2_AWDG_vector                     0x18
#define ADC2_EOC_vector                      0x18
#define TIM4_OVR_UIF_vector                  0x19
#define FLASH_EOP_vector                     0x1A
#define FLASH_WR_PG_DIS_vector               0x1A

#endif //__gpio_h_
