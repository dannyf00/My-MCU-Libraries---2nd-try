#ifndef TMR1OC_H
#define TMR1OC_H

#include "gpio.h"                           //we use gpio functions

//hardware configuration
#define TMR1_PS				3				//0->1:1, 1=2:1, 2=4:1, 3=8:1
//end hardware configuration

//global defines

//XC8 stupidity
//CCPRx register addresses. Confirmed only for PIC16(L)F193x chips
extern volatile unsigned short           CCPR1              @ 0x291;
extern volatile unsigned short           CCPR2              @ 0x298;
extern volatile unsigned short           CCPR3              @ 0x311;
extern volatile unsigned short           CCPR4              @ 0x318;
extern volatile unsigned short           CCPR5              @ 0x31c;


//global variables


//user isr handlers

//channel pointers

//ccp isr
void ccp1_isr(void);
void ccp2_isr(void);
void ccp3_isr(void);
void ccp4_isr(void);
void ccp5_isr(void);

//initialize tmr1oc modules
void tmr1oc_init(void);

//set oc1/ccp1
void tmr1oc_setpr1(uint16_t pr);
//install user handler
void tmr1oc_act1(void (*isrptr)(void));

//set oc2/ccp2
void tmr1oc_setpr2(uint16_t pr);
//install user handler
void tmr1oc_act2(void (*isrptr)(void));

//set oc3/ccp3
void tmr1oc_setpr3(uint16_t pr);
//install user handler
void tmr1oc_act3(void (*isrptr)(void));

//set oc4/ccp4
void tmr1oc_setpr4(uint16_t pr);
//install user handler
void tmr1oc_act4(void (*isrptr)(void));

//set oc5/ccp5
void tmr1oc_setpr5(uint16_t pr);
//install user handler
void tmr1oc_act5(void (*isrptr)(void));

#endif
