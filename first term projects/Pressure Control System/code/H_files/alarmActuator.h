#ifndef __actuator__
#define __actuator__

typedef enum ActuatorState
{
    ActuatorINIT,
    ActuatorWAIT,
    AlarmON,
    AlarmOFF
} Act_State;
extern Act_State ActState;
void ActuatorState();
#endif