#ifndef MAX7219 
#define MAX2719
#include "Bit_Math.h"
#include "stdio.h"
#include "stm32f103_X6.h"
#define MAX7219_DECODE_MODE   0x09
#define MAX7219_INTENSITY     0x0A
#define MAX7219_SCAN_LIMIT    0x0B
#define MAX7219_SHUTDOWN      0x0C
#define MAX7219_DISPLAY_TEST  0x0F

void MAX7219_display_number(uint8_t digit, uint8_t value);
void MAX7219_init();
void MAX7219_clear_display();
#endif