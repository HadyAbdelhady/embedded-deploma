#ifndef INC_STM32F103X6_H_
#define INC_STM32F103X6_H_
//-----------------------------
// Includes
//-----------------------------
#include "stdlib.h"
#include "stdint.h"
//-----------------------------
// Base addresses for Memories
//-----------------------------
#define Flash_Memory_Base 0x08000000UL
#define System_Memory_Base 0x1FFFF000UL
#define SRam_Memory_Base 0x20000000UL

#define Peripherals_Base 0x40000000
#define Cortex_M3_Internal_Peripherals 0xE0000000
//========================================================
//-----------------------------
// Base addresses for AHB BUS Peripherals
//-----------------------------
// RCC
#define RCC_Base 0x40021000UL
//-----------------------------
// Base addresses for APB2 BUS Peripherals
//-----------------------------
// GPIO
// GPIO A B fully included
#define GPIOA_Base 0x40010800UL
#define GPIOB_Base 0x40010C00UL
// GPIO C D Partially
#define GPIOC_Base 0x40011000UL
#define GPIOD_Base 0x40011400UL
// GPIO E Excluded
#define GPIOE_Base 0x40011800UL
// EXTI
#define EXTI_Base 0x40010400UL
// AFIO
#define AFIO_Base 0x40010000UL
// NVIC
#define NVIC_BASE 0xE000E100UL
//USART
#define USART1_BASE                              0x40013800UL



//-----------------------------
//Base addresses for APB1 BUS Peripherals
//-----------------------------
#define USART2_BASE                              0x40004400UL
#define USART3_BASE                              0x40004800UL

//========================================================
//-*-*-*-*-*-*-*-*-*-*-*-
// Peripheral register:
//-*-*-*-*-*-*-*-*-*-*-*

//-*-*-*-*-*-*-*-*-*-*-*-
// Peripheral register:GPIO
//-*-*-*-*-*-*-*-*-*-*-*
typedef struct
{
	volatile uint32_t CRL;
	volatile uint32_t CRH;
	volatile uint32_t IDR;
	volatile uint32_t ODR;
	volatile uint32_t BSRR;
	volatile uint32_t BRR;
	volatile uint32_t LCKR;

} S_GPIO_t;
//-*-*-*-*-*-*-*-*-*-*-*-
// Peripheral register:RCC
//-*-*-*-*-*-*-*-*-*-*-*
typedef struct 
{
	volatile uint32_t RCC_CR;
	volatile uint32_t RCC_CFGR;
	volatile uint32_t RCC_CIR;
	volatile uint32_t RCC_APB2RSTR;
	volatile uint32_t RCC_APB1RSTR;
	volatile uint32_t RCC_AHBENR;
	volatile uint32_t RCC_APB2ENR;
	volatile uint32_t RCC_APB1ENR;
	volatile uint32_t RCC_BDCR;
	volatile uint32_t RCC_CSR;
	volatile uint32_t RCC_AHBSTR;
	volatile uint32_t RCC_CFGR2;
} S_RCC_t;
//-*-*-*-*-*-*-*-*-*-*-*-
// Peripheral register:EXTI
//-*-*-*-*-*-*-*-*-*-*-*
typedef struct
{
	volatile uint32_t EXTI_IMR;
	volatile uint32_t EXTI_EMR;
	volatile uint32_t EXTI_RTSR;
	volatile uint32_t EXTI_FTSR;
	volatile uint32_t EXTI_SWIER;
	volatile uint32_t EXTI_PR;
} S_EXTI_t;
//-*-*-*-*-*-*-*-*-*-*-*-
// Peripheral register:AFIO
//-*-*-*-*-*-*-*-*-*-*-*
typedef struct
{
	volatile uint32_t AFIO_EVCR;
	volatile uint32_t AFIO_MAPR;
	volatile uint32_t EXTICR[4];
	volatile uint32_t Reserved;
	volatile uint32_t AFIO_MAPR2;

} S_AFIO_t;


//-*-*-*-*-*-*-*-*-*-*-*-
//Peripheral register: USART
//-*-*-*-*-*-*-*-*-*-*-*
typedef struct{
	volatile uint32_t SR;//0x00
	volatile uint32_t DR;//0x04
	volatile uint32_t BRR;//0x08
	volatile uint32_t CR1;//0x0C
	volatile uint32_t CR2;//0x10
	volatile uint32_t CR3;//0x14
	volatile uint32_t GTPR;//0x14

}S_USART_t;



//-*-*-*-*-*-*-*-*-*-*-*-
// Peripheral Instants:
//-*-*-*-*-*-*-*-*-*-*-*
#define GPIOA ((S_GPIO_t *)GPIOA_Base)
#define GPIOB ((S_GPIO_t *)GPIOB_Base)
#define GPIOC ((S_GPIO_t *)GPIOC_Base)
#define GPIOD ((S_GPIO_t *)GPIOD_Base)
#define GPIOE ((S_GPIO_t *)GPIOE_Base)

#define RCC ((S_RCC_t *)RCC_Base)

#define EXTI ((S_EXTI_t *)EXTI_Base)

#define AFIO ((S_AFIO_t *)AFIO_Base)

#define NVIC_ISER0 *(volatile uint32_t *)(NVIC_BASE + 0x000)
#define NVIC_ISER1 *(volatile uint32_t *)(NVIC_BASE + 0x004)
#define NVIC_ISER2 *(volatile uint32_t *)(NVIC_BASE + 0x008)
#define NVIC_ICER0 *(volatile uint32_t *)(NVIC_BASE + 0x080)
#define NVIC_ICER1 *(volatile uint32_t *)(NVIC_BASE + 0x084)
#define NVIC_ICER2 *(volatile uint32_t *)(NVIC_BASE + 0x088)

#define USART1			((S_USART_t*)USART1_BASE)
#define USART2			((S_USART_t*)USART2_BASE)
#define USART3			((S_USART_t*)USART3_BASE)


//========================================================

//-*-*-*-*-*-*-*-*-*-*-*-
// IVT Macros
//-*-*-*-*-*-*-*-*-*-*-*
// @ref IVT_IRQ_Number
#define EXTI0_IRQ 6
#define EXTI1_IRQ 7
#define EXTI2_IRQ 8
#define EXTI3_IRQ 9
#define EXTI4_IRQ 10
#define EXTI5_IRQ 23
#define EXTI6_IRQ 23
#define EXTI7_IRQ 23
#define EXTI8_IRQ 23
#define EXTI9_IRQ 23
#define EXTI10_IRQ 40
#define EXTI11_IRQ 40
#define EXTI12_IRQ 40
#define EXTI13_IRQ 40
#define EXTI14_IRQ 40
#define EXTI15_IRQ 40

//USART-IRQ
#define USART1_IRQ 			37
#define USART2_IRQ 			38
#define USART3_IRQ 			39


//-*-*-*-*-*-*-*-*-*-*-*-
// NVIC_IRQ Enable / Disable Macros:
//-*-*-*-*-*-*-*-*-*-*-*

#define NVIC_IRQ6_EXTI0_ENABLE 		(NVIC_ISER0 |= 1 << EXTI0_IRQ)
#define NVIC_IRQ7_EXTI1_ENABLE 		(NVIC_ISER0 |= 1 << EXTI1_IRQ)
#define NVIC_IRQ8_EXTI2_ENABLE 		(NVIC_ISER0 |= 1 << EXTI2_IRQ)
#define NVIC_IRQ9_EXTI3_ENABLE 		(NVIC_ISER0 |= 1 << EXTI3_IRQ)
#define NVIC_IRQ10_EXTI4_ENABLE 	(NVIC_ISER0 |= 1 << EXTI4_IRQ)
#define NVIC_IRQ23_EXTI5_9_ENABLE	(NVIC_ISER0 |= 1 << EXTI5_IRQ)
#define NVIC_IRQ40_EXTI10_15_ENABLE (NVIC_ISER1 |= 1 << 8) // 40-32

#define NVIC_IRQ6_EXTI0_DISABLE 	(NVIC_ICER0 |= 1 << EXTI0_IRQ)
#define NVIC_IRQ7_EXTI1_DISABLE 	(NVIC_ICER0 |= 1 << EXTI1_IRQ)
#define NVIC_IRQ8_EXTI2_DISABLE 	(NVIC_ICER0 |= 1 << EXTI2_IRQ)
#define NVIC_IRQ9_EXTI3_DISABLE 	(NVIC_ICER0 |= 1 << EXTI3_IRQ)
#define NVIC_IRQ10_EXTI4_DISABLE 	(NVIC_ICER0 |= 1 << EXTI4_IRQ)
#define NVIC_IRQ23_EXTI5_9_DISABLE	(NVIC_ICER0 |= 1 << EXTI5_IRQ)
#define NVIC_IRQ40_EXTI10_15_DISABLE (NVIC_ICER1 |= 1 << 8) // 40-32

//-*-*-*-*-*-*-*-*-*-*-*-
// clock enable Macros:
//-*-*-*-*-*-*-*-*-*-*-*

#define RCC_GPIOA_CLK_EN (RCC->RCC_APB2ENR |= (1 << 2))
#define RCC_GPIOB_CLK_EN (RCC->RCC_APB2ENR |= (1 << 3))
#define RCC_GPIOC_CLK_EN (RCC->RCC_APB2ENR |= (1 << 4))
#define RCC_GPIOD_CLK_EN (RCC->RCC_APB2ENR |= (1 << 5))
#define RCC_GPIOE_CLK_EN (RCC->RCC_APB2ENR |= (1 << 6))
#define RCC_AFIO_CLK_EN  (RCC->RCC_APB2ENR |= (1 << 0))

//Enable USART Clock
#define RCC_USART1_CLK_EN		(RCC->RCC_APB2ENR |=(1<<14))
#define RCC_USART2_CLK_EN	    (RCC->RCC_APB1ENR |=(1<<17))
#define RCC_USART3_CLK_EN		(RCC->RCC_APB1ENR |=(1<<18))

//RESET USART
#define RCC_USART1_RESET	    (RCC->RCC_APB2RSTR |=(1<<14))
#define RCC_USART2_RESET		(RCC->RCC_APB1RSTR |=(1<<17))
#define RCC_USART3_RESET		(RCC->RCC_APB1RSTR |=(1<<18))


//USART
//Enabled

#define NVIC_IRQ37_USART1_Enable 		       (NVIC_ISER1 |= 1<<(USART1_IRQ - 32))//BECAUSE YOU EXCEED 32 SO YOU IN REGISTER ISER1>>37(USART1_IRQ)-32
#define NVIC_IRQ37_USART2_Enable 		       (NVIC_ISER1 |= 1<<(USART2_IRQ - 32))
#define NVIC_IRQ37_USART3_Enable 		       (NVIC_ISER1 |= 1<<(USART3_IRQ - 32))

//Disabled
#define NVIC_IRQ37_USART1_Disable 		       (NVIC_ICER1 |= 1<<(USART1_IRQ - 32))//BECAUSE YOU EXCEED 32 SO YOU IN REGISTER ISER1>>37(USART1_IRQ)-32
#define NVIC_IRQ37_USART2_Disable 		       (NVIC_ICER1 |= 1<<(USART2_IRQ - 32))
#define NVIC_IRQ37_USART3_Disable 		       (NVIC_ICER1 |= 1<<(USART3_IRQ - 32))


#endif /* INC_STM32F103X8_H_ */