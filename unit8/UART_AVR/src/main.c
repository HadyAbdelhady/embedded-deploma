#include "uart.h"

int main(void) {

    UART_init(8,0,0,1,9600); // Initialize UART with 8 data bits, no parity, 1 stop bit, and 9600 baud rate
    
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
