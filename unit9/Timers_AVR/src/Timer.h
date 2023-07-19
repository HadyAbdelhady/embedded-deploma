#ifndef TIMER
#define TIMER

/******************************************************************************
*                               INCLUDES			                          *
// *******************************************************************************/
#include <avr/interrupt.h>

/******************************************************************************
 *					Typedef-Defines-ENUMS	                				  *
 *******************************************************************************/

typedef void (*Ptr_Func)(void);
#define NULL_PTR ((void *)(0))

typedef enum
{
    Normal,
    CTC = 0x08
} Timer_Modes_t;

/*• Bit 0 – TOIE0: Timer/Counter0 Overflow Interrupt Enable
When the TOIE0 bit is written to one, and the I-bit in the Status Register is set (one), the
Timer/Counter0 Overflow interrupt is enabled.*/
typedef enum
{
    TOIE_DISABLE,
    TOIE_ENABLE
} TOIE_t;

/*• Bit 1 – OCIE0: Timer/Counter0 Output Compare Match Interrupt Enable
When the OCIE0 bit is written to one, and the I-bit in the Status Register is set (one), the
Timer/Counter0 Compare Match interrupt is enabled.*/
typedef enum
{
    OCIE_DISABLE ,
    OCIE_ENABLE = 0x02
} OCIE_t;

typedef unsigned char E_STATUS_t;
#define E_OK (E_STATUS_t)(0)
#define E_NOK (E_STATUS_t)(1)

typedef enum
{
    NO_CLK_SRC,
    NO_PRESCALING,
    PRESCALING_CLK8,
    PRESCALING_CLK64,
    PRESCALING_CLK256,
    PRESCALING_CLK1024,
    EXT_CLK_FALLING,
    EXT_CLK_RISING,
} TIMER_CLOCK_t;

/******************************************************************************
 *									STRUCT	                				  *
 *******************************************************************************/

typedef struct
{
    Timer_Modes_t mode;
    TOIE_t Overflow;
    OCIE_t Compare;
    TIMER_CLOCK_t CLK;
} Timer_Config_t;

/******************************************************************************
 *									APIS				                      *
 *******************************************************************************/

E_STATUS_t TIMER0_Init(Timer_Config_t *configuartion);
E_STATUS_t TIMER0_Stop();

E_STATUS_t TIMER0_GetCompare(unsigned char *TicksNumber);
E_STATUS_t TIMER0_SetCompare(uint8_t u8_TicksNumber);

E_STATUS_t TIMER0_GetCounter(unsigned char *TicksNumber);
E_STATUS_t TIMER0_SetCounter(uint8_t u8_TicksNumber);

E_STATUS_t TIMER0_GetOverflow(unsigned char *TicksNumber);
E_STATUS_t TIMER0_SetOverflow(uint8_t u8_TicksNumber);

void TIMER0_CALLBACK_Overflow_INTERRUPT(Ptr_Func callback);
void TIMER0_CALLBACK_CompareMatch_INTERRUPT(Ptr_Func callback);

void WDT_OFF(void);
void WDT_ON(void);
#endif