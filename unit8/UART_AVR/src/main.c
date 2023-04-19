#include "uart.h"

int main(void) {
    // Initialize UART with baud rate of 9600
    UART_init(9600);
    
    // Loop forever
    while (1) {
        // Send "Hello, world!" string over UART
        UART_write_string("Hello, world!\n");
        
        // Read single character from UART and send it back
        char data = UART_read_char();
        UART_write_char(data);
    }
    
    return 0;
}
