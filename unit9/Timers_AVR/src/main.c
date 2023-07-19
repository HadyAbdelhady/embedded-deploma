#include "Timer.h"
#include <util/delay.h>
#include "Bit_Math.h"
#include "pwm.h"

#define LED_DDR DDRC
#define LED_PORT PORTC
#define Pin_Number 0

extern uint8_t Over_Flow_Number;
void Over_Flow(void)
{
	TOG_BIT(PORTC, 0);
	_delay_ms(500);
	PORTA = Over_Flow_Number;
}

extern uint8_t PWM_Over_Flow_Number;
extern uint8_t PWM_Compare_Number;

void Compare_Func(void)
{
	TOG_BIT(PORTB, 0);
	_delay_ms(100);
	PORTA = PWM_Compare_Number;
}
void Over_Flow_Func(void)
{
	TOG_BIT(PORTB, 1);
	_delay_ms(100);
	PORTC = PWM_Over_Flow_Number;
}



int main(void)
{
	SET_BIT(DDRC, 0);
	DDRA = 0xFF;
	sei();
	TIMER0_CALLBACK_CompareMatch_INTERRUPT(Over_Flow);
	Timer_Config_t Config = {CTC, TOIE_DISABLE, OCIE_ENABLE, PRESCALING_CLK8};
	TIMER0_GetCompare(0xF0);
	TIMER0_Init(&Config);

	///////////////////PWM//////////////////////

	DDRA = 0xFF;
	DDRB = 0xFF;
	DDRC = 0xFF;
	DDRD = 0xFF;

	volatile uint8_t value;
	PWM0_GetCompare(&value);
	PORTD = value;

	sei();
	PWM0_CALLBACK_CompareMatch_INTERRUPT(Compare_Func);
	PWM0_CALLBACK_Overflow_INTERRUPT(Over_Flow_Func);
	PWM_t PWM_Config = {Phase_Coreect_PWM, TOIE_ENABLE, OCIE_ENABLE, PRESCALING_CLK8, PWM_Non_INVERTING};
	PWM0_SetCompare(0x7F);
	PWM0_Init(&PWM_Config);

	///////////////////WDT//////////////////////

	SET_BIT(LED_DDR, Pin_Number); // Output pin 0
	_delay_ms(500);
	while (1)
	{
		WDT_ON(); // Reset if CPU stuck.
		TOG_BIT(LED_PORT, Pin_Number);
		_delay_ms(2000);
		WDT_OFF();
	}
}
