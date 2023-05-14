// #include <avr/io.h>
#include <util/delay.h>
#include "spi.h"
#include "uart.h"
#include "max7219.h"
void communication_init();
void lab_1();
void lab_2();

int main()
{
    communication_init();
    MAX7219_init();

    while (1)
    {
        // lab_1();
        lab_2();
    }
}

void communication_init()
{
#ifdef SPI_SLAVE_MODE
    SPI_init_slave();
#else
    SPI_init_master(8);
#endif
    UART_init(8, Sync, Parity_Disabled, 1, 9600);
}
void lab_1()
{
    char str[] = "hello this is spi talking to uart";
    uint8_t len = sizeof(str) - 1; // Exclude null termination character
    for (uint8_t i = 0; i < len; i++)
        SPI_transfer((uint8_t)str[i]);
    UART_write_string(str);
    // Wait for some time before sending/receiving another byte
    _delay_ms(100);
}
void lab_2()
{
    MAX7219_display_number(0, 'H');
    MAX7219_display_number(0, 'i');
    MAX7219_display_number(0, '.');
    MAX7219_display_number(0, '!');
}
