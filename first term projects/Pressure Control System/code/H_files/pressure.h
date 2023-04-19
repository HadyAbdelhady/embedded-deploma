#include "Platform_Types.h"

#ifndef _P_
#define _P_
typedef enum Pstate
{
    Pinit,
    Pread,
    Pwait
} P_state;
extern uint32 Pvalue;
extern P_state Pstate;
uint32 pressure_sensor();

#endif