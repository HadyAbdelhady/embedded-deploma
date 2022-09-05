#include "avr\io.h"
#include "util\delay.h"
#include "avr\interrupt.h"
#ifndef __AVR_ATmega32C1__
#define __AVR_ATmega32C1__
#endif
#define BASE *(volatile uint32_t *)(0x20)
#define GICR *(volatile uint32_t *)(BASE + 0x3B)
#define PORTD *(volatile uint32_t *)(BASE + 0x12)
#define DDRD *(volatile uint32_t *)(BASE + 0x11)
#define MCUCR *(volatile uint32_t *)(BASE + 0x35) // int0
#define MCUSR *(volatile uint32_t *)(BASE + 0x34) // int1
#define F_CPU 16000000UL
#define SET_BIT(VAR, BIT) (VAR) |= (1 << (BIT))
#define CLR_BIT(VAR, BIT) (VAR) &= ~(1 << (BIT))
#define TOG_BIT(VAR, BIT) (VAR) ^= (1 << (BIT))
#define GET_BIT(VAR, BIT) (((VAR) >> (BIT)) & 0x01)

void main()
{
    // output for ddrd
    SET_BIT(DDRD, 5);
    SET_BIT(DDRD, 6);
    SET_BIT(DDRD, 7);
    // logical change
    SET_BIT(MCUCR, 0);
    CLR_BIT(MCUCR, 1);
    // rising edge
    SET_BIT(MCUCR, 2);
    SET_BIT(MCUCR, 3);
    // rising edge
    SET_BIT(MCUSR, 6);
    // gicr enable
    SET_BIT(GICR, 5);
    SET_BIT(GICR, 6);
    SET_BIT(GICR, 7);
    sei();
    while (1)
    {
        CLR_BIT(PORTD, 5);
        CLR_BIT(PORTD, 6);
        CLR_BIT(PORTD, 7);
    }
}
ISR(INT0_vect)
{
    SET_BIT(PORTD,5);
    _delay_ms(2000);
}

ISR(INT1_vect)
{
    SET_BIT(PORTD,6);
    _delay_ms(2000);
}
ISR(INT2_vect)
{
    SET_BIT(PORTD,7);
    _delay_ms(2000);
}