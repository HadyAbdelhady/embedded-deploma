#ifndef SPI_H_
#define SPI_H_

#include <avr/io.h>
#include "Z:\Program_Files\Freq_used\utilities\Bit_Math.h"

// Uncomment the following line to use SPI in slave mode
// #define SPI_SLAVE_MODE

#define SPI_DDR DDRB
#define SPI_PORT PORTB
#define SPI_MOSI PB5
#define SPI_MISO PB6
#define SPI_SCK PB7
#define SPI_SS PB4

void SPI_init_master(uint8_t freq_div);
void SPI_init_slave();
uint8_t SPI_transfer(uint8_t data);

#endif /* SPI_H_ */