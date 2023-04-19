#ifndef UART_H_
#define UART_H_

#include <stdint.h>

// Define clock frequency
#define F_CPU 8000000UL

// Macro to set a bit in a register
#define SETBIT(reg, bit, shift) ((reg) |= ((bit) << (shift)))

// Initialize UART with specified baud rate
void UART_init(uint16_t baud_rate);

// Write single character to UART
void UART_write_char(char data);

// Write null-terminated string to UART
void UART_write_string(const char *str);

// Read single character from UART
char UART_read_char(void);

#endif /* UART_H_ */
