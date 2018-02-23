#ifndef PWM_SW_H_INCLUDED
#define PWM_SW_H_INCLUDED

#include "gpio.h"

//hardware configuration
#define PWM_PORT		PORTB
#define PWM_DDR			DDRB
#define PWM_CNT			3				//pwm channels
//end hardware configuration

//global defines
//prescaler settings
#define TMR_CS210_NOCLK		0x00		//cs210=no clock selected
#define TMR_CS210_CLK		0x01		//clk/1
#define TMR_CS210_CLK_8		0x02		//clk/8
#define TMR_CS210_CLK_64	0x03		//clk/64
#define TMR_CS210_CLK_256	0x04		//clk/256
#define TMR_CS210_CLK_1024	0x05		//clk/1024
#define TMR_CS210_CLK_EXT_N	0x06		//external clock on Tn pin, negative transistion
#define TMR_CS210_CLK_EXT_P	0x07		//external clock on Tn pin, positive transistion

#define TMR_PS_1x			TMR_CS210_CLK
#define TMR_PS_8x			TMR_CS210_CLK_8
#define TMR_PS_64x			TMR_CS210_CLK_64
#define TMR_PS_256x			TMR_CS210_CLK_256
#define TMR_PS_1024x		TMR_CS210_CLK_1024
#define TMR_PS_MASK			0x07


typedef struct {
	uint8_t dc;							//duty cycle
	uint8_t pin;						//pins for the channel
} PWM_T;

//global variables

//reset pwm
void pwm_init(uint8_t ps, uint8_t period);

//set dc
void pwm_setdc(uint8_t ch, uint8_t pin, uint8_t dc);

#define pwm0_setdc(pin, dc)					pwm_setdc(0, pin, dc)
#define pwm1_setdc(pin, dc)					pwm_setdc(1, pin, dc)
#define pwm2_setdc(pin, dc)					pwm_setdc(2, pin, dc)
#define pwm3_setdc(pin, dc)					pwm_setdc(3, pin, dc)
#define pwm4_setdc(pin, dc)					pwm_setdc(4, pin, dc)
#define pwm5_setdc(pin, dc)					pwm_setdc(5, pin, dc)

#endif // PWM_SW_H_INCLUDED
