#include "pwm.h"						//16/32-bit pwm

//16-bit pwm routines
//T0CCP0/PF0
void pwm0a_init(uint8_t TxCCP_PS, uint16_t TxCCP_PR) {
	//16-bit split timers, up/down counters
	//T0CCP0 / PF0 used
	//configure gpio: T0CCP0 on PF0
	SYSCTL->RCGCGPIO |= (1<<5);			//0->GPIOA, 1->GPIOB, 2=GPIOC, 3=GPIOD, 4=GPIOE, 5=GPIOF, ...
	while ((SYSCTL->PRGPIO & (1<<5)) == 0) continue;	//1->ready, 0->not ready
	//configure PF0 for alternate function / T0CCP0
	GPIOF->DEN |= (1<<0);				//1=digital enabled, 0=digital disabled
	GPIOF->AFSEL |= (1<<0);				//1=alternate function enabled
	GPIOF->PCTL = (GPIOF->PCTL &~(0x0f << (0*4))) | (0x07<<(0*4));	//mux 7 to route CCP to PF0
	//now PF0 has been configured for T0CCP0

	//route the timer0
	SYSCTL->RCGCTIMER |= (1<<0);		//1->periopheral clock enabled, 0->peripheral clock disabled
	while ((SYSCTL->PRTIMER & (1<<0)) == 0) continue;	//1->ready, 0->not ready
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
	TIMER0->TAPMR = TIMER0->TAPR = (TxCCP_PS - 1) & 0xff;							//set the prescaler
	TIMER0->TAILR= (TxCCP_PR - 1) & 0xffff;							//set the top
	//reset counter
	TIMER0->TAR = 0;

	//clear ISR flags, disable isr
	//disable all interrupt
	TIMER0->IMR &=~(0x1f << 0);						//0->disable time-out interrupt, 1->enable time-out interrupt
	TIMER0->ICR |= (0x1f << 0);						//1->clear interrupt flag, 0->no effect

	//start the timer
	TIMER0->CTL |= (1<<0);							//0->disable timer, 1->enable timer
}

void pwm0b_init(uint8_t TxCCP_PS, uint16_t TxCCP_PR) {
	//T0CCP1 / PF1 used
	//configure gpio: T0CCP1 on PF1
	SYSCTL->RCGCGPIO |= (1<<5);			//0->GPIOA, 1->GPIOB, 2=GPIOC, 3=GPIOD, 4=GPIOE, 5=GPIOF, ...
	while ((SYSCTL->PRGPIO & (1<<5)) == 0) continue;	//1->ready, 0->not ready
	//configure PF1 for alternate function / T0CCP1
	GPIOF->DEN |= (1<<1);				//1=digital enabled, 0=digital disabled
	GPIOF->AFSEL |= (1<<1);				//1=alternate function enabled
	GPIOF->PCTL = (GPIOF->PCTL &~(0x0f << (1*4))) | (0x07<<(1*4));	//mux 7 to route CCP to PF1
	//now PF1 has been configured for T0CCP1

	//route the timer0
	SYSCTL->RCGCTIMER |= (1<<0);		//1->periopheral clock enabled, 0->peripheral clock disabled
	while ((SYSCTL->PRTIMER & (1<<0)) == 0) continue;	//1->ready, 0->not ready
	//configure timebase for 16-bit split timer
	//stop the timer
	TIMER0->CTL &=~(1<<8);							//0->disable timer, 1->enable timer
	//configure the timer, split, upcounter
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
	TIMER0->TBR = 0;

	//clear ISR flags, disable isr
	//disable all interrupt
	TIMER0->IMR &=~(0x1f << 8);						//0->disable time-out interrupt, 1->enable time-out interrupt
	TIMER0->ICR |= (0x1f << 8);						//1->clear interrupt flag, 0->no effect

	//start the timer
	TIMER0->CTL |= (1<<8);							//0->disable timer, 1->enable timer
}

void pwm1a_init(uint8_t TxCCP_PS, uint16_t TxCCP_PR) {
	//T1CCP0 / PF2 used
	//configure gpio: T1CCP0 on PF2
	SYSCTL->RCGCGPIO |= (1<<5);			//0->GPIOA, 1->GPIOB, 2=GPIOC, 3=GPIOD, 4=GPIOE, 5=GPIOF, ...
	while ((SYSCTL->PRGPIO & (1<<5)) == 0) continue;	//1->ready, 0->not ready
	//configure PF2 for alternate function / T1CCP0
	GPIOF->DEN |= (1<<2);				//1=digital enabled, 0=digital disabled
	GPIOF->AFSEL |= (1<<2);				//1=alternate function enabled
	GPIOF->PCTL = (GPIOF->PCTL &~(0x0f << (2*4))) | (0x07<<(2*4));	//mux 7 to route CCP to PF2
	//now PF2 has been configured for T1CCP0

	//route the timer1
	SYSCTL->RCGCTIMER |= (1<<1);		//1->periopheral clock enabled, 0->peripheral clock disabled
	while ((SYSCTL->PRTIMER & (1<<1)) == 0) continue;	//1->ready, 0->not ready
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
	TIMER1->TAR = 0;

	//clear ISR flags, disable isr
	//disable all interrupt
	TIMER1->IMR &=~(0x1f << 0);						//0->disable time-out interrupt, 1->enable time-out interrupt
	TIMER1->ICR |= (0x1f << 0);						//1->clear interrupt flag, 0->no effect

	//start the timer
	TIMER1->CTL |= (1<<0);							//0->disable timer, 1->enable timer
}

void pwm1b_init(uint8_t TxCCP_PS, uint16_t TxCCP_PR) {
	//T1CCP1 / PF3 used
	//configure gpio: T1CCP1 on PF3
	SYSCTL->RCGCGPIO |= (1<<5);			//0->GPIOA, 1->GPIOB, 2=GPIOC, 3=GPIOD, 4=GPIOE, 5=GPIOF, ...
	while ((SYSCTL->PRGPIO & (1<<5)) == 0) continue;	//1->ready, 0->not ready
	//configure PF1 for alternate function / T0CCP1
	GPIOF->DEN |= (1<<3);				//1=digital enabled, 0=digital disabled
	GPIOF->AFSEL |= (1<<3);				//1=alternate function enabled
	GPIOF->PCTL = (GPIOF->PCTL &~(0x0f << (3*4))) | (0x07<<(3*4));	//mux 7 to route CCP to PF1
	//now PF1 has been configured for T0CCP1

	//route the timer1
	SYSCTL->RCGCTIMER |= (1<<1);		//1->periopheral clock enabled, 0->peripheral clock disabled
	while ((SYSCTL->PRTIMER & (1<<1)) == 0) continue;	//1->ready, 0->not ready
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
	TIMER1->TBR = 0;

	//clear ISR flags, disable isr
	//disable all interrupt
	TIMER1->IMR &=~(0x1f << 8);						//0->disable time-out interrupt, 1->enable time-out interrupt
	TIMER1->ICR |= (0x1f << 8);						//1->clear interrupt flag, 0->no effect

	//start the timer
	TIMER1->CTL |= (1<<8);							//0->disable timer, 1->enable timer
}

void pwm2a_init(uint8_t TxCCP_PS, uint16_t TxCCP_PR) {
	//T2CCP0 / PB0 used
	//configure gpio: T2CCP0 on PB0
	SYSCTL->RCGCGPIO |= (1<<1);			//0->GPIOA, 1->GPIOB, 2=GPIOC, 3=GPIOD, 4=GPIOE, 5=GPIOF, ...
	while ((SYSCTL->PRGPIO & (1<<1)) == 0) continue;	//1->ready, 0->not ready
	//configure PB0 for alternate function / T2CCP0
	GPIOB->DEN |= (1<<0);				//1=digital enabled, 0=digital disabled
	GPIOB->AFSEL |= (1<<0);				//1=alternate function enabled
	GPIOB->PCTL = (GPIOB->PCTL &~(0x0f << (0*4))) | (0x07<<(0*4));	//mux 7 to route CCP to PF0
	//now PB0 has been configured for T2CCP0

	//route the timer2
	SYSCTL->RCGCTIMER |= (1<<2);		//1->periopheral clock enabled, 0->peripheral clock disabled
	while ((SYSCTL->PRTIMER & (1<<2)) == 0) continue;	//1->ready, 0->not ready
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
	TIMER2->TAR = 0;

	//clear ISR flags, disable isr
	//disable all interrupt
	TIMER2->IMR &=~(0x1f << 0);						//0->disable time-out interrupt, 1->enable time-out interrupt
	TIMER2->ICR |= (0x1f << 0);						//1->clear interrupt flag, 0->no effect

	//start the timer
	TIMER2->CTL |= (1<<0);							//0->disable timer, 1->enable timer

}

void pwm2b_init(uint8_t TxCCP_PS, uint16_t TxCCP_PR) {
	//T2CCP1 / PB1 used
	//configure gpio: T2CCP1 on PB1
	SYSCTL->RCGCGPIO |= (1<<1);			//0->GPIOA, 1->GPIOB, 2=GPIOC, 3=GPIOD, 4=GPIOE, 5=GPIOF, ...
	while ((SYSCTL->PRGPIO & (1<<1)) == 0) continue;	//1->ready, 0->not ready
	//configure PB1 for alternate function / T2CCP1
	GPIOB->DEN |= (1<<1);				//1=digital enabled, 0=digital disabled
	GPIOB->AFSEL |= (1<<1);				//1=alternate function enabled
	GPIOB->PCTL = (GPIOB->PCTL &~(0x0f << (1*4))) | (0x07<<(1*4));	//mux 7 to route CCP to PF1
	//now PB1 has been configured for T2CCP1

	//route the timer2
	SYSCTL->RCGCTIMER |= (1<<2);		//1->periopheral clock enabled, 0->peripheral clock disabled
	while ((SYSCTL->PRTIMER & (1<<2)) == 0) continue;	//1->ready, 0->not ready
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
	TIMER2->TBR = 0;

	//clear ISR flags, disable isr
	//disable all interrupt
	TIMER2->IMR &=~(0x1f << 8);						//0->disable time-out interrupt, 1->enable time-out interrupt
	TIMER2->ICR |= (0x1f << 8);						//1->clear interrupt flag, 0->no effect

	//start the timer
	TIMER2->CTL |= (1<<8);							//0->disable timer, 1->enable timer
}


void pwm3a_init(uint8_t TxCCP_PS, uint16_t TxCCP_PR) {
	//T3CCP0 / PB2 used
	//configure gpio: T3CCP0 on PB2
	SYSCTL->RCGCGPIO |= (1<<1);			//0->GPIOA, 1->GPIOB, 2=GPIOC, 3=GPIOD, 4=GPIOE, 5=GPIOF, ...
	while ((SYSCTL->PRGPIO & (1<<1)) == 0) continue;	//1->ready, 0->not ready
	//configure PF2 for alternate function / T1CCP0
	GPIOB->DEN |= (1<<2);				//1=digital enabled, 0=digital disabled
	GPIOB->AFSEL |= (1<<2);				//1=alternate function enabled
	GPIOB->PCTL = (GPIOB->PCTL &~(0x0f << (2*4))) | (0x07<<(2*4));	//mux 7 to route CCP to PF2
	//now PB2 has been configured for T3CCP0

	//route timer3
	SYSCTL->RCGCTIMER |= (1<<3);		//1->periopheral clock enabled, 0->peripheral clock disabled
	while ((SYSCTL->PRTIMER & (1<<3)) == 0) continue;	//1->ready, 0->not ready
	//configure timebase for 16-bit split timer
	//stop the timer
	TIMER3->CTL &=~(1<<0);							//0->disable timer, 1->enable timer
	//configure the timer, split, upcounter
	TIMER3->CFG  = 0x04;							//0x00->32/64bit, 0x01->rtc, 0x02-0x03->reserved, 0x04->16/32bit split timers
	TIMER3->TAMR = 	(0<<11) |						//0->legacy ops
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
	TIMER3->CTL |= (1<<6);							//0->output not affected, 1->output inverted
	TIMER3->CTL = (TIMER3->CTL & ~(0x03 << 2)) | (0x00 << 2);		//0->positive edge, 1->negative edge, 2->reserved, 3->both edges
	TIMER3->TAMR &=~(1<<9);							//1->enable PWM interrupt, 0->disable PWM interrupt
	TIMER3->TAMATCHR = 0;							//for 0% duty cycle
	//set the prescaler
	TIMER3->TAPMR = TIMER3->TAPR = (TxCCP_PS - 1) & 0xff;							//set the prescaler
	TIMER3->TAILR= (TxCCP_PR - 1) & 0xffff;							//set the top
	//reset counter
	TIMER3->TAR = 0;

	//clear ISR flags, disable isr
	//disable all interrupt
	TIMER3->IMR &=~(0x1f << 0);						//0->disable time-out interrupt, 1->enable time-out interrupt
	TIMER3->ICR |= (0x1f << 0);						//1->clear interrupt flag, 0->no effect

	//start the timer
	TIMER3->CTL |= (1<<0);							//0->disable timer, 1->enable timer
}

void pwm3b_init(uint8_t TxCCP_PS, uint16_t TxCCP_PR) {
	//T3CCP1 / PB3 used
	//configure gpio: T3CCP1 on PB3
	SYSCTL->RCGCGPIO |= (1<<1);			//0->GPIOA, 1->GPIOB, 2=GPIOC, 3=GPIOD, 4=GPIOE, 5=GPIOF, ...
	while ((SYSCTL->PRGPIO & (1<<1)) == 0) continue;	//1->ready, 0->not ready
	//configure PB3 for alternate function / T3CCP1
	GPIOB->DEN |= (1<<3);				//1=digital enabled, 0=digital disabled
	GPIOB->AFSEL |= (1<<3);				//1=alternate function enabled
	GPIOB->PCTL = (GPIOB->PCTL &~(0x0f << (3*4))) | (0x07<<(3*4));	//mux 7 to route CCP to PF1
	//now PB3 has been configured for T3CCP1

	//route the timer3
	SYSCTL->RCGCTIMER |= (1<<3);		//1->periopheral clock enabled, 0->peripheral clock disabled
	while ((SYSCTL->PRTIMER & (1<<3)) == 0) continue;	//1->ready, 0->not ready
	//configure timebase for 16-bit split timer
	//stop the timer
	TIMER3->CTL &=~(1<<8);							//0->disable timer, 1->enable timer
	//configure the timer, split, upcounter
	TIMER3->CFG  = 0x04;							//0x00->32/64bit, 0x01->rtc, 0x02-0x03->reserved, 0x04->16/32bit split timers
	TIMER3->TBMR = 	(0<<11) |						//0->legacy ops
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
	TIMER3->CTL |= (1<<14);							//0->output not affected, 1->output inverted
	TIMER3->CTL = (TIMER3->CTL & ~(0x03 << 10)) | (0x00 << 10);		//0->positive edge, 1->negative edge, 2->reserved, 3->both edges
	TIMER3->TBMR &=~(1<<9);							//1->enable PWM interrupt, 0->disable PWM interrupt
	TIMER3->TBMATCHR = 0;							//for 0% duty cycle
	//set the prescaler
	TIMER3->TBPMR = TIMER3->TBPR = (TxCCP_PS - 1) & 0xff;							//set the prescaler
	TIMER3->TBILR= (TxCCP_PR - 1) & 0xffff;							//set the top
	//reset counter
	TIMER3->TBR = 0;

	//clear ISR flags, disable isr
	//disable all interrupt
	TIMER3->IMR &=~(0x1f << 8);						//0->disable time-out interrupt, 1->enable time-out interrupt
	TIMER3->ICR |= (0x1f << 8);						//1->clear interrupt flag, 0->no effect

	//start the timer
	TIMER3->CTL |= (1<<8);							//0->disable timer, 1->enable timer

}

void pwm4a_init(uint8_t TxCCP_PS, uint16_t TxCCP_PR) {
	//T4CCP0 / PC0 used
	//configure gpio: T4CCP0 on PC0
	SYSCTL->RCGCGPIO |= (1<<2);			//0->GPIOA, 1->GPIOB, 2=GPIOC, 3=GPIOD, 4=GPIOE, 5=GPIOF, ...
	while ((SYSCTL->PRGPIO & (1<<2)) == 0) continue;	//1->ready, 0->not ready
	//configure PC0 for alternate function / T4CCP0
	GPIOC->DEN |= (1<<0);				//1=digital enabled, 0=digital disabled
	GPIOC->AFSEL |= (1<<0);				//1=alternate function enabled
	GPIOC->PCTL = (GPIOC->PCTL &~(0x0f << (0*4))) | (0x07<<(0*4));	//mux 7 to route CCP to PF0
	//now PC0 has been configured for T4CCP0

	//route the timer4
	SYSCTL->RCGCTIMER |= (1<<4);		//1->periopheral clock enabled, 0->peripheral clock disabled
	while ((SYSCTL->PRTIMER & (1<<4)) == 0) continue;	//1->ready, 0->not ready
	//configure timebase for 16-bit split timer
	//stop the timer
	TIMER4->CTL &=~(1<<0);							//0->disable timer, 1->enable timer
	//configure the timer, split, upcounter
	TIMER4->CFG  = 0x04;							//0x00->32/64bit, 0x01->rtc, 0x02-0x03->reserved, 0x04->16/32bit split timers
	TIMER4->TAMR = 	(0<<11) |						//0->legacy ops
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
	TIMER4->CTL |= (1<<6);							//0->output not affected, 1->output inverted
	TIMER4->CTL = (TIMER4->CTL & ~(0x03 << 2)) | (0x00 << 2);		//0->positive edge, 1->negative edge, 2->reserved, 3->both edges
	TIMER4->TAMR &=~(1<<9);							//1->enable PWM interrupt, 0->disable PWM interrupt
	TIMER4->TAMATCHR = 0;							//for 0% duty cycle
	//set the prescaler
	TIMER4->TAPMR = TIMER4->TAPR = (TxCCP_PS - 1) & 0xff;							//set the prescaler
	TIMER4->TAILR= (TxCCP_PR - 1) & 0xffff;							//set the top
	//reset counter
	TIMER4->TAR = 0;

	//clear ISR flags, disable isr
	//disable all interrupt
	TIMER4->IMR &=~(0x1f << 0);						//0->disable time-out interrupt, 1->enable time-out interrupt
	TIMER4->ICR |= (0x1f << 0);						//1->clear interrupt flag, 0->no effect

	//start the timer
	TIMER4->CTL |= (1<<0);							//0->disable timer, 1->enable timer

}

void pwm4b_init(uint8_t TxCCP_PS, uint16_t TxCCP_PR) {
	//T4CCP1 / PC1 used
	//configure gpio: T4CCP1 on PC1
	SYSCTL->RCGCGPIO |= (1<<2);			//0->GPIOA, 1->GPIOB, 2=GPIOC, 3=GPIOD, 4=GPIOE, 5=GPIOF, ...
	while ((SYSCTL->PRGPIO & (1<<2)) == 0) continue;	//1->ready, 0->not ready
	//configure PC1 for alternate function / T4CCP1
	GPIOC->DEN |= (1<<1);				//1=digital enabled, 0=digital disabled
	GPIOC->AFSEL |= (1<<1);				//1=alternate function enabled
	GPIOC->PCTL = (GPIOC->PCTL &~(0x0f << (1*4))) | (0x07<<(1*4));	//mux 7 to route CCP to PF1
	//now PC1 has been configured for T4CCP1

	//route the TIMER4
	SYSCTL->RCGCTIMER |= (1<<4);		//1->periopheral clock enabled, 0->peripheral clock disabled
	while ((SYSCTL->PRTIMER & (1<<4)) == 0) continue;	//1->ready, 0->not ready
	//configure timebase for 16-bit split timer
	//stop the timer
	TIMER4->CTL &=~(1<<8);							//0->disable timer, 1->enable timer
	//configure the timer, split, upcounter
	TIMER4->CFG  = 0x04;							//0x00->32/64bit, 0x01->rtc, 0x02-0x03->reserved, 0x04->16/32bit split timers
	TIMER4->TBMR = 	(0<<11) |						//0->legacy ops
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
	TIMER4->CTL |= (1<<14);							//0->output not affected, 1->output inverted
	TIMER4->CTL = (TIMER4->CTL & ~(0x03 << 10)) | (0x00 << 10);		//0->positive edge, 1->negative edge, 2->reserved, 3->both edges
	TIMER4->TBMR &=~(1<<9);							//1->enable PWM interrupt, 0->disable PWM interrupt
	TIMER4->TBMATCHR = 0;							//for 0% duty cycle
	//set the prescaler
	TIMER4->TBPMR = TIMER4->TBPR = (TxCCP_PS - 1) & 0xff;							//set the prescaler
	TIMER4->TBILR= (TxCCP_PR - 1) & 0xffff;							//set the top
	//reset counter
	TIMER4->TBR = 0;

	//clear ISR flags, disable isr
	//disable all interrupt
	TIMER4->IMR &=~(0x1f << 8);						//0->disable time-out interrupt, 1->enable time-out interrupt
	TIMER4->ICR |= (0x1f << 8);						//1->clear interrupt flag, 0->no effect

	//start the timer
	TIMER4->CTL |= (1<<8);							//0->disable timer, 1->enable timer

}

void pwm5a_init(uint8_t TxCCP_PS, uint16_t TxCCP_PR) {
	//T5CCP0 / PC2 used
	//configure gpio: T5CCP0 on PC2
	SYSCTL->RCGCGPIO |= (1<<2);			//0->GPIOA, 1->GPIOB, 2=GPIOC, 3=GPIOD, 4=GPIOE, 5=GPIOF, ...
	while ((SYSCTL->PRGPIO & (1<<2)) == 0) continue;	//1->ready, 0->not ready
	//configure PC2 for alternate function / T5CCP0
	GPIOC->DEN |= (1<<2);				//1=digital enabled, 0=digital disabled
	GPIOC->AFSEL |= (1<<2);				//1=alternate function enabled
	GPIOC->PCTL = (GPIOC->PCTL &~(0x0f << (2*4))) | (0x07<<(2*4));	//mux 7 to route CCP to PF2
	//now PC2 has been configured for T5CCP0

	//route timer5
	SYSCTL->RCGCTIMER |= (1<<5);		//1->periopheral clock enabled, 0->peripheral clock disabled
	while ((SYSCTL->PRTIMER & (1<<5)) == 0) continue;	//1->ready, 0->not ready
	//configure timebase for 16-bit split timer
	//stop the timer
	TIMER5->CTL &=~(1<<0);							//0->disable timer, 1->enable timer
	//configure the timer, split, upcounter
	TIMER5->CFG  = 0x04;							//0x00->32/64bit, 0x01->rtc, 0x02-0x03->reserved, 0x04->16/32bit split timers
	TIMER5->TAMR = 	(0<<11) |						//0->legacy ops
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
	TIMER5->CTL |= (1<<6);							//0->output not affected, 1->output inverted
	TIMER5->CTL = (TIMER5->CTL & ~(0x03 << 2)) | (0x00 << 2);		//0->positive edge, 1->negative edge, 2->reserved, 3->both edges
	TIMER5->TAMR &=~(1<<9);							//1->enable PWM interrupt, 0->disable PWM interrupt
	TIMER5->TAMATCHR = 0;							//for 0% duty cycle
	//set the prescaler
	TIMER5->TAPMR = TIMER5->TAPR = (TxCCP_PS - 1) & 0xff;							//set the prescaler
	TIMER5->TAILR= (TxCCP_PR - 1) & 0xffff;							//set the top
	//reset counter
	TIMER5->TAR = 0;

	//clear ISR flags, disable isr
	//disable all interrupt
	TIMER5->IMR &=~(0x1f << 0);						//0->disable time-out interrupt, 1->enable time-out interrupt
	TIMER5->ICR |= (0x1f << 0);						//1->clear interrupt flag, 0->no effect

	//start the timer
	TIMER5->CTL |= (1<<0);							//0->disable timer, 1->enable timer

}

void pwm5b_init(uint8_t TxCCP_PS, uint16_t TxCCP_PR) {
	//T5CCP1 / PC3 used
	//configure gpio: T5CCP1 on PC3
	SYSCTL->RCGCGPIO |= (1<<2);			//0->GPIOA, 1->GPIOB, 2=GPIOC, 3=GPIOD, 4=GPIOE, 5=GPIOF, ...
	while ((SYSCTL->PRGPIO & (1<<2)) == 0) continue;	//1->ready, 0->not ready
	//configure PC3 for alternate function / T5CCP1
	GPIOC->DEN |= (1<<3);				//1=digital enabled, 0=digital disabled
	GPIOC->AFSEL |= (1<<3);				//1=alternate function enabled
	GPIOC->PCTL = (GPIOC->PCTL &~(0x0f << (3*4))) | (0x07<<(3*4));	//mux 7 to route CCP to PF1
	//now PC3 has been configured for T5CCP1

	//route the TIMER5
	SYSCTL->RCGCTIMER |= (1<<5);		//1->periopheral clock enabled, 0->peripheral clock disabled
	while ((SYSCTL->PRTIMER & (1<<5)) == 0) continue;	//1->ready, 0->not ready
	//configure timebase for 16-bit split timer
	//stop the timer
	TIMER5->CTL &=~(1<<8);							//0->disable timer, 1->enable timer
	//configure the timer, split, upcounter
	TIMER5->CFG  = 0x04;							//0x00->32/64bit, 0x01->rtc, 0x02-0x03->reserved, 0x04->16/32bit split timers
	TIMER5->TBMR = 	(0<<11) |						//0->legacy ops
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
	TIMER5->CTL |= (1<<14);							//0->output not affected, 1->output inverted
	TIMER5->CTL = (TIMER5->CTL & ~(0x03 << 10)) | (0x00 << 10);		//0->positive edge, 1->negative edge, 2->reserved, 3->both edges
	TIMER5->TBMR &=~(1<<9);							//1->enable PWM interrupt, 0->disable PWM interrupt
	TIMER5->TBMATCHR = 0;							//for 0% duty cycle
	//set the prescaler
	TIMER5->TBPMR = TIMER5->TBPR = (TxCCP_PS - 1) & 0xff;							//set the prescaler
	TIMER5->TBILR= (TxCCP_PR - 1) & 0xffff;							//set the top
	//reset counter
	TIMER5->TBR = 0;

	//clear ISR flags, disable isr
	//disable all interrupt
	TIMER5->IMR &=~(0x1f << 8);						//0->disable time-out interrupt, 1->enable time-out interrupt
	TIMER5->ICR |= (0x1f << 8);						//1->clear interrupt flag, 0->no effect

	//start the timer
	TIMER5->CTL |= (1<<8);							//0->disable timer, 1->enable timer

}

//32-bit split WTIMERs, up/down counters
void pwmw0a_init(uint16_t TxCCP_PS, uint32_t WTxCCP_PR) {
	//WT0CCP0 / PC4 used
	//configure gpio: WT0CCP0 on PC4
	SYSCTL->RCGCGPIO |= (1<<2);			//0->GPIOA, 1->GPIOB, 2=GPIOC, 3=GPIOD, 4=GPIOE, 5=GPIOF, ...
	while ((SYSCTL->PRGPIO & (1<<2)) == 0) continue;	//1->ready, 0->not ready
	//configure PC4 for alternate function / WT0CCP0
	GPIOC->DEN |= (1<<4);				//1=digital enabled, 0=digital disabled
	GPIOC->AFSEL |= (1<<4);				//1=alternate function enabled
	GPIOC->PCTL = (GPIOC->PCTL &~(0x0f << (4*4))) | (0x07<<(4*4));	//mux 7 to route CCP to PC4
	//now PC4 has been configured for WT0CCP0

	//route the WTIMER0
	SYSCTL->RCGCWTIMER |= (1<<0);		//1->periopheral clock enabled, 0->peripheral clock disabled
	while ((SYSCTL->PRWTIMER & (1<<0)) == 0) continue;	//1->ready, 0->not ready
	//configure timebase for 32-bit split WTIMER
	//stop the WTIMER
	WTIMER0->CTL &=~(1<<0);							//0->disable WTIMER, 1->enable WTIMER
	//configure the WTIMER, split, upcounter
	WTIMER0->CFG  = 0x04;							//0x00->32/64bit, 0x01->rtc, 0x02-0x03->reserved, 0x04->16/32bit split WTIMERs
	WTIMER0->TAMR = 	(0<<11) |						//0->legacy ops
					(0<<10) |						//0->update match register on the next cycle, 1->update match register now
					(0<< 9) |						//0->pwm interrupt disabled, 1->pwm interrupt enabled
					(0<< 8) |						//0->update load register ont he next cycle; 1->update load register now
					(0<< 7) |						//0->disable snap shot, 1->enable snap shot
					(0<< 6) |						//0->WTIMER counts right away; 1->WTIMER waits on trigger before counting
					(0<< 5) |						//0->match interrupt disabled, 1->match interrupt enabled
					(0<< 4) |						//0->counts down, 1->counts up
					(1<< 3) |						//0->capture / compare enabled 1->pwm enabled
					(0<< 2) |						//0->edge count for capture; 1->edge time for capture
					(2<< 0) |						//0x00->reserved, 0x01->one shot, 0x02->periodic, 0x03->capture
					0x00;

	//invert the output as the WTIMER is a down counter
	WTIMER0->CTL |= (1<<6);							//0->output not affected, 1->output inverted
	WTIMER0->CTL = (WTIMER0->CTL & ~(0x03 << 2)) | (0x00 << 2);		//0->positive edge, 1->negative edge, 2->reserved, 3->both edges
	WTIMER0->TAMR &=~(1<<9);							//1->enable PWM interrupt, 0->disable PWM interrupt
	WTIMER0->TAMATCHR = 0;							//for 0% duty cycle
	//set the prescaler
	WTIMER0->TAPMR = WTIMER0->TAPR = (TxCCP_PS - 1) & 0xffff;							//set the prescaler
	WTIMER0->TAILR= (WTxCCP_PR - 1);							//set the top
	//reset counter
	WTIMER0->TAR = 0;

	//clear ISR flags, disable isr
	//disable all interrupt
	WTIMER0->IMR &=~(0x1f << 0);						//0->disable time-out interrupt, 1->enable time-out interrupt
	WTIMER0->ICR |= (0x1f << 0);						//1->clear interrupt flag, 0->no effect

	//start the WTIMER
	WTIMER0->CTL |= (1<<0);							//0->disable WTIMER, 1->enable WTIMER

}

void pwmw0b_init(uint16_t TxCCP_PS, uint32_t WTxCCP_PR) {
	//WT0CCP1 / PC5 used
	//configure gpio: WT0CCP1 on PC5
	SYSCTL->RCGCGPIO |= (1<<2);			//0->GPIOA, 1->GPIOB, 2=GPIOC, 3=GPIOD, 4=GPIOE, 5=GPIOF, ...
	while ((SYSCTL->PRGPIO & (1<<2)) == 0) continue;	//1->ready, 0->not ready
	//configure PC5 for alternate function / WT0CCP1
	GPIOC->DEN |= (1<<5);				//1=digital enabled, 0=digital disabled
	GPIOC->AFSEL |= (1<<5);				//1=alternate function enabled
	GPIOC->PCTL = (GPIOC->PCTL &~(0x0f << (5*4))) | (0x07<<(5*4));	//mux 7 to route CCP to PF1
	//now PF1 has been configured for T0CCP1

	//route the WTIMER0
	SYSCTL->RCGCWTIMER |= (1<<0);		//1->periopheral clock enabled, 0->peripheral clock disabled
	while ((SYSCTL->PRWTIMER & (1<<0)) == 0) continue;	//1->ready, 0->not ready
	//configure timebase for 32-bit split WTIMER
	//stop the WTIMER
	WTIMER0->CTL &=~(1<<8);							//0->disable WTIMER, 1->enable WTIMER
	//configure the WTIMER, split, upcounter
	WTIMER0->CFG  = 0x04;							//0x00->32/64bit, 0x01->rtc, 0x02-0x03->reserved, 0x04->16/32bit split WTIMERs
	WTIMER0->TBMR = 	(0<<11) |						//0->legacy ops
					(0<<10) |						//0->update match register on the next cycle, 1->update match register now
					(0<< 9) |						//0->pwm interrupt disabled, 1->pwm interrupt enabled
					(0<< 8) |						//0->update load register ont he next cycle; 1->update load register now
					(0<< 7) |						//0->disable snap shot, 1->enable snap shot
					(0<< 6) |						//0->WTIMER counts right away; 1->WTIMER waits on trigger before counting
					(0<< 5) |						//0->match interrupt disabled, 1->match interrupt enabled
					(0<< 4) |						//0->counts down, 1->counts up
					(1<< 3) |						//0->capture / compare enabled 1->pwm enabled
					(0<< 2) |						//0->edge count for capture; 1->edge time for capture
					(2<< 0) |						//0x00->reserved, 0x01->one shot, 0x02->periodic, 0x03->capture
					0x00;

	//invert the output as the WTIMER is a down counter
	WTIMER0->CTL |= (1<<14);							//0->output not affected, 1->output inverted
	WTIMER0->CTL = (WTIMER0->CTL & ~(0x03 << 10)) | (0x00 << 10);		//0->positive edge, 1->negative edge, 2->reserved, 3->both edges
	WTIMER0->TBMR &=~(1<<9);							//1->enable PWM interrupt, 0->disable PWM interrupt
	WTIMER0->TBMATCHR = 0;							//for 0% duty cycle
	//set the prescaler
	WTIMER0->TBPMR = WTIMER0->TBPR = (TxCCP_PS - 1) & 0xffff;							//set the prescaler
	WTIMER0->TBILR= (WTxCCP_PR - 1);							//set the top
	//reset counter
	WTIMER0->TBR = 0;

	//clear ISR flags, disable isr
	//disable all interrupt
	WTIMER0->IMR &=~(0x1f << 8);						//0->disable time-out interrupt, 1->enable time-out interrupt
	WTIMER0->ICR |= (0x1f << 8);						//1->clear interrupt flag, 0->no effect

	//start the WTIMER
	WTIMER0->CTL |= (1<<8);							//0->disable WTIMER, 1->enable WTIMER

}

void pwmw1a_init(uint16_t TxCCP_PS, uint32_t WTxCCP_PR) {
	//WT1CCP0 / PC6 used
	//configure gpio: WT1CCP0 on PC6
	SYSCTL->RCGCGPIO |= (1<<2);			//0->GPIOA, 1->GPIOB, 2=GPIOC, 3=GPIOD, 4=GPIOE, 5=GPIOF, ...
	while ((SYSCTL->PRGPIO & (1<<2)) == 0) continue;	//1->ready, 0->not ready
	//configure PC6 for alternate function / WT1CCP0
	GPIOC->DEN |= (1<<6);				//1=digital enabled, 0=digital disabled
	GPIOC->AFSEL |= (1<<6);				//1=alternate function enabled
	GPIOC->PCTL = (GPIOC->PCTL &~(0x0f << (6*4))) | (0x07<<(6*4));	//mux 7 to route CCP to PF2
	//now PC6 has been configured for WT1CCP0

	//route the WTIMER1
	SYSCTL->RCGCWTIMER |= (1<<1);		//1->periopheral clock enabled, 0->peripheral clock disabled
	while ((SYSCTL->PRWTIMER & (1<<1)) == 0) continue;	//1->ready, 0->not ready
	//configure timebase for 32-bit split WTIMER
	//stop the WTIMER
	WTIMER1->CTL &=~(1<<0);							//0->disable WTIMER, 1->enable WTIMER
	//configure the WTIMER, split, upcounter
	WTIMER1->CFG  = 0x04;							//0x00->32/64bit, 0x01->rtc, 0x02-0x03->reserved, 0x04->16/32bit split WTIMERs
	WTIMER1->TAMR = 	(0<<11) |						//0->legacy ops
					(0<<10) |						//0->update match register on the next cycle, 1->update match register now
					(0<< 9) |						//0->pwm interrupt disabled, 1->pwm interrupt enabled
					(0<< 8) |						//0->update load register ont he next cycle; 1->update load register now
					(0<< 7) |						//0->disable snap shot, 1->enable snap shot
					(0<< 6) |						//0->WTIMER counts right away; 1->WTIMER waits on trigger before counting
					(0<< 5) |						//0->match interrupt disabled, 1->match interrupt enabled
					(0<< 4) |						//0->counts down, 1->counts up
					(1<< 3) |						//0->capture / compare enabled 1->pwm enabled
					(0<< 2) |						//0->edge count for capture; 1->edge time for capture
					(2<< 0) |						//0x00->reserved, 0x01->one shot, 0x02->periodic, 0x03->capture
					0x00;

	//invert the output as the WTIMER is a down counter
	WTIMER1->CTL |= (1<<6);							//0->output not affected, 1->output inverted
	WTIMER1->CTL = (WTIMER1->CTL & ~(0x03 << 2)) | (0x00 << 2);		//0->positive edge, 1->negative edge, 2->reserved, 3->both edges
	WTIMER1->TAMR &=~(1<<9);							//1->enable PWM interrupt, 0->disable PWM interrupt
	WTIMER1->TAMATCHR = 0;							//for 0% duty cycle
	//set the prescaler
	WTIMER1->TAPMR = WTIMER1->TAPR = (TxCCP_PS - 1) & 0xffff;							//set the prescaler
	WTIMER1->TAILR= (WTxCCP_PR - 1);							//set the top
	//reset counter
	WTIMER1->TAR = 0;

	//clear ISR flags, disable isr
	//disable all interrupt
	WTIMER1->IMR &=~(0x1f << 0);						//0->disable time-out interrupt, 1->enable time-out interrupt
	WTIMER1->ICR |= (0x1f << 0);						//1->clear interrupt flag, 0->no effect

	//start the WTIMER
	WTIMER1->CTL |= (1<<0);							//0->disable WTIMER, 1->enable WTIMER

}

void pwmw1b_init(uint16_t TxCCP_PS, uint32_t WTxCCP_PR) {
	//WT1CCP1 / PC7 used
	//configure gpio: WT1CCP1 on PC7
	SYSCTL->RCGCGPIO |= (1<<2);			//0->GPIOA, 1->GPIOB, 2=GPIOC, 3=GPIOD, 4=GPIOE, 5=GPIOF, ...
	while ((SYSCTL->PRGPIO & (1<<2)) == 0) continue;	//1->ready, 0->not ready
	//configure PC7 for alternate function / WT0CCP1
	GPIOC->DEN |= (1<<7);				//1=digital enabled, 0=digital disabled
	GPIOC->AFSEL |= (1<<7);				//1=alternate function enabled
	GPIOC->PCTL = (GPIOC->PCTL &~(0x0f << (7*4))) | (0x07<<(7*4));	//mux 7 to route CCP to PF1
	//now PF1 has been configured for T0CCP1

	//route the WTIMER1
	SYSCTL->RCGCWTIMER |= (1<<1);		//1->periopheral clock enabled, 0->peripheral clock disabled
	while ((SYSCTL->PRWTIMER & (1<<1)) == 0) continue;	//1->ready, 0->not ready
	//configure timebase for 16-bit split WTIMER
	//stop the WTIMER
	WTIMER1->CTL &=~(1<<8);							//0->disable WTIMER, 1->enable WTIMER
	//configure the WTIMER, split, upcounter
	WTIMER1->CFG  = 0x04;							//0x00->32/64bit, 0x01->rtc, 0x02-0x03->reserved, 0x04->16/32bit split WTIMERs
	WTIMER1->TBMR = 	(0<<11) |						//0->legacy ops
					(0<<10) |						//0->update match register on the next cycle, 1->update match register now
					(0<< 9) |						//0->pwm interrupt disabled, 1->pwm interrupt enabled
					(0<< 8) |						//0->update load register ont he next cycle; 1->update load register now
					(0<< 7) |						//0->disable snap shot, 1->enable snap shot
					(0<< 6) |						//0->WTIMER counts right away; 1->WTIMER waits on trigger before counting
					(0<< 5) |						//0->match interrupt disabled, 1->match interrupt enabled
					(0<< 4) |						//0->counts down, 1->counts up
					(1<< 3) |						//0->capture / compare enabled 1->pwm enabled
					(0<< 2) |						//0->edge count for capture; 1->edge time for capture
					(2<< 0) |						//0x00->reserved, 0x01->one shot, 0x02->periodic, 0x03->capture
					0x00;

	//invert the output as the WTIMER is a down counter
	WTIMER1->CTL |= (1<<14);							//0->output not affected, 1->output inverted
	WTIMER1->CTL = (WTIMER1->CTL & ~(0x03 << 10)) | (0x00 << 10);		//0->positive edge, 1->negative edge, 2->reserved, 3->both edges
	WTIMER1->TBMR &=~(1<<9);							//1->enable PWM interrupt, 0->disable PWM interrupt
	WTIMER1->TBMATCHR = 0;							//for 0% duty cycle
	//set the prescaler
	WTIMER1->TBPMR = WTIMER1->TBPR = (TxCCP_PS - 1) & 0xffff;							//set the prescaler
	WTIMER1->TBILR= (WTxCCP_PR - 1);							//set the top
	//reset counter
	WTIMER1->TBR = 0;

	//clear ISR flags, disable isr
	//disable all interrupt
	WTIMER1->IMR &=~(0x1f << 8);						//0->disable time-out interrupt, 1->enable time-out interrupt
	WTIMER1->ICR |= (0x1f << 8);						//1->clear interrupt flag, 0->no effect

	//start the WTIMER
	WTIMER1->CTL |= (1<<8);							//0->disable WTIMER, 1->enable WTIMER

}

void pwmw2a_init(uint16_t TxCCP_PS, uint32_t WTxCCP_PR) {
	//WT2CCP0 / PD0 used
	//configure gpio: WT2CCP0 on PD0
	SYSCTL->RCGCGPIO |= (1<<3);			//0->GPIOA, 1->GPIOB, 2=GPIOC, 3=GPIOD, 4=GPIOE, 5=GPIOF, ...
	while ((SYSCTL->PRGPIO & (1<<3)) == 0) continue;	//1->ready, 0->not ready
	//configure PD0 for alternate function / WT2CCP0
	GPIOD->DEN |= (1<<0);				//1=digital enabled, 0=digital disabled
	GPIOD->AFSEL |= (1<<0);				//1=alternate function enabled
	GPIOD->PCTL = (GPIOD->PCTL &~(0x0f << (0*4))) | (0x07<<(0*4));	//mux 7 to route CCP to PF0
	//now PD0 has been configured for WT2CCP0

	//route the WTIMER2
	SYSCTL->RCGCWTIMER |= (1<<2);		//1->periopheral clock enabled, 0->peripheral clock disabled
	while ((SYSCTL->PRWTIMER & (1<<2)) == 0) continue;	//1->ready, 0->not ready
	//configure timebase for 16-bit split WTIMER
	//stop the WTIMER
	WTIMER2->CTL &=~(1<<0);							//0->disable WTIMER, 1->enable WTIMER
	//configure the WTIMER, split, upcounter
	WTIMER2->CFG  = 0x04;							//0x00->32/64bit, 0x01->rtc, 0x02-0x03->reserved, 0x04->16/32bit split WTIMERs
	WTIMER2->TAMR = 	(0<<11) |						//0->legacy ops
					(0<<10) |						//0->update match register on the next cycle, 1->update match register now
					(0<< 9) |						//0->pwm interrupt disabled, 1->pwm interrupt enabled
					(0<< 8) |						//0->update load register ont he next cycle; 1->update load register now
					(0<< 7) |						//0->disable snap shot, 1->enable snap shot
					(0<< 6) |						//0->WTIMER counts right away; 1->WTIMER waits on trigger before counting
					(0<< 5) |						//0->match interrupt disabled, 1->match interrupt enabled
					(0<< 4) |						//0->counts down, 1->counts up
					(1<< 3) |						//0->capture / compare enabled 1->pwm enabled
					(0<< 2) |						//0->edge count for capture; 1->edge time for capture
					(2<< 0) |						//0x00->reserved, 0x01->one shot, 0x02->periodic, 0x03->capture
					0x00;

	//invert the output as the WTIMER is a down counter
	WTIMER2->CTL |= (1<<6);							//0->output not affected, 1->output inverted
	WTIMER2->CTL = (WTIMER2->CTL & ~(0x03 << 2)) | (0x00 << 2);		//0->positive edge, 1->negative edge, 2->reserved, 3->both edges
	WTIMER2->TAMR &=~(1<<9);							//1->enable PWM interrupt, 0->disable PWM interrupt
	WTIMER2->TAMATCHR = 0;							//for 0% duty cycle
	//set the prescaler
	WTIMER2->TAPMR = WTIMER2->TAPR = (TxCCP_PS - 1) & 0xffff;							//set the prescaler
	WTIMER2->TAILR= (WTxCCP_PR - 1);							//set the top
	//reset counter
	WTIMER2->TAR = 0;

	//clear ISR flags, disable isr
	//disable all interrupt
	WTIMER2->IMR &=~(0x1f << 0);						//0->disable time-out interrupt, 1->enable time-out interrupt
	WTIMER2->ICR |= (0x1f << 0);						//1->clear interrupt flag, 0->no effect

	//start the WTIMER
	WTIMER2->CTL |= (1<<0);							//0->disable WTIMER, 1->enable WTIMER

}

void pwmw2b_init(uint16_t TxCCP_PS, uint32_t WTxCCP_PR) {
	//WT2CCP1 / PD1 used
	//configure gpio: WT2CCP1 on PD1
	SYSCTL->RCGCGPIO |= (1<<3);			//0->GPIOA, 1->GPIOB, 2=GPIOC, 3=GPIOD, 4=GPIOE, 5=GPIOF, ...
	while ((SYSCTL->PRGPIO & (1<<3)) == 0) continue;	//1->ready, 0->not ready
	//configure PD1 for alternate function / WT2CCP1
	GPIOD->DEN |= (1<<1);				//1=digital enabled, 0=digital disabled
	GPIOD->AFSEL |= (1<<1);				//1=alternate function enabled
	GPIOD->PCTL = (GPIOD->PCTL &~(0x0f << (1*4))) | (0x07<<(1*4));	//mux 7 to route CCP to PF1
	//now PD1 has been configured for WT2CCP1

	//route the WTIMER2
	SYSCTL->RCGCWTIMER |= (1<<2);		//1->periopheral clock enabled, 0->peripheral clock disabled
	while ((SYSCTL->PRWTIMER & (1<<2)) == 0) continue;	//1->ready, 0->not ready
	//configure timebase for 32-bit split WTIMER
	//stop the WTIMER
	WTIMER2->CTL &=~(1<<8);							//0->disable WTIMER, 1->enable WTIMER
	//configure the WTIMER, split, upcounter
	WTIMER2->CFG  = 0x04;							//0x00->32/64bit, 0x01->rtc, 0x02-0x03->reserved, 0x04->16/32bit split WTIMERs
	WTIMER2->TBMR = 	(0<<11) |						//0->legacy ops
					(0<<10) |						//0->update match register on the next cycle, 1->update match register now
					(0<< 9) |						//0->pwm interrupt disabled, 1->pwm interrupt enabled
					(0<< 8) |						//0->update load register ont he next cycle; 1->update load register now
					(0<< 7) |						//0->disable snap shot, 1->enable snap shot
					(0<< 6) |						//0->WTIMER counts right away; 1->WTIMER waits on trigger before counting
					(0<< 5) |						//0->match interrupt disabled, 1->match interrupt enabled
					(0<< 4) |						//0->counts down, 1->counts up
					(1<< 3) |						//0->capture / compare enabled 1->pwm enabled
					(0<< 2) |						//0->edge count for capture; 1->edge time for capture
					(2<< 0) |						//0x00->reserved, 0x01->one shot, 0x02->periodic, 0x03->capture
					0x00;

	//invert the output as the WTIMER is a down counter
	WTIMER2->CTL |= (1<<14);							//0->output not affected, 1->output inverted
	WTIMER2->CTL = (WTIMER2->CTL & ~(0x03 << 10)) | (0x00 << 10);		//0->positive edge, 1->negative edge, 2->reserved, 3->both edges
	WTIMER2->TBMR &=~(1<<9);							//1->enable PWM interrupt, 0->disable PWM interrupt
	WTIMER2->TBMATCHR = 0;							//for 0% duty cycle
	//set the prescaler
	WTIMER2->TBPMR = WTIMER2->TBPR = (TxCCP_PS - 1) & 0xffff;							//set the prescaler
	WTIMER2->TBILR= (WTxCCP_PR - 1);							//set the top
	//reset counter
	WTIMER2->TBR = 0;

	//clear ISR flags, disable isr
	//disable all interrupt
	WTIMER2->IMR &=~(0x1f << 8);						//0->disable time-out interrupt, 1->enable time-out interrupt
	WTIMER2->ICR |= (0x1f << 8);						//1->clear interrupt flag, 0->no effect

	//start the WTIMER
	WTIMER2->CTL |= (1<<8);							//0->disable WTIMER, 1->enable WTIMER

}

void pwmw3a_init(uint16_t TxCCP_PS, uint32_t WTxCCP_PR) {
	//WT3CCP0 / PD2 used
	//configure gpio: WT3CCP0 on PD2
	SYSCTL->RCGCGPIO |= (1<<3);			//0->GPIOA, 1->GPIOB, 2=GPIOC, 3=GPIOD, 4=GPIOE, 5=GPIOF, ...
	while ((SYSCTL->PRGPIO & (1<<3)) == 0) continue;	//1->ready, 0->not ready
	//configure PD2 for alternate function / WT1CCP0
	GPIOD->DEN |= (1<<2);				//1=digital enabled, 0=digital disabled
	GPIOD->AFSEL |= (1<<2);				//1=alternate function enabled
	GPIOD->PCTL = (GPIOD->PCTL &~(0x0f << (2*4))) | (0x07<<(2*4));	//mux 7 to route CCP to PF2
	//now PD2 has been configured for WT3CCP0

	//route WTIMER3
	SYSCTL->RCGCWTIMER |= (1<<3);		//1->periopheral clock enabled, 0->peripheral clock disabled
	while ((SYSCTL->PRWTIMER & (1<<3)) == 0) continue;	//1->ready, 0->not ready
	//configure timebase for 32-bit split WTIMER
	//stop the WTIMER
	WTIMER3->CTL &=~(1<<0);							//0->disable WTIMER, 1->enable WTIMER
	//configure the WTIMER, split, upcounter
	WTIMER3->CFG  = 0x04;							//0x00->32/64bit, 0x01->rtc, 0x02-0x03->reserved, 0x04->16/32bit split WTIMERs
	WTIMER3->TAMR = 	(0<<11) |						//0->legacy ops
					(0<<10) |						//0->update match register on the next cycle, 1->update match register now
					(0<< 9) |						//0->pwm interrupt disabled, 1->pwm interrupt enabled
					(0<< 8) |						//0->update load register ont he next cycle; 1->update load register now
					(0<< 7) |						//0->disable snap shot, 1->enable snap shot
					(0<< 6) |						//0->WTIMER counts right away; 1->WTIMER waits on trigger before counting
					(0<< 5) |						//0->match interrupt disabled, 1->match interrupt enabled
					(0<< 4) |						//0->counts down, 1->counts up
					(1<< 3) |						//0->capture / compare enabled 1->pwm enabled
					(0<< 2) |						//0->edge count for capture; 1->edge time for capture
					(2<< 0) |						//0x00->reserved, 0x01->one shot, 0x02->periodic, 0x03->capture
					0x00;

	//invert the output as the WTIMER is a down counter
	WTIMER3->CTL |= (1<<6);							//0->output not affected, 1->output inverted
	WTIMER3->CTL = (WTIMER3->CTL & ~(0x03 << 2)) | (0x00 << 2);		//0->positive edge, 1->negative edge, 2->reserved, 3->both edges
	WTIMER3->TAMR &=~(1<<9);							//1->enable PWM interrupt, 0->disable PWM interrupt
	WTIMER3->TAMATCHR = 0;							//for 0% duty cycle
	//set the prescaler
	WTIMER3->TAPMR = WTIMER3->TAPR = (TxCCP_PS - 1) & 0xffff;							//set the prescaler
	WTIMER3->TAILR= (WTxCCP_PR - 1);							//set the top
	//reset counter
	WTIMER3->TAR = 0;

	//clear ISR flags, disable isr
	//disable all interrupt
	WTIMER3->IMR &=~(0x1f << 0);						//0->disable time-out interrupt, 1->enable time-out interrupt
	WTIMER3->ICR |= (0x1f << 0);						//1->clear interrupt flag, 0->no effect

	//start the WTIMER
	WTIMER3->CTL |= (1<<0);							//0->disable WTIMER, 1->enable WTIMER

}

void pwmw3b_init(uint16_t TxCCP_PS, uint32_t WTxCCP_PR) {
	//WT3CCP1 / PD3 used
	//configure gpio: WT3CCP1 on PD3
	SYSCTL->RCGCGPIO |= (1<<3);			//0->GPIOA, 1->GPIOB, 2=GPIOC, 3=GPIOD, 4=GPIOE, 5=GPIOF, ...
	while ((SYSCTL->PRGPIO & (1<<3)) == 0) continue;	//1->ready, 0->not ready
	//configure PD3 for alternate function / WT3CCP1
	GPIOD->DEN |= (1<<3);				//1=digital enabled, 0=digital disabled
	GPIOD->AFSEL |= (1<<3);				//1=alternate function enabled
	GPIOD->PCTL = (GPIOD->PCTL &~(0x0f << (3*4))) | (0x07<<(3*4));	//mux 7 to route CCP to PF1
	//now PD3 has been configured for WT3CCP1

	//route the WTIMER3
	SYSCTL->RCGCWTIMER |= (1<<3);		//1->periopheral clock enabled, 0->peripheral clock disabled
	while ((SYSCTL->PRWTIMER & (1<<3)) == 0) continue;	//1->ready, 0->not ready
	//configure timebase for 32-bit split WTIMER
	//stop the WTIMER
	WTIMER3->CTL &=~(1<<8);							//0->disable WTIMER, 1->enable WTIMER
	//configure the WTIMER, split, upcounter
	WTIMER3->CFG  = 0x04;							//0x00->32/64bit, 0x01->rtc, 0x02-0x03->reserved, 0x04->16/32bit split WTIMERs
	WTIMER3->TBMR = 	(0<<11) |						//0->legacy ops
					(0<<10) |						//0->update match register on the next cycle, 1->update match register now
					(0<< 9) |						//0->pwm interrupt disabled, 1->pwm interrupt enabled
					(0<< 8) |						//0->update load register ont he next cycle; 1->update load register now
					(0<< 7) |						//0->disable snap shot, 1->enable snap shot
					(0<< 6) |						//0->WTIMER counts right away; 1->WTIMER waits on trigger before counting
					(0<< 5) |						//0->match interrupt disabled, 1->match interrupt enabled
					(0<< 4) |						//0->counts down, 1->counts up
					(1<< 3) |						//0->capture / compare enabled 1->pwm enabled
					(0<< 2) |						//0->edge count for capture; 1->edge time for capture
					(2<< 0) |						//0x00->reserved, 0x01->one shot, 0x02->periodic, 0x03->capture
					0x00;

	//invert the output as the WTIMER is a down counter
	WTIMER3->CTL |= (1<<14);							//0->output not affected, 1->output inverted
	WTIMER3->CTL = (WTIMER3->CTL & ~(0x03 << 10)) | (0x00 << 10);		//0->positive edge, 1->negative edge, 2->reserved, 3->both edges
	WTIMER3->TBMR &=~(1<<9);							//1->enable PWM interrupt, 0->disable PWM interrupt
	WTIMER3->TBMATCHR = 0;							//for 0% duty cycle
	//set the prescaler
	WTIMER3->TBPMR = WTIMER3->TBPR = (TxCCP_PS - 1) & 0xffff;							//set the prescaler
	WTIMER3->TBILR= (WTxCCP_PR - 1);							//set the top
	//reset counter
	WTIMER3->TBR = 0;

	//clear ISR flags, disable isr
	//disable all interrupt
	WTIMER3->IMR &=~(0x1f << 8);						//0->disable time-out interrupt, 1->enable time-out interrupt
	WTIMER3->ICR |= (0x1f << 8);						//1->clear interrupt flag, 0->no effect

	//start the WTIMER
	WTIMER3->CTL |= (1<<8);							//0->disable WTIMER, 1->enable WTIMER

}

void pwmw4a_init(uint16_t TxCCP_PS, uint32_t WTxCCP_PR) {
	//WT4CCP0 / PD4 used
	//configure gpio: WT4CCP0 on PD4
	SYSCTL->RCGCGPIO |= (1<<3);			//0->GPIOA, 1->GPIOB, 2=GPIOC, 3=GPIOD, 4=GPIOE, 5=GPIOF, ...
	while ((SYSCTL->PRGPIO & (1<<3)) == 0) continue;	//1->ready, 0->not ready
	//configure PD4 for alternate function / WT4CCP0
	GPIOD->DEN |= (1<<4);				//1=digital enabled, 0=digital disabled
	GPIOD->AFSEL |= (1<<4);				//1=alternate function enabled
	GPIOD->PCTL = (GPIOD->PCTL &~(0x0f << (4*4))) | (0x07<<(4*4));	//mux 7 to route CCP to PF0
	//now PD0 has been configured for WT4CCP0

	//route the WTIMER4
	SYSCTL->RCGCWTIMER |= (1<<4);		//1->periopheral clock enabled, 0->peripheral clock disabled
	while ((SYSCTL->PRWTIMER & (1<<4)) == 0) continue;	//1->ready, 0->not ready
	//configure timebase for 32-bit split WTIMER
	//stop the WTIMER
	WTIMER4->CTL &=~(1<<0);							//0->disable WTIMER, 1->enable WTIMER
	//configure the WTIMER, split, upcounter
	WTIMER4->CFG  = 0x04;							//0x00->32/64bit, 0x01->rtc, 0x02-0x03->reserved, 0x04->16/32bit split WTIMERs
	WTIMER4->TAMR = 	(0<<11) |						//0->legacy ops
					(0<<10) |						//0->update match register on the next cycle, 1->update match register now
					(0<< 9) |						//0->pwm interrupt disabled, 1->pwm interrupt enabled
					(0<< 8) |						//0->update load register ont he next cycle; 1->update load register now
					(0<< 7) |						//0->disable snap shot, 1->enable snap shot
					(0<< 6) |						//0->WTIMER counts right away; 1->WTIMER waits on trigger before counting
					(0<< 5) |						//0->match interrupt disabled, 1->match interrupt enabled
					(0<< 4) |						//0->counts down, 1->counts up
					(1<< 3) |						//0->capture / compare enabled 1->pwm enabled
					(0<< 2) |						//0->edge count for capture; 1->edge time for capture
					(2<< 0) |						//0x00->reserved, 0x01->one shot, 0x02->periodic, 0x03->capture
					0x00;

	//invert the output as the WTIMER is a down counter
	WTIMER4->CTL |= (1<<6);							//0->output not affected, 1->output inverted
	WTIMER4->CTL = (WTIMER4->CTL & ~(0x03 << 2)) | (0x00 << 2);		//0->positive edge, 1->negative edge, 2->reserved, 3->both edges
	WTIMER4->TAMR &=~(1<<9);							//1->enable PWM interrupt, 0->disable PWM interrupt
	WTIMER4->TAMATCHR = 0;							//for 0% duty cycle
	//set the prescaler
	WTIMER4->TAPMR = WTIMER4->TAPR = (TxCCP_PS - 1) & 0xffff;							//set the prescaler
	WTIMER4->TAILR= (WTxCCP_PR - 1);							//set the top
	//reset counter
	WTIMER4->TAR = 0;

	//clear ISR flags, disable isr
	//disable all interrupt
	WTIMER4->IMR &=~(0x1f << 0);						//0->disable time-out interrupt, 1->enable time-out interrupt
	WTIMER4->ICR |= (0x1f << 0);						//1->clear interrupt flag, 0->no effect

	//start the WTIMER
	WTIMER4->CTL |= (1<<0);							//0->disable WTIMER, 1->enable WTIMER

}

void pwmw4b_init(uint16_t TxCCP_PS, uint32_t WTxCCP_PR) {
	//WT4CCP1 / PD5 used
	//configure gpio: WT4CCP1 on PD5
	SYSCTL->RCGCGPIO |= (1<<3);			//0->GPIOA, 1->GPIOB, 2=GPIOC, 3=GPIOD, 4=GPIOE, 5=GPIOF, ...
	while ((SYSCTL->PRGPIO & (1<<3)) == 0) continue;	//1->ready, 0->not ready
	//configure PD5 for alternate function / WT4CCP1
	GPIOD->DEN |= (1<<5);				//1=digital enabled, 0=digital disabled
	GPIOD->AFSEL |= (1<<5);				//1=alternate function enabled
	GPIOD->PCTL = (GPIOD->PCTL &~(0x0f << (5*4))) | (0x07<<(5*4));	//mux 7 to route CCP to PF1
	//now PD5 has been configured for WT4CCP1

	//route the WTIMER4
	SYSCTL->RCGCWTIMER |= (1<<4);		//1->periopheral clock enabled, 0->peripheral clock disabled
	while ((SYSCTL->PRWTIMER & (1<<4)) == 0) continue;	//1->ready, 0->not ready
	//configure timebase for 32-bit split WTIMER
	//stop the WTIMER
	WTIMER4->CTL &=~(1<<8);							//0->disable WTIMER, 1->enable WTIMER
	//configure the WTIMER, split, upcounter
	WTIMER4->CFG  = 0x04;							//0x00->32/64bit, 0x01->rtc, 0x02-0x03->reserved, 0x04->16/32bit split WTIMERs
	WTIMER4->TBMR = 	(0<<11) |						//0->legacy ops
					(0<<10) |						//0->update match register on the next cycle, 1->update match register now
					(0<< 9) |						//0->pwm interrupt disabled, 1->pwm interrupt enabled
					(0<< 8) |						//0->update load register ont he next cycle; 1->update load register now
					(0<< 7) |						//0->disable snap shot, 1->enable snap shot
					(0<< 6) |						//0->WTIMER counts right away; 1->WTIMER waits on trigger before counting
					(0<< 5) |						//0->match interrupt disabled, 1->match interrupt enabled
					(0<< 4) |						//0->counts down, 1->counts up
					(1<< 3) |						//0->capture / compare enabled 1->pwm enabled
					(0<< 2) |						//0->edge count for capture; 1->edge time for capture
					(2<< 0) |						//0x00->reserved, 0x01->one shot, 0x02->periodic, 0x03->capture
					0x00;

	//invert the output as the WTIMER is a down counter
	WTIMER4->CTL |= (1<<14);							//0->output not affected, 1->output inverted
	WTIMER4->CTL = (WTIMER4->CTL & ~(0x03 << 10)) | (0x00 << 10);		//0->positive edge, 1->negative edge, 2->reserved, 3->both edges
	WTIMER4->TBMR &=~(1<<9);							//1->enable PWM interrupt, 0->disable PWM interrupt
	WTIMER4->TBMATCHR = 0;							//for 0% duty cycle
	//set the prescaler
	WTIMER4->TBPMR = WTIMER4->TBPR = (TxCCP_PS - 1) & 0xffff;							//set the prescaler
	WTIMER4->TBILR= (WTxCCP_PR - 1);							//set the top
	//reset counter
	WTIMER4->TBR = 0;

	//clear ISR flags, disable isr
	//disable all interrupt
	WTIMER4->IMR &=~(0x1f << 8);						//0->disable time-out interrupt, 1->enable time-out interrupt
	WTIMER4->ICR |= (0x1f << 8);						//1->clear interrupt flag, 0->no effect

	//start the WTIMER
	WTIMER4->CTL |= (1<<8);							//0->disable WTIMER, 1->enable WTIMER

}

void pwmw5a_init(uint16_t TxCCP_PS, uint32_t WTxCCP_PR) {
	//WT5CCP0 / PD6 used
	//configure gpio: WT5CCP0 on PD6
	SYSCTL->RCGCGPIO |= (1<<3);			//0->GPIOA, 1->GPIOB, 2=GPIOC, 3=GPIOD, 4=GPIOE, 5=GPIOF, ...
	while ((SYSCTL->PRGPIO & (1<<3)) == 0) continue;	//1->ready, 0->not ready
	//configure PD6 for alternate function / WT5CCP0
	GPIOD->DEN |= (1<<6);				//1=digital enabled, 0=digital disabled
	GPIOD->AFSEL |= (1<<6);				//1=alternate function enabled
	GPIOD->PCTL = (GPIOD->PCTL &~(0x0f << (6*4))) | (0x07<<(6*4));	//mux 7 to route CCP to PF2
	//now PD6 has been configured for WT5CCP0

	//route WTIMER5
	SYSCTL->RCGCWTIMER |= (1<<5);		//1->periopheral clock enabled, 0->peripheral clock disabled
	while ((SYSCTL->PRWTIMER & (1<<5)) == 0) continue;	//1->ready, 0->not ready
	//configure timebase for 32-bit split WTIMER
	//stop the WTIMER
	WTIMER5->CTL &=~(1<<0);							//0->disable WTIMER, 1->enable WTIMER
	//configure the WTIMER, split, upcounter
	WTIMER5->CFG  = 0x04;							//0x00->32/64bit, 0x01->rtc, 0x02-0x03->reserved, 0x04->16/32bit split WTIMERs
	WTIMER5->TAMR = 	(0<<11) |						//0->legacy ops
					(0<<10) |						//0->update match register on the next cycle, 1->update match register now
					(0<< 9) |						//0->pwm interrupt disabled, 1->pwm interrupt enabled
					(0<< 8) |						//0->update load register ont he next cycle; 1->update load register now
					(0<< 7) |						//0->disable snap shot, 1->enable snap shot
					(0<< 6) |						//0->WTIMER counts right away; 1->WTIMER waits on trigger before counting
					(0<< 5) |						//0->match interrupt disabled, 1->match interrupt enabled
					(0<< 4) |						//0->counts down, 1->counts up
					(1<< 3) |						//0->capture / compare enabled 1->pwm enabled
					(0<< 2) |						//0->edge count for capture; 1->edge time for capture
					(2<< 0) |						//0x00->reserved, 0x01->one shot, 0x02->periodic, 0x03->capture
					0x00;

	//invert the output as the WTIMER is a down counter
	WTIMER5->CTL |= (1<<6);							//0->output not affected, 1->output inverted
	WTIMER5->CTL = (WTIMER5->CTL & ~(0x03 << 2)) | (0x00 << 2);		//0->positive edge, 1->negative edge, 2->reserved, 3->both edges
	WTIMER5->TAMR &=~(1<<9);							//1->enable PWM interrupt, 0->disable PWM interrupt
	WTIMER5->TAMATCHR = 0;							//for 0% duty cycle
	//set the prescaler
	WTIMER5->TAPMR = WTIMER5->TAPR = (TxCCP_PS - 1) & 0xffff;							//set the prescaler
	WTIMER5->TAILR= (WTxCCP_PR - 1);							//set the top
	//reset counter
	WTIMER5->TAR = 0;

	//clear ISR flags, disable isr
	//disable all interrupt
	WTIMER5->IMR &=~(0x1f << 0);						//0->disable time-out interrupt, 1->enable time-out interrupt
	WTIMER5->ICR |= (0x1f << 0);						//1->clear interrupt flag, 0->no effect

	//start the WTIMER
	WTIMER5->CTL |= (1<<0);							//0->disable WTIMER, 1->enable WTIMER

}

void pwmw5b_init(uint16_t TxCCP_PS, uint32_t WTxCCP_PR) {
	//WT5CCP1 / PD7 used
	//configure gpio: WT5CCP1 on PD7
	SYSCTL->RCGCGPIO |= (1<<3);			//0->GPIOA, 1->GPIOB, 2=GPIOC, 3=GPIOD, 4=GPIOE, 5=GPIOF, ...
	while ((SYSCTL->PRGPIO & (1<<3)) == 0) continue;	//1->ready, 0->not ready
	//configure PD7 for alternate function / WT5CCP1
	GPIOD->DEN |= (1<<7);				//1=digital enabled, 0=digital disabled
	GPIOD->AFSEL |= (1<<7);				//1=alternate function enabled
	GPIOD->PCTL = (GPIOD->PCTL &~(0x0f << (7*4))) | (0x07<<(7*4));	//mux 7 to route CCP to PF1
	//now PD7 has been configured for WT5CCP1

	//route the WTIMER5
	SYSCTL->RCGCWTIMER |= (1<<5);		//1->periopheral clock enabled, 0->peripheral clock disabled
	while ((SYSCTL->PRWTIMER & (1<<5)) == 0) continue;	//1->ready, 0->not ready
	//configure timebase for 32-bit split WTIMER
	//stop the WTIMER
	WTIMER5->CTL &=~(1<<8);							//0->disable WTIMER, 1->enable WTIMER
	//configure the WTIMER, split, upcounter
	WTIMER5->CFG  = 0x04;							//0x00->32/64bit, 0x01->rtc, 0x02-0x03->reserved, 0x04->16/32bit split WTIMERs
	WTIMER5->TBMR = 	(0<<11) |						//0->legacy ops
					(0<<10) |						//0->update match register on the next cycle, 1->update match register now
					(0<< 9) |						//0->pwm interrupt disabled, 1->pwm interrupt enabled
					(0<< 8) |						//0->update load register ont he next cycle; 1->update load register now
					(0<< 7) |						//0->disable snap shot, 1->enable snap shot
					(0<< 6) |						//0->WTIMER counts right away; 1->WTIMER waits on trigger before counting
					(0<< 5) |						//0->match interrupt disabled, 1->match interrupt enabled
					(0<< 4) |						//0->counts down, 1->counts up
					(1<< 3) |						//0->capture / compare enabled 1->pwm enabled
					(0<< 2) |						//0->edge count for capture; 1->edge time for capture
					(2<< 0) |						//0x00->reserved, 0x01->one shot, 0x02->periodic, 0x03->capture
					0x00;

	//invert the output as the WTIMER is a down counter
	WTIMER5->CTL |= (1<<14);							//0->output not affected, 1->output inverted
	WTIMER5->CTL = (WTIMER5->CTL & ~(0x03 << 10)) | (0x00 << 10);		//0->positive edge, 1->negative edge, 2->reserved, 3->both edges
	WTIMER5->TBMR &=~(1<<9);							//1->enable PWM interrupt, 0->disable PWM interrupt
	WTIMER5->TBMATCHR = 0;							//for 0% duty cycle
	//set the prescaler
	WTIMER5->TBPMR = WTIMER5->TBPR = (TxCCP_PS - 1) & 0xffff;							//set the prescaler
	WTIMER5->TBILR= (WTxCCP_PR - 1);							//set the top
	//reset counter
	WTIMER5->TBR = 0;

	//clear ISR flags, disable isr
	//disable all interrupt
	WTIMER5->IMR &=~(0x1f << 8);						//0->disable time-out interrupt, 1->enable time-out interrupt
	WTIMER5->ICR |= (0x1f << 8);						//1->clear interrupt flag, 0->no effect

	//start the WTIMER
	WTIMER5->CTL |= (1<<8);							//0->disable WTIMER, 1->enable WTIMER

}

//16/32-bit PWM output
//PS defined by TxCCP_PS
//PR defined by TxCCP_PR
//valid pin assignment:
//PF0/T0CCP0
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
//PC0/T4CCP0
//PC1/T4CCP1
//PC2/T5CCP0
//PC3/T5CCP1
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
