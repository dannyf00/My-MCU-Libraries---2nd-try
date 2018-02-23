#include "rtc.h"

//hardware configuration
//end hardware configuration

//global defines

//empty handler
static void empty_handler(void) {
	//do nothing here
}
//global variables
static void (* _isrptr_alr)(void)=empty_handler;			//rtc alarm flag
static void (* _isrptr_ovf)(void)=empty_handler;			//rtc overflow flag

//rtc alarm isr
void RTC_IRQHandler(void) {
	//overflow isr
	if (RTC->CRL & RTC_CRL_OWF) {							//overflow flag is set
		RTC->CRL &=~RTC_CRL_OWF;							//clear the overflow flag
		_isrptr_ovf();										//execute user handler
	}
}

//reset the rtc
//ps = prescaler
//pr = period for alarm
//alarm isr is enabled
void rtc_init(uint32_t ps) {
	_isrptr_alr = _isrptr_ovf = empty_handler;								//set default isr_ptr value

	//enable backup domain
	RCC->APB1ENR |= RCC_APB1ENR_PWREN;                            // enable clock for Power interface
	PWR->CR      |= PWR_CR_DBP;                                   // enable access to RTC, BDC registers

	RCC->BDCR |= (RCC_BDCR_RTCSEL_LSI | RCC_BDCR_RTCEN);          // set RTC clock source(LSI/LSE/HSE), enable RTC clock

	//enable LSI -> only if LSI is used as a clock source
	RCC->CSR |= RCC_CSR_LSION;					//1->turn on LSI, 0->turn off LSI
	while ((RCC->CSR & RCC_CSR_LSIRDY) == 0) continue;	//1->LSI ready, 0->LSI not ready

	//configure RTC
	//unlocking sequence needed for CRL, CNT and ALR registers
	while ((RTC->CRL & RTC_CRL_RTOFF) == 0) continue;	//wait for RTOFF value to 1 -> prior operations have finished
	RTC->CRL |= RTC_CRL_CNF;					//1->set CNF to enter configuration mode, 0->exit configuration mode
	//write to one or more RTC registers
	ps = ps - 1;
	RTC->PRLH = ps >> 16; RTC->PRLL = ps;		//set up the preload register
	//RTC->ALRH = alr>> 16; RTC->ALRL = alr;		//set up the alarm
	RTC->CRL &=~(RTC_CRL_OWF | RTC_CRL_ALRF | RTC_CRL_SECF);					//clear the overflow flags
	RTC->CRH &=~(RTC_CRH_OWIE | RTC_CRH_ALRIE | RTC_CRH_SECIE);					//1->enable overflow interrupt

	//locking sequency
	RTC->CRL &=~RTC_CRL_CNF;					//1->set CNF to enter configuration mode, 0->exit configuration mode
	while ((RTC->CRL & RTC_CRL_RTOFF) == 0) continue;	//wait for RTOFF value to 1 -> prior operations have finished
	//NVIC_EnableIRQ(RTC_IRQn);					//enable rtc handler
}

//install rtc overflow isr
void rtc_act(void (*isr_ptr)(void)) {
	_isrptr_ovf = isr_ptr;						//install user handler
	//clear the flags
	RTC->CRL &=~(RTC_CRL_OWF | RTC_CRL_ALRF | RTC_CRL_SECF);					//clear the overflow flags
	RTC->CRH |= RTC_CRH_OWIE;					//1->enable overflow interrupt
	NVIC_EnableIRQ(RTC_IRQn);					//enable rtc handler
}

//read rtc counter
uint32_t rtc_get(void) {
	uint32_t tmp;
	uint16_t lsb;

	//tmp = RTC->CNTH;
	//tmp = (tmp << 16) | RTC->CNTL;
	//return tmp;
	do {
		tmp = RTC->CNTH;
		lsb = RTC->CNTL;
	} while (tmp != RTC->CNTH);

	return (tmp << 16) | lsb;	
}

//set rtc counter
uint32_t rtc_set(uint32_t val) {
	//unlocking sequence needed for CRL, CNT and ALR registers
	while ((RTC->CRL & RTC_CRL_RTOFF) == 0) continue;	//wait for RTOFF value to 1 -> prior operations have finished
	RTC->CRL |= RTC_CRL_CNF;					//1->set CNF to enter configuration mode, 0->exit configuration mode
	//write to one or more RTC registers
	RTC->CNTH = val >> 16; RTC->CNTL = val;
	//RTC->ALRH = alr>> 16; RTC->ALRL = alr;		//set up the alarm
	//locking sequency
	RTC->CRL &=~RTC_CRL_CNF;					//1->set CNF to enter configuration mode, 0->exit configuration mode
	while ((RTC->CRL & RTC_CRL_RTOFF) == 0) continue;	//wait for RTOFF value to 1 -> prior operations have finished
	return val;
}

