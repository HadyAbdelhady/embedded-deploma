#include "alarmActuator.h"
#include "alarmMonitor.h"
#include "mainAlgo.h"
#include "pressure.h"
#include "Platform_Types.h"
#include "driver.h"
#include <stdlib.h>
int main()
{

	uint32 (*Pressure_state)() = &pressure_sensor;
	void (*Alarm_Actuator_state)() = &ActuatorState;
	void (*Alarm_monitor_state)() = &MonitorState;
	void (*Algo_State)() = &AlgoState;
	GPIO_INITIALIZATION();
	while (1)
	{
		Pressure_state();
		Alarm_Actuator_state();
		Alarm_monitor_state();
		Algo_State();
	}
}