#ifndef _PWM_H
#define _PWM_H

#include "gpio.h"

//initialize pwm prescaler + period
void pwm1_init(uint16_t TxCCP_PS, uint16_t TxCCP_PR);
void pwm2_init(uint16_t TxCCP_PS, uint16_t TxCCP_PR);
void pwm3_init(uint16_t TxCCP_PS, uint16_t TxCCP_PR);
void pwm5_init(uint16_t TxCCP_PS, uint16_t TxCCP_PR);			//if available

//set pwm duty cycles
#define pwm1_setdc1(dc) do {IO_OUT(GPIOC, 1<<1); TIM1->CCR1H = (dc) >> 8; TIM1->CCR1L = (dc);} while (0)	//PC1=T1CC1
#define pwm1_setdc2(dc) do {IO_OUT(GPIOC, 1<<2); TIM1->CCR2H = (dc) >> 8; TIM1->CCR2L = (dc);} while (0)	//PC2=T1CC2
#define pwm1_setdc3(dc) do {IO_OUT(GPIOC, 1<<3); TIM1->CCR3H = (dc) >> 8; TIM1->CCR3L = (dc);} while (0)	//PC3=T1CC3
#define pwm1_setdc4(dc) do {IO_OUT(GPIOC, 1<<4); TIM1->CCR4H = (dc) >> 8; TIM1->CCR4L = (dc);} while (0)	//PC4=T1CC4

#if defined(TIM2_CCMR1_RESET_VALUE)
#define pwm2_setdc1(dc) do {IO_OUT(GPIOD, 1<<4); TIM2->CCR1H = (dc) >> 8; TIM2->CCR1L = (dc);} while (0)	//PD4=T2CC1
#endif
#if defined(TIM2_CCMR2_RESET_VALUE)
#define pwm2_setdc2(dc) do {IO_OUT(GPIOD, 1<<3); TIM2->CCR2H = (dc) >> 8; TIM2->CCR2L = (dc);} while (0)	//PD3=T2CC2
#endif
#if defined(TIM2_CCMR3_RESET_VALUE)
#define pwm2_setdc3(dc) do {IO_OUT(GPIOA, 1<<3); TIM2->CCR3H = (dc) >> 8; TIM2->CCR3L = (dc);} while (0)	//PA3=T2CC3
#endif
#if defined(TIM2_CCMR4_RESET_VALUE)
#define pwm2_setdc4(dc) do {IO_OUT(GPIOC, 1<<4); TIM2->CCR4H = (dc) >> 8; TIM2->CCR4L = (dc);} while (0)	//?
#endif

#if defined(TIM3_CCMR1_RESET_VALUE)
#define pwm3_setdc1(dc) do {IO_OUT(GPIOD, 1<<1); TIM3->CCR1H = (dc) >> 8; TIM3->CCR1L = (dc);} while (0)	//PD2=T3CC1
#endif
#if defined(TIM3_CCMR2_RESET_VALUE)
#define pwm3_setdc2(dc) do {IO_OUT(GPIOD, 1<<0); TIM3->CCR2H = (dc) >> 8; TIM3->CCR2L = (dc);} while (0)	//PD0=T3CC1
#endif
#if defined(TIM3_CCMR3_RESET_VALUE)
#define pwm3_setdc3(dc) do {IO_OUT(GPIOC, 1<<3); TIM3->CCR3H = (dc) >> 8; TIM3->CCR3L = (dc);} while (0)	//?
#endif
#if defined(TIM3_CCMR4_RESET_VALUE)
#define pwm3_setdc4(dc) do {IO_OUT(GPIOC, 1<<4); TIM3->CCR4H = (dc) >> 8; TIM3->CCR4L = (dc);} while (0)	//?
#endif

//T5CCP1..4, if available
#if defined(TIM5_CCMR4_RESET_VALUE)
#define pwm5_setdc1(dc) do {IO_OUT(GPIOD, 1<<1); TIM5->CCR1H = (dc) >> 8; TIM5->CCR1L = (dc);} while (0)	//?
#endif
#if defined(TIM5_CCMR4_RESET_VALUE)
#define pwm5_setdc2(dc) do {IO_OUT(GPIOD, 1<<0); TIM5->CCR2H = (dc) >> 8; TIM5->CCR2L = (dc);} while (0)	//?
#endif
#if defined(TIM5_CCMR4_RESET_VALUE)
#define pwm5_setdc3(dc) do {IO_OUT(GPIOC, 1<<3); TIM5->CCR3H = (dc) >> 8; TIM5->CCR3L = (dc);} while (0)	//?
#endif
#if defined(TIM5_CCMR4_RESET_VALUE)
#define pwm5_setdc4(dc) do {IO_OUT(GPIOC, 1<<4); TIM5->CCR4H = (dc) >> 8; TIM5->CCR4L = (dc);} while (0)	//?
#endif

#endif
