#ifndef __headers__
#define __headers__


#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

//interrupt addresses

#define EXTI_BASE	 0x40010400  //base
#define EXTI_IMR  	 *(volatile uint32_t *)(EXTI_BASE + 0x00) //interrupt mask register
#define EXTI_RTSR  	 *(volatile uint32_t *)(EXTI_BASE + 0x08) //rising detection register
#define EXTI_PR  	 *(volatile uint32_t *)(EXTI_BASE + 0x14) // pending register
#define NVIC_ISER0  	 *(volatile uint32_t *)(0xE000E100)   //interrupt controller for arm corterx m3
//doesnt i need sw interrup event?

// clock addresses

#define RCC_BASE  	 0x40021000  //base
#define RCC_APB2ENR  *(volatile uint32_t *)(RCC_BASE + 0x18) //apb2 bus enabler
#define RCC_CFGR  	 *(volatile uint32_t *)(RCC_BASE + 0x4)  //confegration
#define RCC_CR  	 *(volatile uint32_t *)(RCC_BASE)        // clear
//doesnt i need ahp adress?


// GPIO addresses

#define GPIOA_BASE 	 0x40010800
#define GPIOA_CRH	 *(volatile uint32_t *)(GPIOA_BASE + 0x04)
#define GPIOA_ODR	 *(volatile uint32_t *)(GPIOA_BASE + 0x0C)
#define GPIOA_CRL	 *(volatile uint32_t *)(GPIOA_BASE + 0x00)


#endif