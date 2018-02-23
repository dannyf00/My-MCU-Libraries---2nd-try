#ifndef REFCO_H_INCLUDED
#define REFCO_H_INCLUDED

//32MX1xx/2xx reference clock output configuration
//REFCO on RPB2/PB2

#include "gpio.h"						//we use gpio

//hardware configuration
//end hardware configuration

//global defines
//ROSEL bits in REFOCON
#define REFCO_SYSCLK		0			//select sysclk
#define REFCO_PBCLK			1			//select PBCLK
#define REFCO_POSCCLK		2			//select primary oscillator
#define REFCO_FRCCLK		3			//select fast internal
#define REFCO_LPRCCLK		4			//select low frequency primary
#define REFCO_SOSCCLK		5			//select 2ndary oscillator
#define REFCO_USBPLLCLK		6			//select usb pll
#define REFCO_SYSPLLCLK		7			//select system pll
#define REFCO_REFCLKI		8			//select refclock input

//global variables

//initialize ref clock
//1. select the source;
//2. disable the output / module
//3. enable the output / module
//4. output ***disabled***
uint32_t refco_init(uint32_t clk_source);

//set ref clock divider N (0..32767)
//F_REFCO = F_CLK / (2 * (N + M / 512))
//return REFOCON.RODIV bits
uint32_t refco_setdiv(uint32_t n, uint32_t m);

//set ref clock output to desired frequency
//fref_out <=freq_in / (2 * (N + M / 512))
//output: N..M
uint32_t refco_setfreq(uint32_t fref_in, uint32_t fref_out, uint32_t *N);

//enable refco output
//assume that dividers are set
void refco_en(void);

//disable refco output
void refco_dis(void);

#endif /* REFCO_H_INCLUDED */
