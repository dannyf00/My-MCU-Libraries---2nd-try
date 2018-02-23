#include "hpwm.h"								//we use hardware pwm, vs. timer ccp

//use hardware PWM0 module
//ps/3bits: 0..7
//pr/16bits
//PWM0:PWM0a/PD0, PWM0b/PD1
void HPWM0_init(uint32_t ps, uint32_t pr) {
	//configure the gpio pins
	SYSCTL->RCGC2 |= (1<<3);					//enable clock. 0->GPIOA, 1->GPIOB, 2->GPIOC, 3->GPIOD, 4->GPIOE, ...
	GPIOD->AFSEL |= (1<<0);						//1->enable alternate function, 0->disable alternate function
	GPIOD->AFSEL |= (1<<1);						//1->enable alternate function, 0->disable alternate function

	//1. Enable the PWM clock by writing a value of 0x0010.0000 to the RCGC0 register in the System	Control module.
	SYSCTL->RCGC0 |= (1<<20);				//0->disable pwm clock, 1->enable pwm clock
	//2. In the GPIO module, enable the appropriate pins for their alternate function using the	GPIOAFSEL register.
	//3. Configure the Run-Mode Clock Configuration (RCC) register in the System Control module	to
	//use the PWM divide (USEPWMDIV) and set the divider (PWMDIV) to divide by 2 (000).
	SYSCTL->RCC |= (1<<20);					//1->use PWMdivider, 0->do not use the pwm divider
	SYSCTL->RCC = (SYSCTL->RCC &~(0x07<<17)) | ((ps & 0x0)<<17);	//set pwm divider: 0->2:1, 1->4:1, 2->8:1, 3->16:1, 4->32:1, 5/6/7->64:1 (default)

	PWM->ENABLE &=~((1<<1) | (1<<0));				//1->enable pwm output on pwm 0A/B, 0->disable pwm

	//stop the pwm
	PWMGEN0->CTL &=~(1<<0);						//1->start the pwm, 0->stop the pwm

	//signal not inverted
	PWMGEN0->INTEN &=~(1<<0);					//0->not inverted, 1->inverted

	//4. Configure the PWM generator for countdown mode with immediate updates to the parameters.
	// Write the PWM0CTL register with a value of 0x0000.0000.
	PWMGEN0->CTL = 	(0<<5) |					//0->update cmpb on 0, 1->update now
					(0<<4) |					//0->update cmpa on 0, 1->update now
					(0<<3) |					//0->update load on 0, 1->update now
					(1<<2) |					//1->timer stops on debut, 0->timer keeps running
					(0<<1) |					//1->up/down mode, 0->down mode
					(0<<0) |					//1->start the pwm, 1->stop the pwm
					0x00;
	// Write the PWM0GENA register with a value of 0x0000.008C.
	PWMGEN0->GENA = //0x008c;
					(0<<10) |					//CmpBD:  0->do nothing, 1->flip output, 2->clear output, 3->set output
					(0<< 8) |					//CmpBU:  0->do nothing, 1->flip output, 2->clear output, 3->set output
					(2<< 6) |					//CmpAD:  0->do nothing, 1->flip output, 2->clear output, 3->set output
					(0<< 4) |					//CmpAU:  0->do nothing, 1->flip output, 2->clear output, 3->set output
					(3<< 2) |					//atLoad: 0->do nothing, 1->flip output, 2->clear output, 3->set output
					(0<< 0) |					//atZero: 0->do nothing, 1->flip output, 2->clear output, 3->set output
					0x00;

	// Write the PWM0GENB register with a value of 0x0000.080C.
	PWMGEN0->GENB = //0x080c;
					(2<<10) |					//CmpBD:  0->do nothing, 1->flip output, 2->clear output, 3->set output
					(0<< 8) |					//CmpBU:  0->do nothing, 1->flip output, 2->clear output, 3->set output
					(0<< 6) |					//CmpAD:  0->do nothing, 1->flip output, 2->clear output, 3->set output
					(0<< 4) |					//CmpAU:  0->do nothing, 1->flip output, 2->clear output, 3->set output
					(3<< 2) |					//atLoad: 0->do nothing, 1->flip output, 2->clear output, 3->set output
					(0<< 0) |					//atZero: 0->do nothing, 1->flip output, 2->clear output, 3->set output
					0x00;
	//5. Set the period. For a 25-KHz frequency, the period = 1/25,000, or 40 microseconds. The PWM
	//clock source is 10 MHz; the system clock divided by 2. This translates to 400 clock ticks per
	//period. Use this value to set the PWM0LOAD register. In Count-Down mode, set the Load field
	//in the PWM0LOAD register to the requested period minus one.
	// Write the PWM0LOAD register with a value of 0x0000.018F.
	PWMGEN0->LOAD = pr - 1;
	//6. Set the pulse width of the PWM0 pin for a 25% duty cycle.
	// Write the PWM0CMPA register with a value of 0x0000.012B.
	PWMGEN0->CMPA = 0;							//minimum duty cycle
	//7. Set the pulse width of the PWM1 pin for a 75% duty cycle.
	// Write the PWM0CMPB register with a value of 0x0000.0063.
	PWMGEN0->CMPB = 0;							//minimum duty cycle
	//8. Start the timers in PWM generator 0.
	// Write the PWM0CTL register with a value of 0x0000.0001.
	PWMGEN0->CTL |= (1<<0);						//1->start the pwm, 0->stop the pwm
	//9. Enable PWM outputs.
	// Write the PWMENABLE register with a value of 0x0000.0003.
	PWM->ENABLE |= ((1<<1) | (1<<0));				//1->enable pwm output on pwm 0A/B, 0->disable pwm
}

//use hardware PWM0 module
//ps/3bits: 0..7
//pr/16bits
//PWM1:PWM1a/PB0, PWM1b/PB1
void HPWM1_init(uint32_t ps, uint32_t pr) {
	//configure the gpio pins
	SYSCTL->RCGC2 |= (1<<2);					//enable clock. 0->GPIOA, 1->GPIOB, 2->GPIOC, 3->GPIOD, 4->GPIOE, ...
	GPIOB->AFSEL |= (1<<0);						//1->enable alternate function, 0->disable alternate function
	GPIOB->AFSEL |= (1<<1);						//1->enable alternate function, 0->disable alternate function

	//1. Enable the PWM clock by writing a value of 0x0010.0000 to the RCGC0 register in the System	Control module.
	SYSCTL->RCGC0 |= (1<<20);					//0->disable pwm clock, 1->enable pwm clock
	//2. In the GPIO module, enable the appropriate pins for their alternate function using the	GPIOAFSEL register.
	//3. Configure the Run-Mode Clock Configuration (RCC) register in the System Control module	to
	//use the PWM divide (USEPWMDIV) and set the divider (PWMDIV) to divide by 2 (000).
	SYSCTL->RCC |= (1<<20);						//1->use PWMdivider, 0->do not use the pwm divider
	SYSCTL->RCC = (SYSCTL->RCC &~(0x07<<17)) | ((ps & 0x0)<<17);	//set pwm divider: 0->2:1, 1->4:1, 2->8:1, 3->16:1, 4->32:1, 5/6/7->64:1 (default)

	PWM->ENABLE &=~((1<<3) | (1<<2));				//1->enable pwm output on pwm 1A/B, 0->disable pwm output

	//stop the pwm
	PWMGEN1->CTL &=~(1<<0);						//1->start the pwm, 0->stop the pwm

	//signal not inverted
	PWMGEN0->INTEN &=~(1<<1);					//0->not inverted, 1->inverted

	//4. Configure the PWM generator for countdown mode with immediate updates to the parameters.
	// Write the PWM0CTL register with a value of 0x0000.0000.
	PWMGEN1->CTL = 	(0<<5) |					//0->update cmpb on 0, 1->update now
					(0<<4) |					//0->update cmpa on 0, 1->update now
					(0<<3) |					//0->update load on 0, 1->update now
					(1<<2) |					//1->timer stops on debut, 0->timer keeps running
					(0<<1) |					//1->up/down mode, 0->down mode
					(0<<0) |					//1->start the pwm, 1->stop the pwm
					0x00;
	// Write the PWM0GENA register with a value of 0x0000.008C.
	PWMGEN1->GENA = //0x008c;
					(0<<10) |					//CmpBD:  0->do nothing, 1->flip output, 2->clear output, 3->set output
					(0<< 8) |					//CmpBU:  0->do nothing, 1->flip output, 2->clear output, 3->set output
					(2<< 6) |					//CmpAD:  0->do nothing, 1->flip output, 2->clear output, 3->set output
					(0<< 4) |					//CmpAU:  0->do nothing, 1->flip output, 2->clear output, 3->set output
					(3<< 2) |					//atLoad: 0->do nothing, 1->flip output, 2->clear output, 3->set output
					(0<< 0) |					//atZero: 0->do nothing, 1->flip output, 2->clear output, 3->set output
					0x00;

	// Write the PWM0GENB register with a value of 0x0000.080C.
	PWMGEN1->GENB = //0x080c;
					(2<<10) |					//CmpBD:  0->do nothing, 1->flip output, 2->clear output, 3->set output
					(0<< 8) |					//CmpBU:  0->do nothing, 1->flip output, 2->clear output, 3->set output
					(0<< 6) |					//CmpAD:  0->do nothing, 1->flip output, 2->clear output, 3->set output
					(0<< 4) |					//CmpAU:  0->do nothing, 1->flip output, 2->clear output, 3->set output
					(3<< 2) |					//atLoad: 0->do nothing, 1->flip output, 2->clear output, 3->set output
					(0<< 0) |					//atZero: 0->do nothing, 1->flip output, 2->clear output, 3->set output
					0x00;
	//5. Set the period. For a 25-KHz frequency, the period = 1/25,000, or 40 microseconds. The PWM
	//clock source is 10 MHz; the system clock divided by 2. This translates to 400 clock ticks per
	//period. Use this value to set the PWM0LOAD register. In Count-Down mode, set the Load field
	//in the PWM0LOAD register to the requested period minus one.
	// Write the PWM0LOAD register with a value of 0x0000.018F.
	PWMGEN1->LOAD = pr - 1;
	//6. Set the pulse width of the PWM0 pin for a 25% duty cycle.
	// Write the PWM0CMPA register with a value of 0x0000.012B.
	PWMGEN1->CMPA = 0;						//minimum duty cycle
	//7. Set the pulse width of the PWM1 pin for a 75% duty cycle.
	// Write the PWM0CMPB register with a value of 0x0000.0063.
	PWMGEN1->CMPB = 0;						//minimum duty cycle
	//8. Start the timers in PWM generator 0.
	// Write the PWM0CTL register with a value of 0x0000.0001.
	PWMGEN1->CTL |= (1<<0);						//1->start the pwm, 0->stop the pwm
	//9. Enable PWM outputs.
	// Write the PWMENABLE register with a value of 0x0000.0003.
	PWM->ENABLE |= ((1<<3) | (1<<2));				//1->enable pwm output on pwm 1A/B, 0->disable pwm output
}

//use hardware PWM0 module
//ps/3bits: 0..7
//pr/16bits
//PWM2:PWM2a/PE0, PWM2b/PE1
void HPWM2_init(uint32_t ps, uint32_t pr) {
	//configure the gpio pins
	SYSCTL->RCGC2 |= (1<<4);					//enable clock. 0->GPIOA, 1->GPIOB, 2->GPIOC, 3->GPIOD, 4->GPIOE, ...
	GPIOE->AFSEL |= (1<<0);						//1->enable alternate function, 0->disable alternate function
	GPIOE->AFSEL |= (1<<1);						//1->enable alternate function, 0->disable alternate function

	//1. Enable the PWM clock by writing a value of 0x0010.0000 to the RCGC0 register in the System	Control module.
	SYSCTL->RCGC0 |= (1<<20);					//0->disable pwm clock, 1->enable pwm clock
	//2. In the GPIO module, enable the appropriate pins for their alternate function using the	GPIOAFSEL register.
	//3. Configure the Run-Mode Clock Configuration (RCC) register in the System Control module	to
	//use the PWM divide (USEPWMDIV) and set the divider (PWMDIV) to divide by 2 (000).
	SYSCTL->RCC |= (1<<20);						//1->use PWMdivider, 0->do not use the pwm divider
	SYSCTL->RCC = (SYSCTL->RCC &~(0x07<<17)) | ((ps & 0x0)<<17);	//set pwm divider: 0->2:1, 1->4:1, 2->8:1, 3->16:1, 4->32:1, 5/6/7->64:1 (default)

	PWM->ENABLE &=~((1<<5) | (1<<4));				//1->enable pwm output on pwm 2A/B, 0->disable

	//stop the pwm
	PWMGEN2->CTL &=~(1<<0);						//1->start the pwm, 0->stop the pwm

	//signal not inverted
	PWMGEN0->INTEN &=~(1<<2);					//0->not inverted, 1->inverted

	//4. Configure the PWM generator for countdown mode with immediate updates to the parameters.
	// Write the PWM0CTL register with a value of 0x0000.0000.
	PWMGEN2->CTL = 	(0<<5) |					//0->update cmpb on 0, 1->update now
					(0<<4) |					//0->update cmpa on 0, 1->update now
					(0<<3) |					//0->update load on 0, 1->update now
					(1<<2) |					//1->timer stops on debut, 0->timer keeps running
					(0<<1) |					//1->up/down mode, 0->down mode
					(0<<0) |					//1->start the pwm, 1->stop the pwm
					0x00;
	// Write the PWM0GENA register with a value of 0x0000.008C.
	PWMGEN2->GENA = //0x008c;
					(0<<10) |					//CmpBD:  0->do nothing, 1->flip output, 2->clear output, 3->set output
					(0<< 8) |					//CmpBU:  0->do nothing, 1->flip output, 2->clear output, 3->set output
					(2<< 6) |					//CmpAD:  0->do nothing, 1->flip output, 2->clear output, 3->set output
					(0<< 4) |					//CmpAU:  0->do nothing, 1->flip output, 2->clear output, 3->set output
					(3<< 2) |					//atLoad: 0->do nothing, 1->flip output, 2->clear output, 3->set output
					(0<< 0) |					//atZero: 0->do nothing, 1->flip output, 2->clear output, 3->set output
					0x00;

	// Write the PWM0GENB register with a value of 0x0000.080C.
	PWMGEN2->GENB = //0x080c;
					(2<<10) |					//CmpBD:  0->do nothing, 1->flip output, 2->clear output, 3->set output
					(0<< 8) |					//CmpBU:  0->do nothing, 1->flip output, 2->clear output, 3->set output
					(0<< 6) |					//CmpAD:  0->do nothing, 1->flip output, 2->clear output, 3->set output
					(0<< 4) |					//CmpAU:  0->do nothing, 1->flip output, 2->clear output, 3->set output
					(3<< 2) |					//atLoad: 0->do nothing, 1->flip output, 2->clear output, 3->set output
					(0<< 0) |					//atZero: 0->do nothing, 1->flip output, 2->clear output, 3->set output
					0x00;
	//5. Set the period. For a 25-KHz frequency, the period = 1/25,000, or 40 microseconds. The PWM
	//clock source is 10 MHz; the system clock divided by 2. This translates to 400 clock ticks per
	//period. Use this value to set the PWM0LOAD register. In Count-Down mode, set the Load field
	//in the PWM0LOAD register to the requested period minus one.
	// Write the PWM0LOAD register with a value of 0x0000.018F.
	PWMGEN2->LOAD = pr - 1;
	//6. Set the pulse width of the PWM0 pin for a 25% duty cycle.
	// Write the PWM0CMPA register with a value of 0x0000.012B.
	PWMGEN2->CMPA = 0;						//minimum duty cycle
	//7. Set the pulse width of the PWM1 pin for a 75% duty cycle.
	// Write the PWM0CMPB register with a value of 0x0000.0063.
	PWMGEN2->CMPB = 0;						//minimum duty cycle
	//8. Start the timers in PWM generator 0.
	// Write the PWM0CTL register with a value of 0x0000.0001.
	PWMGEN2->CTL |= (1<<0);						//1->start the pwm, 0->stop the pwm
	//9. Enable PWM outputs.
	// Write the PWMENABLE register with a value of 0x0000.0003.
	PWM->ENABLE |= ((1<<5) | (1<<4));				//1->enable pwm output on pwm 2A/B, 0->disable
}

