#include "utilities.h"
void clock_init(void)
{
    // init clock for GPIOA
    RCC_APB2ENR |= 1 << 2;

    // init clock for GPIOA
    RCC_APB2ENR |= 1 << 0;

    // set PPRE2(bits 11:13) to 101:HCLK devided by 4
    RCC_CFGR |= (0b101 << 11);

    // set PPRE1(bits 8:10) to 100:HCLK devided by 2
    RCC_CFGR |= (0b100 << 8);
}

void GPIO_init(void)
{
    // input init
    GPIOA_CRL |= (1 << 2);
    // Init GPIOA
    GPIOA_CRH &= 0xFF0FFFFF;
    GPIOA_CRH |= 0x00200000;
}

void main()
{
    clock_init();
    GPIO_init();

    // enable interrupt mask on EXTI0
    EXTI_IMR |= (1 << 0);

    // enabling rising trigger
    EXTI_RTSR |= (1 << 0);

    // enable NVIC IRQ 6
    NVIC_ISER0 |= (1 << 6);

    while (1)
        ;
}
void EXTI0_IRQHandler(void)
{
    // toggle led
    GPIOA_ODR ^= (1 << 13);
    // clear pending
    EXTI_PR |= (1 << 0);
}