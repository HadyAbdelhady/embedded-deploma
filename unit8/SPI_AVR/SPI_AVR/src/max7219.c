#include "max7219.h"
#include "spi.h"
void max7219_write_register(uint8_t reg, uint8_t data)
{
    // Select the MAX7219
    CLR_BIT(PORTB, SPI_SS);
    // Send the register address followed by the data
    SPI_transfer(reg);
    SPI_transfer(data);

    // Deselect the MAX7219
    SET_BIT(PORTB, SPI_SS);
}
void MAX7219_init()
{
    // Turn off the display test mode
    max7219_write_register(MAX7219_DISPLAY_TEST, 0);
    // Set the scan limit to display all digits (digit 0-7)
    max7219_write_register(MAX7219_SCAN_LIMIT, 7);
    // Set the decode mode to "No decode" for all digits
    max7219_write_register(MAX7219_DECODE_MODE, 0);
    // Set the intensity to the maximum value (15)
    max7219_write_register(MAX7219_INTENSITY, 15);
    // Turn on the display
    max7219_write_register(MAX7219_SHUTDOWN, 1);
}
void MAX7219_display_number(uint8_t digit, uint8_t value)
{
    max7219_write_register(digit + 1, value);
}

void MAX7219_clear_display()
{
    for (uint8_t i = 0; i <= 7; i++)
        max7219_write_register(i, 0);
}