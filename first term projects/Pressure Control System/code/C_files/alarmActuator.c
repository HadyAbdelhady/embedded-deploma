#include "H_files\Platform_Types.h"
#include "driver.h"
#include "alarmActuator.h"
Act_State ActState=ActuatorINIT;
void ActuatorState()
{
	
    switch (ActState)
    {
    case ActuatorINIT:
    case ActuatorWAIT:
        ActState = ActuatorWAIT;
        break;
    case AlarmON:
        Set_Alarm_actuator(0);
        ActState = ActuatorWAIT;
        break;
    case AlarmOFF:
        Set_Alarm_actuator(1);
        ActState = ActuatorWAIT;
        break;
    default:
        break;
    }
}