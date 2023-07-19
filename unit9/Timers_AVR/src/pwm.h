
#ifndef PWM_H_
#define PWM_H_

/******************************************************************************
 *                               INCLUDES			                          *
 *******************************************************************************/
#include "Timer.h"

/******************************************************************************
 *					Typedef-Defines-ENUMS	                				  *
 *******************************************************************************/

typedef enum
{
	Fast_PWM = 0x40,
	Phase_Coreect_PWM = 0x08
} PWM_Modes_t;

typedef enum
{
	PWM_INVERTING = 0x30,
	PWM_Non_INVERTING = 0x10
} PWM_INV_t;

/******************************************************************************
 *									STRUCT	                				  *
 *******************************************************************************/
typedef struct
{
	PWM_Modes_t Mode;
	TOIE_t Overflow;
	OCIE_t Compare;
	TIMER_CLOCK_t CLK;
	PWM_INV_t Invering;
} PWM_t;

/******************************************************************************
 *									APIS				                      *
 *******************************************************************************/
void PWM0_Init(PWM_t *configuartion);
void PWM0_Stop();

void PWM0_GetCompare(unsigned char *TicksNumber);
void PWM0_SetCompare(uint8_t TicksNumber);

void PWM0_GetCounter(unsigned char *TicksNumber);
void PWM0_SetCounter(uint8_t TicksNumber);

void PWM0_GetOverflow(unsigned char *TicksNumber);
void PWM0_SetOverflow(uint8_t TicksNumber);

void PWM0_CALLBACK_Overflow_INTERRUPT(Ptr_Func callback);
void PWM0_CALLBACK_CompareMatch_INTERRUPT(Ptr_Func callback);

#endif /* PWM_H_ */