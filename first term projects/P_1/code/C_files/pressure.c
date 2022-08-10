#include "pressure.h"
#include "Platform_Types.h"
#include "driver.h"

P_state Pstate = Pinit;
uint32 Pvalue;
uint32 pressure_sensor()
{
    switch (Pstate)
    {
    case Pinit:
        Pstate = Pread;
        break;
    case Pread:
        Pvalue = getPressureVal();
        Pstate = Pwait;
        break;
    case Pwait:
        Delay(1000);
        Pstate = Pread;
        break;
    default:
        break;
    }
    return Pvalue;
}