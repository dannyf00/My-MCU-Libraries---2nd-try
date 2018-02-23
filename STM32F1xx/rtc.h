#ifndef RTC_H
#define RTC_H

#include "gpio.h"					//we use F_CPU + gpio functions

//hardware configuration
//end hardware configuration

//global defines
#define RCC_RTCSEL_LSI	RCC_BDCR_RTCSEL_LSI
#define RCC_RTCSEL_LSE	RCC_BDCR_RTCSEL_LSE
#define RCC_RTCSEL_HSE	RCC_BDCR_RTCSEL_HSE

//reset the rtc
//ps = prescaler
void rtc_init(uint32_t ps);

//install rtc overflow isr
void rtc_act(void (*isr_ptr)(void));

//read rtc counter
uint32_t rtc_get(void);
uint32_t rtc_set(uint32_t val);
#endif
