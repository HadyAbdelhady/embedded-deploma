#ifndef UART_H_
#define UART_H_

#include <stdint.h>

// Define clock frequency

// Macro to set a bit in a register
#define SETBIT(reg, shift, bit) ((reg) |= ((bit) << (shift)))
typedef enum Connection_Mode
{
    Async,
    Sync
} Mode;
typedef enum parityMode
{
    Parity_Disabled,
    Parity_ODD,
    Parity_EVEN
} parity;

// Initialize UART with specified baud rate
void UART_init(uint8_t num_data, uint8_t mode, uint8_t parity, uint8_t stop, uint16_t baud_rate);
// Write single character to UART
void UART_write_char(char data);

// Write null-terminated string to UART
void UART_write_string(const char *str);

// Read single character from UART
char UART_read_char(void);

#endif /* UART_H_ */
