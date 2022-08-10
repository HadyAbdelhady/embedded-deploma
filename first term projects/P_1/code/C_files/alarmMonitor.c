#include "driver.h"
#include "alarmActuator.h"
#include "alarmMonitor.h"
#include "pressure.h"
#include "mainAlgo.h"
Mon_State Monitor_State=MonitorWait;
void MonitorState()
{
	
    switch (Monitor_State)
    {
    case MonitorOFF:
        ActState = AlarmOFF;
        if (Pvalue > Algo_pressure_threshold)
            Monitor_State = MonitorON;
        else
            Monitor_State = MonitorOFF;
        break;
    case MonitorON:
        ActState = AlarmON;
        Monitor_State = MonitorWait;
        break;
    case MonitorWait:
        Monitor_State = MonitorOFF;
        Delay(500);
        break;
    default:
        break;
    }
}