
/******************************************************************************
 *                              INCLUDES                                       *
 *******************************************************************************/
#include "Timer.h"
#include "Bit_Math.h"

/******************************************************************************
 *                               GLOBAL & EXTERN VARIABLES                     *
 *******************************************************************************/
Ptr_Func CALLBACK_OVER_FLOW;
Ptr_Func CALLBACK_COMPARE;
uint8_t Over_Flow_Number = 0;
Timer_Config_t *Global_configuartion;
/******************************************************************************
 *								 APIS IMPLEMENTATION			              *
 *******************************************************************************/

E_STATUS_t TIMER0_Init(Timer_Config_t *configuartion)
{
	E_STATUS_t Value = E_OK;
	if (NULL_PTR == configuartion)
	{
		Value = E_NOK;
	}
	else
	{
		Global_configuartion = configuartion;
		if ((Global_configuartion->mode == Normal) || (Global_configuartion->mode == CTC))
		{
			TCCR0 |= Global_configuartion->mode;
		}
		else
		{
			Value = E_NOK;
		}
		if ((Global_configuartion->CLK >= NO_CLK_SRC) && (Global_configuartion->CLK <= EXT_CLK_RISING))
		{
			TCCR0 |= Global_configuartion->CLK;
		}
		else
		{
			Value = E_NOK;
		}
		if ((Global_configuartion->Compare == OCIE_DISABLE) || (Global_configuartion->Compare == OCIE_ENABLE))
		{
			TIMSK |= Global_configuartion->Compare;
		}
		else
		{
			Value = E_NOK;
		}
		if ((Global_configuartion->Overflow == TOIE_DISABLE) || (Global_configuartion->Overflow == TOIE_ENABLE))
		{
			TIMSK |= Global_configuartion->Overflow;
		}
		else
		{
			Value = E_NOK;
		}
	}
	return Value;
}

E_STATUS_t TIMER0_Stop()
{
	E_STATUS_t Value = E_OK;
	CLR_BIT(TCCR0, CS00);
	CLR_BIT(TCCR0, CS01);
	CLR_BIT(TCCR0, CS02);
	return Value;
}

/*Does the TCNT0 counter start from TCNT0's value and count up to the overflow value?
Yes.
Does the Timer/Counter 0 count from 0 to OCR0 value in CTC mode?
Yes.*/

E_STATUS_t TIMER0_GetCompare(unsigned char *TicksNumber)
{
	/*The Output Compare Register contains an 8-bit value that is continuously compared with the
	counter value (TCNT0). A match can be used to generate an output compare interrupt, or to
	generate a waveform output on the OC0 pin*/
	E_STATUS_t Value = E_OK;
	*TicksNumber = OCR0;
	return Value;
}

E_STATUS_t TIMER0_SetCompare(uint8_t u8_TicksNumber)
{
	E_STATUS_t Value = E_OK;
	OCR0 = u8_TicksNumber;
	return Value;
}

E_STATUS_t TIMER0_GetCounter(unsigned char *TicksNumber)
{
	E_STATUS_t Value = E_OK;
	*TicksNumber = TCNT0;
	return Value;
}
E_STATUS_t TIMER0_SetCounter(uint8_t u8_TicksNumber)
{
	E_STATUS_t Value = E_OK;
	TCNT0 = u8_TicksNumber;
	return Value;
}

E_STATUS_t TIMER0_GetOverflow(unsigned char *TicksNumber)
{
	E_STATUS_t Value = E_OK;
	*TicksNumber = Over_Flow_Number;
	return Value;
}

E_STATUS_t TIMER0_SetOverflow(uint8_t u8_TicksNumber)
{
	E_STATUS_t Value = E_OK;
	Over_Flow_Number = u8_TicksNumber;
	return Value;
}

void TIMER0_CALLBACK_Overflow_INTERRUPT(Ptr_Func callback)
{
	CALLBACK_OVER_FLOW = callback;
}
void TIMER0_CALLBACK_CompareMatch_INTERRUPT(Ptr_Func callback)
{
	CALLBACK_COMPARE = callback;
}

void WDT_OFF(void)
{
	WDTCR |= (1 << WDTOE) | (1 << WDE);
	WDTCR = 0x00;
}

void WDT_ON(void)
{
	WDTCR |= (1 << WDP1) | (1 << WDP2) | (1 << WDE);
	CLR_BIT(WDTCR, WDP0);
}
