#include "uart.h"
#include <avr/io.h>
#include <util/delay.h>

// Define bit masks for UART control and status registers
#define UART_CTRL_REG_B (1 << RXEN) | (1 << TXEN)
#define UART_CTRL_REG_C (1 << UCSZ1) | (1 << UCSZ0)
#define UART_STATUS_REG_A (1 << RXC) | (1 << UDRE)

void UART_init(uint16_t baud_rate) {
    // Calculate UBRR value based on clock frequency and baud rate
    uint16_t ubrr = F_CPU/16/baud_rate - 1;
    
    // Set UBRRH and UBRRL registers for baud rate
    SETBIT(UBRRH, ubrr >> 8, 0);
    SETBIT(UBRRL, ubrr, 0);
    
    // Enable UART transmitter and receiver
    SETBIT(UCSRB, UART_CTRL_REG_B, 0);
    
    // Set data frame format to 8-bit
    SETBIT(UCSRC, UART_CTRL_REG_C, 0);
    SETBIT(UCSRC, 1, UCSZ0);
    SETBIT(UCSRC, 1, UCSZ1);
}

void UART_write_char(char data) {
    // Wait for data register to be empty
    while (!(UCSRA & (1 << UDRE)));
    
    // Write character to UART
    UDR = data;
}

void UART_write_string(const char *str) {
    // Send each character of string using UART_write_char()
    while (*str) {
        UART_write_char(*str++);
    }
}

char UART_read_char(void) {
    // Wait for character to be received
    while (!(UCSRA & (1 << RXC)));
    
    // Return received character
    return UDR;
}
