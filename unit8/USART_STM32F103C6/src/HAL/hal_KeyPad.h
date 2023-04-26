#ifndef _KEYPAD_
#define _KEYPAD_
#include "MCAL/mcal_stm32f103X6_gpio.h"

#define KeyPad_PORT              GPIOB

#define R0 GPIO_PIN_0
#define R1 GPIO_PIN_1
#define R2 GPIO_PIN_3
#define R3 GPIO_PIN_4
#define C0 GPIO_PIN_5
#define C1 GPIO_PIN_6
#define C2 GPIO_PIN_7
#define C3 GPIO_PIN_8
void init_Keypad(void);
char GetKey_Keypad(void);
#endif