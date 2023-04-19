#include "mainAlgo.h"
uint32 Algo_pressure_threshold = 20;
Algo_Status state = Algo_HIGH_PRESSURE;
void AlgoState()
{
    switch (state)
    {
    case Algo_HIGH_PRESSURE:
        if (Pvalue > Algo_pressure_threshold)
        {
            state = Algo_HIGH_PRESSURE;
        }
        else
            state = Algo_NORMAL_PRESSURE;
        break;
    default:
        break;
    }
}