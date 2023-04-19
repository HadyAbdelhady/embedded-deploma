#include "uart.h"
#include <avr/io.h>
#include <util/delay.h>

// This function initializes the UART with the given parameters.
// This function sets the UBRR value based on the given baud rate and clock frequency
// and configures the data frame format, parity, stop bits, and mode.
// It also enables the receiver, transmitter, and receive complete interrupt.

void UART_init(uint8_t num_data, uint8_t mode, uint8_t parity, uint8_t stop, uint16_t baud_rate)
{

    // Setting baud rate
    uint16_t ubrr = F_CPU / 16 / baud_rate - 1;
    UBRRH = (uint8_t)(ubrr >> 8);
    UBRRL = (uint8_t)(ubrr);

    // Setting data frame size
    // num_data: the number of data bits in the data frame
    switch (num_data)
    {
    case 5:
        SETBIT(UCSRC, UCSZ0, 0);
        break;
    case 6:
        SETBIT(UCSRC, UCSZ0, 1);
        break;
    case 7:
        SETBIT(UCSRC, UCSZ1, 1);
        break;
    case 8:
        SETBIT(UCSRC, UCSZ0, 1);
        SETBIT(UCSRC, UCSZ1, 1);
        break;
    case 9:
        SETBIT(UCSRC, UCSZ0, 1);
        SETBIT(UCSRC, UCSZ1, 1);
        SETBIT(UCSRB, UCSZ2, 1);
        break;
    default:
        break;
    }
    // Setting parity
    // parity: the parity mode (0 for disabled, 1 for odd parity, or 2 for even parity)
    switch (parity)
    {
    case 0:
        SETBIT(UCSRC, UPM0, 0);
        SETBIT(UCSRC, UPM1, 0);
        break;
    case 1:
        SETBIT(UCSRC, UPM1, 1);
        SETBIT(UCSRC, UPM0, 0);
        break;
    case 2:
        SETBIT(UCSRC, UPM1, 1);
        SETBIT(UCSRC, UPM0, 1);
        break;
    default:
        break;
    }

    // Setting stop bits
    // stop: the number of stop bits (1 or 2)

    switch (stop)
    {
    case 1:
        SETBIT(UCSRC, USBS, 0);
        break;
    case 2:
        SETBIT(UCSRC, USBS, 1);
        break;
    default:
        break;
    }

    // Setting mode
    // mode: the UART mode (0 for asynchronous or 1 for synchronous)

    switch (mode)
    {
    case 0:
        SETBIT(UCSRC, UMSEL, 0);
        break;
    case 1:
        SETBIT(UCSRC, UMSEL, 1);
        break;
    default:
        break;
    }

    // Enabling receiver, transmitter, and receive complete interrupt
    SETBIT(UCSRB, RXEN, 1);
    SETBIT(UCSRB, TXEN, 1);
    SETBIT(UCSRB, RXCIE, 1);
}

void UART_write_char(char data)
{
    // Wait for data register to be empty
    while (!(UCSRA & (1 << UDRE)))
        ;

    // Write character to UART
    UDR = data;
}

void UART_write_string(const char *str)
{
    // Send each character of string using UART_write_char()
    while (*str)
    {
        UART_write_char(*str++);
    }
}

char UART_read_char(void)
{
    // Wait for character to be received
    while (!(UCSRA & (1 << RXC)))
        ;

    // Return received character
    return UDR;
}
