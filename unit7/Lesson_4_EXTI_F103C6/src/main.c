#include "stm32f103_X6.h"
#include "mcal_stm32f103X6_gpio.h"
#include "mcal_stm32f103c6_exti.h"
#include "hal_KeyPad.h"
#include "hal_lcd.h"

unsigned int IQR_FLAG = 0;

void CLOCK_INIT(void)
{
    RCC_GPIOA_CLK_EN;
    RCC_GPIOB_CLK_EN;
    RCC_AFIO_CLK_EN;
}
void wait_ms(uint32_t time)
{
    uint32_t i, j;
    for (i = 0; i < time; i++)
        for (j = 0; j < 255; j++);
}
void EXTI9callback()
{
    IQR_FLAG = 1;
    Write_String_LCD("IRQ EXTI9 is happend _|- ");
    wait_ms(1000);
}

int main(void)
{
    CLOCK_INIT();
    init_LCD();
    Clear_LCD();
    Write_String_LCD("hello , keypad and LCD in ready");
    wait_ms(2000);
    EXTI_PinConfig_t EXTI_CFG;
    MCAL_EXTI_GPIO_Init(&EXTI_CFG, EXTI_P(9, GPIOB), EXTI_Trigger_RISING, EXTI_IRQ_Enable, EXTI9callback);
    IQR_FLAG = 1;
    while (1)
    {
        if (IQR_FLAG)
        {
            Clear_LCD();
            IQR_FLAG = 0;
        }
    }
}