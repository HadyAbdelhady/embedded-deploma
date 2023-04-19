#ifndef _ALGO_
#define _ALGO_
#include "Platform_Types.h"
#include "pressure.h"
typedef enum Algostate
{
    Algo_NORMAL_PRESSURE,
    Algo_HIGH_PRESSURE
} Algo_Status;
extern uint32 Algo_pressure_threshold;
extern Algo_Status state;
void AlgoState();
#endif