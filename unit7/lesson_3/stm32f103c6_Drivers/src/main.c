#include "stm32f103c6_gpio_driver.h"

void GPIO_init_()
{
    GPIO_Pin_Config_t P_cnfg;
    // declaring pin 1 to be input mode as floating inputs
    P_cnfg.GPIO_Pin_Number = GPIO_PIN_1;
    P_cnfg.GPIO_Mode = GPIO_Mode_Input_FLO;
    MCAL_GPIO_Init(GPIOA, &P_cnfg);
    // declaring pin 13 to be floating inputs
    P_cnfg.GPIO_Pin_Number = GPIO_PIN_13;
    P_cnfg.GPIO_Mode = GPIO_Mode_Input_FLO;
    MCAL_GPIO_Init(GPIOA, &P_cnfg);
    // pin 1 in portB  push pull output
    P_cnfg.GPIO_Pin_Number = GPIO_PIN_1;
    P_cnfg.GPIO_Mode = GPIO_Mode_Output_PP;
    P_cnfg.GPIO_OUTPUT_Speed = GPIO_SPEED_10MHz;
    MCAL_GPIO_Init(GPIOB, &P_cnfg);
    // declaring pin 13 to be floating inputs
    P_cnfg.GPIO_Pin_Number = GPIO_PIN_13;
    P_cnfg.GPIO_OUTPUT_Speed = GPIO_SPEED_10MHz;
    P_cnfg.GPIO_Mode = GPIO_Mode_Input_FLO;
    MCAL_GPIO_Init(GPIOB, &P_cnfg);
}
void Clock_init()
{
    // set on the clock for PORTA
    RCC_GPIOA_CLK_EN();
    // set on the clock for PORTB
    RCC_GPIOB_CLK_EN();
}

int main()
{
    Clock_init();
    GPIO_init_();
    while (1)
    {
        int bit_status = MCAL_GPIO_ReadPin(GPIOA,GPIO_PIN_1);
        // PORTA Pin 1 connected to External push up resistor
        // take action when read 0 from pin
        if (bit_status == 0)
        {
            MCAL_GPIO_TogglePin(GPIOB,GPIO_PIN_1);
            while (bit_status == 0)
                ; // while pressing is still
        }
        if (MCAL_GPIO_ReadPin(GPIOA,GPIO_PIN_13) == 1)
        {
            MCAL_GPIO_TogglePin(GPIOB,GPIO_PIN_13);
        }
    }
    // delay
    for (int i = 0; i < 100000; i++)
        ;

    return 0;
}
