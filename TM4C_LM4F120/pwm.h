#ifndef PWM_H_
#define PWM_H_

#include "gpio.h"						//we use gpio

//16/32-bit PWM output
//PS defined by TxCCP_PS
//PR defined by TxCCP_PR
//valid pin assignment:
//PF0/T0CCP0 - not used / locked by CR
//PF1/T0CCP1
//PF2/T1CCP0
//PF3/T1CCP1
//PF4/T2CCP0 - not used / see PB0
//PB0/T2CCP0
//PB1/T2CCP1
//PB2/T3CCP0
//PB3/T3CCP1
//PB4/T1CCP0 - not used/see PF2
//PB5/T1CCP1 - not used/see PF3
//PB6/T0CCP0 - not used/see PF0
//PB7/T0CCP1 - not used/see PF1
//PC0/T4CCP0 - not used/SWCLK
//PC1/T4CCP1 - not used/SWDIO
//PC2/T5CCP0 - not used/TDI
//PC3/T5CCP1 - not used/TDO
//PC4/WT0CCP0
//PC5/WT0CCP1
//PC6/WT1CCP0
//PC7/WT1CCP1
//PD0/WT2CCP0
//PD1/WT2CCP1
//PD2/WT3CCP0
//PD3/WT3CCP1
//PD4/WT4CCP0
//PD5/WT4CCP1
//PD6/WT5CCP0
//PD7/WT5CCP1

//16-bit pwm
//initilize pwm
//TxCCP_PS = 1: prescaler not a true prescaler
void pwm0a_init(uint8_t TxCCP_PS, uint16_t TxCCP_PR);
void pwm0b_init(uint8_t TxCCP_PS, uint16_t TxCCP_PR);
void pwm1a_init(uint8_t TxCCP_PS, uint16_t TxCCP_PR);
void pwm1b_init(uint8_t TxCCP_PS, uint16_t TxCCP_PR);
void pwm2a_init(uint8_t TxCCP_PS, uint16_t TxCCP_PR);
void pwm2b_init(uint8_t TxCCP_PS, uint16_t TxCCP_PR);
void pwm3a_init(uint8_t TxCCP_PS, uint16_t TxCCP_PR);
void pwm3b_init(uint8_t TxCCP_PS, uint16_t TxCCP_PR);
void pwm4a_init(uint8_t TxCCP_PS, uint16_t TxCCP_PR);
void pwm4b_init(uint8_t TxCCP_PS, uint16_t TxCCP_PR);
void pwm5a_init(uint8_t TxCCP_PS, uint16_t TxCCP_PR);
void pwm5b_init(uint8_t TxCCP_PS, uint16_t TxCCP_PR);

//set pwm duty cycle
#define pwm0a_setdc(dc)		TIMER0->TAMATCHR = (dc)
#define pwm0b_setdc(dc)		TIMER0->TBMATCHR = (dc)
#define pwm1a_setdc(dc)		TIMER1->TAMATCHR = (dc)
#define pwm1b_setdc(dc)		TIMER1->TBMATCHR = (dc)
#define pwm2a_setdc(dc)		TIMER2->TAMATCHR = (dc)
#define pwm2b_setdc(dc)		TIMER2->TBMATCHR = (dc)
#define pwm3a_setdc(dc)		TIMER3->TAMATCHR = (dc)
#define pwm3b_setdc(dc)		TIMER3->TBMATCHR = (dc)
#define pwm4a_setdc(dc)		TIMER4->TAMATCHR = (dc)
#define pwm4b_setdc(dc)		TIMER4->TBMATCHR = (dc)
#define pwm5a_setdc(dc)		TIMER5->TAMATCHR = (dc)
#define pwm5b_setdc(dc)		TIMER5->TBMATCHR = (dc)

//32-bit pwm
//initilize pwm
//TxCCP_PS = 1: prescaler not a true prescaler
void wpwm0a_init(uint16_t TxCCP_PS, uint32_t WTxCCP_PR);
void wpwm0b_init(uint16_t TxCCP_PS, uint32_t WTxCCP_PR);
void wpwm1a_init(uint16_t TxCCP_PS, uint32_t WTxCCP_PR);
void wpwm1b_init(uint16_t TxCCP_PS, uint32_t WTxCCP_PR);
void wpwm2a_init(uint16_t TxCCP_PS, uint32_t WTxCCP_PR);
void wpwm2b_init(uint16_t TxCCP_PS, uint32_t WTxCCP_PR);
void wpwm3a_init(uint16_t TxCCP_PS, uint32_t WTxCCP_PR);
void wpwm3b_init(uint16_t TxCCP_PS, uint32_t WTxCCP_PR);
void wpwm4a_init(uint16_t TxCCP_PS, uint32_t WTxCCP_PR);
void wpwm4b_init(uint16_t TxCCP_PS, uint32_t WTxCCP_PR);
void wpwm5a_init(uint16_t TxCCP_PS, uint32_t WTxCCP_PR);
void wpwm5b_init(uint16_t TxCCP_PS, uint32_t WTxCCP_PR);

//set wpwm duty cycle
#define wpwm0a_setdc(dc)		WTIMER0->TAMATCHR = (dc)
#define wpwm0b_setdc(dc)		WTIMER0->TBMATCHR = (dc)
#define wpwm1a_setdc(dc)		WTIMER1->TAMATCHR = (dc)
#define wpwm1b_setdc(dc)		WTIMER1->TBMATCHR = (dc)
#define wpwm2a_setdc(dc)		WTIMER2->TAMATCHR = (dc)
#define wpwm2b_setdc(dc)		WTIMER2->TBMATCHR = (dc)
#define wpwm3a_setdc(dc)		WTIMER3->TAMATCHR = (dc)
#define wpwm3b_setdc(dc)		WTIMER3->TBMATCHR = (dc)
#define wpwm4a_setdc(dc)		WTIMER4->TAMATCHR = (dc)
#define wpwm4b_setdc(dc)		WTIMER4->TBMATCHR = (dc)
#define wpwm5a_setdc(dc)		WTIMER5->TAMATCHR = (dc)
#define wpwm5b_setdc(dc)		WTIMER5->TBMATCHR = (dc)

#endif /* PWM_H_ */
