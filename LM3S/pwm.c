#include "pwm.h"					//timer's pwm function

//CCPx pin out
//T0CCP0/PD4
//T0CCP1/PC5
//T0CCP2/PD5
//T1CCP3/PC6
//T1CCP4/PC7
//T2CCP5/PB5

//16-bit pwm routines
void pwm0_init(uint8_t TxCCP_PS, uint16_t TxCCP_PR) {
	//16-bit split timers, up/down counters
	//T0CCP0 / PD4 used
	//configure gpio: T0CCP0 on PF0
	SYSCTL->RCGC2 |= (1<<3);			//0->GPIOA, 1->GPIOB, 2=GPIOC, 3=GPIOD, 4=GPIOE, 5=GPIOF, ...
	//while ((SYSCTL->PRGPIO & (1<<5)) == 0) continue;	//1->ready, 0->not ready
	//configure PF0 for alternate function / T0CCP0
	GPIOD->DEN |= (1<<4);				//1=digital enabled, 0=digital disabled
	GPIOD->AFSEL |= (1<<4);				//1=alternate function enabled
	//GPIOF->PCTL = (GPIOF->PCTL &~(0x0f << (0*4))) | (0x07<<(0*4));	//mux 7 to route CCP to PF0
	//now PF0 has been configured for T0CCP0

	//route the timer0
	SYSCTL->RCGC1 |= (1<<16);		//1->periopheral clock enabled, 0->peripheral clock disabled
	//while ((SYSCTL->PRTIMER & (1<<0)) == 0) continue;	//1->ready, 0->not ready
	//configure timebase for 16-bit split timer
	//stop the timer
	TIMER0->CTL &=~(1<<0);							//0->disable timer, 1->enable timer
	//configure the timer, split, upcounter
	TIMER0->CFG  = 0x04;							//0x00->32/64bit, 0x01->rtc, 0x02-0x03->reserved, 0x04->16/32bit split timers
	TIMER0->TAMR = 	(0<<11) |						//0->legacy ops
					(0<<10) |						//0->update match register on the next cycle, 1->update match register now
					(0<< 9) |						//0->pwm interrupt disabled, 1->pwm interrupt enabled
					(0<< 8) |						//0->update load register ont he next cycle; 1->update load register now
					(0<< 7) |						//0->disable snap shot, 1->enable snap shot
					(0<< 6) |						//0->timer counts right away; 1->timer waits on trigger before counting
					(0<< 5) |						//0->match interrupt disabled, 1->match interrupt enabled
					(0<< 4) |						//0->counts down, 1->counts up
					(1<< 3) |						//0->capture / compare enabled 1->pwm enabled
					(0<< 2) |						//0->edge count for capture; 1->edge time for capture
					(2<< 0) |						//0x00->reserved, 0x01->one shot, 0x02->periodic, 0x03->capture
					0x00;

	//invert the output as the timer is a down counter
	TIMER0->CTL |= (1<<6);							//0->output not affected, 1->output inverted
	TIMER0->CTL = (TIMER0->CTL & ~(0x03 << 2)) | (0x00 << 2);		//0->positive edge, 1->negative edge, 2->reserved, 3->both edges
	TIMER0->TAMR &=~(1<<9);							//1->enable PWM interrupt, 0->disable PWM interrupt
	TIMER0->TAMATCHR = 0;							//for 0% duty cycle
	//set the prescaler
	TIMER0->TAPMR = TIMER0->TAPR = (TxCCP_PS - 1) & 0xff;			//set the prescaler
	TIMER0->TAILR= (TxCCP_PR - 1) & 0xffff;							//set the top
	//reset counter
	//TIMER0->TAR = 0;

	//clear ISR flags, disable isr
	//disable all interrupt
	TIMER0->IMR &=~(0x1f << 0);						//0->disable time-out interrupt, 1->enable time-out interrupt
	TIMER0->ICR |= (0x1f << 0);						//1->clear interrupt flag, 0->no effect

	//start the timer
	TIMER0->CTL |= (1<<0);							//0->disable timer, 1->enable timer
}

void pwm1_init(uint8_t TxCCP_PS, uint16_t TxCCP_PR) {
	//T0CCP1 / PC5 used
	//configure gpio: T0CCP1 on PF1
	SYSCTL->RCGC2 |= (1<<2);			//0->GPIOA, 1->GPIOB, 2=GPIOC, 3=GPIOD, 4=GPIOE, 5=GPIOF, ...
	//while ((SYSCTL->PRGPIO & (1<<5)) == 0) continue;	//1->ready, 0->not ready
	//configure PF1 for alternate function / T0CCP1
	GPIOC->DEN |= (1<<5);				//1=digital enabled, 0=digital disabled
	GPIOC->AFSEL |= (1<<5);				//1=alternate function enabled
	//GPIOF->PCTL = (GPIOF->PCTL &~(0x0f << (1*4))) | (0x07<<(1*4));	//mux 7 to route CCP to PF1
	//now PF1 has been configured for T0CCP1

	//route the timer0
	SYSCTL->RCGC1 |= (1<<16);		//1->periopheral clock enabled, 0->peripheral clock disabled
	//while ((SYSCTL->PRTIMER & (1<<0)) == 0) continue;	//1->ready, 0->not ready
	//configure timebase for 16-bit split timer
	//stop the timer
	TIMER0->CTL &=~(1<<8);							//0->disable timer, 1->enable timer
	//configure the timer, split, downcounter
	TIMER0->CFG  = 0x04;							//0x00->32/64bit, 0x01->rtc, 0x02-0x03->reserved, 0x04->16/32bit split timers
	TIMER0->TBMR = 	(0<<11) |						//0->legacy ops
					(0<<10) |						//0->update match register on the next cycle, 1->update match register now
					(0<< 9) |						//0->pwm interrupt disabled, 1->pwm interrupt enabled
					(0<< 8) |						//0->update load register ont he next cycle; 1->update load register now
					(0<< 7) |						//0->disable snap shot, 1->enable snap shot
					(0<< 6) |						//0->timer counts right away; 1->timer waits on trigger before counting
					(0<< 5) |						//0->match interrupt disabled, 1->match interrupt enabled
					(0<< 4) |						//0->counts down, 1->counts up
					(1<< 3) |						//0->capture / compare enabled 1->pwm enabled
					(0<< 2) |						//0->edge count for capture; 1->edge time for capture
					(2<< 0) |						//0x00->reserved, 0x01->one shot, 0x02->periodic, 0x03->capture
					0x00;

	//invert the output as the timer is a down counter
	TIMER0->CTL |= (1<<14);							//0->output not affected, 1->output inverted
	TIMER0->CTL = (TIMER0->CTL & ~(0x03 << 10)) | (0x00 << 10);		//0->positive edge, 1->negative edge, 2->reserved, 3->both edges
	TIMER0->TBMR &=~(1<<9);							//1->enable PWM interrupt, 0->disable PWM interrupt
	TIMER0->TBMATCHR = 0;							//for 0% duty cycle
	//set the prescaler
	TIMER0->TBPMR = TIMER0->TBPR = (TxCCP_PS - 1) & 0xff;							//set the prescaler
	TIMER0->TBILR= (TxCCP_PR - 1) & 0xffff;							//set the top
	//reset counter
	//TIMER0->TBR = 0;

	//clear ISR flags, disable isr
	//disable all interrupt
	TIMER0->IMR &=~(0x1f << 8);						//0->disable time-out interrupt, 1->enable time-out interrupt
	TIMER0->ICR |= (0x1f << 8);						//1->clear interrupt flag, 0->no effect

	//start the timer
	TIMER0->CTL |= (1<<8);							//0->disable timer, 1->enable timer
}

void pwm2_init(uint8_t TxCCP_PS, uint16_t TxCCP_PR) {
	//16-bit split timers, up/down counters
	//T0CCP2/PD5
	//configure gpio: T0CCP0 on PF0
	SYSCTL->RCGC2 |= (1<<3);			//0->GPIOA, 1->GPIOB, 2=GPIOC, 3=GPIOD, 4=GPIOE, 5=GPIOF, ...
	//while ((SYSCTL->PRGPIO & (1<<5)) == 0) continue;	//1->ready, 0->not ready
	//configure PF0 for alternate function / T0CCP0
	GPIOD->DEN |= (1<<5);				//1=digital enabled, 0=digital disabled
	GPIOD->AFSEL |= (1<<5);				//1=alternate function enabled
	//GPIOF->PCTL = (GPIOF->PCTL &~(0x0f << (0*4))) | (0x07<<(0*4));	//mux 7 to route CCP to PF0
	//now PF0 has been configured for T0CCP0

	//route the timer1
	SYSCTL->RCGC1 |= (1<<17);		//1->periopheral clock enabled, 0->peripheral clock disabled
	//while ((SYSCTL->PRTIMER & (1<<0)) == 0) continue;	//1->ready, 0->not ready
	//configure timebase for 16-bit split timer
	//stop the timer
	TIMER1->CTL &=~(1<<0);							//0->disable timer, 1->enable timer
	//configure the timer, split, upcounter
	TIMER1->CFG  = 0x04;							//0x00->32/64bit, 0x01->rtc, 0x02-0x03->reserved, 0x04->16/32bit split timers
	TIMER1->TAMR = 	(0<<11) |						//0->legacy ops
					(0<<10) |						//0->update match register on the next cycle, 1->update match register now
					(0<< 9) |						//0->pwm interrupt disabled, 1->pwm interrupt enabled
					(0<< 8) |						//0->update load register ont he next cycle; 1->update load register now
					(0<< 7) |						//0->disable snap shot, 1->enable snap shot
					(0<< 6) |						//0->timer counts right away; 1->timer waits on trigger before counting
					(0<< 5) |						//0->match interrupt disabled, 1->match interrupt enabled
					(0<< 4) |						//0->counts down, 1->counts up
					(1<< 3) |						//0->capture / compare enabled 1->pwm enabled
					(0<< 2) |						//0->edge count for capture; 1->edge time for capture
					(2<< 0) |						//0x00->reserved, 0x01->one shot, 0x02->periodic, 0x03->capture
					0x00;

	//invert the output as the timer is a down counter
	TIMER1->CTL |= (1<<6);							//0->output not affected, 1->output inverted
	TIMER1->CTL = (TIMER1->CTL & ~(0x03 << 2)) | (0x00 << 2);		//0->positive edge, 1->negative edge, 2->reserved, 3->both edges
	TIMER1->TAMR &=~(1<<9);							//1->enable PWM interrupt, 0->disable PWM interrupt
	TIMER1->TAMATCHR = 0;							//for 0% duty cycle
	//set the prescaler
	TIMER1->TAPMR = TIMER1->TAPR = (TxCCP_PS - 1) & 0xff;							//set the prescaler
	TIMER1->TAILR= (TxCCP_PR - 1) & 0xffff;							//set the top
	//reset counter
	//TIMER1->TAR = 0;

	//clear ISR flags, disable isr
	//disable all interrupt
	TIMER1->IMR &=~(0x1f << 0);						//0->disable time-out interrupt, 1->enable time-out interrupt
	TIMER1->ICR |= (0x1f << 0);						//1->clear interrupt flag, 0->no effect

	//start the timer
	TIMER1->CTL |= (1<<0);							//0->disable timer, 1->enable timer
}

void pwm3_init(uint8_t TxCCP_PS, uint16_t TxCCP_PR) {
	//T1CCP3/PC6
	//configure gpio: T0CCP1 on PF1
	SYSCTL->RCGC2 |= (1<<2);			//0->GPIOA, 1->GPIOB, 2=GPIOC, 3=GPIOD, 4=GPIOE, 5=GPIOF, ...
	//while ((SYSCTL->PRGPIO & (1<<5)) == 0) continue;	//1->ready, 0->not ready
	//configure PF1 for alternate function / T0CCP1
	GPIOC->DEN |= (1<<6);				//1=digital enabled, 0=digital disabled
	GPIOC->AFSEL |= (1<<6);				//1=alternate function enabled
	//GPIOF->PCTL = (GPIOF->PCTL &~(0x0f << (1*4))) | (0x07<<(1*4));	//mux 7 to route CCP to PF1
	//now PF1 has been configured for T0CCP1

	//route the TIMER1
	SYSCTL->RCGC1 |= (1<<17);		//1->periopheral clock enabled, 0->peripheral clock disabled
	//while ((SYSCTL->PRTIMER & (1<<0)) == 0) continue;	//1->ready, 0->not ready
	//configure timebase for 16-bit split timer
	//stop the timer
	TIMER1->CTL &=~(1<<8);							//0->disable timer, 1->enable timer
	//configure the timer, split, upcounter
	TIMER1->CFG  = 0x04;							//0x00->32/64bit, 0x01->rtc, 0x02-0x03->reserved, 0x04->16/32bit split timers
	TIMER1->TBMR = 	(0<<11) |						//0->legacy ops
					(0<<10) |						//0->update match register on the next cycle, 1->update match register now
					(0<< 9) |						//0->pwm interrupt disabled, 1->pwm interrupt enabled
					(0<< 8) |						//0->update load register ont he next cycle; 1->update load register now
					(0<< 7) |						//0->disable snap shot, 1->enable snap shot
					(0<< 6) |						//0->timer counts right away; 1->timer waits on trigger before counting
					(0<< 5) |						//0->match interrupt disabled, 1->match interrupt enabled
					(0<< 4) |						//0->counts down, 1->counts up
					(1<< 3) |						//0->capture / compare enabled 1->pwm enabled
					(0<< 2) |						//0->edge count for capture; 1->edge time for capture
					(2<< 0) |						//0x00->reserved, 0x01->one shot, 0x02->periodic, 0x03->capture
					0x00;

	//invert the output as the timer is a down counter
	TIMER1->CTL |= (1<<14);							//0->output not affected, 1->output inverted
	TIMER1->CTL = (TIMER1->CTL & ~(0x03 << 10)) | (0x00 << 10);		//0->positive edge, 1->negative edge, 2->reserved, 3->both edges
	TIMER1->TBMR &=~(1<<9);							//1->enable PWM interrupt, 0->disable PWM interrupt
	TIMER1->TBMATCHR = 0;							//for 0% duty cycle
	//set the prescaler
	TIMER1->TBPMR = TIMER1->TBPR = (TxCCP_PS - 1) & 0xff;							//set the prescaler
	TIMER1->TBILR= (TxCCP_PR - 1) & 0xffff;							//set the top
	//reset counter
	//TIMER1->TBR = 0;

	//clear ISR flags, disable isr
	//disable all interrupt
	TIMER1->IMR &=~(0x1f << 8);						//0->disable time-out interrupt, 1->enable time-out interrupt
	TIMER1->ICR |= (0x1f << 8);						//1->clear interrupt flag, 0->no effect

	//start the timer
	TIMER1->CTL |= (1<<8);							//0->disable timer, 1->enable timer
}

void pwm4_init(uint8_t TxCCP_PS, uint16_t TxCCP_PR) {
	//16-bit split timers, up/down counters
	//T1CCP4/PC7
	//configure gpio: T0CCP0 on PF0
	SYSCTL->RCGC2 |= (1<<2);			//0->GPIOA, 1->GPIOB, 2=GPIOC, 3=GPIOD, 4=GPIOE, 5=GPIOF, ...
	//while ((SYSCTL->PRGPIO & (1<<5)) == 0) continue;	//1->ready, 0->not ready
	//configure PF0 for alternate function / T0CCP0
	GPIOC->DEN |= (1<<7);				//1=digital enabled, 0=digital disabled
	GPIOC->AFSEL |= (1<<7);				//1=alternate function enabled
	//GPIOF->PCTL = (GPIOF->PCTL &~(0x0f << (0*4))) | (0x07<<(0*4));	//mux 7 to route CCP to PF0
	//now PF0 has been configured for T0CCP0

	//route the TIMER2
	SYSCTL->RCGC1 |= (1<<18);		//1->periopheral clock enabled, 0->peripheral clock disabled
	//while ((SYSCTL->PRTIMER & (1<<0)) == 0) continue;	//1->ready, 0->not ready
	//configure timebase for 16-bit split timer
	//stop the timer
	TIMER2->CTL &=~(1<<0);							//0->disable timer, 1->enable timer
	//configure the timer, split, upcounter
	TIMER2->CFG  = 0x04;							//0x00->32/64bit, 0x01->rtc, 0x02-0x03->reserved, 0x04->16/32bit split timers
	TIMER2->TAMR = 	(0<<11) |						//0->legacy ops
					(0<<10) |						//0->update match register on the next cycle, 1->update match register now
					(0<< 9) |						//0->pwm interrupt disabled, 1->pwm interrupt enabled
					(0<< 8) |						//0->update load register ont he next cycle; 1->update load register now
					(0<< 7) |						//0->disable snap shot, 1->enable snap shot
					(0<< 6) |						//0->timer counts right away; 1->timer waits on trigger before counting
					(0<< 5) |						//0->match interrupt disabled, 1->match interrupt enabled
					(0<< 4) |						//0->counts down, 1->counts up
					(1<< 3) |						//0->capture / compare enabled 1->pwm enabled
					(0<< 2) |						//0->edge count for capture; 1->edge time for capture
					(2<< 0) |						//0x00->reserved, 0x01->one shot, 0x02->periodic, 0x03->capture
					0x00;

	//invert the output as the timer is a down counter
	TIMER2->CTL |= (1<<6);							//0->output not affected, 1->output inverted
	TIMER2->CTL = (TIMER2->CTL & ~(0x03 << 2)) | (0x00 << 2);		//0->positive edge, 1->negative edge, 2->reserved, 3->both edges
	TIMER2->TAMR &=~(1<<9);							//1->enable PWM interrupt, 0->disable PWM interrupt
	TIMER2->TAMATCHR = 0;							//for 0% duty cycle
	//set the prescaler
	TIMER2->TAPMR = TIMER2->TAPR = (TxCCP_PS - 1) & 0xff;							//set the prescaler
	TIMER2->TAILR= (TxCCP_PR - 1) & 0xffff;							//set the top
	//reset counter
	//TIMER2->TAR = 0;

	//clear ISR flags, disable isr
	//disable all interrupt
	TIMER2->IMR &=~(0x1f << 0);						//0->disable time-out interrupt, 1->enable time-out interrupt
	TIMER2->ICR |= (0x1f << 0);						//1->clear interrupt flag, 0->no effect

	//start the timer
	TIMER2->CTL |= (1<<0);							//0->disable timer, 1->enable timer
}

void pwm5_init(uint8_t TxCCP_PS, uint16_t TxCCP_PR) {
	//T2CCP5/PB5
	//configure gpio: T0CCP1 on PF1
	SYSCTL->RCGC2 |= (1<<1);			//0->GPIOA, 1->GPIOB, 2=GPIOC, 3=GPIOD, 4=GPIOE, 5=GPIOF, ...
	//while ((SYSCTL->PRGPIO & (1<<5)) == 0) continue;	//1->ready, 0->not ready
	//configure PF1 for alternate function / T0CCP1
	GPIOB->DEN |= (1<<5);				//1=digital enabled, 0=digital disabled
	GPIOB->AFSEL |= (1<<5);				//1=alternate function enabled
	//GPIOF->PCTL = (GPIOF->PCTL &~(0x0f << (1*4))) | (0x07<<(1*4));	//mux 7 to route CCP to PF1
	//now PF1 has been configured for T0CCP1

	//route the timer2
	SYSCTL->RCGC1 |= (1<<18);		//1->periopheral clock enabled, 0->peripheral clock disabled
	//while ((SYSCTL->PRTIMER & (1<<0)) == 0) continue;	//1->ready, 0->not ready
	//configure timebase for 16-bit split timer
	//stop the timer
	TIMER2->CTL &=~(1<<8);							//0->disable timer, 1->enable timer
	//configure the timer, split, upcounter
	TIMER2->CFG  = 0x04;							//0x00->32/64bit, 0x01->rtc, 0x02-0x03->reserved, 0x04->16/32bit split timers
	TIMER2->TBMR = 	(0<<11) |						//0->legacy ops
					(0<<10) |						//0->update match register on the next cycle, 1->update match register now
					(0<< 9) |						//0->pwm interrupt disabled, 1->pwm interrupt enabled
					(0<< 8) |						//0->update load register ont he next cycle; 1->update load register now
					(0<< 7) |						//0->disable snap shot, 1->enable snap shot
					(0<< 6) |						//0->timer counts right away; 1->timer waits on trigger before counting
					(0<< 5) |						//0->match interrupt disabled, 1->match interrupt enabled
					(0<< 4) |						//0->counts down, 1->counts up
					(1<< 3) |						//0->capture / compare enabled 1->pwm enabled
					(0<< 2) |						//0->edge count for capture; 1->edge time for capture
					(2<< 0) |						//0x00->reserved, 0x01->one shot, 0x02->periodic, 0x03->capture
					0x00;

	//invert the output as the timer is a down counter
	TIMER2->CTL |= (1<<14);							//0->output not affected, 1->output inverted
	TIMER2->CTL = (TIMER2->CTL & ~(0x03 << 10)) | (0x00 << 10);		//0->positive edge, 1->negative edge, 2->reserved, 3->both edges
	TIMER2->TBMR &=~(1<<9);							//1->enable PWM interrupt, 0->disable PWM interrupt
	TIMER2->TBMATCHR = 0;							//for 0% duty cycle
	//set the prescaler
	TIMER2->TBPMR = TIMER2->TBPR = (TxCCP_PS - 1) & 0xff;							//set the prescaler
	TIMER2->TBILR= (TxCCP_PR - 1) & 0xffff;							//set the top
	//reset counter
	//TIMER2->TBR = 0;

	//clear ISR flags, disable isr
	//disable all interrupt
	TIMER2->IMR &=~(0x1f << 8);						//0->disable time-out interrupt, 1->enable time-out interrupt
	TIMER2->ICR |= (0x1f << 8);						//1->clear interrupt flag, 0->no effect

	//start the timer
	TIMER2->CTL |= (1<<8);							//0->disable timer, 1->enable timer
}
