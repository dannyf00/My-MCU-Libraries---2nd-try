#ifndef _PWM_H
#define _PWM_H

//support pwm on STM32F1 chips.
//supported timers: TIM1/2/3/4/15/16/17
//support Ch1/2/3/4. complimentary channels and break lines not supported

#include "gpio.h"					//we use F_CPU + gpio functions

//hardware configuration
#define TIM1CH1toGPIO()				TIM1CH1toPA8()
#define TIM1CH2toGPIO()				TIM1CH2toPA9()
#define TIM1CH3toGPIO()				TIM1CH3toPA10()
#define TIM1CH4toGPIO()				TIM1CH4toPA11()

#define TIM3CH1toGPIO()				TIM3CH1toPA6()		//TIM3CH1toPB4()
#define TIM3CH2toGPIO()				TIM3CH2toPA7()		//TIM3CH2toPB5()
#define TIM3CH3toGPIO()				TIM3CH3toPB0()
#define TIM3CH4toGPIO()				TIM3CH4toPB1()

#define TIM14CH1toGPIO()			TIM14CH1toPA4()		//TIM14CH1toPA7(), TIM14CH1toPB1()

#define TIM15CH1toGPIO()			TIM15CH1toPA2()		//TIM15CH1toPB14() - only on STM32F030x8
#define TIM15CH2toGPIO()			TIM15CH2toPA3()		//TIM15CH1toPB15() - only on STM32F030x8

#define TIM16CH1toGPIO()			TIM16CH1toPA6()		//TIM16CH1toPB8()

#define TIM17CH1toGPIO()			TIM17CH1toPA7()		//TIM17CH1toPB9()
//end hardware configuration

//global defines
//MODER=0b10 (alternate function), OTYPER=(push-pull), OSPEEDR = medium speed
//Alternate function = 2, AFR[1]/high byte
#define TIM1CH1toPA8()				do {RCC->AHBENR |= RCC_AHBENR_GPIOAEN; GPIOA->MODER = (GPIOA->MODER &~(0b11<<(2* 8))) | (0b10<<(2* 8)); GPIOA->OTYPER &=~(1<< 8); GPIOA->OSPEEDR = (GPIOA->OSPEEDR &~(0b11<<(2* 8))) | (0b01<<(2* 8)); GPIOA->AFR[1] = (GPIOA->AFR[1] &~(0x0f<<(4*( 8%8)))) | (2<<(4*( 8%8)));} while (0)
#define TIM1CH2toPA9()				do {RCC->AHBENR |= RCC_AHBENR_GPIOAEN; GPIOA->MODER = (GPIOA->MODER &~(0b11<<(2* 9))) | (0b10<<(2* 9)); GPIOA->OTYPER &=~(1<< 9); GPIOA->OSPEEDR = (GPIOA->OSPEEDR &~(0b11<<(2* 9))) | (0b01<<(2* 9)); GPIOA->AFR[1] = (GPIOA->AFR[1] &~(0x0f<<(4*( 9%8)))) | (2<<(4*( 9%8)));} while (0)
#define TIM1CH3toPA10()				do {RCC->AHBENR |= RCC_AHBENR_GPIOAEN; GPIOA->MODER = (GPIOA->MODER &~(0b11<<(2*10))) | (0b10<<(2*10)); GPIOA->OTYPER &=~(1<<10); GPIOA->OSPEEDR = (GPIOA->OSPEEDR &~(0b11<<(2*10))) | (0b01<<(2*10)); GPIOA->AFR[1] = (GPIOA->AFR[1] &~(0x0f<<(4*(10%8)))) | (2<<(4*(10%8)));} while (0)
#define TIM1CH4toPA11()				do {RCC->AHBENR |= RCC_AHBENR_GPIOAEN; GPIOA->MODER = (GPIOA->MODER &~(0b11<<(2*11))) | (0b10<<(2*11)); GPIOA->OTYPER &=~(1<<11); GPIOA->OSPEEDR = (GPIOA->OSPEEDR &~(0b11<<(2*11))) | (0b01<<(2*11)); GPIOA->AFR[1] = (GPIOA->AFR[1] &~(0x0f<<(4*(11%8)))) | (2<<(4*(11%8)));} while (0)

//MODER=0b10 (alternate function), OTYPER=(push-pull), OSPEEDR = medium speed
//Alternate function = 1, AFR[0]/low byte
#define TIM3CH1toPA6()				do {RCC->AHBENR |= RCC_AHBENR_GPIOAEN; GPIOA->MODER = (GPIOA->MODER &~(0b11<<(2* 6))) | (0b10<<(2* 6)); GPIOA->OTYPER &=~(1<< 6); GPIOA->OSPEEDR = (GPIOA->OSPEEDR &~(0b11<<(2* 6))) | (0b01<<(2* 6)); GPIOA->AFR[0] = (GPIOA->AFR[0] &~(0x0f<<(4*( 6%8)))) | (1<<(4*( 6%8)));} while (0)
//AF1
#define TIM3CH1toPB4()				do {RCC->AHBENR |= RCC_AHBENR_GPIOBEN; GPIOB->MODER = (GPIOB->MODER &~(0b11<<(2* 4))) | (0b10<<(2* 4)); GPIOB->OTYPER &=~(1<< 4); GPIOB->OSPEEDR = (GPIOB->OSPEEDR &~(0b11<<(2* 4))) | (0b01<<(2* 4)); GPIOB->AFR[0] = (GPIOB->AFR[0] &~(0x0f<<(4*( 4%8)))) | (1<<(4*( 4%8)));} while (0)
//AF1
#define TIM3CH2toPA7()				do {RCC->AHBENR |= RCC_AHBENR_GPIOAEN; GPIOA->MODER = (GPIOA->MODER &~(0b11<<(2* 7))) | (0b10<<(2* 7)); GPIOA->OTYPER &=~(1<< 7); GPIOA->OSPEEDR = (GPIOA->OSPEEDR &~(0b11<<(2* 7))) | (0b01<<(2* 7)); GPIOA->AFR[0] = (GPIOA->AFR[0] &~(0x0f<<(4*( 7%8)))) | (1<<(4*( 7%8)));} while (0)
//AF1
#define TIM3CH2toPB5()				do {RCC->AHBENR |= RCC_AHBENR_GPIOBEN; GPIOB->MODER = (GPIOB->MODER &~(0b11<<(2* 5))) | (0b10<<(2* 5)); GPIOB->OTYPER &=~(1<< 5); GPIOB->OSPEEDR = (GPIOB->OSPEEDR &~(0b11<<(2* 5))) | (0b01<<(2* 5)); GPIOB->AFR[0] = (GPIOB->AFR[0] &~(0x0f<<(4*( 5%8)))) | (1<<(1*( 5%8)));} while (0)
//AF1
#define TIM3CH3toPB0()				do {RCC->AHBENR |= RCC_AHBENR_GPIOBEN; GPIOB->MODER = (GPIOB->MODER &~(0b11<<(2* 0))) | (0b10<<(2* 0)); GPIOB->OTYPER &=~(1<< 0); GPIOB->OSPEEDR = (GPIOB->OSPEEDR &~(0b11<<(2* 0))) | (0b01<<(2* 0)); GPIOB->AFR[0] = (GPIOB->AFR[0] &~(0x0f<<(4*( 0%8)))) | (1<<(4*( 0%8)));} while (0)
//AF1
#define TIM3CH4toPB1()				do {RCC->AHBENR |= RCC_AHBENR_GPIOBEN; GPIOB->MODER = (GPIOB->MODER &~(0b11<<(2* 1))) | (0b10<<(2* 1)); GPIOB->OTYPER &=~(1<< 1); GPIOB->OSPEEDR = (GPIOB->OSPEEDR &~(0b11<<(2* 1))) | (0b01<<(2* 1)); GPIOB->AFR[0] = (GPIOB->AFR[0] &~(0x0f<<(4*( 1%8)))) | (1<<(4*( 1%8)));} while (0)

//AF4, AFR[0]/low byte
#define TIM14CH1toPA4()				do {RCC->AHBENR |= RCC_AHBENR_GPIOAEN; GPIOA->MODER = (GPIOA->MODER &~(0b11<<(2* 4))) | (0b10<<(2* 4)); GPIOA->OTYPER &=~(1<< 4); GPIOA->OSPEEDR = (GPIOA->OSPEEDR &~(0b11<<(2* 4))) | (0b01<<(2* 4)); GPIOA->AFR[0] = (GPIOA->AFR[0] &~(0x0f<<(4*( 4%8)))) | (4<<(4*( 4%8)));} while (0)
#define TIM14CH1toPA7()				do {RCC->AHBENR |= RCC_AHBENR_GPIOAEN; GPIOA->MODER = (GPIOA->MODER &~(0b11<<(2* 7))) | (0b10<<(2* 7)); GPIOA->OTYPER &=~(1<< 7); GPIOA->OSPEEDR = (GPIOA->OSPEEDR &~(0b11<<(2* 7))) | (0b01<<(2* 7)); GPIOA->AFR[0] = (GPIOA->AFR[0] &~(0x0f<<(4*( 7%8)))) | (4<<(4*( 7%8)));} while (0)
//AF0, AFR[0]/low byte
#define TIM14CH1toPB1()				do {RCC->AHBENR |= RCC_AHBENR_GPIOBEN; GPIOB->MODER = (GPIOB->MODER &~(0b11<<(2* 1))) | (0b10<<(2* 1)); GPIOB->OTYPER &=~(1<< 1); GPIOB->OSPEEDR = (GPIOB->OSPEEDR &~(0b11<<(2* 1))) | (0b01<<(2* 1)); GPIOB->AFR[0] = (GPIOB->AFR[0] &~(0x0f<<(4*( 1%8)))) | (0<<(4*( 1%8)));} while (0)

//MODER=0b10 (alternate function), OTYPER=(push-pull), OSPEEDR = medium speed
//Alternate function = 0, AFR[0]/low byte
#define TIM15CH1toPA2()				do {RCC->AHBENR |= RCC_AHBENR_GPIOAEN; GPIOA->MODER = (GPIOA->MODER &~(0b11<<(2* 2))) | (0b10<<(2* 2)); GPIOA->OTYPER &=~(1<< 2); GPIOA->OSPEEDR = (GPIOA->OSPEEDR &~(0b11<<(2* 2))) | (0b01<<(2* 2)); GPIOA->AFR[0] = (GPIOA->AFR[0] &~(0x0f<<(4*( 2%8)))) | (0<<(4*( 2%8)));} while (0)
#define TIM15CH2toPA3()				do {RCC->AHBENR |= RCC_AHBENR_GPIOAEN; GPIOA->MODER = (GPIOA->MODER &~(0b11<<(2* 3))) | (0b10<<(2* 3)); GPIOA->OTYPER &=~(1<< 3); GPIOA->OSPEEDR = (GPIOA->OSPEEDR &~(0b11<<(2* 3))) | (0b01<<(2* 3)); GPIOA->AFR[0] = (GPIOA->AFR[0] &~(0x0f<<(4*( 3%8)))) | (0<<(4*( 3%8)));} while (0)
//AF=1, AFR[1]/high byte
#define TIM15CH1toPB14()			do {RCC->AHBENR |= RCC_AHBENR_GPIOBEN; GPIOB->MODER = (GPIOB->MODER &~(0b11<<(2*14))) | (0b10<<(2*14)); GPIOB->OTYPER &=~(1<<14); GPIOB->OSPEEDR = (GPIOB->OSPEEDR &~(0b11<<(2*14))) | (0b01<<(2*14)); GPIOB->AFR[1] = (GPIOB->AFR[1] &~(0x0f<<(4*(14%8)))) | (1<<(4*(14%8)));} while (0)
#define TIM15CH1toPB15()			do {RCC->AHBENR |= RCC_AHBENR_GPIOBEN; GPIOB->MODER = (GPIOB->MODER &~(0b11<<(2*15))) | (0b10<<(2*15)); GPIOB->OTYPER &=~(1<<15); GPIOB->OSPEEDR = (GPIOB->OSPEEDR &~(0b11<<(2*15))) | (0b01<<(2*15)); GPIOB->AFR[1] = (GPIOB->AFR[1] &~(0x0f<<(4*(15%8)))) | (1<<(4*(15%8)));} while (0)

//MODER=0b10 (alternate function), OTYPER=(push-pull), OSPEEDR = medium speed
//Alternate function = 5, AFR[0]/low byte
#define TIM16CH1toPA6()				do {RCC->AHBENR |= RCC_AHBENR_GPIOAEN; GPIOA->MODER = (GPIOA->MODER &~(0b11<<(2* 6))) | (0b10<<(2* 6)); GPIOA->OTYPER &=~(1<< 6); GPIOA->OSPEEDR = (GPIOA->OSPEEDR &~(0b11<<(2* 6))) | (0b01<<(2* 6)); GPIOA->AFR[0] = (GPIOA->AFR[0] &~(0x0f<<(4*( 6%8)))) | (5<<(4*( 6%8)));} while (0)
//AF2, AFR[1]/high byte
#define TIM16CH1toPB8()				do {RCC->AHBENR |= RCC_AHBENR_GPIOBEN; GPIOB->MODER = (GPIOB->MODER &~(0b11<<(2* 8))) | (0b10<<(2* 8)); GPIOB->OTYPER &=~(1<< 8); GPIOB->OSPEEDR = (GPIOB->OSPEEDR &~(0b11<<(2* 8))) | (0b01<<(2* 8)); GPIOB->AFR[1] = (GPIOB->AFR[1] &~(0x0f<<(4*( 8%8)))) | (2<<(4*( 8%8)));} while (0)

//MODER=0b10 (alternate function), OTYPER=(push-pull), OSPEEDR = medium speed
//Alternate function = 5, AFR[0]/low byte
#define TIM17CH1toPA7()				do {RCC->AHBENR |= RCC_AHBENR_GPIOAEN; GPIOA->MODER = (GPIOA->MODER &~(0b11<<(2* 7))) | (0b10<<(2* 7)); GPIOA->OTYPER &=~(1<< 7); GPIOA->OSPEEDR = (GPIOA->OSPEEDR &~(0b11<<(2* 7))) | (0b01<<(2* 7)); GPIOA->AFR[0] = (GPIOA->AFR[0] &~(0x0f<<(4*( 7%8)))) | (5<<(4*( 7%8)));} while (0)
//AF2, AFR[1]/high byte
#define TIM17CH1toPB9()				do {RCC->AHBENR |= RCC_AHBENR_GPIOBEN; GPIOB->MODER = (GPIOB->MODER &~(0b11<<(2* 9))) | (0b10<<(2* 9)); GPIOB->OTYPER &=~(1<< 9); GPIOB->OSPEEDR = (GPIOB->OSPEEDR &~(0b11<<(2* 9))) | (0b01<<(2* 9)); GPIOB->AFR[1] = (GPIOB->AFR[1] &~(0x0f<<(4*( 9%8)))) | (2<<(4*( 9%8)));} while (0)
//global variables

//initialize pwm to TxCCP_PS (prescaler) and TxCCP_PR (period)
void pwm1_init(uint16_t TxCCP_PS, uint16_t TxCCP_PR);

//set duty cycle
#define pwm1_setdc1(dc)		TIM1->CCR1 = (dc)
#define pwm1_setdc2(dc)		TIM1->CCR2 = (dc)
#define pwm1_setdc3(dc)		TIM1->CCR3 = (dc)
#define pwm1_setdc4(dc)		TIM1->CCR4 = (dc)

//initialize pwm to TxCCP_PS (prescaler) and TxCCP_PR (period)
void pwm3_init(uint16_t TxCCP_PS, uint16_t TxCCP_PR);

//set duty cycle
#define pwm3_setdc1(dc)			TIM3->CCR1 = (dc)
#define pwm3_setdc2(dc)			TIM3->CCR2 = (dc)
#define pwm3_setdc3(dc)			TIM3->CCR3 = (dc)
#define pwm3_setdc4(dc)			TIM3->CCR4 = (dc)

//initialize pwm to TxCCP_PS (prescaler) and TxCCP_PR (period)
void pwm14_init(uint16_t TxCCP_PS, uint16_t TxCCP_PR);
//set duty cycle
#define pwm14_setdc1(dc)			TIM14->CCR1 = (dc)
#define pwm14_setdc2(dc)			TIM14->CCR2 = (dc)
#define pwm14_setdc3(dc)			TIM14->CCR3 = (dc)
#define pwm14_setdc4(dc)			TIM14->CCR4 = (dc)

//initialize pwm to TxCCP_PS (prescaler) and TxCCP_PR (period)
void pwm15_init(uint16_t TxCCP_PS, uint16_t TxCCP_PR);
//set duty cycle
#define pwm15_setdc1(dc)			TIM15->CCR1 = (dc)
#define pwm15_setdc2(dc)			TIM15->CCR2 = (dc)
#define pwm15_setdc3(dc)			TIM15->CCR3 = (dc)
#define pwm15_setdc4(dc)			TIM15->CCR4 = (dc)

//initialize pwm to TxCCP_PS (prescaler) and TxCCP_PR (period)
void pwm16_init(uint16_t TxCCP_PS, uint16_t TxCCP_PR);
//set duty cycle
#define pwm16_setdc1(dc)			TIM16->CCR1 = (dc)
#define pwm16_setdc2(dc)			TIM16->CCR2 = (dc)
#define pwm16_setdc3(dc)			TIM16->CCR3 = (dc)
#define pwm16_setdc4(dc)			TIM16->CCR4 = (dc)

//initialize pwm to TxCCP_PS (prescaler) and TxCCP_PR (period)
void pwm17_init(uint16_t TxCCP_PS, uint16_t TxCCP_PR);
//set duty cycle
#define pwm17_setdc1(dc)			TIM17->CCR1 = (dc)
#define pwm17_setdc2(dc)			TIM17->CCR2 = (dc)
#define pwm17_setdc3(dc)			TIM17->CCR3 = (dc)
#define pwm17_setdc4(dc)			TIM17->CCR4 = (dc)

#endif
