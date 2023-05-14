#include "spi.h"

#ifdef SPI_SLAVE_MODE
void SPI_init_slave()
{
    // Set MOSI and SCK as input pins
    SPI_DDR &= ~((1 << SPI_MOSI) | (1 << SPI_SCK));
    // Set MISO and SS as output pins
    SPI_DDR |= (1 << SPI_MISO) | (1 << SPI_SS);
    // Enable SPI, set as slave, clock rate fosc/16
    SPCR |= (1 << SPE);
}
#else
void SPI_init_master(uint8_t freq_div)
{
    // Set MOSI, SCK and SS as output pins
    SPI_DDR |= (1 << SPI_MOSI) | (1 << SPI_SCK) | (1 << SPI_SS);
    // Set MISO as input pin
    CLR_BIT(SPI_DDR, SPI_MISO);
    // Enable SPI, set as master, set clock rate
    SPCR |= (1 << SPE) | (1 << MSTR);
    switch (freq_div)
    {
    case 2:
        CLR_BIT(SPCR, SPR1);
        SET_BIT(SPCR, SPR0);
        break;
    case 4:
        SPCR &= ~((1 << SPR1) | (1 << SPR0));
        break;
    case 8:
        CLR_BIT(SPCR, SPR0);
        SET_BIT(SPCR, SPR1);
        break;
    case 16:
        SPCR |= (1 << SPR1) | (1 << SPR0);
        break;
    default:
        break;
    }
}
#endif

uint8_t SPI_transfer(uint8_t data)
{
    SPDR = data;
    // Wait for transmission to complete
    while (!(SPSR & (1 << SPIF)));
    return SPDR;
}
