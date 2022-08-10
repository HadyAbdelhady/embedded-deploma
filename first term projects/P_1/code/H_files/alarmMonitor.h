#ifndef __monitor__
#define __monitor__
typedef enum MonitorState
{
    MonitorOFF,
    MonitorON,
    MonitorWait
} Mon_State;

extern Mon_State Monitor_State;

void MonitorState();
#endif