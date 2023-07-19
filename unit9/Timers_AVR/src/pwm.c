
/******************************************************************************
 *                              INCLUDES                                       *
 *******************************************************************************/

#include "pwm.h"
#include "Bit_Math.h"

/******************************************************************************
 *                               GLOBAL & EXTERN VARIABLES                     *
 *******************************************************************************/
Ptr_Func PWM_CALLBACK_OVER_FLOW;
Ptr_Func PWM_CALLBACK_COMPARE;
uint8_t PWM_Compare_Number;
uint8_t PWM_Over_Flow_Number;
PWM_t *PWM_Global_configuartion;
/******************************************************************************
 *								 APIS IMPLEMENTATION			              *
 *******************************************************************************/

void PWM0_Init(PWM_t *configuartion)
{
	PWM_Global_configuartion = configuartion;
	if ((PWM_Global_configuartion->Mode == Fast_PWM) || (PWM_Global_configuartion->Mode == Phase_Coreect_PWM))
	{
		// TCCR0 |= PWM_Global_configuartion->Mode;
		if (PWM_Global_configuartion->Mode == Fast_PWM)
		{
			SET_BIT(TCCR0, WGM00);
			SET_BIT(TCCR0, WGM01);
		}
		else
		{
			SET_BIT(TCCR0, WGM00);
			CLR_BIT(TCCR0, WGM01);
		}
	}
	if ((PWM_Global_configuartion->CLK >= NO_CLK_SRC) && (PWM_Global_configuartion->CLK <= EXT_CLK_RISING))
	{
		TCCR0 |= PWM_Global_configuartion->CLK;
	}

	if ((PWM_Global_configuartion->Compare == OCIE_DISABLE) || (PWM_Global_configuartion->Compare == OCIE_ENABLE))
	{
		TIMSK |= PWM_Global_configuartion->Compare;
	}

	if ((PWM_Global_configuartion->Overflow == TOIE_DISABLE) || (PWM_Global_configuartion->Overflow == TOIE_ENABLE))
	{
		TIMSK |= PWM_Global_configuartion->Overflow;
	}

	if ((PWM_Global_configuartion->Invering == PWM_INVERTING) || (PWM_Global_configuartion->Invering == PWM_Non_INVERTING))
	{
		// TCCR0 |= PWM_Global_configuartion->Invering;
		if (PWM_Global_configuartion->Invering == PWM_INVERTING)
		{
			SET_BIT(TCCR0, COM00);
			SET_BIT(TCCR0, COM01);
		}
		else
		{
			CLR_BIT(TCCR0, COM00);
			SET_BIT(TCCR0, COM01);
		}
	}
}

void PWM0_Stop()
{
	CLR_BIT(TCCR0, CS00);
	CLR_BIT(TCCR0, CS01);
	CLR_BIT(TCCR0, CS02);
}

/*Does the TCNT0 counter start from TCNT0's value and count up to the overflow value?
Yes.
Does the Timer/Counter 0 count from 0 to OCR0 value in CTC mode?
Yes.*/

void PWM0_GetCompare(unsigned char *TicksNumber)
{
	/*The Output Compare Register contains an 8-bit value that is continuously compared with the
	counter value (TCNT0). A match can be used to generate an output compare interrupt, or to
	generate a waveform output on the OC0 pin*/
	*TicksNumber = OCR0;
}

void PWM0_SetCompare(uint8_t TicksNumber)
{

	OCR0 = TicksNumber;
}
void PWM0_GetCounter(unsigned char *TicksNumber)
{
	*TicksNumber = TCNT0;
}
void PWM0_SetCounter(uint8_t TicksNumber)
{
	TCNT0 = TicksNumber;
}

void PWM0_GetOverflow(unsigned char *TicksNumber)
{

	*TicksNumber = PWM_Over_Flow_Number;
}

void PWM0_SetOverflow(uint8_t TicksNumber)
{
	PWM_Over_Flow_Number = TicksNumber;
}

void PWM0_CALLBACK_Overflow_INTERRUPT(Ptr_Func callback)
{
	PWM_CALLBACK_OVER_FLOW = callback;
}

void PWM0_CALLBACK_CompareMatch_INTERRUPT(Ptr_Func callback)
{
	PWM_CALLBACK_COMPARE = callback;
}

ISR(TIMER0_COMP_vect)
{
	PWM_Compare_Number++;
	PWM_CALLBACK_COMPARE();
}

ISR(TIMER0_OVF_vect)
{
	PWM_Over_Flow_Number++;
	PWM_CALLBACK_OVER_FLOW();
}
