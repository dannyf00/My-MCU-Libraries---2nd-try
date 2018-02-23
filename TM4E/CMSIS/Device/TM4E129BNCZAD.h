
/****************************************************************************************************//**
 * @file     TM4E129BNCZAD.h
 *
 * @brief    CMSIS Cortex-M4 Peripheral Access Layer Header File for
 *           TM4E129BNCZAD from Texas Instruments.
 *
 * @version  V10956
 * @date     5. June 2013
 *
 * @note     Generated with SVDConv V2.79b 
 *           from CMSIS SVD File 'TM4E129BNCZAD.svd.xml' Version 10956,
 *
 * @par      
 *           Software License Agreement
 *           
 *           Texas Instruments (TI) is supplying this software for use solely and
 *           exclusively on TI's microcontroller products. The software is owned by
 *           TI and/or its suppliers, and is protected under applicable copyright
 *           laws. You may not combine this software with "viral" open-source
 *           software in order to form a larger program.
 *           
 *           THIS SOFTWARE IS PROVIDED "AS IS" AND WITH ALL FAULTS.
 *           NO WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT
 *           NOT LIMITED TO, IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 *           A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE. TI SHALL NOT, UNDER ANY
 *           CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL, OR CONSEQUENTIAL
 *           DAMAGES, FOR ANY REASON WHATSOEVER.
 *           
 *           
 *
 *******************************************************************************************************/



/** @addtogroup Texas Instruments
  * @{
  */

/** @addtogroup TM4E129BNCZAD
  * @{
  */

#ifndef TM4E129BNCZAD_H
#define TM4E129BNCZAD_H

#ifdef __cplusplus
extern "C" {
#endif


/* -------------------------  Interrupt Number Definition  ------------------------ */

typedef enum {
/* -------------------  Cortex-M4 Processor Exceptions Numbers  ------------------- */
  Reset_IRQn                    = -15,              /*!<   1  Reset Vector, invoked on Power up and warm reset                 */
  NonMaskableInt_IRQn           = -14,              /*!<   2  Non maskable Interrupt, cannot be stopped or preempted           */
  HardFault_IRQn                = -13,              /*!<   3  Hard Fault, all classes of Fault                                 */
  MemoryManagement_IRQn         = -12,              /*!<   4  Memory Management, MPU mismatch, including Access Violation
                                                         and No Match                                                          */
  BusFault_IRQn                 = -11,              /*!<   5  Bus Fault, Pre-Fetch-, Memory Access Fault, other address/memory
                                                         related Fault                                                         */
  UsageFault_IRQn               = -10,              /*!<   6  Usage Fault, i.e. Undef Instruction, Illegal State Transition    */
  SVCall_IRQn                   =  -5,              /*!<  11  System Service Call via SVC instruction                          */
  DebugMonitor_IRQn             =  -4,              /*!<  12  Debug Monitor                                                    */
  PendSV_IRQn                   =  -2,              /*!<  14  Pendable request for system service                              */
  SysTick_IRQn                  =  -1,              /*!<  15  System Tick Timer                                                */
/* ------------------  TM4E129BNCZAD Specific Interrupt Numbers  ------------------ */
  GPIOA_IRQn                    =   0,              /*!<   0  GPIOA                                                            */
  GPIOB_IRQn                    =   1,              /*!<   1  GPIOB                                                            */
  GPIOC_IRQn                    =   2,              /*!<   2  GPIOC                                                            */
  GPIOD_IRQn                    =   3,              /*!<   3  GPIOD                                                            */
  GPIOE_IRQn                    =   4,              /*!<   4  GPIOE                                                            */
  UART0_IRQn                    =   5,              /*!<   5  UART0                                                            */
  UART1_IRQn                    =   6,              /*!<   6  UART1                                                            */
  SSI0_IRQn                     =   7,              /*!<   7  SSI0                                                             */
  I2C0_IRQn                     =   8,              /*!<   8  I2C0                                                             */
  ADC0SS0_IRQn                  =  14,              /*!<  14  ADC0SS0                                                          */
  ADC0SS1_IRQn                  =  15,              /*!<  15  ADC0SS1                                                          */
  ADC0SS2_IRQn                  =  16,              /*!<  16  ADC0SS2                                                          */
  ADC0SS3_IRQn                  =  17,              /*!<  17  ADC0SS3                                                          */
  WATCHDOG0_IRQn                =  18,              /*!<  18  WATCHDOG0                                                        */
  TIMER0A_IRQn                  =  19,              /*!<  19  TIMER0A                                                          */
  TIMER0B_IRQn                  =  20,              /*!<  20  TIMER0B                                                          */
  TIMER1A_IRQn                  =  21,              /*!<  21  TIMER1A                                                          */
  TIMER1B_IRQn                  =  22,              /*!<  22  TIMER1B                                                          */
  TIMER2A_IRQn                  =  23,              /*!<  23  TIMER2A                                                          */
  TIMER2B_IRQn                  =  24,              /*!<  24  TIMER2B                                                          */
  COMP0_IRQn                    =  25,              /*!<  25  COMP0                                                            */
  COMP1_IRQn                    =  26,              /*!<  26  COMP1                                                            */
  COMP2_IRQn                    =  27,              /*!<  27  COMP2                                                            */
  SYSCTL_IRQn                   =  28,              /*!<  28  SYSCTL                                                           */
  FLASH_CTRL_IRQn               =  29,              /*!<  29  FLASH_CTRL                                                       */
  GPIOF_IRQn                    =  30,              /*!<  30  GPIOF                                                            */
  GPIOG_IRQn                    =  31,              /*!<  31  GPIOG                                                            */
  GPIOH_IRQn                    =  32,              /*!<  32  GPIOH                                                            */
  UART2_IRQn                    =  33,              /*!<  33  UART2                                                            */
  SSI1_IRQn                     =  34,              /*!<  34  SSI1                                                             */
  TIMER3A_IRQn                  =  35,              /*!<  35  TIMER3A                                                          */
  TIMER3B_IRQn                  =  36,              /*!<  36  TIMER3B                                                          */
  I2C1_IRQn                     =  37,              /*!<  37  I2C1                                                             */
  EMAC0_IRQn                    =  40,              /*!<  40  EMAC0                                                            */
  HIB_IRQn                      =  41,              /*!<  41  HIB                                                              */
  USB0_IRQn                     =  42,              /*!<  42  USB0                                                             */
  UDMA_IRQn                     =  44,              /*!<  44  UDMA                                                             */
  UDMAERR_IRQn                  =  45,              /*!<  45  UDMAERR                                                          */
  ADC1SS0_IRQn                  =  46,              /*!<  46  ADC1SS0                                                          */
  ADC1SS1_IRQn                  =  47,              /*!<  47  ADC1SS1                                                          */
  ADC1SS2_IRQn                  =  48,              /*!<  48  ADC1SS2                                                          */
  ADC1SS3_IRQn                  =  49,              /*!<  49  ADC1SS3                                                          */
  EPI0_IRQn                     =  50,              /*!<  50  EPI0                                                             */
  GPIOJ_IRQn                    =  51,              /*!<  51  GPIOJ                                                            */
  GPIOK_IRQn                    =  52,              /*!<  52  GPIOK                                                            */
  GPIOL_IRQn                    =  53,              /*!<  53  GPIOL                                                            */
  SSI2_IRQn                     =  54,              /*!<  54  SSI2                                                             */
  SSI3_IRQn                     =  55,              /*!<  55  SSI3                                                             */
  UART3_IRQn                    =  56,              /*!<  56  UART3                                                            */
  UART4_IRQn                    =  57,              /*!<  57  UART4                                                            */
  UART5_IRQn                    =  58,              /*!<  58  UART5                                                            */
  UART6_IRQn                    =  59,              /*!<  59  UART6                                                            */
  UART7_IRQn                    =  60,              /*!<  60  UART7                                                            */
  I2C2_IRQn                     =  61,              /*!<  61  I2C2                                                             */
  I2C3_IRQn                     =  62,              /*!<  62  I2C3                                                             */
  TIMER4A_IRQn                  =  63,              /*!<  63  TIMER4A                                                          */
  TIMER4B_IRQn                  =  64,              /*!<  64  TIMER4B                                                          */
  TIMER5A_IRQn                  =  65,              /*!<  65  TIMER5A                                                          */
  TIMER5B_IRQn                  =  66,              /*!<  66  TIMER5B                                                          */
  SYSEXC_IRQn                   =  67,              /*!<  67  SYSEXC                                                           */
  PECI0_IRQn                    =  68,              /*!<  68  PECI0                                                            */
  I2C4_IRQn                     =  70,              /*!<  70  I2C4                                                             */
  I2C5_IRQn                     =  71,              /*!<  71  I2C5                                                             */
  GPIOM_IRQn                    =  72,              /*!<  72  GPIOM                                                            */
  GPION_IRQn                    =  73,              /*!<  73  GPION                                                            */
  FAN0_IRQn                     =  74,              /*!<  74  FAN0                                                             */
  GPIOP0_IRQn                   =  76,              /*!<  76  GPIOP0                                                           */
  GPIOP1_IRQn                   =  77,              /*!<  77  GPIOP1                                                           */
  GPIOP2_IRQn                   =  78,              /*!<  78  GPIOP2                                                           */
  GPIOP3_IRQn                   =  79,              /*!<  79  GPIOP3                                                           */
  GPIOP4_IRQn                   =  80,              /*!<  80  GPIOP4                                                           */
  GPIOP5_IRQn                   =  81,              /*!<  81  GPIOP5                                                           */
  GPIOP6_IRQn                   =  82,              /*!<  82  GPIOP6                                                           */
  GPIOP7_IRQn                   =  83,              /*!<  83  GPIOP7                                                           */
  GPIOQ0_IRQn                   =  84,              /*!<  84  GPIOQ0                                                           */
  GPIOQ1_IRQn                   =  85,              /*!<  85  GPIOQ1                                                           */
  GPIOQ2_IRQn                   =  86,              /*!<  86  GPIOQ2                                                           */
  GPIOQ3_IRQn                   =  87,              /*!<  87  GPIOQ3                                                           */
  GPIOQ4_IRQn                   =  88,              /*!<  88  GPIOQ4                                                           */
  GPIOQ5_IRQn                   =  89,              /*!<  89  GPIOQ5                                                           */
  GPIOQ6_IRQn                   =  90,              /*!<  90  GPIOQ6                                                           */
  GPIOQ7_IRQn                   =  91,              /*!<  91  GPIOQ7                                                           */
  GPIOR_IRQn                    =  92,              /*!<  92  GPIOR                                                            */
  GPIOS_IRQn                    =  93,              /*!<  93  GPIOS                                                            */
  TIMER6A_IRQn                  =  98,              /*!<  98  TIMER6A                                                          */
  TIMER6B_IRQn                  =  99,              /*!<  99  TIMER6B                                                          */
  TIMER7A_IRQn                  = 100,              /*!< 100  TIMER7A                                                          */
  TIMER7B_IRQn                  = 101,              /*!< 101  TIMER7B                                                          */
  I2C6_IRQn                     = 102,              /*!< 102  I2C6                                                             */
  I2C7_IRQn                     = 103,              /*!< 103  I2C7                                                             */
  ONEWIRE0_IRQn                 = 105,              /*!< 105  ONEWIRE0                                                         */
  I2C8_IRQn                     = 109,              /*!< 109  I2C8                                                             */
  I2C9_IRQn                     = 110,              /*!< 110  I2C9                                                             */
  GPIOT_IRQn                    = 111,              /*!< 111  GPIOT                                                            */
  FAN1_IRQn                     = 112               /*!< 112  FAN1                                                             */
} IRQn_Type;


/** @addtogroup Configuration_of_CMSIS
  * @{
  */


/* ================================================================================ */
/* ================      Processor and Core Peripheral Section     ================ */
/* ================================================================================ */

/* ----------------Configuration of the Cortex-M4 Processor and Core Peripherals---------------- */
#define __CM4_REV                 0x0102            /*!< Cortex-M4 Core Revision                                               */
#define __MPU_PRESENT                  0            /*!< MPU present or not                                                    */
#define __NVIC_PRIO_BITS               3            /*!< Number of Bits used for Priority Levels                               */
#define __Vendor_SysTickConfig         0            /*!< Set to 1 if different SysTick Config is used                          */
#define __FPU_PRESENT                  1            /*!< FPU present or not                                                    */
/** @} */ /* End of group Configuration_of_CMSIS */

#include "core_cm4.h"                               /*!< Cortex-M4 processor and core peripherals                              */
#include "system_TM4E129.h"                         /*!< TM4E129BNCZAD System                                                  */


/* ================================================================================ */
/* ================       Device Specific Peripheral Section       ================ */
/* ================================================================================ */


/** @addtogroup Device_Peripheral_Registers
  * @{
  */


/* -------------------  Start of section using anonymous unions  ------------------ */
#if defined(__CC_ARM)
  #pragma push
  #pragma anon_unions
#elif defined(__ICCARM__)
  #pragma language=extended
#elif defined(__GNUC__)
  /* anonymous unions are enabled by default */
#elif defined(__TMS470__)
/* anonymous unions are enabled by default */
#elif defined(__TASKING__)
  #pragma warning 586
#else
  #warning Not supported compiler type
#endif



/* ================================================================================ */
/* ================                    WATCHDOG0                   ================ */
/* ================================================================================ */


/**
  * @brief Register map for WATCHDOG0 peripheral (WATCHDOG0)
  */

typedef struct {                                    /*!< WATCHDOG0 Structure                                                   */
  __IO uint32_t  LOAD;                              /*!< Watchdog Load                                                         */
  __IO uint32_t  VALUE;                             /*!< Watchdog Value                                                        */
  __IO uint32_t  CTL;                               /*!< Watchdog Control                                                      */
  __O  uint32_t  ICR;                               /*!< Watchdog Interrupt Clear                                              */
  __IO uint32_t  RIS;                               /*!< Watchdog Raw Interrupt Status                                         */
  __IO uint32_t  MIS;                               /*!< Watchdog Masked Interrupt Status                                      */
  __I  uint32_t  RESERVED0[256];
  __IO uint32_t  TEST;                              /*!< Watchdog Test                                                         */
  __I  uint32_t  RESERVED1[505];
  __IO uint32_t  LOCK;                              /*!< Watchdog Lock                                                         */
} WATCHDOG0_Type;


/* ================================================================================ */
/* ================                      SSI0                      ================ */
/* ================================================================================ */


/**
  * @brief Register map for SSI0 peripheral (SSI0)
  */

typedef struct {                                    /*!< SSI0 Structure                                                        */
  __IO uint32_t  CR0;                               /*!< SSI Control 0                                                         */
  __IO uint32_t  CR1;                               /*!< SSI Control 1                                                         */
  __IO uint32_t  DR;                                /*!< SSI Data                                                              */
  __IO uint32_t  SR;                                /*!< SSI Status                                                            */
  __IO uint32_t  CPSR;                              /*!< SSI Clock Prescale                                                    */
  __IO uint32_t  IM;                                /*!< SSI Interrupt Mask                                                    */
  __IO uint32_t  RIS;                               /*!< SSI Raw Interrupt Status                                              */
  __IO uint32_t  MIS;                               /*!< SSI Masked Interrupt Status                                           */
  __O  uint32_t  ICR;                               /*!< SSI Interrupt Clear                                                   */
  __IO uint32_t  DMACTL;                            /*!< SSI DMA Control                                                       */
  __I  uint32_t  RESERVED0[998];
  __IO uint32_t  PP;                                /*!< SSI Peripheral Properties                                             */
  __I  uint32_t  RESERVED1;
  __IO uint32_t  CC;                                /*!< SSI Clock Configuration                                               */
} SSI0_Type;


/* ================================================================================ */
/* ================                      UART0                     ================ */
/* ================================================================================ */


/**
  * @brief Register map for UART0 peripheral (UART0)
  */

typedef struct {                                    /*!< UART0 Structure                                                       */
  __IO uint32_t  DR;                                /*!< UART Data                                                             */
  
  union {
    __IO uint32_t  ECR_UART_ALT;                    /*!< UART Receive Status/Error Clear                                       */
    __IO uint32_t  RSR;                             /*!< UART Receive Status/Error Clear                                       */
  };
  __I  uint32_t  RESERVED0[4];
  __IO uint32_t  FR;                                /*!< UART Flag                                                             */
  __I  uint32_t  RESERVED1;
  __IO uint32_t  ILPR;                              /*!< UART IrDA Low-Power Register                                          */
  __IO uint32_t  IBRD;                              /*!< UART Integer Baud-Rate Divisor                                        */
  __IO uint32_t  FBRD;                              /*!< UART Fractional Baud-Rate Divisor                                     */
  __IO uint32_t  LCRH;                              /*!< UART Line Control                                                     */
  __IO uint32_t  CTL;                               /*!< UART Control                                                          */
  __IO uint32_t  IFLS;                              /*!< UART Interrupt FIFO Level Select                                      */
  __IO uint32_t  IM;                                /*!< UART Interrupt Mask                                                   */
  __IO uint32_t  RIS;                               /*!< UART Raw Interrupt Status                                             */
  __IO uint32_t  MIS;                               /*!< UART Masked Interrupt Status                                          */
  __O  uint32_t  ICR;                               /*!< UART Interrupt Clear                                                  */
  __IO uint32_t  DMACTL;                            /*!< UART DMA Control                                                      */
  __I  uint32_t  RESERVED2[22];
  __IO uint32_t  _9BITADDR;                         /*!< UART 9-Bit Self Address                                               */
  __IO uint32_t  _9BITAMASK;                        /*!< UART 9-Bit Self Address Mask                                          */
  __I  uint32_t  RESERVED3[965];
  __IO uint32_t  PP;                                /*!< UART Peripheral Properties                                            */
  __I  uint32_t  RESERVED4;
  __IO uint32_t  CC;                                /*!< UART Clock Configuration                                              */
} UART0_Type;


/* ================================================================================ */
/* ================                      I2C0                      ================ */
/* ================================================================================ */


/**
  * @brief Register map for I2C0 peripheral (I2C0)
  */

typedef struct {                                    /*!< I2C0 Structure                                                        */
  __IO uint32_t  MSA;                               /*!< I2C Master Slave Address                                              */
  
  union {
    __IO uint32_t  MCS_I2C0_ALT;                    /*!< I2C Master Control/Status                                             */
    __IO uint32_t  MCS;                             /*!< I2C Master Control/Status                                             */
  };
  __IO uint32_t  MDR;                               /*!< I2C Master Data                                                       */
  __IO uint32_t  MTPR;                              /*!< I2C Master Timer Period                                               */
  __IO uint32_t  MIMR;                              /*!< I2C Master Interrupt Mask                                             */
  __IO uint32_t  MRIS;                              /*!< I2C Master Raw Interrupt Status                                       */
  __IO uint32_t  MMIS;                              /*!< I2C Master Masked Interrupt Status                                    */
  __O  uint32_t  MICR;                              /*!< I2C Master Interrupt Clear                                            */
  __IO uint32_t  MCR;                               /*!< I2C Master Configuration                                              */
  __IO uint32_t  MCLKOCNT;                          /*!< I2C Master Clock Low Timeout Count                                    */
  __I  uint32_t  RESERVED0;
  __IO uint32_t  MBMON;                             /*!< I2C Master Bus Monitor                                                */
  __IO uint32_t  MBLEN;                             /*!< I2C Master Burst Length                                               */
  __IO uint32_t  MBCNT;                             /*!< I2C Master Burst Count                                                */
  __I  uint32_t  RESERVED1[498];
  __IO uint32_t  SOAR;                              /*!< I2C Slave Own Address                                                 */
  
  union {
    __IO uint32_t  SCSR_I2C0_ALT;                   /*!< I2C Slave Control/Status                                              */
    __IO uint32_t  SCSR;                            /*!< I2C Slave Control/Status                                              */
  };
  __IO uint32_t  SDR;                               /*!< I2C Slave Data                                                        */
  __IO uint32_t  SIMR;                              /*!< I2C Slave Interrupt Mask                                              */
  __IO uint32_t  SRIS;                              /*!< I2C Slave Raw Interrupt Status                                        */
  __IO uint32_t  SMIS;                              /*!< I2C Slave Masked Interrupt Status                                     */
  __O  uint32_t  SICR;                              /*!< I2C Slave Interrupt Clear                                             */
  __IO uint32_t  SOAR2;                             /*!< I2C Slave Own Address 2                                               */
  __IO uint32_t  SACKCTL;                           /*!< I2C Slave ACK Control                                                 */
  __I  uint32_t  RESERVED2[439];
  __IO uint32_t  FIFODATA;                          /*!< I2C FIFO Data                                                         */
  __IO uint32_t  FIFOCTL;                           /*!< I2C FIFO Control                                                      */
  __IO uint32_t  FIFOSTATUS;                        /*!< I2C FIFO Status                                                       */
  __I  uint32_t  RESERVED3[45];
  __IO uint32_t  PP;                                /*!< I2C Peripheral Properties                                             */
  __IO uint32_t  PC;                                /*!< I2C Peripheral Configuration                                          */
} I2C0_Type;


/* ================================================================================ */
/* ================                     TIMER0                     ================ */
/* ================================================================================ */


/**
  * @brief Register map for TIMER0 peripheral (TIMER0)
  */

typedef struct {                                    /*!< TIMER0 Structure                                                      */
  __IO uint32_t  CFG;                               /*!< GPTM Configuration                                                    */
  __IO uint32_t  TAMR;                              /*!< GPTM Timer A Mode                                                     */
  __IO uint32_t  TBMR;                              /*!< GPTM Timer B Mode                                                     */
  __IO uint32_t  CTL;                               /*!< GPTM Control                                                          */
  __IO uint32_t  SYNC;                              /*!< GPTM Synchronize                                                      */
  __I  uint32_t  RESERVED0;
  __IO uint32_t  IMR;                               /*!< GPTM Interrupt Mask                                                   */
  __IO uint32_t  RIS;                               /*!< GPTM Raw Interrupt Status                                             */
  __IO uint32_t  MIS;                               /*!< GPTM Masked Interrupt Status                                          */
  __O  uint32_t  ICR;                               /*!< GPTM Interrupt Clear                                                  */
  __IO uint32_t  TAILR;                             /*!< GPTM Timer A Interval Load                                            */
  __IO uint32_t  TBILR;                             /*!< GPTM Timer B Interval Load                                            */
  __IO uint32_t  TAMATCHR;                          /*!< GPTM Timer A Match                                                    */
  __IO uint32_t  TBMATCHR;                          /*!< GPTM Timer B Match                                                    */
  __IO uint32_t  TAPR;                              /*!< GPTM Timer A Prescale                                                 */
  __IO uint32_t  TBPR;                              /*!< GPTM Timer B Prescale                                                 */
  __IO uint32_t  TAPMR;                             /*!< GPTM TimerA Prescale Match                                            */
  __IO uint32_t  TBPMR;                             /*!< GPTM TimerB Prescale Match                                            */
  __IO uint32_t  TAR;                               /*!< GPTM Timer A                                                          */
  __IO uint32_t  TBR;                               /*!< GPTM Timer B                                                          */
  __IO uint32_t  TAV;                               /*!< GPTM Timer A Value                                                    */
  __IO uint32_t  TBV;                               /*!< GPTM Timer B Value                                                    */
  __IO uint32_t  RTCPD;                             /*!< GPTM RTC Predivide                                                    */
  __I  uint32_t  RESERVED1[4];
  __IO uint32_t  DMAEV;                             /*!< GPTM DMA Event                                                        */
  __IO uint32_t  ADCEV;                             /*!< GPTM ADC Event                                                        */
  __I  uint32_t  RESERVED2[979];
  __IO uint32_t  PP;                                /*!< GPTM Peripheral Properties                                            */
  __I  uint32_t  RESERVED3;
  __IO uint32_t  CC;                                /*!< GPTM Clock Configuration                                              */
} TIMER0_Type;


/* ================================================================================ */
/* ================                      ADC0                      ================ */
/* ================================================================================ */


/**
  * @brief Register map for ADC0 peripheral (ADC0)
  */

typedef struct {                                    /*!< ADC0 Structure                                                        */
  __IO uint32_t  ACTSS;                             /*!< ADC Active Sample Sequencer                                           */
  __IO uint32_t  RIS;                               /*!< ADC Raw Interrupt Status                                              */
  __IO uint32_t  IM;                                /*!< ADC Interrupt Mask                                                    */
  __IO uint32_t  ISC;                               /*!< ADC Interrupt Status and Clear                                        */
  __IO uint32_t  OSTAT;                             /*!< ADC Overflow Status                                                   */
  __IO uint32_t  EMUX;                              /*!< ADC Event Multiplexer Select                                          */
  __IO uint32_t  USTAT;                             /*!< ADC Underflow Status                                                  */
  __I  uint32_t  RESERVED0;
  __IO uint32_t  SSPRI;                             /*!< ADC Sample Sequencer Priority                                         */
  __IO uint32_t  SPC;                               /*!< ADC Sample Phase Control                                              */
  __IO uint32_t  PSSI;                              /*!< ADC Processor Sample Sequence Initiate                                */
  __I  uint32_t  RESERVED1;
  __IO uint32_t  SAC;                               /*!< ADC Sample Averaging Control                                          */
  __IO uint32_t  DCISC;                             /*!< ADC Digital Comparator Interrupt Status and Clear                     */
  __IO uint32_t  CTL;                               /*!< ADC Control                                                           */
  __I  uint32_t  RESERVED2;
  __IO uint32_t  SSMUX0;                            /*!< ADC Sample Sequence Input Multiplexer Select 0                        */
  __IO uint32_t  SSCTL0;                            /*!< ADC Sample Sequence Control 0                                         */
  __IO uint32_t  SSFIFO0;                           /*!< ADC Sample Sequence Result FIFO 0                                     */
  __IO uint32_t  SSFSTAT0;                          /*!< ADC Sample Sequence FIFO 0 Status                                     */
  __IO uint32_t  SSOP0;                             /*!< ADC Sample Sequence 0 Operation                                       */
  __IO uint32_t  SSDC0;                             /*!< ADC Sample Sequence 0 Digital Comparator Select                       */
  __IO uint32_t  SSEMUX0;                           /*!< ADC Sample Sequence Extended Input Multiplexer Select 0               */
  __IO uint32_t  SSTSH0;                            /*!< ADC Sample Sequence 0 Sample and Hold Time                            */
  __IO uint32_t  SSMUX1;                            /*!< ADC Sample Sequence Input Multiplexer Select 1                        */
  __IO uint32_t  SSCTL1;                            /*!< ADC Sample Sequence Control 1                                         */
  __IO uint32_t  SSFIFO1;                           /*!< ADC Sample Sequence Result FIFO 1                                     */
  __IO uint32_t  SSFSTAT1;                          /*!< ADC Sample Sequence FIFO 1 Status                                     */
  __IO uint32_t  SSOP1;                             /*!< ADC Sample Sequence 1 Operation                                       */
  __IO uint32_t  SSDC1;                             /*!< ADC Sample Sequence 1 Digital Comparator Select                       */
  __IO uint32_t  SSEMUX1;                           /*!< ADC Sample Sequence Extended Input Multiplexer Select 1               */
  __IO uint32_t  SSTSH1;                            /*!< ADC Sample Sequence 1 Sample and Hold Time                            */
  __IO uint32_t  SSMUX2;                            /*!< ADC Sample Sequence Input Multiplexer Select 2                        */
  __IO uint32_t  SSCTL2;                            /*!< ADC Sample Sequence Control 2                                         */
  __IO uint32_t  SSFIFO2;                           /*!< ADC Sample Sequence Result FIFO 2                                     */
  __IO uint32_t  SSFSTAT2;                          /*!< ADC Sample Sequence FIFO 2 Status                                     */
  __IO uint32_t  SSOP2;                             /*!< ADC Sample Sequence 2 Operation                                       */
  __IO uint32_t  SSDC2;                             /*!< ADC Sample Sequence 2 Digital Comparator Select                       */
  __IO uint32_t  SSEMUX2;                           /*!< ADC Sample Sequence Extended Input Multiplexer Select 2               */
  __IO uint32_t  SSTSH2;                            /*!< ADC Sample Sequence 2 Sample and Hold Time                            */
  __IO uint32_t  SSMUX3;                            /*!< ADC Sample Sequence Input Multiplexer Select 3                        */
  __IO uint32_t  SSCTL3;                            /*!< ADC Sample Sequence Control 3                                         */
  __IO uint32_t  SSFIFO3;                           /*!< ADC Sample Sequence Result FIFO 3                                     */
  __IO uint32_t  SSFSTAT3;                          /*!< ADC Sample Sequence FIFO 3 Status                                     */
  __IO uint32_t  SSOP3;                             /*!< ADC Sample Sequence 3 Operation                                       */
  __IO uint32_t  SSDC3;                             /*!< ADC Sample Sequence 3 Digital Comparator Select                       */
  __IO uint32_t  SSEMUX3;                           /*!< ADC Sample Sequence Extended Input Multiplexer Select 3               */
  __IO uint32_t  SSTSH3;                            /*!< ADC Sample Sequence 3 Sample and Hold Time                            */
  __I  uint32_t  RESERVED3[784];
  __O  uint32_t  DCRIC;                             /*!< ADC Digital Comparator Reset Initial Conditions                       */
  __I  uint32_t  RESERVED4[63];
  __IO uint32_t  DCCTL0;                            /*!< ADC Digital Comparator Control 0                                      */
  __IO uint32_t  DCCTL1;                            /*!< ADC Digital Comparator Control 1                                      */
  __IO uint32_t  DCCTL2;                            /*!< ADC Digital Comparator Control 2                                      */
  __IO uint32_t  DCCTL3;                            /*!< ADC Digital Comparator Control 3                                      */
  __IO uint32_t  DCCTL4;                            /*!< ADC Digital Comparator Control 4                                      */
  __IO uint32_t  DCCTL5;                            /*!< ADC Digital Comparator Control 5                                      */
  __IO uint32_t  DCCTL6;                            /*!< ADC Digital Comparator Control 6                                      */
  __IO uint32_t  DCCTL7;                            /*!< ADC Digital Comparator Control 7                                      */
  __I  uint32_t  RESERVED5[8];
  __IO uint32_t  DCCMP0;                            /*!< ADC Digital Comparator Range 0                                        */
  __IO uint32_t  DCCMP1;                            /*!< ADC Digital Comparator Range 1                                        */
  __IO uint32_t  DCCMP2;                            /*!< ADC Digital Comparator Range 2                                        */
  __IO uint32_t  DCCMP3;                            /*!< ADC Digital Comparator Range 3                                        */
  __IO uint32_t  DCCMP4;                            /*!< ADC Digital Comparator Range 4                                        */
  __IO uint32_t  DCCMP5;                            /*!< ADC Digital Comparator Range 5                                        */
  __IO uint32_t  DCCMP6;                            /*!< ADC Digital Comparator Range 6                                        */
  __IO uint32_t  DCCMP7;                            /*!< ADC Digital Comparator Range 7                                        */
  __I  uint32_t  RESERVED6[88];
  __IO uint32_t  PP;                                /*!< ADC Peripheral Properties                                             */
  __IO uint32_t  PC;                                /*!< ADC Peripheral Configuration                                          */
  __IO uint32_t  CC;                                /*!< ADC Clock Configuration                                               */
} ADC0_Type;


/* ================================================================================ */
/* ================                      COMP                      ================ */
/* ================================================================================ */


/**
  * @brief Register map for COMP peripheral (COMP)
  */

typedef struct {                                    /*!< COMP Structure                                                        */
  __IO uint32_t  ACMIS;                             /*!< Analog Comparator Masked Interrupt Status                             */
  __IO uint32_t  ACRIS;                             /*!< Analog Comparator Raw Interrupt Status                                */
  __IO uint32_t  ACINTEN;                           /*!< Analog Comparator Interrupt Enable                                    */
  __I  uint32_t  RESERVED0;
  __IO uint32_t  ACREFCTL;                          /*!< Analog Comparator Reference Voltage Control                           */
  __I  uint32_t  RESERVED1[3];
  __IO uint32_t  ACSTAT0;                           /*!< Analog Comparator Status 0                                            */
  __IO uint32_t  ACCTL0;                            /*!< Analog Comparator Control 0                                           */
  __I  uint32_t  RESERVED2[6];
  __IO uint32_t  ACSTAT1;                           /*!< Analog Comparator Status 1                                            */
  __IO uint32_t  ACCTL1;                            /*!< Analog Comparator Control 1                                           */
  __I  uint32_t  RESERVED3[6];
  __IO uint32_t  ACSTAT2;                           /*!< Analog Comparator Status 2                                            */
  __IO uint32_t  ACCTL2;                            /*!< Analog Comparator Control 2                                           */
  __I  uint32_t  RESERVED4[982];
  __IO uint32_t  PP;                                /*!< Analog Comparator Peripheral Properties                               */
} COMP_Type;


/* ================================================================================ */
/* ================                      USB0                      ================ */
/* ================================================================================ */


/**
  * @brief Register map for USB0 peripheral (USB0)
  */

typedef struct {                                    /*!< USB0 Structure                                                        */
  __IO uint8_t   FADDR;                             /*!< USB Device Functional Address                                         */
  __IO uint8_t   POWER;                             /*!< USB Power                                                             */
  __I  uint16_t  RESERVED0;
  __IO uint16_t  RXIS;                              /*!< USB Receive Interrupt Status                                          */
  __IO uint16_t  TXIE;                              /*!< USB Transmit Interrupt Enable                                         */
  __IO uint16_t  RXIE;                              /*!< USB Receive Interrupt Enable                                          */
  
  union {
    __IO uint8_t   IS_USB0_ALT;                     /*!< USB General Interrupt Status                                          */
    __IO uint8_t   IS;                              /*!< USB General Interrupt Status                                          */
  };
  
  union {
    __IO uint8_t   IE_USB0_ALT;                     /*!< USB Interrupt Enable                                                  */
    __IO uint8_t   IE;                              /*!< USB Interrupt Enable                                                  */
  };
  __IO uint16_t  FRAME;                             /*!< USB Frame Value                                                       */
  __IO uint8_t   EPIDX;                             /*!< USB Endpoint Index                                                    */
  __IO uint8_t   TEST;                              /*!< USB Test Mode                                                         */
  __I  uint32_t  RESERVED1[4];
  __IO uint32_t  FIFO0;                             /*!< USB FIFO Endpoint 0                                                   */
  __IO uint32_t  FIFO1;                             /*!< USB FIFO Endpoint 1                                                   */
  __IO uint32_t  FIFO2;                             /*!< USB FIFO Endpoint 2                                                   */
  __IO uint32_t  FIFO3;                             /*!< USB FIFO Endpoint 3                                                   */
  __IO uint32_t  FIFO4;                             /*!< USB FIFO Endpoint 4                                                   */
  __IO uint32_t  FIFO5;                             /*!< USB FIFO Endpoint 5                                                   */
  __IO uint32_t  FIFO6;                             /*!< USB FIFO Endpoint 6                                                   */
  __IO uint32_t  FIFO7;                             /*!< USB FIFO Endpoint 7                                                   */
  __I  uint32_t  RESERVED2[8];
  __IO uint8_t   DEVCTL;                            /*!< USB Device Control                                                    */
  __IO uint8_t   CCONF;                             /*!< USB Common Configuration                                              */
  __IO uint8_t   TXFIFOSZ;                          /*!< USB Transmit Dynamic FIFO Sizing                                      */
  __IO uint8_t   RXFIFOSZ;                          /*!< USB Receive Dynamic FIFO Sizing                                       */
  __IO uint16_t  TXFIFOADD;                         /*!< USB Transmit FIFO Start Address                                       */
  __IO uint16_t  RXFIFOADD;                         /*!< USB Receive FIFO Start Address                                        */
  __I  uint32_t  RESERVED3[2];
  __IO uint8_t   ULPIVBUSCTL;                       /*!< USB ULPI VBUS Control                                                 */
  __I  uint8_t   RESERVED4[3];
  __IO uint8_t   ULPIREGDATA;                       /*!< USB ULPI Register Data                                                */
  __IO uint8_t   ULPIREGADDR;                       /*!< USB ULPI Register Address                                             */
  __IO uint8_t   ULPIREGCTL;                        /*!< USB ULPI Register Control                                             */
  __IO uint8_t   ULPIRAWDATA;                       /*!< USB ULPI Raw Data                                                     */
  __IO uint8_t   EPINFO;                            /*!< USB Endpoint Information                                              */
  __IO uint8_t   RAMINFO;                           /*!< USB RAM Information                                                   */
  __IO uint8_t   CONTIM;                            /*!< USB Connect Timing                                                    */
  __IO uint8_t   VPLEN;                             /*!< USB OTG VBUS Pulse Timing                                             */
  __IO uint8_t   HSEOF;                             /*!< USB High-Speed Last Transaction to End of Frame Timing                */
  __IO uint8_t   FSEOF;                             /*!< USB Full-Speed Last Transaction to End of Frame Timing                */
  __IO uint8_t   LSEOF;                             /*!< USB Low-Speed Last Transaction to End of Frame Timing                 */
  __I  uint8_t   RESERVED5[1];
  __IO uint8_t   TXFUNCADDR0;                       /*!< USB Transmit Functional Address Endpoint 0                            */
  __I  uint8_t   RESERVED6[1];
  __IO uint8_t   TXHUBADDR0;                        /*!< USB Transmit Hub Address Endpoint 0                                   */
  __IO uint8_t   TXHUBPORT0;                        /*!< USB Transmit Hub Port Endpoint 0                                      */
  __I  uint32_t  RESERVED7;
  __IO uint8_t   TXFUNCADDR1;                       /*!< USB Transmit Functional Address Endpoint 1                            */
  __I  uint8_t   RESERVED8[1];
  __IO uint8_t   TXHUBADDR1;                        /*!< USB Transmit Hub Address Endpoint 1                                   */
  __IO uint8_t   TXHUBPORT1;                        /*!< USB Transmit Hub Port Endpoint 1                                      */
  __IO uint8_t   RXFUNCADDR1;                       /*!< USB Receive Functional Address Endpoint 1                             */
  __I  uint8_t   RESERVED9[1];
  __IO uint8_t   RXHUBADDR1;                        /*!< USB Receive Hub Address Endpoint 1                                    */
  __IO uint8_t   RXHUBPORT1;                        /*!< USB Receive Hub Port Endpoint 1                                       */
  __IO uint8_t   TXFUNCADDR2;                       /*!< USB Transmit Functional Address Endpoint 2                            */
  __I  uint8_t   RESERVED10[1];
  __IO uint8_t   TXHUBADDR2;                        /*!< USB Transmit Hub Address Endpoint 2                                   */
  __IO uint8_t   TXHUBPORT2;                        /*!< USB Transmit Hub Port Endpoint 2                                      */
  __IO uint8_t   RXFUNCADDR2;                       /*!< USB Receive Functional Address Endpoint 2                             */
  __I  uint8_t   RESERVED11[1];
  __IO uint8_t   RXHUBADDR2;                        /*!< USB Receive Hub Address Endpoint 2                                    */
  __IO uint8_t   RXHUBPORT2;                        /*!< USB Receive Hub Port Endpoint 2                                       */
  __IO uint8_t   TXFUNCADDR3;                       /*!< USB Transmit Functional Address Endpoint 3                            */
  __I  uint8_t   RESERVED12[1];
  __IO uint8_t   TXHUBADDR3;                        /*!< USB Transmit Hub Address Endpoint 3                                   */
  __IO uint8_t   TXHUBPORT3;                        /*!< USB Transmit Hub Port Endpoint 3                                      */
  __IO uint8_t   RXFUNCADDR3;                       /*!< USB Receive Functional Address Endpoint 3                             */
  __I  uint8_t   RESERVED13[1];
  __IO uint8_t   RXHUBADDR3;                        /*!< USB Receive Hub Address Endpoint 3                                    */
  __IO uint8_t   RXHUBPORT3;                        /*!< USB Receive Hub Port Endpoint 3                                       */
  __IO uint8_t   TXFUNCADDR4;                       /*!< USB Transmit Functional Address Endpoint 4                            */
  __I  uint8_t   RESERVED14[1];
  __IO uint8_t   TXHUBADDR4;                        /*!< USB Transmit Hub Address Endpoint 4                                   */
  __IO uint8_t   TXHUBPORT4;                        /*!< USB Transmit Hub Port Endpoint 4                                      */
  __IO uint8_t   RXFUNCADDR4;                       /*!< USB Receive Functional Address Endpoint 4                             */
  __I  uint8_t   RESERVED15[1];
  __IO uint8_t   RXHUBADDR4;                        /*!< USB Receive Hub Address Endpoint 4                                    */
  __IO uint8_t   RXHUBPORT4;                        /*!< USB Receive Hub Port Endpoint 4                                       */
  __IO uint8_t   TXFUNCADDR5;                       /*!< USB Transmit Functional Address Endpoint 5                            */
  __I  uint8_t   RESERVED16[1];
  __IO uint8_t   TXHUBADDR5;                        /*!< USB Transmit Hub Address Endpoint 5                                   */
  __IO uint8_t   TXHUBPORT5;                        /*!< USB Transmit Hub Port Endpoint 5                                      */
  __IO uint8_t   RXFUNCADDR5;                       /*!< USB Receive Functional Address Endpoint 5                             */
  __I  uint8_t   RESERVED17[1];
  __IO uint8_t   RXHUBADDR5;                        /*!< USB Receive Hub Address Endpoint 5                                    */
  __IO uint8_t   RXHUBPORT5;                        /*!< USB Receive Hub Port Endpoint 5                                       */
  __IO uint8_t   TXFUNCADDR6;                       /*!< USB Transmit Functional Address Endpoint 6                            */
  __I  uint8_t   RESERVED18[1];
  __IO uint8_t   TXHUBADDR6;                        /*!< USB Transmit Hub Address Endpoint 6                                   */
  __IO uint8_t   TXHUBPORT6;                        /*!< USB Transmit Hub Port Endpoint 6                                      */
  __IO uint8_t   RXFUNCADDR6;                       /*!< USB Receive Functional Address Endpoint 6                             */
  __I  uint8_t   RESERVED19[1];
  __IO uint8_t   RXHUBADDR6;                        /*!< USB Receive Hub Address Endpoint 6                                    */
  __IO uint8_t   RXHUBPORT6;                        /*!< USB Receive Hub Port Endpoint 6                                       */
  __IO uint8_t   TXFUNCADDR7;                       /*!< USB Transmit Functional Address Endpoint 7                            */
  __I  uint8_t   RESERVED20[1];
  __IO uint8_t   TXHUBADDR7;                        /*!< USB Transmit Hub Address Endpoint 7                                   */
  __IO uint8_t   TXHUBPORT7;                        /*!< USB Transmit Hub Port Endpoint 7                                      */
  __IO uint8_t   RXFUNCADDR7;                       /*!< USB Receive Functional Address Endpoint 7                             */
  __I  uint8_t   RESERVED21[1];
  __IO uint8_t   RXHUBADDR7;                        /*!< USB Receive Hub Address Endpoint 7                                    */
  __IO uint8_t   RXHUBPORT7;                        /*!< USB Receive Hub Port Endpoint 7                                       */
  __I  uint32_t  RESERVED22[16];
  __I  uint16_t  RESERVED23;
  
  union {
    __O  uint8_t   CSRL0_USB0_ALT;                  /*!< USB Control and Status Endpoint 0 Low                                 */
    __O  uint8_t   CSRL0;                           /*!< USB Control and Status Endpoint 0 Low                                 */
  };
  __O  uint8_t   CSRH0;                             /*!< USB Control and Status Endpoint 0 High                                */
  __I  uint16_t  RESERVED24[3];
  __IO uint8_t   COUNT0;                            /*!< USB Receive Byte Count Endpoint 0                                     */
  __I  uint8_t   RESERVED25[1];
  __IO uint8_t   TYPE0;                             /*!< USB Type Endpoint 0                                                   */
  __IO uint8_t   NAKLMT;                            /*!< USB NAK Limit                                                         */
  __I  uint32_t  RESERVED26;
  __IO uint16_t  TXMAXP1;                           /*!< USB Maximum Transmit Data Endpoint 1                                  */
  
  union {
    __IO uint8_t   TXCSRL1_USB0_ALT;                /*!< USB Transmit Control and Status Endpoint 1 Low                        */
    __IO uint8_t   TXCSRL1;                         /*!< USB Transmit Control and Status Endpoint 1 Low                        */
  };
  __IO uint8_t   TXCSRH1;                           /*!< USB Transmit Control and Status Endpoint 1 High                       */
  __IO uint16_t  RXMAXP1;                           /*!< USB Maximum Receive Data Endpoint 1                                   */
  
  union {
    __IO uint8_t   RXCSRL1_USB0_ALT;                /*!< USB Receive Control and Status Endpoint 1 Low                         */
    __IO uint8_t   RXCSRL1;                         /*!< USB Receive Control and Status Endpoint 1 Low                         */
  };
  
  union {
    __IO uint8_t   RXCSRH1_USB0_ALT;                /*!< USB Receive Control and Status Endpoint 1 High                        */
    __IO uint8_t   RXCSRH1;                         /*!< USB Receive Control and Status Endpoint 1 High                        */
  };
  __IO uint16_t  RXCOUNT1;                          /*!< USB Receive Byte Count Endpoint 1                                     */
  __IO uint8_t   TXTYPE1;                           /*!< USB Host Transmit Configure Type Endpoint 1                           */
  
  union {
    __IO uint8_t   TXINTERVAL1_USB0_ALT;            /*!< USB Host Transmit Interval Endpoint 1                                 */
    __IO uint8_t   TXINTERVAL1;                     /*!< USB Host Transmit Interval Endpoint 1                                 */
  };
  __IO uint8_t   RXTYPE1;                           /*!< USB Host Configure Receive Type Endpoint 1                            */
  
  union {
    __IO uint8_t   RXINTERVAL1_USB0_ALT;            /*!< USB Host Receive Polling Interval Endpoint 1                          */
    __IO uint8_t   RXINTERVAL1;                     /*!< USB Host Receive Polling Interval Endpoint 1                          */
  };
  __I  uint16_t  RESERVED27;
  __IO uint16_t  TXMAXP2;                           /*!< USB Maximum Transmit Data Endpoint 2                                  */
  
  union {
    __IO uint8_t   TXCSRL2_USB0_ALT;                /*!< USB Transmit Control and Status Endpoint 2 Low                        */
    __IO uint8_t   TXCSRL2;                         /*!< USB Transmit Control and Status Endpoint 2 Low                        */
  };
  __IO uint8_t   TXCSRH2;                           /*!< USB Transmit Control and Status Endpoint 2 High                       */
  __IO uint16_t  RXMAXP2;                           /*!< USB Maximum Receive Data Endpoint 2                                   */
  
  union {
    __IO uint8_t   RXCSRL2_USB0_ALT;                /*!< USB Receive Control and Status Endpoint 2 Low                         */
    __IO uint8_t   RXCSRL2;                         /*!< USB Receive Control and Status Endpoint 2 Low                         */
  };
  
  union {
    __IO uint8_t   RXCSRH2_USB0_ALT;                /*!< USB Receive Control and Status Endpoint 2 High                        */
    __IO uint8_t   RXCSRH2;                         /*!< USB Receive Control and Status Endpoint 2 High                        */
  };
  __IO uint16_t  RXCOUNT2;                          /*!< USB Receive Byte Count Endpoint 2                                     */
  __IO uint8_t   TXTYPE2;                           /*!< USB Host Transmit Configure Type Endpoint 2                           */
  
  union {
    __IO uint8_t   TXINTERVAL2_USB0_ALT;            /*!< USB Host Transmit Interval Endpoint 2                                 */
    __IO uint8_t   TXINTERVAL2;                     /*!< USB Host Transmit Interval Endpoint 2                                 */
  };
  __IO uint8_t   RXTYPE2;                           /*!< USB Host Configure Receive Type Endpoint 2                            */
  
  union {
    __IO uint8_t   RXINTERVAL2_USB0_ALT;            /*!< USB Host Receive Polling Interval Endpoint 2                          */
    __IO uint8_t   RXINTERVAL2;                     /*!< USB Host Receive Polling Interval Endpoint 2                          */
  };
  __I  uint16_t  RESERVED28;
  __IO uint16_t  TXMAXP3;                           /*!< USB Maximum Transmit Data Endpoint 3                                  */
  
  union {
    __IO uint8_t   TXCSRL3_USB0_ALT;                /*!< USB Transmit Control and Status Endpoint 3 Low                        */
    __IO uint8_t   TXCSRL3;                         /*!< USB Transmit Control and Status Endpoint 3 Low                        */
  };
  __IO uint8_t   TXCSRH3;                           /*!< USB Transmit Control and Status Endpoint 3 High                       */
  __IO uint16_t  RXMAXP3;                           /*!< USB Maximum Receive Data Endpoint 3                                   */
  
  union {
    __IO uint8_t   RXCSRL3_USB0_ALT;                /*!< USB Receive Control and Status Endpoint 3 Low                         */
    __IO uint8_t   RXCSRL3;                         /*!< USB Receive Control and Status Endpoint 3 Low                         */
  };
  
  union {
    __IO uint8_t   RXCSRH3_USB0_ALT;                /*!< USB Receive Control and Status Endpoint 3 High                        */
    __IO uint8_t   RXCSRH3;                         /*!< USB Receive Control and Status Endpoint 3 High                        */
  };
  __IO uint16_t  RXCOUNT3;                          /*!< USB Receive Byte Count Endpoint 3                                     */
  __IO uint8_t   TXTYPE3;                           /*!< USB Host Transmit Configure Type Endpoint 3                           */
  
  union {
    __IO uint8_t   TXINTERVAL3_USB0_ALT;            /*!< USB Host Transmit Interval Endpoint 3                                 */
    __IO uint8_t   TXINTERVAL3;                     /*!< USB Host Transmit Interval Endpoint 3                                 */
  };
  __IO uint8_t   RXTYPE3;                           /*!< USB Host Configure Receive Type Endpoint 3                            */
  
  union {
    __IO uint8_t   RXINTERVAL3_USB0_ALT;            /*!< USB Host Receive Polling Interval Endpoint 3                          */
    __IO uint8_t   RXINTERVAL3;                     /*!< USB Host Receive Polling Interval Endpoint 3                          */
  };
  __I  uint16_t  RESERVED29;
  __IO uint16_t  TXMAXP4;                           /*!< USB Maximum Transmit Data Endpoint 4                                  */
  
  union {
    __IO uint8_t   TXCSRL4_USB0_ALT;                /*!< USB Transmit Control and Status Endpoint 4 Low                        */
    __IO uint8_t   TXCSRL4;                         /*!< USB Transmit Control and Status Endpoint 4 Low                        */
  };
  __IO uint8_t   TXCSRH4;                           /*!< USB Transmit Control and Status Endpoint 4 High                       */
  __IO uint16_t  RXMAXP4;                           /*!< USB Maximum Receive Data Endpoint 4                                   */
  
  union {
    __IO uint8_t   RXCSRL4_USB0_ALT;                /*!< USB Receive Control and Status Endpoint 4 Low                         */
    __IO uint8_t   RXCSRL4;                         /*!< USB Receive Control and Status Endpoint 4 Low                         */
  };
  
  union {
    __IO uint8_t   RXCSRH4_USB0_ALT;                /*!< USB Receive Control and Status Endpoint 4 High                        */
    __IO uint8_t   RXCSRH4;                         /*!< USB Receive Control and Status Endpoint 4 High                        */
  };
  __IO uint16_t  RXCOUNT4;                          /*!< USB Receive Byte Count Endpoint 4                                     */
  __IO uint8_t   TXTYPE4;                           /*!< USB Host Transmit Configure Type Endpoint 4                           */
  
  union {
    __IO uint8_t   TXINTERVAL4_USB0_ALT;            /*!< USB Host Transmit Interval Endpoint 4                                 */
    __IO uint8_t   TXINTERVAL4;                     /*!< USB Host Transmit Interval Endpoint 4                                 */
  };
  __IO uint8_t   RXTYPE4;                           /*!< USB Host Configure Receive Type Endpoint 4                            */
  
  union {
    __IO uint8_t   RXINTERVAL4_USB0_ALT;            /*!< USB Host Receive Polling Interval Endpoint 4                          */
    __IO uint8_t   RXINTERVAL4;                     /*!< USB Host Receive Polling Interval Endpoint 4                          */
  };
  __I  uint16_t  RESERVED30;
  __IO uint16_t  TXMAXP5;                           /*!< USB Maximum Transmit Data Endpoint 5                                  */
  
  union {
    __IO uint8_t   TXCSRL5_USB0_ALT;                /*!< USB Transmit Control and Status Endpoint 5 Low                        */
    __IO uint8_t   TXCSRL5;                         /*!< USB Transmit Control and Status Endpoint 5 Low                        */
  };
  __IO uint8_t   TXCSRH5;                           /*!< USB Transmit Control and Status Endpoint 5 High                       */
  __IO uint16_t  RXMAXP5;                           /*!< USB Maximum Receive Data Endpoint 5                                   */
  
  union {
    __IO uint8_t   RXCSRL5_USB0_ALT;                /*!< USB Receive Control and Status Endpoint 5 Low                         */
    __IO uint8_t   RXCSRL5;                         /*!< USB Receive Control and Status Endpoint 5 Low                         */
  };
  
  union {
    __IO uint8_t   RXCSRH5_USB0_ALT;                /*!< USB Receive Control and Status Endpoint 5 High                        */
    __IO uint8_t   RXCSRH5;                         /*!< USB Receive Control and Status Endpoint 5 High                        */
  };
  __IO uint16_t  RXCOUNT5;                          /*!< USB Receive Byte Count Endpoint 5                                     */
  __IO uint8_t   TXTYPE5;                           /*!< USB Host Transmit Configure Type Endpoint 5                           */
  
  union {
    __IO uint8_t   TXINTERVAL5_USB0_ALT;            /*!< USB Host Transmit Interval Endpoint 5                                 */
    __IO uint8_t   TXINTERVAL5;                     /*!< USB Host Transmit Interval Endpoint 5                                 */
  };
  __IO uint8_t   RXTYPE5;                           /*!< USB Host Configure Receive Type Endpoint 5                            */
  
  union {
    __IO uint8_t   RXINTERVAL5_USB0_ALT;            /*!< USB Host Receive Polling Interval Endpoint 5                          */
    __IO uint8_t   RXINTERVAL5;                     /*!< USB Host Receive Polling Interval Endpoint 5                          */
  };
  __I  uint16_t  RESERVED31;
  __IO uint16_t  TXMAXP6;                           /*!< USB Maximum Transmit Data Endpoint 6                                  */
  
  union {
    __IO uint8_t   TXCSRL6_USB0_ALT;                /*!< USB Transmit Control and Status Endpoint 6 Low                        */
    __IO uint8_t   TXCSRL6;                         /*!< USB Transmit Control and Status Endpoint 6 Low                        */
  };
  __IO uint8_t   TXCSRH6;                           /*!< USB Transmit Control and Status Endpoint 6 High                       */
  __IO uint16_t  RXMAXP6;                           /*!< USB Maximum Receive Data Endpoint 6                                   */
  
  union {
    __IO uint8_t   RXCSRL6_USB0_ALT;                /*!< USB Receive Control and Status Endpoint 6 Low                         */
    __IO uint8_t   RXCSRL6;                         /*!< USB Receive Control and Status Endpoint 6 Low                         */
  };
  
  union {
    __IO uint8_t   RXCSRH6_USB0_ALT;                /*!< USB Receive Control and Status Endpoint 6 High                        */
    __IO uint8_t   RXCSRH6;                         /*!< USB Receive Control and Status Endpoint 6 High                        */
  };
  __IO uint16_t  RXCOUNT6;                          /*!< USB Receive Byte Count Endpoint 6                                     */
  __IO uint8_t   TXTYPE6;                           /*!< USB Host Transmit Configure Type Endpoint 6                           */
  
  union {
    __IO uint8_t   TXINTERVAL6_USB0_ALT;            /*!< USB Host Transmit Interval Endpoint 6                                 */
    __IO uint8_t   TXINTERVAL6;                     /*!< USB Host Transmit Interval Endpoint 6                                 */
  };
  __IO uint8_t   RXTYPE6;                           /*!< USB Host Configure Receive Type Endpoint 6                            */
  
  union {
    __IO uint8_t   RXINTERVAL6_USB0_ALT;            /*!< USB Host Receive Polling Interval Endpoint 6                          */
    __IO uint8_t   RXINTERVAL6;                     /*!< USB Host Receive Polling Interval Endpoint 6                          */
  };
  __I  uint16_t  RESERVED32;
  __IO uint16_t  TXMAXP7;                           /*!< USB Maximum Transmit Data Endpoint 7                                  */
  
  union {
    __IO uint8_t   TXCSRL7_USB0_ALT;                /*!< USB Transmit Control and Status Endpoint 7 Low                        */
    __IO uint8_t   TXCSRL7;                         /*!< USB Transmit Control and Status Endpoint 7 Low                        */
  };
  __IO uint8_t   TXCSRH7;                           /*!< USB Transmit Control and Status Endpoint 7 High                       */
  __IO uint16_t  RXMAXP7;                           /*!< USB Maximum Receive Data Endpoint 7                                   */
  
  union {
    __IO uint8_t   RXCSRL7_USB0_ALT;                /*!< USB Receive Control and Status Endpoint 7 Low                         */
    __IO uint8_t   RXCSRL7;                         /*!< USB Receive Control and Status Endpoint 7 Low                         */
  };
  
  union {
    __IO uint8_t   RXCSRH7_USB0_ALT;                /*!< USB Receive Control and Status Endpoint 7 High                        */
    __IO uint8_t   RXCSRH7;                         /*!< USB Receive Control and Status Endpoint 7 High                        */
  };
  __IO uint16_t  RXCOUNT7;                          /*!< USB Receive Byte Count Endpoint 7                                     */
  __IO uint8_t   TXTYPE7;                           /*!< USB Host Transmit Configure Type Endpoint 7                           */
  
  union {
    __IO uint8_t   TXINTERVAL7_USB0_ALT;            /*!< USB Host Transmit Interval Endpoint 7                                 */
    __IO uint8_t   TXINTERVAL7;                     /*!< USB Host Transmit Interval Endpoint 7                                 */
  };
  __IO uint8_t   RXTYPE7;                           /*!< USB Host Configure Receive Type Endpoint 7                            */
  
  union {
    __IO uint8_t   RXINTERVAL7_USB0_ALT;            /*!< USB Host Receive Polling Interval Endpoint 7                          */
    __IO uint8_t   RXINTERVAL7;                     /*!< USB Host Receive Polling Interval Endpoint 7                          */
  };
  __I  uint16_t  RESERVED33[65];
  __IO uint8_t   DMAINTR;                           /*!< USB DMA Interrupt                                                     */
  __I  uint8_t   RESERVED34[3];
  __IO uint16_t  DMACTL0;                           /*!< USB DMA Control 0                                                     */
  __I  uint16_t  RESERVED35;
  __IO uint32_t  DMAADDR0;                          /*!< USB DMA Address 0                                                     */
  __IO uint32_t  DMACOUNT0;                         /*!< USB DMA Count 0                                                       */
  __I  uint32_t  RESERVED36;
  __IO uint16_t  DMACTL1;                           /*!< USB DMA Control 1                                                     */
  __I  uint16_t  RESERVED37;
  __IO uint32_t  DMAADDR1;                          /*!< USB DMA Address 1                                                     */
  __IO uint32_t  DMACOUNT1;                         /*!< USB DMA Count 1                                                       */
  __I  uint32_t  RESERVED38;
  __IO uint16_t  DMACTL2;                           /*!< USB DMA Control 2                                                     */
  __I  uint16_t  RESERVED39;
  __IO uint32_t  DMAADDR2;                          /*!< USB DMA Address 2                                                     */
  __IO uint32_t  DMACOUNT2;                         /*!< USB DMA Count 2                                                       */
  __I  uint32_t  RESERVED40;
  __IO uint16_t  DMACTL3;                           /*!< USB DMA Control 3                                                     */
  __I  uint16_t  RESERVED41;
  __IO uint32_t  DMAADDR3;                          /*!< USB DMA Address 3                                                     */
  __IO uint32_t  DMACOUNT3;                         /*!< USB DMA Count 3                                                       */
  __I  uint32_t  RESERVED42;
  __IO uint16_t  DMACTL4;                           /*!< USB DMA Control 4                                                     */
  __I  uint16_t  RESERVED43;
  __IO uint32_t  DMAADDR4;                          /*!< USB DMA Address 4                                                     */
  __IO uint32_t  DMACOUNT4;                         /*!< USB DMA Count 4                                                       */
  __I  uint32_t  RESERVED44;
  __IO uint16_t  DMACTL5;                           /*!< USB DMA Control 5                                                     */
  __I  uint16_t  RESERVED45;
  __IO uint32_t  DMAADDR5;                          /*!< USB DMA Address 5                                                     */
  __IO uint32_t  DMACOUNT5;                         /*!< USB DMA Count 5                                                       */
  __I  uint32_t  RESERVED46;
  __IO uint16_t  DMACTL6;                           /*!< USB DMA Control 6                                                     */
  __I  uint16_t  RESERVED47;
  __IO uint32_t  DMAADDR6;                          /*!< USB DMA Address 6                                                     */
  __IO uint32_t  DMACOUNT6;                         /*!< USB DMA Count 6                                                       */
  __I  uint32_t  RESERVED48;
  __IO uint16_t  DMACTL7;                           /*!< USB DMA Control 7                                                     */
  __I  uint16_t  RESERVED49;
  __IO uint32_t  DMAADDR7;                          /*!< USB DMA Address 7                                                     */
  __IO uint32_t  DMACOUNT7;                         /*!< USB DMA Count 7                                                       */
  __I  uint32_t  RESERVED50[33];
  __IO uint16_t  RQPKTCOUNT1;                       /*!< USB Request Packet Count in Block Transfer Endpoint 1                 */
  __I  uint16_t  RESERVED51;
  __IO uint16_t  RQPKTCOUNT2;                       /*!< USB Request Packet Count in Block Transfer Endpoint 2                 */
  __I  uint16_t  RESERVED52;
  __IO uint16_t  RQPKTCOUNT3;                       /*!< USB Request Packet Count in Block Transfer Endpoint 3                 */
  __I  uint16_t  RESERVED53;
  __IO uint16_t  RQPKTCOUNT4;                       /*!< USB Request Packet Count in Block Transfer Endpoint 4                 */
  __I  uint16_t  RESERVED54;
  __IO uint16_t  RQPKTCOUNT5;                       /*!< USB Request Packet Count in Block Transfer Endpoint 5                 */
  __I  uint16_t  RESERVED55;
  __IO uint16_t  RQPKTCOUNT6;                       /*!< USB Request Packet Count in Block Transfer Endpoint 6                 */
  __I  uint16_t  RESERVED56;
  __IO uint16_t  RQPKTCOUNT7;                       /*!< USB Request Packet Count in Block Transfer Endpoint 7                 */
  __I  uint16_t  RESERVED57[17];
  __IO uint16_t  RXDPKTBUFDIS;                      /*!< USB Receive Double Packet Buffer Disable                              */
  __IO uint16_t  TXDPKTBUFDIS;                      /*!< USB Transmit Double Packet Buffer Disable                             */
  __IO uint16_t  CTO;                               /*!< USB Chirp Timeout                                                     */
  __IO uint16_t  HHSRTN;                            /*!< USB High Speed to UTM Operating Delay                                 */
  __IO uint16_t  HSBT;                              /*!< USB High Speed Time-out Adder                                         */
  __I  uint16_t  RESERVED58[11];
  __IO uint16_t  LPMATTR;                           /*!< USB LPM Attributes                                                    */
  __IO uint8_t   LPMCNTRL;                          /*!< USB LPM Control                                                       */
  __IO uint8_t   LPMIM;                             /*!< USB LPM Interrupt Mask                                                */
  __IO uint8_t   LPMRIS;                            /*!< USB LPM Raw Interrupt Status                                          */
  __IO uint8_t   LPMFADDR;                          /*!< USB LPM Function Address                                              */
  __I  uint16_t  RESERVED59[77];
  __IO uint32_t  EPC;                               /*!< USB External Power Control                                            */
  __IO uint32_t  EPCRIS;                            /*!< USB External Power Control Raw Interrupt Status                       */
  __IO uint32_t  EPCIM;                             /*!< USB External Power Control Interrupt Mask                             */
  __IO uint32_t  EPCISC;                            /*!< USB External Power Control Interrupt Status and Clear                 */
  __IO uint32_t  DRRIS;                             /*!< USB Device RESUME Raw Interrupt Status                                */
  __IO uint32_t  DRIM;                              /*!< USB Device RESUME Interrupt Mask                                      */
  __O  uint32_t  DRISC;                             /*!< USB Device RESUME Interrupt Status and Clear                          */
  __IO uint32_t  GPCS;                              /*!< USB General-Purpose Control and Status                                */
  __I  uint32_t  RESERVED60[4];
  __IO uint32_t  VDC;                               /*!< USB VBUS Droop Control                                                */
  __IO uint32_t  VDCRIS;                            /*!< USB VBUS Droop Control Raw Interrupt Status                           */
  __IO uint32_t  VDCIM;                             /*!< USB VBUS Droop Control Interrupt Mask                                 */
  __IO uint32_t  VDCISC;                            /*!< USB VBUS Droop Control Interrupt Status and Clear                     */
  __I  uint32_t  RESERVED61[736];
  __IO uint32_t  PP;                                /*!< USB Peripheral Properties                                             */
  __IO uint32_t  PC;                                /*!< USB Peripheral Configuration                                          */
  __IO uint32_t  CC;                                /*!< USB Clock Configuration                                               */
} USB0_Type;


/* ================================================================================ */
/* ================                    GPIOA_AHB                   ================ */
/* ================================================================================ */


/**
  * @brief Register map for GPIOA_AHB peripheral (GPIOA_AHB)
  */

typedef struct {                                    /*!< GPIOA_AHB Structure                                                   */
  __I  uint32_t  RESERVED0[255];
  __IO uint32_t  DATA;                              /*!< GPIO Data                                                             */
  __IO uint32_t  DIR;                               /*!< GPIO Direction                                                        */
  __IO uint32_t  IS;                                /*!< GPIO Interrupt Sense                                                  */
  __IO uint32_t  IBE;                               /*!< GPIO Interrupt Both Edges                                             */
  __IO uint32_t  IEV;                               /*!< GPIO Interrupt Event                                                  */
  __IO uint32_t  IM;                                /*!< GPIO Interrupt Mask                                                   */
  __IO uint32_t  RIS;                               /*!< GPIO Raw Interrupt Status                                             */
  __IO uint32_t  MIS;                               /*!< GPIO Masked Interrupt Status                                          */
  __O  uint32_t  ICR;                               /*!< GPIO Interrupt Clear                                                  */
  __IO uint32_t  AFSEL;                             /*!< GPIO Alternate Function Select                                        */
  __I  uint32_t  RESERVED1[55];
  __IO uint32_t  DR2R;                              /*!< GPIO 2-mA Drive Select                                                */
  __IO uint32_t  DR4R;                              /*!< GPIO 4-mA Drive Select                                                */
  __IO uint32_t  DR8R;                              /*!< GPIO 8-mA Drive Select                                                */
  __IO uint32_t  ODR;                               /*!< GPIO Open Drain Select                                                */
  __IO uint32_t  PUR;                               /*!< GPIO Pull-Up Select                                                   */
  __IO uint32_t  PDR;                               /*!< GPIO Pull-Down Select                                                 */
  __IO uint32_t  SLR;                               /*!< GPIO Slew Rate Control Select                                         */
  __IO uint32_t  DEN;                               /*!< GPIO Digital Enable                                                   */
  __IO uint32_t  LOCK;                              /*!< GPIO Lock                                                             */
  __I  uint32_t  CR;                                /*!< GPIO Commit                                                           */
  __IO uint32_t  AMSEL;                             /*!< GPIO Analog Mode Select                                               */
  __IO uint32_t  PCTL;                              /*!< GPIO Port Control                                                     */
  __IO uint32_t  ADCCTL;                            /*!< GPIO ADC Control                                                      */
  __IO uint32_t  DMACTL;                            /*!< GPIO DMA Control                                                      */
  __IO uint32_t  SI;                                /*!< GPIO Select Interrupt                                                 */
  __IO uint32_t  DR12R;                             /*!< GPIO 12-mA Drive Select                                               */
  __IO uint32_t  WAKEPEN;                           /*!< GPIO Wake Pin Enable                                                  */
  __IO uint32_t  WAKELVL;                           /*!< GPIO Wake Level                                                       */
  __IO uint32_t  WAKESTAT;                          /*!< GPIO Wake Status                                                      */
  __I  uint32_t  RESERVED2[669];
  __IO uint32_t  PP;                                /*!< GPIO Peripheral Property                                              */
  __IO uint32_t  PC;                                /*!< GPIO Peripheral Configuration                                         */
} GPIOA_AHB_Type;


/* ================================================================================ */
/* ================                      LPCB0                     ================ */
/* ================================================================================ */


/**
  * @brief Register map for LPCB0 peripheral (LPCB0)
  */

typedef struct {                                    /*!< LPCB0 Structure                                                       */
  __IO uint32_t  CTL;                               /*!< LPCB Control                                                          */
  __IO uint32_t  STS;                               /*!< LPCB Status                                                           */
  __IO uint32_t  IRQCTL;                            /*!< LPCB IRQ Control                                                      */
  __IO uint32_t  IRQSTACT;                          /*!< LPCB IRQ Status and Active State                                      */
  __IO uint32_t  CH0CTL;                            /*!< LPCB Channel 0 Control                                                */
  __IO uint32_t  CH0ST;                             /*!< LPCB Channel 0 Status                                                 */
  __IO uint32_t  CH0ADR;                            /*!< LPCB Channel 0 Address                                                */
  __IO uint32_t  CH0EXT;                            /*!< LPCB Channel 0 Extension                                              */
  __IO uint32_t  CH1CTL;                            /*!< LPCB Channel 1 Control                                                */
  __IO uint32_t  CH1ST;                             /*!< LPCB Channel 1 Status                                                 */
  __IO uint32_t  CH1ADR;                            /*!< LPCB Channel 1 Address                                                */
  __IO uint32_t  CH1EXT;                            /*!< LPCB Channel 1 Extension                                              */
  __IO uint32_t  CH2CTL;                            /*!< LPCB Channel 2 Control                                                */
  __IO uint32_t  CH2ST;                             /*!< LPCB Channel 2 Status                                                 */
  __IO uint32_t  CH2ADR;                            /*!< LPCB Channel 2 Address                                                */
  __IO uint32_t  CH2EXT;                            /*!< LPCB Channel 2 Extension                                              */
  __IO uint32_t  CH3CTL;                            /*!< LPCB Channel 3 Control                                                */
  __IO uint32_t  CH3ST;                             /*!< LPCB Channel 3 Status                                                 */
  __IO uint32_t  CH3ADR;                            /*!< LPCB Channel 3 Address                                                */
  __IO uint32_t  CH3EXT;                            /*!< LPCB Channel 3 Extension                                              */
  __IO uint32_t  CH4CTL;                            /*!< LPCB Channel 4 Control                                                */
  __IO uint32_t  CH4ST;                             /*!< LPCB Channel 4 Status                                                 */
  __IO uint32_t  CH4ADR;                            /*!< LPCB Channel 4 Address                                                */
  __IO uint32_t  CH4EXT;                            /*!< LPCB Channel 4 Extension                                              */
  __IO uint32_t  CH5CTL;                            /*!< LPCB Channel 5 Control                                                */
  __IO uint32_t  CH5ST;                             /*!< LPCB Channel 5 Status                                                 */
  __IO uint32_t  CH5ADR;                            /*!< LPCB Channel 5 Address                                                */
  __IO uint32_t  CH5EXT;                            /*!< LPCB Channel 5 Extension                                              */
  __IO uint32_t  CH6CTL;                            /*!< LPCB Channel 6 Control                                                */
  __IO uint32_t  CH6ST;                             /*!< LPCB Channel 6 Status                                                 */
  __IO uint32_t  CH6ADR;                            /*!< LPCB Channel 6 Address                                                */
  __IO uint32_t  CH6EXT;                            /*!< LPCB Channel 6 Extension                                              */
  __IO uint32_t  CH7CTL;                            /*!< LPCB Channel 7 Control                                                */
  __IO uint32_t  CH7ST;                             /*!< LPCB Channel 7 Status                                                 */
  __IO uint32_t  CH7ADR;                            /*!< LPCB Channel 7 Address                                                */
  __IO uint32_t  CH7EXT;                            /*!< LPCB Channel 7 Extension                                              */
  __I  uint32_t  RESERVED0[4];
  __IO uint32_t  STSADDR;                           /*!< LPCB Status Block Address                                             */
  __I  uint32_t  RESERVED1[3];
  __IO uint32_t  RTCCTL;                            /*!< LPCB RTC Control                                                      */
  __IO uint32_t  RTCADR;                            /*!< LPCB RTC Address                                                      */
  __I  uint32_t  RESERVED2[2];
  __IO uint32_t  RTCCALH;                           /*!< LPCB RTC Calendar High                                                */
  __IO uint32_t  RTCCALL;                           /*!< LPCB RTC Calendar High                                                */
  __IO uint32_t  RTCALRM;                           /*!< LPCB RTC Alarm                                                        */
  __I  uint32_t  RESERVED3;
  __IO uint32_t  RTCMOD0;                           /*!< LPCB RTC Modify 0 Register                                            */
  __IO uint32_t  RTCMOD1;                           /*!< LPCB RTC Modify 1 Register                                            */
  __IO uint32_t  RTCMOD2;                           /*!< LPCB RTC Modify 2 Register                                            */
  __IO uint32_t  RTCMOD3;                           /*!< LPCB RTC Modify 3 Register                                            */
  __I  uint32_t  RESERVED4[8];
  __IO uint32_t  IM;                                /*!< LPCB Interrupt Mask                                                   */
  __IO uint32_t  RIS;                               /*!< LPCB Raw Interrupt Status                                             */
  __IO uint32_t  MIS;                               /*!< LPCB Masked Interrupt Status                                          */
  __O  uint32_t  IC;                                /*!< LPCB Interrupt Clear                                                  */
  __IO uint32_t  IM2;                               /*!< LPCB Interrupt Mask 2                                                 */
  __IO uint32_t  RIS2;                              /*!< LPCB Raw Interrupt Status 2                                           */
  __IO uint32_t  MIS2;                              /*!< LPCB Masked Interrupt Status 2                                        */
  __IO uint32_t  IC2;                               /*!< LPCB Interrupt Clear 2                                                */
  __IO uint32_t  DMACX;                             /*!< LPCB DMA and COMx Control                                             */
  __IO uint32_t  CXADR;                             /*!< LPCB COMx Address                                                     */
  __IO uint32_t  COMXY;                             /*!< LPCB COMx and COMy Extended Control                                   */
  __IO uint32_t  CCYADR;                            /*!< LPCB COMy Address                                                     */
  __IO uint32_t  BASE;                              /*!< LPCB Base Address                                                     */
  __I  uint32_t  RESERVED5[3];
  __IO uint32_t  COMXYSTS;                          /*!< LPCB COMx and COMy Status                                             */
  __IO uint32_t  COMXICPT;                          /*!< LPCB COMx Intercept                                                   */
  __IO uint32_t  COMYICPT;                          /*!< LPCB COMy Intercept                                                   */
  __IO uint32_t  COMBAUD;                           /*!< LPCB COM Baud Override                                                */
  __I  uint32_t  RESERVED6[172];
  __IO uint32_t  POOL;                              /*!< LPCB Register Pool                                                    */
  __I  uint32_t  RESERVED7[255];
  __IO uint32_t  RTCDAT;                            /*!< LPCB RTC Data                                                         */
  __I  uint32_t  RESERVED8[495];
  __IO uint32_t  PP;                                /*!< LPCB Peripheral Properties                                            */
} LPCB0_Type;


/* ================================================================================ */
/* ================                      FAN0                      ================ */
/* ================================================================================ */


/**
  * @brief Register map for FAN0 peripheral (FAN0)
  */

typedef struct {                                    /*!< FAN0 Structure                                                        */
  __IO uint32_t  STS;                               /*!< FAN Status                                                            */
  __IO uint32_t  CTL;                               /*!< FAN Control                                                           */
  __I  uint32_t  RESERVED0[2];
  __IO uint32_t  CH0;                               /*!< FAN Channel 0 Setup                                                   */
  __IO uint32_t  CMD0;                              /*!< FAN Channel 0 Command                                                 */
  __IO uint32_t  CST0;                              /*!< FAN Channel 0 Status                                                  */
  __I  uint32_t  RESERVED1;
  __IO uint32_t  CH1;                               /*!< FAN Channel 1 Setup                                                   */
  __IO uint32_t  CMD1;                              /*!< FAN Channel 1 Command                                                 */
  __IO uint32_t  CST1;                              /*!< FAN Channel 1 Status                                                  */
  __I  uint32_t  RESERVED2;
  __IO uint32_t  CH2;                               /*!< FAN Channel 2 Setup                                                   */
  __IO uint32_t  CMD2;                              /*!< FAN Channel 2 Command                                                 */
  __IO uint32_t  CST2;                              /*!< FAN Channel 2 Status                                                  */
  __I  uint32_t  RESERVED3;
  __IO uint32_t  CH3;                               /*!< FAN Channel 3 Setup                                                   */
  __IO uint32_t  CMD3;                              /*!< FAN Channel 3 Command                                                 */
  __IO uint32_t  CST3;                              /*!< FAN Channel 3 Status                                                  */
  __I  uint32_t  RESERVED4;
  __IO uint32_t  CH4;                               /*!< FAN Channel 4 Setup                                                   */
  __IO uint32_t  CMD4;                              /*!< FAN Channel 4 Command                                                 */
  __IO uint32_t  CST4;                              /*!< FAN Channel 4 Status                                                  */
  __I  uint32_t  RESERVED5;
  __IO uint32_t  CH5;                               /*!< FAN Channel 5 Setup                                                   */
  __IO uint32_t  CMD5;                              /*!< FAN Channel 5 Command                                                 */
  __IO uint32_t  CST5;                              /*!< FAN Channel 5 Status                                                  */
  __I  uint32_t  RESERVED6;
  __IO uint32_t  CH6;                               /*!< FAN Channel 6 Setup                                                   */
  __IO uint32_t  CMD6;                              /*!< FAN Channel 6 Command                                                 */
  __IO uint32_t  CST6;                              /*!< FAN Channel 6 Status                                                  */
  __I  uint32_t  RESERVED7;
  __IO uint32_t  CH7;                               /*!< FAN Channel 7 Setup                                                   */
  __IO uint32_t  CMD7;                              /*!< FAN Channel 7 Command                                                 */
  __IO uint32_t  CST7;                              /*!< FAN Channel 7 Status                                                  */
  __I  uint32_t  RESERVED8;
  __IO uint32_t  IM;                                /*!< FAN Interrupt Mask                                                    */
  __IO uint32_t  RIS;                               /*!< FAN Raw Interrupt Status                                              */
  __IO uint32_t  MIS;                               /*!< FAN Masked Interrupt Status                                           */
  __IO uint32_t  IC;                                /*!< FAN Interrupt Clear                                                   */
  __I  uint32_t  RESERVED9[968];
  __IO uint32_t  PP;                                /*!< FAN Peripheral Properties                                             */
} FAN0_Type;


/* ================================================================================ */
/* ================                     EEPROM                     ================ */
/* ================================================================================ */


/**
  * @brief Register map for EEPROM peripheral (EEPROM)
  */

typedef struct {                                    /*!< EEPROM Structure                                                      */
  __IO uint32_t  EESIZE;                            /*!< EEPROM Size Information                                               */
  __IO uint32_t  EEBLOCK;                           /*!< EEPROM Current Block                                                  */
  __IO uint32_t  EEOFFSET;                          /*!< EEPROM Current Offset                                                 */
  __I  uint32_t  RESERVED0;
  __IO uint32_t  EERDWR;                            /*!< EEPROM Read-Write                                                     */
  __IO uint32_t  EERDWRINC;                         /*!< EEPROM Read-Write with Increment                                      */
  __IO uint32_t  EEDONE;                            /*!< EEPROM Done Status                                                    */
  __IO uint32_t  EESUPP;                            /*!< EEPROM Support Control and Status                                     */
  __IO uint32_t  EEUNLOCK;                          /*!< EEPROM Unlock                                                         */
  __I  uint32_t  RESERVED1[3];
  __IO uint32_t  EEPROT;                            /*!< EEPROM Protection                                                     */
  __IO uint32_t  EEPASS0;                           /*!< EEPROM Password                                                       */
  __IO uint32_t  EEPASS1;                           /*!< EEPROM Password                                                       */
  __IO uint32_t  EEPASS2;                           /*!< EEPROM Password                                                       */
  __IO uint32_t  EEINT;                             /*!< EEPROM Interrupt                                                      */
  __I  uint32_t  RESERVED2[3];
  __IO uint32_t  EEHIDE0;                           /*!< EEPROM Block 0 Hide                                                   */
  __IO uint32_t  EEHIDE1;                           /*!< EEPROM Block Hide 1                                                   */
  __IO uint32_t  EEHIDE2;                           /*!< EEPROM Block Hide 2                                                   */
  __I  uint32_t  RESERVED3[9];
  __IO uint32_t  EEDBGME;                           /*!< EEPROM Debug Mass Erase                                               */
  __I  uint32_t  RESERVED4[975];
  __IO uint32_t  PP;                                /*!< EEPROM Peripheral Properties                                          */
} EEPROM_Type;


/* ================================================================================ */
/* ================                      PECI0                     ================ */
/* ================================================================================ */


/**
  * @brief Register map for PECI0 peripheral (PECI0)
  */

typedef struct {                                    /*!< PECI0 Structure                                                       */
  __IO uint32_t  CTL;                               /*!< PECI Control                                                          */
  __IO uint32_t  DIV;                               /*!< PECI Poll-Rate Divider                                                */
  __I  uint32_t  RESERVED0[2];
  __IO uint32_t  M0D0C;                             /*!< PECI Microprocessor 0 / Domain 0 Control                              */
  __IO uint32_t  M0D1C;                             /*!< PECI Microprocessor 0 / Domain 1 Control                              */
  __IO uint32_t  M1D0C;                             /*!< PECI Microprocessor 1 / Domain 0 Control                              */
  __IO uint32_t  M1D1C;                             /*!< PECI Microprocessor 1 / Domain 1 Control                              */
  __IO uint32_t  M0D0AVG;                           /*!< PECI Microprocessor 0 / Domain 0 Average                              */
  __IO uint32_t  M0D1AVG;                           /*!< PECI Microprocessor 0 / Domain 1 Average                              */
  __IO uint32_t  M1D0AVG;                           /*!< PECI Microprocessor 1 / Domain 0 Average                              */
  __IO uint32_t  M1D1AVG;                           /*!< PECI Microprocessor 1 / Domain 1 Average                              */
  __I  uint32_t  RESERVED1[4];
  __IO uint32_t  M0D0;                              /*!< PECI Microprocessor 0 / Domain 0 Value                                */
  __IO uint32_t  M0D1;                              /*!< PECI Microprocessor 0 / Domain 1 Value                                */
  __IO uint32_t  M1D0;                              /*!< PECI Microprocessor 1 / Domain 0 Value                                */
  __IO uint32_t  M1D1;                              /*!< PECI Microprocessor 1 / Domain 1 Value                                */
  __I  uint32_t  RESERVED2[12];
  __IO uint32_t  IM;                                /*!< PECI Interrupt Mask                                                   */
  __IO uint32_t  RIS;                               /*!< PECI Raw Interrupt Status                                             */
  __IO uint32_t  MIS;                               /*!< PECI Masked Interrupt Status                                          */
  __O  uint32_t  IC;                                /*!< PECI Interrupt Clear                                                  */
  __I  uint32_t  RESERVED3[28];
  __IO uint32_t  ACADDR;                            /*!< PECI Advanced Command Address                                         */
  __IO uint32_t  ACARG;                             /*!< PECI Advanced Command Argument                                        */
  __IO uint32_t  ACRDWR0;                           /*!< PECI Advanced Command Data 0                                          */
  __IO uint32_t  ACRDWR1;                           /*!< PECI Advanced Command Data 1                                          */
  __IO uint32_t  ACCMD;                             /*!< PECI Advanced Command                                                 */
  __IO uint32_t  ACCODE;                            /*!< PECI Advanced Command Completion Code                                 */
  __I  uint32_t  RESERVED4[59];
  __IO uint32_t  BAUD;                              /*!< PECI Current Baud Value                                               */
  __I  uint32_t  RESERVED5[878];
  __IO uint32_t  PP;                                /*!< PECI Peripheral Properties                                            */
} PECI0_Type;


/* ================================================================================ */
/* ================                    ONEWIRE0                    ================ */
/* ================================================================================ */


/**
  * @brief Register map for ONEWIRE0 peripheral (ONEWIRE0)
  */

typedef struct {                                    /*!< ONEWIRE0 Structure                                                    */
  __IO uint32_t  CS;                                /*!< 1-Wire Control and Status                                             */
  __IO uint32_t  TIM;                               /*!< 1-Wire Timing Override                                                */
  __IO uint32_t  DATW;                              /*!< 1-Wire Data Write                                                     */
  __IO uint32_t  DATR;                              /*!< One-Wire Data Read                                                    */
  __I  uint32_t  RESERVED0[60];
  __IO uint32_t  IM;                                /*!< 1-Wire Interrupt Mask                                                 */
  __IO uint32_t  RIS;                               /*!< 1-Wire Raw Interrupt Status                                           */
  __IO uint32_t  MIS;                               /*!< 1-Wire Masked Interrupt Status                                        */
  __IO uint32_t  ICR;                               /*!< 1-Wire Interrupt Clear                                                */
  __I  uint32_t  RESERVED1[4];
  __IO uint32_t  DMA;                               /*!< 1-Wire uDMA Control                                                   */
  __I  uint32_t  RESERVED2[935];
  __IO uint32_t  PP;                                /*!< 1-Wire Peripheral Properites                                          */
} ONEWIRE0_Type;


/* ================================================================================ */
/* ================                      HIM0                      ================ */
/* ================================================================================ */


/**
  * @brief Register map for HIM0 peripheral (HIM0)
  */

typedef struct {                                    /*!< HIM0 Structure                                                        */
  __IO uint32_t  KBCSTS;                            /*!< HIM KBC Status                                                        */
  __IO uint32_t  KBCCTL;                            /*!< HIM KBC Control                                                       */
  __I  uint32_t  RESERVED0[2];
  __IO uint32_t  KBCSI0;                            /*!< HIM KBC Scan-In 0                                                     */
  __IO uint32_t  KBCSI4;                            /*!< HIM KBC Scan-In 4                                                     */
  __IO uint32_t  KBCSI8;                            /*!< HIM KBC Scan-In 8                                                     */
  __IO uint32_t  KBCSI12;                           /*!< HIM KBC Scan-In 12                                                    */
  __IO uint32_t  KBCSI16;                           /*!< HIM KBC Scan-In 16                                                    */
  __I  uint32_t  RESERVED1[55];
  __IO uint32_t  PS2STS;                            /*!< HIM PS2 Status                                                        */
  __IO uint32_t  PS2CTL;                            /*!< PS2 Control                                                           */
  __I  uint32_t  RESERVED2[2];
  __IO uint32_t  PS2CMD0;                           /*!< HIM PS/2 0 Command                                                    */
  __IO uint32_t  PS2RDAT0;                          /*!< HIM PS/2 0 Receive Data                                               */
  __IO uint32_t  PS2CMD1;                           /*!< HIM PS/2 1 Command                                                    */
  __IO uint32_t  PS2RDAT1;                          /*!< HIM PS/2 1 Receive Data                                               */
  __IO uint32_t  PS2CMD2;                           /*!< HIM PS/2 2 Command                                                    */
  __IO uint32_t  PS2RDAT2;                          /*!< HIM PS/2 2 Receive Data                                               */
  __IO uint32_t  PS2CMD3;                           /*!< HIM PS/2 3 Command                                                    */
  __IO uint32_t  PS2RDAT3;                          /*!< HIM PS/2 3 Receive Data                                               */
  __I  uint32_t  RESERVED3[52];
  __IO uint32_t  LEDCTL0;                           /*!< LED 0 Control                                                         */
  __IO uint32_t  LEDCTL1;                           /*!< LED 1 Control                                                         */
  __IO uint32_t  LEDCTL2;                           /*!< LED 2 Control                                                         */
  __IO uint32_t  LEDCTL3;                           /*!< LED 3 Control                                                         */
  __I  uint32_t  RESERVED4[28];
  __IO uint32_t  LEDSQ0;                            /*!< LED 0 Sequence                                                        */
  __IO uint32_t  LEDSQ1;                            /*!< LED 1 Sequence                                                        */
  __IO uint32_t  LEDSQ2;                            /*!< LED 2 Sequence                                                        */
  __IO uint32_t  LEDSQ3;                            /*!< LED 3 Sequence                                                        */
  __IO uint32_t  LEDSQ4;                            /*!< LED 4 Sequence                                                        */
  __IO uint32_t  LEDSQ5;                            /*!< LED 5 Sequence                                                        */
  __IO uint32_t  LEDSQ6;                            /*!< LED 6 Sequence                                                        */
  __IO uint32_t  LEDSQ7;                            /*!< LED 7 Sequence                                                        */
  __IO uint32_t  LEDSQ8;                            /*!< LED 8 Sequence                                                        */
  __IO uint32_t  LEDSQ9;                            /*!< LED 9 Sequence                                                        */
  __IO uint32_t  LEDSQ10;                           /*!< LED 10 Sequence                                                       */
  __IO uint32_t  LEDSQ11;                           /*!< LED 11 Sequence                                                       */
  __IO uint32_t  LEDSQ12;                           /*!< LED 12 Sequence                                                       */
  __IO uint32_t  LEDSQ13;                           /*!< LED 13 Sequence                                                       */
  __IO uint32_t  LEDSQ14;                           /*!< LED 14 Sequence                                                       */
  __IO uint32_t  LEDSQ15;                           /*!< LED 15 Sequence                                                       */
  __I  uint32_t  RESERVED5[16];
  __IO uint32_t  CIRSTSCTL;                         /*!< HIM CIR Status and Control                                            */
  __IO uint32_t  CIRRMIMX;                          /*!< HIM CIR Min and Max Receive Count                                     */
  __IO uint32_t  CIRRCNT;                           /*!< HIM CIR Receive                                                       */
  __I  uint32_t  RESERVED6;
  
  union {
    __IO uint32_t  CIRTCNT_HIM0_ALT;                /*!< HIM CIR Transmit Counter                                              */
    __IO uint32_t  CIRTCNT;                         /*!< HIM CIR Transmit Counter                                              */
  };
  __I  uint32_t  RESERVED7[59];
  __IO uint32_t  SHREGCTL;                          /*!< HIM SHREG Control                                                     */
  __I  uint32_t  RESERVED8[255];
  __IO uint32_t  KIM;                               /*!< HIM KBC Interrupt Mask                                                */
  __IO uint32_t  KRIS;                              /*!< HIM KBC Raw Interrupt Status                                          */
  __IO uint32_t  KMIS;                              /*!< HIM KBC Masked Interrupt Status                                       */
  __IO uint32_t  KICR;                              /*!< HIM KBC Interrupt Clear                                               */
  __IO uint32_t  PIM;                               /*!< HIM PS/2 Interrupt Mask                                               */
  __IO uint32_t  PRIS;                              /*!< HIM PS/2 Raw Interrupt Status                                         */
  __IO uint32_t  PMIS;                              /*!< HIM PS/2 Masked Interrupt Status                                      */
  __IO uint32_t  PICR;                              /*!< HIM PS/2 Interrupt Clear                                              */
  __IO uint32_t  LIM;                               /*!< HIM LED Interrupt Mask                                                */
  __IO uint32_t  LRIS;                              /*!< HIM LED Raw Interrupt Status                                          */
  __IO uint32_t  LMIS;                              /*!< HIM LED Masked Interrupt Status                                       */
  __IO uint32_t  LICR;                              /*!< HIM LED Interrupt Clear                                               */
  __IO uint32_t  CIM;                               /*!< HIM CIR Interrupt Mask                                                */
  __IO uint32_t  CRIS;                              /*!< HIM CIR Raw Interrupt Status                                          */
  __IO uint32_t  CMIS;                              /*!< HIM CIR Masked Interrupt Status                                       */
  __IO uint32_t  CICR;                              /*!< HIM CIR Interrupt Clear                                               */
  __I  uint32_t  RESERVED9[480];
  __IO uint32_t  PP;                                /*!< HIM Peripheral Properties                                             */
} HIM0_Type;


/* ================================================================================ */
/* ================                      EPI0                      ================ */
/* ================================================================================ */


/**
  * @brief Register map for EPI0 peripheral (EPI0)
  */

typedef struct {                                    /*!< EPI0 Structure                                                        */
  __IO uint32_t  CFG;                               /*!< EPI Configuration                                                     */
  __IO uint32_t  BAUD;                              /*!< EPI Main Baud Rate                                                    */
  __IO uint32_t  BAUD2;                             /*!< EPI Main Baud Rate                                                    */
  __I  uint32_t  RESERVED0;
  
  union {
    __IO uint32_t  SDRAMCFG_EPI_ALTSD;              /*!< EPI SDRAM Configuration                                               */
    __IO uint32_t  HB8CFG_EPI_ALT8;                 /*!< EPI Host-Bus 8 Configuration                                          */
    __IO uint32_t  HB16CFG_EPI_ALT16;               /*!< EPI Host-Bus 16 Configuration                                         */
    __IO uint32_t  GPCFG;                           /*!< EPI General-Purpose Configuration                                     */
  };
  
  union {
    __IO uint32_t  HB16CFG2_EPI_ALT16;              /*!< EPI Host-Bus 16 Configuration 2                                       */
    __IO uint32_t  HB8CFG2_EPI_ALT8;                /*!< EPI Host-Bus 8 Configuration 2                                        */
  };
  __I  uint32_t  RESERVED1;
  __IO uint32_t  ADDRMAP;                           /*!< EPI Address Map                                                       */
  __IO uint32_t  RSIZE0;                            /*!< EPI Read Size 0                                                       */
  __IO uint32_t  RADDR0;                            /*!< EPI Read Address 0                                                    */
  __IO uint32_t  RPSTD0;                            /*!< EPI Non-Blocking Read Data 0                                          */
  __I  uint32_t  RESERVED2;
  __IO uint32_t  RSIZE1;                            /*!< EPI Read Size 1                                                       */
  __IO uint32_t  RADDR1;                            /*!< EPI Read Address 1                                                    */
  __IO uint32_t  RPSTD1;                            /*!< EPI Non-Blocking Read Data 1                                          */
  __I  uint32_t  RESERVED3[9];
  __IO uint32_t  STAT;                              /*!< EPI Status                                                            */
  __I  uint32_t  RESERVED4[2];
  __IO uint32_t  RFIFOCNT;                          /*!< EPI Read FIFO Count                                                   */
  __IO uint32_t  READFIFO0;                         /*!< EPI Read FIFO                                                         */
  __IO uint32_t  READFIFO1;                         /*!< EPI Read FIFO Alias 1                                                 */
  __IO uint32_t  READFIFO2;                         /*!< EPI Read FIFO Alias 2                                                 */
  __IO uint32_t  READFIFO3;                         /*!< EPI Read FIFO Alias 3                                                 */
  __IO uint32_t  READFIFO4;                         /*!< EPI Read FIFO Alias 4                                                 */
  __IO uint32_t  READFIFO5;                         /*!< EPI Read FIFO Alias 5                                                 */
  __IO uint32_t  READFIFO6;                         /*!< EPI Read FIFO Alias 6                                                 */
  __IO uint32_t  READFIFO7;                         /*!< EPI Read FIFO Alias 7                                                 */
  __I  uint32_t  RESERVED5[92];
  __IO uint32_t  FIFOLVL;                           /*!< EPI FIFO Level Selects                                                */
  __IO uint32_t  WFIFOCNT;                          /*!< EPI Write FIFO Count                                                  */
  __IO uint32_t  DMATXCNT;                          /*!< EPI DMA Transmit Count                                                */
  __I  uint32_t  RESERVED6;
  __IO uint32_t  IM;                                /*!< EPI Interrupt Mask                                                    */
  __IO uint32_t  RIS;                               /*!< EPI Raw Interrupt Status                                              */
  __IO uint32_t  MIS;                               /*!< EPI Masked Interrupt Status                                           */
  __IO uint32_t  EISC;                              /*!< EPI Error and Interrupt Status and Clear                              */
  __I  uint32_t  RESERVED7[58];
  
  union {
    __IO uint32_t  HB16CFG3_EPI_ALT16;              /*!< EPI Host-Bus 16 Configuration 3                                       */
    __IO uint32_t  HB8CFG3;                         /*!< EPI Host-Bus 8 Configuration 3                                        */
  };
  
  union {
    __IO uint32_t  HB8CFG4_EPI_ALT8;                /*!< EPI Host-Bus 8 Configuration 4                                        */
    __IO uint32_t  HB16CFG4;                        /*!< EPI Host-Bus 16 Configuration 4                                       */
  };
  
  union {
    __IO uint32_t  HB16TIME_EPI_ALT16;              /*!< EPI Host-Bus 16 Timing Extension                                      */
    __IO uint32_t  HB8TIME;                         /*!< EPI Host-Bus 8 Timing Extension                                       */
  };
  
  union {
    __IO uint32_t  HB16TIME2_EPI_ALT16;             /*!< EPI Host-Bus 16 Timing Extension                                      */
    __IO uint32_t  HB8TIME2;                        /*!< EPI Host-Bus 8 Timing Extension                                       */
  };
  
  union {
    __IO uint32_t  HB8TIME3_EPI_ALT8;               /*!< EPI Host-Bus 8 Timing Extension                                       */
    __IO uint32_t  HB16TIME3;                       /*!< EPI Host-Bus 16 Timing Extension                                      */
  };
  
  union {
    __IO uint32_t  HB16TIME4;                       /*!< EPI Host-Bus 16 Timing Extension                                      */
    __IO uint32_t  HB8TIME4_EPI_ALT8;               /*!< EPI Host-Bus 8 Timing Extension                                       */
  };
  __I  uint32_t  RESERVED8[16];
  __IO uint32_t  HBPSRAM;                           /*!< EPI Host-Bus PSRAM                                                    */
} EPI0_Type;


/* ================================================================================ */
/* ================                      EMAC0                     ================ */
/* ================================================================================ */


/**
  * @brief Register map for EMAC0 peripheral (EMAC0)
  */

typedef struct {                                    /*!< EMAC0 Structure                                                       */
  __IO uint32_t  CFG;                               /*!< Ethernet MAC Configuration                                            */
  __IO uint32_t  FRAMEFLTR;                         /*!< Ethernet MAC Frame Filter                                             */
  __IO uint32_t  HASHTBLH;                          /*!< Ethernet MAC Hash Table High                                          */
  __IO uint32_t  HASHTBLL;                          /*!< Ethernet MAC Hash Table Low                                           */
  __IO uint32_t  MIIADDR;                           /*!< Ethernet MAC MII Address                                              */
  __IO uint32_t  MIIDATA;                           /*!< Ethernet MAC MII Data Register                                        */
  __IO uint32_t  FLOWCTL;                           /*!< Ethernet MAC Flow Control                                             */
  __IO uint32_t  VLANTG;                            /*!< Ethernet MAC VLAN Tag                                                 */
  __I  uint32_t  RESERVED0;
  __IO uint32_t  STATUS;                            /*!< Ethernet MAC Status                                                   */
  __IO uint32_t  RWUFF;                             /*!< Ethernet MAC Remote Wake-Up Frame Filter                              */
  __IO uint32_t  PMTCTLSTAT;                        /*!< Ethernet MAC PMT Control and Status Register                          */
  __I  uint32_t  RESERVED1[2];
  __IO uint32_t  RIS;                               /*!< Ethernet MAC Raw Interrupt Status                                     */
  __IO uint32_t  IM;                                /*!< Ethernet MAC Interrupt Mask                                           */
  __IO uint32_t  ADDR0H;                            /*!< Ethernet MAC Address 0 High                                           */
  __IO uint32_t  ADDR0L;                            /*!< Ethernet MAC Address 0 Low Register                                   */
  __IO uint32_t  ADDR1H;                            /*!< Ethernet MAC Address 1 High                                           */
  __IO uint32_t  ADDR1L;                            /*!< Ethernet MAC Address 1 Low                                            */
  __IO uint32_t  ADDR2H;                            /*!< Ethernet MAC Address 2 High                                           */
  __IO uint32_t  ADDR2L;                            /*!< Ethernet MAC Address 2 Low                                            */
  __IO uint32_t  ADDR3H;                            /*!< Ethernet MAC Address 3 High                                           */
  __IO uint32_t  ADDR3L;                            /*!< Ethernet MAC Address 3 Low                                            */
  __I  uint32_t  RESERVED2[31];
  __IO uint32_t  WDOGTO;                            /*!< Ethernet MAC Watchdog Timeout                                         */
  __I  uint32_t  RESERVED3[8];
  __IO uint32_t  MMCCTRL;                           /*!< Ethernet MAC MMC Control                                              */
  __I  uint32_t  RESERVED4[5];
  __IO uint32_t  TXCNTGB;                           /*!< Ethernet MAC Transmit Frame Count for Good and Bad Frames             */
  __I  uint32_t  RESERVED5[12];
  __IO uint32_t  TXCNTSCOL;                         /*!< Ethernet MAC Transmit Frame Count for Frames Transmitted after
                                                         Single Collision                                                      */
  __IO uint32_t  TXCNTMCOL;                         /*!< Ethernet MAC Transmit Frame Count for Frames Transmitted after
                                                         Multiple Collisions                                                   */
  __I  uint32_t  RESERVED6[4];
  __IO uint32_t  TXOCTCNTG;                         /*!< Ethernet MAC Transmit Octet Count Good                                */
  __I  uint32_t  RESERVED7[6];
  __IO uint32_t  RXCNTGB;                           /*!< Ethernet MAC Receive Frame Count for Good and Bad Frames              */
  __I  uint32_t  RESERVED8[4];
  __IO uint32_t  RXCNTCRCERR;                       /*!< Ethernet MAC Receive Frame Count for CRC Error Frames                 */
  __IO uint32_t  RXCNTALGNERR;                      /*!< Ethernet MAC Receive Frame Count for Alignment Error Frames           */
  __I  uint32_t  RESERVED9[10];
  __IO uint32_t  RXCNTGUNI;                         /*!< Ethernet MAC Receive Frame Count for Good Unicast Frames              */
  __I  uint32_t  RESERVED10[239];
  __IO uint32_t  VLNINCREP;                         /*!< Ethernet MAC VLAN Tag Inclusion or Replacement                        */
  __IO uint32_t  VLANHASH;                          /*!< Ethernet MAC VLAN Hash Table                                          */
  __I  uint32_t  RESERVED11[93];
  __IO uint32_t  TIMSTCTRL;                         /*!< Ethernet MAC Timestamp Control                                        */
  __IO uint32_t  SUBSECINC;                         /*!< Ethernet MAC Sub-Second Increment                                     */
  __IO uint32_t  TIMSEC;                            /*!< Ethernet MAC System Time - Seconds                                    */
  __IO uint32_t  TIMNANO;                           /*!< Ethernet MAC System Time - Nanoseconds                                */
  __IO uint32_t  TIMSECU;                           /*!< Ethernet MAC System Time - Seconds Update                             */
  __IO uint32_t  TIMNANOU;                          /*!< Ethernet MAC System Time - Nanoseconds Update                         */
  __IO uint32_t  TIMADD;                            /*!< Ethernet MAC Time Stamp Addend                                        */
  __IO uint32_t  TARGSEC;                           /*!< Ethernet MAC Target Time Seconds                                      */
  __IO uint32_t  TARGNANO;                          /*!< Ethernet MAC Target Time Nanoseconds                                  */
  __IO uint32_t  HWORDSEC;                          /*!< Ethernet MAC System Time-Higher Word Seconds                          */
  __IO uint32_t  TIMSTAT;                           /*!< Ethernet MAC Time Stamp Status                                        */
  __IO uint32_t  PPSCTRL;                           /*!< Ethernet MAC PPS Control                                              */
  __I  uint32_t  RESERVED12[12];
  __IO uint32_t  PPS0INTVL;                         /*!< Ethernet MAC PPS0 Interval                                            */
  __IO uint32_t  PPS0WIDTH;                         /*!< Ethernet MAC PPS0 Width                                               */
  __I  uint32_t  RESERVED13[294];
  __IO uint32_t  DMABUSMOD;                         /*!< Ethernet MAC DMA Bus Mode                                             */
  __O  uint32_t  TXPOLLD;                           /*!< Ethernet MAC Transmit Poll Demand                                     */
  __O  uint32_t  RXPOLLD;                           /*!< Ethernet MAC Receive Poll Demand                                      */
  __IO uint32_t  RXDLADDR;                          /*!< Ethernet MAC Receive Descriptor List Address                          */
  __IO uint32_t  TXDLADDR;                          /*!< Ethernet MAC Transmit Descriptor List Address                         */
  __IO uint32_t  DMARIS;                            /*!< Ethernet MAC DMA Interrupt Status                                     */
  __IO uint32_t  DMAOPMODE;                         /*!< Ethernet MAC DMA Operation Mode                                       */
  __IO uint32_t  DMAIM;                             /*!< Ethernet MAC DMA Interrupt Mask Register                              */
  __IO uint32_t  MFBOC;                             /*!< Ethernet MAC Missed Frame and Buffer Overflow Counter                 */
  __IO uint32_t  RXINTWDT;                          /*!< Ethernet MAC Receive Interrupt Watchdog Timer                         */
  __I  uint32_t  RESERVED14[8];
  __IO uint32_t  HOSTXDESC;                         /*!< Ethernet MAC Current Host Transmit Descriptor                         */
  __IO uint32_t  HOSRXDESC;                         /*!< Ethernet MAC Current Host Receive Descriptor                          */
  __IO uint32_t  HOSTXBA;                           /*!< Ethernet MAC Current Host Transmit Buffer Address                     */
  __IO uint32_t  HOSRXBA;                           /*!< Ethernet MAC Current Host Receive Buffer Address                      */
  __I  uint32_t  RESERVED15[218];
  __IO uint32_t  PP;                                /*!< Ethernet MAC Peripheral Property Register                             */
  __IO uint32_t  PC;                                /*!< Ethernet MAC Peripheral Configuration Register                        */
  __IO uint32_t  CC;                                /*!< Ethernet MAC Clock Configuration Register                             */
} EMAC0_Type;


/* ================================================================================ */
/* ================                     SYSEXC                     ================ */
/* ================================================================================ */


/**
  * @brief Register map for SYSEXC peripheral (SYSEXC)
  */

typedef struct {                                    /*!< SYSEXC Structure                                                      */
  __IO uint32_t  RIS;                               /*!< System Exception Raw Interrupt Status                                 */
  __IO uint32_t  IM;                                /*!< System Exception Interrupt Mask                                       */
  __IO uint32_t  MIS;                               /*!< System Exception Masked Interrupt Status                              */
  __O  uint32_t  IC;                                /*!< System Exception Interrupt Clear                                      */
} SYSEXC_Type;


/* ================================================================================ */
/* ================                       HIB                      ================ */
/* ================================================================================ */


/**
  * @brief Register map for HIB peripheral (HIB)
  */

typedef struct {                                    /*!< HIB Structure                                                         */
  __IO uint32_t  RTCC;                              /*!< Hibernation RTC Counter                                               */
  __IO uint32_t  RTCM0;                             /*!< Hibernation RTC Match 0                                               */
  __I  uint32_t  RESERVED0;
  __IO uint32_t  RTCLD;                             /*!< Hibernation RTC Load                                                  */
  __IO uint32_t  CTL;                               /*!< Hibernation Control                                                   */
  __IO uint32_t  IM;                                /*!< Hibernation Interrupt Mask                                            */
  __IO uint32_t  RIS;                               /*!< Hibernation Raw Interrupt Status                                      */
  __IO uint32_t  MIS;                               /*!< Hibernation Masked Interrupt Status                                   */
  __IO uint32_t  IC;                                /*!< Hibernation Interrupt Clear                                           */
  __IO uint32_t  RTCT;                              /*!< Hibernation RTC Trim                                                  */
  __IO uint32_t  RTCSS;                             /*!< Hibernation RTC Sub Seconds                                           */
  __IO uint32_t  IO;                                /*!< Hibernation IO Configuration                                          */
  __IO uint32_t  DATA;                              /*!< Hibernation Data                                                      */
  __I  uint32_t  RESERVED1[179];
  __IO uint32_t  CALCTL;                            /*!< Hibernation Calendar Control                                          */
  __I  uint32_t  RESERVED2[3];
  __IO uint32_t  CAL0;                              /*!< Hibernation Calendar 0                                                */
  __IO uint32_t  CAL1;                              /*!< Hibernation Calendar 1                                                */
  __I  uint32_t  RESERVED3[2];
  __O  uint32_t  CALLD0;                            /*!< Hibernation Calendar Load 0                                           */
  __O  uint32_t  CALLD1;                            /*!< Hibernation Calendar Load                                             */
  __I  uint32_t  RESERVED4[2];
  __IO uint32_t  CALM0;                             /*!< Hibernation Calendar Match 0                                          */
  __IO uint32_t  CALM1;                             /*!< Hibernation Calendar Match 1                                          */
  __I  uint32_t  RESERVED5[10];
  __IO uint32_t  LOCK;                              /*!< Hibernation Lock                                                      */
  __I  uint32_t  RESERVED6[39];
  __IO uint32_t  TPCTL;                             /*!< HIB Tamper Control                                                    */
  __IO uint32_t  TPSTAT;                            /*!< HIB Tamper Status                                                     */
  __I  uint32_t  RESERVED7[2];
  __IO uint32_t  TPIO;                              /*!< HIB Tamper I/O Control and Status                                     */
  __I  uint32_t  RESERVED8[51];
  __IO uint32_t  TPLOG0;                            /*!< HIB Tamper Log 0                                                      */
  __IO uint32_t  TPLOG1;                            /*!< HIB Tamper Log 1                                                      */
  __IO uint32_t  TPLOG2;                            /*!< HIB Tamper Log 2                                                      */
  __IO uint32_t  PLOG3;                             /*!< HIB Tamper Log 3                                                      */
  __IO uint32_t  TPLOG4;                            /*!< HIB Tamper Log 4                                                      */
  __IO uint32_t  TPLOG5;                            /*!< HIB Tamper Log 5                                                      */
  __IO uint32_t  TPLOG6;                            /*!< HIB Tamper Log 6                                                      */
  __IO uint32_t  TPLOG7;                            /*!< HIB Tamper Log 7                                                      */
  __I  uint32_t  RESERVED9[688];
  __IO uint32_t  PP;                                /*!< Hibernation Peripheral Properties                                     */
  __I  uint32_t  RESERVED10;
  __IO uint32_t  CC;                                /*!< Hibernation Clock Control                                             */
} HIB_Type;


/* ================================================================================ */
/* ================                   FLASH_CTRL                   ================ */
/* ================================================================================ */


/**
  * @brief Register map for FLASH_CTRL peripheral (FLASH_CTRL)
  */

typedef struct {                                    /*!< FLASH_CTRL Structure                                                  */
  __IO uint32_t  FMA;                               /*!< Flash Memory Address                                                  */
  __IO uint32_t  FMD;                               /*!< Flash Memory Data                                                     */
  __IO uint32_t  FMC;                               /*!< Flash Memory Control                                                  */
  __IO uint32_t  FCRIS;                             /*!< Flash Controller Raw Interrupt Status                                 */
  __IO uint32_t  FCIM;                              /*!< Flash Controller Interrupt Mask                                       */
  __IO uint32_t  FCMISC;                            /*!< Flash Controller Masked Interrupt Status and Clear                    */
  __I  uint32_t  RESERVED0[2];
  __IO uint32_t  FMC2;                              /*!< Flash Memory Control 2                                                */
  __I  uint32_t  RESERVED1[3];
  __IO uint32_t  FWBVAL;                            /*!< Flash Write Buffer Valid                                              */
  __I  uint32_t  RESERVED2[2];
  __IO uint32_t  FLPEKEY;                           /*!< Flash Program/Erase Key                                               */
  __I  uint32_t  RESERVED3[48];
  __IO uint32_t  FWBN;                              /*!< Flash Write Buffer n                                                  */
  __I  uint32_t  RESERVED4[923];
  __IO uint32_t  RDPUMPTCR0;                        /*!< Read Pump TCR Mask 0                                                  */
  __I  uint32_t  RESERVED5[19];
  __IO uint32_t  PP;                                /*!< Code SRAM Peripheral Properties                                       */
  __IO uint32_t  SSIZE;                             /*!< SRAM Size                                                             */
  __IO uint32_t  CONF;                              /*!< Flash Configuration Register                                          */
  __IO uint32_t  ROMSWMAP;                          /*!< ROM Software Map                                                      */
  __IO uint32_t  DMASZ;                             /*!< Code SRAM DMA Address Size                                            */
  __IO uint32_t  DMAST;                             /*!< Code SRAM DMA Starting Address                                        */
  __I  uint32_t  RESERVED6[63];
  __IO uint32_t  RVP;                               /*!< Reset Vector Pointer                                                  */
  __I  uint32_t  RESERVED7[62];
  __IO uint32_t  BOOTCFG;                           /*!< Boot Configuration                                                    */
  __I  uint32_t  RESERVED8[2];
  __IO uint32_t  USRPWRUP;                          /*!< USER Power-Up Control                                                 */
  __IO uint32_t  USERREG0;                          /*!< User Register 0                                                       */
  __IO uint32_t  USERREG1;                          /*!< User Register 1                                                       */
  __IO uint32_t  USERREG2;                          /*!< User Register 2                                                       */
  __IO uint32_t  USERREG3;                          /*!< User Register 3                                                       */
  __I  uint32_t  RESERVED9[4];
  __IO uint32_t  FMPRE0;                            /*!< Flash Memory Protection Read Enable 0                                 */
  __IO uint32_t  FMPRE1;                            /*!< Flash Memory Protection Read Enable 1                                 */
  __IO uint32_t  FMPRE2;                            /*!< Flash Memory Protection Read Enable 2                                 */
  __IO uint32_t  FMPRE3;                            /*!< Flash Memory Protection Read Enable 3                                 */
  __IO uint32_t  FMPRE4;                            /*!< Flash Memory Protection Read Enable 4                                 */
  __IO uint32_t  FMPRE5;                            /*!< Flash Memory Protection Read Enable 5                                 */
  __IO uint32_t  FMPRE6;                            /*!< Flash Memory Protection Read Enable 6                                 */
  __IO uint32_t  FMPRE7;                            /*!< Flash Memory Protection Read Enable 7                                 */
  __IO uint32_t  FMPRE8;                            /*!< Flash Memory Protection Read Enable 8                                 */
  __IO uint32_t  FMPRE9;                            /*!< Flash Memory Protection Read Enable 9                                 */
  __IO uint32_t  FMPRE10;                           /*!< Flash Memory Protection Read Enable 10                                */
  __IO uint32_t  FMPRE11;                           /*!< Flash Memory Protection Read Enable 11                                */
  __IO uint32_t  FMPRE12;                           /*!< Flash Memory Protection Read Enable 12                                */
  __IO uint32_t  FMPRE13;                           /*!< Flash Memory Protection Read Enable 13                                */
  __IO uint32_t  FMPRE14;                           /*!< Flash Memory Protection Read Enable 14                                */
  __IO uint32_t  FMPRE15;                           /*!< Flash Memory Protection Read Enable 15                                */
  __I  uint32_t  RESERVED10[112];
  __IO uint32_t  FMPPE0;                            /*!< Flash Memory Protection Program Enable 0                              */
  __IO uint32_t  FMPPE1;                            /*!< Flash Memory Protection Program Enable 1                              */
  __IO uint32_t  FMPPE2;                            /*!< Flash Memory Protection Program Enable 2                              */
  __IO uint32_t  FMPPE3;                            /*!< Flash Memory Protection Program Enable 3                              */
  __IO uint32_t  FMPPE4;                            /*!< Flash Memory Protection Program Enable 4                              */
  __IO uint32_t  FMPPE5;                            /*!< Flash Memory Protection Program Enable 5                              */
  __IO uint32_t  FMPPE6;                            /*!< Flash Memory Protection Program Enable 6                              */
  __IO uint32_t  FMPPE7;                            /*!< Flash Memory Protection Program Enable 7                              */
  __IO uint32_t  FMPPE8;                            /*!< Flash Memory Protection Program Enable 8                              */
  __IO uint32_t  FMPPE9;                            /*!< Flash Memory Protection Program Enable 9                              */
  __IO uint32_t  FMPPE10;                           /*!< Flash Memory Protection Program Enable 10                             */
  __IO uint32_t  FMPPE11;                           /*!< Flash Memory Protection Program Enable 11                             */
  __IO uint32_t  FMPPE12;                           /*!< Flash Memory Protection Program Enable 12                             */
  __IO uint32_t  FMPPE13;                           /*!< Flash Memory Protection Program Enable 13                             */
  __IO uint32_t  FMPPE14;                           /*!< Flash Memory Protection Program Enable 14                             */
  __IO uint32_t  FMPPE15;                           /*!< Flash Memory Protection Program Enable 15                             */
} FLASH_CTRL_Type;


/* ================================================================================ */
/* ================                     SYSCTL                     ================ */
/* ================================================================================ */


/**
  * @brief Register map for SYSCTL peripheral (SYSCTL)
  */

typedef struct {                                    /*!< SYSCTL Structure                                                      */
  __IO uint32_t  DID0;                              /*!< Device Identification 0                                               */
  __IO uint32_t  DID1;                              /*!< Device Identification 1                                               */
  __I  uint32_t  RESERVED0[12];
  __IO uint32_t  PTBOCTL;                           /*!< Power-Temp Brown Out Control                                          */
  __I  uint32_t  RESERVED1[5];
  __IO uint32_t  RIS;                               /*!< Raw Interrupt Status                                                  */
  __IO uint32_t  IMC;                               /*!< Interrupt Mask Control                                                */
  __IO uint32_t  MISC;                              /*!< Masked Interrupt Status and Clear                                     */
  __IO uint32_t  RESC;                              /*!< Reset Cause                                                           */
  __IO uint32_t  PWRTC;                             /*!< Power-Temperature Cause                                               */
  __IO uint32_t  NMIC;                              /*!< NMI Cause Register                                                    */
  __I  uint32_t  RESERVED2[5];
  __IO uint32_t  MOSCCTL;                           /*!< Main Oscillator Control                                               */
  __I  uint32_t  RESERVED3[12];
  __IO uint32_t  RSCLKCFG;                          /*!< Run and Sleep Mode Configuration Register                             */
  __I  uint32_t  RESERVED4[3];
  __IO uint32_t  MEMTIM0;                           /*!< Memory Timing Parameter Register 0 for Main Flash and EEPROM          */
  __I  uint32_t  RESERVED5;
  __IO uint32_t  DSMEMTIM0;                         /*!< Deep Sleep Mode Memory Timing Register 0 for Main Flash and
                                                         EEPROM                                                                */
  __I  uint32_t  RESERVED6[27];
  __IO uint32_t  ALTCLKCFG;                         /*!< Alternate Clock Configuration                                         */
  __I  uint32_t  RESERVED7[2];
  __IO uint32_t  DSCLKCFG;                          /*!< Deep Sleep Clock Configuration Register                               */
  __IO uint32_t  DIVSCLK;                           /*!< Divisor and Source Clock Configuration                                */
  __IO uint32_t  SYSPROP;                           /*!< System Properties                                                     */
  __IO uint32_t  PIOSCCAL;                          /*!< Precision Internal Oscillator Calibration                             */
  __IO uint32_t  PIOSCSTAT;                         /*!< Precision Internal Oscillator Statistics                              */
  __I  uint32_t  RESERVED8[2];
  __IO uint32_t  PLLFREQ0;                          /*!< PLL Frequency 0                                                       */
  __IO uint32_t  PLLFREQ1;                          /*!< PLL Frequency 1                                                       */
  __IO uint32_t  PLLSTAT;                           /*!< PLL Status                                                            */
  __I  uint32_t  RESERVED9[13];
  __IO uint32_t  NVMSTAT;                           /*!< Non-Volatile Memory Information                                       */
  __I  uint32_t  RESERVED10[13];
  __IO uint32_t  RESBEHAVCTL;                       /*!< Reset Behavior Control Register                                       */
  __I  uint32_t  RESERVED11[6];
  __IO uint32_t  HSSR;                              /*!< Hardware System Service Request                                       */
  __I  uint32_t  RESERVED12[34];
  __IO uint32_t  USBPDS;                            /*!< USB Power Domain Status                                               */
  __IO uint32_t  USBMPC;                            /*!< USB Memory Power Control                                              */
  __IO uint32_t  EMACPDS;                           /*!< Ethernet MAC Power Domain Status                                      */
  __IO uint32_t  EMACMPC;                           /*!< Ethernet MAC Memory Power Control                                     */
  __I  uint32_t  RESERVED13[28];
  __IO uint32_t  PPWD;                              /*!< Watchdog Timer Peripheral Present                                     */
  __I  uint32_t  RESERVED14;
  __IO uint32_t  PPGPIO;                            /*!< General-Purpose Input/Output Peripheral Present                       */
  __IO uint32_t  PPDMA;                             /*!< Micro Direct Memory Access Peripheral Present                         */
  __IO uint32_t  PPEPI;                             /*!< EPI Peripheral Present -SCPL                                          */
  __IO uint32_t  PPHIB;                             /*!< Hibernation Peripheral Present                                        */
  __IO uint32_t  PPUART;                            /*!< Universal Asynchronous Receiver/Transmitter Peripheral Present        */
  __IO uint32_t  PPSSI;                             /*!< Synchronous Serial Interface Peripheral Present                       */
  __IO uint32_t  PPI2C;                             /*!< Inter-Integrated Circuit Peripheral Present                           */
  __I  uint32_t  RESERVED15;
  __IO uint32_t  PPUSB;                             /*!< Universal Serial Bus Peripheral Present                               */
  __I  uint32_t  RESERVED16;
  __IO uint32_t  PPEPHY;                            /*!< Ethernet PHY Peripheral Present                                       */
  __IO uint32_t  PPCAN;                             /*!< Controller Area Network Peripheral Present                            */
  __IO uint32_t  PPADC;                             /*!< Analog-to-Digital Converter Peripheral Present                        */
  __IO uint32_t  PPACMP;                            /*!< Analog Comparator Peripheral Present                                  */
  __IO uint32_t  PPPWM;                             /*!< Pulse Width Modulator Peripheral Present                              */
  __IO uint32_t  PPQEI;                             /*!< Quadrature Encoder Interface Peripheral Present                       */
  __IO uint32_t  PPLPC;                             /*!< Low Pin Count Interface Peripheral Present                            */
  __I  uint32_t  RESERVED17;
  __IO uint32_t  PPPECI;                            /*!< Platform Environment Control Interface Peripheral Present             */
  __IO uint32_t  PPFAN;                             /*!< Fan Control Peripheral Present                                        */
  __IO uint32_t  PPEEPROM;                          /*!< EEPROM Peripheral Present                                             */
  __IO uint32_t  PPWTIMER;                          /*!< Wide Timer Peripheral Present                                         */
  __I  uint32_t  RESERVED18[4];
  __IO uint32_t  PPRTS;                             /*!< Remote Temperature Sensor Peripheral Present -SCPL                    */
  __IO uint32_t  PPCCM;                             /*!< CRC and Cryptographic Modules Peripheral Present                      */
  __I  uint32_t  RESERVED19[6];
  __IO uint32_t  PPLCD;                             /*!< LCD Peripheral Present - INIT ROM                                     */
  __I  uint32_t  RESERVED20;
  __IO uint32_t  PPOWIRE;                           /*!< One-Wire Peripheral Present -SCPL                                     */
  __IO uint32_t  PPEMAC;                            /*!< Ethernet MAC Peripheral Present                                       */
  __IO uint32_t  PPPRB;                             /*!< Power Regulator Bus Peripheral Present -SCPL                          */
  __IO uint32_t  PPHIM;                             /*!< Human Interface Master Peripheral Present -SCPL                       */
  __I  uint32_t  RESERVED21[86];
  __IO uint32_t  SRWD;                              /*!< Watchdog Timer Software Reset                                         */
  __IO uint32_t  SRTIMER;                           /*!< Timer Software Reset                                                  */
  __IO uint32_t  SRGPIO;                            /*!< General-Purpose Input/Output Software Reset                           */
  __IO uint32_t  SRDMA;                             /*!< Micro Direct Memory Access Software Reset                             */
  __IO uint32_t  SREPI;                             /*!< EPI Software Reset                                                    */
  __IO uint32_t  SRHIB;                             /*!< Hibernation Software Reset                                            */
  __IO uint32_t  SRUART;                            /*!< Universal Asynchronous Receiver/Transmitter Software Reset            */
  __IO uint32_t  SRSSI;                             /*!< Synchronous Serial Interface Software Reset                           */
  __IO uint32_t  SRI2C;                             /*!< Inter-Integrated Circuit Software Reset                               */
  __I  uint32_t  RESERVED22;
  __IO uint32_t  SRUSB;                             /*!< Universal Serial Bus Software Reset                                   */
  __I  uint32_t  RESERVED23[3];
  __IO uint32_t  SRADC;                             /*!< Analog-to-Digital Converter Software Reset                            */
  __IO uint32_t  SRACMP;                            /*!< Analog Comparator Software Reset                                      */
  __I  uint32_t  RESERVED24[2];
  __IO uint32_t  SRLPC;                             /*!< Low Pin Count Interface Software Reset                                */
  __I  uint32_t  RESERVED25;
  __IO uint32_t  SRPECI;                            /*!< Platform Environment Control Interface Software Reset                 */
  __IO uint32_t  SRFAN;                             /*!< Fan Software Reset                                                    */
  __IO uint32_t  SREEPROM;                          /*!< EEPROM Software Reset                                                 */
  __I  uint32_t  RESERVED26[6];
  __IO uint32_t  SRCCM;                             /*!< CRC and Cryptographic Modules Software Reset                          */
  __I  uint32_t  RESERVED27[8];
  __IO uint32_t  SROWIRE;                           /*!< One-Wire Software Reset                                               */
  __IO uint32_t  SREMAC;                            /*!< Ethernet MAC Software Reset                                           */
  __I  uint32_t  RESERVED28;
  __IO uint32_t  SRHIM;                             /*!< Human Interface Master Software Reset                                 */
  __I  uint32_t  RESERVED29[22];
  __IO uint32_t  RCGCWD;                            /*!< Watchdog Timer Run Mode Clock Gating Control                          */
  __IO uint32_t  RCGCTIMER;                         /*!< Timer Run Mode Clock Gating Control                                   */
  __IO uint32_t  RCGCGPIO;                          /*!< General-Purpose Input/Output Run Mode Clock Gating Control            */
  __IO uint32_t  RCGCDMA;                           /*!< Micro Direct Memory Access Run Mode Clock Gating Control              */
  __IO uint32_t  RCGCEPI;                           /*!< EPI Run Mode Clock Gating Control                                     */
  __IO uint32_t  RCGCHIB;                           /*!< Hibernation Run Mode Clock Gating Control                             */
  __IO uint32_t  RCGCUART;                          /*!< Universal Asynchronous Receiver/Transmitter Run Mode Clock Gating
                                                         Control                                                               */
  __IO uint32_t  RCGCSSI;                           /*!< Synchronous Serial Interface Run Mode Clock Gating Control            */
  __IO uint32_t  RCGCI2C;                           /*!< Inter-Integrated Circuit Run Mode Clock Gating Control                */
  __I  uint32_t  RESERVED30;
  __IO uint32_t  RCGCUSB;                           /*!< Universal Serial Bus Run Mode Clock Gating Control                    */
  __I  uint32_t  RESERVED31[3];
  __IO uint32_t  RCGCADC;                           /*!< Analog-to-Digital Converter Run Mode Clock Gating Control             */
  __IO uint32_t  RCGCACMP;                          /*!< Analog Comparator Run Mode Clock Gating Control                       */
  __I  uint32_t  RESERVED32[2];
  __IO uint32_t  RCGCLPC;                           /*!< Low Pin Count Interface Run Mode Clock Gating Control                 */
  __I  uint32_t  RESERVED33;
  __IO uint32_t  RCGCPECI;                          /*!< Platform Environment Control Interface Run Mode Clock Gating
                                                         Control                                                               */
  __IO uint32_t  RCGCFAN;                           /*!< Fan Run Mode Clock Gating Control                                     */
  __IO uint32_t  RCGCEEPROM;                        /*!< EEPROM Run Mode Clock Gating Control                                  */
  __I  uint32_t  RESERVED34[6];
  __IO uint32_t  RCGCCCM;                           /*!< CRC and Cryptographic Modules Run Mode Clock Gating Control           */
  __I  uint32_t  RESERVED35[8];
  __IO uint32_t  RCGCOWIRE;                         /*!< One-Wire Run Mode Clock Gating Control                                */
  __IO uint32_t  RCGCEMAC;                          /*!< Ethernet MAC Run Mode Clock Gating Control                            */
  __I  uint32_t  RESERVED36;
  __IO uint32_t  RCGCHIM;                           /*!< Human Interface Master Run Mode Clock Gating Control                  */
  __I  uint32_t  RESERVED37[22];
  __IO uint32_t  SCGCWD;                            /*!< Watchdog Timer Sleep Mode Clock Gating Control                        */
  __IO uint32_t  SCGCTIMER;                         /*!< Timer Sleep Mode Clock Gating Control                                 */
  __IO uint32_t  SCGCGPIO;                          /*!< General-Purpose Input/Output Sleep Mode Clock Gating Control          */
  __I  uint32_t  RESERVED38;
  __IO uint32_t  SCGCEPI;                           /*!< EPI Sleep Mode Clock Gating Control                                   */
  __IO uint32_t  SCGCHIB;                           /*!< Hibernation Sleep Mode Clock Gating Control                           */
  __IO uint32_t  SCGCUART;                          /*!< Universal Asynchronous Receiver/Transmitter Sleep Mode Clock
                                                         Gating Control                                                        */
  __IO uint32_t  SCGCSSI;                           /*!< Synchronous Serial Interface Sleep Mode Clock Gating Control          */
  __IO uint32_t  SCGCI2C;                           /*!< Inter-Integrated Circuit Sleep Mode Clock Gating Control              */
  __I  uint32_t  RESERVED39;
  __IO uint32_t  SCGCUSB;                           /*!< Universal Serial Bus Sleep Mode Clock Gating Control                  */
  __I  uint32_t  RESERVED40[3];
  __IO uint32_t  SCGCADC;                           /*!< Analog-to-Digital Converter Sleep Mode Clock Gating Control           */
  __IO uint32_t  SCGCACMP;                          /*!< Analog Comparator Sleep Mode Clock Gating Control                     */
  __I  uint32_t  RESERVED41[2];
  __IO uint32_t  SCGCLPC;                           /*!< Low Pin Count Interface Sleep Mode Clock Gating Control               */
  __I  uint32_t  RESERVED42;
  __IO uint32_t  SCGCPECI;                          /*!< Platform Environment Control Interface Sleep Mode Clock Gating
                                                         Control                                                               */
  __IO uint32_t  SCGCFAN;                           /*!< Fan Sleep Mode Clock Gating Control                                   */
  __IO uint32_t  SCGCEEPROM;                        /*!< EEPROM Sleep Mode Clock Gating Control                                */
  __I  uint32_t  RESERVED43[6];
  __IO uint32_t  SCGCCCM;                           /*!< CRC and Cryptographic Modules Sleep Mode Clock Gating Control         */
  __I  uint32_t  RESERVED44[8];
  __IO uint32_t  SCGCOWIRE;                         /*!< One-Wire Sleep Mode Clock Gating Control                              */
  __IO uint32_t  SCGCEMAC;                          /*!< Ethernet MAC Sleep Mode Clock Gating Control                          */
  __I  uint32_t  RESERVED45;
  __IO uint32_t  SCGCHIM;                           /*!< Human Interface Master Sleep Mode Clock Gating Control                */
  __I  uint32_t  RESERVED46[22];
  __IO uint32_t  DCGCWD;                            /*!< Watchdog Timer Deep-Sleep Mode Clock Gating Control                   */
  __IO uint32_t  DCGCTIMER;                         /*!< Timer Deep-Sleep Mode Clock Gating Control                            */
  __IO uint32_t  DCGCGPIO;                          /*!< General-Purpose Input/Output Deep-Sleep Mode Clock Gating Control     */
  __I  uint32_t  RESERVED47;
  __IO uint32_t  DCGCEPI;                           /*!< EPI Deep-Sleep Mode Clock Gating Control                              */
  __IO uint32_t  DCGCHIB;                           /*!< Hibernation Deep-Sleep Mode Clock Gating Control                      */
  __IO uint32_t  DCGCUART;                          /*!< Universal Asynchronous Receiver/Transmitter Deep-Sleep Mode
                                                         Clock Gating Control                                                  */
  __IO uint32_t  DCGCSSI;                           /*!< Synchronous Serial Interface Deep-Sleep Mode Clock Gating Control     */
  __IO uint32_t  DCGCI2C;                           /*!< Inter-Integrated Circuit Deep-Sleep Mode Clock Gating Control         */
  __I  uint32_t  RESERVED48;
  __IO uint32_t  DCGCUSB;                           /*!< Universal Serial Bus Deep-Sleep Mode Clock Gating Control             */
  __I  uint32_t  RESERVED49[3];
  __IO uint32_t  DCGCADC;                           /*!< Analog-to-Digital Converter Deep-Sleep Mode Clock Gating Control      */
  __IO uint32_t  DCGCACMP;                          /*!< Analog Comparator Deep-Sleep Mode Clock Gating Control                */
  __I  uint32_t  RESERVED50[2];
  __IO uint32_t  DCGCLPC;                           /*!< Low Pin Count Interface Deep-Sleep Mode Clock Gating Control          */
  __I  uint32_t  RESERVED51;
  __IO uint32_t  DCGCPECI;                          /*!< Platform Environment Control Interface Deep-Sleep Mode Clock
                                                         Gating Control                                                        */
  __IO uint32_t  DCGCFAN;                           /*!< Fan Deep-Sleep Mode Clock Gating Control                              */
  __IO uint32_t  DCGCEEPROM;                        /*!< EEPROM Deep-Sleep Mode Clock Gating Control                           */
  __I  uint32_t  RESERVED52[6];
  __IO uint32_t  DCGCCCM;                           /*!< CRC and Cryptographic Modules Deep-Sleep Mode Clock Gating Control    */
  __I  uint32_t  RESERVED53[8];
  __IO uint32_t  DCGCOWIRE;                         /*!< One-Wire Deep-Sleep Mode Clock Gating Control                         */
  __IO uint32_t  DCGCEMAC;                          /*!< Ethernet MAC Deep-Sleep Mode Clock Gating Control                     */
  __I  uint32_t  RESERVED54;
  __IO uint32_t  DCGCHIM;                           /*!< Human Interface Master Deep-Sleep Mode Clock Gating Control           */
  __I  uint32_t  RESERVED55[22];
  __IO uint32_t  PCWD;                              /*!< Watchdog Timer Power Control                                          */
  __IO uint32_t  PCTIMER;                           /*!< 16/32-Bit General-Purpose Timer Power Control                         */
  __IO uint32_t  PCGPIO;                            /*!< General-Purpose Input/Output Power Control                            */
  __IO uint32_t  PCDMA;                             /*!< Micro Direct Memory Access Power Control                              */
  __IO uint32_t  PCEPI;                             /*!< External Peripheral Interface Power Control                           */
  __IO uint32_t  PCHIB;                             /*!< Hibernation Power Control                                             */
  __IO uint32_t  PCUART;                            /*!< Universal Asynchronous Receiver/Transmitter Power Control             */
  __IO uint32_t  PCSSI;                             /*!< Synchronous Serial Interface Power Control                            */
  __IO uint32_t  PCI2C;                             /*!< Inter-Integrated Circuit Power Control                                */
  __I  uint32_t  RESERVED56;
  __IO uint32_t  PCUSB;                             /*!< Universal Serial Bus Power Control                                    */
  __I  uint32_t  RESERVED57[3];
  __IO uint32_t  PCADC;                             /*!< Analog-to-Digital Converter Power Control                             */
  __IO uint32_t  PCACMP;                            /*!< Analog Comparator Power Control                                       */
  __I  uint32_t  RESERVED58[2];
  __IO uint32_t  PCLPC;                             /*!< Low Pin Count Interface Power Control                                 */
  __I  uint32_t  RESERVED59;
  __IO uint32_t  PCPECI;                            /*!< Platform Environment Control Interface Power Control                  */
  __IO uint32_t  PCFAN;                             /*!< Fan Power Control                                                     */
  __IO uint32_t  PCEEPROM;                          /*!< EEPROM Power Control                                                  */
  __I  uint32_t  RESERVED60[6];
  __IO uint32_t  PCCCM;                             /*!< CRC and Cryptographic Modules Power Control                           */
  __I  uint32_t  RESERVED61[8];
  __IO uint32_t  PCOWIRE;                           /*!< 1-Wire Power Control                                                  */
  __IO uint32_t  PCEMAC;                            /*!< Ethernet MAC Power Control                                            */
  __I  uint32_t  RESERVED62;
  __IO uint32_t  PCHIM;                             /*!< Human Interface Master Power Control                                  */
  __I  uint32_t  RESERVED63[22];
  __IO uint32_t  PRWD;                              /*!< Watchdog Timer Peripheral Ready                                       */
  __IO uint32_t  PRTIMER;                           /*!< Timer Peripheral Ready                                                */
  __IO uint32_t  PRGPIO;                            /*!< General-Purpose Input/Output Peripheral Ready                         */
  __IO uint32_t  PRDMA;                             /*!< Micro Direct Memory Access Peripheral Ready                           */
  __IO uint32_t  PREPI;                             /*!< EPI Peripheral Ready                                                  */
  __IO uint32_t  PRHIB;                             /*!< Hibernation Peripheral Ready                                          */
  __IO uint32_t  PRUART;                            /*!< Universal Asynchronous Receiver/Transmitter Peripheral Ready          */
  __IO uint32_t  PRSSI;                             /*!< Synchronous Serial Interface Peripheral Ready                         */
  __IO uint32_t  PRI2C;                             /*!< Inter-Integrated Circuit Peripheral Ready                             */
  __I  uint32_t  RESERVED64;
  __IO uint32_t  PRUSB;                             /*!< Universal Serial Bus Peripheral Ready                                 */
  __I  uint32_t  RESERVED65[3];
  __IO uint32_t  PRADC;                             /*!< Analog-to-Digital Converter Peripheral Ready                          */
  __IO uint32_t  PRACMP;                            /*!< Analog Comparator Peripheral Ready                                    */
  __I  uint32_t  RESERVED66[2];
  __IO uint32_t  PRLPC;                             /*!< Low Pin Count Interface Peripheral Ready                              */
  __I  uint32_t  RESERVED67;
  __IO uint32_t  PRPECI;                            /*!< Platform Environment Control Interface Peripheral Ready               */
  __IO uint32_t  PRFAN;                             /*!< Fan Peripheral Ready                                                  */
  __IO uint32_t  PREEPROM;                          /*!< EEPROM Peripheral Ready                                               */
  __I  uint32_t  RESERVED68[6];
  __IO uint32_t  PRCCM;                             /*!< CRC and Cryptographic Modules Peripheral Ready                        */
  __I  uint32_t  RESERVED69[8];
  __IO uint32_t  PROWIRE;                           /*!< One-Wire Peripheral Ready                                             */
  __IO uint32_t  PREMAC;                            /*!< Ethernet MAC Peripheral Ready                                         */
  __I  uint32_t  RESERVED70;
  __IO uint32_t  PRHIM;                             /*!< Human Interface Master Peripheral Ready                               */
} SYSCTL_Type;


/* ================================================================================ */
/* ================                      UDMA                      ================ */
/* ================================================================================ */


/**
  * @brief Register map for UDMA peripheral (UDMA)
  */

typedef struct {                                    /*!< UDMA Structure                                                        */
  __IO uint32_t  STAT;                              /*!< DMA Status                                                            */
  __O  uint32_t  CFG;                               /*!< DMA Configuration                                                     */
  __IO uint32_t  CTLBASE;                           /*!< DMA Channel Control Base Pointer                                      */
  __IO uint32_t  ALTBASE;                           /*!< DMA Alternate Channel Control Base Pointer                            */
  __IO uint32_t  WAITSTAT;                          /*!< DMA Channel Wait-on-Request Status                                    */
  __O  uint32_t  SWREQ;                             /*!< DMA Channel Software Request                                          */
  __IO uint32_t  USEBURSTSET;                       /*!< DMA Channel Useburst Set                                              */
  __O  uint32_t  USEBURSTCLR;                       /*!< DMA Channel Useburst Clear                                            */
  __IO uint32_t  REQMASKSET;                        /*!< DMA Channel Request Mask Set                                          */
  __O  uint32_t  REQMASKCLR;                        /*!< DMA Channel Request Mask Clear                                        */
  __IO uint32_t  ENASET;                            /*!< DMA Channel Enable Set                                                */
  __O  uint32_t  ENACLR;                            /*!< DMA Channel Enable Clear                                              */
  __IO uint32_t  ALTSET;                            /*!< DMA Channel Primary Alternate Set                                     */
  __O  uint32_t  ALTCLR;                            /*!< DMA Channel Primary Alternate Clear                                   */
  __IO uint32_t  PRIOSET;                           /*!< DMA Channel Priority Set                                              */
  __O  uint32_t  PRIOCLR;                           /*!< DMA Channel Priority Clear                                            */
  __I  uint32_t  RESERVED0[3];
  __IO uint32_t  ERRCLR;                            /*!< DMA Bus Error Clear                                                   */
  __I  uint32_t  RESERVED1[300];
  __IO uint32_t  CHASGN;                            /*!< DMA Channel Assignment                                                */
  __I  uint32_t  RESERVED2[3];
  __IO uint32_t  CHMAP0;                            /*!< DMA Channel Map Select 0                                              */
  __IO uint32_t  CHMAP1;                            /*!< DMA Channel Map Select 1                                              */
  __IO uint32_t  CHMAP2;                            /*!< DMA Channel Map Select 2                                              */
  __IO uint32_t  CHMAP3;                            /*!< DMA Channel Map Select 3                                              */
} UDMA_Type;


/* ================================================================================ */
/* ================                      CCM0                      ================ */
/* ================================================================================ */


/**
  * @brief Register map for CCM0 peripheral (CCM0)
  */

typedef struct {                                    /*!< CCM0 Structure                                                        */
  __I  uint32_t  RESERVED0[256];
  __IO uint32_t  CRCCTRL;                           /*!< CRC Control                                                           */
  __I  uint32_t  RESERVED1[3];
  __IO uint32_t  CRCSEED;                           /*!< CRC SEED/Context                                                      */
  __IO uint32_t  CRCDIN;                            /*!< CRC Data Input                                                        */
  __IO uint32_t  CRCRSLTPP;                         /*!< CRC Post Processing Result                                            */
} CCM0_Type;


/* ================================================================================ */
/* ================                     SHAMD5                     ================ */
/* ================================================================================ */


/**
  * @brief Register map for SHAMD5 peripheral (SHAMD5)
  */

typedef struct {                                    /*!< SHAMD5 Structure                                                      */
  __IO uint32_t  ODIGEST_A;                         /*!< SHA Secure Outer Digest A                                             */
  __IO uint32_t  ODIGEST_B;                         /*!< SHA Secure Outer Digest B                                             */
  __IO uint32_t  ODIGEST_C;                         /*!< SHA Secure Outer Digest C                                             */
  __IO uint32_t  ODIGEST_D;                         /*!< SHA Secure Outer Digest D                                             */
  __IO uint32_t  ODIGEST_E;                         /*!< SHA Secure Outer Digest E                                             */
  __IO uint32_t  ODIGEST_F;                         /*!< SHA Secure Outer Digest F                                             */
  __IO uint32_t  ODIGEST_G;                         /*!< SHA Secure Outer Digest G                                             */
  __IO uint32_t  ODIGEST_H;                         /*!< SHA Secure Outer Digest H                                             */
  __IO uint32_t  IDIGEST_A;                         /*!< SHA Secure Inner Digest A                                             */
  __IO uint32_t  IDIGEST_B;                         /*!< SHA Secure Inner Digest B                                             */
  __IO uint32_t  IDIGEST_C;                         /*!< SHA Secure Inner Digest C                                             */
  __IO uint32_t  IDIGEST_D;                         /*!< SHA Secure Inner Digest D                                             */
  __IO uint32_t  IDIGEST_E;                         /*!< SHA Secure Inner Digest E                                             */
  __IO uint32_t  IDIGEST_F;                         /*!< SHA Secure Inner Digest F                                             */
  __IO uint32_t  IDIGEST_G;                         /*!< SHA Secure Inner Digest G                                             */
  __IO uint32_t  IDIGEST_H;                         /*!< SHA Secure Inner Digest H                                             */
  __IO uint32_t  DIGEST_COUNT;                      /*!< SHA Secure Digest Count                                               */
  __IO uint32_t  MODE;                              /*!< SHA Secure Mode                                                       */
  __IO uint32_t  LENGTH;                            /*!< SHA Secure Mode                                                       */
  __I  uint32_t  RESERVED0[13];
  __IO uint32_t  DATA_0_IN;                         /*!< SHA Secure Data 0 Input                                               */
  __IO uint32_t  DATA_1_IN;                         /*!< SHA Secure Data 1 Input                                               */
  __IO uint32_t  DATA_2_IN;                         /*!< SHA Secure Data 2 Input                                               */
  __IO uint32_t  DATA_3_IN;                         /*!< SHA Secure Data 3 Input                                               */
  __IO uint32_t  DATA_4_IN;                         /*!< SHA Secure Data 4 Input                                               */
  __IO uint32_t  DATA_5_IN;                         /*!< SHA Secure Data 5 Input                                               */
  __IO uint32_t  DATA_6_IN;                         /*!< SHA Secure Data 6 Input                                               */
  __IO uint32_t  DATA_7_IN;                         /*!< SHA Secure Data 7 Input                                               */
  __IO uint32_t  DATA_8_IN;                         /*!< SHA Secure Data 8 Input                                               */
  __IO uint32_t  DATA_9_IN;                         /*!< SHA Secure Data 9 Input                                               */
  __IO uint32_t  DATA_10_IN;                        /*!< SHA Secure Data 10 Input                                              */
  __IO uint32_t  DATA_11_IN;                        /*!< SHA Secure Data 11 Input                                              */
  __IO uint32_t  DATA_12_IN;                        /*!< SHA Secure Data 12 Input                                              */
  __IO uint32_t  DATA_13_IN;                        /*!< SHA Secure Data 13 Input                                              */
  __IO uint32_t  DATA_14_IN;                        /*!< SHA Secure Data 14 Input                                              */
  __IO uint32_t  DATA_15_IN;                        /*!< SHA Secure Data 15 Input                                              */
  __I  uint32_t  RESERVED1[16];
  __IO uint32_t  REVISION;                          /*!< SHA Secure Revision                                                   */
  __I  uint32_t  RESERVED2[3];
  __IO uint32_t  SYSCONFIG;                         /*!< SHA Secure System Configuration                                       */
  __IO uint32_t  SYSSTATUS;                         /*!< SHA Secure System Status                                              */
  __IO uint32_t  IRQSTATUS;                         /*!< SHA Secure Interrupt Status                                           */
  __IO uint32_t  IRQENABLE;                         /*!< SHA Secure Interrupt Enable                                           */
} SHAMD5_Type;


/* ================================================================================ */
/* ================                       AES                      ================ */
/* ================================================================================ */


/**
  * @brief Register map for AES peripheral (AES)
  */

typedef struct {                                    /*!< AES Structure                                                         */
  __IO uint32_t  KEY2_6;                            /*!< AES Secure Key 2_6                                                    */
  __IO uint32_t  KEY2_7;                            /*!< AES Secure Key 2_7                                                    */
  __IO uint32_t  KEY2_4;                            /*!< AES Secure Key 2_4                                                    */
  __IO uint32_t  KEY2_5;                            /*!< AES Secure Key 2_5                                                    */
  __IO uint32_t  KEY2_2;                            /*!< AES Secure Key 2_2                                                    */
  __IO uint32_t  KEY2_3;                            /*!< AES Secure Key 2_3                                                    */
  __IO uint32_t  KEY2_0;                            /*!< AES Secure Key 2_0                                                    */
  __IO uint32_t  KEY2_1;                            /*!< AES Secure Key 2_1                                                    */
  __IO uint32_t  KEY1_6;                            /*!< AES Secure Key 1_6                                                    */
  __IO uint32_t  KEY1_7;                            /*!< AES Secure Key 1_7                                                    */
  __IO uint32_t  KEY1_4;                            /*!< AES Secure Key 1_4                                                    */
  __IO uint32_t  KEY1_5;                            /*!< AES Secure Key 1_5                                                    */
  __IO uint32_t  KEY1_2;                            /*!< AES Secure Key 1_2                                                    */
  __IO uint32_t  KEY1_3;                            /*!< AES Secure Key 1_3                                                    */
  __IO uint32_t  KEY1_0;                            /*!< AES Secure Key 1_0                                                    */
  __IO uint32_t  KEY1_1;                            /*!< AES Secure Key 1_1                                                    */
  __IO uint32_t  IV_IN_0;                           /*!< AES Secure Initialization Vector Input 0                              */
  __IO uint32_t  IV_IN_1;                           /*!< AES Secure Initialization Vector Input 1                              */
  __IO uint32_t  IV_IN_2;                           /*!< AES Secure Initialization Vector Input 2                              */
  __IO uint32_t  IV_IN_3;                           /*!< AES Initialization Vector Input 3                                     */
  __IO uint32_t  CTRL;                              /*!< AES Secure Control                                                    */
  __IO uint32_t  C_LENGTH_0;                        /*!< AES Secure Crypto Data Length 0                                       */
  __IO uint32_t  C_LENGTH_1;                        /*!< AES Secure Crypto Data Length 1                                       */
  __IO uint32_t  AUTH_LENGTH;                       /*!< AES Secure Authentication Data Length                                 */
  __IO uint32_t  DATA_IN_0;                         /*!< AES Secure Data R/W Plaintext/Ciphertext 0                            */
  __IO uint32_t  DATA_IN_1;                         /*!< AES Secure Data R/W Plaintext/Ciphertext 1                            */
  __IO uint32_t  DATA_IN_2;                         /*!< AES Secure Data R/W Plaintext/Ciphertext 2                            */
  __IO uint32_t  DATA_IN_3;                         /*!< AES Secure Data R/W Plaintext/Ciphertext 3                            */
  __IO uint32_t  TAG_OUT_0;                         /*!< AES Secure Hash Tag Out 0                                             */
  __IO uint32_t  TAG_OUT_1;                         /*!< AES Secure Hash Tag Out 1                                             */
  __IO uint32_t  TAG_OUT_2;                         /*!< AES Secure Hash Tag Out 2                                             */
  __IO uint32_t  TAG_OUT_3;                         /*!< AES Secure Hash Tag Out 3                                             */
  __IO uint32_t  REVISION;                          /*!< AES Secure IP Revision Identifier                                     */
  __IO uint32_t  SYSCONFIG;                         /*!< AES Secure System Configuration                                       */
  __IO uint32_t  SYSSTATUS;                         /*!< AES Secure System Status                                              */
  __IO uint32_t  IRQSTATUS;                         /*!< AES Secure Interrupt Status                                           */
  __IO uint32_t  IRQENABLE;                         /*!< AES Secure Interrupt Enable                                           */
  __IO uint32_t  DIRTYBITS;                         /*!< AES Secure Dirty Bits                                                 */
} AES_Type;


/* ================================================================================ */
/* ================                       DES                      ================ */
/* ================================================================================ */


/**
  * @brief Register map for DES peripheral (DES)
  */

typedef struct {                                    /*!< DES Structure                                                         */
  __IO uint32_t  KEY3_L;                            /*!< DES3DES Key 3 LSW for 192-bit key                                     */
  __IO uint32_t  KEY3_H;                            /*!< DES3DES Key 3 MSW for 192-bit key                                     */
  __IO uint32_t  KEY2_L;                            /*!< DES3DES Key 2 LSW for 128-bit key                                     */
  __IO uint32_t  KEY2_H;                            /*!< DES3DES Key 2 MSW for 128-bit key                                     */
  __IO uint32_t  KEY1_L;                            /*!< DES3DES Key 1 LSW for 64-bit key                                      */
  __IO uint32_t  KEY1_H;                            /*!< DES3DES Key 1 MSW for 64-bit key                                      */
  __IO uint32_t  IV_L;                              /*!< DES3DES Secure Initialization Vector                                  */
  __IO uint32_t  IV_H;                              /*!< DES3DES Secure Initialization Vector                                  */
  __IO uint32_t  CTRL;                              /*!< DES3DES Secure Control                                                */
  __IO uint32_t  LENGTH;                            /*!< DES3DES Secure Cryptographic Data Length                              */
  __IO uint32_t  DATA_L;                            /*!< DES3DES Secure LSW Data R/W                                           */
  __IO uint32_t  DATA_H;                            /*!< DES3DES Secure MSW Data R/W                                           */
  __IO uint32_t  REVISION;                          /*!< DES3DES Secure Revision Number                                        */
  __IO uint32_t  SYSCONFIG;                         /*!< DES3DES Secure System Configuration                                   */
  __IO uint32_t  SYSSTATUS;                         /*!< DES3DES Secure System Status                                          */
  __IO uint32_t  IRQSTATUS;                         /*!< DES3DES Secure Interrupt Status                                       */
  __IO uint32_t  IRQENABLE;                         /*!< DES3DES Secure Interrupt Enable                                       */
  __IO uint32_t  DIRTYBITS;                         /*!< DES3DES Secure Dirty Bits                                             */
} DES_Type;


/* --------------------  End of section using anonymous unions  ------------------- */
#if defined(__CC_ARM)
  #pragma pop
#elif defined(__ICCARM__)
  /* leave anonymous unions enabled */
#elif defined(__GNUC__)
  /* anonymous unions are enabled by default */
#elif defined(__TMS470__)
  /* anonymous unions are enabled by default */
#elif defined(__TASKING__)
  #pragma warning restore
#else
  #warning Not supported compiler type
#endif




/* ================================================================================ */
/* ================              Peripheral memory map             ================ */
/* ================================================================================ */

#define WATCHDOG0_BASE                  0x40000000UL
#define WATCHDOG1_BASE                  0x40001000UL
#define SSI0_BASE                       0x40008000UL
#define SSI1_BASE                       0x40009000UL
#define SSI2_BASE                       0x4000A000UL
#define SSI3_BASE                       0x4000B000UL
#define UART0_BASE                      0x4000C000UL
#define UART1_BASE                      0x4000D000UL
#define UART2_BASE                      0x4000E000UL
#define UART3_BASE                      0x4000F000UL
#define UART4_BASE                      0x40010000UL
#define UART5_BASE                      0x40011000UL
#define UART6_BASE                      0x40012000UL
#define UART7_BASE                      0x40013000UL
#define I2C0_BASE                       0x40020000UL
#define I2C1_BASE                       0x40021000UL
#define I2C2_BASE                       0x40022000UL
#define I2C3_BASE                       0x40023000UL
#define TIMER0_BASE                     0x40030000UL
#define TIMER1_BASE                     0x40031000UL
#define TIMER2_BASE                     0x40032000UL
#define TIMER3_BASE                     0x40033000UL
#define TIMER4_BASE                     0x40034000UL
#define TIMER5_BASE                     0x40035000UL
#define ADC0_BASE                       0x40038000UL
#define ADC1_BASE                       0x40039000UL
#define COMP_BASE                       0x4003C000UL
#define USB0_BASE                       0x40050000UL
#define GPIOA_AHB_BASE                  0x40058000UL
#define GPIOB_AHB_BASE                  0x40059000UL
#define GPIOC_AHB_BASE                  0x4005A000UL
#define GPIOD_AHB_BASE                  0x4005B000UL
#define GPIOE_AHB_BASE                  0x4005C000UL
#define GPIOF_AHB_BASE                  0x4005D000UL
#define GPIOG_AHB_BASE                  0x4005E000UL
#define GPIOH_AHB_BASE                  0x4005F000UL
#define GPIOJ_AHB_BASE                  0x40060000UL
#define GPIOK_BASE                      0x40061000UL
#define GPIOL_BASE                      0x40062000UL
#define GPIOM_BASE                      0x40063000UL
#define GPION_BASE                      0x40064000UL
#define GPIOP_BASE                      0x40065000UL
#define GPIOQ_BASE                      0x40066000UL
#define GPIOR_BASE                      0x40067000UL
#define GPIOS_BASE                      0x40068000UL
#define GPIOT_BASE                      0x40069000UL
#define LPCB0_BASE                      0x40080000UL
#define FAN0_BASE                       0x40084000UL
#define FAN1_BASE                       0x40085000UL
#define EEPROM_BASE                     0x400AF000UL
#define PECI0_BASE                      0x400B0000UL
#define ONEWIRE0_BASE                   0x400B6000UL
#define HIM0_BASE                       0x400B7000UL
#define I2C8_BASE                       0x400B8000UL
#define I2C9_BASE                       0x400B9000UL
#define I2C4_BASE                       0x400C0000UL
#define I2C5_BASE                       0x400C1000UL
#define I2C6_BASE                       0x400C2000UL
#define I2C7_BASE                       0x400C3000UL
#define EPI0_BASE                       0x400D0000UL
#define TIMER6_BASE                     0x400E0000UL
#define TIMER7_BASE                     0x400E1000UL
#define EMAC0_BASE                      0x400EC000UL
#define SYSEXC_BASE                     0x400F9000UL
#define HIB_BASE                        0x400FC000UL
#define FLASH_CTRL_BASE                 0x400FD000UL
#define SYSCTL_BASE                     0x400FE000UL
#define UDMA_BASE                       0x400FF000UL
#define CCM0_BASE                       0x44030000UL
#define SHAMD5_BASE                     0x44034000UL
#define AES_BASE                        0x44036000UL
#define DES_BASE                        0x44038000UL


/* ================================================================================ */
/* ================             Peripheral declaration             ================ */
/* ================================================================================ */

#define WATCHDOG0                       ((WATCHDOG0_Type          *) WATCHDOG0_BASE)
#define WATCHDOG1                       ((WATCHDOG0_Type          *) WATCHDOG1_BASE)
#define SSI0                            ((SSI0_Type               *) SSI0_BASE)
#define SSI1                            ((SSI0_Type               *) SSI1_BASE)
#define SSI2                            ((SSI0_Type               *) SSI2_BASE)
#define SSI3                            ((SSI0_Type               *) SSI3_BASE)
#define UART0                           ((UART0_Type              *) UART0_BASE)
#define UART1                           ((UART0_Type              *) UART1_BASE)
#define UART2                           ((UART0_Type              *) UART2_BASE)
#define UART3                           ((UART0_Type              *) UART3_BASE)
#define UART4                           ((UART0_Type              *) UART4_BASE)
#define UART5                           ((UART0_Type              *) UART5_BASE)
#define UART6                           ((UART0_Type              *) UART6_BASE)
#define UART7                           ((UART0_Type              *) UART7_BASE)
#define I2C0                            ((I2C0_Type               *) I2C0_BASE)
#define I2C1                            ((I2C0_Type               *) I2C1_BASE)
#define I2C2                            ((I2C0_Type               *) I2C2_BASE)
#define I2C3                            ((I2C0_Type               *) I2C3_BASE)
#define TIMER0                          ((TIMER0_Type             *) TIMER0_BASE)
#define TIMER1                          ((TIMER0_Type             *) TIMER1_BASE)
#define TIMER2                          ((TIMER0_Type             *) TIMER2_BASE)
#define TIMER3                          ((TIMER0_Type             *) TIMER3_BASE)
#define TIMER4                          ((TIMER0_Type             *) TIMER4_BASE)
#define TIMER5                          ((TIMER0_Type             *) TIMER5_BASE)
#define ADC0                            ((ADC0_Type               *) ADC0_BASE)
#define ADC1                            ((ADC0_Type               *) ADC1_BASE)
#define COMP                            ((COMP_Type               *) COMP_BASE)
#define USB0                            ((USB0_Type               *) USB0_BASE)
#define GPIOA_AHB                       ((GPIOA_AHB_Type          *) GPIOA_AHB_BASE)
#define GPIOB_AHB                       ((GPIOA_AHB_Type          *) GPIOB_AHB_BASE)
#define GPIOC_AHB                       ((GPIOA_AHB_Type          *) GPIOC_AHB_BASE)
#define GPIOD_AHB                       ((GPIOA_AHB_Type          *) GPIOD_AHB_BASE)
#define GPIOE_AHB                       ((GPIOA_AHB_Type          *) GPIOE_AHB_BASE)
#define GPIOF_AHB                       ((GPIOA_AHB_Type          *) GPIOF_AHB_BASE)
#define GPIOG_AHB                       ((GPIOA_AHB_Type          *) GPIOG_AHB_BASE)
#define GPIOH_AHB                       ((GPIOA_AHB_Type          *) GPIOH_AHB_BASE)
#define GPIOJ_AHB                       ((GPIOA_AHB_Type          *) GPIOJ_AHB_BASE)
#define GPIOK                           ((GPIOA_AHB_Type          *) GPIOK_BASE)
#define GPIOL                           ((GPIOA_AHB_Type          *) GPIOL_BASE)
#define GPIOM                           ((GPIOA_AHB_Type          *) GPIOM_BASE)
#define GPION                           ((GPIOA_AHB_Type          *) GPION_BASE)
#define GPIOP                           ((GPIOA_AHB_Type          *) GPIOP_BASE)
#define GPIOQ                           ((GPIOA_AHB_Type          *) GPIOQ_BASE)
#define GPIOR                           ((GPIOA_AHB_Type          *) GPIOR_BASE)
#define GPIOS                           ((GPIOA_AHB_Type          *) GPIOS_BASE)
#define GPIOT                           ((GPIOA_AHB_Type          *) GPIOT_BASE)
#define LPCB0                           ((LPCB0_Type              *) LPCB0_BASE)
#define FAN0                            ((FAN0_Type               *) FAN0_BASE)
#define FAN1                            ((FAN0_Type               *) FAN1_BASE)
#define EEPROM                          ((EEPROM_Type             *) EEPROM_BASE)
#define PECI0                           ((PECI0_Type              *) PECI0_BASE)
#define ONEWIRE0                        ((ONEWIRE0_Type           *) ONEWIRE0_BASE)
#define HIM0                            ((HIM0_Type               *) HIM0_BASE)
#define I2C8                            ((I2C0_Type               *) I2C8_BASE)
#define I2C9                            ((I2C0_Type               *) I2C9_BASE)
#define I2C4                            ((I2C0_Type               *) I2C4_BASE)
#define I2C5                            ((I2C0_Type               *) I2C5_BASE)
#define I2C6                            ((I2C0_Type               *) I2C6_BASE)
#define I2C7                            ((I2C0_Type               *) I2C7_BASE)
#define EPI0                            ((EPI0_Type               *) EPI0_BASE)
#define TIMER6                          ((TIMER0_Type             *) TIMER6_BASE)
#define TIMER7                          ((TIMER0_Type             *) TIMER7_BASE)
#define EMAC0                           ((EMAC0_Type              *) EMAC0_BASE)
#define SYSEXC                          ((SYSEXC_Type             *) SYSEXC_BASE)
#define HIB                             ((HIB_Type                *) HIB_BASE)
#define FLASH_CTRL                      ((FLASH_CTRL_Type         *) FLASH_CTRL_BASE)
#define SYSCTL                          ((SYSCTL_Type             *) SYSCTL_BASE)
#define UDMA                            ((UDMA_Type               *) UDMA_BASE)
#define CCM0                            ((CCM0_Type               *) CCM0_BASE)
#define SHAMD5                          ((SHAMD5_Type             *) SHAMD5_BASE)
#define AES                             ((AES_Type                *) AES_BASE)
#define DES                             ((DES_Type                *) DES_BASE)


/** @} */ /* End of group Device_Peripheral_Registers */
/** @} */ /* End of group TM4E129BNCZAD */
/** @} */ /* End of group Texas Instruments */

#ifdef __cplusplus
}
#endif


#endif  /* TM4E129BNCZAD_H */

