#include "Z:\Program_Files\Freq_used\utilities\Platform_Types.h"
#include "Z:\Program_Files\Freq_used\utilities\Bit_Math.h"

// GPIO configrations
// GpioA
#define GPIOA_CRL *(vuint32 *)(PORTA_BASE + 0x00)
#define GPIOA_CRH *(vuint32 *)(PORTA_BASE + 0x04)
#define GPIOA_ODR *(vuint32 *)(PORTA_BASE + 0x0C)
#define GPIOA_IDR *(vuint32 *)(PORTA_BASE + 0x08)
// GpioB
#define GPIOB_CRL *(vuint32 *)(PORTB_BASE + 0x00)
#define GPIOB_CRH *(vuint32 *)(PORTB_BASE + 0x04)
#define GPIOB_ODR *(vuint32 *)(PORTB_BASE + 0x0C)

// PortA and B bases
#define PORTA_BASE 0x40010800
#define PORTB_BASE 0x40010C00
// clock confifrations
#define RCC_BASE 0x40021000
#define RCC_APB2ENR *(vuint32 *)(RCC_BASE + 0x18)
#define RCC_CFGR *(vuint32 *)(RCC_BASE + 0x04)

#define delay                         \
    for (uint32 i = 0; i < 8000; i++) \
        ;

void GPIO_init_()
{
    // declaring pin 1 to be input mode as floating inputs
    GPIOA_CRL |= (0b0100 << 4);
    // declaring pin 13 to be floating inputs
    GPIOA_CRH |= (0b0100 << 20);
    // pin 1 in portB  push pull output
    GPIOB_CRL |= (0b0001 << 4);
    // declaring pin 13 to be floating inputs
    GPIOB_CRH |= (0b0001 << 20);
}
void Clock_init()
{
    // set on the clock for PORTA
    RCC_APB2ENR |= (1 << 2);
    // set on the clock for PORTB
    RCC_APB2ENR |= (1 << 3);
}

int main()
{
    Clock_init();
    GPIO_init_();
    while (1)
    {
        int bit_status = READ_BIT(GPIOA_IDR, 1);
        // PORTA Pin 1 connected to External push up resistor
        // take action when read 0 from pin
        if (bit_status == 0)
        {
            TOG_BIT(GPIOB_ODR, 1);
            while (bit_status == 0)
                ; // while pressing is still
        }
        if (bit_status == 1)
        {
            TOG_BIT(GPIOB_ODR, 1);
        }
    }
    delay
    return 0;
}
