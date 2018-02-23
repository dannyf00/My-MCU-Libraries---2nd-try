//#include "stm8s.h"							//we use stm8s
#include "gpio.h"							//we use gpio

//global defines
//external high speed oscillator
#if !defined(HSE_VALUE)						//maybe defined by user in the preprocessor
#define HSE_VALUE		16000000ul			//default to 16Mhz crystal
#endif

//internal high speed oscillator
#if !defined(HSI_VALUE)						//if hsi is not defined
#define HSI_VALUE		16000000ul			//actual values may vary=16Mhz
#endif

//internal high speed oscillator
#if !defined(LSI_VALUE)						//if hsi is not defined
#define LSI_VALUE		128000				//low speed oscillator=128Khz
#endif

//external low speed oscillator
#if !defined(LSE_VALUE)						//if hsi is not defined
#define LSE_VALUE		32768				//low speed oscillator
#endif


//global variables
volatile uint32_t SystemCoreClock=16000000ul/8;				//systemcoreclock. defaults to HSI (@16Mhz) / 8

//use hsi oscillator
void SystemCoreClockHSI(uint8_t CLK_HSIDIV) {
   /* check the parameters */
    //assert_param(IS_CLK_PRESCALER_OK(CLK_HSIDIV));
	
	//CLK_DeInit();
	CLK->ICKR |= CLK_ICKR_HSIEN;					//enable HSI
	while ((CLK->ICKR & CLK_ICKR_HSIRDY) == 0) continue;	//wait until HSI is ready
	CLK->SWCR|= CLK_SWCR_SWEN;						//start the switch
	CLK->SWR = 0xe1;								//0xe1->HSI, 0xd2->LSI, 0xb4->HSE	//CLK_HSICmd(ENABLE);
	while ((CLK->SWCR & CLK_SWCR_SWBSY) == 1) continue;	//wait until the busy signal is no more	//while(SET != CLK_GetFlagStatus(CLK_FLAG_HSIRDY)) continue;	//make sure hsi is ready
	CLK->CKDIVR = (CLK->CKDIVR &~CLK_CKDIVR_HSIDIV) | (CLK_HSIDIV & CLK_CKDIVR_HSIDIV);	//set hsi divider
	CLK->CKDIVR = (CLK->CKDIVR &~CLK_CKDIVR_CPUDIV) | (CLK_PRESCALER_CPUDIV1& CLK_CKDIVR_CPUDIV);	//set cpu divier -> default to 1:1
	//update SystemCoreClock
	switch (CLK_HSIDIV) {
		case CLK_PRESCALER_HSIDIV1: SystemCoreClock = HSI_VALUE / 1; break;
		case CLK_PRESCALER_HSIDIV2: SystemCoreClock = HSI_VALUE / 2; break;
		case CLK_PRESCALER_HSIDIV4: SystemCoreClock = HSI_VALUE / 4; break;
		case CLK_PRESCALER_HSIDIV8: SystemCoreClock = HSI_VALUE / 8; break;
		default: SystemCoreClock = HSI_VALUE / 8; break;
	}
}

//use hse oscillator
void SystemCoreClockHSE(void) {
   /* check the parameters */
    //assert_param(IS_CLK_PRESCALER_OK(CLK_HSIDIV));
	
	//CLK_DeInit();
	CLK->ECKR |= CLK_ECKR_HSEEN;					//enable HSE
	while ((CLK->ECKR & CLK_ECKR_HSERDY) == 0) continue;	//wait until HSE is ready
	CLK->SWCR|= CLK_SWCR_SWEN;						//start the switch
	CLK->SWR = 0xb4;								//0xe1->HSI, 0xd2->LSI, 0xb4->HSE	//CLK_HSICmd(ENABLE);
	while ((CLK->SWCR & CLK_SWCR_SWBSY) == 1) continue;	//wait until the busy signal is no more	//while(SET != CLK_GetFlagStatus(CLK_FLAG_HSIRDY)) continue;	//make sure hsi is ready
	//update SystemCoreClock
	SystemCoreClock = HSE_VALUE;
}

//reset the mcu
void mcu_init(void){
	//SystemCoreClockHSI_16MHz();						//set clock to hsi, _2MHz, _4MHz, _8MHz, _16MHz
	//SystemCoreClockHSE();							//set clock to hse, @ HSE_VALUE
	//SystemCoreClockHSI_2MHz();						//set clock to hsi, _2MHz, _4MHz, _8MHz, _16MHz
	//SystemCoreClockLSI();							//running at LSI (=128Khz)
	//CLK->PCKENR1=CLK->PCKENR2=0x00;					//disable all peripheral clocks
	//CLK_PeripheralClockConfig(CLK_PERIPHERAL_TIMER2, ENABLE);	//enable clock to tim2
}

#ifdef USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *   where the assert_param error has occurred.
  * @param file: pointer to the source file name
  * @param line: assert_param error line source number
  * @retval : None
  */
void assert_failed(u8* file, u32 line)
{ 
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif
