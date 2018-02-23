#ifndef _PWM_H
#define _PWM_H

//support pwm on STM32F1 chips.
//supported timers: TIM1/2/3/4/15/16/17
//support Ch1/2/3/4. complimentary channels and break lines not supported

#include "gpio.h"					//we use F_CPU + gpio functions

//hardware configuration
#define USE_TIM1CH1
#define USE_TIM1CH2
#define USE_TIM1CH3
#define USE_TIM1CH4
#define TIM1REMAP			TIM1REMAP3				//select TIMER1 remap scheme

#define USE_TIM2CH1
#define USE_TIM2CH2
#define USE_TIM2CH3
#define USE_TIM2CH4
#define TIM2REMAP			TIM2REMAP3				//select TIMER2 remap scheme

#define USE_TIM3CH1
#define USE_TIM3CH2
#define USE_TIM3CH3
#define USE_TIM3CH4
#define TIM3REMAP			TIM3REMAP3				//select TIMER3 remap scheme

#define USE_TIM4CH1
#define USE_TIM4CH2
#define USE_TIM4CH3
#define USE_TIM4CH4
#define TIM4REMAP			TIM4REMAP1				//select TIMER4 remap scheme

#define USE_TIM15CH1
#define USE_TIM15CH2
#define USE_TIM15CH3
#define USE_TIM15CH4
#define TIM15REMAP			TIM15REMAP1				//select TIMER15 remap scheme

#define USE_TIM16CH1
#define USE_TIM16CH2
#define USE_TIM16CH3
#define USE_TIM16CH4
#define TIM16REMAP			TIM16REMAP1				//select TIMER15 remap scheme

#define USE_TIM17CH1
#define USE_TIM17CH2
#define USE_TIM17CH3
#define USE_TIM17CH4
#define TIM17REMAP			TIM17REMAP1				//select TIMER15 remap scheme

//end hardware configuration

//global defines
//TMR1 remap macros
/*
MAPR Bits 7:6 TIM1_REMAP[1:0]: TIM1 remapping
These bits are set and cleared by software. They control the mapping of TIM1 channels 1 to 4, 1N to 3N, external trigger (ETR) and Break input (BKIN) on the GPIO ports.
00: No remap (ETR/PA12, CH1/PA8, CH2/PA9, CH3/PA10, CH4/PA11, BKIN/PB12, CH1N/PB13, CH2N/PB14, CH3N/PB15)
01: Partial remap (ETR/PA12, CH1/PA8, CH2/PA9, CH3/PA10, CH4/PA11, BKIN/PA6, CH1N/PA7, CH2N/PB0, CH3N/PB1)
10: not used
11: Full remap (ETR/PE7, CH1/PE9, CH2/PE11, CH3/PE13, CH4/PE14, BKIN/PE15, CH1N/PE8, CH2N/PE10, CH3N/PE12)
*/
#define TIM1REMAP0		(0<<6)
#define TIM1REMAP1		(1<<6)
#define TIM1REMAP2		(2<<6)
#define TIM1REMAP3		(3<<6)

/*
MAPR Bits 9:8 TIM2_REMAP[1:0]: TIM2 remapping
These bits are set and cleared by software. They control the mapping of TIM2 channels 1 to 4 and external trigger (ETR) on the GPIO ports.
00: No remap (CH1/ETR/PA0, CH2/PA1, CH3/PA2, CH4/PA3)
01: Partial remap (CH1/ETR/PA15, CH2/PB3, CH3/PA2, CH4/PA3)
10: Partial remap (CH1/ETR/PA0, CH2/PA1, CH3/PB10, CH4/PB11)
11: Full remap (CH1/ETR/PA15, CH2/PB3, CH3/PB10, CH4/PB11)
*/
#define TIM2REMAP0		(0<< 8)
#define TIM2REMAP1		(1<< 8)
#define TIM2REMAP2		(2<< 8)
#define TIM2REMAP3		(3<< 8)

/*
MAPR Bits 11:10 TIM3_REMAP[1:0]: TIM3 remapping
These bits are set and cleared by software. They control the mapping of TIM3 channels 1 to 4 on the GPIO ports.
00: No remap (CH1/PA6, CH2/PA7, CH3/PB0, CH4/PB1)
01: Not used
10: Partial remap (CH1/PB4, CH2/PB5, CH3/PB0, CH4/PB1)
11: Full remap (CH1/PC6, CH2/PC7, CH3/PC8, CH4/PC9)
Note: TIM3_ETR on PE0 is not re-mapped.
*/
#define TIM3REMAP0		(0<<10)
#define TIM3REMAP1		(1<<10)
#define TIM3REMAP2		(2<<10)
#define TIM3REMAP3		(3<<10)

/*
MAPR Bit 12 TIM4_REMAP: TIM4 remapping
This bit is set and cleared by software. It controls the mapping of TIM4 channels 1 to 4 onto the GPIO ports.
0: No remap (TIM4_CH1/PB6, TIM4_CH2/PB7, TIM4_CH3/PB8, TIM4_CH4/PB9)
1: Full remap (TIM4_CH1/PD12, TIM4_CH2/PD13, TIM4_CH3/PD14, TIM4_CH4/PD15)
Note: TIM4_ETR on PE0 is not re-mapped.
*/
#define TIM4REMAP0		(0<<12)
#define TIM4REMAP1		(1<<12)

/*
MAPR2 Bit 12 TIM12_REMAP: TIM12 remapping
This bit is set and cleared by software. It controls the mapping of the TIM12_CH1 and TIM12_CH2 alternate function onto the GPIO ports.
0: No remap (CH1/PC4, CH2/PC5)
1: Remap (CH1/PB12, CH2/PB13)
Note: This bit is available only in high density value line devices.
 */
#define TIM12REMAP0		(0<<12)
#define TIM12REMAP1		(1<<12)

/*
MAPR2 Bit 8 TIM13_REMAP: TIM13 remapping
This bit is set and cleared by software. It controls the mapping of the TIM13_CH1 alternate function onto the GPIO ports.
0: No remap (PC8)
1: Remap (PB0)
 */
#define TIM13REMAP0		(0<<8)
#define TIM13REMAP1		(1<<8)

/*
MAPR2 Bit 9 TIM14_REMAP: TIM14 remapping
This bit is set and cleared by software. It controls the mapping of the TIM14_CH1 alternate function onto the GPIO ports.
0: No remap (PC9)
1: Remap (PB1)
 */
#define TIM14REMAP0		(0<<9)
#define TIM14REMAP1		(1<<9)

/*
MAPR2 Bit 0 TIM15_REMAP: TIM15 remapping
This bit is set and cleared by software. It controls the mapping of the alternate functions of TIM15 channels 1 and 2 onto the GPIO ports.
0: No remap (CH1/PA2, CH2/PA3)
1: Remap (CH1/PB14, CH2/PB15)
 */
#define TIM15REMAP0		(0<<0)
#define TIM15REMAP1		(1<<0)

/*
MAPR2 Bit 1 TIM16_REMAP: TIM16 remapping
This bit is set and cleared by software. It controls the mapping of the alternate functions of TIM16 channel 1 onto the GPIO ports.
0: No remap (CH1/PB8)
1: Remap (CH1/PA6)
 */
#define TIM16REMAP0		(0<<1)
#define TIM16REMAP1		(1<<1)

/*
MAPR2 Bit 2 TIM17_REMAP: TIM17 remapping
This bit is set and cleared by software. It controls the mapping of the alternate functions of TIM17 channel 1 onto the GPIO ports.
0: No remap (CH1/PB9)
1: Remap (CH1/PA7)
 */
#define TIM17REMAP0		(0<<2)
#define TIM17REMAP1		(1<<2)


//global variables

/*
Bits 7:6 TIM1_REMAP[1:0]: TIM1 remapping
These bits are set and cleared by software. They control the mapping of TIM1 channels 1 to 4, 1N to 3N, external trigger (ETR) and Break input (BKIN) on the GPIO ports.
00: No remap (ETR/PA12, CH1/PA8, CH2/PA9, CH3/PA10, CH4/PA11, BKIN/PB12, CH1N/PB13, CH2N/PB14, CH3N/PB15)
01: Partial remap (ETR/PA12, CH1/PA8, CH2/PA9, CH3/PA10, CH4/PA11, BKIN/PA6, CH1N/PA7, CH2N/PB0, CH3N/PB1)
10: not used
11: Full remap (ETR/PE7, CH1/PE9, CH2/PE11, CH3/PE13, CH4/PE14, BKIN/PE15, CH1N/PE8, CH2N/PE10, CH3N/PE12)
*/
//initialize pwm to TxCCP_PS (prescaler) and TxCCP_PR (period)
void pwm1_init(uint16_t TxCCP_PS, uint16_t TxCCP_PR);

//set duty cycle
#define pwm1_setdc1(dc)		TIM1->CCR1 = (dc)
#define pwm1_setdc2(dc)		TIM1->CCR2 = (dc)
#define pwm1_setdc3(dc)		TIM1->CCR3 = (dc)
#define pwm1_setdc4(dc)		TIM1->CCR4 = (dc)

/*
Bits 9:8 TIM2_REMAP[1:0]: TIM2 remapping
These bits are set and cleared by software. They control the mapping of TIM2 channels 1 to 4 and external trigger (ETR) on the GPIO ports.
00: No remap (CH1/ETR/PA0, CH2/PA1, CH3/PA2, CH4/PA3)
01: Partial remap (CH1/ETR/PA15, CH2/PB3, CH3/PA2, CH4/PA3)
10: Partial remap (CH1/ETR/PA0, CH2/PA1, CH3/PB10, CH4/PB11)
11: Full remap (CH1/ETR/PA15, CH2/PB3, CH3/PB10, CH4/PB11)
*/
//initialize pwm to TxCCP_PS (prescaler) and TxCCP_PR (period)
void pwm2_init(uint16_t TxCCP_PS, uint16_t TxCCP_PR);

//set duty cycle
#define pwm2_setdc1(dc)		TIM2->CCR1 = (dc)
#define pwm2_setdc2(dc)		TIM2->CCR2 = (dc)
#define pwm2_setdc3(dc)		TIM2->CCR3 = (dc)
#define pwm2_setdc4(dc)		TIM2->CCR4 = (dc)

/*
Bits 11:10 TIM3_REMAP[1:0]: TIM3 remapping
These bits are set and cleared by software. They control the mapping of TIM3 channels 1 to 4 on the GPIO ports.
00: No remap (CH1/PA6, CH2/PA7, CH3/PB0, CH4/PB1)
01: Not used
10: Partial remap (CH1/PB4, CH2/PB5, CH3/PB0, CH4/PB1)
11: Full remap (CH1/PC6, CH2/PC7, CH3/PC8, CH4/PC9)
Note: TIM3_ETR on PE0 is not re-mapped.
*/
//initialize pwm to TxCCP_PS (prescaler) and TxCCP_PR (period)
void pwm3_init(uint16_t TxCCP_PS, uint16_t TxCCP_PR);

//set duty cycle
#define pwm3_setdc1(dc)			TIM3->CCR1 = (dc)
#define pwm3_setdc2(dc)			TIM3->CCR2 = (dc)
#define pwm3_setdc3(dc)			TIM3->CCR3 = (dc)
#define pwm3_setdc4(dc)			TIM3->CCR4 = (dc)

/*
MAPR Bit 12 TIM4_REMAP: TIM4 remapping
This bit is set and cleared by software. It controls the mapping of TIM4 channels 1 to 4 onto the GPIO ports.
0: No remap (TIM4_CH1/PB6, TIM4_CH2/PB7, TIM4_CH3/PB8, TIM4_CH4/PB9)
1: Full remap (TIM4_CH1/PD12, TIM4_CH2/PD13, TIM4_CH3/PD14, TIM4_CH4/PD15)
Note: TIM4_ETR on PE0 is not re-mapped.
*/
//initialize pwm to TxCCP_PS (prescaler) and TxCCP_PR (period)
void pwm4_init(uint16_t TxCCP_PS, uint16_t TxCCP_PR);
//set duty cycle
#define pwm4_setdc1(dc)			TIM4->CCR1 = (dc)
#define pwm4_setdc2(dc)			TIM4->CCR2 = (dc)
#define pwm4_setdc3(dc)			TIM4->CCR3 = (dc)
#define pwm4_setdc4(dc)			TIM4->CCR4 = (dc)

/*
MAPR2 Bit 12 TIM12_REMAP: TIM12 remapping
This bit is set and cleared by software. It controls the mapping of the TIM12_CH1 and TIM12_CH2 alternate function onto the GPIO ports.
0: No remap (CH1/PC4, CH2/PC5)
1: Remap (CH1/PB12, CH2/PB13)
Note: This bit is available only in high density value line devices.*/
//initialize pwm to TxCCP_PS (prescaler) and TxCCP_PR (period)
void pwm12_init(uint16_t TxCCP_PS, uint16_t TxCCP_PR);
//set duty cycle
#define pwm12_setdc1(dc)			TIM12->CCR1 = (dc)
#define pwm12_setdc2(dc)			TIM12->CCR2 = (dc)
//#define pwm12_setdc3(dc)			TIM12->CCR3 = (dc)
//#define pwm12_setdc4(dc)			TIM12->CCR4 = (dc)

/*
MAPR2 Bit 8 TIM13_REMAP: TIM13 remapping
This bit is set and cleared by software. It controls the mapping of the TIM13_CH1 alternate function onto the GPIO ports.
0: No remap (PC8)
1: Remap (PB0)
*/
//initialize pwm to TxCCP_PS (prescaler) and TxCCP_PR (period)
void pwm13_init(uint16_t TxCCP_PS, uint16_t TxCCP_PR);
//set duty cycle
#define pwm13_setdc1(dc)			TIM13->CCR1 = (dc)
//#define pwm13_setdc2(dc)			TIM13->CCR2 = (dc)
//#define pwm13_setdc3(dc)			TIM13->CCR3 = (dc)
//#define pwm13_setdc4(dc)			TIM13->CCR4 = (dc)

/*
MAPR2 Bit 9 TIM14_REMAP: TIM14 remapping
This bit is set and cleared by software. It controls the mapping of the TIM14_CH1 alternate function onto the GPIO ports.
0: No remap (PC9)
1: Remap (PB1)
*/
//initialize pwm to TxCCP_PS (prescaler) and TxCCP_PR (period)
void pwm14_init(uint16_t TxCCP_PS, uint16_t TxCCP_PR);
//set duty cycle
#define pwm14_setdc1(dc)			TIM14->CCR1 = (dc)
//#define pwm14_setdc2(dc)			TIM14->CCR2 = (dc)
//#define pwm14_setdc3(dc)			TIM14->CCR3 = (dc)
//#define pwm14_setdc4(dc)			TIM14->CCR4 = (dc)

/*
MAPR2 Bit 0 TIM15_REMAP: TIM15 remapping
This bit is set and cleared by software. It controls the mapping of the alternate functions of
TIM15 channels 1 and 2 onto the GPIO ports.
0: No remap (CH1/PA2, CH2/PA3)
1: Remap (CH1/PB14, CH2/PB15)
*/
//initialize pwm to TxCCP_PS (prescaler) and TxCCP_PR (period)
void pwm15_init(uint16_t TxCCP_PS, uint16_t TxCCP_PR);
//set duty cycle
#define pwm15_setdc1(dc)			TIM15->CCR1 = (dc)
#define pwm15_setdc2(dc)			TIM15->CCR2 = (dc)
//#define pwm15_setdc3(dc)			TIM15->CCR3 = (dc)
//#define pwm15_setdc4(dc)			TIM15->CCR4 = (dc)
/*
MAPR2 Bit 1 TIM16_REMAP: TIM16 remapping
This bit is set and cleared by software. It controls the mapping of the alternate functions of TIM16 channel 1 onto the GPIO ports.
0: No remap (CH1/PB8)
1: Remap (CH1/PA6)
*/
//initialize pwm to TxCCP_PS (prescaler) and TxCCP_PR (period)
void pwm16_init(uint16_t TxCCP_PS, uint16_t TxCCP_PR);
//set duty cycle
#define pwm16_setdc1(dc)			TIM16->CCR1 = (dc)
//#define pwm16_setdc2(dc)			TIM16->CCR2 = (dc)
//#define pwm16_setdc3(dc)			TIM16->CCR3 = (dc)
//#define pwm16_setdc4(dc)			TIM16->CCR4 = (dc)

/*
MAPR2 Bit 2 TIM17_REMAP: TIM17 remapping
This bit is set and cleared by software. It controls the mapping of the alternate functions of
TIM17 channel 1 onto the GPIO ports.
0: No remap (CH1/PB9)
1: Remap (CH1/PA7)
*/
//initialize pwm to TxCCP_PS (prescaler) and TxCCP_PR (period)
void pwm17_init(uint16_t TxCCP_PS, uint16_t TxCCP_PR);
//set duty cycle
#define pwm17_setdc1(dc)			TIM17->CCR1 = (dc)
//#define pwm17_setdc2(dc)			TIM17->CCR2 = (dc)
//#define pwm17_setdc3(dc)			TIM17->CCR3 = (dc)
//#define pwm17_setdc4(dc)			TIM17->CCR4 = (dc)

#endif
