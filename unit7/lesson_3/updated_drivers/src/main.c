#include "stm32f103_X6.h"
#include "mcal_stm32f103X6_gpio.h"
#include "hal_lcd.h"
#include "hal_keypad.h"

#define ZERO    0x01
#define ONE     0x79
#define TWO     0x24
#define THREE   0x30
#define FOUR    0x4C
#define FIVE    0x12
#define SIX     0x02
#define SEVEN   0x19
#define EIGHT   0x00
#define NINE    0x10
// GPIO_Pin_Config_t PinCfg;

void clock_init()
{
    // Enable clock GPIOA
    RCC_GPIOA_CLK_EN();
    // Enable clock GPIOB Bit 3 IOPBEN: IO port B clock enable
    RCC_GPIOB_CLK_EN();
}
void GPIO_init()
{
    // PA1 input HighZ Floating input (reset state)
    MCAL_GPIO_SET_Pin(GPIOB, GPIO_PIN_9, GPIO_Mode_Output_PP, GPIO_SPEED_10MHz);
    MCAL_GPIO_SET_Pin(GPIOB, GPIO_PIN_10, GPIO_Mode_Output_PP, GPIO_SPEED_10MHz);
    MCAL_GPIO_SET_Pin(GPIOB, GPIO_PIN_11, GPIO_Mode_Output_PP, GPIO_SPEED_10MHz);
    MCAL_GPIO_SET_Pin(GPIOB, GPIO_PIN_12, GPIO_Mode_Output_PP, GPIO_SPEED_10MHz);
    MCAL_GPIO_SET_Pin(GPIOB, GPIO_PIN_13, GPIO_Mode_Output_PP, GPIO_SPEED_10MHz);
    MCAL_GPIO_SET_Pin(GPIOB, GPIO_PIN_14, GPIO_Mode_Output_PP, GPIO_SPEED_10MHz);
    MCAL_GPIO_SET_Pin(GPIOB, GPIO_PIN_15, GPIO_Mode_Output_PP, GPIO_SPEED_10MHz);

}
void wait_ms(uint32_t time)
{
    uint32_t i, j;
    for (i = 0; i < time; i++)
        for (j = 0; j < 255; j++)
            ;
}
int main(void)
{

    clock_init();
    init_LCD();
    unsigned char key_pressed;
    Write_String_LCD("HEY");
    wait_ms(30);
    Clear_LCD();
    GPIO_init();
    unsigned char LCD_DISPLAY[11] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '0'};
    unsigned char DISPLAY[11] = {ZERO, ONE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, ZERO};
    for (unsigned char i = 0; i < 11; i++)
    {
        Write_char_LCD(LCD_DISPLAY[i]);
        MCAL_GPIO_WritePort(GPIOB, DISPLAY[i] << 9); /* write data on to the LED port */
        wait_ms(100);
        /* wait for 1 second */
    }

    Clear_LCD();
    init_Keypad();
    Write_String_LCD("Keypad is ready");
    wait_ms(30);
    Clear_LCD();

    while (1)
    {
        key_pressed = GetKey_Keypad();
        switch (key_pressed)
        {
        case 'A':
            break;
        case '?':
            Clear_LCD();
            break;
        default:
            Write_char_LCD(key_pressed);
            break;
        }
    }
}
