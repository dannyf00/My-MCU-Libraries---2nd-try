#include "exti.h"					//we use exti

//hardware configuration
//end hardware configuration

//empty handler
static void empty_handler(void) {
	//do nothing here
}

//global variables
static void (* _exti0_isrptr)(void)=empty_handler;				//exti0 isrpointer pointing to empty_handler by default
static void (* _exti1_isrptr)(void)=empty_handler;				//exti0 isrpointer pointing to empty_handler by default
static void (* _exti2_isrptr)(void)=empty_handler;				//exti0 isrpointer pointing to empty_handler by default
static void (* _exti3_isrptr)(void)=empty_handler;				//exti0 isrpointer pointing to empty_handler by default
static void (* _exti4_isrptr)(void)=empty_handler;				//exti0 isrpointer pointing to empty_handler by default
static void (* _exti5_isrptr)(void)=empty_handler;				//exti0 isrpointer pointing to empty_handler by default
static void (* _exti6_isrptr)(void)=empty_handler;				//exti0 isrpointer pointing to empty_handler by default
static void (* _exti7_isrptr)(void)=empty_handler;				//exti0 isrpointer pointing to empty_handler by default
static void (* _exti8_isrptr)(void)=empty_handler;				//exti0 isrpointer pointing to empty_handler by default
static void (* _exti9_isrptr)(void)=empty_handler;				//exti0 isrpointer pointing to empty_handler by default
static void (* _exti10_isrptr)(void)=empty_handler;				//exti0 isrpointer pointing to empty_handler by default
static void (* _exti11_isrptr)(void)=empty_handler;				//exti0 isrpointer pointing to empty_handler by default
static void (* _exti12_isrptr)(void)=empty_handler;				//exti0 isrpointer pointing to empty_handler by default
static void (* _exti13_isrptr)(void)=empty_handler;				//exti0 isrpointer pointing to empty_handler by default
static void (* _exti14_isrptr)(void)=empty_handler;				//exti0 isrpointer pointing to empty_handler by default
static void (* _exti15_isrptr)(void)=empty_handler;				//exti0 isrpointer pointing to empty_handler by default

//EXTI0 ISR
void EXTI0_IRQHandler(void) {
	//clear the flag
	EXTI->PR |= (1<<0);						//1->clear the flag
	//execute user isr
	_exti0_isrptr();
}

//EXTI1 ISR
void EXTI1_IRQHandler(void) {
	//clear the flag
	EXTI->PR |= (1<<1);						//1->clear the flag
	//execute user isr
	_exti1_isrptr();
}

//EXTI2 ISR
void EXTI2_IRQHandler(void) {
	//clear the flag
	EXTI->PR |= (1<<2);						//1->clear the flag
	//execute user isr
	_exti2_isrptr();
}

//EXTI3 ISR
void EXTI3_IRQHandler(void) {
	//clear the flag
	EXTI->PR |= (1<<3);						//1->clear the flag
	//execute user isr
	_exti3_isrptr();
}

//EXTI4 ISR
void EXTI4_IRQHandler(void) {
	//clear the flag
	EXTI->PR |= (1<<4);						//1->clear the flag
	//execute user isr
	_exti4_isrptr();
}

//EXTI9-5 ISR
void EXTI9_5_IRQHandler(void) {
	//clear the flag and execute user isr
	switch (EXTI->PR) {
	case (1<<5): EXTI->PR |= (1<<5); _exti5_isrptr(); break;
	case (1<<6): EXTI->PR |= (1<<6); _exti6_isrptr(); break;
	case (1<<7): EXTI->PR |= (1<<7); _exti7_isrptr(); break;
	case (1<<8): EXTI->PR |= (1<<8); _exti8_isrptr(); break;
	case (1<<9): EXTI->PR |= (1<<9); _exti9_isrptr(); break;
	}
}

//EXTI15-10 ISR
void EXTI15_10_IRQHandler(void) {
	//clear the flag and execute user isr
	switch (EXTI->PR) {
	case (1<<10): EXTI->PR |= (1<<10); _exti10_isrptr(); break;
	case (1<<11): EXTI->PR |= (1<<11); _exti11_isrptr(); break;
	case (1<<12): EXTI->PR |= (1<<12); _exti12_isrptr(); break;
	case (1<<13): EXTI->PR |= (1<<13); _exti13_isrptr(); break;
	case (1<<14): EXTI->PR |= (1<<14); _exti14_isrptr(); break;
	case (1<<15): EXTI->PR |= (1<<15); _exti15_isrptr(); break;
	}
}

//global defines
#define EXTI_FALLING	0				//trigger on falling edge
#define EXTI_RISING		1				//trigger on rising edge
#define EXTI_BOTH		2				//trigger on falling and rising edges

//global variables
//initialize the exti
//pin: one pin only
//gpio: GPIOA..GPIOG
void exti_init(GPIO_TypeDef * gpio, uint16_t pin, uint8_t edge) {
	//enable afio
	RCC->APB2ENR |= RCC_APB2ENR_AFIOEN;
	//enable the clock
	switch ((uint32_t) gpio) {
#if defined(RCC_APB2ENR_IOPAEN)
	case (uint32_t) GPIOA: RCC->APB2ENR |= RCC_APB2ENR_IOPAEN; break;
#endif
#if defined(RCC_APB2ENR_IOPBEN)
	case (uint32_t) GPIOB: RCC->APB2ENR |= RCC_APB2ENR_IOPBEN; break;
#endif
#if defined(RCC_APB2ENR_IOPCEN)
	case (uint32_t) GPIOC: RCC->APB2ENR |= RCC_APB2ENR_IOPCEN; break;
#endif
#if defined(RCC_APB2ENR_IOPDEN)
	case (uint32_t) GPIOD: RCC->APB2ENR |= RCC_APB2ENR_IOPDEN; break;
#endif
#if defined(RCC_APB2ENR_IOPEEN)
	case (uint32_t) GPIOE: RCC->APB2ENR |= RCC_APB2ENR_IOPEEN; break;
#endif
#if defined(RCC_APB2ENR_IOPFEN)
	case (uint32_t) GPIOF: RCC->APB2ENR |= RCC_APB2ENR_IOPFEN; break;
#endif
#if defined(RCC_APB2ENR_IOPGEN)
	case (uint32_t) GPIOG: RCC->APB2ENR |= RCC_APB2ENR_IOPGEN; break;
#endif
	}
	//configure exti edges
	//1->falling/rising edge enabled, 0->falling/rising edge disabled
	switch (edge) {
	case EXTI_FALLING: 	EXTI->FTSR |= pin; EXTI->RTSR &=~pin; break;
	case EXTI_RISING: 	EXTI->FTSR &=~pin; EXTI->RTSR |= pin; break;
	case EXTI_BOTH: 	EXTI->FTSR |= pin; EXTI->RTSR |= pin; break;
	}
	//configure the port
	switch (pin) {
	case (1<< 0): AFIO->EXTICR[0] = (AFIO->EXTICR[0] &~0x000f) | (gpio - GPIOA); break;
	case (1<< 1): AFIO->EXTICR[0] = (AFIO->EXTICR[0] &~0x00f0) | (gpio - GPIOA); break;
	case (1<< 2): AFIO->EXTICR[0] = (AFIO->EXTICR[0] &~0x0f00) | (gpio - GPIOA); break;
	case (1<< 3): AFIO->EXTICR[0] = (AFIO->EXTICR[0] &~0xf000) | (gpio - GPIOA); break;
	case (1<< 4): AFIO->EXTICR[1] = (AFIO->EXTICR[1] &~0x000f) | (gpio - GPIOA); break;
	case (1<< 5): AFIO->EXTICR[1] = (AFIO->EXTICR[1] &~0x00f0) | (gpio - GPIOA); break;
	case (1<< 6): AFIO->EXTICR[1] = (AFIO->EXTICR[1] &~0x0f00) | (gpio - GPIOA); break;
	case (1<< 7): AFIO->EXTICR[1] = (AFIO->EXTICR[1] &~0xf000) | (gpio - GPIOA); break;
	case (1<< 8): AFIO->EXTICR[2] = (AFIO->EXTICR[2] &~0x000f) | (gpio - GPIOA); break;
	case (1<< 9): AFIO->EXTICR[2] = (AFIO->EXTICR[2] &~0x00f0) | (gpio - GPIOA); break;
	case (1<<10): AFIO->EXTICR[2] = (AFIO->EXTICR[2] &~0x0f00) | (gpio - GPIOA); break;
	case (1<<11): AFIO->EXTICR[2] = (AFIO->EXTICR[2] &~0xf000) | (gpio - GPIOA); break;
	case (1<<12): AFIO->EXTICR[3] = (AFIO->EXTICR[3] &~0x000f) | (gpio - GPIOA); break;
	case (1<<13): AFIO->EXTICR[3] = (AFIO->EXTICR[3] &~0x00f0) | (gpio - GPIOA); break;
	case (1<<14): AFIO->EXTICR[3] = (AFIO->EXTICR[3] &~0x0f00) | (gpio - GPIOA); break;
	case (1<<15): AFIO->EXTICR[3] = (AFIO->EXTICR[3] &~0xf000) | (gpio - GPIOA); break;
	};
}

//install user handler
void exti_act(uint16_t pin, void (*isr_ptr)(void)) {
	//clear the flag
	EXTI->PR |= pin;						//1->clear the flag
	//enable the interrupt
	EXTI->IMR |= pin;							//1->enable the interrupt, 0->disable the interrupt
	EXTI->EMR |= pin;							//1->enable the event trigger, 0->disable the event trigger

	//enable nvic
	switch (pin) {
	case (1<<0): NVIC_EnableIRQ(EXTI0_IRQn); _exti0_isrptr = isr_ptr; break;
	case (1<<1): NVIC_EnableIRQ(EXTI1_IRQn); _exti1_isrptr = isr_ptr; break;
	case (1<<2): NVIC_EnableIRQ(EXTI2_IRQn); _exti2_isrptr = isr_ptr; break;
	case (1<<3): NVIC_EnableIRQ(EXTI3_IRQn); _exti3_isrptr = isr_ptr; break;
	case (1<<4): NVIC_EnableIRQ(EXTI4_IRQn); _exti4_isrptr = isr_ptr; break;
	case (1<<5): NVIC_EnableIRQ(EXTI9_5_IRQn); _exti5_isrptr = isr_ptr; break;
	case (1<<6): NVIC_EnableIRQ(EXTI9_5_IRQn); _exti6_isrptr = isr_ptr; break;
	case (1<<7): NVIC_EnableIRQ(EXTI9_5_IRQn); _exti7_isrptr = isr_ptr; break;
	case (1<<8): NVIC_EnableIRQ(EXTI9_5_IRQn); _exti8_isrptr = isr_ptr; break;
	case (1<<9): NVIC_EnableIRQ(EXTI9_5_IRQn); _exti9_isrptr = isr_ptr; break;
	case (1<<10): NVIC_EnableIRQ(EXTI15_10_IRQn); _exti10_isrptr = isr_ptr; break;
	case (1<<11): NVIC_EnableIRQ(EXTI15_10_IRQn); _exti11_isrptr = isr_ptr; break;
	case (1<<12): NVIC_EnableIRQ(EXTI15_10_IRQn); _exti12_isrptr = isr_ptr; break;
	case (1<<13): NVIC_EnableIRQ(EXTI15_10_IRQn); _exti13_isrptr = isr_ptr; break;
	case (1<<14): NVIC_EnableIRQ(EXTI15_10_IRQn); _exti14_isrptr = isr_ptr; break;
	case (1<<15): NVIC_EnableIRQ(EXTI15_10_IRQn); _exti15_isrptr = isr_ptr; break;
	}
}
